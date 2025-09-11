#!/bin/bash

# Windows 64位构建脚本
# 此脚本用于在Linux环境下交叉编译Windows 64位应用程序

echo "开始构建Windows 64位应用程序..."

# 检查MinGW-w64工具链是否安装
if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
    echo "错误: MinGW-w64工具链未安装"
    echo "请运行: sudo apt-get update && sudo apt-get install -y mingw-w64"
    exit 1
fi

# 创建构建目录
mkdir -p build_windows
cd build_windows

# 运行CMake配置
echo "配置CMake..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=../library/borealis/library/lib/extern/SDL/build-scripts/cmake-toolchain-mingw64-x86_64.cmake \
         -DCMAKE_BUILD_TYPE=Release \
         -DPLATFORM_DESKTOP=ON

# 编译项目
echo "开始编译..."
make -j$(nproc)

# 复制资源文件
echo "复制资源文件..."
cp -r ../resources .

# 检查是否生成了可执行文件
if [ -f "borealis_demo.exe" ]; then
    echo "构建成功！"
    echo "可执行文件位置: build_windows/borealis_demo.exe"
    echo "文件大小: $(du -h borealis_demo.exe | cut -f1)"
    
    # 运行文件检查
    file borealis_demo.exe
else
    echo "构建失败：未找到可执行文件"
    exit 1
fi

echo "Windows构建完成！"
