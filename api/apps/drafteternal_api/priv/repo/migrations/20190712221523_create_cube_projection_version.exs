defmodule CreateCubeProjectionVersions do
  use Ecto.Migration
  @disable_ddl_transaction true

  @prefix "cube"

  def up do
    execute("CREATE SCHEMA #{@prefix}")

    create table(:projection_versions, primary_key: false, prefix: @prefix) do
      add(:projection_name, :text, primary_key: true)
      add(:last_seen_event_number, :bigint)

      timestamps(type: :naive_datetime_usec)
    end
  end

  def down do
    drop(table(:projection_versions, prefix: @prefix))

    execute("DROP SCHEMA #{@prefix}")
  end
end
