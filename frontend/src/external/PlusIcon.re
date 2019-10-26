[@bs.module "react-icons/fa"]
external comp : ReasonReact.reactClass = "FaPlus";

let make = (~style=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "style": style
    },
    children
  );