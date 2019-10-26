defmodule DraftEternalApi.Guardian do
  use Guardian, otp_app: :drafteternal_api

  def subject_for_token(user_id, _claims), do: {:ok, "User:#{user_id}"}
  # def subject_for_token(resource, claims), do: {:error, :reason_for_error}

  def resource_from_claims(%{"sub" => "User:" <> user_id = _sub}), do: {:ok, user_id}
  def resource_from_claims(_claims), do: {:error, :reason_for_error}
end
