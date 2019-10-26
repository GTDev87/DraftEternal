defmodule ProviderApi.Guardian.AuthPipeline do
  @claims %{typ: "access"}

  use Guardian.Plug.Pipeline, otp_app: :provider_api,
                              module: ProviderApi.Guardian,
                              error_handler: ProviderApi.Guardian.AuthErrorHandler

  plug Guardian.Plug.VerifySession, claims: @claims
  plug Guardian.Plug.VerifyHeader, claims: @claims, realm: "Bearer"
  plug Guardian.Plug.EnsureAuthenticated
  plug Guardian.Plug.LoadResource, allow_blank: false
end
