let objNullableToRecordOptional = (obj, convertToRecord) =>
  switch (Js.Null_undefined.toOption(obj)) {
  | None => None
  | Some(obj) => Some(obj |> convertToRecord)
  };

let recordOptionalToObjNullable = (record, convertToObj) =>
  switch (record) {
  | None => Js.Nullable.null
  | Some(record) => record |> convertToObj |> Js.Nullable.return
  };

let getConnectionList = (items, idFunction) =>
  items##edges
  |> Belt.List.fromArray
  |> Belt.List.map(_, (edge) => Belt.Option.map(edge, (e) => idFunction(e##node)));

module GenerateModel = (Root: Domain.ROOT_MODEL, ()): (
  Domain.SCHEMA_TYPE
    with module Root = Root
) => {
  module Root = Root;
  type _t = Domain.SchemaType.t;
/* LOOK HERE */
  type Root.t += Schema;
  type Root.t += Schema = Schema;

  type Domain.RootModel.id += Id(UUID.t);
  type Domain.RootModel.id += Id = Id;

  type t = Root.t;
  type id = (Domain.RootModel.id, _t);

  let idToString = (id: id) : UUID.t => {
    switch(id){
    | (Id(uuid), _) => uuid
    | _ => ""
    };
  };

  let idToRootId = (id: id) : Domain.RootModel.id =>
    switch(id){
    | (Id(uuid), _t) => Id(uuid)
    };

  let rootIdToId = (id: Domain.RootModel.id) : id =>
    switch(id){
    | id => (id, Type);
    };

  let stringToId = (uuid: UUID.t): id => (Id(uuid), Type);
};

module AddModel = (
  Schema : Domain.SCHEMA_TYPE,
  ModelType : Domain.MODEL
) :
  (Domain.MODEL_RECORD
    with module Model = ModelType
    and type _data = Domain.RootModel.data
    and type _record = Domain.RootModel.record
    and type model = ModelType.Record.t
    and type Wrapper.model = ModelType.Record.t
    and type Wrapper.rootRecord = Domain.RootModel.record
    and type Model.Record.t = ModelType.Record.t
  ) => {
  module Model = ModelType;

  let _defaultData = Model._defaultData;

  type model = Model.Record.t;
  type Domain.RootModel.record += Record(model);
  type Domain.RootModel.t += Schema;
  type Domain.RootModel.id += Id(UUID.t);

  type _data = Domain.RootModel.data;

  type _record = Domain.RootModel.record;
  type _t = Domain.RootModel.t;
  type _id = Domain.RootModel.id;

  type record = (_record, Domain.SchemaType.t);

  module Wrapper = {
    type rootRecord = _record;
    type model = Model.Record.t;
    let wrapNonRoot = (model: model) : record => (Record(model), Type);
    let unwrapNonRoot = (record: record): option(model) =>
      switch (record) {
      | (Record(model), _) => Some(model)
      | _ => None
      };

    let wrap = (model: model) : _record => Record(model);
    let unwrap = (record: _record): option(model) =>
      switch (record) {
      | Record(model) => Some(model)
      | _ => None
      };
    let apolloEnabled = true;
  }
};

module type NORMALIZR_GENERATOR_TYPE {
  type id;
  type t;
  type record;
  type normalizedType;
  let modelIdToIdFunction: (id) => (t, UUID.t);

  let modelTypeToRecordType: (record) => (t, UUID.t);

  let normalizerCommitItemToSchema: (normalizedType, record) => normalizedType;
};

module AddRecord(
  Record : Domain.MODEL_RECORD,
  NormalizrGenerator: NORMALIZR_GENERATOR_TYPE
    with type id = Domain.RootModel.id
    and type t = Domain.RootModel.t
    and type record = Domain.RootModel.record
  ,
) : (
  NORMALIZR_GENERATOR_TYPE
    with type id = Domain.RootModel.id
    and type t = Domain.RootModel.t
    and type record = Domain.RootModel.record
    and type normalizedType = NormalizrNew.normalizedSchema(Domain.RootModel.t, UUID.t, Domain.RootModel.record)
) {

  type id = Domain.RootModel.id;
  type t = Domain.RootModel.t;
  type record = Domain.RootModel.record;

  type Domain.RootModel.id += Id(UUID.t);
  type Domain.RootModel.t += Schema;
  type Domain.RootModel.record += Record(Record.Model.Record.t);

  type normalizedType = NormalizrNew.normalizedSchema(t, UUID.t, record);

  let modelIdToIdFunction = (id: id): (t, UUID.t) => {
    switch(id){
    | Id(uuid) => (Schema, uuid)
    | _ => NormalizrGenerator.modelIdToIdFunction(id)
    };
  };
  
  let modelTypeToRecordType = (record: record): (t, UUID.t) => {
    switch(record){
    | Record(model) => (
      Schema,
      Record.Model.Record.findId(model)
    )
    | _ => NormalizrGenerator.modelTypeToRecordType(record)
    };
  };

  let normalizerCommitItemToSchema:
    (normalizedType, record) => normalizedType =
      NormalizrNew.Normalizr.commitItemToSchema(modelTypeToRecordType);
};

module EmptyNormalizr(
  Root: Domain.ROOT_MODEL
    with type id = Domain.RootModel.id
    and type t = Domain.RootModel.t
    and type record = Domain.RootModel.record
) : (
  NORMALIZR_GENERATOR_TYPE
    with type id = Domain.RootModel.id
    and type t = Domain.RootModel.t
    and type record = Domain.RootModel.record
    and type normalizedType = NormalizrNew.normalizedSchema(Root.t, UUID.t, Root.record)
) = {
  module Implementation = {
    type id = Domain.RootModel.id;
    type t = Domain.RootModel.t;
    type record = Domain.RootModel.record;
    type normalizedType = NormalizrNew.normalizedSchema(t, UUID.t, record);

    let modelIdToIdFunction = (id: id): (t, UUID.t) => {
      switch(id){
      | Root.EMPTY_ID => (Root.EMPTY_T, "")
      | _ => (Root.EMPTY_T, "")
      };
    };

    let modelTypeToRecordType = (record: record): (t, UUID.t) => {
      switch(record){
      | Root.EMPTY_RECORD => (Root.EMPTY_T, "")
      | _ => (Root.EMPTY_T, "")
      };
    };

    let normalizerCommitItemToSchema:
      (normalizedType, Root.record) => normalizedType =
        NormalizrNew.Normalizr.commitItemToSchema(modelTypeToRecordType);
  };
  
  include Implementation;

  module AddRecord = (
    Domain : Domain.MODEL_RECORD
      with type Model.InternalSchema.t = Domain.RootModel.t
      and type Model.InternalSchema.id = Domain.RootModel.id
      and type _record = Domain.RootModel.record
  ) => AddRecord(
    Domain,
    Implementation
  );
};

module CreateFakeLocal() : (
  Domain.LOCAL_RECORD
    with type _record = unit
) {

  type _record = unit;
  
  let _defaultRecord = (id: UUID.t) => ();
  
  module Record = {
    type t = unit;
    let default = (id: UUID.t) => ();
  };
}

module BuildModel(
  ModelRecord : Domain.RECORD,
  ModelSchemaType : Domain.SCHEMA_TYPE,
  Fragment : Domain.FRAGMENT
    with type data = ModelRecord._data
): (
  Domain.MODEL
    with module ModelRecord = ModelRecord
    and module ModelSchemaType = ModelSchemaType
    and module InternalSchema = ModelSchemaType.Root
    and module Fragment = Fragment
    and type _data = ModelRecord._data
    and type idType = ModelSchemaType.id
    and type rootIdType = Domain.RootModel.id
    and type _record = ModelRecord._record
    and type _local = ModelRecord.Local.Record.t
    and type Record.defaultParam = ModelRecord.defaultParam
) {
  
  module ModelSchemaType = ModelSchemaType;
  module InternalSchema = ModelSchemaType.Root;
  module Fragment = Fragment;
  module ModelRecord = ModelRecord;

  type _record = ModelRecord._record;

  type rootIdType = Domain.RootModel.id;
  
  type idType = ModelSchemaType.id;
  let idToRootId = ModelSchemaType.idToRootId;
  let getUUIDFromId = (id: idType): UUID.t => ModelSchemaType.idToString(id);
  let idToTypedId = (id: UUID.t): idType => ModelSchemaType.stringToId(id);

  type _data = ModelRecord._data;
  type _local = ModelRecord.Local.Record.t;
  let _defaultData = ModelRecord._defaultData;
  let _defaultRecordId = ModelRecord._defaultRecordId;
  let _defaultRecord = ModelRecord._defaultRecord;

  let fragmentType = Fragment.fragmentType;
  let fragmentName = Fragment.Fields.name;
  let objectToId = (obj: Fragment.Fields.t): idType => Fragment.toId(obj) |> idToTypedId;

  module Record = {
    type t = _record;
    type defaultParam = ModelRecord.defaultParam;
    type defaultFn = (ModelRecord.defaultParam, idType) => t;
    let findId = ModelRecord.findId;

    module Local = ModelRecord.Local;

    module Data = {
      type t = _data;

      let fromObject = Fragment.fromObject;
    };
    let default = _defaultRecord;
    let defaultWithId = (param: defaultParam, id) =>
      ModelRecord._defaultWithId(param, id |> getUUIDFromId);

    let fromObject = (obj: Fragment.Fields.t): t => {
      data: Fragment.fromObject(obj),
      local: ModelRecord.Local.Record.default(Fragment.toId(obj))
    };
  };
};
