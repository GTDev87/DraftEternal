defmodule DraftEternalApi.Web.Schema.Member.Mutations do
  use Absinthe.Schema.Notation
  import_types(DraftEternalApi.Web.Schema.Domain.Cube.Mutations.CreateCube.GraphQL)

  object :member_mutation do
    import_fields(:create_cube)
  end
end