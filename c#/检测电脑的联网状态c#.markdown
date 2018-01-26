##### 获取电脑联网状态
1. 声明外部函数

```cs
[DllImport("winInet.dll")]
private static extern bool InternetGetConnectState(ref int flag,int dwReserved);
```
2. 使用当返回为true时说明有网，返回false则没有网。

```cs
int flag = 0;
bool result = InternetGetConnectState(ref flag,0);
```
3. 根据flag判断连接类型

```cs
if(result)
{
    if(flag & 1 != 0)//调制解调器
    {
    }
    if(flag & 2 != 0)//网卡
    {
    }
    if(flag & 4 != 0)//代理
    {
    }
    if(flag & 8 != 0)
    {
    }
}
```
