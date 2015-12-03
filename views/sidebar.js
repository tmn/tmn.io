var React = require('react');

var Sidebar = () => {
  return (
    <section id="sidebar">
      <img src="/img/tmn.jpg" alt="" className="sidebar-profile-picture" />
      <header>
        <h1>Tri Nguyen</h1>
        <p>Gullet ska hjæm t Trondhjæm! <a className="gold" href="https://twitter.com/hashtag/RBK?src=hash">#RBK</a></p>
        <ul className="profileLocation-list">
          <li><a href="https://github.com/tmn/"><i className="fa fa-github fa-custom"></i></a></li>
          <li><a href="https://twitter.com/itmn/"><i className="fa fa-twitter fa-custom"></i></a></li>
          <li><a href="https://cv.tmn.io/">CV</a></li>
        </ul>
      </header>
      <div className="sidebar-content">


        <div className="post-list">
          <h4>Latest posts</h4>
          <ul>
            <li><a href="/read/2015-11-22-making-mobile-apps-using-Fuse">Making mobile apps using Fuse</a></li>
            <li><a href="/read/2015-11-19-robohydra-for-your-project">Robohydra for your project</a></li>
          </ul>
        </div>
      </div>
    </section>
  );
}

module.exports = Sidebar;
