type action =
  | ChangeTab(SideTab.t)
  | OpenModal(DashModal.t)
  | CloseModal
  | CopyBuilderCube(Cube_Model.Record.t)
  | ResetBuilderCube
  | UpdateBuilderCube(BuilderCube.Action.action);

type model = User_Local_Model.Record.t;

let reduce = (action, local: model) =>
  switch (action) {
  | ChangeTab(tab) => {...local, tab}
  | OpenModal(modal) => {...local, modal: Some(modal)}
  | CloseModal => {...local, modal: None}
  | CopyBuilderCube(cube) => {...local, builderCube: cube}
  | ResetBuilderCube => {...local, builderCube: Cube_Model.Record.default()}
  | UpdateBuilderCube(a) => {...local, builderCube: BuilderCube.Action.reduce(a, local.builderCube)}
};