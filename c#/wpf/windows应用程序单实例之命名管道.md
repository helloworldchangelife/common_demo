#### 单一实例应用程序对象设计的思想
既然我们说了使用命名管道来实现这个功能，那们管道是什么呢？
##### 管道的功能
管道是进程间通信的一种方式，我们可以这样想，有两个人，住在两个房子里，他们两在任何时候都无法联系，也就是说这两个人任何时候都不知道他们各自在干什么。但是他们两却想进行一些消息交换，这时该怎么办呢。没错我们可以找第三者权限更大的房主（操作系统），其中一个人A就让房主修了一个管道，另外一个人B也就可以通过这个管道和他交换东西（数据）。B每次想要给A东西的时候就需要找这个管道（connect）。现在呢A和B可以互相拿数据了，但是B找到管道后，向管道内放了个鸡蛋（数据），A不知道，A一天就瘦到管道那才知道B给他东西了，这样A就啥都干不了了。所以A就又想了个办法，安了个门铃，当B connect(寻找)的时候若找到了（触发门铃）。门铃响了A就知道了，A就开始做他一系列的事情（处理数据，发送数据）。
##### 整体思想
现在管道的功能我们也清楚了，就是起个桥梁的作用，沟通两个进程。那么现在进行介绍实现这个功能的思路。

我们知道每个程序的入口都有一个Main函数，所以我们需要在main函数开头进行检测是否已经开启过当前程序。在wpf中main函数是自动生产成的（也可以手动写），所以我们不好加我们的逻辑，但是我们可以知道MAin函数中会实例化一个Application对象，所以我们就有了新的思路。

我们创建一个类SinglePattemApp 继承至Application 这个类就是一个工具类，我们以后实现单例的逻辑就在这个类的构造函数中写（还可以附带其他功能）。当我们的应用程序想要这个功能的时候只需要将wpf应用的App类继承至SinglePattemApp。我们在SinglePattem中可以定义一些事件然后在我们的wpf应用程序中触发（可以实现好多功能）。是不是有点迷惑呢。我们接下来进行介绍SinglePattemApp类的实现思想。
##### SinglePattemApp实现
这一部分是这篇文章的重点，我争取写明白^-^!

1. 首先呢SinglePattemApp需要继承至Application (这个是必须的哦^-^)
2. 实现它的构造函数,这个uniqueAppName就是用来识别的关键。。。
```cs
SinglePattemApp(string uniqueAppName);
```
3. 我们在SingleApp的构造函数中使用uniqueAppName来创建一个命名管道。（这样这个管道就是唯一的，当然我们也可以用uniqueAppName来找这个管道^-^）当然这个管道我们还可以利用uniqueAppName找到。
```cs
try
{
    var server = new NamedPipeServerStream(uniqueAppName,
                    PipeDirection.In, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous);
}
catch(IOException)
{
    return false;
}
catch(UnauthorizedAccessException)
{
    return false;
}
```
4. 上面的代码就是创建一个名字为uniqueAppName的管道，而且这个名字的管道在操作系统中只能有一个。我们就可以根据这个思路来实现我们的单例应用程序了。当第一个应用程序起来时运行上面的代码会成功创建一个管道，不会抛出异常，当不是第一个应用程序的时候运行到上面的代码时，会抛出异常（因为第一个已经建立了这个名字的管道^-^）。所以我们可以根据上面的逻辑就可以判断应用程序是不是已经有一个实例在运行了。
5. 如果只是想实现单例应用程序上面介绍的已经够了，不过如果只是用管道实现这个功能是不是有点大才小用呢，而且上篇文章中介绍的方法要比这个好多了。有的时候我们的应用程序会有这样的一些功能，当应用程序起来时，我们呢继续启动它的另外一个实例，当前这个运行的程序就会触发一些功能，例如激活当前窗口，或弹出一个窗口。那么这是上面的和上篇的方法都达不到了^-^。那我们该怎么办呢？别着急，我们先把上面的逻辑进行封装，封装如下（是不很简单呢^-^只需要在try中return true，catch中return false就可以了）：
```
//return true 当前应用程序时第一个实例
//return false 不是第一个实例。
bool Checkout(string uniqueAppName);
```
6. 既然我们想当运行起其他程序实例时，已经运行的程序触发一些事件，去做一些提示，或者其他事情。那么我们该怎么样通知到已经运行的程序呢（就是一开时介绍的门铃^-^）。这个时候我们就使用命名管道的BeginWaitForConnection方法，它会注册一个回调，当有人连接这个管道时触发（connect）。注册回调当然应该加到Checkout中去：
```
var server = new NamedPipeServerStream(uniqueAppName,
                    PipeDirection.In, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous);
server.BeginWaitForConnection(OnWaitConnection, server);//OnWaitConnection就是我们注册的方法^-^
```
7. 现在我们只需要在OnWaitConnetcion中进行处理连接，继续注册回调。下面介绍OnWaitConnection方法。当然我们需要处理这个管道,所以我们需要把上面的Server当参数传进去。
```cs
//S就是上面的server ^-^
private void OnWaitForConnection(object s)
{
    var sever = (NamedPipeServerStream)s ;
    //1.do something  
    server.Disconnect();
    //重新注册这样以后都会触发了。
    server.BeginWaitForConnection(OnWaitConnection, server);
    //2 do something
    //例如触发一些子类注册的事件。
}
```
8. 我们可以在第2步的dosomething中触发一些事件，这些事件需要我们在我们的应用程序中进行注册。^-^此时是不是就豁然开朗了呢，没错我们的提示信息，弹窗口等等一系列事都可以注册在这些事件中。
9. 讲到这剩下的就不多了，就剩下是我们在SinglePattemApp的构造函数中做的一些处理根据Checkout返回值进行分别处理。
```cs
SinglePattemApp(string uniqueAppName)
{
    //dosomething
    bool result = Checkout(uniqueAppName)
    if(!result)//抛出异常返回false 说明不是第一个
    {
        //创建NamedPipeClientStream进行连接接uniqueAppName的管道
        //此时第一个程序就会触发OnWaitForConnection
        //此处就可一结束进程了 exit()退出了.
         Environment.Exit(0);
    }
    //dosomething
}
```
这样一个简单的程序单实例就完成了，当然想要这个功能我们得继承它---->SinglePattemApp。
