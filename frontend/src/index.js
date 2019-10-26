import app from './server';
import express from 'express';

if (module.hot) {
  module.hot.accept('./server');
  console.info('✅  Server-side HMR Enabled!');
}

const port = process.env.PORT || 3000;

export default express()
  .use((req, res) => app.handle(req, res))
  .listen(port, '0.0.0.0', function (err) {
    if (err) {
      console.error(err);
      return;
    }
    console.log(`> Started on port ${port}`);
  });
