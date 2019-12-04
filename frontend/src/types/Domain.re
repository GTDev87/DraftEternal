module type ContainerInterface = {
  module Fragment: ApolloClient.ReadFragment;
};

module type Model = {
  type _data;
  type _local;

  type _record = RecordType.Type.t(_data, _local);
  type idType;
  type rootIdType;
  let idToRootId: (idType) => rootIdType;
  let getUUIDFromId: (idType) => UUID.t;

  module ModelSchema:  {
    type _id;
    type _id += Id(UUID.t);

    type t;
    type t += Schema;
  };

  module rec Fragment: {
    module Fields: ReasonApolloTypes.Config;
  }
  and Record: {
    type t = _record;
    type defaultParam;
    type defaultFn = (defaultParam, idType) => t;
    let findId: (_record) => UUID.t;

    module Data: {
      type t = _data;
      let fromObject: Fragment.Fields.t => t;
    };
    let fromObject: Fragment.Fields.t => t;
    let defaultWithId: defaultFn;
  };

  let fragmentType: string;
  let fragmentName: string;
  let _defaultData: (UUID.t) => _data;
};

module type Record = {
  type _data;
  type _record;
  
  let _defaultData: (UUID.t) => _data;
  let _defaultRecordId: (UUID.t) => _record;
  let _defaultRecord: unit => _record;
  let findId: (_record) => UUID.t;
};

module type FragmentObj = {
  type data;

  module Fields: {
    type t;
    let name: string;
    let query: string;
    let parse: (Js.Json.t) => t;
  };
  
  let fragmentType: string;
  
  let fromObject: (Fields.t) => data;
};

module type LocalRecord = {
  type _record;
  
  let _defaultRecord: (UUID.t) => _record;
  
  module Record: {
    type t = _record;
    let default: (UUID.t) => _record;
  };
};

module type Container {
  type idType;
  type config;
  type record;

  let getById: idType => option(config);
  let getRecordById: idType => option(record);

  [@bs.obj] external makeProps:
      (~id: 'id, ~children: 'children, ~key: string=?, unit) => {. "children": 'children, "id": 'id} = "";

  let make: ({ . "children": (record => React.element), "id": string}) => React.element;
};

module type DomainWrapper = {
  type model;
  type rootRecord;
  let wrap: model => rootRecord;
  let unwrap: rootRecord => option(model);
  let apolloEnabled: bool;
};

module type ModelRecordType {
  module Model: Model;
  module Wrapper: DomainWrapper;
  type model;
  type _data;
  type _record;
  type _record += Record(Model.Record.t);
};

module type Action = {
  type action;
  type model;
  let reduce: (action, Js.Promise.t(model)) => Js.Promise.t(model);
};

module type M = {
  module rec Model: Model
  and Action: (Action with type model = Model.Record.t);
};
