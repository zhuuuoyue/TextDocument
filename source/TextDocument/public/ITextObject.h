#pragma once

#include "TextDocumentExports.h"

#include <vector>
#include <string>

namespace td
{
class TEXT_DOCUMENT_API ITextObject
{
public:

    virtual ~ITextObject();

    virtual void SetIndentation(std::size_t indent) = 0;

    virtual std::size_t GetIndentation() const = 0;

    virtual void SetMarginTop(std::size_t value) = 0;

    virtual std::size_t GetMarginTop() const = 0;

    virtual void SetMarginBottom(std::size_t value) = 0;

    virtual std::size_t GetMarginBottom() const = 0;

    virtual std::vector<std::string> Generate() const = 0;
};
}
