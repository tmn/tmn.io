var React = require('react');

var Articles = require('./articles');
var Header = require('./header');
var Sidebar = require('./sidebar');

var Index = React.createClass({
  render: function () {
    return (
      <html>
      <head>
        <meta charSet="utf-8" />
        <title>{this.props.title}</title>
        <link rel="stylesheet" type="text/css" href="/css/reset.css" />
        <link rel="stylesheet" type="text/css" href="/css/main.css" />
        <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/highlight.js/8.9.1/styles/github-gist.min.css" />
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css" />

        <meta name="viewport" content="width=device-width" />
      </head>
      <body>
        <div className="wrap0">
          <Articles />
          <Sidebar />
        </div>

        <script src="//cdnjs.cloudflare.com/ajax/libs/highlight.js/8.9.1/highlight.min.js"></script>
        <script dangerouslySetInnerHTML={{__html: `hljs.initHighlightingOnLoad();`}}></script>
        <script dangerouslySetInnerHTML={{__html: `
          (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
          (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
          m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
          })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

          ga('create', 'UA-999552-13', 'auto');
          ga('send', 'pageview');
        `}} />
      </body>
      </html>
    );
  }
});

module.exports = Index;
