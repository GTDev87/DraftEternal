module Record = Cube_Record;

module GraphFragment = [%graphql
  {|
    fragment cubeFields on Cube {
      id
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.CubeFields;

let fragmentType = "Cube";

let fromObject = (obj: Fields.t): Record._data => {
  id: obj##id,
};