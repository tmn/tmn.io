import fs from 'fs';
import path from 'path';
import React from 'react';
import marked from 'marked';

const Article = ({ article }) => (
  <article>
    <header>
      <span className="article-meta">{ article.date }</span>
      <a href={ article.url }><h1>{ article.title }</h1></a>
    </header>

    <div dangerouslySetInnerHTML={ { __html: marked(article.content, { sanitize: true }) } } />
  </article>
);


const Articles = () => {
  let articles = fs.readdirSync(__dirname + '/../articles').reverse();

  articles = articles.filter((f) => {
    return path.extname(f) === '.md';
  });

  return (
    <section id="blogContent" className="container">
      { articles.map((a, key) => {
        let md = fs.readFileSync(path.join(__dirname + '/../articles', a), 'utf8');
        md = md.split('\n');

        const article = {
          title: md[0].split('#').slice(1).join('#'),
          date: md[1],
          content: md.slice(3).join('\n'),
          url: 'read/' + a.slice(0, -3)
        };

        return <Article key={ key } article={ article } />;
      }) }
    </section>
  );
};

module.exports = Articles;
