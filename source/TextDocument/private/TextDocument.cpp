#include "TextDocument.h"

#include <sstream>
#include <fstream>

using namespace td;

void TextDocument::AddTextObject(std::unique_ptr<ITextObject> obj)
{
    m_objects.emplace_back(std::move(obj));
}

std::vector<std::string> TextDocument::GenerateLines() const
{
    std::vector<std::string> result;
    for (std::size_t i = 0; i < m_objects.size(); ++i)
    {
        const std::unique_ptr<ITextObject>& obj = m_objects[i];
        if (nullptr == obj)
        {
            continue;
        }
        std::size_t margin = i ? obj->GetMarginTop() : 0;
        while (margin)
        {
            result.emplace_back(std::string{});
            --margin;
        }

        std::size_t indent = obj->GetIndentation();
        std::stringstream ss;
        while (indent)
        {
            ss << "    ";
            --indent;
        }
        std::string prefix = ss.str();
        std::vector<std::string> lines = obj->Generate();
        for (const std::string& line : lines)
        {
            result.emplace_back(prefix + line);
        }

        margin = obj->GetMarginBottom();
        while (margin)
        {
            result.emplace_back(std::string{});
            --margin;
        }
    }
    return result;
}

bool TextDocument::Save(const std::filesystem::path& filename) const
{
    bool ret{ false };
    std::ofstream ofs(filename);
    if (ofs.is_open())
    {
        std::vector<std::string> lines = GenerateLines();
        for (const std::string& line : lines)
        {
            ofs << line << '\n';
        }
        ret = true;
    }
    ofs.close();
    return ret;
}