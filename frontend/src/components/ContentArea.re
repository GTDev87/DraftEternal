let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let contentArea = [%bs.raw {| css(tw`
`)|}];

[@react.component]
let make = (~tab, ~user: option(User.Model.Record.t), ~normalized, ~updateNormalizr) => {
  <div className=contentArea>
    {
      switch(tab) {
      | SideTab.Library => <div/>
      | SideTab.Builder =>
          switch(user){
          | Some(user) => <CubeBuilder id={user.local.newCubeId} normalized updateNormalizr />
          | None => <div />
          }
      }
    }
  </div>
};