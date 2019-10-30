module Record = Cube_Record;

module GraphFragment = [%graphql
  {|
    fragment cubeFields on Cube {
      id
      name
      description
      display
      cardIds
      creatorId
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.CubeFields;

let fragmentType = "Cube";

let fromObject = (obj: Fields.t): Record._data => {
  id: obj##id,
  name: obj##name,
  description: obj##description,
  display: obj##display,
  cardIds: obj##cardIds |> Belt.List.fromArray |> Belt.List.map(_, Schema.Card.stringToId),
  creatorId: Schema.User.stringToId(obj##creatorId),
};