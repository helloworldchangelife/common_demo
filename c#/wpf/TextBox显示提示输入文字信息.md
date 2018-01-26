
直接上代码
 <!--more-->
```xml
<TextBox x:Name="password">
    <TextBox.Resources>
        <VisualBrush x:Key="HelpBrush" TileMode="None" Opacity="0.3" Stretch="None" AlignmentX="Left">
            <VisualBrush.Visual>
                <TextBlock>请输入密码</TextBlock>
            </VisualBrush.Visual>
        </VisualBrush>
    </TextBox.Resources>
    <TextBox.Style>
        <Style TargetType="TextBox">
            <Style.Triggers >
                <Trigger Property="Text" Value="{x:Null}">
                    <Setter Property="Background" Value="{StaticResource HelpBrush}"></Setter>
                </Trigger>
                <Trigger Property="Text" Value="">
                    <Setter Property="Background" Value="{StaticResource HelpBrush}"></Setter>
                </Trigger>  
            </Style.Triggers>
        </Style>
    </TextBox.Style>
</TextBox>
```
对应的结果：

![image](http://note.youdao.com/yws/public/resource/0fc3d02c47a8f7216e6bf44d810c5a9a/xmlnote/BF753430113B42BF86323F256FCCDCEA/7526)