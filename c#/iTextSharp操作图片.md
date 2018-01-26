#### itextSharp

>itextSharp 是用来生成PDF文档的c#组件，相当于java版的iText。

下面介绍在pdf中插入图片
再此之前需要先引入两个命名空间：
```cs
using iTextSharp.text;
using iTextSharp.text.pdf;
```
```cs
string imagePath = @"你要打图像开文件的路径";
string fileName  = @"保存后的pdf名称"
Document document = new Document(PageSize.A4);
PdfWriter writer = PdfWriter.GetInstance(document, new FileStream(fileName, FileMode.Create));
document.Open();
itextSharp.text.Image img = TextSharp.text.Image.GetInstance(imagePath);
img.SetSetAbsolutePosition = (0,PageSize.A4.Width - img.Width);
writer.DirectContent.AddImage(img);
document.Close();
```
###### iTextSharp获取图片实例
Image是一个抽象类，所以：
```cs
public static Image getInstance(Uri url);
public static Image getInstance(string filename) ;
```
这两个方法会判断图片的类别，并返回对应类别的对象。
```cs
Image wmf = Image.getInstance(
"../examples/harbour.wmf"); 

Image gif = Image.getInstance("../examples/vonnegut.gif"); 

Image jpeg = Image.getInstance("../examples/myKids.jpg"); 

Image png = Image.getInstance("../examples/hitchcock.png"); 
```
###### 设置图片的位置：
```cs
public void setAbsolutePosition(int absoluteX, int absoluteY) ;
```
###### 使用原始图片数据得到图片实例
```cs
public static Image getInstance(byte[] img);
public static Image getInstance(int width, int height, int components, int bpc, byte data[]);
```
#### 将Visual转换为pdf

###### wpf将控件导出为图片
RenderTargetBitmap类
```cs
 var bitmap = new RenderTargetBitmap((int)bitmapSize.Width, (int)bitmapSize.Height, 96, 96, PixelFormats.Pbgra32);
 bitmap.Render(control);//控件
 var saveEncoder = new TiffBitmapEncoder();saveEncoder.Frames.Add(BitmapFrame.Create(bitmap));
 System.IO.FileStream fs = System.IO.File.Open(fileName, System.IO.FileMode.OpenOrCreate);
 saveEncoder.Save(fs);
 fs.Close();
```
###### 导出图片的格式
可以将控件转换为多种图片格式，支持的Encoder有：
```cs
var saveEncoder = new BmpBitmapEncoder();
```
```cs
var saveEncoder = new GifBitmapEncoder();
```
```cs
var saveEncoder = new JpegBitmapEncoder();
```
```cs
var saveEncoder = new PngBitmapEncoder();
```
```cs
var saveEncoder = new WmpBitmapEncoder();
```
```cs
var saveEncoder = new TiffBitmapEncoder();
```
#### 评价
使用这种方式生成的pdf文件，pdf中保存的图片是位图，而不是矢量图，因此它会失真。原因是使用RenderTargetBitmap导出的图片就是位图
itextSharp 是一个开源库，但是其文档不全，与之对应的java版iText，文档比较齐全，可以观看java itextde1文档进行使用。