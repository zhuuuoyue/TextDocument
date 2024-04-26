#pragma once

#include "TextDocumentExports.h"
#include "ITextObject.h"

#include <string>
#include <any>
#include <memory>

namespace td
{
enum class Alignment
{
    LEFT, CENTER, RIGHT
};

class TEXT_DOCUMENT_API ICellFormatter
{
public:

    virtual ~ICellFormatter();

    virtual std::string Format(const std::any& value, std::size_t row, std::size_t col, const std::vector<std::vector<std::any>>& data) const = 0;
};

template<class T>
class CellFormatter : public ICellFormatter
{
public:

    virtual std::string Format(const std::any& value, std::size_t row, std::size_t col, const std::vector<std::vector<std::any>>& data) const override
    {
        return value.has_value() ? std::to_string(std::any_cast<T>(value)) : std::string{};
    }
};

template<>
class CellFormatter<std::string> : public ICellFormatter
{
public:

    virtual std::string Format(const std::any& value, std::size_t row, std::size_t col, const std::vector<std::vector<std::any>>& data) const override
    {
        return value.has_value() ? std::any_cast<std::string>(value) : std::string{};
    }
};

template<>
class CellFormatter<bool> : public ICellFormatter
{
public:

    virtual std::string Format(const std::any& value, std::size_t row, std::size_t col, const std::vector<std::vector<std::any>>& data) const override
    {
        return value.has_value() ? (std::any_cast<bool>(value) ? "*" : "") : std::string{};
    }
};

class TEXT_DOCUMENT_API Column
{
public:

    template<class T>
    Column(const std::string& title_ = "", Alignment align_ = Alignment::LEFT)
        : title{ title_ }
        , formatter{ std::make_shared<CellFormatter<T>>() }
        , align{ align_ }
    {
    }

    Column() {}

    Column(const std::string& title_, std::shared_ptr<ICellFormatter> formatter_, Alignment align_ = Alignment::LEFT)
        : title{ title_ }
        , formatter{ formatter_ }
        , align{ align_ }
    {
    }

    std::string title;
    std::shared_ptr<ICellFormatter> formatter;
    Alignment align{ Alignment::LEFT };
};

class TEXT_DOCUMENT_API ITable : public ITextObject
{
public:

    static std::unique_ptr<ITable> Create();

    virtual void AddColumn(std::unique_ptr<Column> column) = 0;

    virtual void AddColumn(const std::string& title, std::shared_ptr<ICellFormatter> formatter, Alignment align) = 0;

    virtual void AddRow(const std::vector<std::any>& row) = 0;

    virtual void AddRows(const std::vector<std::vector<std::any>>& rows) = 0;
};
}
