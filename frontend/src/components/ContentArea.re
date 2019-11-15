let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let contentArea = [%bs.raw {| css(tw`
  h-full
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~guest, ~cardIds, ~normalized, ~updateNormalizr, ~index) => {
  let updateUser = (action) => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };

  Js.log("content area");


  <div className=contentArea>
    {
      switch(user.local.tab) {
      | SideTab.Library => <div/>
      | SideTab.SearchCard => <SearchCard cardIds normalized index />
      | SideTab.CreateCube => <CubeBuilder user guest cardIds normalized updateNormalizr index />
      | SideTab.CubeManager => <CubeManager user normalized onCubeClick={cId => updateUser(User.Action.LocalAction(ChangeTab(SideTab.Cube(cId)))) |> ignore} />
      | SideTab.Cube(id) => <CubeLayout user id normalized updateNormalizr index />
      }
    }
  </div>
};