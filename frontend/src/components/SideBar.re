let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let sideBar = [%bs.raw {| css(tw`
`)|}];

let sideBarLine = [%bs.raw {| css(tw`
  py-6
  cursor-pointer
`)|}];

let sideBarBold = [%bs.raw {| css(tw`
  font-bold
  bg-teal-darker
  cursor-default
`)|}];

let sideBarWithBold = cx(sideBarLine, sideBarBold);

[@react.component]
let make = (~tab, ~chooseTab) => {
  <div className=sideBar>
    {
      SideTab.all
      |> Belt.List.map(_, (t) =>
           <div onClick={(e) => chooseTab(t)} className=(tab === t ? sideBarWithBold : sideBarLine)>
            {SideTab.toSidebarImageName(t)}
           </div>
      )
      |> Utils.ReasonReact.listToReactArray
    }
  </div>
};