defmodule ProviderApi.Router do
  use ProviderApi.Web, :router

  pipeline :api_auth do
    plug(:accepts, ["json", "json-api"])
    plug(JaSerializer.Deserializer)
  end

  pipeline :api do
    plug(ProviderApi.Guardian.AuthPipeline)
    plug(:accepts, ["json", "json-api"])
  end

  scope "/api/v1", ProviderApi do
    pipe_through(:api)

    # auth
    delete("/logout", AuthController, :delete)

    # users
    resources "/users", UserController, except: [:new, :edit] do
      get("/current", UserController, :current, as: :current_user)
    end
  end

  scope "/api/v1/auth", ProviderApi do
    pipe_through(:api_auth)

    get("/:provider", AuthController, :request)
    get("/:provider/callback", AuthController, :callback)
    post("/:provider/callback", AuthController, :callback)
  end
end
