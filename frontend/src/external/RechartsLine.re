[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "Line";

let make = (~dataKey, ~stroke, ~_type, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "dataKey": dataKey,
      "stroke": stroke,
      "type": _type,
    },
    children
  );
