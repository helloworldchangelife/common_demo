### wpf webBrowser控件
#### 介绍
WebBrowsers可以让我们在窗体中进行导航网页。
WebBrowser控件内部使用ie的引擎，因此使用WebBrowser我们必须安装ie浏览器（windows默认安装的）。
#### 使用
直接在xmal中使用webBrowser控件
```xml
<WebBrowser x:Name="WebBrowser1" Source ="xxx.com"></WebBrowser>
```
其中Source熟悉可以将webBrowser控件指向一个网页（也可以是本地文件的绝对路径）
除了使用Source属性还有以下方法进行导航：

方法 | 用法
----|----
`Navigate()` |传入网页url ` WebBrowser1.Navigate(new Uri(address));`
`NavigateToString`|传入html页面内容` WebBrowser1.NavigateToString("<html><body></body></html > ");`
`GoBack()`| 导航到上一个文档，需要判断能否调用` if (WebBrowser1.CanGoBack){WebBrowser1.GoBack();}`
`GoForward`|导航到下一个文档`if (WebBrowser1.CanGoForward){WebBrowser1.GoForward();}`

事件|发生时间|用法
-|-|-
`Navigating` | 发生在导航到新的页面时发生，可以在这里取消导航|` WebBrowser1.Navigating += (sender, args) ={args.Cancel = true;};`
`Navigated`| 导航之后，在下载web页面之前引发|` WebBrowser1.Navigated += (sender, args) =>{Console.WriteLine("ed" + args?.Uri);};`
`LoadCompleteed`|当web页面下载完成时引发这个事件，这时可以处理网页|`WebBrowser1.LoadCompleted += (sender, args)=>{Console.WriteLine(WebBrowser1.Document);};`

#### 问题
- js报错
默认情况下webBrowser用的是比较低的ie内核，这样如果访问的网页有不支持的脚本或者其他问题，就会没有办法正常运行，比如报错 javaScript错误。
    - 避免报错不弹提示框。
    ```cs
    WebBrowser1.Navigated += (sender, args) =>
    {
         SetSilent(wbMain, true)
    }   
    ```
    ```cs
    public static void SetSilent(WebBrowser browser, bool silent)
    {
        if (browser == null)
         throw new ArgumentNullException("browser");

        // get an IWebBrowser2 from the document
        IOleServiceProvider sp = browser.Document as IOleServiceProvider;
        if (sp != null)
        {
            Guid IID_IWebBrowserApp = new Guid("0002DF05-0000-0000-C000-000000000046");
            Guid IID_IWebBrowser2 = new Guid("D30C1661-CDAF-11d0-8A3E-00C04FC9E26E");

            object webBrowser;
            sp.QueryService(ref IID_IWebBrowserApp, ref IID_IWebBrowser2, out webBrowser);
            if (webBrowser != null)
            {
             webBrowser.GetType().InvokeMember("Silent", BindingFlags.Instance | BindingFlags.Public | BindingFlags.PutDispProperty, null, webBrowser, new object[] { silent });
            }
        }
    }
    [ComImport, Guid("6D5140C1-7436-11CE-8034-00AA006009FA"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    private interface IOleServiceProvider
    {
        [PreserveSig]
        int QueryService([In] ref Guid guidService, [In] ref Guid riid, [MarshalAs(UnmanagedType.IDispatch)] out object ppvObject);
    }
    ```
    这种只是让它不出现报错窗口，不能从根本上解决。
    - 修改注册表使用新的ie内核,下面是代码：
    ```cs
     static void SetWebBrowserFeatures(int ieVersion)
        {
            if (LicenseManager.UsageMode != LicenseUsageMode.Runtime)
                return;
            var appName = System.IO.Path.GetFileName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName);
            UInt32 ieMode = GeoEmulationModee(ieVersion);
            var featureControlRegKey = @"HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Main\FeatureControl\";
            Registry.SetValue(featureControlRegKey + "FEATURE_BROWSER_EMULATION",
                appName, ieMode, RegistryValueKind.DWord);
            Registry.SetValue(featureControlRegKey + "FEATURE_ENABLE_CLIPCHILDREN_OPTIMIZATION",
                appName, 1, RegistryValueKind.DWord);
        }

        static UInt32 GeoEmulationModee(int browserVersion)
        {
            UInt32 mode = 11000; // Internet Explorer 11. Webpages containing standards-based !DOCTYPE directives are displayed in IE11 Standards mode. 
            switch (browserVersion)
            {
                case 7:
                    mode = 7000; // Webpages containing standards-based !DOCTYPE directives are displayed in IE7 Standards mode. 
                    break;
                case 8:
                    mode = 8000; // Webpages containing standards-based !DOCTYPE directives are displayed in IE8 mode. 
                    break;
                case 9:
                    mode = 9000; // Internet Explorer 9. Webpages containing standards-based !DOCTYPE directives are displayed in IE9 mode.                    
                    break;
                case 10:
                    mode = 10000; // Internet Explorer 10.
                    break;
                case 11:
                    mode = 11000; // Internet Explorer 11
                    break;
            }
            return mode;
        }
    ```
    比如你想使用最新的IE11
    ```cs
     SetWebBrowserFeatures(11);
    ```
    - 在网页中强制以ie最高级别的可用模式显示内容
    ```html
    <meta http-equiv="X-UA-Compatible" content="edge" />
    ```
- 内存泄漏
[Memory leak when using WPF WebBrowser control in multiple windows
](https://stackoverflow.com/questions/8302933/how-to-get-around-the-memory-leak-in-the-net-webbrowser-control)
内存泄漏的解决方式
    - 不使用wpf中的 WebBrowser
    - 将WebBrowser放到子进程中，每次开关都会重新分配内存
    - 删除掉所有引用，来清理内存泄漏。关闭窗口时调用下面代码。
    ```cs
        public void Dispose()
        {
            webBrowser.Dispose();

            var window = GetWindowElement(webBrowser);

            if (window == null)
                return;

            var field = typeof(Window).GetField("_swh", BindingFlags.NonPublic | BindingFlags.Instance);

            var valueSwh = field.GetValue(window);
            var valueSourceWindow = valueSwh.GetType().GetField("_sourceWindow", BindingFlags.Instance | BindingFlags.NonPublic).GetValue(valueSwh);
            var valuekeyboardInput = valueSourceWindow.GetType().GetField("_keyboardInputSinkChildren", BindingFlags.Instance | BindingFlags.NonPublic).GetValue(valueSourceWindow);

            var inputSites = valuekeyboardInput as IEnumerable<IKeyboardInputSite>;

            if (inputSites == null)
                return;

            var currentSite = inputSites.FirstOrDefault(s => ReferenceEquals(s.Sink, webBrowser));

            if (currentSite != null)
                currentSite.Unregister();
        }

        private static Window GetWindowElement(DependencyObject element)
        {
            while (element != null && !(element is Window))
            {
                element = VisualTreeHelper.GetParent(element);
            }

            return element as Window;
        }
    ```