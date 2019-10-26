[@bs.module "reactstrap"]
external tabs : ReasonReact.reactClass = "TabContent";

let make = (~activeTab, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tabs,
    ~props={
      "activeTab": activeTab,
    },
    children
  );
