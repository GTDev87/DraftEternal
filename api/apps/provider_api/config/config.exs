# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.
use Mix.Config

# General application configuration
config :provider_api,
  ecto_repos: [ProviderApi.Repo]

# Configures the endpoint
config :provider_api, ProviderApi.Endpoint,
  url: [host: "localhost"],
  secret_key_base: System.get_env("SECRET_KEY_BASE"),
  pubsub: [name: ProviderApi.PubSub, adapter: Phoenix.PubSub.PG2],
  render_errors: [view: ProviderApi.ErrorView, accepts: ~w(html json json-api)]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Change the json response type to json-api
config :phoenix, :json_library, Jason

config :plug, :types, %{
  "application/vnd.api+json" => ["json-api"]
}

# Ueberauth Config for oauth
config :ueberauth, Ueberauth,
  base_path: "/api/v1/auth",
  providers: [
    google: { Ueberauth.Strategy.Google, [] },
    identity: { Ueberauth.Strategy.Identity, [
        callback_methods: ["POST"],
        uid_field: :username,
        nickname_field: :username,
      ] },
  ]

# Ueberauth Strategy Config for Google oauth
config :ueberauth, Ueberauth.Strategy.Google.OAuth,
  client_id: System.get_env("DRAFTETERNAL_GOOGLE_CLIENT_ID"),
  client_secret: System.get_env("DRAFTETERNAL_GOOGLE_CLIENT_SECRET")
  # redirect_uri: System.get_env("DRAFTETERNAL_GOOGLE_REDIRECT_URI")

# Guardian configuration
config :provider_api, ProviderApi.Guardian,
  allowed_algos: ["HS512"], # optional
  verify_module: Guardian.JWT,  # optional
  issuer: "drafteternal_api",
  ttl: { 30, :days },
  allowed_drift: 2000,
  verify_issuer: true, # optional
  # generated using: JOSE.JWK.generate_key({:oct, 16}) |> JOSE.JWK.to_map |> elem(1)
  secret_key: System.get_env("GUARDIAN_SECRET") || %{"k" => "CMiIxqWkh_Vz_2RNsy11Nw", "kty" => "oct"}#,
  # serializer: ProviderApi.GuardianSerializer
# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env}.exs"
