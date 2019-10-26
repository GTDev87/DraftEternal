open Belt;
let updateIndex = (list, idx, func) =>
  List.mapWithIndex(list, (i, ele) => i == idx ? func(ele) : ele);

let combineActions =
    (
      reducer: ('a, Js.Promise.t('b)) => Js.Promise.t('b),
      state: 'b,
      action1: 'a,
      action2: 'a,
    )
    : Js.Promise.t('b) =>
  state |> Js.Promise.resolve |> reducer(action1, _) |> reducer(action2, _);