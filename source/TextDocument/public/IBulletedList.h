#pragma once

#include "TextDocumentExports.h"
#include "IList.h"

#include <memory>

namespace td
{
class TEXT_DOCUMENT_API IBulletedList : public IList
{
public:

    static std::unique_ptr<IBulletedList> Create();
};
}
