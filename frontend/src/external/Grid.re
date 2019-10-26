[@bs.module "reactstrap"]
external grid : ReasonReact.reactClass = "Container";

let make = (~style=?, ~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=grid,
    ~props={
      "style": Js.Nullable.fromOption(style),
      "className": Js.Nullable.fromOption(className),
    },
    children
  );