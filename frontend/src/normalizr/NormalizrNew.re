type recordList('uuid, 'rType) = list(('uuid, 'rType));
type normalizedSchema('schemaType, 'uuid, 'rType) =
  list(('schemaType, recordList('uuid, 'rType)));
type typeConversionFunction('rType, 'schemaType, 'uuid) =
  'rType => ('schemaType, 'uuid);
type idConversionFunction('idType, 'schemaType, 'uuid) =
  'idType => ('schemaType, 'uuid);

module type Normalizr = {
  let defaultNormalized: list(unit);
  let addOrModifyById:
    (recordList('uuid, 'rType), 'rType, 'uuid) => recordList('uuid, 'rType);
  let commitItemToSchema:
    (
      typeConversionFunction('rType, 'schemaType, 'uuid),
      normalizedSchema('schemaType, 'uuid, 'rType),
      'rType
    ) =>
    normalizedSchema('schemaType, 'uuid, 'rType);
  let getItemFromSchema:
    (
      idConversionFunction('idType, 'schemaType, 'uuid),
      normalizedSchema('schemaType, 'uuid, 'rType),
      'idType
    ) =>
    option('rType);
};

module Normalizr = {
  let defaultNormalized = [];

  let addOrModifyById = (recordList, rType, newUUID) =>
    recordList
    |> Belt.List.getBy(_, ((uuid, _)) => uuid == newUUID)
    |> (
      maybeRecordTuple =>
        switch (maybeRecordTuple) {
        | None => recordList @ [(newUUID, rType)]
        | Some(_) =>
          Belt.List.map(recordList, ((iterUUID, iterRecordType)) =>
            newUUID == iterUUID ?
              (newUUID, rType) : (iterUUID, iterRecordType)
          )
        }
    );

  let commitItemToSchema = (typeConversionFunction, normalizedSchema, rType) => {
    let (newSchmaType, id) = typeConversionFunction(rType);
    normalizedSchema
    |> Belt.List.getBy(_, ((schemaType, _)) => schemaType == newSchmaType)
    |> (
      maybeSchmaType =>
        switch (maybeSchmaType) {
        | None =>
          normalizedSchema
          @ [(newSchmaType, addOrModifyById([], rType, id))]
        | Some(_) =>
          normalizedSchema
          |> Belt.List.map(_, ((iterSchemaType, iterRecordList)) =>
               iterSchemaType == newSchmaType ?
                 (
                   iterSchemaType,
                   addOrModifyById(iterRecordList, rType, id),
                 ) :
                 (iterSchemaType, iterRecordList)
             )
        }
    );
  };

  let getItemFromSchema = (modelIdToIdFunction, normalizedSchema, modelIdType) => {
    let (schemaType, id) = modelIdToIdFunction(modelIdType);
    normalizedSchema
    |> Belt.List.getBy(_, ((iterSchemaType, _)) =>
         schemaType == iterSchemaType
       )
    |> (
      maybeRecordListTuple =>
        switch (maybeRecordListTuple) {
        | None => None
        | Some((_, recordList)) =>
          recordList
          |> Belt.List.getBy(_, ((iterUUID, _)) => iterUUID == id)
          |> Belt.Option.map(_, ((_, iterRecord)) => iterRecord)
        }
    );
  };
};