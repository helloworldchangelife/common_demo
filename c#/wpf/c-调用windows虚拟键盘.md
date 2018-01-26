
调用windows自带的tabtip.exe来调用虚拟键盘。

我们在textBox获取焦点时候进行调用虚拟键盘
<!--more-->
```cs
 private void textBox_GotFocus(object sender, RoutedEventArgs e)
{
try
{
    dynamic file = "C:\\Program Files\\Common Files\\microsoft  shared\\ink\\TabTip.exe";
    if (!System.IO.File.Exists(file))
        return;
    Process.Start(file);
}
catch (Exception)
{
}     


}
```

失去焦点进行关闭虚拟键盘
```cs
private const Int32 WM_SYSCOMMAND = 274;
private const UInt32 SC_CLOSE = 61536;
[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
private static extern bool PostMessage(IntPtr hWnd, int Msg, uint wParam, uint lParam);
[DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
private void textBox_LostFocus(object sender, RoutedEventArgs e)
{
    IntPtr TouchhWnd = new IntPtr(0);
    TouchhWnd = FindWindow("IPTip_Main_Window", null);
    if (TouchhWnd == IntPtr.Zero)
        return;
    PostMessage(TouchhWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}
```