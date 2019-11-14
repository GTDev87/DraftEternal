defmodule DraftEternalApi.Web.Schema.Domain.Cube.Query do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web
  alias DraftEternalApi.Web.Schema.Domain.Cube.Types

  import_types(DraftEternalApi.Web.Schema.Domain.Cube.Types)

  object :cube do
    field :id, non_null(:id) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.Cube, :id))
    end

    field :name, non_null(:string) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.Cube, :name))
    end

    field :description, non_null(:string) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.Cube, :description))
    end

    field :display, non_null(:display_type) do
      resolve(fn id, _, info ->
        info.context.loader
        |> Dataloader.load(:db, Web.Model.Cube, id)
        |> on_load(fn loader ->
          display_type =
            loader
            |> Dataloader.get(:db, Web.Model.Cube, id)
            |> Map.get(:display)
            |> Types.DisplayType.to_enum()

          {:ok, display_type}
        end)
      end)
    end

    field :creator_id, non_null(:id) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.Cube, :creator_id))
    end

    field :creator, non_null(:user) do
      resolve(Web.Lib.BatchUtils.get_field(Web.Model.Cube, :creator_id))
    end

    field :card_ids, non_null(list_of(non_null(:id))) do
      resolve(fn id, _, info ->
        Web.Lib.BatchUtils.batch_through_field(info.context.loader, id, Web.Model.CubeCard, :cube_id, fn (loader, cube_cards) ->
          card_ids = cube_cards |> Enum.map(fn cc -> cc.card_id end)
          {:ok, card_ids}
        end)
      end)
    end

    field :cards, non_null(list_of(non_null(:card))) do
      resolve(fn id, _, info ->
        Web.Lib.BatchUtils.batch_through_field(info.context.loader, id, Web.Model.CubeCard, :cube_id, fn (loader, cube_cards) ->
          card_ids = cube_cards |> Enum.map(fn cc -> cc.card_id end)
          {:ok, card_ids}
        end)
      end)
    end
  end
end
