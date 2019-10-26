defmodule DraftEternalApi.Repo.Migrations.CreateUser do
  use Ecto.Migration

  def change do
    create table(:users, primary_key: false) do
      add :id, :binary_id, primary_key: true, null: false
      add :email, :string

      timestamps()
    end

    create index(:users, [:email], unique: true)
  end
end
