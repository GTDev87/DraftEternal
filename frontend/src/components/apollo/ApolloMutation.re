type apolloMutationType('a) = (
  ~variables: Js.Json.t=?,
  ~client: ApolloClient.generatedApolloClient=?,
  ~refetchQueries: ReasonApolloHooks.Mutation.refetchQueries=?,
  ~awaitRefetchQueries: bool=?,
  unit
) => Js.Promise.t(ReasonApolloHooks.Mutation.controlledVariantResult('a));

module type MutationInternal = {
    module Config: { let query: string; type t; let parse: Js.Json.t => t; }

    type mutationFunctionType;

    let callMutationWithApollo: apolloMutationType(Config.t) => mutationFunctionType;
};

module type MutationContainer = {
    module Config: { let query: string; type t; let parse: Js.Json.t => t; }

    type apolloFunctionType = apolloMutationType(Config.t);
    type mutationFunctionType;
    type callMutationType = (apolloFunctionType) => mutationFunctionType;

    let callMutationWithApollo: callMutationType;
    let make: {. "children": (mutationFunctionType) => React.element} => React.element;

    [@bs.obj] external makeProps:
      (~children: mutationFunctionType => React.element, ~key: string=?, unit) => {. "children": mutationFunctionType => React.element} = "";
};

module CreateMutationContainer = (MutationInternalType: MutationInternal) : (
    MutationContainer
        with type mutationFunctionType = MutationInternalType.mutationFunctionType
        and module Config = MutationInternalType.Config
        and type apolloFunctionType = apolloMutationType(MutationInternalType.Config.t)
) => {
    /* SUPER BAD NAMING */
    module Config = MutationInternalType.Config;
    module InternalMutation = ReasonApolloHooks.Mutation.Make(Config);

    type mutationFunctionType = MutationInternalType.mutationFunctionType;
    type apolloFunctionType = apolloMutationType(Config.t);
    type callMutationType = (apolloFunctionType) => MutationInternalType.mutationFunctionType;

    let callMutationWithApollo: (apolloFunctionType => mutationFunctionType) = MutationInternalType.callMutationWithApollo;

    let makeProps = (~children, ()) => {
        "children": children,
    };

    [@react.component]
    let make = (~children: (mutationFunctionType) => React.element) => {
        let (internalMutation, _simple, _full) = InternalMutation.use(());

        children(callMutationWithApollo(internalMutation));
    };
}