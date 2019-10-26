module ModelGenerator = ModelUtils.GenerateModel(ModelUtils.RootModel);

module Profile = ModelGenerator();
module User = ModelGenerator();
module Card = ModelGenerator();
module Cube = ModelGenerator();
