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

let cardSelectionAreaCardSmall = [%bs.raw {| css(tw`
  cursor-pointer
`)|}];

let cardSelectionAreaOptions =[%bs.raw {| css(tw`
  flex-no-grow
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~normalized, ~updateUser) => {
  <div className=cardSelectionArea>
    <div className=cardSelectionAreaStats>
      {ReasonReact.string("Stats")}
    </div>
    <div className=cardSelectionAreaSelectionsBox>
      <div className=cardSelectionAreaSelections>
        {
          user.local.builderCube.data.cardIds
          |> Belt.List.map(_, (cardId: Schema.Card.id) =>
              <div
                key={cardId |> Card.Model.getUUIDFromId}
                className=cardSelectionAreaCardSmall
                onClick={(_) => updateUser(User.Action.LocalAction(UpdateBuilderCube(RemoveCard(cardId)))) |> ignore}
              >
                <CardSmallLayout key=(Card.Model.getUUIDFromId(cardId)) id=cardId normalized />
              </div>
          )
          |> Utils_ReasonReact.listToReactArray
        }
      </div>
    </div>
    <div className=cardSelectionAreaOptions>
      <Button onClick=((_) => ())>
        {ReasonReact.string("SAVE")}
      </Button>
    </div>
  </div>
};