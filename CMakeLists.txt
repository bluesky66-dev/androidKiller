cmake_minimum_required (VERSION 2.6)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(LibOutPutDirectory "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(DllOutPutDirectory "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LibOutPutDirectory})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LibOutPutDirectory})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DllOutPutDirectory})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DllOutPutDirectory})
function(SUBDIRLIST filter curdir)
	IF(filter)
		FILE(GLOB SRC ${curdir}/*.h ${curdir}/*.cpp ${curdir}/*.qml ${curdir}/*.c)
		source_group(${filter} FILES ${SRC})
	ENDIF()
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	FOREACH(child ${children})
	IF(IS_DIRECTORY ${curdir}/${child})
		FILE(GLOB SRC ${curdir}/${child}/*.h ${curdir}/${child}/*.cpp ${curdir}/${child}/*.c ${curdir}/${child}/*.qrc ${curdir}/${child}/*.ui ${curdir}/${child}/*.ts ${curdir}/*.qml)
		source_group(${filter}\\${child} FILES ${SRC})
		SUBDIRLIST(${filter}\\${child} ${curdir}/${child})
	ENDIF()
	ENDFOREACH()
endfunction()

SUBDIRLIST("" ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${LibOutPutDirectory})
include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(ProjectName "androidKiller")
set(OutPutName "androidKiller")
project (${ProjectName})
set(CMAKE_AUTOMOC ON)
cmake_policy(SET CMP0015 NEW)
if(POLICY CMP0020)
	cmake_policy(SET CMP0020 NEW)
endif()

FILE(GLOB_RECURSE MAIN_SRC ./*.h ./*.cpp ./*.c)
FILE(GLOB_RECURSE UIRES ./*.ui)
FILE(GLOB_RECURSE QRC_SOURCE_FILES ./*.qrc)
add_executable(${ProjectName} WIN32 ${MAIN_SRC} ${UIRES} ${QRC_SOURCE_FILES})


set(BuildCommand if not exist ${DllOutPutDirectory}/$<$<CONFIG:Debug>:Qt5Cored.dll>$<$<CONFIG:Release>:Qt5Core.dll> goto Qt5Core\ngoto OK\n:Qt5Core\necho \"cannot find Qt5Core\"\ngoto QtDeployCommand\n:QtDeployCommand\necho \"start deploy\"\ncall ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe ${DllOutPutDirectory}/${OutPutName}.exe
\n:OK\necho \"deploy success\")
add_custom_command(TARGET ${ProjectName}
POST_BUILD
COMMAND  ${BuildCommand}
)

set(BuildCommand echo d|XCOPY \"${CMAKE_CURRENT_SOURCE_DIR}/res\" /S /D /Y \"${DllOutPutDirectory}/res\")
add_custom_command(TARGET ${ProjectName}
POST_BUILD
COMMAND  ${BuildCommand}
)

set(BuildCommand echo d|XCOPY \"${CMAKE_CURRENT_SOURCE_DIR}/bin\" /S /D /Y \"${DllOutPutDirectory}\")
add_custom_command(TARGET ${ProjectName}
POST_BUILD
COMMAND  ${BuildCommand}
)

find_package(Qt5Widgets)
qt5_wrap_ui(ui_FILES ${UIRES})
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

set_property(SOURCE ${ui_FILES} PROPERTY SKIP_AUTOMOC ON)
set_property(SOURCE ${QRC_FILES} PROPERTY SKIP_AUTOMOC ON)

add_definitions(-D _UNICODE)



target_link_libraries(${ProjectName} Qt5::Widgets debug zlibd.lib optimized zlib.lib)
set_target_properties(${ProjectName} PROPERTIES OUTPUT_NAME ${OutPutName})