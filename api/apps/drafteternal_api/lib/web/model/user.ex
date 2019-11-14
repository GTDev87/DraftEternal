defmodule DraftEternalApi.Web.Model.User do
  use DraftEternalApi.Web, :model
  use DraftEternalApi.Web.Lib.EctoTypeUtils
  @model "users"
  @validated_fields [:id, :email]

  @primary_key {:id, :binary_id, autogenerate: false}
  @foreign_key_type Ecto.UUID
  schema @model do
    # field :id, Ecto.UUID
    field(:email, :string)

    timestamps()
  end

  def_ecto_types(
    @model,
    id: String.t(),
    email: String.t()
  )
end
