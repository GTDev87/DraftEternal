defmodule ProviderApi.Repo do

  use Ecto.Repo, otp_app: :provider_api, adapter: Ecto.Adapters.Postgres
  def init(_type, config) do
    url = Keyword.get(config, :url)

    options = DatabaseUrl.parse(url)

    new_config =
      config 
      |> Keyword.put(:username, Keyword.get(options, :username, ""))
      |> Keyword.put(:password, Keyword.get(options, :password, ""))
      |> Keyword.put(:hostname, Keyword.get(options, :host, ""))
      |> Keyword.put(:database, Keyword.get(options, :database, ""))
      |> Keyword.delete(:url)

    {:ok, new_config}
  end
end
