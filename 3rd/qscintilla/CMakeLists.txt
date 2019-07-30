set(ProjectName "qscintilla")
set(OutPutName "qscintilla")
project (${ProjectName})
SUBDIRLIST("" ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_AUTOMOC ON)
set(CMAKE_DEBUG_POSTFIX "d")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lexlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB_RECURSE MAIN_SRC ./*.h ./*.cpp ./*.c)

add_definitions(-D SCINTILLA_QT -D SCI_LEXER -D INCLUDE_DEPRECATED_FEATURES -D QSCINTILLA_MAKE_DLL -D QSCINTILLA_MAKE_DLL)

add_library(${ProjectName} SHARED ${MAIN_SRC})

find_package(Qt5Widgets)
find_package(Qt5PrintSupport)
target_link_libraries(${ProjectName} Qt5::Widgets Qt5::PrintSupport)

set_target_properties(${ProjectName} PROPERTIES OUTPUT_NAME ${OutPutName})