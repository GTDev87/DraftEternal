module Model = Cube_Model.M;

module ModelSchema = Schema.Cube;
module Record = ModelUtils.AddModel(ModelSchema, Model);

module Action = Cube_Action;
module Mutation = Cube_Mutation;
module Container = Container.M(Model);
