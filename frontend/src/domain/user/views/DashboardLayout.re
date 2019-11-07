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
let make = (~id: Schema.User.id, ~cardIds, ~normalized, ~updateNormalizr, ~index) => {

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

      <div className=dashboardLayout>
        {
          <ReactModal
            autoFocus=false
            isOpen={user.local.modal !== None}
            className=dashboardLayoutModalClass
            onRequestClose={() => updateUser(User.Action.LocalAction(CloseModal))}
          >
            {
              /* REMEMBER RESET ID IN LOCAL */
              switch (user.local.modal) {
              | Some(SaveCube) => <SaveCubeContentModal user updateUser normalized />
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
            <SideBar user chooseTab={(t) => updateUser(User.Action.LocalAction(ChangeTab(t)))} normalized/>
          </div>
          <div className=dashboardContentAreaSelection>
            <ContentArea user cardIds normalized updateNormalizr index />
          </div>
        </div>
      </div>
    }
  }  
};