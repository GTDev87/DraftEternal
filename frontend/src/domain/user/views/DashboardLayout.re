let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let dashboardLayout = [%bs.raw {| css(tw`
  w-screen
  h-screen
  flex
  flex-col
  p-0
  m-0
  overflow-y-hidden
`)|}];

let dashboardLayoutMastHead = [%bs.raw {| css(tw`
  flex-no-grow
`)|}];

let dashboardContentArea = [%bs.raw {| css(tw`
  flex-1
  flex-grow
  flex
  overflow-y-hidden
`)|}];

let dashboardContentAreaSideBar = [%bs.raw {| css(tw`
  w-1/6	
  bg-teal-dark
`)|}];

let dashboardContentAreaSelection = [%bs.raw {| css(tw`
  w-5/6
  bg-teal-light
`)|}];


[@react.component]
let make = (~id: Schema.User.id, ~cardIds, ~normalized, ~updateNormalizr) => {

  // let (user.local.tab, dispatch) = SideTab.tabReducer();

  let optionUser =
    MyNormalizr.Converter.User.Remote.getRecord(normalized, id);

  switch(MyNormalizr.Converter.User.Remote.getRecord(normalized, id)){
  | None => <div/>
  | Some(user) => {
      let updateUser = action => {
        MyNormalizr.Converter.User.Remote.updateWithDefault(
          (),
          normalized |> Js.Promise.resolve,
          User.Model.idToTypedId(user.data.id),
          action,
        )
        |> updateNormalizr;
      };

      Js.log("user.local.tab");
      Js.log(user.local.tab);

      <div className=dashboardLayout>
        {
          <>
          </>;
          /*
            <ReactModal
              autoFocus=false
              isOpen={user.local.tab === CreateCube}
              onRequestClose={() => updateUser(User.Action.LocalAction(ChangeTab(Library)))}
            >
              {
                switch (user.local.tab) {
                | CreateCube =>
                  <div/>
                  // let newClassroom =
                  //   normalized
                  //   |> MyNormalizr.Converter.Cube.Remote.getRecord(_, user.local.newCubeId)
                  //   |> Belt.Option.getWithDefault(_, Cube.Model.Record.defaultWithId((), user.local.newCubeId));
        
                  // <Cube.Mutation.CreateCube>
                  //   ...((createCube) =>
                  //       <NewClassroomModalContents
                  //         newClassroom
                  //         addNewClassroom={
                  //           () =>
                  //             updateTeacher(
                  //               Teacher.Action.(
                  //                 CombineReducer(
                  //                   /* AddClassroom, */
                  //                   ApolloAddClassroom(() => addClassroom(
                  //                     ~id=newClassroom.data.id,
                  //                     ~name=newClassroom.data.name,
                  //                     ~teacherId=teacherId |> Teacher.Model.getUUIDFromId,
                  //                     (),
                  //                   )),
                  //                   CombineReducer(
                  //                     OpenModal(None),
                  //                     SelectSideBar(
                  //                       SideTab.Classroom,
                  //                       teacher.local.newClassroomId
                  //                       |> Classroom.Model.getUUIDFromId,
                  //                     ),
                  //                   ),
                  //                 )
                  //               ),
                  //             )
                  //         }
                  //         updateNewClassroom
                  //         normalized
                  //       />
                  //   )
                  // </Cube.Mutation.CreateCube>;

                        <NewClassroomModalContents
                          newClassroom
                          addNewClassroom={
                            () =>
                              updateTeacher(
                                Teacher.Action.(
                                  CombineReducer(
                                    /* AddClassroom, */
                                    ApolloAddClassroom(() => addClassroom(
                                      ~id=newClassroom.data.id,
                                      ~name=newClassroom.data.name,
                                      ~teacherId=teacherId |> Teacher.Model.getUUIDFromId,
                                      (),
                                    )),
                                    CombineReducer(
                                      OpenModal(None),
                                      SelectSideBar(
                                        SideTab.Classroom,
                                        teacher.local.newClassroomId
                                        |> Classroom.Model.getUUIDFromId,
                                      ),
                                    ),
                                  )
                                ),
                              )
                          }
                          updateNewClassroom
                          normalized
                        />
                | _ => <div/>
                }
              }
            </ReactModal>
          */
        }
        <div className=dashboardLayoutMastHead>
          <MastHead user />
        </div>
        <div className=dashboardContentArea>
          <div className=dashboardContentAreaSideBar>
            <SideBar user chooseTab={(t) => updateUser(User.Action.LocalAction(ChangeTab(t)))} normalized/>
          </div>
          <div className=dashboardContentAreaSelection>
            <ContentArea user cardIds normalized updateNormalizr />
          </div>
        </div>
      </div>

    }
  }  
  
};