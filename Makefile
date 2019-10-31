
DRAFTETERNAL_DB_URL=`heroku config:get DATABASE_URL -a drafteternal`
PROVIDER_DB_URL=`heroku config:get HEROKU_POSTGRESQL_GREEN_URL -a drafteternal`
DRAFTETERNAL_COMMANDED_DB_URL=`heroku config:get HEROKU_POSTGRESQL_ORANGE_URL -a drafteternal`

# create-prod-db :
# 	export DRAFTETERNAL_COMMANDED_DB_URL=${DRAFTETERNAL_COMMANDED_DB_URL}; \
# 	export PROVIDER_DB_URL=${PROVIDER_DB_URL}; \
# 	cd api && \
# 	mix deps.get ; \
# 	MIX_ENV=dev mix ecto.migrate_seed

clean :
	rm -rf api/_build api/deps frontend/node_modules frontend/.cache frontend/lib/ frontend/build/ frontend/yarn-error.log api/.elixir_ls

up :
	export DRAFTETERNAL_DB_URL=${DRAFTETERNAL_DB_URL}; \
	export PROVIDER_DB_URL=${PROVIDER_DB_URL}; \
	export DRAFTETERNAL_COMMANDED_DB_URL=${DRAFTETERNAL_COMMANDED_DB_URL}; \
	kompose up

down :
	kompose down