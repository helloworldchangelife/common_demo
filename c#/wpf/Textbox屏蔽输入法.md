我们知道WPF中的Textbox控件中默认是允许输入法的，也就是说我们可以在TextBox中输入中文。
假设我们现在要求用户只能输入键盘上的字符，也就是说不能输入中文，韩文等字符。这时我们该怎么办呢？

一般情况下的TextBox（最最普通的直接拖出来的）
XMAL代码为
```
 <TextBox x:Name="phoneNumber"/>
```
- 此时的效果为：

![image](http://note.youdao.com/yws/public/resource/0fc3d02c47a8f7216e6bf44d810c5a9a/xmlnote/34D8946206394868A36902C6E363BBBA/7309)

下面我们介绍Wpf如何屏蔽输入法的步骤。
1. 在XAMl中引入命名空间我们重命名为input
```
xmlns:input="clr-namespace:System.Windows.Input;assembly=PresentationCore"
```
2.修改TextBox的代码
```
<TextBox x:Name="phoneNumber" input:InputMethod.IsInputMethodEnabled="False"/>
```

- 此时效果：

![image](http://note.youdao.com/yws/public/resource/0fc3d02c47a8f7216e6bf44d810c5a9a/xmlnote/7AF6F88AD2B649669DEA8E6EE3CF963E/7334)

我在测试时不管怎么切换输入法都无法输入中文。所以我们的效果已经达到了。
