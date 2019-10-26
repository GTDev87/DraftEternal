[@bs.module "@vx/responsive"]
external comp : ReasonReact.reactClass = "ParentSize";

let make = (children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props=Js.Obj.empty(),
    children
  );