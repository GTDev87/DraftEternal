// I need to revisit this pattern

const config = {
  local: {
    frontend: "http://localhost:3000",
    api: "http://localhost:4001",
    auth: "http://localhost:4000",
  },
  staging: {
    frontend: "http://drafteternal-workers.dubcell.com",
    api: "http://api.drafteternal-workers.dubcell.com",
    auth: "http://auth.drafteternal-workers.dubcell.com",
  },
  production: {
    frontend: "http://drafteternal-workers.dubcell.com",
    api: "http://api.drafteternal-workers.dubcell.com",
    auth: "http://auth.drafteternal-workers.dubcell.com",
  },
};

// console.log("process.env.RAZZLE_APP_ENV = %j", process.env.RAZZLE_APP_ENV);

export default config[process.env.RAZZLE_APP_ENV || "local"];