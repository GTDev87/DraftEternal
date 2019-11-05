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
  h-full
  flex
  flex-col
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
let make = (~user: User.Model.Record.t, ~cardIds, ~normalized, ~updateNormalizr, ~index) => {
  let updateUser = action => {
    MyNormalizr.Converter.User.Remote.updateWithDefault(
      (),
      normalized |> Js.Promise.resolve,
      User.Model.idToTypedId(user.data.id),
      action,
    )
    |> updateNormalizr;
  };

  let (query, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateQuery(query) => (query == "") ? None : Some(query)
        },
      None
    );

  let updatedCardIds =
    switch(query) {
    | None => cardIds
    | Some(query) =>
        index
        |> FlexSearch.search(_, query)
        |> Belt.List.fromArray
        |> Belt.List.map(_, Card.Model.idToTypedId)
    };
  
  <div className=cubeBuilder>
    <div className=cubeBuilderCardPickerArea>
      <div className=cubeBuilderCardSearchArea>
        <TextInput
          // className=inputClass
          placeholder=("Search")
          value={
            switch(query){
            | None => ""
            | Some(text) => text
            }
          }
          onTextChange={(t) => {
            dispatch(UpdateQuery(t));
            () |> Js.Promise.resolve; 
          }}
          autoFocus=false
        />
      </div>
      
      <InfiniteScrollLoadNumber
        className=cubeBuilderScrollArea
        loader={<div>{ReasonReact.string("LOADING...")}</div>}
      >
        {
          Belt.List.map(updatedCardIds, (cId: Card.Model.idType) => {
            <div
              key=(Card.Model.getUUIDFromId(cId))
              className=cubeBuilderCardPickerAreaSingleCard
              onClick={(_) => User.Action.LocalAction(UpdateBuilderCube(AddCard(cId))) |> updateUser |> ignore}
            >
              <CardFullLayout id=cId normalized />
            </div>
          })
        }
      </InfiniteScrollLoadNumber>
    </div>
    <div className=cubeBuilderCardSelectionArea>
      <CardSelectionArea user normalized updateUser />
    </div>
  </div>
};