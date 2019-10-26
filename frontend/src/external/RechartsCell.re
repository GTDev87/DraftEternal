[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "Cell";

let make = (~fill, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "fill": fill,
    },
    children
  );

