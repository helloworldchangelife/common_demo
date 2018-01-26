#### PDfSharp
> pdfSharp是c#用来操作pdf格式文件的一个开源库。

pdfSharp可以使用点集来画曲线，直线。。。用来生成矢量图。也可以把inkCanvas转换为矢量图。
下面对pdfsharp画曲线所需要的api，进行简单介绍。其他用法可以去[官网](http://www.pdfsharp.net/wiki/PDFsharpSamples.ashx)查看。

##### 用法

1. 创建pdf对象。
```cs
var document = new Document();
```
2. 新建一个Page对象（设置page大小）。
```cs
var page = new document.AddPage();
page.Width = width ;
page.Height = height;
```
3. 定义XGraphics对象用来画曲线。
```
XGraphics gfx = XGraphics.FromPdfPage(page);
```
4. 设置画曲线的pen
```cs
Color color;
var xColor = XColor.FromArgb(color.A, color.R, color.G, color.B);
pen = new XPen(xColor, inkWidth);
```
5. 画曲线并保存
```cs
gfx.DrawCurve(pen, xpoints, 1);
gfx.Save();
document.Save(filePath);
```
##### 实例

下面对上面介绍的api进行封装，用来实现将inkCanvas转换为pdf(矢量图)

```cs
public class PdfFile
{
    private PdfDocument document;
    private Xpen pen;

    public PdfFile()
    {
        document = new PdfDocument();
    }

     public void Save(string filePath)
    {
        document.Save(filePath);
    }

    public void SetPen(Color color,double Width)
    {
        var xColor = XColor.FromArgb(color.A,color.R,color.G,color.B);
        pen = new XPen(xColor, Width);
    }

    public  void DrawInk(Stroke stroke, XGraphics gfx, double tension)
    {
        if(stroke == null)
        {
            return;
        }
        var StrokePoints = stroke.StylusPoints;
        XPoint[] points = new XPoint[StrokePoints.Count];
        for (int i = 0; i < StrokePoints.Count;i++)
        {
            var point = StrokePoints[i].ToPoint();
            points[i] = new XPoint(point.X, point.Y);
        }
        if (StrokePoints.Count > 1)
        {
            gfx.DrawCurve(pen, points, 1);
        }
    }

    public void DrawInkCanvas(StrokeCollection strokes,double tensio)
    {
        var page = document.AddPage();
        XGraphics gfx = XGraphics.FromPdfPage(page);
        foreach (var item in strokes)
        {
            DrawInk(item,gfx,tensio);
        }
        gfx.Save();
    }
}
```

后面有时间可以扩展更多方法，用法。