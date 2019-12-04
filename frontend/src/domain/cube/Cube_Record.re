type _data = {
  id: UUID.t,
  name: string,
  description: string,
  display: DisplayType.t,
  cardIds: list(Schema.Card.id),
  creatorId: Schema.User.id,
};

module Local = ModelUtils.CreateFakeLocal();

type _record = RecordType.Type.t(_data, Local.Record.t);

let _defaultData = (id) => {
  {
    id: id,
    name: "",
    description: "",
    display: `PUBLIC,
    cardIds: [],
    creatorId: Schema.User.stringToId(""),
  }
  /* UI */
};

let _defaultRecordId = (id): _record => {
  data: _defaultData(id),
  /* local: Classroom_Local.Model.Record.default(id), */
  local: Local.Record.default(id),
};

let _defaultRecord = (): _record => {
  _defaultRecordId(UUID.generateUUID())
};

type defaultParam = unit;
let _defaultWithId = ((): defaultParam, id: UUID.t) => _defaultRecordId(id);

let findId = (record : _record) => record.data.id;