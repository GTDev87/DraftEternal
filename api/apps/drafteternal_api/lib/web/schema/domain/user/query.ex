defmodule DraftEternalApi.Web.Schema.Domain.User.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :user do
    field :id, non_null(:id) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.User, :id))
    end

    field :email, non_null(:string) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.User, :email))
    end

    field :collection_ids, non_null(list_of(non_null(:id))) do
      resolve(fn id, _, info ->
        {:ok, []}
      end)
    end

    field :collection, non_null(list_of(non_null(:card))) do
      resolve(fn id, _, info ->
        {:ok, []}
      end)
    end

    field :cube_ids, non_null(list_of(non_null(:id))) do
      resolve(fn id, _, info ->
        Web.Lib.BatchUtils.batch_through_field(info.context.loader, id, Web.Model.Cube, :creator_id, fn (loader, cubes) ->
          {:ok, cubes |> Enum.map(fn q -> q.id end)}
        end)
      end)
    end

    field :cubes, non_null(list_of(non_null(:cube))) do
      resolve(fn id, _, info ->
        Web.Lib.BatchUtils.batch_through_field(info.context.loader, id, Web.Model.Cube, :creator_id, fn (loader, cubes) ->
          {:ok, cubes |> Enum.map(fn q -> q.id end)}
        end)
      end)
    end
  end
end
