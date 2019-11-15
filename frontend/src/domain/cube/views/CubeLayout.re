let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardLayout = [%bs.raw {| css(tw`
  h-full
  overflow-hidden
  flex
  flex-col
`)|}];

let cardLayoutTitle = [%bs.raw {| css(tw`
  p-2
  text-4xl
  font-bold
  flex
  justify-between
  pb-0
`)|}];

let cardLayoutTitleString = [%bs.raw {| css(tw`
  flex
  justify-center
  items-center
`)|}];

let cardLayoutButton = [%bs.raw {| css(tw`
  text-base
`)|}];

let cardLayoutButtonInner = [%bs.raw {| css(tw`
  px-8
  py-2
`)|}];

let cardLayoutButtonWrapper = [%bs.raw {| css(tw`
  flex
  justify-center
  items-center
`)|}];

let cardLayoutSearchArea = [%bs.raw {| css(tw`
  overflow-y-scroll
`)|}];

[@react.component]
let make = (~user, ~id, ~normalized, ~updateNormalizr, ~index) => {
  let optionCube = MyNormalizr.Converter.Cube.Remote.getRecord(normalized, id);

  let cardIds = 
    optionCube
    |> Belt.Option.mapWithDefault(_, [], (cube) => cube.data.cardIds);
  <div className=cardLayout>
    <div className=cardLayoutTitle>
      <div className=cardLayoutTitleString>
        {ReasonReact.string(Belt.Option.mapWithDefault(optionCube, "", (c) => c.data.name))}
      </div>
      <div className=cardLayoutButtonWrapper>
        <Button
          className=cardLayoutButton
          onClick=((_) => ())
          autoFocus=false
          innerClassName=cardLayoutButtonInner
        >
          {ReasonReact.string("Edit")}
        </Button>
      </div>
    </div>
    <div className=cardLayoutSearchArea>
      <SearchCard cardIds normalized index />
    </div>
  </div>
};