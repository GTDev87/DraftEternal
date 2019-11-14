/* type renderPropObjJS = {
  .
  "loading": bool,
  "called": bool,
  "data": Js.Nullable.t(Js.Json.t),
  "error": Js.Nullable.t(ReasonApolloTypes.apolloError),
  "networkStatus": int,
  "variables": Js.Null_undefined.t(Js.Json.t),
}; */



type t('a) = unit => Js.Promise.t(ReasonApolloHooks.Mutation.controlledVariantResult('a));

/*  */

let runApollo = (apollo: t('a)): Js.Promise.t(ReasonApolloHooks.Mutation.controlledVariantResult('a)) => apollo();