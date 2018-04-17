### WebBrowser渲染
如下图其中 ShDocVw 及以下就是WebBrowser的内容，Browser UI不属于WebBrowser。
@import "ie.png"
不少软件都内嵌了IE的WebBrowser控件（也就是MSHTML.dll）来显示网页， 当用户机器升级到某个IE版本时， WebBrowser控件也会随之升级到相应的Ie对应的渲染引擎。为了保证WebBrowser控件能够正常工作，不同ie版本的WebBrowser控件在默认情况下使用ie7的渲染模式。
修改ie
- 使用注册表检测是否安装ie，并获取ie的版本号。
```cs
RegistryKey mainKey = Microsoft.Win32.Registry.LocalMachine;
RegistryKey subKey = mainKey.OpenSubKey(@"SOFTWARE\Microsoft\Internet Explorer");
if (subKey == null)
{
    Console.WriteLine("未安装ie");
    return;
}else
{
    object value = subKey.GetValue("Version");
}
```
下面获取主版本号。
```cs
char[] separator = {'.'};
var mywords = value.Split(separator);
var mainVersion = mywords[0];
```
在我的机器上面从注册表中获取的版本号比ie上的版本号低，所以不能这样操作。
#### wpf中ie版本号对应的解决方案：
- 使用winForms中webBrowser的Version属性
```cs 
var version = new WebBrowser().Version.Major;
```
此时获取的版本号与 ie中看到的相同。

- 另外一种注册表获取
```cs
public static string GetVersion()
{
    RegistryKey browserKeys;
    //on 64bit the browsers are in a different location
    browserKeys = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\WOW6432Node\Clients\StartMenuInternet\IEXPLORE.EXE\shell\open\command");
    if (browserKeys == null)
        browserKeys = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Clients\StartMenuInternet\IEXPLORE.EXE\shell\open\command");
    if (browserKeys != null)
    {
        var filepath = browserKeys.GetValue(null)?.ToString();
        if (!string.IsNullOrEmpty(filepath))
        {
            return FileVersionInfo.GetVersionInfo(filepath)?.FileVersion;
        }
    }
    return null;
}
```
利用一开始讲到的方法获取主版本号
```cs
char[] separator = {'.'};
var mywords = GetVersion()?.Split(separator);
if(mywords != null)
    var mainVersion = mywords[0];
```