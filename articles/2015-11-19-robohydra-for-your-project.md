# Robohydra for your project
Thursday 18 November 2015

Robohydra? Pylons? Zealots?! Everytime I implement Robohydra in one of the teams projects, people tend to ask _"did you just implement StarCraft again?!"_. And I have to admit, I've been using Robohydra **a lot** lately.


## What is it? What is it good for?

First of all, Robohydra is _"a web server designed to help you test any kind of HTTP client"_. So, what is it good for?

Let's say your team is told to fix and implement some JavaScript features on one of the biggie systems you've got. Maybe it is a huge social network with millions of users, or just your tiny webshop. The first thing you have to do is to set up the whole environment locally on your computer. Which means you need to sandbox the current system with the right database and software versions, and everything else.

Or you can just use Robohydra! With a simple Robohydra plugin you can bypass the hassle of setting up the system locally. All you need from the project is the few JavaScript files to solve the issue. How? You ask. Let me show you!

To get started, you need Robohydra:

```javascript
var robohydra = require('robohydra');

// Get them HEADS
var RoboHydraHead = robohydra.heads.RoboHydraHead;
var RoboHydraHeadFilesystem = robohydra.heads.RoboHydraHeadFilesystem;
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy;
var RoboHydraHeadStatic = robohydra.heads.RoboHydraHeadStatic;
```

Then the proxy for our production site:

```javascript
new RoboHydraHeadProxy({
  name: 'My Social Network',
  mountPath: '/',                   // application path
  proxyTo: 'http://example.com/'    // external application
});
```

And now the fun part! Say all your JavaScript files are located at _http://example.com/js/_. But locally it's in `~/awesomeProject/src/main/webapp/js/src`. Here is where the magic happens. Robohydra lets you direct all request to a simple path on the external server to some local files. By using the `RoboHydraHeadFilesystem` you can simply serve static local files to all request towards _http://example.com/js/_:


```javascript
new RoboHydraHeadFilesystem({
  name: 'My JavaScript files',
  mountPath: '/js',                       // external path to JS files
  documentRoot: 'src/main/webapp/js/src'  // local path to JS files
});
```

Now when you access the site through `http://localhost:3000/` in your browser, all JavaScript files are served locally, while the rest is proxied from your production site.

Awesome!

But say you've already got the system set up locally. The problem now is that for every style you change, or JavaScript logic you add, you have to rebuild and redeploy the whole package. Maybe it's a Java package deployed on a local tomcat server. Well, you don't want to rebuild and redeploy the package for every change! Neither do you want to f**k up the Java code and configs some other developer has written to reflect your needs. Well, you can of course proxy local servers too. So simplyswitch the `RoboHydraHeadProxy` to point to your local server. And voilà. Same behaviour!

### This is how the plugin will look like

```javascript
var robohydra = require('robohydra');

var RoboHydraHeadFilesystem = robohydra.heads.RoboHydraHeadFilesystem;
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy;

exports.getBodyParts = function (conf) {
  return {
    heads: [
      new RoboHydraHeadFilesystem({
        name: 'My JavaScript files',
        mountPath: '/js',
        documentRoot: 'src/main/webapp/js/src'
      }),

      new RoboHydraHeadProxy({
        name: 'My Social Network',
        mountPath: '/',
        proxyTo: 'http://example.com/'
      })
    ]
  };
};
```

## Some data not available outside the network?

Sometimes you may be told to demo a solution for peoples outside your company network. And you simply don't have access to the resources needed. What do you do?

The `RoboHydraHeadStatic` lets you serve static mocks without changing anything in your project. No extra configs, no adjustments, no refactoring. Your project is still untouched. The only thing you need to do is to construct som mock data, and run it all through Robohydra: 

Mocks (`data.json`):
```json
[
  {
    "name": "Super secret resource #1",
    "value": 10000
  },
  {
    "name": "Super secret resource #2",
    "value": 35000
  },

  ...
]
```

The plugin (`plugin.js`):

```javascript
new RoboHydraHeadStatic({
  path: '/api/resource/:id',
  content: {
    success: true,
    results: res.send(data[id])
  }
});
```

Now when Robohydra runs alongside the rest of the system. All request towards `/api/resource/(someResourceId)` will return local mocks instead of errors caused by unavailable resources. And while we're talking about errors. You can of course return intended errors for the sake of tests too!

Here's another one. Let's say you need a resource that takes time to load. This is easily done by setting some `setTimeout` on the request handler, and of course, the `RoboHydraHead` allow you to do this:

```javascript
new RoboHydraHead({
  path: '/slow/resource/:millis',
  handler: function (req, res) {
    setTimeout(function () {
      res.send({message: 'wooo!'});
    }, req.queryParams.millis || 10000);
  }
});
```


## Sum it up already!
These are my main use cases with Robohydra. By using these methods you can simply create tests clients for your client-server application, return canned responses, static content, reverse proxy requests and a whole lot more. It also comes with a web interface that allow you to change its behaviour dynamically, with easy access to scenarios and test results. Head over to [robohydra.org](http://robohydra.org/) and grab your copy of this awesome tool!

![Robohydra screen](http://tmn.io/img/robohydra_screen.png)

Also. Follow the awesome creator, [@estebanm](https://twitter.com/estebanm) and [@robohydra](https://twitter.com/robohydra), on Twitter.
