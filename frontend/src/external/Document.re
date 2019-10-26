type mediaQuery;

type document;
type window;

[@bs.val] external typeof: 'a => string = "typeof";
[@bs.val] external document: document = "window.document";
[@bs.val] external fetch: ApolloClient.fetch = "window.fetch";
[@bs.val] external window: window = "window";
[@bs.val] external hash: string = "window.location.hash";
[@bs.val] external origin: string = "window.location.origin";

[@bs.val] external queryParams: string = "window.location.search";
[@bs.module "query-string"]
external parse: string => Js.Dict.t(string) = "parse";

let getHash = (): option(string) =>
  queryParams |> parse |> Js.Dict.get(_, "jwt");

let isBrowser = () =>
  typeof(window) != "undefined" && typeof(document) != "undefined";

[@bs.val] external matchMedia: string => mediaQuery = "window.matchMedia";

[@bs.send]
external addListener: (mediaQuery, unit => unit) => unit = "addListener";
[@bs.send]
external removeListener: (mediaQuery, unit => unit) => unit = "removeListener";

[@bs.get] external matches: mediaQuery => bool = "matches";