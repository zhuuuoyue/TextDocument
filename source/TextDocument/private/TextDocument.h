#pragma once

#include "ITextDocument.h"

#include <vector>

namespace td
{
class TextDocument : public ITextDocument
{
public:

    virtual void AddTextObject(std::unique_ptr<ITextObject> obj) override;

    virtual std::vector<std::string> GenerateLines() const override;

    virtual bool Save(const std::filesystem::path& filename) const override;

private:

    std::vector<std::unique_ptr<ITextObject>> m_objects;
};
}
