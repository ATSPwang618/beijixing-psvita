#!/bin/bash

# Windows应用程序分发包创建脚本
# 此脚本用于创建可分发的Windows应用程序包

echo "创建Windows应用程序分发包..."

# 确保在Windows目录下
cd "$(dirname "$0")"

# 检查是否存在可执行文件
if [ ! -f "borealis_demo.exe" ]; then
    echo "错误: 找不到 borealis_demo.exe"
    echo "请先运行 build_windows.sh 进行构建"
    exit 1
fi

# 创建分发目录
DIST_DIR="dist/borealis-demo-windows"
rm -rf dist
mkdir -p "$DIST_DIR"

echo "复制文件到分发目录..."

# 复制可执行文件
cp borealis_demo.exe "$DIST_DIR/"

# 复制资源文件
cp -r resources "$DIST_DIR/"

# 复制启动脚本
cp start.bat "$DIST_DIR/"

# 创建README文件
cat > "$DIST_DIR/README.txt" << 'EOF'
Borealis Demo - Windows版本

运行方法:
1. 双击 start.bat 启动应用程序
2. 或者直接运行 borealis_demo.exe

系统要求:
- Windows 7 或更高版本 (64位)
- 无需安装额外的运行时库

文件说明:
- borealis_demo.exe: 主程序
- start.bat: 启动脚本
- resources/: 资源文件目录

项目主页: https://github.com/ATSPwang618/music-player-test

EOF

# 获取文件大小信息
EXE_SIZE=$(du -h borealis_demo.exe | cut -f1)
TOTAL_SIZE=$(du -sh "$DIST_DIR" | cut -f1)

echo "创建分发包信息:"
echo "- 可执行文件大小: $EXE_SIZE"
echo "- 总包大小: $TOTAL_SIZE"
echo "- 分发目录: $DIST_DIR"

# 创建压缩包
echo "创建ZIP压缩包..."
cd dist
zip -r ../borealis-demo-windows.zip borealis-demo-windows/
cd ..

ZIP_SIZE=$(du -h borealis-demo-windows.zip | cut -f1)
echo "- 压缩包大小: $ZIP_SIZE"
echo "- 压缩包位置: $(pwd)/borealis-demo-windows.zip"

echo ""
echo "分发包创建完成！"
echo "可以将 borealis-demo-windows.zip 分发给用户使用。"
