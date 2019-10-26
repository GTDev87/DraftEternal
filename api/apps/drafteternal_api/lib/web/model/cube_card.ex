defmodule DraftEternalApi.Web.Model.CubeCard do
  use DraftEternalApi.Web, :model
  use DraftEternalApi.Web.Lib.EctoTypeUtils
  @model "cube_cards"
  @validated_fields [:id, :cube_id, :card_id]

  @primary_key {:id, :binary_id, autogenerate: false}
  @foreign_key_type Ecto.UUID
  schema @model do
    # field :id, Ecto.UUID
    belongs_to(:cube, DraftEternalApi.Web.Model.Cube, foreign_key: :cube_id)
    field(:card_id, :string)

    timestamps()
  end

  def_ecto_types(
    @model,
    id: String.t(),
    cube_id: String.t(),
    card_id: String.t(),
  )
end
