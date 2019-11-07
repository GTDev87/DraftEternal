module M = [%graphql
  {|
    query member {
      member {
        ...User_Model.Fragment.Fields
      }
    }
  |}
];