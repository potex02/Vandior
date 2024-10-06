macro(Vandior_enable_ipo)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)
  if(result)
    message(STATUS "Inter Procedural Optimization (IPO) is supported. Enabling IPO.")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(WARNING "Inter Procedural Optimization (IPO) is not supported: ${output}")
    message(STATUS "Please check your compiler settings or update your compiler.")
  endif()
endmacro()
