# Making mobile apps using Fuse
Sunday 22 November 2015

There's a new kid in town! In October 2015 the peoples over at Fuse announced their new UX tool suite for building awesome mobile applications as an open BETA. A tool meant to bring designers and developer closer together.

I tried it for the first time back in 2013, and a lot have changed since. With the much improved UX Markup and the integration of JavaScript you can easily get around creating great looking apps in no time. For the more advanced users, Fuse also let you access the native APIs directly using their own language called Uno, a native C# dialect. And if you are familiar with C#, nearly everything you know will apply to Uno code. While playing around with Fuse, I created a simple app displaying the bus departures time in Trondheim, Norway. You can grab the code on [my GitHub page](https://github.com/tmn/FuseBus).

There are of course other tools out there letting you create and deploy application on multiple platforms. But the cool thing about Fuse is its ability to push updates of the look and feel to multiple devices in real time. So for every bits of design and logic you change, Fuse will stream the changes to all connected devices while developing. Now the designers can flip pixels while the developer is writing the business logic, and all changes is reflected in real time in the application. No need to re-compile. You **really** have to try it!

![Fuse](http://tmn.io/img/fusetools.jpg)

## Native apps

Fuse code compiles down to native C++. So the code you write will run natively on each platform. Only Android and iOS is supported for the time being. This may change in the future.


## Trying out Fuse

In order to start exploring Fuse all you need is to download and install the tool itself from [fusetools.com](https://fusetools.com/). Their site is also the best reference for learning Fuse.

The Fuse team provides great tutorial videos for you to get started with creating awesome apps. Some bits are less documented in the documentation, but you'll get an idea of what it can do. And there is enough information to get around. Fuse also has a growing community. And the whole team is actively answering questions you might have :-)



## Creating our first app!

We will start out simple by using only UX Markup. UX Markup is a XML-based format that should be immediately familiar to anyone who has worked with similar formats. The root tag of your application is the `<App>` tag. This one bootstraps the app and takes care of the application lifecycle.

```xml
<App Theme="Basic" Background="#fff">
  <Text>This is header!</Text>
</App>
```


### Reusable classes

The main .ux file might grow out of scale, and you might want to tighten it up by extracting some of the code, and make reusable components. This is achieved by declaring bits of the code as classes. They all can be contained inside the main .ux file like this:

```xml
<App>
  <Panel ux:Class="MyAwesomePanel">
    <Text FontSize="14">This is my awesome panel!</Text>
  </Panel>

  <!-- and use it here!-->
  <MyAwesomePanel />
  <MyAwesomePanel />
  <MyAwesomePanel />
  <MyAwesomePanel />
</App>
```

... or you can create a separate file like this:

```xml
<Panel ux:Class="MyAwesomePanel">
  <Text FontSize="14">This is my awesome panel!</Text>
</Panel>
```

And use it as the example above. No need for extra include statements.



## JavaScript

UX Markup itself can do magic, and other things like animations, triggers, interactions, and much more. But sometimes you need more. You need some kind of business logic. The app needs to do _something_. This is easily done by using JavaScript. The JavaScript itself will run through JavaScriptCore on iOS, and V8 on Android.

Here is an example on how you can write JavaScript for your Fuse app:

```javascript
function click_handler() {
  debug_log('I just got clicked!');
}

module.exports = {
  click_handler: click_handler
}
```

And including it inside your .ux file:
```xml
<App>
  <JavaScript File="js/app.js" />
  <Button Clicked="{click_handler}" Text="Click me!" />
</App>
```

### Multiple JavaScript files/modules

One thing you might wanna do is to split the JavaScript into different modules. Because, you simply don't want to write your whole app in one huge JavaScript file! Requiring other modules is easy:

```xml
<App>
  <JavaScript File="js/MyComponent.js" ux:Global="MyComponent" />
  <JavaScript File="js/app.js" />
</App>
```

js/MyComponent.js:
```javascript
function MyComponent() {
  // .. do awesome stuff here!
}

module.exports = MyComponent;
```

js/app.js:
```javascript
var MyComponent = require('MyComponent');

//...
```

Notice the use of `ux:Global` when including the JavaScript file in the `.ux` file. The file is still included without the `ux:Global` attribute. But to access it from other JavaScript code you need to give it a name.


## Exposing native APIs with Uno

Uno is a native dialect of #C where you have direct access to Android and iOS APIs. I'll use the same example as they do in [the documentation](https://www.fusetools.com/learn/uno#creating-new-fusejs-modules).

Let's start out creating a `SystemSound.uno`. This uno class will provide system notification functionality in the JavaScript. To do this we need to import the iOS and Android audio packages:

```csharp
using Android.android.media;
using Android.android.app;
using iOS.AudioToolbox;
```


When creating a native module for JavaScript we have to manually define the members returned when it is used. Else it wont return anything. To do this we adds the members inside the constructor like this:

```csharp
public SystemSounds()
{
  AddMember(new NativeFunction("playNotification", (NativeCallback) PlayNotification));
}
```

Now the calling JavaScript will get access to the `playNotification` function.

Next, we need to create the callback function `PlayNotification`. And since the Android and iOS API doesn't work the same way, we can't use the same code for both. It is therefore required to implement the functionality for each platform we want to support:

```csharp
object PlayNotification(Context c, object[] args)
{
  if defined (Android)
  {
    var uri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
    var ringtone = RingtoneManager.getRingtone(Activity.GetAppActivity(), uri);
    ringtone.play();
  }
  else if defined (iOS)
  {
    Functions.AudioServicesPlaySystemSound(1310);
  }

  return null;
}
```

The PlayNotification function takes two arguments (`Context c, object[] args`). The first one is the running JavaScript context, and the second is the arguments that will be passed to the function by the JavaScript. This example doesn't need any of them. And we don't want to get anything in return either, so it will just return `null`.

The whole code would look something like this:

```csharp
using Uno;
using Fuse.Scripting;
using Fuse.Reactive;

using Android.android.media;
using Android.android.app;
using iOS.AudioToolbox;

public class SystemSounds : NativeModule
{
  public SystemSounds()
  {
    AddMember(new NativeFunction("playNotification", (NativeCallback) PlayNotification));
  }

  object PlayNotification(Context c, object[] args)
  {
    if defined(Android)
    {
      var uri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
      var ringtone = RingtoneManager.getRingtone(Activity.GetAppActivity(), uri);
      ringtone.play();
    }
    else if defined (iOS)
    {
      Functions.AudioServicesPlaySystemSound(1310);
    }

    return null;
  }
}
```

### Let's use our new module!


Next up is to use our new module inside our application. This is done by calling it from the `.ux` file:

```xml
<App>
  <SystemSounds ux:Global="SystemSounds" />
  <JavaScript File="js/app.js" />

  <Button Clicked="{playSound}" Text="Play sound!" />
</App>
```

Which makes it avaiable as `SystemSound` to the JavaScript:

```javascript
var SystemSounds = require('SystemSounds');

function playSound() {
  SystemSound.playNotification();
}

module.exports = {
  playSound: playSound
};
```

The Fuse team is rapidly implementing these kinds of abstractions inside the Fuse API. But you might come over native features that is not yet implemented. And by having access to the .uno code, you're free to make them yourself.


## To sum it up

This was just a short introduction to what Fuse can do, and how you easily could get started on your new app project. It's super easy to set up, and very familiar if you've done some coding before. Especially if you have written code for the web. There are many more important things to learn about Fuse, like animations, interactions, triggers and more. And I couldn't cover it all in this post. However I believe that this quick read will help you get on track and the rest would be piece of cookies!

I've of course experienced some random crashes and bugs in the Fuse process at this early stage. Although this does not affect the application itself, it may be some kind of frustrating while writing it. But I'll say that it's wroth it. I really thinks this is a promising tool with great peoples working on it.

Head over to [fusetools.com](https://fusetools.com/) and check it out yourself. And make sure to check out the [examples](https://www.fusetools.com/examples) too!
