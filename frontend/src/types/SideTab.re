type t =
  | Library
  | CreateCube
  | SearchCard
  | MyCube(Schema.Cube.id);

type action =
  | ToLibrary
  | ToCreateCube
  | ToSearchCard
  | ToMyCube(Schema.Cube.id);

let all = (myCubeIds) => ([
  SearchCard,
  Library,
  CreateCube,
] @ Belt.List.map(myCubeIds, (c: Schema.Cube.id) => MyCube(c)));

let toIcon = (sideTabType : t) =>
  switch(sideTabType){
  | Library => <CubeIcon />
  | CreateCube => <CubeIcon />
  | SearchCard => <CubeIcon />
  | MyCube(_) => <CubeIcon />
  };

let toAction = (sideTabType : t): action =>
  switch(sideTabType){
  | Library => ToLibrary
  | CreateCube => ToCreateCube
  | SearchCard => ToSearchCard
  | MyCube(id) => ToMyCube(id)
  };

let tabReducer = (): (t, (action) => unit) =>
  React.useReducer(
    (_, action) =>
      switch (action) {
      | ToLibrary => Library
      | ToCreateCube => CreateCube
      | ToSearchCard => SearchCard
      | ToMyCube(id) => MyCube(id)
      },
      Library,
  );

