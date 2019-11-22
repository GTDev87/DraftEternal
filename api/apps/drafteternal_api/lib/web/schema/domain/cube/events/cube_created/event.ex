defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event do
  @derive Jason.Encoder
  defstruct [
    id: "",
    name: "",
    description: "",
    display: "",
    creator_id: "",
    card_ids: [],
  ]

  alias DraftEternalApi.Web.Schema.Domain.Cube.Aggregate
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event

  def apply(%Aggregate{} = cube, %Event{} = created) do
    %Aggregate{cube |
      id: created.id,
      name: created.name,
      description: created.description,
      display: created.display,
      creator_id: created.creator_id,
      card_ids: created.card_ids,
    }
  end
end