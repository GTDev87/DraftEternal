let css = Css.css;
let cx = Css.cx;
let tw = Css.tw;

let cardFullLayout = [%bs.raw {| css(tw`
  w-full
`)|}];

let cardFullLayoutImage = [%bs.raw {| css(tw`
  max-w-full
`)|}];

[@react.component]
let make = (~normalized, ~id: Card.Model.idType, ~onClick=?) => {
  let optionCard = MyNormalizr.Converter.Card.Remote.getRecord(normalized, id);

  switch(optionCard) {
  | None => <div/>
  | Some(card) =>
      <div
        className=cardFullLayout
        onClick={
          switch(onClick){
          | None => ((e) => {()})
          | Some(onClick) => onClick
          }
        }
      >
        <img className=cardFullLayoutImage src={card.data.imageUrl} alt=card.data.name />
      </div>
  }
};