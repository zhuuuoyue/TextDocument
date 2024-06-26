#include "INumberedList.h"
#include "IBulletedList.h"
#include "ITextDocument.h"
#include "IParagraph.h"
#include "ITable.h"
#include "IBarPlot.h"

#include <any>
#include <sstream>

using namespace td;

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

class DoubleFormatter final : public IValueFormatter
{
public:
    virtual std::string Format(double value, std::size_t index, const std::vector<BarPlotItem>& data) const override
    {
        std::stringstream ss;
        if (value < std::numeric_limits<double>::epsilon())
        {
            ss << '(' << std::abs(value) << ')';
        }
        else
        {
            ss << value;
        }
        return ss.str();
    }
};

int main()
{
    std::unique_ptr<ITextDocument> doc = ITextDocument::Create();

    {
        std::unique_ptr<IParagraph> paragraph = IParagraph::Create();
        paragraph->SetText("Hello World");
        doc->AddTextObject(std::move(paragraph));
    }

    {
        std::unique_ptr<IParagraph> header = IParagraph::Create();
        header->SetText("Tab. Province Information");
        doc->AddTextObject(std::move(header));
    }

    {
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
    }

    {
        std::unique_ptr<IBarPlot> plot = IBarPlot::Create();
        plot->AddItems({ {"Hubei", 18.59}, {"Jiangsu", 10.72}, {"Shanghai", 0.624} });
        doc->AddTextObject(std::move(plot));
    }

    {
        std::unique_ptr<IValueFormatter> formatter = std::make_unique<DoubleFormatter>();

        std::unique_ptr<IBarPlot> plot = IBarPlot::Create();
        plot->SetValueFormatter(std::move(formatter));
        plot->AddItems({ {"Beijing", -15}, {"Jiangsu", 2}, {"Guangzhou", 13} });
        doc->AddTextObject(std::move(plot));
    }

    {
        std::unique_ptr<IBarPlot> plot = IBarPlot::Create();
        plot->AddItems({ {"Beijing", -15}, {"Jinan", -8}, {"Zhengzhou", -2} });
        doc->AddTextObject(std::move(plot));
    }

    {
        std::unique_ptr<INumberedList> lst = INumberedList::Create();
        lst->AddItems({ "Hubei", "Jiangsu", "Shanghai" });
        doc->AddTextObject(std::move(lst));
    }

    {
        std::unique_ptr<IBulletedList> lst = IBulletedList::Create();
        lst->AddItems({ "Hubei", "Jiangsu", "Shanghai" });
        doc->AddTextObject(std::move(lst));
    }

    doc->Save("text.txt");
    return 0;
}
