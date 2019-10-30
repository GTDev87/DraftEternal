let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardPicker = [%bs.raw {| css(tw`
  h-full
`)|}];

[@react.component]
let make = (~id, ~normalized, ~updateNormalizr) => {
  let newCube =
    normalized
    |> MyNormalizr.Converter.Cube.Remote.getRecord(_, id)
    |> Belt.Option.getWithDefault(_, Cube.Model.Record.defaultWithId((), id));

  <div className=cardPicker>
  </div>
};