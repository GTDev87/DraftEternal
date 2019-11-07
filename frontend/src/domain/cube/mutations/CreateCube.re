module Mutation = [%graphql
  {|
    mutation CreateCube($id: ID!, $name: String!, $description: String!, $display: DisplayType!, $creatorId: ID!, $cardIds: [ID!]) {
      createCube(cube: {id: $id, name: $name, description: $description, display: $display, creatorId: $creatorId, cardIds: $cardIds}) {
        ...Cube_Model.Fragment.CubeFields
      }
    }
  |}
];


module MutationInternals = {
  module Config = Mutation;
  type mutationFunctionType = (
    ~id: UUID.t,
    ~name: string,
    ~description: string,
    ~display: DisplayType.t,
    ~creatorId: User.Model.idType,
    ~cardIds: list(Card.Model.idType)
  ) => Js.Promise.t(ReasonApolloHooks.Mutation.controlledVariantResult(Config.t));

  let callMutationWithApollo = (apolloMutation : ApolloMutation.apolloMutationType(Config.t)) => 
    ((~id, ~name, ~description, ~display, ~creatorId, ~cardIds) => {
      let compiledMutation = Mutation.make(
        ~id,
        ~name,
        ~description,
        ~display,
        ~creatorId=User_Model.getUUIDFromId(creatorId),
        ~cardIds=
          cardIds
          |> Belt.List.map(_, Card_Model.getUUIDFromId)
          |> Belt.List.toArray,
        ()
      );
      apolloMutation(
        ~variables=compiledMutation##variables,
        ~client=Client.instance,
        ~refetchQueries= (_) => {
          [|
            Query_Member.M.make() |> ReasonApolloHooks.Utils.toQueryObj,
            Query_Card.M.make() |> ReasonApolloHooks.Utils.toQueryObj,
          |];
        },
        // ~optimisticResponse=Config.t,
        (),
      );
    });
};

module ContainerMutation = ApolloMutation.CreateMutationContainer(MutationInternals);