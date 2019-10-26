defmodule DraftEternalApi.Guardian.Context do
  @behaviour Plug

  import Plug.Conn
  # import Ecto.Query, only: [where: 2]

  def init(opts), do: opts

  @type info :: %{context: %{current_user: %{id: String.t()}}}

  def call(conn, _) do
    case build_context(conn) do
      {:ok, context} ->
        put_private(conn, :absinthe, %{context: context})

      _ ->
        conn
    end
  end

  defp build_context(conn) do
    with ["Bearer " <> token] <- get_req_header(conn, "authorization"),
         {:ok, jwt_user} <- ProviderApi.Guardian.decode_and_verify(token) do

      %{"sub" => "User:" <> user_id} = jwt_user
      email = Map.get(jwt_user, "email", nil)

      current_user = %{id: user_id, email: email}
      {:ok, %{current_user: current_user, token: token}}
    end
  end
end
