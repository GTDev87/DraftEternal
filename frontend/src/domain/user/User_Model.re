module ModelSchema = Schema.User;
type idType = ModelSchema.id;
type rootIdType = ModelUtils.RootModel.id;
let idToRootId = ModelSchema.idToRootId;
let getUUIDFromId = (id: idType): UUID.t => ModelSchema.idToString(id);
let idToRootId = ModelSchema.idToRootId;
let idToTypedId = (id: UUID.t): idType => ModelSchema.stringToId(id);

/* */
module ModelRecord = User_Record;
type _data = ModelRecord._data;
type _local = ModelRecord._local;
type _record = RecordType.t(_data, _local);
let _defaultData = ModelRecord._defaultData;
let _defaultRecordId = ModelRecord._defaultRecordId;
let _defaultRecord = ModelRecord._defaultRecord;

/* */
module Fragment = User_Fragment;
let fragmentType = Fragment.fragmentType;
let fragmentName = Fragment.Fields.name;
let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

module Record = {
  type t = _record;
  type defaultParam = unit;
  type defaultFn = (defaultParam, idType) => t;
  let findId = ModelRecord.findId;
  module Data = {
    type t = _data;

    let fromObject = Fragment.fromObject;
  };
  let default = _defaultRecord;
  let defaultWithId = ((), id) => _defaultRecordId(id |> getUUIDFromId);

  let fromObject = (obj: Fragment.Fields.t): t => {
    data: Data.fromObject(obj),
    local: User_Local.Model.Record.default(obj##id),
  };
};
