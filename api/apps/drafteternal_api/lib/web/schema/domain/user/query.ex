defmodule DraftEternalApi.Web.Schema.Domain.User.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :user do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.User, :id))
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.User, :id))
    end

    field :email, non_null(:string) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.User, :email))
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
        {:ok, []}
      end)
    end

    field :cubes, non_null(list_of(non_null(:cube))) do
      resolve(fn id, _, info ->
        {:ok, []}
      end)
    end
  end
end
