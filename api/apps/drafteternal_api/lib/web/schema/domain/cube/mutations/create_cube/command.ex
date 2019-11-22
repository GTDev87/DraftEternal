defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.Command do
  defstruct [
    id: "",
    name: "",
    description: "",
    display: "",
    creator_id: "",
    card_ids: [],
  ]

  use ExConstructor
  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.Command
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event
  alias DraftEternalApi.Web.Schema.Domain.Cube.Aggregate

  def execute(%Aggregate{id: nil} = cube, %Command{} = create) do
    %Event{
      id: create.id,
      name: create.name,
      description: create.description,
      display: create.display,
      creator_id: create.creator_id,
      card_ids: create.card_ids,
    }
  end
end