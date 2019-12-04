type data = User_Record._data;

module GraphFragment = [%graphql
  {|
    fragment userFields on User {
      id
      email
      cubes {
        ...Cube_Model.M.Fragment.Fields
      }
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.UserFields;

let fragmentType = "User";

let fromObject = (obj: Fields.t): data => {
  {
    id: obj##id,
    email: obj##email,
    guest: false,
    cubeIds:
      obj##cubes
      |> Belt.List.fromArray
      |> Belt.List.map(_, Cube_Model.M.objectToId),
  };
}