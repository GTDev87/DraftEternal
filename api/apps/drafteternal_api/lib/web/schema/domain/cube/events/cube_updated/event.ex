defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Event do
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
  alias DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeUpdated.Event

  def apply(%Aggregate{} = cube, %Event{} = updated) do
    %Aggregate{cube |
      id: updated.id,
      name: updated.name,
      description: updated.description,
      display: updated.display,
      creator_id: updated.creator_id,
      card_ids: updated.card_ids,
    }
  end
end