defmodule DraftEternalApi.Web.Schema.Domain.Card.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :card do
    field :id, non_null(:id) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
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
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
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
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
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
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("CardText")
        }
      end)
    end

    field :cost, non_null(:integer) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Cost")
        }
      end)
    end

    field :influence, non_null(:string) do
      # resolve(Web.Lib.BatchUtils.get_field(Web.Model.Profile, :id))
      resolve(fn id, _, info ->
        {
          :ok,
          id
          |> DraftEternalApi.Web.Lib.KeyValue.get
          |> Map.get("Influence")
        }
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