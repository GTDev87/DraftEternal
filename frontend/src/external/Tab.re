[@bs.module "reactstrap"]
external tab : ReasonReact.reactClass = "TabPane";

let make = (~tabId : string, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tab,
    ~props={
      "tabId": tabId,
    },
    children
  );
