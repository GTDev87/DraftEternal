defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Projection do
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event

  alias DraftEternalApi.Web.Model.Cube
  alias DraftEternalApi.Web.Model.CubeCard

  def execute(multi, %Event{} = created) do

    Enum.reduce(created.card_ids, multi, fn card_id, multi ->

      CubeCard.Multi.insert(multi, %CubeCard{
        id: UUID.uuid4(),
        card_id: card_id,
        cube_id: created.id,
      })
    end)
    |> Cube.Multi.insert(%Cube{
      id: created.id,
      name: created.name,
      description: created.description,
      creator_id: created.creator_id,
    })
  end
end