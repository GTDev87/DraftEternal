
[@react.component]
let make = () =>

  <Member.Container errorComponent={<GoogleLoginButton />}>
    ...{(~member) =>
      <User.Container id=member##id>
        ...{(user) =>
          <NormalizerInit records=[User.Record.Record(user)]>
            ...{(~normalized, ~updateNormalizr) => {
              <DashboardLayout user normalized updateNormalizr />
            }}
          </NormalizerInit>
        }
      </User.Container>
    }
  </Member.Container>;