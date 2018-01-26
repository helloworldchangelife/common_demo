在wpf如果想将窗口设置为透明，我们除了需要将窗口的背景色设置为透明色，还需要将窗口的AllowsTransparency属性设置为true。

在下面的例子中我们加了一个Grid让他显示一个圆形的不规则窗体。

#### 详细代码
```xml
<Window x:Class="October30.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:October30"
        mc:Ignorable="d"
        Title="MainWindow" Height="350" Width="525"
		Visibility="Visible" 
		ResizeMode="NoResize"
		SizeToContent="Manual" 
		WindowStyle="None"
		Background="#00000000" 
		AllowsTransparency="True">
    <Grid x:Name="LayoutRoot" OpacityMask="{x:Null}" Background="#00000000">
        <Ellipse Fill="#FFB7ecda" 
            Stroke="#FF172A9c" 
            StrokeThickness="3"
            HorizontalAlignment="Right" 
            Margin="0,0,140,60" 
            VerticalAlignment="Bottom" Width="138" Height="138">
        </Ellipse>
    </Grid>
</Window>

```
下面我们对上面窗口用到的属性进行介绍。

#### Visibility 属性有3个枚举值 Collapsed,Hidden,Visible

#### ResizeMode 可以根据ResizeMode的枚举值决定用户是否可以改变窗口的尺寸。
- Nosize不能进行改变窗口大小。
- CanMinimize只能进行最小化。
- CanResize允许改变窗口大小。
- CanResizeWithGrip可以改变窗口大小。

#### SizeToContent 可以创建自动放大自身尺寸的窗口。
- Manual 禁止窗口自动改变尺寸。
- Height,Width，Width And Height允许在不同方向上扩展。

#### WindowStyle 这个属性决定了窗口的边框。
- SingleBorderWindow（默认边框）
- Node 标题栏区域被一条细边框代替。当AllowsTransparency为true时必须为这个（透明窗口）

#### AllowsTransparency 
- 设置为true,并且背景色被设置为透明色，Window就允许其他窗口透过它显示。
- false 窗口背后的内容不能显示，透明背景就会呈现黑色。
- 它和WindowStyle=None 时可创建不规则的窗口。
#### 最后的结果。
![image](http://note.youdao.com/yws/public/resource/b81d0fd1b58019bf3975416f1e50e15e/xmlnote/3086D8D75B1D435CABB858CACEC63A0A/8073)