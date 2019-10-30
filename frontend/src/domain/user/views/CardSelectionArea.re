let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardSelectionArea = [%bs.raw {| css(tw`
  h-full
  flex
  flex-col
  overflow-hidden
`)|}];

let cardSelectionAreaStats = [%bs.raw {| css(tw`
  flex-no-grow
`)|}];

let cardSelectionAreaSelectionsBox = [%bs.raw {| css(tw`
  flex-grow
  overflow-hidden
`)|}];


let cardSelectionAreaSelections = [%bs.raw {| css(tw`
  h-full
  overflow-y-scroll
  rounded
  border-solid
  border-teal-darker
  border
  mx-2
`)|}];

let cardSelectionAreaOptions =[%bs.raw {| css(tw`
  flex-no-grow
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~normalized, ~updateNormalizr) => {
  <div className=cardSelectionArea>
    <div className=cardSelectionAreaStats>
      {ReasonReact.string("Stats")}
    </div>
    <div className=cardSelectionAreaSelectionsBox>
      <div className=cardSelectionAreaSelections>
        {
          user.local.builderCube.data.cardIds
          |> Belt.List.map(_, (cardId: Schema.Card.id) => <CardSmallLayout key=(Card.Model.getUUIDFromId(cardId)) id=cardId normalized />)
          |> Utils_ReasonReact.listToReactArray
        }
      </div>
    </div>
    <div className=cardSelectionAreaOptions>
      {ReasonReact.string("SAVE")}
    </div>
  </div>
};