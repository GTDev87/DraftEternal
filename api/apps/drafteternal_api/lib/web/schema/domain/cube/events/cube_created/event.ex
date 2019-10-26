defmodule DraftEternalApi.Web.Schema.Domain.Cube.Events.CubeCreated.Event do
  @derive Jason.Encoder
  defstruct [
    id: "",
    name: "",
    description: "",
    creator_id: "",
    card_ids: [],
  ]
end