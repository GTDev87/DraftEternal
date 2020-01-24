module ModelGenerator = ModelUtils.GenerateModel(Domain.RootModel);

module Profile : Domain.SCHEMA_TYPE = ModelGenerator();
module User : Domain.SCHEMA_TYPE = ModelGenerator();
module Card : Domain.SCHEMA_TYPE = ModelGenerator();
module Cube : Domain.SCHEMA_TYPE = ModelGenerator();
module Seat : Domain.SCHEMA_TYPE = ModelGenerator();
module Pack : Domain.SCHEMA_TYPE = ModelGenerator();
module Draft : Domain.SCHEMA_TYPE = ModelGenerator();
