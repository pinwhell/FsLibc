file(GLOB fslc_SRC src/*.c)
file(GLOB fslc_INC include/fslc/*.h)
file(GLOB fslc_SINC include/*.h)

add_library(fslc ${fslc_SRC})
target_include_directories(fslc PUBLIC include/fslc)
if(NOT ENABLE_STANDARD_SYMNAMES)
	target_compile_definitions(fslc PUBLIC ALT_FSLC_NAMES)
endif()

install(TARGETS fslc DESTINATION lib)
install(FILES ${fslc_SINC} DESTINATION include)
install(FILES ${fslc_INC} DESTINATION include/fslc)
