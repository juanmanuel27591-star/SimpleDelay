cmake_minimum_required(VERSION 3.22)

project(SimpleDelay VERSION 0.1.0)

set(CMAKE_CXK_STANDARD 17)
set(CMAKE_CXK_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.4
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(SimpleDelay
    COMPANY_NAME "Portfolio"
    IS_SYNTH FALSE
    NEEDS_MIDI INPUT FALSE
    NEEDS_MIDI OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE Prtf
    PLUGIN_CODE Sdly
    FORMATS VST3 Standalone
    PRODUCT_NAME "Simple Delay"
)

target_sources(SimpleDelay PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_compile_definitions(SimpleDelay PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(SimpleDelay
    PRIVATE
        juce::juce_audio_utils
    PUBLIC 
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

