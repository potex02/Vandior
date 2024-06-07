# Enable cache if available
function(Vandior_enable_cache)
    set(CACHE_OPTION
            "ccache"
            CACHE STRING "Compiler cache to be used")
    set(CACHE_OPTION_VALUES "ccache" "sccache")
    set_property(CACHE CACHE_OPTION PROPERTY STRINGS ${CACHE_OPTION_VALUES})
    list(
            FIND
            CACHE_OPTION_VALUES
            ${CACHE_OPTION}
            CACHE_OPTION_INDEX)

    if (${CACHE_OPTION_INDEX} EQUAL -1)
        message(
                STATUS
                "Using custom compiler cache system: '${CACHE_OPTION}', explicitly supported entries are ${CACHE_OPTION_VALUES}"
        )
    endif ()

    # Find the program for the selected cache option
    find_program(CACHE_BINARY NAMES ${CACHE_OPTION_VALUES})

    if (CACHE_BINARY)
        message(STATUS "Cache binary '${CACHE_BINARY}' found and enabled. Compiler cache will be used.")

        # Additional security checks to ensure CACHE_BINARY is executable
        if (EXISTS ${CACHE_BINARY} AND IS_EXECUTABLE ${CACHE_BINARY})
            # Set the compiler launcher properties securely
            set(CMAKE_CXX_COMPILER_LAUNCHER
                    ${CACHE_BINARY}
                    CACHE FILEPATH "CXX compiler cache used" FORCE)
            set(CMAKE_C_COMPILER_LAUNCHER
                    ${CACHE_BINARY}
                    CACHE FILEPATH "C compiler cache used" FORCE)
        else ()
            message(WARNING "The found cache binary '${CACHE_BINARY}' is not executable. Not using it.")
        endif ()
    else ()
        message(WARNING "${CACHE_OPTION} is enabled but was not found. Not using it.")
    endif ()
endfunction()
