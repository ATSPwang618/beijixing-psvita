#!/bin/bash

echo "=== PlayStation Vita 开发环境打包工具 ==="
echo "正在创建完整的 PSV 开发包..."

# 创建打包目录
PACKAGE_DIR="/tmp/vita_dev_package"
mkdir -p "$PACKAGE_DIR"

echo "1. 打包 VitaSDK..."
cd /usr/local
sudo tar -czf "$PACKAGE_DIR/vitasdk-complete.tar.gz" vitasdk/
echo "   VitaSDK 打包完成: $(du -sh $PACKAGE_DIR/vitasdk-complete.tar.gz | cut -f1)"

echo "2. 打包项目文件..."
cd /workspaces
tar -czf "$PACKAGE_DIR/borealis_template.tar.gz" \
    --exclude="borealis_template/build_psv" \
    --exclude="borealis_template/.git" \
    --exclude="borealis_template/android-project/app/build" \
    --exclude="borealis_template/android-project/.gradle" \
    borealis_template/
echo "   项目文件打包完成: $(du -sh $PACKAGE_DIR/borealis_template.tar.gz | cut -f1)"

echo "3. 创建安装脚本..."
cat > "$PACKAGE_DIR/install.sh" << 'EOF'
#!/bin/bash

echo "=== PlayStation Vita 开发环境安装器 ==="

# 检查是否为 root
if [[ $EUID -eq 0 ]]; then
   echo "请不要以 root 身份运行此脚本"
   exit 1
fi

# 检查系统
if ! command -v apt &> /dev/null; then
    echo "错误: 此安装器需要 Ubuntu/Debian 系统"
    exit 1
fi

echo "1. 安装系统依赖..."
sudo apt update
sudo apt install -y build-essential cmake git pkg-config libssl-dev

echo "2. 安装 VitaSDK..."
if [ -f "vitasdk-complete.tar.gz" ]; then
    sudo tar -xzf vitasdk-complete.tar.gz -C /usr/local/
    echo "VitaSDK 安装完成"
else
    echo "错误: 找不到 vitasdk-complete.tar.gz"
    exit 1
fi

echo "3. 设置环境变量..."
VITASDK_ENV="export VITASDK=/usr/local/vitasdk"
PATH_ENV="export PATH=\$VITASDK/bin:\$PATH"

if ! grep -q "VITASDK" ~/.bashrc; then
    echo "$VITASDK_ENV" >> ~/.bashrc
    echo "$PATH_ENV" >> ~/.bashrc
    echo "环境变量已添加到 ~/.bashrc"
fi

echo "4. 解压项目文件..."
if [ -f "borealis_template.tar.gz" ]; then
    tar -xzf borealis_template.tar.gz
    echo "项目文件解压完成"
else
    echo "错误: 找不到 borealis_template.tar.gz"
    exit 1
fi

echo ""
echo "=== 安装完成! ==="
echo ""
echo "请运行以下命令来应用环境变量:"
echo "source ~/.bashrc"
echo ""
echo "然后可以开始编译:"
echo "cd borealis_template"
echo "mkdir -p build_psv && cd build_psv"
echo "cmake .. -DCMAKE_TOOLCHAIN_FILE=\$VITASDK/share/vita.toolchain.cmake -DPLATFORM_PSV=ON -DUSE_GXM=ON"
echo "make -j\$(nproc)"
echo ""
EOF

chmod +x "$PACKAGE_DIR/install.sh"

echo "4. 复制说明文档..."
cp /workspaces/borealis_template/VITA_BUILD_GUIDE.md "$PACKAGE_DIR/"

echo "5. 创建版本信息..."
cat > "$PACKAGE_DIR/VERSION.txt" << EOF
PlayStation Vita 开发包
======================

打包时间: $(date)
VitaSDK 版本: $(cat /usr/local/vitasdk/version.txt 2>/dev/null || echo "未知")
项目版本: Borealis UI Demo
构建平台: $(uname -a)

文件清单:
- vitasdk-complete.tar.gz  VitaSDK 完整工具链
- borealis_template.tar.gz Borealis 演示项目
- install.sh               自动安装脚本
- VITA_BUILD_GUIDE.md      详细编译指南
- VERSION.txt              本文件

使用方法:
1. 运行 ./install.sh
2. 参考 VITA_BUILD_GUIDE.md 进行编译
EOF

echo ""
echo "=== 打包完成! ==="
echo ""
echo "打包位置: $PACKAGE_DIR"
echo "文件列表:"
ls -lah "$PACKAGE_DIR"
echo ""
echo "总大小: $(du -sh $PACKAGE_DIR | cut -f1)"
echo ""
echo "要创建最终压缩包，请运行:"
echo "cd $PACKAGE_DIR && tar -czf vita_dev_complete.tar.gz *"
