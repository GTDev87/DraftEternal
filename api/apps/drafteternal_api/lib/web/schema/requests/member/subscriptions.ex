defmodule DraftEternalApi.Web.Schema.Member.Subscriptions do
  use Absinthe.Schema.Notation

  import_types(DraftEternalApi.Web.Schema.Domain.User.Subscription)

  object :member_subscription do
    ## ad authentication in here somehow
    import_fields(:user)
  end
end
