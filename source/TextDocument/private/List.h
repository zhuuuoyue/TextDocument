#pragma once

#include <vector>
#include <string>

namespace td
{
template<class Base>
class List : public Base
{
public:

    virtual void AddItem(const std::string& item) override
    {
        m_items.emplace_back(item);
    }

    virtual void AddItems(const std::vector<std::string>& items) override
    {
        for (const std::string& item : items)
        {
            m_items.emplace_back(item);
        }
    }

protected:

    std::vector<std::string> m_items;
};
}