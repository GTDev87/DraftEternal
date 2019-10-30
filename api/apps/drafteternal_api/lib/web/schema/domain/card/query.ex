defmodule DraftEternalApi.Web.Schema.Domain.Card.Query do
  use Absinthe.Schema.Notation
  use DraftEternalApi.Web.Lib.AbsintheInputUtils
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  typed_enum InfluenceType do
    value(:fire, "F")
    value(:time, "T")
    value(:justice, "J")
    value(:primal, "P")
    value(:shadow, "S")
  end

  object :card do
    field :id, non_null(:id) do
      resolve(fn id, _, info ->
        {:ok, id }
      end)
    end

    field :eternal_id, non_null(:id) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("EternalID")
        }
      end)
    end

    field :set_number, non_null(:integer) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("SetNumber")
        }
      end)
    end

    field :name, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Name")
        }
      end)
    end

    field :card_text, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("CardText") || ""
        }
      end)
    end

    field :cost, non_null(:integer) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Cost")
        }
      end)
    end

    field :influence, non_null(list_of(non_null(:influence_type))) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Influence")
          |> String.replace("{", "")
          |> String.replace("}", "")
          |> String.split("")
          |> Enum.filter(fn a -> a != "" end)
          |> Enum.map(&InfluenceType.to_enum/1)
        }
      end)
    end

    field :colors, non_null(list_of(non_null(:influence_type))) do
      resolve(fn id, _, info ->
        colors =
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Influence")
          |> String.replace("{", "")
          |> String.replace("}", "")
          |> String.split("")
          |> Enum.filter(fn a -> a != "" end)
          |> Enum.group_by(fn a -> a end)
          |> Map.keys
          |> Enum.map(&InfluenceType.to_enum/1)

        {:ok, colors}
      end)
    end

    field :attack, :integer do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Attack")
        }
      end)
    end

    field :health, :integer do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Health")
        }
      end)
    end

    field :rarity, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Rarity")
        }
      end)
    end

    field :card_type, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Type")
        }
      end)
    end

    field :image_url, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("ImageUrl")
        }
      end)
    end

    field :thumbnail_url, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("ImageUrl")
          |> String.replace("full", "icon")
          |> String.replace("png", "jpg")
        }
      end)
    end

    field :details_url, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("DetailsUrl")
        }
      end)
    end

    field :deck_buildable, non_null(:string) do
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("DeckBuildable")
        }
      end)
    end
  end
end