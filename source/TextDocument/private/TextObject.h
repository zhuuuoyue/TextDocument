#pragma once

#include <utility>

namespace td
{
template<class Base>
class TextObject : public Base
{
public:

    virtual void SetIndentation(std::size_t indent) override
    {
        m_indent = indent;
    }

    virtual std::size_t GetIndentation() const override
    {
        return m_indent;
    }

    virtual void SetMarginTop(std::size_t value) override
    {
        m_marginTop = value;
    }

    virtual std::size_t GetMarginTop() const override
    {
        return m_marginTop;
    }

    virtual void SetMarginBottom(std::size_t value) override
    {
        m_marginBottom = value;
    }

    virtual std::size_t GetMarginBottom() const override
    {
        return m_marginBottom;
    }

protected:

    std::size_t m_indent{ 0 };
    std::size_t m_marginTop{ 1 };
    std::size_t m_marginBottom{ 0 };
};
}
