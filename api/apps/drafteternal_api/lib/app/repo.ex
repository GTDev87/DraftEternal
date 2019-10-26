defmodule DraftEternalApi.Web.Repo do
  use Ecto.Repo, otp_app: :drafteternal_api, adapter: Ecto.Adapters.Postgres
  require Logger
  def init(_type, config) do
    url = Keyword.get(config, :url)

    options = DatabaseUrl.parse(url)

    new_config =
      config 
      |> Keyword.put(:username, Keyword.get(options, :username))
      |> Keyword.put(:password, Keyword.get(options, :password))
      |> Keyword.put(:hostname, Keyword.get(options, :host))
      |> Keyword.put(:database, Keyword.get(options, :database))
      |> Keyword.delete(:url)
    
    {:ok, new_config}
  end
end

defmodule DraftEternalApi.Web.WriteRepo do
  use Ecto.Repo, otp_app: :drafteternal_api, adapter: Ecto.Adapters.Postgres
  require Logger
  def init(_type, config) do
    url = Keyword.get(config, :url)

    options = DatabaseUrl.parse(url)

    new_config =
      config 
      |> Keyword.put(:username, Keyword.get(options, :username))
      |> Keyword.put(:password, Keyword.get(options, :password))
      |> Keyword.put(:hostname, Keyword.get(options, :host))
      |> Keyword.put(:database, Keyword.get(options, :database))
      |> Keyword.delete(:url)
    
    {:ok, new_config}
  end
end

defmodule DraftEternalApi.Web.ReadWriteRepo do
  require Logger

  DraftEternalApi.Web.Repo.__info__(:functions)
  |> Enum.each(fn {func_name, arity} ->
    fn_args = DraftEternalApi.Web.Lib.RepoUtils.create_args(DraftEternalApi.Web.Repo, arity)

    all_fn_args =
      [Macro.var(:type, nil)] ++
        DraftEternalApi.Web.Lib.RepoUtils.create_args(DraftEternalApi.Web.Repo, arity)

    def unquote(:"#{func_name}")(unquote_splicing(all_fn_args)) do
      case type do
        :mutation -> DraftEternalApi.Web.WriteRepo
        _ -> DraftEternalApi.Web.Repo
      end
      |> apply(unquote(func_name), unquote(fn_args))
    end
  end)
end
