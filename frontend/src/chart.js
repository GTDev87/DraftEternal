import React, { Children } from 'react';
import PropTypes from 'prop-types';

import { chartTheme } from '@data-ui/theme';
import { Axis, AxisBottom, AxisTop, AxisLeft, AxisRight } from '@vx/axis';
import { curveBasis } from '@vx/curve';
import localPoint from '@vx/event/build/localPoint';
import { Group } from '@vx/group';
import { PatternLines } from '@vx/pattern';
import { withScreenSize } from '@vx/responsive';
import { scaleBand, scaleLinear } from '@vx/scale';
import { AreaClosed, LinePath, Bar } from '@vx/shape';
import { Text } from '@vx/text';
import TooltipWithBounds, { withTooltipPropTypes as vxTooltipPropTypes } from '@vx/tooltip/build/tooltips/TooltipWithBounds';

import { max, mean, extent as d3Extent, histogram as d3Histogram } from 'd3-array';
import { scaleLinear as d3ScaleLinear } from 'd3-scale';
import { NodeGroup } from 'react-move';

// for annoying warning
Axis.propTypes.label = PropTypes.oneOfType([PropTypes.element, PropTypes.string]);
AxisBottom.propTypes.label = PropTypes.oneOfType([PropTypes.element, PropTypes.string]);
AxisTop.propTypes.label = PropTypes.oneOfType([PropTypes.element, PropTypes.string]);
AxisLeft.propTypes.label = PropTypes.oneOfType([PropTypes.element, PropTypes.string]);
AxisRight.propTypes.label = PropTypes.oneOfType([PropTypes.element, PropTypes.string]);

const gridStylesShape = PropTypes.shape({
  stroke: PropTypes.string,
  strokeWidth: PropTypes.number,
});

function kernelParabolic(smoothing = 5) {
  return val => (
    Math.abs(val / smoothing) <= 1
      ? 0.75 * ((1 - (val * val)) / smoothing)
      : 0
  );
}

function kernelGaussian() {
  return val => (
    (1 / Math.sqrt(2 * Math.PI)) * Math.exp(-0.5 * (val * val))
  );
}

function addDensityAndCumulativeValuesToBins(bins) {
  let cumulative = 0;
  bins.forEach((bin) => {
    cumulative += (isNaN(bin.count) ? 0 : bin.count);
    bin.cumulative = cumulative;
  });

  const total = cumulative;
  bins.forEach((bin) => {
    bin.density = bin.count / total;
    bin.cumulativeDensity = bin.cumulative / total;
  });
}

const sortBins = (a, b) => caseInsensitiveSort(a.bin, b.bin);

function binCategoricalData({ rawDataByIndex, valueAccessor, binValues = null }) {
  const binsByIndex = {};

  Object.keys(rawDataByIndex).forEach((index) => {
    const data = rawDataByIndex[index];
    const bins = {};

    data.forEach((datum) => {
      const bin = valueAccessor(datum);
      bins[bin] = bins[bin] || { bin, data: [], count: 0, id: bin };
      bins[bin].data.push(datum);
      bins[bin].count += 1;
    });

    // convert to an array of bins
    if (binValues) {
      binsByIndex[index] = binValues.map(bin => (bins[bin] || { bin, count: 0, data: [] }));
    } else {
      binsByIndex[index] = Object.values(bins).sort(sortBins);
    }
  });

  return binsByIndex;
}

function binNumericData({
  allData,
  binCount = 10,
  binValues,
  limits,
  rawDataByIndex,
  valueAccessor,
}) {
  const binsByIndex = {};
  const histogram = d3Histogram();
  let extent = d3Extent(
    [
      ...allData.map(valueAccessor),
      ...allData.map(d => (valueAccessor(d) + 1))
    ]
  ); /* change add epsilon*/

  // Hack
  if(!binValues){
    const range = extent[1] - extent[0];
    binCount = (range) < binCount ? range : binCount;
  }
  // End Hack

  if (binValues) { // account for extent of binValues if passed
    const binExtent = d3Extent(binValues);
    extent = [
      Math.min(binExtent[0], extent[0]),
      Math.max(binExtent[1], extent[1]),
    ];
  }
  const scale = d3ScaleLinear().domain(extent).nice(binCount);

  console.log("binValues = %j", binValues);
  console.log("extent = %j", extent);
  console.log("scale = %j", scale);
  console.log("scale.domain() = %j", scale.domain());
  console.log("binCount = %j", binCount);
  console.log("limits = %j", limits);

  histogram
    .domain(limits || scale.domain())
    .thresholds(binValues || scale.ticks(binCount));

  function trimSeries(series) {
    series.reverse();
    let removed =
      series
        .reduce((memo, ele) => memo.concat([(memo.length !== 0 ? memo[memo.length - 1] : 0) + ele.length]), [])
        .filter((ele) => ele === 0)
        .length;

    return series.reverse().slice(0, -1 * removed);
  }

  Object.keys(rawDataByIndex).forEach((index) => {
    const data = rawDataByIndex[index];
    const seriesBins = histogram.value(valueAccessor)(data);

    // we remove the last bin because n bin thresholds give gives n+1 bins
    // if binValues is not specified, our last threshold is the upper bound
    // of the data so the final bin should always be zero

    const trimmedBins =
      binValues
        ? seriesBins
        : trimSeries(seriesBins);

    binsByIndex[index] = trimmedBins.map((bin, i) => ({
      bin0: bin.x0,
      bin1: bin.x1,
      data: bin,
      count: bin.length,
      id: i.toString(),
    }));

    // warn JIC
    if (trimmedBins.length < seriesBins.length && seriesBins[seriesBins.length - 1].count > 0) {
      console.warn('threw away non-zero bin');
    }
  });

  return binsByIndex;
}

