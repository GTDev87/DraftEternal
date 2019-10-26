defmodule DraftEternalApi.Mixfile do
  use Mix.Project

  def project do
    [
      app: :drafteternal_api,
      version: "0.0.1",
      elixir: "~> 1.9.0",
      elixirc_paths: elixirc_paths(Mix.env()),
      compilers: [:phoenix, :gettext] ++ Mix.compilers(),
      build_embedded: Mix.env() == :prod,
      start_permanent: Mix.env() == :prod,
      aliases: aliases(),
      deps: deps()
    ]
  end

  # Configuration for the OTP application.
  #
  # Type `mix help compile.app` for more information.
  def application do
    [
      mod: {DraftEternalApi, []},
      extra_applications: [
        :logger,
        :eventstore,
        :ecto_sql
      ]
    ]
  end

  # Specifies which paths to compile per environment.
  defp elixirc_paths(:test), do: ["lib", "test/support"]
  defp elixirc_paths(_), do: ["lib"]

  # Specifies your project dependencies.
  #
  # Type `mix help deps` for examples and options.
  defp deps do
    [
      {:phoenix, "~> 1.4.0"},
      {:phoenix_pubsub, "~> 1.1"},
      {:phoenix_ecto, "~>4.0"},
      {:postgrex, "~> 0.14.3"},
      {:phoenix_html, "~> 2.11"},
      {:phoenix_live_reload, "~> 1.2", only: :dev},
      {:gettext, "~> 0.13.1"},
      {:absinthe, "~> 1.4.14"},
      {:absinthe_plug, "~> 1.4"},
      {:poison, "~> 3.0"},
      {:plug, "~> 1.7.1"},
      {:plug_cowboy, "~> 2.0"},
      {:absinthe_ecto, "~> 0.1"},
      {:cors_plug, "~> 1.3"},
      {:faker, "~> 0.8"},
      {:guardian, "~> 1.2.1"},
      {:eventstore, "~> 0.17"},
      {:elixir_uuid, "~> 1.2"},
      {:dialyxir, "~> 1.0.0-rc.3", only: [:dev], runtime: false},
      {:dataloader, "~> 1.0.6"},
      {:statistics, "~> 0.5.0"},
      {:matrix, "~> 0.3.0"},
      {:jason, "~> 1.1"},
      {:database_url, "~> 0.1"},
      {:commanded, "~> 0.19"},
      {:commanded_ecto_projections, "~> 0.8"},
      {:commanded_eventstore_adapter, "~> 0.6"},
      {:castore, "~> 0.1.0"},
      {:mint, "~> 0.4.0"},
      {:exconstructor, "~> 1.1"}
    ]
  end

  # Aliases are shortcuts or tasks specific to the current project.
  # For example, to create, migrate and run the seeds file at once:
  #
  #     $ mix ecto.setup
  #
  # See the documentation for `Mix` for more info on aliases.
  defp aliases do
    [
      # "ecto.setup": ["ecto.create", "ecto.migrate", "run priv/repo/seeds.exs"],
      "ecto.reset": ["ecto.drop", "ecto.setup"],
      test: ["ecto.create --quiet", "ecto.migrate", "test"]
    ]
  end
end
