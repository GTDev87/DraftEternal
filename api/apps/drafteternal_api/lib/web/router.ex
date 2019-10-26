defmodule DraftEternalApi.Web.Router do
  use DraftEternalApi.Web, :router

  pipeline :api do
    plug DraftEternalApi.Guardian.AuthPipeline
    # plug DraftEternalApi.Web.Context
    # plug Guardian.Plug.VerifyHeader
    plug :accepts, ["json"]
  end

  scope "/" do
    pipe_through :api

    forward "/api", Absinthe.Plug,
      schema: DraftEternalApi.Web.Schema

    forward "/graphiql", Absinthe.Plug.GraphiQL,
      schema: DraftEternalApi.Web.Schema,
      socket: DraftEternalApi.Web.UserSocket
  end
end
