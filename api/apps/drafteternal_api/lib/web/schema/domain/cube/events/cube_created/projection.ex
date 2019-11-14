defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Projection do
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event

  alias DraftEternalApi.Web.Model.Cube
  alias DraftEternalApi.Web.Model.CubeCard

  def execute(multi, %Event{} = created) do
    multi =
      Cube.Multi.insert(multi, %Cube{
        id:  created.id,
        name: created.name,
        description: created.description,
        creator_id: created.creator_id,
        display: created.display,
      })

    Enum.reduce(created.card_ids, multi, fn card_id, multi ->
      uuid = UUID.uuid4()
      CubeCard.Multi.insert(multi, %CubeCard{
        id: uuid,
        cube_id: created.id,
        card_id: card_id,
      }, suffix: uuid)
    end)
  end
end