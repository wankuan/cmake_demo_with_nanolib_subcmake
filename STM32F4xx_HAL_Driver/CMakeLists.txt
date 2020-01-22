file(GLOB sources Src/*.c)
add_library(STM32F4_HAL_LIB ${sources})

target_include_directories(STM32F4_HAL_LIB PUBLIC Inc)
target_include_directories(STM32F4_HAL_LIB PUBLIC Inc/Legacy)

set(HSE_VALUE 25000000)

# set up some defines for the StdPeriph library

target_compile_definitions(STM32F4_HAL_LIB PUBLIC STM32F429xx)
target_compile_definitions(STM32F4_HAL_LIB PUBLIC USE_HAL_DRIVER)
target_compile_definitions(STM32F4_HAL_LIB PUBLIC HSE_VALUE=${HSE_VALUE})

# # additional compiler options: use size-optimized version of library in release build, use -O0 in debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -Os)
endif()

target_compile_options(STM32F4_HAL_LIB PRIVATE ${additional_flags})