function collectDataFromChildSeries(children) {
  let allRawData = [];
  let allBinnedData = [];

  const rawDataByIndex = {};
  const binnedDataByIndex = {};

  Children.forEach(children, (Child, i) => {
    const name = componentName(Child);

    if (isSeries(name)) {
      const rawData = Child.props.rawData;
      const binnedData = Child.props.binnedData;

      if (rawData && rawData.length > 0) {
        rawDataByIndex[i] = rawData;
        allRawData = allRawData.concat(rawData);
      }
      if (binnedData && binnedData.length > 0) {
        binnedDataByIndex[i] = binnedData;
        allBinnedData = allBinnedData.concat(binnedData);
      }
    }
  });

  return { allBinnedData, allRawData, binnedDataByIndex, rawDataByIndex };
}

function collectBinnedDataFromChildSeries({
  children,
  binCount,
  binType,
  binValues,
  limits,
  valueAccessor,
}) {
  const {
    allRawData,
    rawDataByIndex,
    binnedDataByIndex,
  } = collectDataFromChildSeries(children);

  let result = binnedDataByIndex;

  if (Object.keys(binnedDataByIndex).length === 0) {
    const binningFunc = binType === 'numeric' ? binNumericData : binCategoricalData;

    result = binningFunc({
      allData: allRawData,
      rawDataByIndex,
      valueAccessor,
      limits,
      binCount,
      binValues,
    });
  }

  Object.values(result).forEach((bins) => {
    addDensityAndCumulativeValuesToBins(bins);
  });

  return result;
}

function componentName(component) {
  if (component && component.type) {
    return component.type.displayName || component.type.name || 'Component';
  }
  return 'Component';
}


function isAxis(name) {
  return (/axis/gi).test(name);
}

function isSeries(name) {
  return (/series/gi).test(name);
}

function kernelDensityEstimator(kernel, bins) {
  return values => (
    bins.map(bin => ({
      bin,
      value: mean(values, v => kernel(bin - v)),
    }))
  );
}

let numericBinnedDatumShape = PropTypes.shape({
  id: PropTypes.string.isRequired,
  bin0: PropTypes.number.isRequired,
  bin1: PropTypes.number.isRequired,
  count: PropTypes.number.isRequired,

  cumulative: PropTypes.number,
  density: PropTypes.number,
  cumulativeDensity: PropTypes.number,
});

let categoricalBinnedDatumShape = PropTypes.shape({
  id: PropTypes.string.isRequired,
  bin: PropTypes.string.isRequired,
  count: PropTypes.number.isRequired,

  cumulative: PropTypes.number,
  density: PropTypes.number,
  cumulativeDensity: PropTypes.number,
});

const binnedDataShape = PropTypes.arrayOf(
  PropTypes.oneOfType([
    numericBinnedDatumShape,
    categoricalBinnedDatumShape,
  ]),
);


let BarSeries = ({
  animated,
  binnedData,
  binScale,
  fill,
  fillOpacity,
  horizontal,
  onClick,
  onMouseMove,
  onMouseLeave,
  stroke,
  strokeWidth,
  valueKey,
  barFn,
  valueScale,
}) => {
  if (!binScale || !valueScale || !binnedData || binnedData.length === 0) return null;

  const maxBarLength = Math.max(...valueScale.range());

  // @TODO with custom bin values, bin1 - bin0 may be different for each bar, account for this
  const barWidth = binScale.bandwidth
    ? binScale.bandwidth() // categorical
    : Math.abs(binScale(binnedData[0].bin1) - binScale(binnedData[0].bin0)); // numeric

  return (
    <Group>
      {animated && (
        <AnimatedBarSeries
          binnedData={binnedData}
          binScale={binScale}
          horizontal={horizontal}
          fill={fill}
          fillOpacity={fillOpacity}
          onClick={onClick}
          onMouseMove={onMouseMove}
          onMouseLeave={onMouseLeave}
          stroke={stroke}
          strokeWidth={strokeWidth}
          valueKey={valueKey}
          valueScale={valueScale}
          barFn={barFn}
        />
      )}

      {!animated &&
        binnedData.map((d, i) => {
          const binPosition = binScale(d.bin || (horizontal ? d.bin1 : d.bin0));
          const barLength = horizontal
            ? valueScale(d[valueKey])
            : maxBarLength - valueScale(d[valueKey]);
          const color = d.fill || callOrValue(fill, d, i);

          let x = horizontal ? 0 : binPosition;
          let y = horizontal ? binPosition : maxBarLength - barLength;
          let width = horizontal ? barLength : barWidth;
          let height = horizontal ? barWidth : barLength;

          let dimensions = { x, y, width, height };

          return (
            <Group>
              <Bar
                key={`bar-${binPosition}`}
                x={x}
                y={y}
                width={width}
                height={height}
                fill={color}
                fillOpacity={
                  typeof fillOpacity !== 'undefined' ? fillOpacity : callOrValue(fillOpacity, d, i)
                }
                stroke={d.stroke || callOrValue(stroke, d, i)}
                strokeWidth={d.strokeWidth || callOrValue(strokeWidth, d, i)}
                onClick={
                  onClick &&
                  (() => (event) => {
                    onClick({ event, data: binnedData, datum: d, color, index: i });
                  })
                }
                onMouseMove={
                  onMouseMove &&
                  (() => (event) => {
                    onMouseMove({ event, data: binnedData, datum: d, color, index: i });
                  })
                }
                onMouseLeave={onMouseLeave && (() => onMouseLeave)}
              />
              {barFn && barFn({ ...dimensions, ...d }) /* CHANGE */}
            </Group>
          );
        })}
    </Group>
  );
}

