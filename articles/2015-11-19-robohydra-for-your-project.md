# Robohydra for your project
Thursday 18 November 2015

Robohydra? Pylons? Zealots?! Everytime I implement Robohydra in one of the teams projects, people tend to ask _"did you just implement StarCraft again?!"_. And I have to admit, I've been using Robohydra **a lot** lately.


### What is it? What is it good for?

First of all, Robohydra is _"a web server designed to help you test any kind of HTTP client"_. So, what is it good for?

Let's say your team is told to fix and implement some JavaScript features on one of the biggie systems you've got. Maybe it is a huge social network with millions of users, or just your tiny webshop. The first thing you have to do is to setup the whole environment locally on your computer. This means you need a sandbox for this current system with the right database and software versions to boot it up.

Or you can use Robohydra! With a simple Robohydra plugin you can bypass the hassle by setting up the system locally, and just clone the JavaScriprt files you need to solve the issue. How? You ask. Let me show you!

To get started, you need Robohydra:

```javascript
var robohydra = require('robohydra')

// Get them HEADS
var RoboHydraHead = robohydra.heads.RoboHydraHead
var RoboHydraHeadFilesystem = robohydra.heads.RoboHydraHeadFilesystem
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy
var RoboHydraHeadStatic = robohydra.heads.RoboHydraHeadStatic
```

Let's set up the proxy for our production site:

```javascript
new RoboHydraHeadProxy({
  name: 'My Social Network',
  mountPath: '/',                   // application path
  proxyTo: 'http://example.com/'    // external application
})
```

And now the fun part! Let's say all your JavaScript files are located at _http://example.com/js/_. But locally it's in `~/awesomeProject/src/main/webapp/js/src`. By using the `RoboHydraHeadFilesystem` you can simply serve static files through Robohydra to all request on `/js`:


```javascript
new RoboHydraHeadFilesystem({
  name: 'My JavaScript files',
  mountPath: '/js',                       // external path to JS files
  documentRoot: 'src/main/webapp/js/src'  // local path to JS files
})
```

Robohydra is by default run on port `3000`. So when you now access `http://localhost:3000/`, all JavaScript files are served locally, while the rest is proxied from your production site.

Awesome!

But let's say you've already got the system setup locally. Meaning, you already went through the hassle setting up the whole thingy. The problem now is that for every style you change, or JavaScript logic you add, you have to rebuild and redeploy the whole package. Maybe it's a Java package deployed on a local tomcat server. Well, you don't want to rebuild and redeploy the package for every change! And you don't want to f**k up the Java code some other developer has written to reflect your needs. Robohydra to the rescue! You can simply switch the `RoboHydraHeadProxy` to point to your local server. And voilà. Same behaviour.

**This is how the plugin will look like:**

```javascript
var robohydra = require('robohydra')

var RoboHydraHeadFilesystem = robohydra.heads.RoboHydraHeadFilesystem
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy

exports.getBodyParts = function (conf) {
  return {
    heads: [
      new RoboHydraHeadProxy({
        name: 'My Social Network',
        mountPath: '/',
        proxyTo: 'http://example.com/'
      }),

      new RoboHydraHeadFilesystem({
        name: 'My JavaScript files',
        mountPath: '/js',
        documentRoot: 'src/main/webapp/js/src'
      })
    ]
  }
}
```

### Some data not available outside the network?

Sometimes you may be told to demo a solution for peoples outside your company network. And you simply don't have access to the resources needed. What do you do?!

Well, using Robohydra you can simply mock the data without changing anything in your project. No extra configs, no adjustments, no refactoring. Your project is still untouched. The only thing you need to do is running it through Robohydra, with some local mock data.


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
})
```

Now when you start up Robohydra alongside the rest of the system. All request towards `/api/resource/(someResourceId)` will return local mocks instead of errors because of unavailable resources. And while we're talking about errors. You can of course return intended errors for the sake of tests too!

Here's another one. Let's say you need a resource that takes time to load. With `RoboHydraHead` you'll get more flexibility in your request handling:

```javascript
new RoboHydraHead({
  path: '/slow/resource/:millis',
  handler: function (req, res) {
    setTimeout(function () {
      res.send({message: 'wooo!'})
    }, req.queryParams.millis || 10000);
  }
})
```


### Sum it up already!
These are my main use cases with Robohydra. By using these methods you can simply create tests clients for your client-server application, return canned responses, static content, reverse proxy requests and a whole lot more. It also comes with a web interface that allow you to change its behaviour dynamically, with easy access to scenarios and test results. Head over to [robohydra.org](http://robohydra.org/) and grab your copy of this awesome tool!

![Robohydra screen](http://tmn.io/img/robohydra_screen.png)

Also. Follow the awesome creator, [@estebanm](https://twitter.com/estebanm) and [@robohydra](https://twitter.com/robohydra), on Twitter.
