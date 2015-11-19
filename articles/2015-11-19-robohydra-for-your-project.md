# Robohydra for your project
Thursday 18 November 2015

Robohydra? Pylons? Zealots?! Everytime I implement Robohydra in one of the teams projects, people tend to ask _"did you just implement StarCraft again?!"_. And I have to admit, I've been using Robohydra **a lot** lately.


### What is it? What is it good for?

First of all, Robohydra is _"a web server designed to help you test any kind of HTTP client"_. So, what is it good for?

Let's say your team is told to fix and implement some JavaScript features on one of the biggie systems you've got. Maybe it is a huge social network with millions of users, or just your tiny webshop. The first thing you have to do is to setup the whole environment locally on your computer. This means you need a sandbox for this current system with the right database and software versions to boot it up.

Or you can use Robohydra! With a simple Robohydra plugin you can bypass the hassle by setting up the system locally, and just clone the JavaScriprt files you need to solve the issue. How? You ask. Let me show you!


This is an example on how to only serve the JavaScript file from your local disk. The rest is fetched form the external source:

```javascript
var robohydra = require('robohydra')

var RoboHydraHeadFilesystem = robohydra.heads.RoboHydraHeadFilesystem
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy

exports.getBodyParts = function (conf) {
  return {
    heads: [
      new RoboHydraHeadFilesystem({
        name: 'My JavaScript files',
        mountPath: '/js',                         // external path to JS files
        documentRoot: 'src/main/webapp/js/src'    // local path to JS files
      }),

      new RoboHydraHeadProxy({
        name: 'My Social Network',
        mountPath: '/',                           // application path
        proxyTo: 'http://mysocialnetwork.com/'    // external application
      })
    ]
  }
}

```

Awesome!

But let's say you've already got the system setup locally. And for every style you change, or JavaScript logic you add, you have to rebuild and redeploy the whole package. Let's say it's a Java package deployed on a local tomcat server. Well, you don't want to rebuild and redeploy the package for every change! And you don't want to f**k up the Java code other has written to reflect your needs. Robohydra to the rescue!



### Some data not available outside the network?

Sometimes you may be told to demo a solution for peoples outside your company network. And you simply don't have access to the resources needed. What do you do?!

Well, using Robohydra you can simply mock the data without changing anything in your project. No extra configs, no adjustments, no refactoring. Your project is still untouched. The only thing you do is running it through Robohydra!


Mock data (`data.json`):
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
]
```

The Robohydra plugin (`plugin.js`):

```javascript
var robohydra = require('robohydra')

var RoboHydraHead = robohydra.heads.RoboHydraHead
var RoboHydraHeadProxy = robohydra.heads.RoboHydraHeadProxy

var data = require('./data.json')

exports.getBodyParts = function (conf) {
  return {
    heads: [
      new RoboHydraHead({
        path: '/api/resource/:id',
        handler: function (req, res) {
          res.send(data[id])
        }
      }),

      new RoboHydraHeadProxy({
        name: 'Cookiemonster',
        mountPath: '/',
        proxyTo: 'http://mySuperSecretResources.com/'
      })
    ]
  }
}
```

Now when you start up Robohydra alongside the rest of the system. All request towards `/api/resource/:id` will return local data, instead of returning errors because unavailable resources. And while we're talking about errors. You can of course return intended errors for the sake of tests too!

These are my main use cases with Robohydra. By using these methods you can simply create tests clients for your client-server application, return canned responses, static content, reverse proxy requests and a whole lot more. It also comes with a web interface that allow you to change its behaviour dynamically, with easy access to scenarios and test results. Head over to [robohydra.org](http://robohydra.org/) and grab your copy of this awesome tool!

![Robohydra screen](http://tmn.io/img/robohydra_screen.png)

Follow the awesome creator, [@estebanm](https://twitter.com/estebanm) amd [@robohydra](https://twitter.com/robohydra), on Twitter.
