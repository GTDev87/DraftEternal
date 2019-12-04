type _record = Cube_Model.M.Record.t;

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  Cube_Model.M.Record.defaultWithId((), newCubeId);
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};