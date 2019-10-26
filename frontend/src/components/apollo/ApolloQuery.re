[@bs.config {jsx: 3}];

module Container = (Config: ReasonApolloTypes.Config) => {
  module QueryComponent = ReasonApollo.CreateQuery(Config);

  let defaultLoadingComponent = <div> {ReasonReact.string("Loading")} </div>;
  let defaultErrorComponent = error =>
    <div>
      {ReasonReact.string("Error: ")}
      {ReasonReact.string(error##message)}
    </div>;

  [@react.component]
  let make = (
    ~query,
    ~errorComponent=?,
    ~loadingComponent=?,
    ~children
  ) => {
    <QueryComponent variables=query##variables>
      ...{
            ({result}) =>
              switch (result) {
              | Loading =>
                loadingComponent
                |> Belt.Option.getWithDefault(_, defaultLoadingComponent)
              | Error(error) =>
                Belt.Option.getWithDefault(
                  errorComponent,
                  defaultErrorComponent(error),
                )
              | Data(response) => children(~response)
              }
          }
    </QueryComponent>
  };
};

