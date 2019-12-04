let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cubeClientDraftModal = [%bs.raw {| css(tw`
  h-full
  overflow-hidden
  flex
  flex-col
`)|}];

[@react.component]
let make = (~id, ~normalized, ~updateNormalizr, ~index) => {
  let optionCube = MyNormalizr.Converter.Cube.Remote.getRecord(normalized, id);

  Belt.Option.mapWithDefault(optionCube, <div/>, (cube) => {
    <div className=cubeClientDraftModal>
    </div>
  })
};