module Interop = {
  [@bs.module "reactstrap"] [@react.component]
  external make: (
    ~isOpen: bool,
    ~toggle: (unit) => Js.Promise.t(unit),
    ~style: Js.Nullable.t(string),
    ~size: string,
    ~autoFocus: Js.Nullable.t(bool),
    ~children: React.element,
    ~contentClassName: Js.Nullable.t(string),
    unit
  ) => React.element = "Modal";
};

[@react.component]
let make = (~isOpen, ~onRequestClose, ~style=?, ~autoFocus=?, ~className=?, ~children) => {
  <Interop
    isOpen
    toggle=onRequestClose
    style=Js.Nullable.fromOption(style)
    size="lg"
    autoFocus=Js.Nullable.fromOption(autoFocus)
    contentClassName=Js.Nullable.fromOption(className)
  >
    {children}
  </Interop>
};
