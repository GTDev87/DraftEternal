type renderPropObjJS = {
  .
  "loading": bool,
  "called": bool,
  "data": Js.Nullable.t(Js.Json.t),
  "error": Js.Nullable.t(ReasonApolloTypes.apolloError),
  "networkStatus": int,
  "variables": Js.Null_undefined.t(Js.Json.t),
};

type t = unit => Js.Promise.t(renderPropObjJS);

/*  */

let runApollo = (apollo: t): Js.Promise.t(renderPropObjJS) => apollo();