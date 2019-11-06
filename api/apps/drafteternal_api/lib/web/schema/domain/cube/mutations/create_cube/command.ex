defmodule DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.Command do
  defstruct [
    id: "",
    name: "",
    description: "",
    display: "",
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
      display: cube.display,
      creator_id: cube.creator_id,
      card_ids: cube.card_ids,
    }
  end
end