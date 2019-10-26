[@bs.deriving {jsConverter: newType}]
type env = {
  frontend: string,
  api: string,
  auth: string,
};

type configFn = string => abs_env;

[@bs.module "../../../../src/config.js"] external config: abs_env = "default";
let config = envFromJs(config);