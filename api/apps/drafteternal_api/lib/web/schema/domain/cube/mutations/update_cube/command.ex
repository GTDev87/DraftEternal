defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.UpdateCube.Command do
  defstruct [
    id: "",
    name: "",
    description: "",
    display: "",
    creator_id: "",
    card_ids: [],
  ]

  use ExConstructor
  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.UpdateCube.Command
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Event
  alias DraftEternalApi.Web.Schema.Domain.Cube.Aggregate

  def execute(%Aggregate{id: id} = cube, %Command{} = update) when id != nil do
    require Logger
    Logger.debug("cube = #{inspect cube}")
    %Event{
      id: update.id,
      name: update.name,
      description: update.description,
      display: update.display,
      creator_id: update.creator_id,
      card_ids: update.card_ids,
    }
  end
  def execute(%Aggregate{} = cube, %Command{}) do
    require Logger
    Logger.debug("non cube = #{inspect cube}")
    {:error, :updating_non_existant}
  end
end