include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(Vandior_setup_dependencies)

    if (NOT TARGET glm::glm)
        CPMAddPackage("gh:g-truc/glm#0.9.9.8")
    endif ()

    # For each dependency, see if it's
    # already been provided to us by a parent project

    if (NOT TARGET fmtlib::fmtlib)
        CPMAddPackage("gh:fmtlib/fmt#10.2.1")
    endif ()

    if (NOT TARGET spdlog::spdlog)
        if (WIN32)
            CPMAddPackage(
                    NAME
                    spdlog
                    VERSION
                    1.13.0
                    GITHUB_REPOSITORY
                    "gabime/spdlog"
                    OPTIONS
                    "SPDLOG_FMT_EXTERNAL ON"
                    "SPDLOG_ENABLE_PCH ON"
                    "SPDLOG_BUILD_PIC ON"
                    "SPDLOG_WCHAR_SUPPORT ON"
                    "SPDLOG_WCHAR_FILENAMES ON"
                    "SPDLOG_SANITIZE_ADDRESS ON")
        else ()
            CPMAddPackage(
                    NAME
                    spdlog
                    VERSION
                    1.13.0
                    GITHUB_REPOSITORY
                    "gabime/spdlog"
                    OPTIONS
                    "SPDLOG_FMT_EXTERNAL ON"
                    "SPDLOG_ENABLE_PCH ON"
                    "SPDLOG_BUILD_PIC ON"
                    "SPDLOG_SANITIZE_ADDRESS ON")

        endif ()
    endif ()

    if (NOT TARGET Catch2::Catch2WithMain)
        CPMAddPackage("gh:catchorg/Catch2@3.5.2")
    endif ()

    if (NOT TARGET CLI11::CLI11)
        CPMAddPackage("gh:CLIUtils/CLI11@2.3.2")
    endif ()
	
	CPMAddPackage(
	  NAME nlohmann_json
	  VERSION 3.9.1
	  URL https://github.com/nlohmann/json/archive/v3.9.1.tar.gz
	  OPTIONS
		"JSON_BuildTests OFF"
	)
endfunction()
