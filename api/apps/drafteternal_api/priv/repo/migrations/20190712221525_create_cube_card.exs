defmodule DraftEternalApi.Repo.Migrations.CreateCubeCard do
  use Ecto.Migration

  def change do
    create table(:cube_cards, primary_key: false) do
      add :id, :binary_id, primary_key: true, null: false

      add :cube_id, references(:cubes, on_delete: :nothing, type: :binary_id), null: false

      add :card_id, :string

      timestamps()
    end

    create index(:cube_cards, [:cube_id], unique: false)
    create index(:cube_cards, [:card_id], unique: false)
  end
end
