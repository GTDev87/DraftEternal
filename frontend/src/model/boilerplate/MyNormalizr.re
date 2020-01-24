
module FullReduced = 
  ModelUtils.AddRecord(
    User.Record, ModelUtils.AddRecord(
      Card.Record, ModelUtils.AddRecord(
        Cube.Record, ModelUtils.EmptyNormalizr(
          Domain.RootModel
        )
      )
    )
  )
;

module Converter = {
  // module Profile = NormalizrSetup.DomainTypeConverter(Profile, FullReduced, Profile.Container, Profile.Record.Wrapper);
  module User = NormalizrSetup.DomainTypeConverter(FullReduced, User);
  module Card = NormalizrSetup.DomainTypeConverter(FullReduced, Card);
  module Cube = NormalizrSetup.DomainTypeConverter(FullReduced, Cube);
};

