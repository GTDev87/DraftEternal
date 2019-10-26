/* This doesn't really belong here but I'll add it it belongs with queries*/
module MemberContainer = ApolloQuery.Container(Query.Member.M);
module CardContainer = ApolloQuery.Container(Query.Card.M);

[@react.component]
let make = (~errorComponent, ~children) => {
  <CardContainer query={Query.Card.M.make()} errorComponent>
    ...{(~response) =>
      <MemberContainer query={Query.Member.M.make()} errorComponent>
        ...{(~response) => children(~member=response##member)}
      </MemberContainer>
    }
  </CardContainer>
};