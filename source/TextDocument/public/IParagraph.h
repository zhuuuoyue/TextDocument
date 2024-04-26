#pragma once

#include "TextDocumentExports.h"
#include "ITextObject.h"

#include <string>
#include <memory>

namespace td
{
class TEXT_DOCUMENT_API IParagraph : public ITextObject
{
public:

    static std::unique_ptr<IParagraph> Create();

    virtual void SetText(const std::string& text) = 0;

    virtual const std::string& GetText() const = 0;
};
}