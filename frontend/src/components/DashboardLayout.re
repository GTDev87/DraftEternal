let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let dashboardLayout = [%bs.raw {| css(tw`
  w-screen
  h-screen
  flex
  flex-col
`)|}];

let dashboardLayoutMastHead = [%bs.raw {| css(tw`
`)|}];

let dashboardContentArea = [%bs.raw {| css(tw`
  h-full
  flex
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
let make = (~user: option(User.Model.Record.t)=?, ~normalized, ~updateNormalizr) => {

  let (tab, dispatch) = SideTab.tabReducer();

  <div className=dashboardLayout>
    <div className=dashboardLayoutMastHead>
      <MastHead user />
    </div>
    <div className=dashboardContentArea>
      <div className=dashboardContentAreaSideBar>
        <SideBar tab chooseTab={(t) => dispatch(SideTab.toAction(t))}/>
      </div>
      <div className=dashboardContentAreaSelection>
        <ContentArea tab user normalized updateNormalizr />
      </div>
    </div>
  </div>
};