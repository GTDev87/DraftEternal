defmodule DraftEternalApi.Web.Lib.AbsintheInputUtils do
  use Absinthe.Schema.Notation

  defmacro __using__(_env) do
    quote do
      import DraftEternalApi.Web.Lib.AbsintheInputUtils
    end
  end

  def orListFields([h]), do: h
  def orListFields([h | t]), do: {:|, [], [h, orListFields(t)]}

  def atom_to_type(:id), do: {:|, [], [atom_to_type(:string), atom_to_type(:integer)]}
  def atom_to_type(:float), do: {:float, [], []}
  def atom_to_type(:integer), do: {:non_neg_integer, [], []}
  def atom_to_type(:string), do: {:binary, [], []}
  def atom_to_type(:boolean), do: {:boolean, [], []}
  def atom_to_type(a), do: a

  def handle_field_types({:non_null, _, [v]}), do: atom_to_type(v)
  def handle_field_types(v), do: {:|, [], [atom_to_type(v), nil]}

  def generate_types({_, _, [k, v]}), do: {k, handle_field_types(v)}
  def generate_types({_, _, [k, _v, type]}), do: {k, type}

  def get_block({:__block__, _, res}), do: res
  def get_block(res), do: [res]

  def get_absinthe_fields({a, b, [k | [v | _]]}), do: {a, b, [k, v]}

  def keys_from_absinthe({_, _, [k | _]}), do: k

  def pairs_from_absinthe({_, _, [k | [v | _]]}), do: {k, v}

  def value_fields({a, b, [v, _]}), do: {a, b, [v]}

  def module_name_to_atom({_, _, [captal_name]}),
    do:
      captal_name
      |> Atom.to_string()
      |> Macro.underscore()
      |> String.to_atom()

  defmacro typed_enum(name, do: fields) do
    require Logger
    block_fields = fields |> get_block()
    value_fields = Enum.map(block_fields, &value_fields/1)
    keys = Enum.map(block_fields, &keys_from_absinthe/1)
    pairs = Enum.map(block_fields, &pairs_from_absinthe/1)

    atom_name = module_name_to_atom(name)
    type_fields = orListFields(keys)

    quote do
      defmodule unquote(name) do
        @type t :: unquote(type_fields)

        Enum.each(unquote(pairs), fn {enum, val} ->
          Module.eval_quoted(
            __MODULE__,
            quote do
              def to_enum(unquote(val)), do: unquote(enum)
              def to_val(unquote(enum)), do: unquote(val)
            end
          )
        end)

        def to_enum(_), do: nil
        def to_val(_), do: nil
      end

      enum unquote(atom_name) do
        (unquote_splicing(value_fields))
      end
    end
  end

  defmacro def_absinthe_input(name, do: fields) do
    block_fields = fields |> get_block()
    absinthe_fields = Enum.map(block_fields, &get_absinthe_fields/1)
    type_fields = Enum.map(block_fields, &generate_types/1)
    keys = Enum.map(absinthe_fields, &keys_from_absinthe/1)
    atom_name = module_name_to_atom(name)

    quote do
      defmodule unquote(name) do
        defstruct unquote(keys)
        @enforce_keys unquote(keys)

        @type t :: %__MODULE__{unquote_splicing(type_fields)}
      end

      input_object unquote(atom_name) do
        (unquote_splicing(absinthe_fields))
      end
    end
  end
end
