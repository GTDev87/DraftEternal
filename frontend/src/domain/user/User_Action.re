/* done */
type action =
  | Nothing
  | LocalAction(User_Local.Action.action)
  | ApolloCreateCubeMutationWithAction(ApolloType.t(CreateCube.Mutation.t), action)
  | CombineReducer(action, action);

type model = User_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((user: model) => {
       switch (action) {
       /* both below */
       | Nothing => user |> Js.Promise.resolve
       | LocalAction(localAction) =>
         {
           ...user,
           local: User_Local.Action.reduce(localAction, user.local),
         }
         |> Js.Promise.resolve
       | ApolloCreateCubeMutationWithAction(apollo, action) =>
          apollo
          |> ApolloType.runApollo
          |> Utils.Promise.runBothIgnoreFirst(_, reduce(action, Js.Promise.resolve(user)))
       | CombineReducer(action1, action2) =>
          ActionUtil.combineActions(reduce, user, action1, action2)
        };
  });