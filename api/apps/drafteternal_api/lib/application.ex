defmodule DraftEternalApi.Commanded.Application do
  use Commanded.Application,
    otp_app: :drafteternal_api,
    event_store: [
      adapter: Commanded.EventStore.Adapters.EventStore,
      event_store: DraftEternalApi.EventStore
    ],
    pubsub: :local,
    registry: :local

  # use Commanded.Projections.Ecto
  #   name: "DraftEternalApi.Web.Schema.Domain.User.Projector",
  #   application: DraftEternalApi.Web,
  #   repo: DraftEternalApi.Web.Repo,
  #   consistency: :strong,

  router DraftEternalApi.Web.Schema.Router
end