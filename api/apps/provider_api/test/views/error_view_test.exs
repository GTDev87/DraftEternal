defmodule ProviderApi.ErrorViewTest do
  use ProviderApi.ConnCase, async: true

  # Bring render/3 and render_to_string/3 for testing custom views
  import Phoenix.View

  test "renders 401.json-api" do
    assert render(ProviderApi.ErrorView, "401.json-api", []) ==
           %{"errors" => [%{code: 401, title: "Unauthorized"}], "jsonapi" => %{"version" => "1.0"}}
  end

  test "renders 403.json-api" do
    assert render(ProviderApi.ErrorView, "403.json-api", []) ==
           %{"errors" => [%{code: 403, title: "Forbidden"}], "jsonapi" => %{"version" => "1.0"}}
  end

  test "renders 404.json-api" do
    assert render(ProviderApi.ErrorView, "404.json-api", []) ==
           %{"errors" => [%{code: 404, title: "Resource not found"}], "jsonapi" => %{"version" => "1.0"}}
  end

  test "renders 422.json-api" do
    assert render(ProviderApi.ErrorView, "422.json-api", []) ==
           %{"errors" => [%{code: 422, title: "Unprocessable entity"}], "jsonapi" => %{"version" => "1.0"}}
  end

  test "render 500.json-api" do
    assert render(ProviderApi.ErrorView, "500.json-api", []) ==
           %{"errors" => [%{code: 500, title: "Internal Server Error"}], "jsonapi" => %{"version" => "1.0"}}
  end

  test "render any other" do
    assert render(ProviderApi.ErrorView, "505.json-api", []) ==
           %{"errors" => [%{code: 500, title: "Internal Server Error"}], "jsonapi" => %{"version" => "1.0"}}
  end
end
