var React = require('react');

module.exports = () => {
  return (
    <header id="mainHeader">
      <div className="mainHeader-content">
        <img src="/img/tmn.jpg" alt="Tri Nguyen" className="profilePicture" />
        <h1 className="mainHeader-title">Tri Nguyen</h1>
        <p>Mr. prokrastinering av 'Åh! Se der!'-borg</p>
        <ul className="profileLocation-list">
          <li><a href="https://github.com/tmn/">GitHub</a></li>
          <li><a href="https://twitter.com/itmn/">Twitter</a></li>
          <li><a href="/is/professional">CV</a></li>
        </ul>
      </div>
    </header>
  );
}
