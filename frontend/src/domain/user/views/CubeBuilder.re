let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cubeBuilder = [%bs.raw {| css(tw`
  flex
  h-full
`)|}];

let cubeBuilderCardPickerArea = [%bs.raw {| css(tw`
  w-3/4
  h-full
  flex
  flex-wrap
  overflow-y-scroll
`)|}];

let cubeBuilderCardPickerAreaSingleCard = [%bs.raw {| css(tw`
  w-1/6
  cursor-pointer
`)|}];

let cubeBuilderCardSelectionArea = [%bs.raw {| css(tw`
  w-1/4
  h-full
  bg-teal-dark
  table-auto
  overflow-y-scroll
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~cardIds, ~normalized, ~updateNormalizr) => {
  let updateUser = action => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };

  <div className=cubeBuilder>
    <div className=cubeBuilderCardPickerArea>
      {
        cardIds
        |> Belt.List.map(_, (cId: Card.Model.idType) => {
            <div
              key=(Card.Model.getUUIDFromId(cId))
              className=cubeBuilderCardPickerAreaSingleCard
              onClick={(_) => updateUser(User.Action.LocalAction(UpdateBuilderCube(AddCard(cId)))) |> ignore}
            >
              <CardFullLayout id=cId normalized />
            </div>
        })
        |> Utils_ReasonReact.listToReactArray
      }
    </div>
    <div className=cubeBuilderCardSelectionArea>
      {
        [Card.Model.idToTypedId("0-3")] @ user.local.builderCube.data.cardIds
        |> Belt.List.map(_, (cardId: Schema.Card.id) => <CardSmallLayout key=(Card.Model.getUUIDFromId(cardId)) id=cardId normalized />)
        |> Utils_ReasonReact.listToReactArray
      }
    </div>
  </div>
};