[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "XAxis";

let make = (~dataKey, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "dataKey": dataKey,
    },
    children
  );

