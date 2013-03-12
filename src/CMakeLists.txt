set(TARGET qt-patcher)

set(SOURCES
    main.cpp
    patcherapplication.cpp
    arguments.cpp
    binarypatcher.cpp
    textpatcher.cpp
)

add_executable(${TARGET} ${SOURCES})
