[@bs.module "react-sidebar"]
external comp : ReasonReact.reactClass = "default";


let make = (~sidebar, ~isDocked, ~onSetOpen, ~isOpen, ~style=?, ~contentStyle=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "onSetOpen": onSetOpen,
      "sidebar": sidebar,
      "open": isOpen,
      "docked": isDocked,
      "styles": {
        "sidebar": Js.Nullable.fromOption(style),
        "content": Js.Nullable.fromOption(contentStyle),
      },
    },
    children
  );
