let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardLayout = [%bs.raw {| css(tw`
  h-full
  overflow-hidden
  flex
  flex-col
`)|}];

let cardLayoutTitle = [%bs.raw {| css(tw`
  p-2
  text-4xl
  font-bold
  flex
  justify-between
  pb-0
`)|}];

let cardLayoutTitleString = [%bs.raw {| css(tw`
  flex
  justify-center
  items-center
`)|}];

let cardLayoutButton = [%bs.raw {| css(tw`
  text-base
`)|}];

let cardLayoutButtonInner = [%bs.raw {| css(tw`
  px-8
  py-2
`)|}];

let cardLayoutButtonWrapper = [%bs.raw {| css(tw`
  flex
  justify-center
  items-center
`)|}];

let cardLayoutSearchArea = [%bs.raw {| css(tw`
  overflow-y-scroll
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~id, ~normalized, ~updateNormalizr, ~index) => {

  let updateUser = (action) => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };
  let optionCube = MyNormalizr.Converter.Cube.Remote.getRecord(normalized, id);

  Belt.Option.mapWithDefault(optionCube, <div/>, (cube) => {
    let userId = 
      optionCube
      |> Belt.Option.mapWithDefault(_, "", (cube) => User.Model.getUUIDFromId(cube.data.creatorId));

    let iAmCreator = (userId == user.data.id);

    <div className=cardLayout>
      <div className=cardLayoutTitle>
        <div className=cardLayoutTitleString>
          {ReasonReact.string(Belt.Option.mapWithDefault(optionCube, "", (c) => c.data.name))}
        </div>
        <div className=cardLayoutButtonWrapper>
          {
            iAmCreator ?
              <Button
                className=cardLayoutButton
                onClick=((_) => {
                  updateUser(CombineReducer(
                    User.Action.LocalAction(CopyBuilderCube(cube)),
                    User.Action.LocalAction(ChangeTab(SideTab.CreateCube))
                  ));
                  Js.log("BETWEEN");
                  ();
                })
                autoFocus=false
                innerClassName=cardLayoutButtonInner
              >
                {ReasonReact.string("Edit")}
              </Button> :
              <div/>
          }
        </div>
      </div>
      <div className=cardLayoutSearchArea>
        <SearchCard cardIds=cube.data.cardIds normalized index />
      </div>
    </div>
  })
};