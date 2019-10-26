defmodule DraftEternalApi.Web.Schema.Domain.Seat.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :seat do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :draft, non_null(:draft) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :draft_id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, "123"} end)
    end

    field :seat_number, non_null(:integer) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, 1} end)
    end

    field :selected_cards, non_null(list_of(non_null(:card))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end

    field :selected_cards, non_null(list_of(non_null(:id))) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info -> {:ok, []} end)
    end
  end
end
