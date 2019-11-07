let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let saveCubeContentModal = [%bs.raw {| css(tw`
  p-4
  bg-teal
`)|}];

let saveCubeContentModalArea = [%bs.raw {| css(tw`
  mb-8
`)|}];

let saveCubeContentModalTitleAreaTextArea = [%bs.raw {| css(tw`
  h-32
  border-solid
  border-blue-lighter
  border
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~updateUser, ~afterSave=?) => {
  Js.log("user.local.builderCube.data.display");
  Js.log(user.local.builderCube.data.display);
  <div className=saveCubeContentModal>
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
          Js.log("DDDDDDDDDDDDDDDDDDDDDD");
          Js.log("dt");
          Js.log(dt);
          updateUser(User.Action.LocalAction(UpdateBuilderCube(SelectDisplay(Belt.Option.getWithDefault(dt, `PUBLIC)))))
        }}
      />
    </div>
    <div className=saveCubeContentModalArea>
      <TextArea
        className=saveCubeContentModalTitleAreaTextArea
        value={user.local.builderCube.data.description}
        onTextChange={(description) => updateUser(User.Action.LocalAction(UpdateBuilderCube(UpdateDescription(description))))}
        placeholder="Enter Description"
      />
    </div>
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
};