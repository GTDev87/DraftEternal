module M = [%graphql
  {|
    query general {
      cards {
        ...Card_Model.Fragment.Fields
      }
    }
  |}
];