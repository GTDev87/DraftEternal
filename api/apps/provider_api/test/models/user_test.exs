defmodule ProviderApi.UserTest do
  use ProviderApi.ModelCase

  alias ProviderApi.User

  @valid_attrs %{auth_provider: "some content", avatar: "some content", email: "some content", first_name: "some content", last_name: "some content"}
  @invalid_attrs %{}

  test "changeset with valid attributes" do
    changeset = User.changeset(%User{}, @valid_attrs)
    assert changeset.valid?
  end

  test "changeset with invalid attributes" do
    changeset = User.changeset(%User{}, @invalid_attrs)
    refute changeset.valid?
  end
end
