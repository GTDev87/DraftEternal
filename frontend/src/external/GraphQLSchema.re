[@bs.module]
external introspect: Js.Json.t = "../../../../graphql_schema.json";
let data:  Js.Json.t = [%bs.raw {| introspect.default.data |}];