[%bs.raw {|require('react-table/react-table.css')|}];
[%bs.raw {|require('bootstrap/dist/css/bootstrap.css')|}];

let component = ReasonReact.statelessComponent("App");

let makeJsx2 = (_children) => {
  ...component,
  render: _self => {
    <ReasonApolloHooks.ApolloProvider client=Client.instance>
      <ReasonApollo.Provider client=Client.instance>
        <MemberPage />
      </ReasonApollo.Provider>
    </ReasonApolloHooks.ApolloProvider>;
  }
};

let default =
  ReasonReact.wrapReasonForJs(~component, _jsProps =>
    makeJsx2([|
      /* ~server=(
           jsProps##server
           |> Js.undefinedToOption
           |> Belt.Option.getWithDefault(_, false)
         ), */
      /* ~initialUrl=Js.undefinedToOption(jsProps##initialUrl), */
    |])
  );