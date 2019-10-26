defmodule ProviderApi.UserController do
  use ProviderApi.Web, :controller

  alias ProviderApi.User

  plug(Guardian.Plug.EnsureAuthenticated, handler: ProviderApi.AuthController)

  def index(conn, _params) do
    users = Repo.all(User)
    render(conn, "index.json-api", data: users)
  end

  def create(conn, %{"data" => %{"type" => "user", "attributes" => user_params}}) do
    changeset = User.changeset(%User{}, user_params |> Map.put(:id, UUID.uuid4()))

    case Repo.insert(changeset) do
      {:ok, user} ->
        conn
        |> put_status(:created)
        |> put_resp_header("location", user_path(conn, :show, user))
        |> render("show.json-api", data: user)

      {:error, changeset} ->
        conn
        |> put_status(422)
        |> render(ProviderApi.ChangesetView, "error.json-api", changeset: changeset)
    end
  end

  def show(conn, %{"id" => id}) do
    if id === "current" do
      user =
        conn
        |> Guardian.Plug.current_resource()

      conn
      |> render(ProviderApi.UserView, "show.json-api", data: user)
    else
      user = Repo.get!(User, id)
      render(conn, "show.json-api", data: user)
    end
  end

  def update(conn, %{"data" => %{"type" => "user", "id" => id, "attributes" => user_params}}) do
    try do
      # get current user
      current_user =
        conn
        |> Guardian.Plug.current_resource()

      user =
        User
        |> where(id: ^current_user.id)
        |> Repo.one!()

      # do the update operation if the user is authorized
      changeset = User.changeset(user, user_params)

      case Repo.update(changeset) do
        {:ok, user} ->
          render(conn, "show.json-api", data: user)

        {:error, changeset} ->
          conn
          |> put_status(422)
          |> render(ProviderApi.ChangesetView, "error.json-api", changeset: changeset)
      end
    rescue
      e ->
        # Print error to the console for debugging
        IO.inspect(e)

        conn
        |> render(ProviderApi.ErrorView, "401.json-api")
    end
  end

  def delete(conn, %{"id" => id}) do
    try do
      # get current user
      current_user =
        conn
        |> Guardian.Plug.current_resource()

      user =
        User
        |> where(id: ^current_user.id)
        |> Repo.one!()

      # do the update operation if the user is authorized
      # Here we use delete! (with a bang) because we expect
      # it to always work (and if it does not, it will raise).
      Repo.delete!(user)

      send_resp(conn, :no_content, "")
    rescue
      e ->
        # Print error to the console for debugging
        IO.inspect(e)

        conn
        |> render(ProviderApi.ErrorView, "401.json-api")
    end
  end
end
