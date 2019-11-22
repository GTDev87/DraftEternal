let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

type state = option(string);

type action =
  | UpdateQuery(string);

let cubeBuilder = [%bs.raw {| css(tw`
  flex
  h-full
`)|}];

let cubeBuilderCardPickerArea = [%bs.raw {| css(tw`
  w-3/4
`)|}];

let cubeBuilderScrollArea = [%bs.raw {| css(tw`
  overflow-y-scroll
`)|}];

let cubeBuilderCardPickerAreaSingleCard = [%bs.raw {| css(tw`
  w-1/6
  cursor-pointer
`)|}];

let cubeBuilderCardSearchArea = [%bs.raw {| css(tw`
  w-full
  bg-green
  flex
`)|}];

let cubeBuilderCardSelectionArea = [%bs.raw {| css(tw`
  w-1/4
  bg-teal-dark
`)|}];

let cubeBuilderCardSearchAreaText = [%bs.raw {| css(tw`
  mr-4
`)|}];

[@react.component]
let make = (~user: User.Model.Record.t, ~guest, ~cardIds, ~normalized, ~updateNormalizr, ~index, ~update=false) => {
  Js.log("CubeBuilder update");
  Js.log(update);
  let updateUser = action => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };

  guest ?
    <GoogleLoginButton /> :
    <div className=cubeBuilder>
      <div className=cubeBuilderCardPickerArea>
        <SearchCard
          selectedCardIds=user.local.builderCube.data.cardIds
          cardIds
          normalized
          index
          onCardClick={(cId) => User.Action.LocalAction(UpdateBuilderCube(AddCard(cId))) |> updateUser |> ignore}
        />
      </div>
      <div className=cubeBuilderCardSelectionArea>
        <CardSelectionArea user normalized updateUser />
      </div>
    </div>
};