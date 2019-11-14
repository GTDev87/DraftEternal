defmodule DraftEternalApi do
  use Application

  # See http://elixir-lang.org/docs/stable/elixir/Application.html
  # for more information on OTP Applications
  def start(_type, _args) do
    import Supervisor.Spec

    # Define workers and child supervisors to be supervised
    children = [
      # Start the Ecto repository
      DraftEternalApi.Commanded.Application,
      DraftEternalApi.Web.Repo,
      DraftEternalApi.Web.WriteRepo,
      # Start the endpoint when the application starts
      DraftEternalApi.Web.Endpoint,
      {Absinthe.Subscription, [DraftEternalApi.Web.Endpoint]},
      # DraftEternalApi.EventStore,
      # worker(DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Projection, [], id: :user_aggregate_projector),
      # Start your own worker by calling: DraftEternalApi.Web.Worker.start_link(arg1, arg2, arg3)
      # worker(DraftEternalApi.Web.Worker, [arg1, arg2, arg3]),
      DraftEternalApi.Web.Schema.Domain.User.Supervisor,
      DraftEternalApi.Web.Schema.Domain.Cube.Supervisor,
      worker(DraftEternalApi.Web.Lib.KeyValue, []),
    ]

    # See http://elixir-lang.org/docs/stable/elixir/Supervisor.html
    # for other strategies and supported options
    opts = [strategy: :one_for_one, name: DraftEternalApi.Supervisor]
    Supervisor.start_link(children, opts)
  end

  defdelegate set(k, v), to: DraftEternalApi.Web.Lib.KeyValue
  defdelegate get(k), to: DraftEternalApi.Web.Lib.KeyValue
  defdelegate clear, to: DraftEternalApi.Web.Lib.KeyValue

  # Tell Phoenix to update the endpoint configuration
  # whenever the application is updated.
  def config_change(changed, _new, removed) do
    DraftEternalApi.Web.Endpoint.config_change(changed, removed)
    :ok
  end
end
