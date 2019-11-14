defmodule DraftEternalApi.Repo.Migrations.CreateCube do
  use Ecto.Migration

  def change do
    create table(:cubes, primary_key: false) do
      add :id, :binary_id, primary_key: true, null: false
      add :name, :string
      add :display, :string
      add :description, :string
      add :creator_id, references(:users, on_delete: :nothing, type: :binary_id), null: false

      timestamps()
    end

    create index(:cubes, [:creator_id], unique: false)
  end
end
