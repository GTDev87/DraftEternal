defmodule ProviderApi.Hooks.UserCreationSuccess do

  ## TODO MAKE THIS EXTERNAL TO THE PROJECT SOMEHOW
  def run(user) do
    Neuron.Config.set(url: "http://localhost:4001/api")
    
    # what are the setting to check
    { :ok, jwt, _ } = ProviderApi.Guardian.encode_and_sign(user, %{"from_provider": true, typ: "access"}, token_type: :token)
    
    Neuron.Config.set(headers: [{:authorization, "Bearer #{jwt}"}])
    Neuron.mutation("{createUser(user: { id: \"#{user.id}\", email: \"#{user.email}\" }){ id }}")
  end
end
