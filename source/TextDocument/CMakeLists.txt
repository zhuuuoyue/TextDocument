cmake_minimum_required(VERSION 3.8)
project(TextDocument)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DTEXT_DOCUMENT_EXPORTS)

include_directories(
    ${PROJECT_SOURCE_DIR}/public
    ${PROJECT_SOURCE_DIR}/private
)

set(PUBLIC_FILES
    ${PROJECT_SOURCE_DIR}/public/TextDocumentExports.h
    ${PROJECT_SOURCE_DIR}/public/ITextDocument.h
    ${PROJECT_SOURCE_DIR}/public/ITextObject.h
    ${PROJECT_SOURCE_DIR}/public/IList.h
    ${PROJECT_SOURCE_DIR}/public/IBulletedList.h
    ${PROJECT_SOURCE_DIR}/public/INumberedList.h
    ${PROJECT_SOURCE_DIR}/public/IParagraph.h
    ${PROJECT_SOURCE_DIR}/public/ITable.h
    ${PROJECT_SOURCE_DIR}/public/IBarPlot.h
)

set(PRIVATE_FILES
    ${PROJECT_SOURCE_DIR}/private/IBulletedList.cpp
    ${PROJECT_SOURCE_DIR}/private/BulletedList.h
    ${PROJECT_SOURCE_DIR}/private/BulletedList.cpp
    ${PROJECT_SOURCE_DIR}/private/INumberedList.cpp
    ${PROJECT_SOURCE_DIR}/private/NumberedList.h
    ${PROJECT_SOURCE_DIR}/private/NumberedList.cpp
    ${PROJECT_SOURCE_DIR}/private/IParagraph.cpp
    ${PROJECT_SOURCE_DIR}/private/Paragraph.h
    ${PROJECT_SOURCE_DIR}/private/Paragraph.cpp
    ${PROJECT_SOURCE_DIR}/private/ITable.cpp
    ${PROJECT_SOURCE_DIR}/private/Table.h
    ${PROJECT_SOURCE_DIR}/private/Table.cpp
    ${PROJECT_SOURCE_DIR}/private/ITextDocument.cpp
    ${PROJECT_SOURCE_DIR}/private/TextDocument.h
    ${PROJECT_SOURCE_DIR}/private/TextDocument.cpp
    ${PROJECT_SOURCE_DIR}/private/List.h
    ${PROJECT_SOURCE_DIR}/private/ITextObject.cpp
    ${PROJECT_SOURCE_DIR}/private/TextObject.h
    ${PROJECT_SOURCE_DIR}/private/IBarPlot.cpp
    ${PROJECT_SOURCE_DIR}/private/BarPlot.h
    ${PROJECT_SOURCE_DIR}/private/BarPlot.cpp
)

source_group("public" FILES ${PUBLIC_FILES})
source_group("private" FILES ${PRIVATE_FILES})

add_library(TextDocument SHARED
    ${PUBLIC_FILES}
    ${PRIVATE_FILES}
)
