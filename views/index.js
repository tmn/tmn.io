var React = require('react');

var Articles = require('./articles');
var Header = require('./header');

var Index = React.createClass({
  render: function () {
    return (
      <html>
      <head>
        <meta charSet="utf-8" />
        <title>{this.props.title}</title>
        <link rel="stylesheet" type="text/css" href="/css/reset.css" />
        <link rel="stylesheet" type="text/css" href="/css/main.css" />

        <meta name="viewport" content="width=device-width" />
      </head>
      <body>
        <Header />
        <Articles />
      </body>
      </html>
    );
  }
});

module.exports = Index;
