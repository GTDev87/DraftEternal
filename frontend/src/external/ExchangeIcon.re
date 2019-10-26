[@bs.module "react-icons/fa"]
external comp : ReasonReact.reactClass = "FaExchange";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style)
    },
    children
  );