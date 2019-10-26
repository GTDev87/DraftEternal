defmodule DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.Command do
  defstruct [
    id: "",
    email: "",
  ]

  use ExConstructor
  alias DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.Command

  def update(%Command{} = create_post, user) do
    %Command{create_post |
      id: user.id,
      email: user.email
    }
  end
end
