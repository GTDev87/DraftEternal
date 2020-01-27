module Model = Card_Model.M;

module ModelSchema = Schema.Card;
module Record = ModelUtils.AddModel(ModelSchema, Model);

module Action = Card_Action;
module Mutation = Card_Mutation;
module Container = Container.M(Model);
