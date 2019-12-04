module M = [%graphql
  {|
    query member {
      member {
        ...User_Model.M.Fragment.Fields
      }
    }
  |}
];