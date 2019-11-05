type action =
  | UpdateName(string)
  | AddCard(Schema.Card.id)
  | RemoveCard(Schema.Card.id)
;

type model = BuilderCube_Model.Record.t;

let has = (list, item) => /* look for belt has*/
  list
  |> Belt.List.keep(_, (ele) => ele == item)
  |> Belt.List.length != 0;

let reduce = (action, builderCube: model) =>
  switch (action) {
  | UpdateName(name) => {...builderCube, data: {...builderCube.data, name}}
  | AddCard(cardId) =>
    switch(has(builderCube.data.cardIds, cardId)) {
    | true => builderCube
    | false => 
      {
        ...builderCube,
        data: {
          ...builderCube.data,
          cardIds: builderCube.data.cardIds @ [cardId]
        }
      }
    }
      
  | RemoveCard(cardId) => {...builderCube, data: {...builderCube.data, cardIds: Belt.List.keep(builderCube.data.cardIds, (cid) => cid != cardId)}} 
      
};