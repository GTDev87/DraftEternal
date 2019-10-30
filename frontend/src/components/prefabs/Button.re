let component = ReasonReact.statelessComponent("Button");

type theme =
  | CTA;

let styleButton = (theme: theme) =>
  switch (theme) {
  | CTA =>
    ReactDOMRe.Style.make(
      ~padding=".25em 1.4em",
      ~color="white",
      ~backgroundColor=Colors.primary,
      ~borderRadius=".2em",
      ~cursor="pointer",
      (),
    )
  };

[@react.component]
let make = (~onClick=?, ~theme=CTA, ~autoFocus=?, ~style=?, ~disabled=?, ~children) => {
    ReasonReact.createDomElement(
      "button",
      ~props={
        "autoFocus": Belt.Option.getWithDefault(autoFocus, true),
        "onClick": onClick,
        "style": Utils.Dom.combineStyles(style, styleButton(theme)),
        "disabled": Js.Nullable.fromOption(disabled)
      },
      children,
    )
};