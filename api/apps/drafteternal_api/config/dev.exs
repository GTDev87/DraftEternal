use Mix.Config

# For development, we disable any cache and enable
# debugging and code reloading.
#
# The watchers configuration can be used to run external
# watchers to your application. For example, we use it
# with brunch.io to recompile .js and .css sources.
config :drafteternal_api, DraftEternalApi.Web.Endpoint,
  http: [port: 4001, compress: true],
  debug_errors: true,
  code_reloader: true,
  check_origin: false,
  watchers: []

# Watch static and templates for browser reloading.
config :drafteternal_api, DraftEternalApi.Web.Endpoint,
  live_reload: [
    patterns: [
      ~r{priv/static/.*(js|css|png|jpeg|jpg|gif|svg)$},
      ~r{priv/gettext/.*(po)$},
      ~r{lib/app_web/views/.*(ex)$},
      ~r{lib/app_web/templates/.*(eex)$}
    ]
  ]

# Do not include metadata nor timestamps in development logs
config :logger, :console, format: "[$level] $message\n"

# Set a higher stacktrace during development. Avoid configuring such
# in production as building large stacktraces may be expensive.
config :phoenix, :stacktrace_depth, 20

username = System.get_env("DB_USERNAME_DEV") || "postgres"
password = System.get_env("DB_PASSWORD_DEV") || "postgres"
database = System.get_env("DB_DRAFTETERNAL_NAME_DEV") || "drafteternal_api_dev"
hostname = System.get_env("DB_HOSTNAME_DEV") || "localhost"

url = System.get_env("DRAFTETERNAL_DB_URL") || "ecto://#{username}:#{password}@#{hostname}/#{database}"
ssl = !!System.get_env("DRAFTETERNAL_DB_URL")

# Configure your database
config :drafteternal_api, DraftEternalApi.Web.Repo,
  adapter: Ecto.Adapters.Postgres,
  url: url,
  ssl: ssl,
  pool_size: 10

config :drafteternal_api, DraftEternalApi.Web.WriteRepo,
  adapter: Ecto.Adapters.Postgres,
  url: url,
  ssl: ssl,
  pool_size: 10

username_commanded = System.get_env("DB_COMMANDED_USERNAME_DEV") || "postgres"
password_commanded = System.get_env("DB_COMMANDED_PASSWORD_DEV") || "postgres"
database_commanded = System.get_env("DB_COMMANDED_DRAFTETERNAL_NAME_DEV") || "drafteternal_commanded_api_dev"
hostname_commanded = System.get_env("DB_COMMANDED_HOSTNAME_DEV") || "localhost"

url_commanded = System.get_env("DRAFTETERNAL_COMMANDED_DB_URL") || "ecto://#{username_commanded}:#{password_commanded}@#{hostname_commanded}/#{database_commanded}"
ssl_commanded = !!System.get_env("DRAFTETERNAL_COMMANDED_DB_URL")

config :drafteternal_api, DraftEternalApi.EventStore,
  serializer: Commanded.Serialization.JsonSerializer,
  url: url_commanded,
  ssl: ssl_commanded,
  pool_size: 10
