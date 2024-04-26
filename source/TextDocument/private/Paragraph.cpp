#include "Paragraph.h"

using namespace td;

std::vector<std::string> Paragraph::Generate() const
{
    return std::vector<std::string>{ m_text };
}