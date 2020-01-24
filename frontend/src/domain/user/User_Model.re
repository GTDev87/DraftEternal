// module M = ModelUtils.BuildModel(User_Record, Schema.User, User_Fragment);

module M = {
  module ModelSchemaType = Schema.User;
  module InternalSchema = ModelSchemaType.Root;
  module ModelRecord = User_Record;
  module Fragment = User_Fragment;

  type rootIdType = Domain.RootModel.id;

  /* ModelSchemaType */
  type idType = ModelSchemaType.id;
  let idToRootId = ModelSchemaType.idToRootId;
  let getUUIDFromId = (id: idType): UUID.t => ModelSchemaType.idToString(id);
  let idToTypedId = (id: UUID.t): idType => ModelSchemaType.stringToId(id);

  /* ModelRecord */
  type _data = ModelRecord._data;
  type _local = ModelRecord.Local.Record.t;
  let _defaultData = ModelRecord._defaultData;
  let _defaultRecordId = ModelRecord._defaultRecordId;
  let _defaultRecord = ModelRecord._defaultRecord;

  type _record = RecordType.Type.t(_data, _local);

  /* Fragment */
  let fragmentType = Fragment.fragmentType;
  let fragmentName = Fragment.Fields.name;
  let objectToId = (obj: Fragment.Fields.t): idType => idToTypedId(obj##id);

  /* Record */
  module Record = {
    type t = _record;
    type defaultParam = ModelRecord.defaultParam;
    type defaultFn = (ModelRecord.defaultParam, idType) => t;
    let findId = ModelRecord.findId;

    module Data = {
      type t = _data;

      let fromObject = Fragment.fromObject;
    };
    let default = _defaultRecord;
    let defaultWithId = (param: defaultParam, id) =>
      ModelRecord._defaultWithId(param, id |> getUUIDFromId);

    let fromObject = (obj: Fragment.Fields.t): t => {
      data: Data.fromObject(obj),
      local: ModelRecord.Local.Record.default(obj##id),
    };
  };
};