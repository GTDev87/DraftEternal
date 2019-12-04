// type _data = {
//   id: string,
//   seed: int,
//   cubeId: Cube.Model.idType,
//   numSeats: int,
//   numCardsInPack: int,
//   seatIds: list(Seat_Model.M.idType),
// };


// type _local = unit;

// type _record = RecordType.Type.t(_data, _local);

// let _defaultData = (id) => {
//   {
//     id: id,
//     seed: 0,
//     cubeId: Cube_Model.M.idToTypedId(""),
//     numSeats: 0,
//     numCardsInPack: 0,
//     seatIds: [],
//   }
//   /* UI */
// };

// let _defaultRecordId = (id): _record => {
//   data: _defaultData(id),
//   /* local: Classroom_Local.Model.Record.default(id), */
//   local: (),
// };

// let _defaultRecord = (): _record => {
//   _defaultRecordId(UUID.generateUUID())
// };

// let findId = (record : _record) => record.data.id;