let listToReactArray = (list) =>
  list
  |> Belt.List.toArray
  |> ReasonReact.array;

// let createBlankComponent = (name) =>
//   {...ReasonReact.statelessComponent(name), render: (_self) => <div/>};