module Model = Card_Model.M;

module ModelSchema = Schema.Card;
module Record = ModelSchema.AddModel(Model);

module Action = Card_Action;
module Mutation = Card_Mutation;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);
