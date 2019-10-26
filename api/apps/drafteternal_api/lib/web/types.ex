defmodule DraftEternalApi.Web.Types do
  use Absinthe.Schema.Notation

  import_types(DraftEternalApi.Web.Schema.Domain.User.Query)
  import_types(DraftEternalApi.Web.Schema.Domain.Card.Query)
  import_types(DraftEternalApi.Web.Schema.Domain.Cube.Query)
  import_types(DraftEternalApi.Web.Schema.Domain.Draft.Query)
  import_types(DraftEternalApi.Web.Schema.Domain.Pack.Query)
  import_types(DraftEternalApi.Web.Schema.Domain.Seat.Query)
end
