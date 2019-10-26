[@bs.module "react-icons/fa"]
external comp : ReasonReact.reactClass = "FaCheck";

let make = (~style=?, ~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style),
      "className": Js.Nullable.fromOption(className)
    },
    children
  );