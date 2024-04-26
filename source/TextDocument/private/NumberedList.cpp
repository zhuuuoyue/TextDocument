#include "NumberedList.h"

using namespace td;

std::vector<std::string> NumberedList::Generate() const
{
    std::vector<std::string> lines;
    for (std::size_t i = 0; i < m_items.size(); ++i)
    {
        lines.emplace_back(std::to_string(i + 1) + ". " + m_items[i]);
    }
    return lines;
}