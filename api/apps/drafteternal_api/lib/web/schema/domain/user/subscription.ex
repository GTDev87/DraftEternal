defmodule DraftEternalApi.Web.Schema.Domain.User.Subscription do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :user do
    field :user, :user do
      config fn _args, _info ->
        {:ok, topic: true}
      end
    end
  end
end
