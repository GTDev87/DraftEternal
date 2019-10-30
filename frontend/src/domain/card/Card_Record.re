type _data = {
  id: UUID.t,
  name: string,
  imageUrl: string,
  thumbnailUrl: string,
  cardText: string,
  cost: int,
  influence: list(InfluenceType.t),
  colors: list(InfluenceType.t),
};

type _local = unit;

type _record = RecordType.t(_data, _local);

let _defaultData = (id) => {
  {
    id: id,
    name: "",
    imageUrl: "",
    thumbnailUrl: "",
    cardText: "",
    cost: 0,
    influence: [],
    colors: [],
  }
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
