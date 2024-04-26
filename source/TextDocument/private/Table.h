#pragma once

#include "TextObject.h"
#include "ITable.h"

namespace td
{
class Table final : public TextObject<ITable>
{
public:

    virtual void AddColumn(std::unique_ptr<Column> column) override
    {
        m_columns.emplace_back(std::move(column));
    }

    virtual void AddRow(const std::vector<std::any>& row) override
    {
        m_rows.emplace_back(row);
    }

    virtual void AddRows(const std::vector<std::vector<std::any>>& rows) override
    {
        m_rows.insert(m_rows.end(), rows.begin(), rows.end());
    }

    virtual std::vector<std::string> Generate() const override;

private:

    std::vector<std::vector<std::string>> GenerateCells() const;

    std::vector<std::size_t> RetrieveWidth(const std::vector<std::vector<std::string>>& cells) const;

    std::string GenerateLine(const std::vector<Alignment>& alignments, const std::vector<std::size_t>& columnWidthList, const std::vector<std::string>& row, char separator, char prefix, char suffix) const;

private:

    std::vector<std::unique_ptr<Column>> m_columns;
    std::vector<std::vector<std::any>> m_rows;
};
}
