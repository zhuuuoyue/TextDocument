# TextDocument

在调试程序时，我们需要查看内存中的数据，有时还需要分析这些数据之间的关系。当数据量过大时，调试起来非常困难，将这些数据结构化地输出是一个非常有用的手段。XML 和 JSON 文件格式通用，但是快速查看这些数据也比较困难。

TextDocument 是一个结构化输出纯文本文件的工具，通过面向对象的设计，允许程序用户可以自定义输出的格式。

## 功能

支持插入以下文字块：

- 插入段落

```txt
Hello World
```

- 插入有序列表

```txt
1. Hubei
2. Jiangsu
3. Shanghai
```

- 插入无序列表

```txt
- Hubei
- Jiangsu
- Shanghai
```

- 插入表格

```txt
+----------+-----------+----------+----------+-------------+------+
|   Name   |   Area    | Capital  | Province |  Position   | Rank |
+----------+-----------+----------+----------+-------------+------+
| Hubei    | 18.590000 | Wuhan    |    *     | [ 114, 30 ] |  1   |
| Jiangsu  | 10.720000 | Nanjing  |    *     | [ 118, 32 ] |  2   |
| Shanghai |  0.624000 | Shanghai |          | [ 121, 31 ] |  3   |
+----------+-----------+----------+----------+-------------+------+
```

- 插入条形图

```txt
(15) ######################################################| Beijing   | 
                                                           |   Jiangsu |####### 2
                                                           | Guangzhou |############################################## 13
```

## 编译

编译 TextDocument 需要编译器支持 C++17 标准，建议使用 Visual Studio 2022 和 CMake 进行编译。

```bash
git clone https://github.com/zhuuuoyue/TextDocument.git
cd TextDocument
mkdir build
cd build
cmake ../source
```

在 `build` 文件夹下，生成了解决方案 `TextDoc.sln` 文件，使用 Visual Studio 2022 打开，点击 Build 进行编译，编译输出位于 `bin/Debug` 文件夹下。

## 使用

使用 TextDocument 可以参考 `source/Example` 工程。

```cpp
int main()
{
    std::unique_ptr<ITextDocument> doc = ITextDocument::Create();

    std::unique_ptr<IParagraph> paragraph = IParagraph::Create();
    paragraph->SetText("Hello World");
    doc->AddTextObject(std::move(paragraph));

    std::unique_ptr<INumberedList> numbered = INumberedList::Create();
    numbered->AddItems({ "Hubei", "Jiangsu", "Shanghai" });
    doc->AddTextObject(std::move(numbered));

    std::unique_ptr<IBulletedList> bulleted = IBulletedList::Create();
    bulleted->AddItems({ "Hubei", "Jiangsu", "Shanghai" });
    doc->AddTextObject(std::move(bulleted));

    doc->Save("text.txt");
    return 0;
}
```

TextDocument 也支持用户通过继承自定义输出格式。

```cpp
class Point
{
public:

    explicit Point(double x_, double y_) : x{ x_ }, y{ y_ } {}

    double x{ 0 };
    double y{ 0 };
};

class PointFormatter final : public ICellFormatter
{
public:

    std::string Format(const std::any& value, std::size_t row, std::size_t col, const std::vector<std::vector<std::any>>& data) const override
    {
        if (!value.has_value())
        {
            return std::string();
        }
        Point pt = std::any_cast<Point>(value);
        std::stringstream ss;
        ss << "[ " << pt.x << ", " << pt.y << " ]";
        return ss.str();
    }
};

int main()
{
    std::unique_ptr<ITextDocument> doc = ITextDocument::Create();

    std::shared_ptr<CellFormatter<std::string>> stringFormatter = std::make_shared<CellFormatter<std::string>>();
    std::shared_ptr<CellFormatter<double>> doubleFormatter = std::make_shared<CellFormatter<double>>();
    std::shared_ptr<CellFormatter<int>> intFormatter = std::make_shared<CellFormatter<int>>();
    std::shared_ptr<CellFormatter<bool>> boolFormatter = std::make_shared<CellFormatter<bool>>();
    std::shared_ptr<ICellFormatter> pointFormatter = std::make_shared<PointFormatter>();

    std::unique_ptr<ITable> table = ITable::Create();
    table->SetMarginTop(0);
    table->AddColumn("Name", stringFormatter, Alignment::LEFT);
    table->AddColumn("Area", doubleFormatter, Alignment::RIGHT);
    table->AddColumn("Capital", stringFormatter, Alignment::LEFT);
    table->AddColumn("Province", boolFormatter, Alignment::CENTER);
    table->AddColumn("Position", pointFormatter, Alignment::CENTER);
    table->AddColumn("Rank", intFormatter, Alignment::CENTER);

    table->AddRow(std::vector<std::any>{std::string{ "Hubei" }, 18.59, std::string{ "Wuhan" }, true, Point{ 114, 30 }, 1});
    table->AddRow(std::vector<std::any>{std::string{ "Jiangsu" }, 10.72, std::string{ "Nanjing" }, true, Point{ 118, 32 }, 2});
    table->AddRow(std::vector<std::any>{std::string{ "Shanghai" }, 0.624, std::string{ "Shanghai" }, false, Point{ 121, 31 }, 3});

    doc->AddTextObject(std::move(table));
    doc->Save("text.txt");
    return 0;
}
```

Example 程序输出内容如下：

```txt
Hello World

Tab. Province Information
+----------+-----------+----------+----------+-------------+------+
|   Name   |   Area    | Capital  | Province |  Position   | Rank |
+----------+-----------+----------+----------+-------------+------+
| Hubei    | 18.590000 | Wuhan    |    *     | [ 114, 30 ] |  1   |
| Jiangsu  | 10.720000 | Nanjing  |    *     | [ 118, 32 ] |  2   |
| Shanghai |  0.624000 | Shanghai |          | [ 121, 31 ] |  3   |
+----------+-----------+----------+----------+-------------+------+

1. Hubei
2. Jiangsu
3. Shanghai

- Hubei
- Jiangsu
- Shanghai
```
