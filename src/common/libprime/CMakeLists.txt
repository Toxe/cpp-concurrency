add_library(prime
    prime.cpp
    prime.h
)

set_target_properties(prime PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(prime PUBLIC cxx_std_20)
target_compile_options(prime PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
target_link_libraries(prime PRIVATE ${SANITIZER_FLAGS})
target_include_directories(prime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
