module CreateFakeFragment(
  RecordType : Domain.RECORD
) : (
  Domain.FRAGMENT
    with type data = RecordType._data
    and type Fields.t = {. "id": string}
) {
  type data = RecordType._data;

  module Fields = {
    type t = {. "id": string};
    let name: string = "";
    let query: string = "";
    let parse = (json: Js.Json.t): t => {"id": ""};
  };
  
  let fragmentType = "";

  let toId = (obj) => obj##id;
  
  let fromObject = (obj: Fields.t): data => RecordType._defaultData(toId(obj));
}