defmodule DraftEternalApi.Web.Schema.Domain.Cube.Types do
  use Absinthe.Schema.Notation

  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  typed_enum DisplayType do
    value(:private, 0)
    value(:public, 1)
    value(:unlisted, 2)
  end
end