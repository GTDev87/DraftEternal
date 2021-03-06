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

let toString = (sideTabType : SideTab.t, normalized) : string =>
  switch(sideTabType){
  | SideTab.Library => "Cube Library"
  | SideTab.SearchCard => "Search Card"
  | SideTab.CreateCube => "+ Create Cube"
  | SideTab.CubeManager => "Cube Manager"
  | SideTab.Cube(id) => ""
  | SideTab.CubeEdit(id) => ""
  };


[@react.component]
let make = (~user: User.Model.Record.t, ~chooseTab, ~normalized, ~guest) => {
  <div className=sideBar>
    {
      SideTab.all(guest)
      |> Belt.List.map(_, (t) => {
          let text = toString(t, normalized);
          <div
            key=text
            onClick={(e) => chooseTab(t) |> ignore}
            className=(user.local.tab === t ? sideBarWithBold : sideBarLine)
          >
            <SidebarImageName icon={SideTab.toIcon(t)} text />
          </div>
      })
      |> Utils.ReasonReact.listToReactArray
    }
  </div>
};