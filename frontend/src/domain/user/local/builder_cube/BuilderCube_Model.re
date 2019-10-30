type _record = Cube.Model.Record.t;

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  let newCubeId = Schema.Cube.stringToId(Rand.generateSeqUUID());
  Cube.Model.Record.defaultWithId((), newCubeId);
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};