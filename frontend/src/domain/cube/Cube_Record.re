type _data = {
  id: UUID.t,
  name: string,
  description: string,
  display: string,
  cardIds: list(Schema.Card.id),
  creatorId: Schema.User.id,
};

type _local = unit;

type _record = RecordType.t(_data, _local);

let _defaultData = (id) => {
  {
    id: id,
    name: "",
    description: "",
    display: "",
    cardIds: [],
    creatorId: Schema.User.stringToId(""),
  }
  /* UI */
};

let _defaultRecordId = (id): _record => {
  data: _defaultData(id),
  /* local: Classroom_Local.Model.Record.default(id), */
  local: (),
};

let _defaultRecord = (): _record => {
  _defaultRecordId(UUID.generateUUID())
};

let findId = (record : _record) => record.data.id;