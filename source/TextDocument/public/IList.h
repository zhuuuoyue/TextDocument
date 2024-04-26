#pragma once

#include "TextDocumentExports.h"
#include "ITextObject.h"

namespace td
{
class TEXT_DOCUMENT_API IList : public ITextObject
{
public:

    virtual void AddItem(const std::string& item) = 0;

    virtual void AddItems(const std::vector<std::string>& items) = 0;
};
}