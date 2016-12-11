import React from 'react';

const Header = ({ showImage = true }) => (
  <header id="mainHeader">
    <div className="container mainHeader-content">
      <a href="/"><h1>TriNguyen</h1></a>

      <nav>
        <ul>
          <li><a href="https://cv.tmn.io/">CV</a></li>
          <li><a href="https://github.com/tmn/">GitHub</a></li>
          <li><a href="https://twitter.com/itmn/">Twitter</a></li>
        </ul>
      </nav>
    </div>
  </header>
);

module.exports = Header;
