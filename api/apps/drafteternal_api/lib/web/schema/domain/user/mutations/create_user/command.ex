defmodule DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.Command do
  defstruct [
    id: "",
    email: "",
  ]

  use ExConstructor
  alias DraftEternalApi.Web.Schema.Domain.User.Aggregate
  alias DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.Command
  alias DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Event

  def execute(%Aggregate{id: nil} = agg, %Command{} = create) do
    %Event{
      id: create.id,
      email: create.email,
    }
  end
end
