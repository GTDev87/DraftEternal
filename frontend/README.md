# Razzle Reason React

## How to use
First install the Reason toolchain ([reason-cli](https://github.com/reasonml/reason-cli)) globally

```bash
npm install -g https://github.com/reasonml/reason-cli/archive/beta-v-1.13.6-bin-darwin.tar.gz
```
Download the example [or clone the whole project](https://github.com/jaredpalmer/razzle.git):

```bash
curl https://codeload.github.com/jaredpalmer/razzle/tar.gz/master | tar -xz --strip=2 razzle-master/examples/with-reason-react
cd with-reason-react
```

Install it and run:

```bash
yarn install
yarn start
```
#### NOTE: This example takes a while to install. Stick with it.

Now you can go and edit `src/App.re`. When you make changes, your **browser and server** will Hot Reload. 


## Idea behind the example
This is an example of how to use [Reason React](https://github.com/reasonml/reason-react) and Razzle together. Yes, you read that correctly. SSR, Reason, React, HMR. 

## Secret sauce
This example works by running BuckleScript Platform to compile Reason-React files (`.re`) and then importing that output back into the vanilla Razzle app using the JS-Reason-React interop.

Since Reason compiles to (beautifully written) JS, we don't have to do anything else to get universal HMR going because Razzle already does that. We just need to import `<App />` a litte bit differently in `src/server.js` and `src/client.js`.


```js
// src/client.js

// We need to point this to our Reason-React output
const App = require('../lib/js/src/app').comp;

import './client.css';

import React from 'react';
import { render } from 'react-dom';

// No JSX required, it's already in JS.
render(
  React.createElement(App, {
    title: 'Welcome to Razzle Reason React!',
  }),
  document.getElementById('root')
);

if (module.hot) {
  module.hot.accept();
}
```


```js
// src/server.js
// We need to point this to our Reason-React output, just like above
const App = require('../lib/js/src/app').comp;

import React from 'react';
import express from 'express';
import path from 'path';
import { renderToString } from 'react-dom/server';

const assets = require(process.env.RAZZLE_ASSETS_MANIFEST);

const server = express();

server
  .disable('x-powered-by')
  .use(express.static(process.env.RAZZLE_PUBLIC_DIR))
  .get('/*', (req, res) => {
    // Again, no JSX needed
    const markup = renderToString(
      React.createElement(App, {
        title: 'Welcome to Razzle Reason React',
      })
    );
    res.send(
      `<!doctype html>
    <html lang="">
    <head>
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta charSet='utf-8' />
        <title>Welcome to Razzle Reason React</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        ${assets.client.css ? `<link rel="stylesheet" href="${assets.client.css}">` : ''}
        <script src="${assets.client.js}" defer></script>
    </head>
    <body>
        <div id="root">${markup}</div>
    </body>
</html>`
    );
  });

export default server;
```

Introspection
```
yarn send-introspection-query http://localhost:4001/api
```
