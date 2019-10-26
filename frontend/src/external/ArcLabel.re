[@bs.module "@data-ui/radial-chart"]
external comp : ReasonReact.reactClass = "ArcLabel";

let make = (children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props=Js.Obj.empty(),
    children
  );
