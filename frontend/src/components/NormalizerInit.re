type state = {normalized: MyNormalizr.FullReduced.normalizedType};

type action =
  | UpdateNormalizr(MyNormalizr.FullReduced.normalizedType);


[@react.component]
let make = (~records: list(Domain.RootModel.record)=[], ~children) => {
  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | UpdateNormalizr(normalized) => {normalized: normalized}
        },
        {
          normalized:
            Belt.List.reduce(
              records,
              NormalizrNew.Normalizr.defaultNormalized,
              MyNormalizr.FullReduced.normalizerCommitItemToSchema,
            )
        }
    );

    children(~normalized=state.normalized, ~updateNormalizr=norm =>
      norm
      |> Js.Promise.then_(n => UpdateNormalizr(n) |> dispatch(_) |> Js.Promise.resolve)
    )
};