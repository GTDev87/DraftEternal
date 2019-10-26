defmodule DraftEternalApi.Web.Lib.BatchUtils do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  # TODO need a way to handle read write repo
  def get_field_with_loader(loader, model_module, id, field) do

    cached_item = get_from_loader_by_id(loader, model_module, id)

    loader
    |> (fn (loader) ->
      case cached_item do
        nil -> Dataloader.load_many(loader, :db, {{:many, model_module}, %{}}, [id])
        _ -> loader
      end
    end).()
    |> on_load(fn loader ->
      case cached_item do
        nil ->
          cashed_res =
            loader
            |> Dataloader.get_many(:db, {{:many, model_module}, %{}}, [id])
            |> List.flatten

          {
            :ok,
            case cashed_res do
              nil -> nil
              [] -> nil
              a -> a |> List.first |> Map.get(field)
            end
          }
        _ -> {:ok, Map.get(cached_item, field)}
      end
    end)
  end

  def get_from_loader_by_id(loader, model_module, id) do
    loader.sources.db.results
    |> Enum.filter(fn ({{_, _, model, _, _, _}, val}) -> model == model_module end)
    |> Enum.map(fn ({key, {:ok, val}}) ->
      case key do
        {_, _, _, :many, _, _} -> List.flatten(Map.values(val))
        {_, _, _, :one, _, _} -> Map.values(val)
      end
    end)
    |> List.flatten
    |> Enum.find(fn (value) -> value.id == id end)
  end

  def get_field(model_module, field) do
    fn id, _, info ->
      get_field_with_loader(info.context.loader, model_module, id, field)
    end
  end

  def batch_through_field(loader, ids, model_module, field, callback) when is_list(ids) do
    query_ids = Enum.map(ids, fn id -> [{field, id}] end)

    loader
    |> Dataloader.load_many(:db, {{:many, model_module}, %{}}, query_ids)
    |> on_load(fn loader ->
      res_objs =
        loader
        |> Dataloader.get_many(:db, {{:many, model_module}, %{}}, query_ids)
        |> List.flatten

      callback.(loader, res_objs)
    end)
  end
  def batch_through_field(loader, id, model_module, field, callback) do
    batch_through_field(loader, [id], model_module, field, callback)
  end


  defp batch_map_priv(loader, [], acc, _, callback) do
    callback.(loader, acc)
  end
  defp batch_map_priv(loader, [head | tail], acc, fun, callback) do
    fun.(loader, head, fn (loader, resp) ->
      batch_map_priv(loader, tail, [resp | acc], fun, callback)
    end)
  end

  def batch_map(loader, collection, fun, callback) do
    batch_map_priv(loader, collection, [], fun, callback)
  end
end
