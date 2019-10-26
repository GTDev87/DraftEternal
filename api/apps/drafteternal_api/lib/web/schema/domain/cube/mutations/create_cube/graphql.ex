defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.GraphQL do
  use Absinthe.Schema.Notation
  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube
  alias Absinthe.Schema.Notation

  def_absinthe_input CubeInput do
    field(:id, non_null(:id))
    field(:name, non_null(:string))
    field(:description, non_null(:string))
    field(:creator_id, non_null(:id))
    field(:card_ids, Notation.non_null(Notation.list_of(Notation.non_null(:id))))
  end

  object :create_cube do
    field :create_cube, type: :cube do
      arg(:cube, :cube_input)

      resolve(&execute/2)
    end
  end

  @spec execute(%{cube: Input.CubeInput.t()}, DraftEternalApi.Guardian.Context.info()) :: {:error, any()} | {:ok, String}
  def execute(args, _info) do
    uuid = args.cube.id

    args
    |> CreateCube.Command.new()
    |> CreateCube.Command.update(args.cube)
    |> DraftEternalApi.Web.Schema.Router.dispatch(include_aggregate_version: true, consistency: :strong)
    |> case do
      {:ok, version} -> {:ok, uuid}
      :ok -> {:ok, uuid}
      reply -> reply
    end
  end
end