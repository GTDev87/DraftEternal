defmodule DraftEternalApi.Web do
  @moduledoc """
  A module that keeps using definitions for controllers,
  views and so on.

  This can be used in your application as:

      use DraftEternalApi.Web.Web, :controller
      use DraftEternalApi.Web.Web, :view

  The definitions below will be executed for every view,
  controller, etc, so keep them short and clean, focused
  on imports, uses and aliases.

  Do NOT define functions inside the quoted expressions
  below.
  """

  def model do
    quote do
      use Ecto.Schema

      import Ecto
      import Ecto.Changeset
      import Ecto.Query

      # maybe move this
      def query(queryable, _params) do
        queryable
      end

      def data() do
        Dataloader.Ecto.new(DraftEternalApi.Web.Repo, query: &query/2)
      end
    end
  end

  def router do
    quote do
      use Phoenix.Router
    end
  end

  def channel do
    quote do
      use Phoenix.Channel

      alias DraftEternalApi.Web.Repo
      import Ecto
      import Ecto.Query
      import DraftEternalApi.Web.Gettext
    end
  end

  @doc """
  When used, dispatch to the appropriate controller/view/etc.
  """
  defmacro __using__(which) when is_atom(which) do
    apply(__MODULE__, which, [])
  end
end