BarSeries.propTypes = {
  animated: PropTypes.bool,
  rawData: PropTypes.array, // eslint-disable-line react/no-unused-prop-types
  binnedData: binnedDataShape,
  fill: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  fillOpacity: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  horizontal: PropTypes.bool,
  stroke: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  strokeWidth: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  valueKey: PropTypes.string,
  onClick: PropTypes.func,

  // likely injected by parent Histogram
  binScale: PropTypes.func,
  valueScale: PropTypes.func,
  onMouseMove: PropTypes.func,
  onMouseLeave: PropTypes.func,
  // renderLabel: PropTypes.func
};
BarSeries.defaultProps = {
  animated: true,
  rawData: [],
  binnedData: [],
  binScale: null,
  fill: chartTheme.colors.default,
  fillOpacity: 0.7,
  horizontal: false,
  onClick: null,
  onMouseMove: null,
  onMouseLeave: null,
  stroke: '#FFFFFF',
  strokeWidth: 1,
  valueKey: 'count',
  valueScale: null
};
BarSeries.displayName = 'BarSeries';

const axisStylesShape = PropTypes.shape({
  stroke: PropTypes.string,
  strokeWidth: PropTypes.number,
  label: PropTypes.shape({
    left: PropTypes.object,
    right: PropTypes.object,
    bottom: PropTypes.object,
    top: PropTypes.object,
  }),
});

const tickStylesShape = PropTypes.shape({
  stroke: PropTypes.string,
  tickLength: PropTypes.number,
  label: PropTypes.shape({
    left: PropTypes.object,
    right: PropTypes.object,
    bottom: PropTypes.object,
    top: PropTypes.object,
  }),
});



const XAxis = ({
  axisStyles,
  label,
  top,
  left,
  numTicks,
  orientation,
  scale,
  tickFormat,
  tickLabelComponent,
  tickStyles,
  tickValues,
}) => {
  if (!scale) return null;
  const Axis = orientation === 'bottom' ? AxisBottom : AxisTop;

  console.log("label = %j", label);

  return (
    <Axis
      top={top}
      left={left}
      hideTicks={false}
      hideZero={false}
      label={
        label
        // typeof label === 'string' && axisStyles.label ?
        //   <text {...(axisStyles.label || {})[orientation]}>
        //     {label}
        //   </text>
        //   : label
      }
      numTicks={numTicks}
      scale={scale}
      stroke={axisStyles.stroke}
      strokeWidth={axisStyles.strokeWidth}
      tickFormat={tickFormat}
      tickLength={tickStyles.tickLength}
      tickStroke={tickStyles.stroke}
      tickLabelComponent={tickLabelComponent || (tickStyles.label &&
        <text {...(tickStyles.tickLabel || {})[orientation]} />
      )}
      tickValues={tickValues}
    />
  );
};

XAxis.propTypes = {
  axisStyles: axisStylesShape,
  label: PropTypes.oneOfType([PropTypes.string, PropTypes.element]),
  numTicks: PropTypes.number,
  orientation: PropTypes.oneOf(['bottom', 'top']),
  tickStyles: tickStylesShape,
  tickLabelComponent: PropTypes.element,
  tickFormat: PropTypes.func,
  tickValues: PropTypes.arrayOf(PropTypes.oneOfType([PropTypes.number, PropTypes.string])),

  // probably injected by parent
  top: PropTypes.number,
  left: PropTypes.number,
  scale: PropTypes.func
};
XAxis.defaultProps = {
  axisStyles: {},
  label: null,
  left: 0,
  numTicks: null,
  orientation: 'bottom',
  scale: null,
  tickFormat: null,
  tickLabelComponent: null,
  tickStyles: {},
  top: 0,
  tickValues: undefined
};
XAxis.displayName = 'XAxis';

let YAxis = ({
  axisStyles,
  label,
  top,
  left,
  numTicks,
  orientation,
  scale,
  tickFormat,
  tickLabelComponent,
  tickStyles,
  tickValues,
}) => {
  if (!scale) return null;

  const Axis = orientation === 'left' ? AxisLeft : AxisRight;

  let [min, max] = scale.domain(); /* change */

  console.log("label = %j", label);
  console.log(label);
  console.log("axisStyles.label = %j", axisStyles.label);

  return (
    <Axis
      top={top}
      left={left}
      hideTicks={false}
      hideZero={false}
      label={
        label
        // typeof label === 'string' && axisStyles.label ?
        // <text {...(axisStyles.label || {})[orientation]}>
        //   {label}
        // </text>
        // : (label)
      }
      numTicks={Math.min(numTicks, max - min)} /* CHANGE */
      scale={scale}
      stroke={axisStyles.stroke}
      strokeWidth={axisStyles.strokeWidth}
      tickFormat={tickFormat}
      tickLength={tickStyles.tickLength}
      tickStroke={tickStyles.stroke}
      tickLabelComponent={tickLabelComponent || (tickStyles.label &&
        <text {...(tickStyles.label || {})[orientation]} />
      )}
      tickValues={tickValues}
    />
  );
}

YAxis.propTypes = {
  axisStyles: axisStylesShape,
  label: PropTypes.oneOfType([PropTypes.string, PropTypes.element]),
  numTicks: PropTypes.number,
  orientation: PropTypes.oneOf(['left', 'right']),
  tickStyles: tickStylesShape,
  tickLabelComponent: PropTypes.element,
  tickFormat: PropTypes.func,
  tickValues: PropTypes.arrayOf(PropTypes.oneOfType([PropTypes.number, PropTypes.string])),

  // probably injected by parent
  top: PropTypes.number,
  left: PropTypes.number,
  scale: PropTypes.func
};
YAxis.defaultProps = {
  axisStyles: {},
  innerHeight: null,
  label: null,
  left: 0,
  numTicks: 5,
  orientation: 'left',
  scale: null,
  tickFormat: null,
  tickLabelComponent: null,
  tickStyles: {},
  tickValues: undefined,
  top: 0
};
YAxis.displayName = 'YAxis';




