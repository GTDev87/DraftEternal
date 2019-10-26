let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let sidebarImageName = [%bs.raw {| css(tw`
  flex
`)|}];

let sidebarImageNameIcon = [%bs.raw {| css(tw`
  w-1/4
  flex
  justify-end
  pr-4

`)|}];

let sidebarImageNameText = [%bs.raw {| css(tw`
  w-3/4
`)|}];


[@react.component]
let make = (~icon, ~text) => {
  <div className=sidebarImageName>
    <div className=sidebarImageNameIcon>{icon}</div>
    <div className=sidebarImageNameText>{ReasonReact.string(text)}</div>
  </div>
};