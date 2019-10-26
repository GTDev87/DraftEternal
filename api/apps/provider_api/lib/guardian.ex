defmodule ProviderApi.Guardian do
  use Guardian, otp_app: :provider_api

  def subject_for_token(resource = %ProviderApi.User{}, _claims), do: {:ok, "User:#{resource.id}"}
  def subject_for_token(%{redirect: sub}, _), do: { :ok, "Redirect:#{sub}" }
  def subject_for_token(resource, claims), do: {:error, :reason_for_error}

  def resource_from_claims(%{ "sub" => "User:" <> id = sub}), do: {:ok,  ProviderApi.Repo.get(ProviderApi.User, id)}
  def resource_from_claims(%{ "sub" => "Redirect:" <> redirect = sub}), do: { :ok, %{redirect: redirect} }
  def resource_from_claims(_claims), do: {:error, :reason_for_error}
end