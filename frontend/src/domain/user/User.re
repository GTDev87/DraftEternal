
module Model = User_Model.M;

module ModelSchema = Schema.User;
module Record = ModelUtils.AddModel(ModelSchema, Model);

module Action = User_Action;
module Mutation = User_Mutation;
module Container = Container.M(Model);
