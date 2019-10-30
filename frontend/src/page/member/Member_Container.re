/* This doesn't really belong here but I'll add it it belongs with queries*/
module MemberContainer = ApolloQuery.Container(Query.Member.M);

[@react.component]
let make = (~errorComponent, ~children) => {
  <MemberContainer query={Query.Member.M.make()} errorComponent>
    ...{(~response) => children(~member=response##member)}
  </MemberContainer>
};