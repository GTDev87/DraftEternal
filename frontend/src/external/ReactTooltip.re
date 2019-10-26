[@bs.module "reactstrap"]
external comp : ReasonReact.reactClass = "UncontrolledTooltip";

let make = (~placement, ~target, children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "placement": placement,
      "target": target,
    },
    children
  );
};
