module M = [%graphql
  {|
    query member {
      member {
        ...User.Model.Fragment.Fields
      }
    }
  |}
];