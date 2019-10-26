[@bs.module "../../../../src/chart.js"]
external col : ReasonReact.reactClass = "default";

/* EXAMPLE OF LOCAL JAVASCRIPT FILE LOADED */
let make = (
  ~data : array('a),
  ~categorical=?,
  ~xLabel=?,
  ~yLabel=?,
  ~textSize=?,
  ~width=?,
  ~binValues=?,
  children
) => {
  /* Js.log("data = %j");
  Js.log(data);
  Js.log("binValues = %j");
  Js.log(binValues); */
  ReasonReact.wrapJsForReason(
    ~reactClass=col,
    ~props={
      "key": binValues,
      "data": data,
      "color": Colors.secondary,
      "xLabel": Js.Nullable.fromOption(xLabel),
      "yLabel": Js.Nullable.fromOption(yLabel),
      "binValues": Js.Nullable.fromOption(binValues),
      "categorical": Js.Nullable.fromOption(categorical),
      "textSize": Js.Nullable.fromOption(textSize),
      "width": Js.Nullable.fromOption(width),
    },
    children
  );
}