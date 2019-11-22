defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Projection do
  import Ecto.Query
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Event

  alias DraftEternalApi.Web.Model.Cube
  alias DraftEternalApi.Web.Model.CubeCard

  def execute(multi, %Event{} = updated) do
    require Logger

    Logger.debug("DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Projection execute")

    cube = Cube.id(updated.id)

    Logger.debug("cube = #{inspect cube}")

    multi =
      Cube.Multi.update(multi, cube, %{
        name: updated.name,
        description: updated.description,
        display: updated.display,
      })

    queryable = from(cc in CubeCard, where: cc.cube_id == ^updated.id)
    
    
    multi = Ecto.Multi.delete_all(multi, :delete_all, queryable)

    Enum.reduce(updated.card_ids, multi, fn card_id, multi ->
      uuid = UUID.uuid4()
      CubeCard.Multi.insert(multi, %CubeCard{
        id: uuid,
        cube_id: updated.id,
        card_id: card_id,
      }, suffix: uuid)
    end)
  end
end