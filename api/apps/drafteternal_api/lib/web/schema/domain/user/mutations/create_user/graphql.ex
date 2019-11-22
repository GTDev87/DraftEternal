defmodule DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.GraphQL do
  use Absinthe.Schema.Notation
  use DraftEternalApi.Web.Lib.AbsintheInputUtils

  alias DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser

  def_absinthe_input UserInput do
    field(:id, non_null(:id))
    field(:email, non_null(:string))
  end

  object :create_user do
    field :create_user, type: :user do
      arg(:user, :user_input)

      resolve(&execute/2)
    end
  end

  alias DraftEternalApi.Web.Schema.Domain.User.Mutations.CreateUser.Command

  @spec execute(%{user: Input.UserInput.t()}, DraftEternalApi.Guardian.Context.info()) :: {:error, any()} | {:ok, String}
  def execute(args, _info) do
    uuid = args.user.id

    %Command{
      id: args.user.id,
      email: args.user.email
    }
    |> DraftEternalApi.Commanded.Application.dispatch(include_aggregate_version: true, consistency: :strong)
    |> case do
      {:ok, version} -> {:ok, uuid}
      :ok -> {:ok, uuid}
      reply -> reply
    end
  end
end
