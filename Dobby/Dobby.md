# Dobby框架

## 环境配置

使用乌班图进行编译。

## 编译流程

先使用`git clone`到本地，最新版有问题`core/arch/Cpu.h`文件找不到，`git checkout`切换一下分支。

```shell
git clone https://github.com/jmpews/Dobby/tree/master
git checkout 0932d69
#解决办法 https://github.com/jmpews/Dobby/issues/237
```

运行`compile.md`文档中的脚本，安卓运行脚本如下：

```shell
#https://github.com/jmpews/Dobby/blob/master/docs/compile.md
# prepare and download cmake/llvm/ndk
sh scripts/setup_linux_cross_compile.sh #下载需要的环境
python3 scripts/platform_builder.py --platform=android --arch=all --cmake_dir=$HOME/opt/cmake-3.25.2 --llvm_dir=$HOME/opt/llvm-15.0.6 --android_ndk_dir=$HOME/opt/ndk-r25b
```

## 如何使用

编译完成后，在`build`目录下找到对应架构的`libdobby.a/so`文件，打开`Android studio`的`cpp`目录下，创建存放`Dobby`系列文件的目录，将`dobby.h`与`libdobby.a/so`文件存放到该目录下，然后对`CMakeLists.txt`进行修改，点击`Sync Project with Gradle Files`后就可以正常编写`hook`。

```

cmake_minimum_required(VERSION 3.22.1)

project("demo")


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
```

