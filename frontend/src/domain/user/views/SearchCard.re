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

let searchCardCardPickerAreaSingleCardWoPointer = [%bs.raw {| css(tw`
  w-1/6
`)|}];

let searchCardCardPickerAreaSingleCardSelected = [%bs.raw {| css(tw`
  opacity-25
  cursor-not-allowed
`)|}];

let searchCardSearchArea = [%bs.raw {| css(tw`
  w-full
  flex
`)|}];

let searchCardSearchInputClass = [%bs.raw {| css(tw`
  m-2
`)|}];


[@react.component]
let make = (~cardIds, ~normalized, ~index, ~onCardClick=?, ~selectedCardIds=?) => {
  let onCardClickVal = Belt.Option.getWithDefault(onCardClick, (_ => ()));
  
  let (query, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | UpdateQuery(query) => (query == "") ? None : Some(query)
        },
      None
    );

  let updatedCardIds: list(Card.Model.idType) =
    switch(query) {
    | None => cardIds
    | Some(query) => {
      let allCardIdsSet =
        cardIds
        |> Belt.List.map(_, Card.Model.getUUIDFromId)
        |> Belt.List.toArray
        |> Belt_SetString.fromArray;

      let searchCardIdsSet =
        index
        |> FlexSearch.search(_, query)
        |> Belt_SetString.fromArray;
      
      let stringList =
        allCardIdsSet
        |> Belt_SetString.intersect(_, searchCardIdsSet)
        |> Belt_SetString.toList;

      Belt.List.map(stringList, Card.Model.idToTypedId);
    }
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
        autoFocus=true
      />
    </div>
    
    <InfiniteScrollLoadNumber
      className=searchCardScrollArea
      loader={<div>{ReasonReact.string("LOADING...")}</div>}
    >
      {
        Belt.List.map(updatedCardIds, (cId: Card.Model.idType) => {
          let selected =
            Belt.Option.mapWithDefault(selectedCardIds, false, (selectedCardIds) => {
              Belt.List.has(selectedCardIds, cId, (a, b) => a == b);
            });
          <div
            key=(Card.Model.getUUIDFromId(cId))
            className=cx((onCardClick != None ? searchCardCardPickerAreaSingleCard: searchCardCardPickerAreaSingleCardWoPointer), selected ? searchCardCardPickerAreaSingleCardSelected : "")
            onClick={(_) => onCardClickVal(cId)}
          >
            <CardFullLayout id=cId normalized />
          </div>
        })
      }
    </InfiniteScrollLoadNumber>
  </div>
};