OPTION(ENABLE_NETLIB "Adds networking to the Project" OFF)

if(ENABLE_NETLIB)
    # fetch project
    include(FetchContent)
    FetchContent_Declare(
            netlib
            GIT_REPOSITORY https://github.com/Halichoerus/NetLibrary
            GIT_TAG        v0.05-alpha)

    FetchContent_GetProperties(netlib)
    if(NOT netlib_POPULATED)
        FetchContent_Populate(netlib)
        add_subdirectory(${netlib_SOURCE_DIR} ${netlib_BINARY_DIR})
    endif()

    # lets not worry about compile warnings
    target_compile_options(
            NetLib
            INTERFACE
            $<$<COMPILE_LANGUAGE:CXX>:-w -fpermissive>)

    #add_dependencies(${PROJECT_NAME} NetLib)
    #target_link_libraries(${PROJECT_NAME}  NetLib)
endif()

if(LIB_RELEASE)

    set(NET_BIN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/netlib/bin)
    set(NET_LIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/netlib/lib)

    find_library(libNetLib REQUIRED
            NAMES NetLib.${POSTFIX}.dll.a
            libGameEngine${POSTFIX}.so
            libGameEngine${POSTFIX}.dylib ASGE${POSTFIX}
            PATHS ${NET_LIB_DIRECTORY} NO_DEFAULT_PATH)
    message("netlib: " ${libNetLib} )

    set_property (
            TARGET NetLib PROPERTY
            IMPORTED_LOCATION
            ${libNetLib})

    set(libNetLib ${libNetLib})

    find_library(libNetDLL REQUIRED
            NAMES NetLib.dd${POSTFIX}.dll
            PATHS ${NET_BIN_DIRECTORY} NO_DEFAULT_PATH)

    message("libNetDLL: " ${libNetDLL} )
    set(libNetDLL ${libNetDLL} PARENT_SCOPE)
endif()
