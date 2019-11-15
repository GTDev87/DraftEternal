let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let buttonOuterStyle = [%bs.raw {| css(tw`
  w-full
`)|}];

let buttonStyle = [%bs.raw {| css(tw`
  bg-teal-dark
  px-4
  py-4
  text-white
  bg-blue
  rounded
  cursor-pointer
  w-full
`)|}];

[@react.component]
let make = (~onClick=?, ~className=?, ~innerClassName=?, ~autoFocus=?, ~style=?, ~disabled=?, ~children) => {
  <div className={cx(buttonOuterStyle, Belt.Option.getWithDefault(className, ""))}>
    {
      ReasonReact.createDomElement(
        "button",
        ~props={
          "autoFocus": Belt.Option.getWithDefault(autoFocus, true),
          "onClick": onClick,
          "className": cx(buttonStyle, Belt.Option.getWithDefault(innerClassName, "")),
          "disabled": Js.Nullable.fromOption(disabled)
        },
        [|children|],
      )
    }
  </div>
};