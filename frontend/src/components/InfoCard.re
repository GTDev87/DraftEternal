
let css = Css.css;
let tw = Css.tw;

let infoCardClass = [%bs.raw
  {| css(tw`
    w-full
    flex
    flex-col
  `)|}
];
let infoCardContentFullSizeClass = [%bs.raw {| css(tw` w-full h-full`)|}];

let infoCardHeaderClass = [%bs.raw
  {| css(tw`
    w-full
    text-white
    bg-blue-lighter
    mb-0
    flex-no-grow
    rounded-tl
    rounded-tr
  `)|}
];
let infoCardContentClass = [%bs.raw
  {| css(tw`
    border-solid
    border-blue-lighter
    border
    h-full
    flex-grow
  `)|}
];

[@react.component]
let make = (~header, ~children) => {
  <div className=infoCardClass>
    <div className=infoCardHeaderClass>{ header }</div>
    <div className=infoCardContentClass>
      <div className=infoCardContentFullSizeClass>{ children |> ReasonReact.array }</div>
    </div>
  </div>
};