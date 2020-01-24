type _record = Cube_Model.M.Record.t;

let _defaultRecord = id => {
  module UUID_SEED_TYPE = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUID_SEED_TYPE);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  Cube_Model.M.Record.defaultWithId((), newCubeId);
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};