#pragma once

#include "IParagraph.h"
#include "TextObject.h"

namespace td
{
class Paragraph final : public TextObject<IParagraph>
{
public:

    virtual void SetText(const std::string& text) override
    {
        m_text = text;
    }

    virtual const std::string& GetText() const override
    {
        return m_text;
    }

    virtual std::vector<std::string> Generate() const override;

private:

    std::string m_text;
};
}
