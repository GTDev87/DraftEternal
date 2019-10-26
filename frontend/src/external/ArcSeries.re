[@bs.module "@data-ui/radial-chart"]
external comp : ReasonReact.reactClass = "ArcSeries";

type dataType('a) = {
  .
  "data": 'a
};

let make = (
  ~labelComponent : ReasonReact.reactElement,
  ~innerRadius : option(float => float)=?,
  ~outerRadius : float => float,
  ~labelRadius : float => float,
  ~fill : (dataType('a)) => string,
  ~data : array('a),
  ~pieValue : ('a) => float,
  ~label : (dataType('a)) => string,
  ~stroke : string,
  ~strokeWidth : float,
  children
) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "labelComponent": labelComponent,
      "innerRadius": Js.Nullable.fromOption(innerRadius),
      "outerRadius": outerRadius,
      "labelRadius": labelRadius,
      "fill": fill,
      "data": data,
      "pieValue": pieValue,
      "label": label,
      "stroke": stroke,
      "strokeWidth": strokeWidth,
    },
    children
  );
