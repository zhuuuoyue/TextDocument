#pragma once

#include "IBarPlot.h"
#include "TextObject.h"

namespace td
{
class ValueFormatter final : public IValueFormatter
{
public:

    virtual std::string Format(double value, std::size_t index, const std::vector<BarPlotItem>& data) const override
    {
        return std::to_string(value);
    }
};

struct PlotData
{
    double minValue{ 0 };
    double maxValue{ 0 };
    std::size_t leftLen{ 0 };
    std::size_t rightLen{ 0 };
    std::size_t labelLen{ 0 };
};

struct BarData
{
    std::string leftLabel;
    double leftValue{ 0 };
    std::size_t leftBar{ 0 };

    std::string label;

    double rightValue{ 0 };
    std::string rightLabel;
    std::size_t rightBar{ 0 };
};

class BarPlot final : public TextObject<IBarPlot>
{
public:

    virtual void SetValueFormatter(std::unique_ptr<IValueFormatter> formatter) override
    {
        m_valueFormatter = std::move(formatter);
    }

    virtual void SetPlotWidth(std::size_t width) override
    {
        m_plotWidth = width;
    }

    virtual void AddItem(const BarPlotItem& item) override
    {
        m_items.emplace_back(item);
    }

    virtual void AddItems(const std::vector<BarPlotItem>& items) override
    {
        m_items.insert(m_items.end(), items.begin(), items.end());
    }

    virtual std::vector<std::string> Generate() const override;

private:

    bool RetrieveLabelWidth(PlotData& plotData) const;

    bool RetrieveMinMaxValues(PlotData& plotData) const;

    bool RetrieveBarData(PlotData& plotData, std::vector<BarData>& barDataVec) const;

    void AppendDataLine(const PlotData& plotData, const BarData& barData, std::vector<std::string>& lines) const;

private:

    std::unique_ptr<IValueFormatter> m_valueFormatter;
    std::vector<BarPlotItem> m_items;
    std::size_t m_plotWidth{ 60 };
};
}
