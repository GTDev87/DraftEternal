module Record = User_Record;

module GraphFragment = [%graphql
  {|
    fragment userFields on User {
      id
      email
      cubes {
        ...Cube_Model.Fragment.Fields
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.UserFields;

let fragmentType = "User";

let fromObject = (obj: Fields.t): Record._data => {
  id: obj##id,
  email: obj##email,
  guest: false,
  cubeIds:
    obj##cubes
    |> Belt.List.fromArray
    |> Belt.List.map(_, Cube_Model.objectToId),
};