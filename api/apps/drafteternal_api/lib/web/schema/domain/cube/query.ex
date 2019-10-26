defmodule DraftEternalApi.Web.Schema.Domain.Cube.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :cube do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :name, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :description, non_null(:string) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :creator_id, list_of(non_null(:id)) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :creator, list_of(non_null(:user)) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :card_ids, list_of(non_null(:id)) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :cards, list_of(non_null(:card)) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end
  end
end
