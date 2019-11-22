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
  p-2
`)|}];

let cardSelectionAreaStatsTitle = [%bs.raw {| css(tw`
  text-3xl
  text-white
  whitespace-no-wrap
`)|}];

let cardSelectionAreaStatsStats = [%bs.raw {| css(tw`
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

let cardSelectionAreaOptions = [%bs.raw {| css(tw`
  flex-no-grow
`)|}];

let cardSelectionAreaOptionsButton = [%bs.raw {| css(tw`
  p-2
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~normalized, ~updateUser) => {
  <div className=cardSelectionArea>
    <div className=cardSelectionAreaStats>
      <div className=cardSelectionAreaStatsTitle>
        {ReasonReact.string(user.local.builderCube.data.name)}
      </div>
      <div className=cardSelectionAreaStatsStats>
        /* {ReasonReact.string("Stats")} */
      </div>
    </div>
    <div className=cardSelectionAreaSelectionsBox>
      <SmallDeckView
        normalized
        cardIds=user.local.builderCube.data.cardIds
        cardSelect={(cardId) => updateUser(User.Action.LocalAction(UpdateBuilderCube(RemoveCard(cardId)))) |> ignore}
      />
    </div>
    <div className=cardSelectionAreaOptions>
      <Cube_Mutation.CreateCube.ContainerMutation>
        ...{(giveTestToClassroomMutation) =>
          <Button
            className=cardSelectionAreaOptionsButton
            onClick=((_) => {
              updateUser(
                User.Action.LocalAction(OpenModal(SaveCube))
              )
            })
          >
            {ReasonReact.string("SAVE")}
          </Button>
        }
      </Cube_Mutation.CreateCube.ContainerMutation>
    </div>
  </div>
};