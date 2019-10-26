defmodule DraftEternalApi.Web.Schema.Router do
  use Commanded.Commands.Router

  alias DraftEternalApi.Web.Schema.Domain.User
  
  identify User.Aggregate, by: :id, prefix: "user-"

  dispatch [
      User.Mutations.CreateUser.Command,
  ], to: User.Aggregate


  alias DraftEternalApi.Web.Schema.Domain.Cube

  identify Cube.Aggregate, by: :id, prefix: "cube-"

  dispatch [
      Cube.Mutations.CreateCube.Command,
  ], to: Cube.Aggregate
end