type _data = {
  id: UUID.t,
  email: string,
  cubeIds: list(Schema.Cube.id),
  guest: bool,
};

type _local = User_Local.Model.Record.t;

type _record = RecordType.t(_data, _local);

let _defaultData = (id) => {
  {
    id: id,
    email: "",
    cubeIds: [],
    guest: false,
  }
  /* UI */
};

let guestDataId = (id): _record => {
  data: {
    id: id,
    email: "",
    cubeIds: [],
    guest: true,
  },
  local: User_Local.Model.Record.default(id),
};

let guestData = () => guestDataId(UUID.generateUUID())


let _defaultRecordId = (id): _record => {
  data: _defaultData(id),
  /* local: Classroom_Local.Model.Record.default(id), */
  local: User_Local.Model.Record.default(id),
};

let _defaultRecord = (): _record => {
  _defaultRecordId(UUID.generateUUID())
};

let findId = (record : _record) => record.data.id;