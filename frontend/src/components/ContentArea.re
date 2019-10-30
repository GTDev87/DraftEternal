let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let contentArea = [%bs.raw {| css(tw`
  h-full
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~cardIds, ~normalized, ~updateNormalizr) => {
  <div className=contentArea>
    {
      switch(user.local.tab) {
      | SideTab.Library => <div/>
      | SideTab.CreateCube =>
          <CubeBuilder user cardIds normalized updateNormalizr />
      | SideTab.MyCube(id) =>
          <CubeBuilder user cardIds normalized updateNormalizr />
      }
    }
  </div>
};