module CardContainer = ApolloQuery.Container(Query.Card.M);

[@react.component]
let make = () =>

  <CardContainer query={Query.Card.M.make()} errorComponent={<div />} >
    ...{(~response) => {
      let cardIds =
        response##cards
        |> Belt.List.fromArray
        |> Belt.List.map(_, Card.Model.objectToId);
      <Member.Container
        errorComponent={
          let guest = User.Model.Record.default();

          <NormalizerInit records=[User.Record.Record(guest)]>
            ...{(~normalized, ~updateNormalizr) => {
              <DashboardLayout id={User.Model.idToTypedId(guest.data.id)} normalized updateNormalizr cardIds/>
            }}
          </NormalizerInit>
        }>
        ...{(~member) =>
          <User.Container id=member##id>
            ...{(user) =>
              <NormalizerInit records=[User.Record.Record(user)]>
                ...{(~normalized, ~updateNormalizr) => {
                  <DashboardLayout id={User.Model.idToTypedId(user.data.id)} normalized updateNormalizr cardIds/>
                }}
              </NormalizerInit>
            }
          </User.Container>
        }
      </Member.Container>
    }}
  </CardContainer>