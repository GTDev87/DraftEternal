module CubeCardContainer = ApolloQuery.Container(Query.CubeCard.M);

let index = FlexSearch.create();

[@react.component]
let make = () =>

  <CubeCardContainer query={Query.CubeCard.M.make()} errorComponent={<div />} >
    ...{(~response) => {
      let cardIds =
        response##cards
        |> Belt.List.fromArray
        |> Belt.List.map(_, Card.Model.objectToId);

      let cubeIds =
        response##cubes
        |> Belt.List.fromArray
        |> Belt.List.map(_, Cube.Model.objectToId);
      <Member.Container
        errorComponent={
          let guest = User_Record.guestData();

          <NormalizerInit records=[]>
            ...{(~normalized, ~updateNormalizr) => {
              
              React.useEffect1(() => {
                /* Once */
                cardIds
                |> MyNormalizr.Converter.Card.idListToFilteredItems(_, MyNormalizr.Converter.Card.Remote.getRecord(normalized))
                |> Belt.List.map(_, (card: Card.Model.Record.t) => FlexSearch.addValue(index, card.data.id, card.data.name ++ " " ++ card.data.cardText));
                None; /* May need a cleanup function */
              }, [||]);
              
              <DashboardLayout guest=true id={User.Model.idToTypedId(guest.data.id)} normalized updateNormalizr cubeIds cardIds index/>
            }}
          </NormalizerInit>
        }>
        ...{(~member) =>
          <User.Container id=member##id>
            ...{(user) =>
              <NormalizerInit records=[User.Record.Record(user)]>
                ...{(~normalized, ~updateNormalizr) => {
                  React.useEffect1(() => {
                    /* Once */
                    cardIds
                    |> MyNormalizr.Converter.Card.idListToFilteredItems(_, MyNormalizr.Converter.Card.Remote.getRecord(normalized))
                    |> Belt.List.map(_, (card: Card.Model.Record.t) => FlexSearch.addValue(index, card.data.id, card.data.name ++ " " ++ card.data.cardText));
                    None; /* May need a cleanup function */
                  }, [||]);

                  <DashboardLayout guest=false id={User.Model.idToTypedId(user.data.id)} normalized updateNormalizr cubeIds cardIds index/>
                }}
              </NormalizerInit>
            }
          </User.Container>
        }
      </Member.Container>
    }}
  </CubeCardContainer>