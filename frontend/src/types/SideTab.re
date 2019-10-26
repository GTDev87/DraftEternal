type t =
  | Library
  | Builder
;

type action =
  | ToLibrary
  | ToBuilder;

let all = [
  Library,
  Builder,
];

let toString = (sideTabType : t) : string =>
  switch(sideTabType){
  | Library => "Cube Library"
  | Builder => "Cube Builder"
  };

let toIcon = (sideTabType : t) =>
  switch(sideTabType){
  | Library => <CubeIcon />
  | Builder => <CubeIcon />
  };

let toAction = (sideTabType : t): action =>
  switch(sideTabType){
  | Library => ToLibrary
  | Builder => ToBuilder
  };

let tabReducer = (): (t, (action) => unit) =>
  React.useReducer(
    (_, action) =>
      switch (action) {
      | ToLibrary => Library
      | ToBuilder => Builder
      },
      Library,
  );

let toSidebarImageName = (sideTabType : t) =>
  <SidebarImageName icon={toIcon(sideTabType)} text=toString(sideTabType) />