#include "Table.h"

#include <sstream>
#include <cassert>

using namespace td;

std::vector<std::string> Table::Generate() const
{
    std::vector<std::vector<std::string>> cells = GenerateCells();
    std::vector<std::size_t> widthList = RetrieveWidth(cells);

    std::vector<Alignment> alignments;
    std::vector<std::string> headerLabels;
    for (const std::unique_ptr<Column>& column : m_columns)
    {
        if (column)
        {
            alignments.emplace_back(column->align);
            headerLabels.emplace_back(column->title);
        }
        else
        {
            alignments.emplace_back(Alignment::LEFT);
            headerLabels.emplace_back(std::string{});
        }
    }
    std::vector<std::string> grid(m_columns.size(), std::string{});
    std::vector<Alignment> headerAligns(m_columns.size(), Alignment::CENTER);

    std::vector<std::string> result;
    std::string line = GenerateLine(alignments, widthList, grid, '+', '-', '-');
    result.emplace_back(line);
    line = GenerateLine(headerAligns, widthList, headerLabels, '|', ' ', ' ');
    result.emplace_back(line);
    line = GenerateLine(alignments, widthList, grid, '+', '-', '-');
    result.emplace_back(line);
    for (const std::vector<std::string>& row : cells)
    {
        line = GenerateLine(alignments, widthList, row, '|', ' ', ' ');
        result.emplace_back(line);
    }
    line = GenerateLine(alignments, widthList, grid, '+', '-', '-');
    result.emplace_back(line);
    return result;
}

std::vector<std::vector<std::string>> Table::GenerateCells() const
{
    std::vector<std::vector<std::string>> cells;

    for (std::size_t i = 0; i < m_rows.size(); ++i)
    {
        std::vector<std::string> rowCells;
        const std::vector<std::any>& rowValues = m_rows[i];
        for (std::size_t j = 0; j < m_columns.size(); ++j)
        {
            std::string text;
            if (j < rowValues.size())
            {
                const std::any& value = rowValues[j];
                if (const std::unique_ptr<Column>& column = m_columns[j])
                {
                    if (const std::shared_ptr<ICellFormatter>& formatter = column->formatter)
                    {
                        text = formatter->Format(value, i, j, m_rows);
                    }
                }
            }
            rowCells.emplace_back(text);
        }
        cells.emplace_back(rowCells);
    }

    return cells;
}

std::vector<std::size_t> Table::RetrieveWidth(const std::vector<std::vector<std::string>>& cells) const
{
    std::vector<std::size_t> widthList;
    for (const std::unique_ptr<Column>& column : m_columns)
    {
        widthList.emplace_back(column ? column->title.size() : 0);
    }
    for (const std::vector<std::string>& row : cells)
    {
        for (std::size_t i = 0; i < row.size(); ++i)
        {
            if (row[i].size() > widthList[i])
            {
                widthList[i] = row[i].size();
            }
        }
    }
    return widthList;
}

std::string Table::GenerateLine(const std::vector<Alignment>& alignments, const std::vector<std::size_t>& columnWidthList, const std::vector<std::string>& row, char separator, char prefix, char suffix) const
{
    assert(alignments.size() == columnWidthList.size());
    assert(alignments.size() == row.size());

    std::stringstream ss;
    ss << separator;
    for (std::size_t i = 0; i < alignments.size(); ++i)
    {
        ss << prefix;

        std::size_t columnWidth = columnWidthList[i];
        const std::string& text = row[i];
        std::size_t textWidth = text.size();
        assert(columnWidth >= textWidth);
        std::size_t prefixCount{ 0 };
        std::size_t suffixCount{ columnWidth - textWidth };
        if (Alignment::CENTER == alignments[i])
        {
            prefixCount = suffixCount / 2;
            suffixCount = suffixCount - prefixCount;
        }
        else if (Alignment::RIGHT == alignments[i])
        {
            std::swap(prefixCount, suffixCount);
        }

        while (prefixCount)
        {
            ss << prefix;
            --prefixCount;
        }

        ss << text;

        while (suffixCount)
        {
            ss << suffix;
            --suffixCount;
        }

        ss << suffix << separator;
    }
    return ss.str();
}