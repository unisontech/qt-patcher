set(TARGET qt-patcher)

set(SOURCES
    main.cpp
    patcherapplication.cpp
    arguments.cpp
    binarypatcher.cpp
    textpatcher.cpp
)

# --- deps ---
if (WIN32)
    add_win32_libs()
endif()

if(MacOSX)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    list(APPEND LIBS ${COCOA_LIBRARY})

    find_library(SYSTEMCONFIGURATION_LIBRARY SystemConfiguration REQUIRED)
    list(APPEND LIBS ${SYSTEMCONFIGURATION_LIBRARY})

    find_library(SECURITY_LIBRARY Security REQUIRED)
    list(APPEND LIBS ${SECURITY_LIBRARY})

    find_library(CARBON_LIBRARY Carbon REQUIRED)
    list(APPEND LIBS ${CARBON_LIBRARY})

    list(APPEND LIBS z)
endif(MacOSX)
# --- eof deps ---


add_executable(${TARGET} ${SOURCES})

qtX_use_modules(
    ${TARGET}
    Core
    )

target_link_libraries(
    ${TARGET}
    ${QT_QTMAIN_LIBRARY}
    ${QT_LIBRARIES}
    ${LIBS}
    )
