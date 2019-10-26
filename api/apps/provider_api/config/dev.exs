use Mix.Config


# For development, we disable any cache and enable
# debugging and code reloading.
#
# The watchers configuration can be used to run external
# watchers to your application. For example, we use it
# with brunch.io to recompile .js and .css sources.
config :provider_api, ProviderApi.Endpoint,
  http: [port: 4000],
  debug_errors: true,
  code_reloader: true,
  check_origin: false,
  watchers: []


# Do not include metadata nor timestamps in development logs
config :logger, :console, format: "[$level] $message\n", compile_time_purge_level: :info


# Set a higher stacktrace during development. Avoid configuring such
# in production as building large stacktraces may be expensive.
config :phoenix, :stacktrace_depth, 20

username = System.get_env("DB_USERNAME_DEV") || "postgres"
password = System.get_env("DB_PASSWORD_DEV") || ""
database = System.get_env("DB_PROVIDER_NAME_DEV") || "drafteternal_provider_api"
hostname = System.get_env("DB_HOSTNAME_DEV") || "localhost"

url = System.get_env("PROVIDER_DB_URL") || "ecto://#{username}:#{password}@#{hostname}/#{database}"

IO.puts("url = #{url}")

ssl = !!System.get_env("PROVIDER_DB_URL")

# Configure your database
config :provider_api, ProviderApi.Repo,
  adapter: Ecto.Adapters.Postgres,
  url: url,
  ssl: ssl,
  pool_size: 10
