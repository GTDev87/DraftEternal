let localStorageNamespace = "drafteternal.app.auth";

let saveAuth = () =>
  switch (Document.getHash()) {
  | None => ()
  | Some(authorizationToken) =>
    Dom.Storage.localStorage
    |> Dom.Storage.setItem(localStorageNamespace, authorizationToken)
  };

let getAuth = () =>
  Document.isBrowser() ?
    Dom.Storage.localStorage |> Dom.Storage.getItem(localStorageNamespace) :
    None;