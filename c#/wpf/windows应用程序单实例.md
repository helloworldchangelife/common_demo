
##### 首先我们需要理解一个知识点。
当我们两次运行一个程序时（windows桌面下点击同一个应用），它是两个进程，它们两个之间是作用相同但是毫无关系的。我们

#### 利用mutex实现进程的单例
要使用mutex我们首先需要知道mutex是进程间通信的一个方式，它是存在于操作系统中的。因此两个进程间是可以通过mutex来进行简单的通信。

下面进行详细的介绍。
```cs
 public partial class App : Application
    {
        //1. 定义mutex。
        private System.Threading.Mutex mutex;

        public App()
        {
            //3.注册startup事件。
            this.Startup += AppStartUp;
        }

        //2. 检测程序。
        void AppStartUp(object sender, StartupEventArgs e)
        {
            bool ret;
            mutex = new System.Threading.Mutex(true,"test",out ret);
            if (!ret) //当ret == false 时说明已有一个程序运行起来了。毕竟操作系统只能拥有一个叫"test"的mutex ^-^ !
            {
                MessageBox.Show("嘿嘿我已经运行起来了 ^-^ !!!");
                Environment.Exit(0);
            }
        }
    }
```
这个方法必须保证mutex不被回收，否则就mutex就会新建成功，这样就无法发挥作用了 - ^v^ -!
这个代码写在App.xaml.cs中就好~，毕竟wpf程序入口在这^-^.
下面进行上面成果的演示---->
![single](http://note.youdao.com/yws/public/resource/b81d0fd1b58019bf3975416f1e50e15e/xmlnote/DB4A1318A2EE4320BE08110567BF4DBB/8088)

#### 通过查找process
第二种方法是根据程序的程序名来进行查找同名的程序，若找到的程序数大于1说明有旧的同名程序。（这种方式几乎不用^-^）!
下面给出代码，代码位置和上面第一种方式的一样，写在AppStartUp中就好 --。
```cs
 int processCount = Process.GetProcessesByName("SinglePattem")
                .Where(o => o.Id != Process.GetCurrentProcess().Id).Count();
            if (processCount > 1)
            {
                MessageBox.Show("哈哈，我又被运行了");
                Environment.Exit(0);
            }
```
#### 后记
还有一种我觉的可以常用的方式，就是前言里提到的使用进程间通信方式命名管道。本来想写在这一篇文章中的，但是这样就会使这篇文章内容太多，以后回来看也会不方便，所以呢剩下的那一种利用管道的方法放在下一篇文章中介绍。