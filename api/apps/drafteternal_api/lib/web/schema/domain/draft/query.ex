defmodule DraftEternalApi.Web.Schema.Domain.Draft.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :draft do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :seed, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :cube_id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :cube, non_null(:cube) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :num_seats, non_null(:integer) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 0} end)
    end

    field :seats, non_null(list_of(non_null(:seat))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end

    field :seat_ids, non_null(list_of(non_null(:id))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end

    field :num_cards_in_pack, non_null(:integer) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 0} end)
    end

    field :cards, non_null(list_of(non_null(:card))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end

    field :card_ids, non_null(list_of(non_null(:id))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end
  end
end
