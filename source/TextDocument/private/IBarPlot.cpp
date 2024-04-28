#include "IBarPlot.h"
#include "BarPlot.h"

using namespace td;

td::IValueFormatter::~IValueFormatter()
{
}

std::unique_ptr<IValueFormatter> td::IValueFormatter::Create()
{
    return std::make_unique<ValueFormatter>();
}

std::unique_ptr<IBarPlot> td::IBarPlot::Create()
{
    return std::make_unique<BarPlot>();
}
