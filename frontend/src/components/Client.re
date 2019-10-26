/* Create Fragment Matcher*/
let fragmentMatcher: ApolloInMemoryCache.fragmentMatcher =
  ApolloInMemoryCache.createIntrospectionFragmentMatcher(
    ~data=GraphQLSchema.data,
  );

/* Create an InMemoryCache */
let inMemoryCache: ReasonApolloTypes.apolloCache =
  ApolloInMemoryCache.createInMemoryCache(~fragmentMatcher, ());

/* Create an HTTP Link */

let httpLink: ReasonApolloTypes.apolloLink =
  ApolloLinks.createHttpLink(
    ~uri=Config.config.api ++ "/api",
    ~fetch=Document.isBrowser() ? Document.fetch : Node.fetch,
    ~headers=
      Json.Encode.object_([
        (
          "authorization",
          "Bearer "
          ++ (
            Document.isBrowser() ?
              LocalStorage.saveAuth()
              |> LocalStorage.getAuth(_)
              |> Belt.Option.getWithDefault(_, "") :
              ""
          )
          |> Json.Encode.string,
        ),
      ]),
    (),
  );

let instance: ApolloClient.generatedApolloClient =
  ReasonApollo.createApolloClient(
    ~link=httpLink,
    ~cache=inMemoryCache,
    ~ssrMode=!Document.isBrowser(),
    (),
  );