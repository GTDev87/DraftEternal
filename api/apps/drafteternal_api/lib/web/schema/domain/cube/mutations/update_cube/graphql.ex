defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.UpdateCube.GraphQL do
  use Absinthe.Schema.Notation
  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  alias DraftEternalApi.Web.Schema.Domain.Cube
  alias Cube.Mutations.UpdateCube
  alias Absinthe.Schema.Notation

  def_absinthe_input CubeInput do
    field(:id, non_null(:id))
    field(:name, non_null(:string))
    field(:description, non_null(:string))
    field(:display, non_null(:display_type), Cube.Types.Displaytype.t())
    field(:creator_id, non_null(:id))
    field(:card_ids, Notation.non_null(Notation.list_of(Notation.non_null(:id))))
  end

  object :update_cube do
    field :update_cube, type: :cube do
      arg(:cube, :cube_input)

      resolve(&execute/2)
    end
  end

  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.UpdateCube.Command

  @spec execute(%{cube: Input.CubeInput.t()}, DraftEternalApi.Guardian.Context.info()) :: {:error, any()} | {:ok, String}
  def execute(args, info) do
    uuid = args.cube.id

    cube_obj = Map.put(args.cube, :creator_id, info.context.current_user.id)

    %Command{
      id: cube_obj.id,
      name: cube_obj.name,
      description: cube_obj.description,
      display: cube_obj.display,
      creator_id: cube_obj.creator_id,
      card_ids: cube_obj.card_ids,
    }
    |> DraftEternalApi.Commanded.Application.dispatch(include_aggregate_version: true, consistency: :strong)
    |> case do
      {:ok, version} -> {:ok, uuid}
      :ok -> {:ok, uuid}
      reply -> reply
    end
  end
end