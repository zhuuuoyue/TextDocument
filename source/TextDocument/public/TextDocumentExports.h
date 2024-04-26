#pragma once

#ifdef TEXT_DOCUMENT_EXPORTS
#define TEXT_DOCUMENT_API __declspec(dllexport)
#else
#define TEXT_DOCUMENT_API __declspec(dllimport)
#endif