let AnimatedDensitySeries = ({
  densityData,
  fill,
  fillOpacity,
  horizontal,
  keyAccessor,
  getX,
  getY,
  showArea,
  showLine,
  stroke,
  strokeWidth,
  strokeDasharray,
  strokeLinecap,
  xScale,
  yScale,
}) => {
  const maxY = Math.max(...yScale.range());
  return (
    <NodeGroup
      data={densityData}
      keyAccessor={keyAccessor}
      start={(d) => {
        if (horizontal) return { x: 0, y: yScale.invert ? yScale(getY(d)) : getY(d) };
        return { x: xScale.invert ? xScale(getX(d)) : getX(d), y: maxY };
      }}
      enter={(d, i) => ({
        x: [xScale.invert ? xScale(getX(d)) : getX(d)],
        y: [yScale.invert ? yScale(getY(d)) : getY(d)],
        fill: [d.fill || fill],
        stroke: [d.stroke || stroke],
        timing: { duration: 300, delay: 10 * i },
      })}
      update={(d, i) => ({
        x: [xScale.invert ? xScale(getX(d)) : getX(d)],
        y: [yScale.invert ? yScale(getY(d)) : getY(d)],
        fill: [d.fill || fill],
        stroke: [d.stroke || stroke],
        timing: { duration: 300, delay: 10 * i },
      })}
      leave={(d, i) => ({
        x: xScale.invert ? xScale(getX(d)) : getX(d),
        y: horizontal ? 0 : maxY,
        timing: { duration: 300, delay: 5 * i },
      })}
    >
      {modifiedData => (
        <Group style={{ pointerEvents: 'none' }}>
          {showArea &&
            <AreaClosed
              data={modifiedData}
              x={d => (xScale.invert ? xScale.invert(d.state.x) : d.state.x)}
              y={d => (yScale.invert ? yScale.invert(d.state.y) : d.state.y)}
              xScale={xScale}
              yScale={yScale}
              fill={fill}
              fillOpacity={fillOpacity}
              stroke="transparent"
              strokeWidth={strokeWidth}
              curve={curveBasis}
            />}
          {showLine && strokeWidth > 0 &&
            <LinePath
              data={modifiedData}
              x={d => (xScale.invert ? xScale.invert(d.state.x) : d.state.x)}
              y={d => (yScale.invert ? yScale.invert(d.state.y) : d.state.y)}
              xScale={xScale}
              yScale={yScale}
              stroke={stroke}
              strokeWidth={strokeWidth}
              strokeDasharray={strokeDasharray}
              strokeLinecap={strokeLinecap}
              curve={curveBasis}
              glyph={null}
            />}
        </Group>
      )}
    </NodeGroup>
  );
}

AnimatedDensitySeries.propTypes = {
  densityData: PropTypes.array.isRequired, // @TODO shape
  fill: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  fillOpacity: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  getX: PropTypes.func.isRequired,
  getY: PropTypes.func.isRequired,
  horizontal: PropTypes.bool,
  keyAccessor: PropTypes.func,
  showArea: PropTypes.bool,
  showLine: PropTypes.bool,
  stroke: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  strokeDasharray: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  strokeLinecap: PropTypes.oneOf(['butt', 'square', 'round', 'inherit']),
  strokeWidth: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  xScale: PropTypes.func.isRequired,
  yScale: PropTypes.func.isRequired
};
AnimatedDensitySeries.defaultProps = {
  fill: chartTheme.colors.default,
  fillOpacity: 0.3,
  horizontal: false,
  showArea: true,
  showLine: true,
  stroke: chartTheme.colors.default,
  strokeWidth: 2,
  strokeDasharray: null,
  strokeLinecap: 'round',
  keyAccessor: d => d.id
};






class WithTooltip extends React.PureComponent {
  constructor(props) {
    super(props);
    this.handleMouseMove = this.handleMouseMove.bind(this);
    this.handleMouseLeave = this.handleMouseLeave.bind(this);
    this.tooltipTimeout = null;
  }

  componentWillUnmount() {
    if (this.tooltipTimeout) {
      clearTimeout(this.tooltipTimeout);
    }
  }

  handleMouseMove({ event, datum, coords, ...rest }) {
    if (this.tooltipTimeout) {
      clearTimeout(this.tooltipTimeout);
    }

    let tooltipCoords = { x: 0, y: 0 };
    if (event && event.target && event.target.ownerSVGElement) {
      tooltipCoords = localPoint(event.target.ownerSVGElement, event);
    }

    tooltipCoords = { ...tooltipCoords, ...coords };

    this.props.showTooltip({
      tooltipLeft: tooltipCoords.x,
      tooltipTop: tooltipCoords.y,
      tooltipData: {
        event,
        datum,
        ...rest,
      },
    });
  }

  handleMouseLeave() {
    const { tooltipTimeout, hideTooltip } = this.props;
    this.tooltipTimeout = setTimeout(() => { hideTooltip(); }, tooltipTimeout);
  }

  render() {
    const {
      children,
      className,
      HoverStyles,
      tooltipData,
      tooltipOpen,
      tooltipLeft,
      tooltipTop,
      tooltipProps,
      renderTooltip,
      styles,
      TooltipComponent,
    } = this.props;

    const childProps = {
      onMouseMove: this.handleMouseMove,
      onMouseLeave: this.handleMouseLeave,
      tooltipData,
    };

    const tooltipContent = renderTooltip
      && tooltipOpen
      && TooltipComponent
      && renderTooltip(tooltipData);

    return (
      <div style={styles} className={className}>

        {/* inject props or pass to a function depending on child */}
        {typeof children === 'function'
          ? children(childProps)
          : React.cloneElement(React.Children.only(children), childProps)}

        {Boolean(tooltipContent) &&
          <TooltipComponent
            key={Math.random()}
            top={tooltipTop}
            left={tooltipLeft}
            {...tooltipProps}
          >
            {tooltipContent}
          </TooltipComponent>}

        {HoverStyles && <HoverStyles />}
      </div>
    );
  }
}

WithTooltip.propTypes = {
  ...vxTooltipPropTypes,
  children: PropTypes.oneOfType([PropTypes.object, PropTypes.func]).isRequired,
  className: PropTypes.string,
  HoverStyles: PropTypes.oneOfType([PropTypes.object, PropTypes.func]),
  renderTooltip: PropTypes.func,
  styles: PropTypes.object,
  TooltipComponent: PropTypes.oneOfType([PropTypes.object, PropTypes.func]),
  tooltipProps: PropTypes.object
};

