defmodule DraftEternalApi.Web.Lib.EctoUtils do
  use DraftEternalApi.Web, :model

  def validate_not_nil(changeset, fields) do
    Enum.reduce(fields, changeset, fn field, changeset ->
      if get_field(changeset, field) == nil do
        add_error(changeset, field, "nil")
      else
        changeset
      end
    end)
  end

  defp query_id_map(query, options),
    do:
      options
      |> Keyword.get(:query_type, :query)
      |> DraftEternalApi.Web.ReadWriteRepo.all(query)
      |> Map.new(&{&1.id, &1})

  def ids_in(model_module, field_name, ids, options) do
    uniq_ids = Enum.uniq(ids)
    require Logger

    Logger.info(
      "req(mod, field, uniq) = (#{inspect(model_module)}, #{inspect(field_name)}, #{
        inspect(uniq_ids)
      })"
    )

    query =
      from(
        p in model_module,
        where: field(p, ^field_name) in ^uniq_ids,
        select: p
      )

    query_id_map(query, options)
  end

  def id_in(model_module, field_name, id, options \\ []),
    do:
      model_module
      |> ids_in(field_name, [id], options)
      |> Map.values()
      |> List.first()

  def all_in(model_module, options \\ []) do
    query = from(p in model_module, select: p)

    query_id_map(query, options)
  end

  def changeset_in(struct, params, fields, validated) do
    struct
    |> Ecto.Changeset.change(%{})
    |> Map.put(:empty_values, [])
    |> cast(params, fields)
    |> validate_not_nil(validated)
  end

  defmodule Multi do
    @spec insert_in(any(), Ecto.Multi.t(), any(), keyword()) :: Ecto.Multi.t()
    def insert_in(model_module, multi, prev_struct, options \\ []) do
      changeset = model_module.changeset(struct(model_module), Map.from_struct(prev_struct))

      Ecto.Multi.insert(multi, :"insert_#{model_module.name()}_#{options[:suffix] || ""}", changeset)
    end

    @spec delete_in(any(), Ecto.Multi.t(), any(), keyword()) :: Ecto.Multi.t()
    def delete_in(model_module, multi, prev_struct, options \\ []) do
      changeset = model_module.changeset(struct(model_module), Map.from_struct(prev_struct))

      # the ok is a problem
      {:ok, changeset} = apply_action(changeset, :delete)

      Ecto.Multi.delete(multi, :"delete_#{model_module.name()}_#{options[:suffix] || ""}", changeset)
    end

    @spec update_in(atom(), Ecto.Multi.t(), any(), any(), keyword()) :: Ecto.Multi.t()
    def update_in(model_module, multi, prev_struct, params, options \\ []) do
      changeset = model_module.changeset(prev_struct, params)

      Ecto.Multi.update(multi, :"update_#{model_module.name()}_#{options[:suffix] || ""}", changeset)
    end

    @spec upsert_in(any(), Ecto.Multi.t(), any(), any(), keyword()) :: Ecto.Multi.t()
    def upsert_in(model_module, multi, prev_struct, struct_params, options \\ []) do
      case(prev_struct) do
        nil ->
          insert_in(model_module, multi, struct_params, options)

        prev_struct ->
          update_in(model_module, multi, prev_struct, Map.from_struct(struct_params), options)
      end
    end

    @spec delete_all_in(any(), Ecto.Multi.t(), any(), keyword()) :: Ecto.Multi.t()
    def delete_all_in(model_module, multi, query, options \\ []) do
      Ecto.Multi.delete_all(multi, :"update_#{model_module.name()}_#{options[:suffix] || ""}", query)
    end
  end
end
