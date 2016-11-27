import React from 'react';

const Header = ({ showImage = true }) => (
  <header id="mainHeader">
    <div className="mainHeader-content">
      { showImage ? <img src="/img/tmn2.png" /> : null }

      <h1>Tri Nguyen</h1>

      <nav>
        <ul>
          <li><a href="https://github.com/tmn/">Github</a></li>
          <li><a href="https://twitter.com/itmn/">Twitter</a></li>
          <li><a href="/is/professional">CV</a></li>
        </ul>
      </nav>
    </div>
  </header>
);

module.exports = Header;
