defmodule DraftEternalApi.Web.Schema.Domain.User.Aggregate do
  defstruct [
    :id,
    :email,
    :profile_id,
  ]

  alias DraftEternalApi.Web.Schema.Domain.User.Aggregate
  alias DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser
  alias DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated

  @doc """
  Publish an article
  """
  def execute(%Aggregate{id: nil} = agg, %CreateUser.Command{} = create) do
    CreateUser.Command.execute(agg, create)
  end
  # state mutators

  def apply(%Aggregate{} = agg, %UserCreated.Event{} = created) do
    UserCreated.Event.apply(agg, created)
  end
end