[@bs.module "reactstrap"]
external comp : ReasonReact.reactClass = "Modal";

let make = (~isOpen, ~onRequestClose, ~style=?, ~autoFocus=?, children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "isOpen": isOpen,
      "toggle": onRequestClose,
      "style": Js.Nullable.fromOption(style),
      "size": "lg",
      "autoFocus": Js.Nullable.fromOption(autoFocus),
    },
    children
  )
};
