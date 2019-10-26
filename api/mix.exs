defmodule UmbrellaApp.Mixfile do
  use Mix.Project
def project do
    [apps_path: "apps",
    #  build_embedded: Mix.env == :prod,
     start_permanent: Mix.env == :prod,
     deps: deps(),
     aliases: aliases()
    ]
  end
  defp deps do
    []
  end

  defp aliases do
    [
      "ecto.setup": [
        "ecto.create",
        "ecto.migrate",
        "run apps/drafteternal_api/priv/repo/seeds.exs",
        "run apps/provider_api/priv/repo/seeds.exs",
      ],
      "ecto.migrate_seed": [
        "ecto.migrate",
        "run apps/drafteternal_api/priv/repo/seeds.exs",
        "run apps/provider_api/priv/repo/seeds.exs",
      ],
      # "ecto.reset": ["ecto.drop", "ecto.setup"],
      # "test": ["ecto.create --quiet", "ecto.migrate", "test"]
    ]
  end
end
