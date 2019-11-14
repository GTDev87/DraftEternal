let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let contentArea = [%bs.raw {| css(tw`
  h-full
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~guest, ~cardIds, ~normalized, ~updateNormalizr, ~index) => {
  <div className=contentArea>
    {
      switch(user.local.tab) {
      | SideTab.Library => <div/>
      | SideTab.SearchCard => <SearchCard cardIds normalized index onCardClick={_ => ()} />
      | SideTab.CreateCube =>
          <CubeBuilder user guest cardIds normalized updateNormalizr index />
      | SideTab.MyCube(id) =>
          <CubeBuilder user guest cardIds normalized updateNormalizr index />
      }
    }
  </div>
};