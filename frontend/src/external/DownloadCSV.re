[@bs.module "react-csv"]
external comp : ReasonReact.reactClass = "CSVLink";

let make = (~data, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "data": data,
    },
    children
  );