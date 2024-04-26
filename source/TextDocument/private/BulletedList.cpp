#include "BulletedList.h"

using namespace td;

std::vector<std::string> BulletedList::Generate() const
{
    std::vector<std::string> lines;
    for (const std::string& item : m_items)
    {
        lines.emplace_back(std::string{ "- " } + item);
    }
    return lines;
}