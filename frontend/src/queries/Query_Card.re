module M = [%graphql
  {|
    query general {
      cards {
        ...Card.Model.Fragment.Fields
      }
    }
  |}
];