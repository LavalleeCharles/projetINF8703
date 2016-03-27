cmake_minimum_required(VERSION 3.3)
project(Source)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp
    MainComponent.cpp
    Oscillateur.cpp
    Oscillateur.h
    Midi.cpp
    Midi.h
    Synthesizer.cpp
    Synthesizer.h
    Voice.cpp
    Voice.h
    Envelope.cpp
    Envelope.h)

add_executable(Source ${SOURCE_FILES})