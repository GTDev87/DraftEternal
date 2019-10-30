
[@react.component]
let make = () =>

  <Member.Container errorComponent={<GoogleLoginButton />}>
    ...{(~member, ~cardIds) =>
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
  </Member.Container>;