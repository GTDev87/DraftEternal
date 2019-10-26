defmodule ProviderApi.UserView do
  use ProviderApi.Web, :view
  use JaSerializer.PhoenixView

  attributes [:avatar, :email, :first_name, :last_name]
end
