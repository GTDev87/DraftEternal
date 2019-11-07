let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let smallDeckViewClass = [%bs.raw {| css(tw`
  h-full
  overflow-y-scroll
  rounded
  border-solid
  border-teal-darker
  border
  mx-2
`)|}];

let smallDeckViewCardClass = [%bs.raw {| css(tw`
  cursor-pointer
`)|}];
  

[@react.component]
let make = (~cardIds, ~normalized, ~cardSelect=?) => {
  let cardSelect = Belt.Option.getWithDefault(cardSelect, (_) => {()});

  <div className=smallDeckViewClass>
    {
      cardIds
      |> Belt.List.map(_, (cardId: Schema.Card.id) =>
          <div
              key={cardId |> Card.Model.getUUIDFromId}
              className=smallDeckViewCardClass
              onClick={(_) => cardSelect(cardId) |> ignore}
          >
              <CardSmallLayout key=(Card.Model.getUUIDFromId(cardId)) id=cardId normalized />
          </div>
      )
      |> Utils_ReasonReact.listToReactArray
    }
  </div>
};