WithTooltip.defaultProps = {
  className: null,
  HoverStyles: () => (
    <style type="text/css">{`
      .vx-arc:hover,
      .vx-bar:hover,
      .vx-glyph-dot:hover {
        opacity: 0.7;
      }
    `}</style>
  ),
  renderTooltip: null,
  styles: { display: 'inline-block', position: 'relative' },
  TooltipComponent: TooltipWithBounds,
  tooltipProps: null,
  tooltipTimeout: 200
};






let getValueKey = ({ normalized, cumulative }) => {
  if (normalized && cumulative) return 'cumulativeDensity';
  if (cumulative) return 'cumulative';
  if (normalized) return 'density';
  return 'count';
};

/*
 * Computes the bin and value domains from numeric or categorical bins
 */
function computeDomainsFromBins({ binsByIndex, binType, valueKey }) {
  let binDomain;
  let valueDomain;

  Object.values(binsByIndex).forEach((bins) => {
    const currValueMax = max(bins, d => d[valueKey]);
    if (!valueDomain) {
      valueDomain = [0, currValueMax];
    } else {
      valueDomain[1] = Math.max(currValueMax, valueDomain[1]);
    }

    if (binType === 'numeric') {
      if (!binDomain) {
        binDomain = [bins[0].bin0, bins[bins.length - 1].bin1];
      } else {
        binDomain[0] = Math.min(bins[0].bin0, binDomain[0]);
        binDomain[1] = Math.max(bins[bins.length - 1].bin1, binDomain[1]);
      }
    } else {
      if (!binDomain) binDomain = {}; // use lookup to avoid lots of Array scans
      bins.forEach((bin) => { binDomain[bin.bin] = true; });
    }
  });

  if (!Array.isArray(binDomain)) {
    binDomain = Object.keys(binDomain).sort(caseInsensitiveSort);
  }

  return { binDomain, valueDomain };
}

let caseInsensitiveSort = (a, b) => {
  if (!a.toLowerCase || !b.toLowerCase) return a - b;
  if (a.toLowerCase() < b.toLowerCase()) return -1;
  if (a.toLowerCase() > b.toLowerCase()) return 1;
  return 0;
};

let themeShape = PropTypes.shape({
  gridStyles: gridStylesShape,
  xAxisStyles: axisStylesShape,
  xTickStyles: tickStylesShape,
  yAxisStyles: axisStylesShape,
  yTickStyles: tickStylesShape,
});

const propTypes = {
  ariaLabel: PropTypes.string.isRequired,
  binValues: PropTypes.arrayOf(PropTypes.oneOfType([PropTypes.number, PropTypes.string])),
  binCount: PropTypes.number,
  binType: PropTypes.oneOf(['numeric', 'categorical']),
  children: PropTypes.node.isRequired,
  cumulative: PropTypes.bool,
  height: PropTypes.number.isRequired,
  horizontal: PropTypes.bool,
  limits: PropTypes.array, // values outside the limits are ignored
  margin: PropTypes.shape({
    top: PropTypes.number,
    right: PropTypes.number,
    bottom: PropTypes.number,
    left: PropTypes.number,
  }),
  normalized: PropTypes.bool,
  theme: themeShape,
  width: PropTypes.number.isRequired,
  valueAccessor: PropTypes.func
};

const defaultProps = {
  binCount: 10,
  binType: 'numeric',
  binValues: null,
  cumulative: false,
  horizontal: false,
  limits: null,
  margin: {
    top: 32,
    right: 32,
    bottom: 64,
    left: 64,
  },
  normalized: false,
  theme: {},
  valueAccessor: d => d
};

class Histogram extends React.PureComponent {
  constructor(props) {
    super(props);
    this.state = this.getStateFromProps(props);
  }

  componentWillReceiveProps(nextProps) {
    this.setState(this.getStateFromProps(nextProps));
  }

  getStateFromProps(props) {
    const dimensions = this.getDimmensions(props);
    const binsByIndex = this.getBinnedData(props);
    const scales = this.getScales(props, binsByIndex, dimensions);

    return {
      binsByIndex,
      ...dimensions,
      ...scales,
    };
  }

  getDimmensions(props) {
    const { margin, width, height } = props || this.props;
    const completeMargin = { ...defaultProps.margin, ...margin };
    return {
      margin: completeMargin,
      innerHeight: height - completeMargin.top - completeMargin.bottom,
      innerWidth: width - completeMargin.left - completeMargin.right,
    };
  }

  getBinnedData(props) {
    const { children, binCount, binType, binValues, limits, valueAccessor } = props || this.props;
    return collectBinnedDataFromChildSeries({
      children,
      binCount,
      binType,
      binValues,
      limits,
      valueAccessor,
    });
  }

  getScales(props, binsByIndex, { innerHeight, innerWidth }) {
    const { binType, binValues, cumulative, horizontal, normalized, padding } = props || this.props;

    const binScaleFunc = binType === 'numeric' ? scaleLinear : scaleBand;
    const valueKey = getValueKey({ normalized, cumulative });
    const { binDomain, valueDomain } = computeDomainsFromBins({
      binsByIndex,
      binType,
      binValues,
      valueKey,
    });

    const binRange = horizontal ? [innerHeight, 0] : [0, innerWidth];
    const valueRange = horizontal ? [0, innerWidth] : [innerHeight, 0];

    // when viewing categorical data horizontally it is more natural to
    // read alphabetical from top down
    if (horizontal && binType === 'categorical') binRange.reverse();


    return {
      binScale: binScaleFunc({ range: binRange, domain: binDomain, padding }),
      valueScale: scaleLinear({ range: valueRange, domain: valueDomain, padding }),
      valueKey,
    };
  }

