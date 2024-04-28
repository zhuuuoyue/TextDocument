#pragma once

#include "TextDocumentExports.h"
#include "ITextObject.h"

#include <string>
#include <vector>
#include <memory>

namespace td
{
class BarPlotItem
{
public:

    BarPlotItem(const std::string& label_, const double& value_)
        : label{ label_ }
        , value{ value_ }
    {
    }

    std::string label;
    double value;
};

class TEXT_DOCUMENT_API IValueFormatter
{
public:

    static std::unique_ptr<IValueFormatter> Create();

    virtual ~IValueFormatter();

    virtual std::string Format(double value, std::size_t index, const std::vector<BarPlotItem>& data) const = 0;
};

class TEXT_DOCUMENT_API IBarPlot : public ITextObject
{
public:

    static std::unique_ptr<IBarPlot> Create();

    virtual void SetValueFormatter(std::unique_ptr<IValueFormatter> formatter) = 0;

    virtual void SetPlotWidth(std::size_t width) = 0;

    virtual void AddItem(const BarPlotItem& item) = 0;
    virtual void AddItems(const std::vector<BarPlotItem>& items) = 0;
};
}
