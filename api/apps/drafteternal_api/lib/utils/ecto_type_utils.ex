defmodule DraftEternalApi.Web.Lib.EctoTypeUtils do
  defmacro __using__(_env) do
    quote do
      import DraftEternalApi.Web.Lib.EctoTypeUtils
    end
  end

  def pluralize(singular_atom) do
    singular_atom
    |> Atom.to_string()
    |> (fn w -> "#{w}s" end).()
    |> String.to_atom()
  end

  defmacro def_ecto_types(model_name, attrs \\ []) do
    optional_keys = Enum.map(attrs, fn {k, v} -> {{:optional, [], [k]}, v} end)
    keys = Keyword.keys(attrs)

    quote do
      alias __MODULE__, as: MODEL

      @type t :: %MODEL{unquote_splicing(attrs)}
      @type input :: %{unquote_splicing(optional_keys)}
      @fields unquote(keys)

      def name, do: unquote(model_name)

      # def query(queryable, _params) do
      #   require Logger
      #   Logger.debug "queryable runnning #{inspect queryable}"
      #   queryable
      # end

      @spec changeset(MODEL.t(), MODEL.input()) :: Changeset.t()
      def changeset(struct, params \\ %{}),
        do:
          DraftEternalApi.Web.Lib.EctoUtils.changeset_in(struct, params, @fields, @validated_fields)

      Enum.each(unquote(keys), fn field_name ->
        Module.eval_quoted(
          __MODULE__,
          quote do
            @spec unquote(pluralize(field_name))([String.t()], keyword()) :: %{
                    String.t() => Model.t()
                  }
            def unquote(pluralize(field_name))(ids, options),
              do: DraftEternalApi.Web.Lib.EctoUtils.ids_in(MODEL, unquote(field_name), ids, options)

            @spec unquote(field_name)(String.t(), keyword()) :: MODEL.t() | nil
            def unquote(field_name)(id, options \\ []),
              do: DraftEternalApi.Web.Lib.EctoUtils.id_in(MODEL, unquote(field_name), id, options)
          end
        )
      end)

      @spec all(keyword()) :: %{String.t() => Model.t()}
      def all(options), do: DraftEternalApi.Web.Lib.EctoUtils.all_in(MODEL, options)

      defmodule Multi do
        @spec insert(Ecto.Multi.t(), MODEL.t(), keyword()) :: Ecto.Multi.t()
        def insert(multi, struct, options \\ []),
          do: DraftEternalApi.Web.Lib.EctoUtils.Multi.insert_in(MODEL, multi, struct, options)

        @spec delete(Ecto.Multi.t(), MODEL.t(), keyword()) :: Ecto.Multi.t()
        def delete(multi, struct, options \\ []),
          do: DraftEternalApi.Web.Lib.EctoUtils.Multi.delete_in(MODEL, multi, struct, options)

        @spec update(Ecto.Multi.t(), MODEL.t(), MODEL.input(), keyword()) :: Ecto.Multi.t()
        def update(multi, struct, params, options \\ []),
          do: DraftEternalApi.Web.Lib.EctoUtils.Multi.update_in(MODEL, multi, struct, params, options)

        @spec upsert(Ecto.Multi.t(), MODEL.t(), MODEL.t(), keyword()) :: Ecto.Multi.t()
        def upsert(multi, struct, params, options \\ []),
          do: DraftEternalApi.Web.Lib.EctoUtils.Multi.upsert_in(MODEL, multi, struct, params, options)
      end
    end
  end
end
