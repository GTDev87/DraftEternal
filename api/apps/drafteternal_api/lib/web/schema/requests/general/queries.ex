defmodule DraftEternalApi.Web.Schema.General.Queries do
  use Absinthe.Schema.Notation
  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  object :general_query do
    field(:cards, non_null(list_of(non_null(:card))), resolve: &get_cards/2)
    field(:cubes, non_null(list_of(non_null(:cube))), resolve: &get_cubes/2)
  end

  def get_json(filename) do
    filename
    |> File.read!
    |> Poison.decode!
  end

  def get_cards(args, _info) do
    all_cards =
      try do
        url = "https://eternalwarcry.com/content/cards/eternal-cards.json"
        response = HTTPoison.get!(url)
        Poison.decode!(response.body)
      rescue
        _ ->
          get_json("./all_cards.json")
      end

    non_nil_cards =
      all_cards
      |> Enum.filter(fn c -> Map.get(c, "EternalID") !== nil end)

    id_fn = fn c -> "#{Map.get(c, "SetNumber")}-#{Map.get(c, "EternalID")}" end;

    non_nil_cards
    |> Enum.map(fn c -> DraftEternalApi.Web.Lib.KeyValue.set(id_fn.(c), c) end)

    card_ids = Enum.map(non_nil_cards, id_fn)

    {:ok, card_ids}
  end

  def get_cubes(args, _info) do
    {
      :ok,
      DraftEternalApi.Web.Model.Cube.all([])
      |> Map.values()
      |> Enum.filter(fn c -> DraftEternalApi.Web.Schema.Domain.Cube.Types.DisplayType.to_enum(c.display) == :public end)
      |> Enum.sort(&(NaiveDateTime.compare(&1.inserted_at, &2.inserted_at) == :lt))
      |> Enum.map(fn c -> c.id end)
    }
  end
end
