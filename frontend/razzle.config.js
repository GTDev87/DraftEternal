'use strict';
const path = require('path');

module.exports = {
  modifyBabelOptions() {
    console.log("running modify babel options ");
    const emotionPlugin = require.resolve("babel-plugin-emotion");
    return {
      "cacheDirectory": ".cache/babel-loader",
      "babelrc": false,
      "env": {
        "production": {
          "plugins": [
            [
              emotionPlugin,
              {
                "hoist": true
              }
            ]
          ]
        },
        "development": {
          "plugins": [
            [
              emotionPlugin,
              {
                "sourceMap": true,
                "autoLabel": true
              }
            ]
          ]
        }
      },
      "presets": [
        [
          require.resolve("babel-preset-stage-0")
        ],
        [
          require.resolve("babel-preset-env"),
          {
            "loose": true,
            "modules": false,
            "useBuiltIns": "usage",
            "shippedProposals": true,
            "targets": {
              "browsers": [
                ">0.25%",
                "not dead"
              ]
            }
          }
        ],
        [
          require.resolve("razzle/babel")
        ]
      ],
      "plugins": [
        require.resolve("babel-plugin-macros"),
        [
          emotionPlugin,
          {
            "autoLabel": true
          }
        ],
        [
          require.resolve("babel-plugin-tailwind-components"),
          {
            config: './tailwind.js',
            format: 'auto'
          }
        ]
      ]
    };
  },
  modify(config, { target, dev }, webpack) {
    const babelRuleIndex = config.module.rules.findIndex(
      (rule) =>
        (rule.use
          && rule.use[0].loader
          && rule.use[0].loader.includes('babel-loader') || (rule.loader && rule.loader.includes('babel-loader')))
    );
    config.module.rules[babelRuleIndex] = Object.assign(config.module.rules[babelRuleIndex], {
      exclude: /(node_modules|bower_components)/,
      include: [
        ...config.module.rules[babelRuleIndex].include,
        path.resolve("./lib"),
      ],
    });

    return config;
  },
};