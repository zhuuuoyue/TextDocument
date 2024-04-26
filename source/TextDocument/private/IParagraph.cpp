#include "IParagraph.h"
#include "Paragraph.h"

using namespace td;

std::unique_ptr<IParagraph> IParagraph::Create()
{
    return std::make_unique<Paragraph>();
}