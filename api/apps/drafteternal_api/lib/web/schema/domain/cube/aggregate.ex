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
  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.{CreateCube, UpdateCube}
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.{CubeCreated, CubeUpdated}

  @doc """
  Publish an article
  """
  def execute(%Aggregate{id: nil} = cube, %CreateCube.Command{} = create) do
    CreateCube.Command.execute(cube, create)
  end
  def execute(%Aggregate{} = cube, %UpdateCube.Command{} = update) do
    UpdateCube.Command.execute(cube, update)
  end

  # state mutators
  def apply(%Aggregate{} = cube, %CubeCreated.Event{} = created) do
    CubeCreated.Event.apply(cube, created)
  end
  def apply(%Aggregate{} = cube, %CubeUpdated.Event{} = updated) do
    CubeUpdated.Event.apply(cube, updated)
  end
end