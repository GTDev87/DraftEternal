type _record = {
  newCubeId: Schema.Cube.id,
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);

  {
    newCubeId: Schema.Cube.stringToId(Rand.generateSeqUUID()),
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};