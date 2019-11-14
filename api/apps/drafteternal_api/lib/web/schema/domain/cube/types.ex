defmodule DraftEternalApi.Web.Schema.Domain.Cube.Types do
  use Absinthe.Schema.Notation

  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  typed_enum DisplayType do
    value(:private, "private")
    value(:public, "public")
    value(:unlisted, "unlisted")
  end
end