  render() {
    const {
      ariaLabel,
      binType,
      binValues,
      children,
      height,
      horizontal,
      theme,
      valueAccessor,
      width,
    } = this.props;

    const {
      binsByIndex,
      binScale,
      innerHeight,
      innerWidth,
      margin,
      valueKey,
      valueScale,
    } = this.state;

    return (
      <svg
        aria-label={ariaLabel}
        role="img"
        width={width}
        height={height}
      >
        <Group left={margin.left} top={margin.top}>
          {React.Children.map(children, (Child, index) => {

            const name = componentName(Child);
            if (isSeries(name)) {
              const binnedData = binsByIndex[index];
              return React.cloneElement(Child, {
                binScale,
                binType,
                binnedData,
                horizontal,
                valueAccessor,
                valueKey,
                valueScale,
              });
            } else if (isAxis(name)) {
              const styleKey = name[0].toLowerCase();
              const binOrValue =
                (name === 'XAxis' && !horizontal) || (name === 'YAxis' && horizontal)
                  ? 'bin'
                  : 'value';
              return React.cloneElement(Child, {
                top: name === 'YAxis' || Child.props.orientation === 'top' ? 0 : innerHeight,
                left: name === 'XAxis' || Child.props.orientation === 'left' ? 0 : innerWidth,
                label: Child.props.label || (binOrValue === 'value' ? valueKey : undefined),
                scale: binOrValue === 'value' ? valueScale : binScale,
                axisStyles: { ...theme[`${styleKey}AxisStyles`], ...Child.props.axisStyles },
                tickStyles: { ...theme[`${styleKey}TickStyles`], ...Child.props.tickStyles },
                tickValues: Child.props.tickValues || (binOrValue === 'bin' ? undefined : binValues),
              });
            }
            return Child;
          })}
        </Group>
      </svg>
    );
  }
}

Histogram.propTypes = propTypes;
Histogram.defaultProps = defaultProps;
Histogram.displayName = 'Histogram';


const getBin = d => (typeof d.bin !== 'undefined' ? d.bin : d.bin0);
const densityAccessor = d => d.value;
const cumulativeAccessor = d => d.cumulative;

let DensitySeries = ({
  animated,
  rawData,
  binnedData,
  binScale,
  binType,
  fill,
  fillOpacity,
  horizontal,
  kernel,
  showArea,
  showLine,
  smoothing,
  stroke,
  strokeWidth,
  strokeDasharray,
  strokeLinecap,
  useEntireScale,
  valueAccessor,
  valueKey,
  valueScale,
}) => {
  if ((!showArea && !showLine)) return null;

  const binWidth = binScale.bandwidth
    ? binScale.bandwidth() // categorical
    : Math.abs(binScale(binnedData[0].bin1) - binScale(binnedData[0].bin0)); // numeric

  const binOffset = 0.5 * binWidth * (horizontal && binType === 'numeric' ? -1 : 1);

  // all density estimators require numeric data, so if we're passed categorical data
  // or pre-aggregated data, we just draw an area curve using the binned data
  let densityScale = valueScale;
  let getDensity = d => d[valueKey];
  let densityData = binnedData;

  if (binType === 'numeric' && rawData.length > 0) {
    // @TODO cache this with a non-functional component
    const cumulative = (/cumulative/gi).test(valueKey);
    const bins = binnedData.map(getBin);

    const kernelFunc = kernel === 'gaussian'
      ? kernelGaussian()
      : kernelParabolic(smoothing);



    const estimator = kernelDensityEstimator(kernelFunc, bins);

    densityData = estimator(rawData.map(valueAccessor));

    // area fills become inverted when the last value is less than the first value.
    // padding with 0s ensures this never happens

    /* change commented these out*/
    // densityData.unshift({ ...densityData[0], value: 0 });
    // densityData.push({ ...densityData[densityData.length - 1], value: 0 });

    const densityRange = valueScale.range();
    if (!useEntireScale) {
      // set the range of the density scale to match the maximum data value
      const maxVal = max(binnedData, d => d[valueKey]);
      densityRange[1] = valueScale(maxVal);
    }

    densityScale = scaleLinear({
      domain: d3Extent(densityData, (d, i) => {
        const val = densityAccessor(d);// compute cumulative in this loop
        d.cumulative = val + (i > 0 ? densityData[i - 1].cumulative : 0);
        d.id = i;
        return cumulative ? d.cumulative : val;
      }),
      range: densityRange,
    });

    getDensity = cumulative ? cumulativeAccessor : densityAccessor;
  }

  const offSetBinScale = binScale.copy();
  offSetBinScale.range(binScale.range().map(v => v + binOffset));

  const getX = horizontal ? getDensity : getBin;
  const getY = horizontal ? getBin : getDensity;
  const xScale = horizontal ? densityScale : offSetBinScale;
  const yScale = horizontal ? offSetBinScale : densityScale;

  return (
    <Group style={{ pointerEvents: 'none' }}>
      {animated &&
        <AnimatedDensitySeries
          densityData={densityData}
          fill={fill}
          fillOpacity={fillOpacity}
          horizontal={horizontal}
          getX={getX}
          getY={getY}
          showArea={showArea}
          showLine={showLine}
          stroke={stroke}
          strokeWidth={strokeWidth}
          strokeDasharray={strokeDasharray}
          strokeLinecap={strokeLinecap}
          xScale={xScale}
          yScale={yScale}
        />}
      {!animated && showArea &&
        <AreaClosed
          data={densityData}
          x={getX}
          y={getY}
          xScale={xScale}
          yScale={yScale}
          fill={fill}
          fillOpacity={fillOpacity}
          stroke="transparent"
          strokeWidth={strokeWidth}
          curve={curveBasis}
        />}
      {!animated && showLine && strokeWidth > 0 &&
        <LinePath
          data={densityData}
          x={getX}
          y={getY}
          xScale={xScale}
          yScale={yScale}
          stroke={stroke}
          strokeWidth={strokeWidth}
          strokeDasharray={strokeDasharray}
          strokeLinecap={strokeLinecap}
          curve={curveBasis}
          glyph={null}
        />}
    </Group>
  );
}

