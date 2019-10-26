# Provider Api

================

[![Build Status](https://travis-ci.org/ghoshnirmalya/provider_api.svg?branch=master)](https://travis-ci.org/ghoshnirmalya/provider_api) [![codecov](https://codecov.io/gh/ghoshnirmalya/provider_api/branch/master/graph/badge.svg?token=)](https://codecov.io/gh/ghoshnirmalya/provider_api)
[![Open Source Helpers](https://www.codetriage.com/ghoshnirmalya/provider_api/badges/users.svg)](https://www.codetriage.com/ghoshnirmalya/provider_api)

An API only app to throw response for a Social Networking app.

```

mix deps.get

mix ecto.create
mix event_store.init
mix ecto.migrate

iex -S mix phx.server
```