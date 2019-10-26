[@bs.module "reactstrap"]
external row : ReasonReact.reactClass = "Row";

let make = (~style=?, ~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=row,
    ~props={
      "style": Js.Nullable.fromOption(style),
      "className": Js.Nullable.fromOption(className),
    },
    children
  );