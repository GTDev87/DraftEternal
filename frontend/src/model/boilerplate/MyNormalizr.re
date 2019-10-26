
module FullReduced = ModelUtils.AddRecord(
    ModelUtils.AddRecord(
      ModelUtils.AddRecord(ModelUtils.EmptyNormalizr(ModelUtils.RootModel), Cube.Record),
    Card.Record),
  User.Record
);

module Converter = {
  // module Profile = NormalizrSetup.DomainTypeConverter(Profile, FullReduced, Profile.Container, Profile.Record.Wrapper);
  module User = NormalizrSetup.DomainTypeConverter(User, FullReduced, User.Container, User.Record.Wrapper);
  module Card = NormalizrSetup.DomainTypeConverter(Card, FullReduced, Card.Container, Card.Record.Wrapper);
  module Cube = NormalizrSetup.DomainTypeConverter(Cube, FullReduced, Cube.Container, Cube.Record.Wrapper);
};

