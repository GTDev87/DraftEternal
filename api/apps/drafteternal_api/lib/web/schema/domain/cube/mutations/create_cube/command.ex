defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.Command do
  defstruct [
    id: "",
    name: "",
    description: "",
    creator_id: "",
    card_ids: [],
  ]

  use ExConstructor
  alias DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.Command

  def update(%Command{} = create_cube, cube) do
    %Command{create_cube |
      id: cube.id,
      name: cube.name,
      description: cube.description,
      creator_id: cube.creator_id,
      card_ids: cube.card_ids,
    }
  end
end