defmodule ProviderApi.User do
  use ProviderApi.Web, :model

  @primary_key {:id, Ecto.UUID, autogenerate: false}
  schema "users" do
    field :email, :string

    timestamps()
  end

  @doc """
  Builds a changeset based on the `struct` and `params`.
  """
  def changeset(struct, params \\ %{}) do
    struct
    |> cast(params, [:id, :email])
    |> validate_required([:id, :email])
    |> unique_constraint(:email)
    |> unique_constraint(:id)
  end
end
