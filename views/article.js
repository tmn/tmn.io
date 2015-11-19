var fs = require('fs');
var path = require('path');
var React = require('react');
var marked = require('marked');

var ArticleSingle = React.createClass({
  render: function () {
    var md = fs.readFileSync(path.join(__dirname + '/../articles', this.props.article) + '.md', 'utf8');
    md = md.split('\n');

    var article = {
      title: md[0].split('#').slice(1).join('#'),
      date: md[1],
      content: md.slice(3).join('\n')
    };

    var rawMarkup = {
      __html: marked(article.content, { sanitize: true })
    };

    return (
      <html>
      <head>
        <meta charSet="utf-8" />
        <title>{this.props.title}</title>
        <link rel="stylesheet" type="text/css" href="/css/reset.css" />
        <link rel="stylesheet" type="text/css" href="/css/main.css" />
        <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/highlight.js/8.9.1/styles/default.min.css" />

        <meta name="viewport" content="width=device-width" />
      </head>
      <body>
        <header id="article-header">
          <div className="container">
            <a href="/">Go back</a>
          </div>
        </header>
        <article className="container">
          <header>
          <h1>{article.title}</h1>
            <span className="article-meta">{article.date}</span>
          </header>

          <div dangerouslySetInnerHTML={rawMarkup} />

          <div id="comment-section" dangerouslySetInnerHTML={{__html: `
            <div id="disqus_thread"></div>
            <script>
            /**
            * RECOMMENDED CONFIGURATION VARIABLES: EDIT AND UNCOMMENT THE SECTION BELOW TO INSERT DYNAMIC VALUES FROM YOUR PLATFORM OR CMS.
            * LEARN WHY DEFINING THESE VARIABLES IS IMPORTANT: https://disqus.com/admin/universalcode/#configuration-variables
            */
            /*
            var disqus_config = function () {
            this.page.url = PAGE_URL; // Replace PAGE_URL with your page's canonical URL variable
            this.page.identifier = PAGE_IDENTIFIER; // Replace PAGE_IDENTIFIER with your page's unique identifier variable
            };
            */
            (function() { // DON'T EDIT BELOW THIS LINE
            var d = document, s = d.createElement('script');

            s.src = '//supertri.disqus.com/embed.js';

            s.setAttribute('data-timestamp', +new Date());
            (d.head || d.body).appendChild(s);
            })();
            </script>
            <noscript>Please enable JavaScript to view the <a href="https://disqus.com/?ref_noscript" rel="nofollow">comments powered by Disqus.</a></noscript>
          `}} />
        </article>

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

module.exports = ArticleSingle;