DensitySeries.propTypes = {
  animated: PropTypes.bool,
  rawData: PropTypes.array, // eslint-disable-line react/no-unused-prop-types
  binnedData: binnedDataShape,
  binType: PropTypes.oneOf(['numeric', 'categorical']),
  fill: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  fillOpacity: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  horizontal: PropTypes.bool,
  kernel: PropTypes.oneOf(['gaussian', 'parabolic']),
  showArea: PropTypes.bool,
  showLine: PropTypes.bool,
  smoothing: PropTypes.number,
  stroke: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  strokeDasharray: PropTypes.oneOfType([PropTypes.func, PropTypes.string]),
  strokeLinecap: PropTypes.oneOf(['butt', 'square', 'round', 'inherit']),
  strokeWidth: PropTypes.oneOfType([PropTypes.func, PropTypes.number]),
  useEntireScale: PropTypes.bool,
  valueAccessor: PropTypes.func,
  valueKey: PropTypes.string,
  padding: PropTypes.number,

  // likely injected by parent Histogram
  binScale: PropTypes.func,
  valueScale: PropTypes.func
};
DensitySeries.defaultProps = {
  animated: true,
  rawData: [],
  binnedData: [],
  binScale: null,
  binType: null,
  fill: chartTheme.colors.default,
  fillOpacity: 0.3,
  horizontal: false,
  kernel: 'gaussian',
  showArea: true,
  showLine: true,
  smoothing: 1,
  stroke: chartTheme.colors.default,
  strokeWidth: 2,
  strokeDasharray: null,
  strokeLinecap: 'round',
  useEntireScale: false,
  valueAccessor: d => d,
  valueKey: 'count',
  valueScale: null,
  padding: .1
};

DensitySeries.displayName = 'DensitySeries';


let callOrValue = (maybeFn, data) => {
  if (typeof maybeFn === 'function') {
    return maybeFn(data);
  }
  return maybeFn;
}

const getBin1 = d => (typeof d.bin !== 'undefined' ? d.bin : d.bin1);

let AnimatedBarSeries = ({
  binnedData,
  valueScale,
  binScale,
  horizontal,
  keyAccessor,
  fill,
  fillOpacity,
  onMouseMove,
  onMouseLeave,
  stroke,
  strokeWidth,
  valueKey,
  barFn,
}) => {
  const maxBarLength = Math.max(...valueScale.range());

  const barWidth = binScale.bandwidth
    ? binScale.bandwidth() // categorical
    : Math.abs(binScale(binnedData[0].bin1) - binScale(binnedData[0].bin0)); // numeric

  const getValue = d => d[valueKey];

  const getX = horizontal ? getValue : getBin;
  const getY = horizontal ? getBin1 : getValue;
  const xScale = horizontal ? valueScale : binScale;
  const yScale = horizontal ? binScale : valueScale;

  console.log('AnimatedBarSeries binnedData = %j', binnedData);

  return (
    <NodeGroup
      data={binnedData}
      keyAccessor={keyAccessor}
      start={(d, i) => ({
        x: horizontal ? 0 : xScale(getX(d)),
        y: horizontal ? yScale(getY(d)) : maxBarLength,
        fill: d.fill || callOrValue(fill, d, i),
        width: horizontal ? 0 : barWidth,
        height: horizontal ? barWidth : 0,
      })}
      enter={(d, i) => ({
        x: [horizontal ? 0 : xScale(getX(d))],
        y: [yScale(getY(d))],
        width: [horizontal ? xScale(getX(d)) : barWidth],
        height: [horizontal ? barWidth : maxBarLength - yScale(getY(d))],
        fill: [d.fill || callOrValue(fill, d, i)],
        stroke: [d.stroke || callOrValue(stroke, d, i)],
        timing: { duration: 300, delay: 10 * i },
      })}
      update={(d, i) => ({
        x: [horizontal ? 0 : xScale(getX(d))],
        y: [yScale(getY(d))],
        width: [horizontal ? xScale(getX(d)) : barWidth],
        height: [horizontal ? barWidth : maxBarLength - yScale(getY(d))],
        fill: [d.fill || callOrValue(fill, d, i)],
        stroke: [d.stroke || callOrValue(stroke, d, i)],
        timing: { duration: 300, delay: 10 * i },
      })}
      leave={(d, i) => ({
        x: horizontal ? 0 : xScale(getX(d)),
        y: horizontal ? yScale(getY(d)) : maxBarLength,
        width: horizontal ? 0 : barWidth,
        height: horizontal ? barWidth : 0,
        timing: { duration: 300, delay: 5 * i },
      })}
    >
      {
        data => {
          let random = Math.random().toString(36).substring(7);
          return (
            <Group>
              {
                data.map((modifiedDatum, i) => {
                  const { data: rawDatum, state: d } = modifiedDatum;

                  return (
                    [
                      <Bar
                        key={`bar_${random}`}
                        x={d.x}
                        y={d.y}
                        width={d.width}
                        height={d.height}
                        fill={d.fill}
                        stroke={d.stroke}
                        fillOpacity={
                          typeof fillOpacity !== 'undefined'
                            ? fillOpacity
                            : callOrValue(fillOpacity, rawDatum, i)
                        }
                        strokeWidth={rawDatum.strokeWidth || callOrValue(strokeWidth, rawDatum, i)}
                        onMouseMove={onMouseMove && (() => (event) => {
                          onMouseMove({ event, datum: rawDatum, data: binnedData, color: d.fill });
                        })}
                        onMouseLeave={onMouseLeave && (() => onMouseLeave)}
                      />,
                      /* Change */
                      barFn && React.cloneElement(barFn({ ...d, ...rawDatum }), { key: `barFn_${random}` })
                    ]
                  );
                })
              }
            </Group>
          )
        }
      }
    </NodeGroup>
  );
}

