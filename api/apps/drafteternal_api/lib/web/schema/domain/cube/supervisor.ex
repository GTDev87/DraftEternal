defmodule DraftEternalApi.Web.Schema.Domain.Cube.Supervisor do
  use Supervisor

  alias DraftEternalApi.Web.Schema.Domain.Cube.Projector
  
  def start_link(arg) do
    Supervisor.start_link(__MODULE__, arg, name: __MODULE__)
  end

  def init(_arg) do
    Supervisor.init([
      Projector
    ], strategy: :one_for_one)
  end
end
