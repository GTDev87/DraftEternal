module Model = Seat_Model.M;

module ModelSchema = Schema.Seat;
module Record = ModelUtils.AddModel(ModelSchema, Model);

module Action = Seat_Action;
module Mutation = Seat_Mutation;
module Container = ApolloFragment.Container(ApolloClient.ReadFragment, Model);
