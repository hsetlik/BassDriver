cmake_minimum_required(VERSION 3.22)
# Version is needed by JUCE.
project(BassDriver VERSION 0.1.0)
# Adding a directory with the library/application name as a subfolder of the
# include folder is a good practice. It helps avoid name clashes later on.

# set up a BinaryData with our fonts
set(FONTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fonts")

juce_add_binary_data(fontsLib
HEADER_NAME FontBinary.h
NAMESPACE FontBinary
SOURCES
"${FONTS_DIR}/arial_narrow.ttf"
"${FONTS_DIR}/bebas_neue_rg.otf"
"${FONTS_DIR}/highway_gothic_condensed.ttf"
"${FONTS_DIR}/kenyan_coffee_rg.otf"
"${FONTS_DIR}/kenyan_coffee_rg_it.otf"
)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/BassDriver")
# Adds a plugin target (that's basically what the Projucer does).

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME Setlik # change this
    IS_SYNTH FALSE # may change this
    NEEDS_MIDI_INPUT FALSE # may change this
    NEEDS_MIDI_OUTPUT FALSE # may change this
    PLUGIN_MANUFACTURER_CODE STLK # change this
    PLUGIN_CODE BDVR # change this
    FORMATS Standalone VST3  AU # may change this
    PRODUCT_NAME "BassDriver" # change this
    COPY_PLUGIN_AFTER_BUILD TRUE 
)

# Sets the source files of the plugin project.
target_sources(${PROJECT_NAME}
    PRIVATE
# Shared Files----------------------------
        source/Identifiers.cpp
        source/Common.cpp
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        ${INCLUDE_DIR}/Identifiers.h
        ${INCLUDE_DIR}/Common.h
        ${INCLUDE_DIR}/PluginEditor.h
        ${INCLUDE_DIR}/PluginProcessor.h

# Audio files------------------------------
        ${INCLUDE_DIR}/Audio/IIRFilter.h
        ${INCLUDE_DIR}/Audio/CompressorDSP.h
        ${INCLUDE_DIR}/Audio/SaturatorDSP.h
        ${INCLUDE_DIR}/Audio/MasterDSP.h
        ${INCLUDE_DIR}/Audio/EqualizerDSP.h
        ${INCLUDE_DIR}/Audio/ValueSmoother.h
        ${INCLUDE_DIR}/Audio/RollingAverage.h
        source/IIRFilter.cpp
        source/CompressorDSP.cpp
        source/SaturatorDSP.cpp
        source/MasterDSP.cpp
        source/EqualizerDSP.cpp
        source/RollingAverage.cpp

# GUI files------------------------------
        ${INCLUDE_DIR}/GUI/ParamSlider.h
        ${INCLUDE_DIR}/GUI/DrivePanel.h
        ${INCLUDE_DIR}/GUI/InputPanel.h
        ${INCLUDE_DIR}/GUI/CompressorPanel.h
        ${INCLUDE_DIR}/GUI/CompressorGraph.h
        ${INCLUDE_DIR}/GUI/EqualizerPanel.h
        ${INCLUDE_DIR}/GUI/CustomLookAndFeel.h
        source/ParamSlider.cpp
        source/DrivePanel.cpp
        source/InputPanel.cpp
        source/CompressorPanel.cpp
        source/CompressorGraph.cpp
        source/EqualizerPanel.cpp
        source/CustomLookAndFeel.cpp
)

# Sets the include directories of the plugin project.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Links to all necessary dependencies. The present ones are recommended by JUCE.
# If you use one of the additional modules, like the DSP module, you need to specify it here.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        fontsLib
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        juce::juce_dsp
)


# These definitions are recommended by JUCE.
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)
# Enables all warnings and treats warnings as errors.
# This needs to be set up only for your projects, not 3rd party
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# In Visual Studio this command provides a nice grouping of source files in "filters".
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/..)

