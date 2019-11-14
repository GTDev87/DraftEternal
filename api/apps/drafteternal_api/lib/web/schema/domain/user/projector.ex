defmodule DraftEternalApi.Web.Schema.Domain.User.Projector do
  use Commanded.Projections.Ecto,
    name: "DraftEternalApi.Web.Schema.Domain.User.Projector",
    application: DraftEternalApi.Commanded.Application,
    consistency: :strong

  alias DraftEternalApi.Web.Schema.Domain.User.Events.{
    UserCreated
  }

  project(%UserCreated.Event{} = event, fn multi ->
    UserCreated.Projection.execute(multi, event)
  end)
end