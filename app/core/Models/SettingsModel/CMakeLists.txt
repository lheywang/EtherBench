# =================================================================================
# @file CMakeLists.txt
#
# @brief SettingsModel build file
# =================================================================================

# Create the SettingsModel library
set(SOURCES
    SettingsModel.cpp
    ConfigNode/ConfigNode.cpp
    ConfigLoader/ConfigLoader.cpp
)

qt_add_library(EtherBenchModelsSettings STATIC ${SOURCES})

target_link_libraries(EtherBenchModelsSettings PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
)


target_include_directories(EtherBenchModelsSettings PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)