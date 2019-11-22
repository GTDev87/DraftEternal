module M = [%graphql
  {|
    query general {
      cards {
        ...Card_Model.Fragment.Fields
      }
      cubes {
        ...Cube_Model.Fragment.Fields
      }
    }
  |}
];