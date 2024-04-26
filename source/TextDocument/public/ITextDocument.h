#pragma once

#include "TextDocumentExports.h"

#include <memory>
#include <vector>
#include <string>
#include <filesystem>

#include "ITextObject.h"

namespace td
{
class TEXT_DOCUMENT_API ITextDocument
{
public:

    static std::unique_ptr<ITextDocument> Create();

    virtual ~ITextDocument();

    virtual void AddTextObject(std::unique_ptr<ITextObject> obj) = 0;

    virtual std::vector<std::string> GenerateLines() const = 0;

    virtual bool Save(const std::filesystem::path& filename) const = 0;
};
}