let BarSeriesPropTypes = BarSeries.propTypes;
let BarSeriesDefaultProps = BarSeries.defaultProps;

AnimatedBarSeries.propTypes = {
  ...BarSeriesPropTypes,
  keyAccessor: PropTypes.func
};

AnimatedBarSeries.defaultProps = {
  ...BarSeriesDefaultProps,
  keyAccessor: d => d.id
};

BarSeries.displayName = 'BarSeries';


let tempData = [
  ['Qatar', 86.9],
  ['Ethiopia', 79.4],
  ['Cayman Islands', 77.8],
  ['Iceland', 77],
  ['Viet Nam', 76],
  ['Tanzania', 75.7],
  ['Thailand', 71],
  ['Norway', 68.7],
  ['China', 68.6],
  ['Paraguay', 66.8],
  ['Sweden', 65.7],
  ['Switzerland', 65.3],
  ['Malaysia', 65],
  ['Russian Federation', 64.8],
  ['New Zealand', 64.1],
  ['Indonesia', 62.7],
  ['Canada', 61.8],
  ['Australia', 61.3],
  ['Brazil', 61.2],
  ['Netherlands', 60.8],
  ['Finland', 60.1],
  ['El Salvador', 59.9],
  ['Israel', 59.7],
  ['Colombia', 59.6],
  ['Ecuador', 59.5],
  ['Korea', 59.5],
  ['Uruguay', 59.5],
  ['Philippines', 59.4],
  ['Hong Kong', 59.1],
  ['Trinidad Tobago', 59.1],
  ['Barbados', 58.9],
  ['United States', 58.6],
  ['Austria', 58.5],
  ['United Kingdom', 58.4],
  ['Guatemala', 58.3],
  ['Denmark', 58],
  ['Mexico', 57.5],
  ['Kyrgyzstan', 57.3],
  ['Germany', 57.1],
  ['Japan', 56.9],
  ['Chile', 56],
  ['Estonia', 56],
  ['Luxembourg', 55.9],
  ['Czech Republic', 55.2],
  ['Costa Rica', 54.7],
  ['Dominican Republic', 54.6],
  ['Cyprus', 53.3],
  ['Ireland', 52.4],
  ['Latvia', 52.4],
  ['Hungary', 51.6],
  ['Slovenia', 51.5],
  ['Lithuania', 51.2],
  ['Romania', 51.1],
  ['Saudi Arabia', 51.1],
  ['France', 50.9],
  ['Slovakia', 50.9],
  ['Poland', 50.2],
  ['Namibia', 50],
  ['Malta', 49.8],
  ['Portugal', 49.7],
  ['Lesotho', 49.2],
  ['Belgium', 49],
  ['Bulgaria', 46.9],
  ['Turkey', 45.9],
  ['Albania', 44.5],
  ['Spain', 44.4],
  ['Italy', 43],
  ['Croatia', 42.1],
  ['Egypt', 42.1],
  ['South Africa', 40],
  ['Macedonia', 39.7],
  ['Greece', 38.4],
  ['Serbia', 37.7],
  ['Palestine', 33.4]
];

const ResponsiveHistogram = withScreenSize(({ screenWidth, children, maxHeight, width, ...rest }) => (
  <Histogram
    width={width || Math.min(1000, screenWidth / 1.3)}
    height={Math.min(1000 / 1.8, screenWidth / 1.3 / 1.8, maxHeight || Number.POSITIVE_INFINITY)}
    ariaLabel="Histogram showing ..."
    theme={chartTheme}
    {...rest}
  >
    {children}
  </Histogram>
));

export default (props) => {
  let data = props.data || tempData;
  if ((!data || data.length === 0)) return <div />;

  let textMaxSize = props.textSize || 16;
  let padding = 92;
  let maxHeight = data.length * textMaxSize + padding; // max bar length not max value TODO BUG
  let color = props.color;

  /* hack for ordering */
  const updateAxisValue = (binName) => {
    const stringVal = `${binName}`;
    const binArray = stringVal.split(' ');
    if(binArray.length < 2) { return binArray.join(' '); }
    return binArray.slice(1).join(' ');
  };

  return (
    <div>
      <ResponsiveHistogram
        key={props.data}
        width={props.width}
        ariaLabel="test"
        valueAccessor={(d) => d[1]}
        maxHeight={maxHeight}
        normalized={props.normalized || false}
        binType={props.categorical ? "categorical" : "numeric"}
        padding={.2}
        binValues={props.binValues}
      >
        <PatternLines
          key={props.data}
          id="normal"
          height={8}
          width={8}
          stroke="#fff"
          background={chartTheme.colors.categories[2]}
          strokeWidth={1}
          orientation={['horizontal', 'vertical']}
        />
        <BarSeries
          key={props.data}
          fill={color || "#224099"}
          fillOpacity={1}
          rawData={data}
          barFn={
            (data) => (
              <Group left={data.x} top={data.y} >
                {
                  data.data.map((d, i) =>
                    <Text
                      key={i}
                      dy={((1 + i) * (data.height / data.data.length)) - 1}
                      dx={data.width / 2}
                      width={data.width}
                      height={data.height}
                      style={
                        {
                          fill: "black",
                          stroke: "black",
                          textAnchor: "middle",
                          fontWeight: "200",
                          fontSize: `${textMaxSize}px`,
                        }
                      }
                    >
                      {d[0]}
                    </Text>
                  )
                }
              </Group>
            )}
        />
        <DensitySeries
          key={props.data}
          stroke={chartTheme.colors.categories[2]}
          showArea={false}
          smoothing={1}
          kernel="gaussian"
          rawData={data}
        />
        {props.xLabel && <XAxis label={props.xLabel} tickFormat={updateAxisValue}/>}
        {props.yLabel && <YAxis label={props.yLabel}/>}
      </ResponsiveHistogram>
    </div>
  );
};
