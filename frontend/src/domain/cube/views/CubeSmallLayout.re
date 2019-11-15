let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardSmallLayout = [%bs.raw {| css(tw`
  p-8
  h-full
  w-full
`)|}];

let cardSmallLayoutIcon = [%bs.raw {| css(tw`
  h-full
  w-full
`)|}];

let cardSmallLayoutText = [%bs.raw {| css(tw`
  flex
  justify-center
  items-center
  text-xl
`)|}];

[@react.component]
let make = (~id: Cube.Model.idType, ~normalized) => {
  let cube =
    normalized
    |> MyNormalizr.Converter.Cube.Remote.getRecord(_, id)
    |> Belt.Option.getWithDefault(_, Cube.Model.Record.defaultWithId((), id));
  <div className=cardSmallLayout>
    <CubeIcon className=cardSmallLayoutIcon />
    <div className=cardSmallLayoutText>
      {ReasonReact.string(cube.data.name)}
    </div>
  </div>
};