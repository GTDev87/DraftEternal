[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "CartesianGrid";

let make = (~strokeDasharray, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "strokeDasharray": strokeDasharray,
    },
    children
  );
