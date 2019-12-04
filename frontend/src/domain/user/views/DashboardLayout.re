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

let dashboardLayoutModalClass = [%bs.raw {| css(tw`
  bg-teal
`)|}];


[@react.component]
let make = (~id: Schema.User.id, ~guest, ~cardIds, ~cubeIds, ~normalized, ~updateNormalizr, ~index) => {

  let optionUser =
    MyNormalizr.Converter.User.Remote.getRecord(normalized, id);

  let user = 
    Belt.Option.getWithDefault(optionUser,
      User_Record.guestDataId(User.Model.getUUIDFromId(id)));
  
  let updateUser = action => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };

  <div className=dashboardLayout>
    {
      <ReactModal
        autoFocus=false
        isOpen={user.local.modal !== None}
        className=dashboardLayoutModalClass
        onRequestClose={() => updateUser(CombineReducer(User.Action.LocalAction(CloseModal), User.Action.LocalAction(ResetBuilderCube)))}
      >
        {
          /* REMEMBER RESET ID IN LOCAL */
          switch (user.local.modal) {
          | Some(SaveCube) =>
              <SaveCubeContentModal
                user
                updateUser
                normalized
                afterSave=User.Action.LocalAction(ResetBuilderCube)
              />
          /* | Some(ClientDraftCube(id, Start)) =>
              <CubeClientDraftModal
                id
                updateNormalizr
                normalized
                index
              /> */
          | None => <> </>
          }
        }
      </ReactModal>
    }
    <div className=dashboardLayoutMastHead>
      <MastHead user />
    </div>
    <div className=dashboardContentArea>
      <div className=dashboardContentAreaSideBar>
        <SideBar
          user
          guest
          chooseTab={(t) =>
            updateUser(
              CombineReducer(
                switch(t){
                | SideTab.CreateCube => User.Action.LocalAction(ResetBuilderCube)
                | _ => User.Action.Nothing
                },
                User.Action.LocalAction(ChangeTab(t))
              )
            )
          }
          normalized
        />
      </div>
      <div className=dashboardContentAreaSelection>
        <ContentArea user guest cardIds cubeIds normalized updateNormalizr index />
      </div>
    </div>
  </div>;
};