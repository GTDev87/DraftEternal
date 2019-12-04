type _data = {
  id: UUID.t,
  email: string,
  cubeIds: list(Schema.Cube.id),
  guest: bool,
};

module Local = User_Local.Model;

type _record = RecordType.Type.t(_data, Local.Record.t);

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
  local: Local.Record.default(id),
};

let guestData = () => guestDataId(UUID.generateUUID())


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