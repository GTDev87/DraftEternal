import React from 'react';
import express from 'express';
import proxy from 'http-proxy-middleware';
import { express as voyagerMiddleware } from 'graphql-voyager/middleware';

import { renderToString } from 'react-dom/server';

import config from './config'; // BuckleScript output directory
import App from './init'; // BuckleScript output directory

const assets = require(process.env.RAZZLE_ASSETS_MANIFEST);
const server = express();

// use this token for introspection query for now eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJ0aXJvX2FwaSIsImVtYWlsIjoiZ3JlZ3Q4N0BnbWFpbC5jb20iLCJleHAiOjE1Mzk0MTQyMDAsImlhdCI6MTUzNjgyMjIwMCwiaXNzIjoidGlyb19hcGkiLCJqdGkiOiI5ZGU1MjQxNy0wMTU1LTQ3MDktODI1NC1lM2IxMTJhNDg2YjEiLCJuYmYiOjE1MzY4MjIxOTksInN1YiI6IlVzZXI6Zjk5OGY0NjktMjI1MC00N2MxLThhMDQtMDI5NzlmOWUwZDI5IiwidHlwIjoiYWNjZXNzIn0.WS1yFhFNA2RyDFPnJ2xJSgyt1GA76s61bgwlgTL6pOHHfyjb9C5LvI54wc2vkE5ahyYyqRneUfh4fibxk2xmjA

var mainApiOptions = (pathLoc) => ({
  target: config.api, // target host
  changeOrigin: true,               // needed for virtual hosted sites
  ws: true,                         // proxy websockets
  pathRewrite: {
    // '^/api/old-path' : '/api/new-path',     // rewrite path
    // '^/api/remove/path' : '/path',           // remove base path
    '^/': pathLoc
  },
  // router: {
  //     // when request.headers.host == 'dev.localhost:3000',
  //     // override target 'http://www.example.org' to 'http://localhost:8000'
  //     'dev.localhost:3000' : 'http://localhost:8000'
  // }
});

// server.use('/api', proxy(mainApiOptions('/')));
server.use('/graphql', proxy(mainApiOptions('/api/')));
server.use('/voyager', voyagerMiddleware({ endpointUrl: '/graphql' }));

server
  .disable('x-powered-by')
  .use(express.static(process.env.RAZZLE_PUBLIC_DIR))
  .get('/*', (req, res) => {

    // console.log("process.env.RAZZLE_ASSETS_MANIFEST = %j", process.env.RAZZLE_ASSETS_MANIFEST);
    // console.log("assets.client = %j", assets.client);
    // console.log("assets.client.css = %j", assets.client.css);
    // console.log("req.url = %j", req.url);

    const markup = renderToString(<App title="Smoothie" initialUrl={req.url} server={true} />);
    res.send(
      `<!doctype html>
    <html lang="">
    <head>
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta charSet='utf-8' />
        <title>Tiro powered by Real and Open</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        ${
      !!assets.client.css
        ? `<link rel="stylesheet" href="${assets.client.css}">`
        : ''
      }
        ${
      process.env.NODE_ENV === 'production'
        ? `<script src="${assets.client.js}" defer></script>`
        : `<script src="${assets.client.js}" defer crossorigin></script>`
      }
    </head>
    <body>
        <div id="root">${markup}</div>
    </body>
</html>`
    );
  });

export default server;