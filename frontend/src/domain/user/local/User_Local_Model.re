type _record = {
  builderCube: Cube.Model.Record.t,
  tab: SideTab.t,
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  {
    builderCube: Cube.Model.Record.defaultWithId((), newCubeId),
    tab: Library,
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};