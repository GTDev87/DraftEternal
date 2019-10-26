
module Model = User_Model;

module ModelSchema = Schema.User;
module Record = ModelSchema.AddModel(Model);

module Action = User_Action;
module Mutation = User_Mutation;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);
