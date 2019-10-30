defmodule DraftEternalApi.Web.Schema.Domain.Cube.Aggregate do
  defstruct [
    :id,
    :name,
    :description,
    :display,
    :creator_id,
    :card_ids,
  ]

  alias DraftEternalApi.Web.Schema.Domain.Cube.Aggregate
  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated

  @doc """
  Publish an article
  """
  def execute(%Aggregate{id: nil}, %CreateCube.Command{} = create) do
    %CubeCreated.Event{
      id: create.id,
      name: create.name,
      description: create.description,
      display: create.display,
      creator_id: create.creator_id,
      card_ids: create.card_ids,
    }
  end
  # state mutators

  def apply(%Aggregate{} = cube, %CubeCreated.Event{} = created) do
    %Aggregate{cube |
      id: created.id,
      name: created.name,
      description: created.description,
      display: created.display,
      creator_id: created.creator_id,
      card_ids: created.card_ids,
    }
  end
end