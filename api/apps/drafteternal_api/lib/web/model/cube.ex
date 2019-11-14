defmodule DraftEternalApi.Web.Model.Cube do
  use DraftEternalApi.Web, :model
  use DraftEternalApi.Web.Lib.EctoTypeUtils
  @model "cubes"
  @validated_fields [:id, :name, :description, :creator_id]

  @primary_key {:id, :binary_id, autogenerate: false}
  @foreign_key_type Ecto.UUID
  schema @model do
    # field :id, Ecto.UUID
    field(:name, :string)
    field(:description, :string)
    field(:display, :string)
    belongs_to(:user, DraftEternalApi.Web.Model.User, foreign_key: :creator_id)

    timestamps()
  end

  def_ecto_types(
    @model,
    id: String.t(),
    name: String.t(),
    display: String.t(),
    description: String.t(),
    creator_id: String.t(),
  )
end
