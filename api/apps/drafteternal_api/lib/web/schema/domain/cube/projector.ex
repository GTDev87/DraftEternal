defmodule DraftEternalApi.Web.Schema.Domain.Cube.Projector do
  use Commanded.Projections.Ecto,
    name: "DraftEternalApi.Web.Schema.Domain.Cube.Projector",
    application: DraftEternalApi.Commanded.Application,
    consistency: :strong

  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.{
    CubeCreated,
    CubeUpdated,
  }

  project(%CubeCreated.Event{} = event, fn multi ->
    CubeCreated.Projection.execute(multi, event)
  end)
  project(%CubeUpdated.Event{} = event, fn multi ->
    CubeUpdated.Projection.execute(multi, event)
  end)
end