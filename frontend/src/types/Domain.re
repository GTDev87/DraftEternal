module type CONTAINER_INTERFACE = {
  module Fragment: ApolloClient.ReadFragment;
};

module type LOCAL_RECORD = {
  type _record;
  
  let _defaultRecord: (UUID.t) => _record;
  
  module Record: {
    type t = _record;
    let default: (UUID.t) => _record;
  };
};

module type ROOT_MODEL = {
  type t = ..;
  type id = ..;
  type record = ..;
  type data;

  type t += EMPTY_T;
  type id += EMPTY_ID;
  type record += EMPTY_RECORD;
};

module RootModel : ROOT_MODEL = {
  type t = ..;
  type id = ..;
  type record = ..;
  type data;

  /* This is here until https://github.com/facebook/reason/issues/1597 */
  /* https://github.com/ocaml/ocaml/pull/1546 */
  type t += EMPTY_T;
  type id += EMPTY_ID;
  type record += EMPTY_RECORD;
};

module SchemaType = {
  type t = Type;
};

module type RECORD = {
  module Local: LOCAL_RECORD;

  type _data;
  type _record = RecordType.Type.t(_data, Local.Record.t);

  type defaultParam;
  
  let _defaultData: (UUID.t) => _data;
  let _defaultRecordId: (UUID.t) => _record;
  let _defaultRecord: unit => _record;
  let findId: (_record) => UUID.t;

  let _defaultWithId: (defaultParam, UUID.t) => _record;
};

type typeWithId = {. "id": string};

module type SCHEMA_TYPE = {

  module Root: ROOT_MODEL;

  /* module CreatedType: SchemaType; */

  type RootModel.id += Id(UUID.t);

  type id;
  type _t =  SchemaType.t;

  let idToString: (id) => UUID.t
  let idToRootId: (id) => RootModel.id;
  let stringToId: (UUID.t) => id;
};

module type MODEL = {
  module ModelSchemaType : SCHEMA_TYPE;
  module InternalSchema : ROOT_MODEL;

  type _local;

  // module InternalSchema : ROOT_MODEL;
  module ModelRecord : RECORD;
  type _data = ModelRecord._data;
  type _record = ModelRecord._record;

  type idType = ModelSchemaType.id;
  type rootIdType = RootModel.id;

  let idToRootId: (ModelSchemaType.id) => RootModel.id;
  let getUUIDFromId: (ModelSchemaType.id) => UUID.t;
  let idToTypedId: (UUID.t) => idType;

  module rec Fragment: {
    module Fields: ReasonApolloTypes.Config;
    let toId: Fields.t => UUID.t;
  }
  and Record: {
    type t = _record;
    type defaultParam;
    type defaultFn = (defaultParam, ModelSchemaType.id) => t;
    let findId: (ModelRecord._record) => UUID.t;
    let default: unit => ModelRecord._record;

    // module Local: LOCAL_RECORD;

    module Data: {
      type t = _data;
      let fromObject: Fragment.Fields.t => t;
    };
    let fromObject: Fragment.Fields.t => t;
    let defaultWithId: defaultFn;
  };

  let objectToId: (Fragment.Fields.t) => idType;

  let fragmentType: string;
  let fragmentName: string;
  let _defaultData: (UUID.t) => _data;
};

module type DOMAIN_WRAPPER = {
  type model;
  type rootRecord = RootModel.record;
  let wrap: model => rootRecord;
  let unwrap: rootRecord => option(model);
  let apolloEnabled: bool;
};

module type MODEL_RECORD {
  module Model: MODEL;
  module Wrapper: DOMAIN_WRAPPER;

  type model;
  type _data;
  type _record;
  type _record += Record(Model.Record.t);

  // type _t = ROOT_MODEL.t;
  // type _id = ROOT_MODEL.id;
  
  type RootModel.t += Schema;
  type RootModel.id += Id(UUID.t);
  type RootModel.record += Record(Model.Record.t);

  // type _t += Schema = ROOT_MODEL.Schema;
  // type _id += Id = ROOT_MODEL.Id;
};

module type FRAGMENT = {
  type data;

  module Fields: {
    type t;
    let name: string;
    let query: string;
    let parse: (Js.Json.t) => t;
  };
  
  let fragmentType: string;
  
  let fromObject: (Fields.t) => data;
  let toId: (Fields.t) => UUID.t;
};

module type CONTAINER {
  type idType;
  type config;
  type record;

  let getById: idType => option(config);
  let getRecordById: idType => option(record);

  [@bs.obj] external makeProps:
      (~id: 'id, ~children: 'children, ~key: string=?, unit) => {. "children": 'children, "id": 'id} = "";

  let make: ({ . "children": (record => React.element), "id": string}) => React.element;
};

module type ACTION = {
  type action;
  type model;
  let reduce: (action, Js.Promise.t(model)) => Js.Promise.t(model);
};

module type M = {
  module rec Model: MODEL
  and Action: (
    ACTION
      with type model = Model.Record.t
  )
  and Container: (
    CONTAINER 
      with type idType = Model.idType
      and type record = Model.Record.t
      and type config = Model.Fragment.Fields.t
  )
  and Record: (
    MODEL_RECORD
      with type Wrapper.model = Action.model
  )
};
