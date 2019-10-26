defmodule ProviderApi.Mixfile do
  use Mix.Project

  def project do
    [
      app: :provider_api,
      version: "0.0.1",
      elixir: "~> 1.6.6",
      elixirc_paths: elixirc_paths(Mix.env()),
      compilers: [:phoenix, :gettext] ++ Mix.compilers(),
      build_embedded: Mix.env() == :prod,
      start_permanent: Mix.env() == :prod,
      # aliases: aliases(),
      deps: deps(),
      preferred_cli_env: [
        coveralls: :test,
        "coveralls.html": :test,
        "coveralls.json": :test
      ],
      test_coverage: [tool: ExCoveralls]
    ]
  end

  # Configuration for the OTP application.
  #
  # Type `mix help compile.app` for more information.
  def application do
    [
      mod: {ProviderApi, []},
      applications: [
        :phoenix,
        :phoenix_pubsub,
        :cowboy,
        :logger,
        :gettext,
        :phoenix_ecto,
        :postgrex,
        :ueberauth,
        :oauth,
        :ueberauth_google,
        :ecto_sql
      ]
    ]
  end

  # Specifies which paths to compile per environment.
  defp elixirc_paths(:test), do: ["lib", "web", "test/support"]
  defp elixirc_paths(_), do: ["lib", "web"]

  # Specifies your project dependencies.
  #
  # Type `mix help deps` for examples and options.
  defp deps do
    [
      {:phoenix, "~> 1.4.0"},
      {:phoenix_pubsub, "~> 1.1"},
      {:phoenix_ecto, "~> 4.0"},
      {:plug_cowboy, "~> 2.0"},
      {:postgrex, "~> 0.14.3"},
      {:gettext, "~> 0.13.1"},
      {:cors_plug, "~> 1.3"},
      {:excoveralls, "~> 0.7.2", only: :test},
      # TODO remove when hooks are disossaciated
      {:neuron, "~> 0.7.0"},
      {:oauth, "~> 1.6", github: "tim/erlang-oauth"},
      {:ueberauth, "~> 0.5.0"},
      {:ueberauth_google, "~> 0.7"},
      {:ja_serializer, "~> 0.12.0"},
      {:guardian, "~> 1.2.1"},
      {:database_url, "~> 0.1"}
    ]
  end

  # Aliases are shortcuts or tasks specific to the current project.
  # For example, to create, migrate and run the seeds file at once:
  #
  #     $ mix ecto.setup
  #
  # See the documentation for `Mix` for more info on aliases.
  # defp aliases do
  #   [
  #     # "ecto.setup": ["ecto.create", "ecto.migrate", "run priv/repo/seeds.exs"],
  #     "ecto.reset": ["ecto.drop", "ecto.setup"],
  #     test: ["ecto.create --quiet", "ecto.migrate", "test"]
  #   ]
  # end
end
