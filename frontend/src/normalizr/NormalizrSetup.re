let tryAgainifNullOption = (optionA, optionB) =>
  switch (optionA) {
  | Some(_) => optionA
  | None => optionB
  };

module DomainTypeConverter = (
  NormalizrGenerator : ModelUtils.NORMALIZR_GENERATOR_TYPE
    with type t = Domain.RootModel.t
    and type id = Domain.RootModel.id
    and type record = Domain.RootModel.record
    and type normalizedType = NormalizrNew.normalizedSchema(Domain.RootModel.t, UUID.t, Domain.RootModel.record),
  DomainType: Domain.M
) => {
  module Container = DomainType.Container;
  module Wrapper = DomainType.Record.Wrapper;

  let normalizerGetItemFromSchema: (NormalizrGenerator.normalizedType, DomainType.Model.idType) => option(Domain.RootModel.record) =
    (
      a =>
        a
        |> DomainType.Model.idToRootId
        |> NormalizrGenerator.modelIdToIdFunction
    )
    |> NormalizrNew.Normalizr.getItemFromSchema;

  let idListToFilteredItems = (idList: list(DomainType.Model.idType), modelTypefunction) =>
    idList
    |> Belt.List.map(_, modelTypefunction)
    |> Utils.List.removeOptionsFromList;

  let update = (
    default: DomainType.Model.idType => DomainType.Model.Record.t,
    getterFn:
      (NormalizrGenerator.normalizedType, DomainType.Model.idType) =>
      option(DomainType.Model.Record.t),
    reduce:
      (DomainType.Action.action, Js.Promise.t(DomainType.Action.model)) =>
      Js.Promise.t(DomainType.Action.model),
    normalized: Js.Promise.t(NormalizrGenerator.normalizedType),
    id: DomainType.Model.idType,
    action: DomainType.Action.action,
  ) : Js.Promise.t(NormalizrGenerator.normalizedType) => {
    normalized
    |> Js.Promise.then_(norm =>
        norm
        |> getterFn(_, id)
        |> Belt.Option.getWithDefault(_, default(id))
        |> Js.Promise.resolve)
    |> reduce(action, _)
    |> (modelPromise) => (normalized, modelPromise)
    |> Js.Promise.all2
    |> Js.Promise.then_(((norm, model)) =>
        Js.Promise.resolve(NormalizrGenerator.normalizerCommitItemToSchema(norm, Wrapper.wrap(model))));
  };
  let fromLocal = (
    normalized: NormalizrGenerator.normalizedType,
    id: DomainType.Model.idType /* maybe make domain model idtype*/,
  ) : option(DomainType.Model.Record.t) =>
    normalized
    |> normalizerGetItemFromSchema(_, id)
    |> Belt.Option.flatMap(_, Wrapper.unwrap);

  let fromSchema = (
    normalized: NormalizrGenerator.normalizedType,
    id: DomainType.Model.idType /* maybe make domain model idtype*/,
  ) : option(DomainType.Model.Record.t) => {
    let optionNormalized = fromLocal(normalized, id);

    Wrapper.apolloEnabled ?
      id
      |> Container.getById
      |> Belt.Option.map(_, (fragment: DomainType.Model.Fragment.Fields.t) =>
           (
             switch (optionNormalized) {
             | Some(data) => {
                 local: data.local,
                 data: DomainType.Model.Record.Data.fromObject(fragment),
               }
             | None => DomainType.Model.Record.fromObject(fragment) /* does this also generate the local? */
             }: DomainType.Model.Record.t
           )
         )
      |> tryAgainifNullOption(_, optionNormalized) :
      optionNormalized;
  };

  module Local = {
    let getRecord = fromLocal;
    let getRecordWithDefault = (
      normalized: NormalizrGenerator.normalizedType,
      id: DomainType.Model.idType,
      param: DomainType.Model.Record.defaultParam,
    ) : DomainType.Model.Record.t =>
      normalized
      |> fromLocal(_, id)
      |> Belt.Option.getWithDefault(_, DomainType.Model.Record.defaultWithId(param, id));

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromLocal,
        DomainType.Action.reduce);
  };

  module Remote = {
    let getRecord = fromSchema;
    let getRecordWithDefault = (
      normalized: NormalizrGenerator.normalizedType,
      id: DomainType.Model.idType,
      param: DomainType.Model.Record.defaultParam,
    ) : DomainType.Model.Record.t =>
      normalized
      |> fromSchema(_, id)
      |> Belt.Option.getWithDefault(_, DomainType.Model.Record.defaultWithId(param, id));

    let updateWithDefault = (param: DomainType.Model.Record.defaultParam) =>
      update(
        DomainType.Model.Record.defaultWithId(param, _),
        fromSchema, /* How does this handle the llocal??????? */
        DomainType.Action.reduce);
  };
};