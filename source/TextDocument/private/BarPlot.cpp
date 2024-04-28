#include "BarPlot.h"

#include <sstream>
#include <cassert>

#include "Utils.h"

using namespace td;

std::vector<std::string> BarPlot::Generate() const
{
    std::vector<std::string> result;
    if (m_items.empty() || 0 == m_plotWidth)
    {
        return result;
    }

    PlotData plotData;
    if (!RetrieveLabelWidth(plotData) || !RetrieveMinMaxValues(plotData))
    {
        return result;
    }
    std::vector<BarData> bars;
    if (!RetrieveBarData(plotData, bars))
    {
        return result;
    }

    for (const BarData& bar : bars)
    {
        AppendDataLine(plotData, bar, result);
    }
    return result;
}

bool BarPlot::RetrieveLabelWidth(PlotData& plotData) const
{
    plotData.labelLen = 0;
    for (const BarPlotItem& item : m_items)
    {
        if (item.label.size() > plotData.labelLen)
        {
            plotData.labelLen = item.label.size();
        }
    }
    return true;
}

bool BarPlot::RetrieveMinMaxValues(PlotData& plotData) const
{
    if (m_items.empty())
    {
        return false;
    }

    plotData.minValue = std::numeric_limits<double>::max();
    plotData.maxValue = std::numeric_limits<double>::min();
    for (const BarPlotItem& item : m_items)
    {
        if (item.value > plotData.maxValue)
        {
            plotData.maxValue = item.value;
        }
        if (item.value < plotData.minValue)
        {
            plotData.minValue = item.value;
        }
    }

    if (IsPositive(plotData.minValue))
    {
        plotData.minValue = 0;
    }
    if (IsNegative(plotData.maxValue))
    {
        plotData.maxValue = 0;
    }
    return true;
}

bool td::BarPlot::RetrieveBarData(PlotData& plotData, std::vector<BarData>& barDataVec) const
{
    const IValueFormatter* formatter = m_valueFormatter.get();
    std::unique_ptr<IValueFormatter> defaultFormatter;
    if (nullptr == formatter)
    {
        defaultFormatter = std::make_unique<ValueFormatter>();
        formatter = defaultFormatter.get();
    }
    if (nullptr == formatter)
    {
        return false;
    }

    double range = plotData.maxValue - plotData.minValue;
    double rightPlotLen = plotData.maxValue / range * m_plotWidth;
    double leftPlotLen = m_plotWidth - rightPlotLen;
    for (std::size_t i = 0; i < m_items.size(); ++i)
    {
        const BarPlotItem& item = m_items[i];

        BarData barData;
        barData.label = item.label;

        if (GreaterThanOrEqualTo(item.value, 0)) // zero or positive
        {
            barData.rightValue = item.value;
            barData.rightLabel = formatter->Format(item.value, i, m_items);
            if (IsPositive(plotData.maxValue))
            {
                barData.rightBar = static_cast<std::size_t>(std::round(item.value / plotData.maxValue * rightPlotLen));
            }

            std::size_t len = barData.rightLabel.size() + barData.rightBar;
            if (len > plotData.rightLen)
            {
                plotData.rightLen = len;
            }
        }
        else
        {
            barData.leftValue = item.value;
            barData.leftLabel = formatter->Format(item.value, i, m_items);
            if (IsNegative(plotData.minValue))
            {
                barData.leftBar = static_cast<std::size_t>(std::round(item.value / plotData.minValue * leftPlotLen));
            }

            std::size_t len = barData.leftLabel.size() + barData.leftBar;
            if (len > plotData.leftLen)
            {
                plotData.leftLen = len;
            }
        }

        barDataVec.emplace_back(barData);
    }
    return true;
}

void BarPlot::AppendDataLine(const PlotData& plotData, const BarData& barData, std::vector<std::string>& lines) const
{
    assert(plotData.leftLen >= (barData.leftLabel.size() + barData.leftBar));

    std::stringstream ss;
    std::size_t c{ 0 };

    if (IsNegative(plotData.minValue))
    {
        c = plotData.leftLen - barData.leftLabel.size() - barData.leftBar;
        while (c--) { ss << ' '; }
        ss << barData.leftLabel << ' ';
        c = barData.leftBar;
        while (c--) { ss << '#'; }
        ss << '|' << ' ';
    }

    if (IsNegative(barData.leftValue))
    {
        ss << barData.label;
        c = plotData.labelLen - barData.label.size();
        while (c--) { ss << ' '; }
    }

    if (IsPositive(barData.rightValue))
    {
        c = plotData.labelLen - barData.label.size();
        while (c--) { ss << ' '; }
        ss << barData.label;
    }

    if (IsPositive(plotData.maxValue))
    {
        ss << ' ' << '|';
        c = barData.rightBar;
        while (c--) { ss << '#'; }
        ss << ' ' << barData.rightLabel;
    }

    lines.emplace_back(ss.str());
}
