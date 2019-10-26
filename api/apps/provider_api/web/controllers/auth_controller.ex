defmodule ProviderApi.AuthController do
  @moduledoc """
  Auth controller responsible for handling Ueberauth responses
  """
  use ProviderApi.Web, :controller

  alias ProviderApi.User
  alias ProviderApi.ProviderIdentity
  alias Ueberauth.Auth

  # this plug needs to be redone
  plug(ProviderApi.Plug.OauthStatePlug)
  plug(Ueberauth)

  def delete(conn, _params) do
    # Sign out the user
    conn
    |> put_status(200)
    |> ProviderApi.Guardian.Plug.sign_out(conn)
  end

  def callback(%{assigns: %{ueberauth_failure: _fails}} = conn, _params) do
    # Guardian.encode_and_sign(user, :token)

    # This callback is called when the user denies the app to get the
    # data from the oauth provider
    conn
    |> put_status(401)
    |> render(ProviderApi.ErrorView, "401.json-api")
  end

  def callback(conn, params) do
    case conn.assigns.ueberauth_auth.provider do
      :google -> sign_in_user(conn, params)
      _ -> sign_in_user(conn, params)
    end
  end

  def get_redirect_from_params(params) do
    {:ok, redirectObj, claims} =
      params
      |> Map.get("state")
      |> ProviderApi.Guardian.resource_from_token()

    redirectObj.redirect
  end

  defp route_to_full_url(redirect, jwt) do
    "#{redirect}?jwt=#{jwt}"
  end

  def sign_in_user(conn, params) do
    ueberauth_auth = conn.assigns.ueberauth_auth
    %{email: email} = ueberauth_auth.info

    # don't like this try catch
    try do
      # Attempt to retrieve exactly one user from the DB, whose
      # email matches the one provided with the login request

      user =
        User
        |> where(email: ^email)
        |> Repo.one!()

      cond do
        true ->
          # Successful login
          # Encode a JWT

          redirect = get_redirect_from_params(params)

          {:ok, _jwt, _} =
            ProviderApi.Guardian.encode_and_sign(user, %{email: user.email, typ: "access"},
              token_type: :token
            )

          auth_conn = ProviderApi.Guardian.Plug.sign_in(conn, user, %{email: user.email})

          jwt = ProviderApi.Guardian.Plug.current_token(auth_conn)

          auth_conn
          |> put_resp_header("authorization", "Bearer #{jwt}")
          |> redirect(external: route_to_full_url(redirect, jwt))

        false ->
          # Unsuccessful login
          conn
          |> put_status(401)
          |> render(ProviderApi.ErrorView, "401.json-api")
      end
    rescue
      e ->
        # Print error to the console for debugging
        IO.inspect(e)

        # Sign the user up
        sign_up_user(conn, params)
    end
  end

  def sign_up_user(conn, params) do
    ueberauth_auth = conn.assigns.ueberauth_auth

    formatted_provider_identity =
      ueberauth_auth
      |> ProviderIdentity.ueberauth_to_provider_identity()
      |> Map.put(:id, UUID.uuid4())

    email = ProviderIdentity.ueberauth_to_email(ueberauth_auth)

    user_changeset = User.changeset(%User{}, %{email: email, id: UUID.uuid4()})

    provider_changeset =
      ProviderIdentity.changeset(%ProviderIdentity{}, formatted_provider_identity)

    Ecto.Multi.new()
    |> Ecto.Multi.insert(:user, user_changeset)
    |> Ecto.Multi.insert(:provider_identity, provider_changeset)
    |> Repo.transaction()
    |> case do
      {:ok, %{user: user, provider_identity: provider_identity}} ->
        # Encode a JWT

        {:ok, jwt, _} =
          ProviderApi.Guardian.encode_and_sign(user, %{email: user.email, typ: "access"},
            token_type: :token
          )

        redirect = get_redirect_from_params(params)

        # send a user creating call to main application
        require Logger
        Logger.debug("user = #{inspect user}")
        {:ok, res} = ProviderApi.Hooks.UserCreationSuccess.run(user)

        conn
        |> put_resp_header("authorization", "Bearer #{jwt}")
        |> redirect(external: route_to_full_url(redirect, jwt))

      {:error, abc, defg, hij} ->
        conn
        |> put_status(422)
        |> render(ProviderApi.ErrorView, "422.json-api")
    end
  end

  def unauthenticated(conn, _params) do
    conn
    |> put_status(401)
    |> render(ProviderApi.ErrorView, "401.json-api")
  end
end
