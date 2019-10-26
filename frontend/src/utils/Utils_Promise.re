let runBothIgnoreFirst =
    (a: Js.Promise.t('a), b: Js.Promise.t('b)): Js.Promise.t('b) =>
  (a, b)
  |> Js.Promise.all2
  |> Js.Promise.then_(((_, second)) => Js.Promise.resolve(second));