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

        <div dangerouslySetInnerHTML={{__html: `
          <script>
            (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
            (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
            m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
            })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

            ga('create', 'UA-999552-13', 'auto');
            ga('send', 'pageview');

          </script>
        `}} />
      </body>
      </html>
    );
  }
});

module.exports = Index;
