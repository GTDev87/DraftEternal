[@bs.module "recharts"]
external comp : ReasonReact.reactClass = "YAxis";

let make = (~dataKey=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "dataKey": Js.Nullable.fromOption(dataKey),
    },
    children
  );

