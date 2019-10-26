open Belt;
[@bs.module "react-table"] external component : ReasonReact.reactClass = "default";

type accessor('a) =
  | String(string)
  | AccessorFn(('a) => ReasonReact.reactElement)
  ;

type rawCellComponentJS;
external rawCellComponentJS : 'a => rawCellComponentJS = "%identity";

/* Todo: This type is a js version of column... will fix later */
type column2('a) = {
  .
  "id": string
};

type cellInfo('a) = {
  .
  "index": int,
  "column": column2('a),
  "id": string
};

type cellInfoFn('a) = cellInfo('a) => ReasonReact.reactElement;

type column('a) = {
  _Header: string,
  accessor: accessor('a),
  id: option(string),
  minWidth: option(int),
  maxWidth: option(int),
  _Cell: option(cellInfoFn('a)),
  headerClassName: option(string)
};

type rawAccessorJS;
external rawAccessorJS : 'a => rawAccessorJS = "%identity";

let styleGroupProps =
  ReactDOMRe.Style.make(
    ~backgroundColor="white",
    ~borderBottom="solid 1px " ++ Colors.secondary, /* what color should this be? */
    /*~padding="0.5em",*/
    ()
  );

let styleCellProps =
  ReactDOMRe.Style.make(
    ~backgroundColor="transparent",
    ~textAlign="initial",
    ~padding="0",
    ()
  );

let baseTdStyle =
  ReactDOMRe.Style.make(
    ~padding=".7em",
    ~borderRight="none",
    ()
  );

let styleProps =
  ReactDOMRe.Style.make(
    ~border="none",
    ()
  );

let styleHeadProps =
  ReactDOMRe.Style.make(
    ~borderBottom="solid 1px white",
    ~backgroundColor=Colors.secondary,
    ()
  );

let styleHeadTrProps =
  ReactDOMRe.Style.make(
    ~textAlign="initial",
    ~borderRight="none",
    ()
  );

let columnRecordToObjColumn = (column: column('a)) =>
  ({
    "Header": column._Header,
    "accessor": switch(column.accessor) {
    | String(s) => rawAccessorJS(s)
    | AccessorFn(fn) => rawAccessorJS(fn)
    },
    "id": column.id,
    "minWidth": Js.Nullable.fromOption(column.minWidth),
    "maxWidth": Js.Nullable.fromOption(column.maxWidth),
    "headerClassName": Belt.Option.getWithDefault(column.headerClassName, ""),
    "Cell": Js.Nullable.fromOption(
      switch(column._Cell) {
      | None => None
      | Some(fn) => Some(rawCellComponentJS(fn))
      }
    ),
  });

let columnsRecordToObjcts = (columns)  =>
  columns
  |> List.map(_, columnRecordToObjColumn)
  |> List.toArray;

type getPropsType = {
  .
  "style": ReactDOMRe.style
};

let make = (
  ~columns: list(column('a)),
  ~dataList: list('a),
  ~pageSize: int,
  ~sortable: option(bool)=?,
  ~getTdProps=?,
  ~getTrGroupPropsFn=?,
  ~style=?,
  children
) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=component,
    ~props={
      "columns": columns |> (columnsRecordToObjcts),
      "data": dataList |> List.toArray,
      "pageSize": pageSize,
      "className": "-striped -highlight",
      "showPaginationBottom": false,
      "getTrGroupProps": (Belt.Option.getWithDefault(getTrGroupPropsFn, (_, _) : getPropsType => {"style": styleGroupProps})),
      "getTrProps": () => {"style": styleCellProps},
      "getTheadProps": () => {"style": styleHeadProps},
      "getTheadTrProps": () => {"style": styleHeadTrProps},
      "getTdProps": () => {"style": Utils.Dom.combineStyles(getTdProps, baseTdStyle)},
      "style": Utils.Dom.combineStyles(style, styleProps),
      "sortable": Js.Nullable.fromOption(sortable),
    },
    children
  )
};
