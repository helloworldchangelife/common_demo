##### windows自带pdf打印生成pdf
我们可以调用c#的PrintDialog进行将Visual打印为pdf
下面这个代码默认调用windows的pdf打印机
```cs
PrintDialog dialog = new PrintDialog();
dialog.PrintVisual(VisualObject,"print hint Message");
```
这个产生的pdf中的图片为矢量图，但是其不好控制，PrintVisual会弹出保存路径的窗口，不易生成我们需要的定制版。

##### 实现自己的打印机
