type t =
  | Library
  | CreateCube
  | SearchCard
  | CubeManager
  | Cube(Cube_Model.idType)
  | CubeEdit(Cube_Model.idType)
;

type action =
  | ToLibrary
  | ToCreateCube
  | ToSearchCard
  | ToCubeManager
  | ToCube(Cube_Model.idType)
  | ToCubeEdit(Cube_Model.idType)
;

let all = (guest) => ([
  SearchCard,
  Library,
  CreateCube,
] @ (guest ? [] : [CubeManager]));

let toIcon = (sideTabType : t) =>
  switch(sideTabType){
  | Library => <CubeIcon />
  | CreateCube => <CubeIcon />
  | SearchCard => <CubeIcon />
  | CubeManager => <CubeIcon />
  | Cube(id) => <div />
  | CubeEdit(id) => <div />
  };

let toAction = (sideTabType : t): action =>
  switch(sideTabType){
  | Library => ToLibrary
  | CreateCube => ToCreateCube
  | SearchCard => ToSearchCard
  | CubeManager => ToCubeManager
  | Cube(id) => ToCube(id)
  | CubeEdit(id) => ToCubeEdit(id)
  };

let tabReducer = (): (t, (action) => unit) =>
  React.useReducer(
    (_, action) =>
      switch (action) {
      | ToLibrary => Library
      | ToCreateCube => CreateCube
      | ToSearchCard => SearchCard
      | ToCubeManager => CubeManager
      | ToCube(id) => Cube(id)
      | ToCubeEdit(id) => CubeEdit(id)
      },
      Library,
  );

