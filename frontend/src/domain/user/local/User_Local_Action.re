type action =
  | ChangeTab(SideTab.t)
  | OpenModal(DashModal.t)
  | CloseModal
  | CopyBuilderCube(Cube_Model.M.Record.t)
  | ResetBuilderCube
  | UpdateBuilderCube(BuilderCube.Action.action);

type model = User_Local_Model.Record.t;

let reduce = (action, local: model) =>
  switch (action) {
  | ChangeTab(tab) => {...local, tab}
  | OpenModal(modal) => {...local, modal: Some(modal)}
  | CloseModal => {...local, modal: None}
  | CopyBuilderCube(cube) => {...local, builderCube: cube, update: true}
  | ResetBuilderCube => {...local, builderCube: Cube_Model.M.Record.default(), update: false}
  | UpdateBuilderCube(a) => {...local, builderCube: BuilderCube.Action.reduce(a, local.builderCube)}
};