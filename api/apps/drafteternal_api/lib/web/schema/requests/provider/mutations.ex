defmodule DraftEternalApi.Web.Schema.Provider.Mutations do
  use Absinthe.Schema.Notation
  import_types(DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.GraphQL)

  object :provider_mutation do
    import_fields(:create_user)
  end
end
