[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "BarChart";

let make = (~width, ~height, ~data, ~margin, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "width": width,
      "height": height,
      "data": data,
      "margin": margin,
    },
    children
  );
