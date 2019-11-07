let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

type state = option(string);

type action =
  | UpdateQuery(string);

let searchCard = [%bs.raw {| css(tw`
  h-full
  flex
  flex-col
`)|}];

let searchCardScrollArea = [%bs.raw {| css(tw`
  overflow-y-scroll
`)|}];

let searchCardCardPickerAreaSingleCard = [%bs.raw {| css(tw`
  w-1/6
  cursor-pointer
`)|}];

let searchCardSearchArea = [%bs.raw {| css(tw`
  w-full
  flex
`)|}];

let searchCardSearchInputClass = [%bs.raw {| css(tw`
  m-2
`)|}];


[@react.component]
let make = (~cardIds, ~normalized, ~index, ~onCardClick) => {
  let (query, dispatch) =
    React.useReducer(
      (_, action) =>
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
  
    <div className=searchCard>
      <div className=searchCardSearchArea>
        <TextInput
          className=searchCardSearchInputClass
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
        className=searchCardScrollArea
        loader={<div>{ReasonReact.string("LOADING...")}</div>}
      >
        {
          Belt.List.map(updatedCardIds, (cId: Card.Model.idType) => {
            <div
              key=(Card.Model.getUUIDFromId(cId))
              className=searchCardCardPickerAreaSingleCard
              onClick={(_) => onCardClick(cId)}
            >
              <CardFullLayout id=cId normalized />
            </div>
          })
        }
      </InfiniteScrollLoadNumber>
  </div>
};