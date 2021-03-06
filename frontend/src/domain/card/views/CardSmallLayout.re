let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardSmallLayout = [%bs.raw {| css(tw`
  w-full
  flex
  text-white
  font-bold
  text-xs
  mb-px
`)|}];

let cardSmallLayoutColor = (colors: list(InfluenceType.t)) =>
  switch(Belt.List.head(colors)) {
  | None => [%bs.raw {| css(tw` bg-grey-darkest `)|}]
  | Some(color) =>
    switch(Belt.List.length(colors)) {
    | 1 =>
        switch(color) {
        | `FIRE => [%bs.raw {| css(tw` bg-red-darker `)|}]
        | `TIME => [%bs.raw {| css(tw` bg-yellow-darker `)|}]
        | `PRIMAL => [%bs.raw {| css(tw` bg-blue-dark `)|}]
        | `JUSTICE => [%bs.raw {| css(tw` bg-green-darker `)|}]
        | `SHADOW => [%bs.raw {| css(tw` bg-purple-dark `)|}]
        }
    | _ => [%bs.raw {| css(tw` bg-black `)|}]
    }
  }
  

let cardSmallLayoutCost = [%bs.raw {| css(tw`
  w-1/10
  flex
  justify-center
  items-center
`)|}];

let cardSmallLayoutImage = [%bs.raw {| css(tw`
  w-1/10
`)|}];

let cardSmallLayoutImageImg = [%bs.raw {| css(tw`
  max-w-full
`)|}];

let cardSmallLayoutName = [%bs.raw {| css(tw`
  w-7/10
  flex
  items-center
  pl-1
  border-teal
  border-solid
  border-0
  border-r
  whitespace-no-wrap
  overflow-x-hidden
`)|}];

let cardSmallLayoutCount = [%bs.raw {| css(tw`
  w-1/10
  flex
  justify-center
  items-center
`)|}];
  

[@react.component]
let make = (~normalized, ~id: Card.Model.idType, ~onClick=?) => {
  let optionCard = MyNormalizr.Converter.Card.Remote.getRecord(normalized, id);

  switch(optionCard) {
  | None => <div/>
  | Some(card) =>
      <div
        className=cx(cardSmallLayout, cardSmallLayoutColor(card.data.colors))
        onClick={
          switch(onClick){
          | None => ((e) => {()})
          | Some(onClick) => onClick
          }
        }
      >
        <div className=cardSmallLayoutCost>{ReasonReact.string(string_of_int(card.data.cost))}</div>
        <div className=cardSmallLayoutImage>
          <img className=cardSmallLayoutImageImg src=card.data.thumbnailUrl alt=card.data.name />
        </div>
        <div className=cardSmallLayoutName>
          {ReasonReact.string(card.data.name)}
        </div>
        <div className=cardSmallLayoutCount>{ReasonReact.string("1")}</div>
      </div>
  }
};