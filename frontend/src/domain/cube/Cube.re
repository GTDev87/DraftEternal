
module Model = Cube_Model;

module ModelSchema = Schema.Cube;
module Record = ModelSchema.AddModel(Model);

module Action = Cube_Action;
module Mutation = Cube_Mutation;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);
