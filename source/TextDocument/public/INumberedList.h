#pragma once

#include "TextDocumentExports.h"
#include "IList.h"

#include <memory>

namespace td
{
class TEXT_DOCUMENT_API INumberedList : public IList
{
public:

    static std::unique_ptr<INumberedList> Create();
};
}