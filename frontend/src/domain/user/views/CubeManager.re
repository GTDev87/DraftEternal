let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

type state = option(string);

type action =
  | UpdateQuery(string);

let deckManagerClass = [%bs.raw {| css(tw`
  h-full
  flex
  flex-col
`)|}];

let deckManagerScrollAreaClass = [%bs.raw {| css(tw`
  overflow-y-scroll
  h-full
`)|}];

let deckManagerCubePickerArea = [%bs.raw {| css(tw`
  w-1/5
  cursor-pointer
`)|}];

[@react.component]
let make = (~cubeIds, ~normalized, ~onCubeClick) => {
  <div className=deckManagerClass>
    <InfiniteScrollLoadNumber
      className=deckManagerScrollAreaClass
      loader={<div>{ReasonReact.string("LOADING...")}</div>}
    >
      {
        Belt.List.map(cubeIds, (cId: Cube.Model.idType) => {
          <div
            key=(Cube.Model.getUUIDFromId(cId))
            className=deckManagerCubePickerArea
            onClick={(_) => {
              Js.log("clicking cube");
              onCubeClick(cId);
            }}
          >
            <CubeSmallLayout id=cId normalized />
          </div>
        })
      }
    </InfiniteScrollLoadNumber>
  </div>
};