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
  def execute(%Aggregate{id: nil}, %CreateUser.Command{} = create) do
    %UserCreated.Event{
      id: create.id,
      email: create.email,
    }
  end
  # state mutators

  def apply(%Aggregate{} = user, %UserCreated.Event{} = created) do
    %Aggregate{user |
      id: created.id,
      email: created.email,
    }
  end
end