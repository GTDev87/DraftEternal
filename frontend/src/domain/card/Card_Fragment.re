type data = Card_Record._data;

module GraphFragment = [%graphql
  {|
    fragment cardFields on Card {
      id
      name
      imageUrl
      thumbnailUrl
      
      attack
      cardText
      cardType
      cost
      deckBuildable
      detailsUrl
      health
      rarity
      setNumber
      influence
      colors
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.CardFields;

let fragmentType = "Card";

let fromObject = (obj: Fields.t): data => {
  id: obj##id,
  name: obj##name,
  imageUrl: obj##imageUrl,
  thumbnailUrl: obj##thumbnailUrl,
  cardText: obj##cardText,
  cost: obj##cost,
  colors: obj##colors |> Belt.List.fromArray,
  influence: obj##influence |> Belt.List.fromArray,
};