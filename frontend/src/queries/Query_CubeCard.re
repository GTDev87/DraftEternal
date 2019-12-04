module M = [%graphql
  {|
    query general {
      cards {
        ...Card_Model.M.Fragment.Fields
      }
      cubes {
        ...Cube_Model.M.Fragment.Fields
      }
    }
  |}
];