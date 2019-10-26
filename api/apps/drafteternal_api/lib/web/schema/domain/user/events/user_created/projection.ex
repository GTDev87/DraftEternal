defmodule DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Projection do
  alias DraftEternalApi.Web.Schema.Domain.User.Events.UserCreated.Event

  def execute(multi, %Event{} = created) do
    DraftEternalApi.Web.Model.User.Multi.insert(multi, %DraftEternalApi.Web.Model.User{
      id: created.id,
      email: created.email
    })
  end
end
