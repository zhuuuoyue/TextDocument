#include "ITextDocument.h"
#include "TextDocument.h"

using namespace td;

std::unique_ptr<ITextDocument> ITextDocument::Create()
{
    return std::make_unique<TextDocument>();
}

ITextDocument::~ITextDocument()
{
}