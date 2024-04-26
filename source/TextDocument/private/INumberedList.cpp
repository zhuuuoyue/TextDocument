#include "INumberedList.h"
#include "NumberedList.h"

using namespace td;

std::unique_ptr<INumberedList> INumberedList::Create()
{
    return std::make_unique<NumberedList>();
}