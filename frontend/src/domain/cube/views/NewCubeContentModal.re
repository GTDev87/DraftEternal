// let css = Css.css;
// let cx = Css.cx;
// let tw = Css.tw;

// let newCubeContentModal = [%bs.raw {| css(tw`
// `)|}];

// [@react.component]
// let make = (~id, ~normalized, ~updateNormalizr) => {
// //   let newCube =
// //     normalized
// //     |> MyNormalizr.Converter.Cube.Remote.getRecord(_, id)
// //     |> Belt.Option.getWithDefault(_, Cube.Model.Record.defaultWithId((), id));

//   <NewTypeModalContents
//     titleText="Create a classroom"
//     placeholderText="Classroom name"
//     descriptionText="Classrooms are where you store your student rosters, where you see tests completed by students and where you see your analytics results from taken tests."
//     buttonText="Create class"
//     value={newClassroom.data.name}
//     onChange={a => updateNewClassroom(Classroom.Action.EditName(a))}
//     addType=addNewClassroom
//     onKeyDown={
//       GenericInput.enterSubmitWithCommand(addNewClassroom, () =>
//         updateNewClassroom(Classroom.Action.NoOpKeyDown)
//       )
//     }
//   />
// };
