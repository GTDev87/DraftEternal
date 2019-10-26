[@react.component]
let make = (~maybeData, ~render) => {
  Belt.Option.mapWithDefault(maybeData, <div />, render)
};
