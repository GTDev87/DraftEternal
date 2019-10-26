defmodule ProviderApi.Repo.Migrations.CreateProviderIdentity do
  use Ecto.Migration

  def change do
    create table(:provider_identities, primary_key: false) do
      add :id, :binary_id, primary_key: true, null: false
      add :provider, :string
      add :name, :string
      add :nickname, :string
      add :picture, :string
      add :user_identifier, :string
      add :email, :string
      add :email_verified, :boolean, default: false, null: false
      add :given_name, :string
      add :family_name, :string

      timestamps()
    end
  end
end
