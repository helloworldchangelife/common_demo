这种实例的用途一般是在，我们输入信息时，信息不满足条件，我们可以使textbox重新获取焦点。
<!--more-->
我们在使用TextBox输入登录账号时，通常会有对输入数据的检测，当输入数据不合法时，失去焦点的TextBox控件，在获取焦点让用户修改输入。

这个该如何做呢？我们可以在TextBox的LostFoucs事件中获取焦点，但是如果直接调用Focus()方法会出现死循环的问题。

下面我们给出一种解决方案。

```cs
private void VaildationData(object sender, RoutedEventArgs e)
{
     if (phoneNumber.Text != "abc")
    { 
        this.Dispatcher.BeginInvoke(
        System.Windows.Threading.DispatcherPriority.Render,
        new Action(() =>
        {
            phoneNumber.Focus();
        }));
    }
}
```
上面就是TextBox对应的的LostFocus事件。

下面我们进行一个实例。
- 我们以简单的登陆界面为例。

对应的XAML界面为
```xml
    //只关心 phoneNumber对应的TextBox
    <Grid>
        <StackPanel Name="stackPanel">
            <Label HorizontalAlignment="Center" >账号登陆</Label>
            <TextBox x:Name="phoneNumber" LostFocus="VaildationData"></TextBox>
            <TextBox x:Name="password"></TextBox>
            <Button>登陆</Button>
            <Label HorizontalAlignment="Center">其他登陆方式</Label>
            <StackPanel Orientation="Horizontal" HorizontalAlignment="Center">
                <Button>游客登陆</Button>
                <Button>扫码登陆</Button>
            </StackPanel>
        </StackPanel>
    </Grid>
```

我们对应的cs文件就是上面所介绍的方法，上面LostFoucs事件中。当我们输入的不是abc且TextBox失去焦点的时候，Focus会自动获取焦点。这就完成了我们一开始介绍的问题。

- 我们现在看下此时的现象

![image](http://note.youdao.com/yws/public/resource/0fc3d02c47a8f7216e6bf44d810c5a9a/xmlnote/F7AE94249596410BB34E271DFC35B2BB/7473)

我们可以看出当我们输入123的时候，不管怎么点击其他按钮，焦点还是在TextBox中，
当我们输入abc的时候，点击了登陆后焦点已经转到登录按钮了。

现在我们就完成了TextBox自动获取焦点的问题，并且没有死循环。