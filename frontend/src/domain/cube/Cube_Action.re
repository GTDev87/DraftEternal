/* done */
type action =
  | NoOpKeyDown;

type model = Cube_Model.M.Record.t;

let rec reduce = (action, promise: Js.Promise.t(model)): Js.Promise.t(model) =>
  promise
  |> Js.Promise.then_((cube: model) => {
       switch (action) {
       /* both below */
       | NoOpKeyDown => cube |> Js.Promise.resolve
       };
     });