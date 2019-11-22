type _record = {
  update: bool,
  selectedCube: option(Cube_Model.idType),
  builderCube: Cube_Model.Record.t,
  tab: SideTab.t,
  modal: option(DashModal.t),
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  let cube = Cube_Model.Record.defaultWithId((), newCubeId);
  let newCube = {...cube, data: {...cube.data, name: "New Cube"}};

  {
    update: false,
    selectedCube: None,
    builderCube: newCube,
    tab: SearchCard,
    modal: None
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};