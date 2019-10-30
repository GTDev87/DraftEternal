type action =
  | ChangeTab(SideTab.t)
  | CopyBuilderCube(Cube.Model.Record.t)
  | ResetBuilderCube
  | UpdateBuilderCube(BuilderCube.Action.action);

type model = User_Local_Model.Record.t;

let reduce = (action, local: model) =>
  switch (action) {
  | ChangeTab(tab) => {...local, tab}
  | CopyBuilderCube(cube) => {...local, builderCube: cube}
  | ResetBuilderCube => {...local, builderCube: Cube.Model.Record.default()}
  | UpdateBuilderCube(a) => {...local, builderCube: BuilderCube.Action.reduce(a, local.builderCube)}
};