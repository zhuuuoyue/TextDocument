#include "ITable.h"
#include "Table.h"

using namespace td;

ICellFormatter::~ICellFormatter()
{
}

std::unique_ptr<ITable> ITable::Create()
{
    return std::make_unique<Table>();
}