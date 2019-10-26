[@bs.module "reactstrap"]
external tab : ReasonReact.reactClass = "NavLink";

let make = (~className, ~onClick, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tab,
    ~props={
      "className": "NavLink " ++ className,
      "onClick": onClick,
    },
    children
  );
