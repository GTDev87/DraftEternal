defmodule ProviderApi.ProviderIdentityTest do
  use ProviderApi.ModelCase

  alias ProviderApi.ProviderIdentity

  @valid_attrs %{email: "some email", email_verified: true, family_name: "some family_name", given_name: "some given_name", name: "some name", nickname: "some nickname", picture: "some picture", provider: "some provider", user_identifier: "some user_identifier"}
  @invalid_attrs %{}

  test "changeset with valid attributes" do
    changeset = ProviderIdentity.changeset(%ProviderIdentity{}, @valid_attrs)
    assert changeset.valid?
  end

  test "changeset with invalid attributes" do
    changeset = ProviderIdentity.changeset(%ProviderIdentity{}, @invalid_attrs)
    refute changeset.valid?
  end
end
