defmodule DraftEternalApi.Web.Lib.Resolver do
  def query_type(info) do
    info
    |> Map.get(:fields_cache, %{})
    |> Map.get({:mutation, []})
    |> case do
      nil -> :query
      _ -> :mutation
    end
  end
end
