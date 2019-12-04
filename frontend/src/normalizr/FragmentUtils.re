module CreateFakeFragment(
  RecordType : Domain.Record
) : (
  Domain.FragmentObj
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
  
  let fromObject = (obj: Fields.t): data => RecordType._defaultData(obj##id);
}