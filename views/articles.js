var fs = require('fs');
var path = require('path');
var React = require('react');
var marked = require('marked');


var Article = ({ article }) => {
  var rawMarkup = {
    __html: marked(article.content, { sanitize: true })
  };
  return (
    <article>
      <header>
        <span className="article-meta">{article.date}</span>
        <a href={article.url}><h1>{article.title}</h1></a>
      </header>

      <div dangerouslySetInnerHTML={rawMarkup} />
    </article>
  );
};

var Articles = () => {
  var articles = fs.readdirSync(__dirname + '/../articles').reverse();
  articles = articles.filter(function (f) {
    return path.extname(f) === '.md';
  });

  return (
    <section id="blogContent">
      {articles.map(function (a, key) {
        var md = fs.readFileSync(path.join(__dirname + '/../articles', a), 'utf8');
        md = md.split('\n');

        var article = {
          title: md[0].split('#').slice(1).join('#'),
          date: md[1],
          content: md.slice(3).join('\n'),
          url: 'read/' + a.slice(0, -3)
        };

        return <Article key={key} article={article} />;
      })}
    </section>
  );
}

module.exports = Articles;
