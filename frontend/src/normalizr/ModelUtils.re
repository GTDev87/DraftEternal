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

module type RootModelType = {
  type t = ..;
  type id = ..;
  type record = ..;

  type t += EMPTY_T;
  type id += EMPTY_ID;
  type record += EMPTY_RECORD;
};

module RootModel : RootModelType = {
  type t = ..;
  type id = ..;
  type record = ..;

  /* This is here until https://github.com/facebook/reason/issues/1597 */
  /* https://github.com/ocaml/ocaml/pull/1546 */
  type t += EMPTY_T;
  type id += EMPTY_ID;
  type record += EMPTY_RECORD;
};

module type SchemaType = {
  type t = Type;
};

module GenerateType = () => {
  type t = Type;
};

module GenerateModel = (Root: RootModelType, ()) => {
  module CreatedType = GenerateType();
  type _t = CreatedType.t;

  type Root.id += Id(UUID.t);
  type _id = Root.id;

  type Root.t += Schema;
  type t = Root.t;
  type id = (_id, _t);

  let idToString = (id: id) : UUID.t => {
    switch(id){
    | (Id(uuid), _) => uuid
    | _ => ""
    };
  };

  let idToRootId = (id: id) : _id =>
    switch(id){
    | (Id(uuid), _t) => Id(uuid)
    };

  let rootIdToId = (id: _id) : id =>
    switch(id){
    | id => (id, Type);
    };

  let stringToId = (uuid: UUID.t): id => (Id(uuid), Type);

  module AddModel = (ModelType : Domain.Model) :
    (Domain.ModelRecordType
      with module Model = ModelType
      and type _record = Root.record
      and type model = ModelType.Record.t
      and type Wrapper.model = ModelType.Record.t
      and type Wrapper.rootRecord = Root.record
      and type Model.Record.t = ModelType.Record.t) =>
  {
    module Model = ModelType;

    type model = Model.Record.t;
    type Root.record += Record(model);
    type _record = Root.record;
    type record = (_record, _t);

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
  }
};

module type NormalizrGeneratorType {
  type id;
  type t;
  type record;
  type normalizedType;
  let modelIdToIdFunction: (id) => (t, UUID.t);

  let modelTypeToRecordType: (record) => (t, UUID.t);

  let normalizerCommitItemToSchema: (normalizedType, RootModel.record) => normalizedType;

};

module AddRecord(
  NormalizrGenerator: NormalizrGeneratorType
    with type id = RootModel.id
    and type t = RootModel.t
    and type record = RootModel.record,
  Record : Domain.ModelRecordType
    with type Model.ModelSchema.t = RootModel.t
    and type Model.ModelSchema._id = RootModel.id
    and type _record = RootModel.record
) : (
  NormalizrGeneratorType
    with type id = Record.Model.ModelSchema._id
    and type t = Record.Model.ModelSchema.t
    and type record = Record._record
    and type normalizedType = NormalizrNew.normalizedSchema(RootModel.t, UUID.t, RootModel.record)
) {
  type id = Record.Model.ModelSchema._id;
  type t = Record.Model.ModelSchema.t;
  type record = Record._record;

  type normalizedType = NormalizrNew.normalizedSchema(RootModel.t, UUID.t, RootModel.record);

  let modelIdToIdFunction = (id: id): (t, UUID.t) => {
    switch(id){
    | Record.Model.ModelSchema.Id(uuid) => (Record.Model.ModelSchema.Schema, uuid)
    | _ => NormalizrGenerator.modelIdToIdFunction(id)
    };
  };
  
  let modelTypeToRecordType = (record: RootModel.record): (RootModel.t, UUID.t) => {
    switch(record){
    | Record.Record(model) => (Record.Model.ModelSchema.Schema, Record.Model.Record.findId(model))
    | _ => NormalizrGenerator.modelTypeToRecordType(record)
    };
  };

  let normalizerCommitItemToSchema:
    (normalizedType, RootModel.record) => normalizedType =
      NormalizrNew.Normalizr.commitItemToSchema(modelTypeToRecordType);
};

module EmptyNormalizr(
  Root: RootModelType
    with type id = RootModel.id
    and type t = RootModel.t
    and type record = RootModel.record
) : (
  NormalizrGeneratorType
    with type id = Root.id
    and type t = Root.t
    and type record = Root.record
    and type normalizedType = NormalizrNew.normalizedSchema(Root.t, UUID.t, Root.record)
) = {
  module Implementation = {
    type id = Root.id;
    type t = Root.t;
    type record = Root.record;
    type normalizedType = NormalizrNew.normalizedSchema(Root.t, UUID.t, Root.record);

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
  }
  
  include Implementation;

  module AddRecord = (
    Domain : Domain.ModelRecordType
      with type Model.ModelSchema.t = RootModel.t
      and type Model.ModelSchema._id = RootModel.id
      and type _record = RootModel.record
  ) => AddRecord(Implementation, Domain);
};