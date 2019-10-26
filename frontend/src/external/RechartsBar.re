[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "Bar";

let make = (~dataKey, ~fill, ~shape, ~label, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "dataKey": dataKey,
      "fill": fill,
      "shape": shape,
      "label": label,
    },
    children
  );
