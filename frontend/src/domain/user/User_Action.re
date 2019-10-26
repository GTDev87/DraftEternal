/* done */
type action =
  | NoOpKeyDown;

type model = User_Model.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((user: model) => {
       switch (action) {
       /* both below */
       | NoOpKeyDown => user |> Js.Promise.resolve
       };
     });