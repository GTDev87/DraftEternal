let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let saveCubeContentModal = [%bs.raw {| css(tw`
  p-4
  bg-teal
  flex
  max-h-screen
`)|}];

let saveCubeContentModalSaveView = [%bs.raw {| css(tw`
  w-1/2
  pr-4
  flex
  flex-col
`)|}];

let saveCubeContentModalDeckView = [%bs.raw {| css(tw`
  w-1/2
`)|}];

let saveCubeContentModalArea = [%bs.raw {| css(tw`
  pb-8
  flex-none
`)|}];

let saveCubeContentModalDescriptionArea = [%bs.raw {| css(tw`
  pb-8
  flex-grow
`)|}];

let saveCubeContentModalSaveButtonArea = [%bs.raw {| css(tw`
  pb-8
  flex-none
`)|}];

let saveCubeContentModalTitleAreaTextArea = [%bs.raw {| css(tw`
  h-32
  border-solid
  border-blue-lighter
  border
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~normalized, ~updateUser, ~afterSave=?) => {
  <div className=saveCubeContentModal>
    <div className=saveCubeContentModalSaveView>
      <div className=saveCubeContentModalArea>
        <TextInput
          value={user.local.builderCube.data.name}
          onTextChange={(name) => updateUser(User.Action.LocalAction(UpdateBuilderCube(UpdateName(name))))}
          placeholder="Enter Name"
        />
      </div>
      <div className=saveCubeContentModalArea>
        <Select
          selectedId={user.local.builderCube.data.display}
          selections={
            DisplayType.all()
            |> Belt.List.map(_, (dt) => ({id: dt, text: DisplayType.toString(dt)}: Select.selectionType(DisplayType.t)))
          }
          idToString={DisplayType.toString}
          onSelect={(dt) => {
            updateUser(User.Action.LocalAction(UpdateBuilderCube(SelectDisplay(Belt.Option.getWithDefault(dt, `PUBLIC)))))
          }}
        />
      </div>
      <div className=saveCubeContentModalDescriptionArea>
        <TextArea
          className=saveCubeContentModalTitleAreaTextArea
          value={user.local.builderCube.data.description}
          onTextChange={(description) => updateUser(User.Action.LocalAction(UpdateBuilderCube(UpdateDescription(description))))}
          placeholder="Enter Description"
        />
      </div>
      <div className=saveCubeContentModalSaveButtonArea>
        <Cube_Mutation.CreateCube.ContainerMutation>
          ...{(giveTestToClassroomMutation) =>
            <Button
              onClick=((_) => {
                giveTestToClassroomMutation(
                  ~id=user.local.builderCube.data.id,
                  ~name=user.local.builderCube.data.name,
                  ~description=user.local.builderCube.data.description,
                  ~display=user.local.builderCube.data.display,
                  ~creatorId=user.local.builderCube.data.creatorId,
                  ~cardIds=user.local.builderCube.data.cardIds,
                )
              })
            >
              {ReasonReact.string("SAVE")}
            </Button>
          }
        </Cube_Mutation.CreateCube.ContainerMutation>
      </div>
    </div>
    <div className=saveCubeContentModalDeckView>
      <SmallDeckView
        normalized
        cardIds=user.local.builderCube.data.cardIds
      />
    </div>
  </div>
};