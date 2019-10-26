defmodule DraftEternalApi.Web.Schema.Domain.Pack.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :pack do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :draft_id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :draft, non_null(:draft) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :cube, non_null(:draft) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :cube_id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :seed, non_null(:string) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :pack_number, non_null(:integer) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 1} end)
    end

    field :card_ids, non_null(list_of(non_null(:id))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 1} end)
    end

    field :cards, non_null(list_of(non_null(:card))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 1} end)
    end
  end
end
