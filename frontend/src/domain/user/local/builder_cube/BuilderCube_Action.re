type action =
  | UpdateName(string)
  | AddCard(Schema.Card.id)
;

type model = BuilderCube_Model.Record.t;

let reduce = (action, builderCube: model) =>
  switch (action) {
  | UpdateName(name) => {...builderCube, data: {...builderCube.data, name}}
  | AddCard(id) => {...builderCube, data: {...builderCube.data, cardIds: builderCube.data.cardIds @ [id]}}
};