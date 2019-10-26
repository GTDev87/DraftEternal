defmodule DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Event do
  @derive Jason.Encoder
  defstruct [
    id: "",
    email: "",
  ]
end