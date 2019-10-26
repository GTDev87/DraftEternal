defmodule ProviderApi.ProviderIdentity do
  use ProviderApi.Web, :model

  @primary_key {:id, Ecto.UUID, autogenerate: false}
  schema "provider_identities" do
    field(:provider, :string)
    field(:name, :string)
    field(:nickname, :string)
    field(:picture, :string)
    field(:user_identifier, :string)

    field(:email, :string)
    field(:email_verified, :boolean, default: false, null: false)
    field(:given_name, :string)
    field(:family_name, :string)

    timestamps()
  end

  def ueberauth_to_email(ueberauth_auth) do
    case ueberauth_auth.provider do
      :google ->
        %{info: %{email: email}} = ueberauth_auth
        email

      _ ->
        "bad email"
    end
  end

  def ueberauth_to_provider_identity(ueberauth_auth) do
    case ueberauth_auth.provider do
      :google ->
        %{
          extra: %{
            raw_info: %{
              user: user
            }
          },
          info: %{
            name: name,
            first_name: first_name,
            last_name: last_name,
            nickname: nickname,
            image: image,
            email: email
          },
          provider: provider,
          uid: uid
        } = ueberauth_auth

        email_verified = Map.get(user, "email_verified", "")
        given_name = Map.get(user, "given_name", "")
        family_name = Map.get(user, "family_name", "")

        %{
          provider: Atom.to_string(provider),
          # gross
          name: if(name == "", do: email, else: name || email),
          nickname: if(nickname == "", do: email, else: nickname || email),
          picture: image,
          user_identifier: Atom.to_string(provider) <> "|" <> uid,
          email: email,
          email_verified: email_verified,
          given_name: given_name,
          family_name: family_name
        }

      _ ->
        %{}
    end
  end

  @doc """
  Builds a changeset based on the `struct` and `params`.
  """
  def changeset(struct, params \\ %{}) do
    struct
    |> cast(params, [
      :id,
      :provider,
      :name,
      :nickname,
      :picture,
      :user_identifier,
      :email,
      :email_verified,
      :given_name,
      :family_name
    ])
    |> validate_required([:id, :provider, :name, :nickname, :picture, :user_identifier, :email])
    |> unique_constraint(:user_identifier)
    |> unique_constraint(:id)
  end
end
