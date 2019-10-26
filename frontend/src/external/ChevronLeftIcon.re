[@bs.module "react-icons/fa"]
external comp : ReasonReact.reactClass = "FaChevronLeft";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": Js.Nullable.fromOption(style)
    },
    children
  );