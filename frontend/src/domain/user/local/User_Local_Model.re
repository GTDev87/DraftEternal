type _record = {
  update: bool,
  builderCube: Cube_Model.M.Record.t,
  tab: SideTab.t,
  modal: option(DashModal.t),
};

let _defaultRecord = id => {
  module UUID_SEED_TYPE = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUID_SEED_TYPE);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  let cube = Cube_Model.M.Record.defaultWithId((), newCubeId);
  let newCube = {...cube, data: {...cube.data, name: "New Cube"}};

  {
    update: false,
    builderCube: newCube,
    tab: SearchCard,
    modal: None
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};