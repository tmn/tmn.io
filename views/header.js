import React from 'react';

const Header = ({ showImage = true }) => (
  <header id="mainHeader">
    <div className="container">
      <a href="/"><h1>Tri Nguyen</h1></a>

      <nav>
        <ul>
          <li><a href="/is/professional">CV</a></li>
          <li> | </li>
          <li><a href="https://github.com/tmn/">GitHub</a></li>
          <li><a href="https://twitter.com/itmn/">Twitter</a></li>
        </ul>
      </nav>
    </div>
  </header>
);

module.exports = Header;
