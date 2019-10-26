defmodule DraftEternalApi.Web.Schema.Domain.Cube.Subscription do
  use Absinthe.Schema.Notation
  import Absinthe.Resolution.Helpers, only: [on_load: 2]

  alias DraftEternalApi.Web

  object :cube do
    field :cube, :cube do
      config fn _args, _info ->
        {:ok, topic: true}
      end
    end
  end
end
