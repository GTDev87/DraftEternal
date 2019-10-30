/* done */
type action =
  | NoOpKeyDown
  | LocalAction(User_Local.Action.action);

type model = User_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((user: model) => {
       switch (action) {
       /* both below */
       | NoOpKeyDown => user |> Js.Promise.resolve
       | LocalAction(localAction) =>
         {
           ...user,
           local: User_Local.Action.reduce(localAction, user.local),
         }
         |> Js.Promise.resolve
       };
     });