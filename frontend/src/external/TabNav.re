[@bs.module "reactstrap"]
external tab : ReasonReact.reactClass = "Nav";

let make = (~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tab,
    ~props={
      "tabs": true,
      "className": Js.Nullable.fromOption(className),
    },
    children
  );
