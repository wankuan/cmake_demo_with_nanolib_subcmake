cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE arm-none-eabi-size)

set(MCU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_C_FLAGS_DEBUG "-Og")
set(CMAKE_C_FLAGS_RELEASE "-O3")

add_definitions(
-DUSE_HAL_DRIVER
-DSTM32F429xx
)


#set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")
set(MCU_FLAGS "-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -fdata-sections -ffunction-sections")
# set(CMAKE_C_FLAGS_DEBUG "-O0 -g2 -ggdb")
set(CMAKE_C_FLAGS_DEBUG "-Og")
set(CMAKE_C_FLAGS_RELEASE "-O3")


include_directories(
    APP/inc
    BSP/inc
    CMSIS/inc
    STM32F4xx_HAL_Driver/Inc
    STM32F4xx_HAL_Driver/Inc/Legacy
)
set_property(SOURCE Start_Up/startup_stm32f429xx.s PROPERTY LANGUAGE C)

SET(SRCS
    Start_Up/startup_stm32f429xx.s
    APP/src/main.c
    APP/src/LED.c
    APP/src//stm32f4xx_hal_msp.c
    APP/src/stm32f4xx_it.c
    BSP/src/bsp.c
    BSP/src/ringbuffer.c
    BSP/src/USART_COM.c
    CMSIS/src/system_stm32f4xx.c
    newlib/syscalls.c
)
add_subdirectory(STM32F4xx_HAL_Driver)


set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F429NIHx_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS
 #"--specs=nano.specs -specs=nosys.specs -nostartfiles -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections"
 "-lc -lm -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections"
)
add_executable(${PROJECT_NAME}.elf ${SRCS})
target_link_libraries(${PROJECT_NAME}.elf PUBLIC STM32F4_HAL_LIB)
set(ELF_FILE ${PROJECT_BINARY_DIR}/${execute_dir}/${PROJECT_NAME}.elf)
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Oihex  ${ELF_FILE} ${HEX_FILE}
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"

    COMMAND ${CMAKE_COMMAND} -E copy ${HEX_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin"

    COMMAND ${CMAKE_SIZE} --format=berkeley ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Invoking: Cross ARM GNU Print Size"
)