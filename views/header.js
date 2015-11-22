var React = require('react');

module.exports = () => {
  return (
    <header id="mainHeader">
      <div className="mainHeader-content">
        <img src="/img/tmn.jpg" alt="Tri Nguyen" className="profilePicture" />
        <h1 className="mainHeader-title">Tri Nguyen</h1>
        <p >Gullet ska hjæm t Trondhjæm! <a className="gold" href="https://twitter.com/hashtag/RBK?src=hash">#RBK</a></p>
        <ul className="profileLocation-list">
          <li><a href="https://github.com/tmn/"><i className="fa fa-github fa-custom"></i></a></li>
          <li><a href="https://twitter.com/itmn/"><i className="fa fa-twitter fa-custom"></i></a></li>
          <li><a href="/is/professional">CV</a></li>
        </ul>
      </div>
    </header>
  );
}
