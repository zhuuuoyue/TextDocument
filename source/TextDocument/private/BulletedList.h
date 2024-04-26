#pragma once

#include "IBulletedList.h"
#include "List.h"
#include "TextObject.h"

namespace td
{
class BulletedList final : public List<TextObject<IBulletedList>>
{
public:

    virtual std::vector<std::string> Generate() const override;
};
}