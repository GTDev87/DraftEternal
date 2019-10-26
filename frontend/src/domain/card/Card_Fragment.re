module Record = Card_Record;

module GraphFragment = [%graphql
  {|
    fragment cardFields on Card {
      id
      name
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.CardFields;

let fragmentType = "Card";

let fromObject = (obj: Fields.t): Record._data => {
  id: obj##id,
};