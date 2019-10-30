type t =
  | Library
  | CreateCube
  | MyCube(Schema.Cube.id);

type action =
  | ToLibrary
  | ToCreateCube
  | ToMyCube(Schema.Cube.id);

let all = (myCubeIds) => ([
  Library,
  CreateCube,
] @ Belt.List.map(myCubeIds, (c: Schema.Cube.id) => MyCube(c)));

let toIcon = (sideTabType : t) =>
  switch(sideTabType){
  | Library => <CubeIcon />
  | CreateCube => <CubeIcon />
  | MyCube(_) => <CubeIcon />
  };

let toAction = (sideTabType : t): action =>
  switch(sideTabType){
  | Library => ToLibrary
  | CreateCube => ToCreateCube
  | MyCube(id) => ToMyCube(id)
  };

let tabReducer = (): (t, (action) => unit) =>
  React.useReducer(
    (_, action) =>
      switch (action) {
      | ToLibrary => Library
      | ToCreateCube => CreateCube
      | ToMyCube(id) => MyCube(id)
      },
      Library,
  );

