#pragma once

#include "INumberedList.h"
#include "List.h"
#include "TextObject.h"

namespace td
{
class NumberedList final : public List<TextObject<INumberedList>>
{
public:

    virtual std::vector<std::string> Generate() const override;
};
}