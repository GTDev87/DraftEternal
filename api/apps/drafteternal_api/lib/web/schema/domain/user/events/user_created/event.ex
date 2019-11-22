defmodule DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Event do
  @derive Jason.Encoder
  defstruct [
    id: "",
    email: "",
  ]

  alias DraftEternalApi.Web.Schema.Domain.User.Aggregate
  alias DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Event

  def apply(%Aggregate{} = user, %Event{} = created) do
    %Aggregate{user |
      id: created.id,
      email: created.email,
    }
  end
end