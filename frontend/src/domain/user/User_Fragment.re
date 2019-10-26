module Record = User_Record;

module GraphFragment = [%graphql
  {|
    fragment userFields on User {
      id
      email
    }
  |}
];

include GraphFragment;
module Fields = GraphFragment.UserFields;

let fragmentType = "User";

let fromObject = (obj: Fields.t): Record._data => {
  id: obj##id,
  email: obj##email,
};