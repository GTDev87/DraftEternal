defmodule DraftEternalApi.Web.Lib.RepoUtils do
  @spec create_args(any(), integer()) :: [any()]
  def create_args(_, 0),
    do: []

  def create_args(fn_mdl, arg_cnt),
    do: Enum.map(1..arg_cnt, &Macro.var(:"arg#{&1}", fn_mdl))
end
