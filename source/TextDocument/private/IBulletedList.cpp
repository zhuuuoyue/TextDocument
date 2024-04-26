#include "IBulletedList.h"
#include "BulletedList.h"

using namespace td;

std::unique_ptr<IBulletedList> IBulletedList::Create()
{
    return std::make_unique<BulletedList>();
}