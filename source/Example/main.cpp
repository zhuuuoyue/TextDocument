#include "INumberedList.h"
#include "IBulletedList.h"
#include "ITextDocument.h"
#include "IParagraph.h"
#include "ITable.h"

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
        std::unique_ptr<Column> nameCol = std::make_unique<Column>("Name", stringFormatter, Alignment::LEFT);
        table->AddColumn(std::move(nameCol));
        std::unique_ptr<Column> areaCol = std::make_unique<Column>("Area", doubleFormatter, Alignment::RIGHT);
        table->AddColumn(std::move(areaCol));
        std::unique_ptr<Column> capitalCol = std::make_unique<Column>("Capital", stringFormatter, Alignment::LEFT);
        table->AddColumn(std::move(capitalCol));
        std::unique_ptr<Column> provinceCol = std::make_unique<Column>("Province", boolFormatter, Alignment::CENTER);
        table->AddColumn(std::move(provinceCol));
        std::unique_ptr<Column> positionCol = std::make_unique<Column>("Position", pointFormatter, Alignment::CENTER);
        table->AddColumn(std::move(positionCol));
        std::unique_ptr<Column> rankCol = std::make_unique<Column>("Rank", intFormatter, Alignment::CENTER);
        table->AddColumn(std::move(rankCol));

        table->AddRow(std::vector<std::any>{std::string{ "Hubei" }, 18.59, std::string{ "Wuhan" }, true, Point{ 114, 30 }, 1});
        table->AddRow(std::vector<std::any>{std::string{ "Jiangsu" }, 10.72, std::string{ "Nanjing" }, true, Point{ 118, 32 }, 2});
        table->AddRow(std::vector<std::any>{std::string{ "Shanghai" }, 0.624, std::string{ "Shanghai" }, false, Point{ 121, 31 }, 3});

        doc->AddTextObject(std::move(table));
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
