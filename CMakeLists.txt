
cmake_minimum_required(VERSION 3.22.1)

project("demo")

#https://blog.51cto.com/u_16213447/11755035?

#添加dobby.h头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dobby/includes)

# 指定 libdobby.a 静态库路径
set(LIBDOBBY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dobby/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
)



target_link_libraries(${CMAKE_PROJECT_NAME}
        ${LIBDOBBY_PATH}
        # List libraries link to the target library
        android
        log)