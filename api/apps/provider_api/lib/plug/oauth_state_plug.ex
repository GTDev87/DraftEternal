defmodule ProviderApi.Plug.OauthStatePlug do
  # The Plug.Conn module gives us the main functions
  # we will use to work with our connection, which is
  # a %Plug.Conn{} struct, also defined in this module.

  def init(opts) do
  end

  defp update_params(conn, new_params) do
    put_in(conn.params, new_params)
  end


  def call(conn, opts) do
    # later make this more solid with real stateful check

    # why is this running twice.
    # Todo fix pipeline
    case conn.params do
      %{"state" => _} ->

        conn
      _ ->
        redirect =
          conn.req_headers
          |> Enum.filter(fn ({name, _}) -> name === "referer" end)
          |> Enum.map(fn ({_, val}) -> val end)
          |> List.first

        stateObj = %{redirect: redirect}

        {:ok, token, claims} = ProviderApi.Guardian.encode_and_sign(stateObj, %{}, ttl: {1, :minute})
        newParams = Map.merge(conn.params, %{"state" => token})

        update_params(conn, newParams)
    end
  end
end
