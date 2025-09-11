# PlayStation Vita 编译指南

## 环境要求

- Ubuntu 20.04 LTS 或更高版本
- 至少 2GB 可用磁盘空间
- 网络连接（用于下载依赖）

## 快速开始

### 1. 解压并安装 VitaSDK

```bash
# 解压 VitaSDK
sudo tar -xzf vitasdk-complete.tar.gz -C /usr/local/

# 设置环境变量
export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH

# 添加到 ~/.bashrc 以便永久生效
echo 'export VITASDK=/usr/local/vitasdk' >> ~/.bashrc
echo 'export PATH=$VITASDK/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

### 2. 验证安装

```bash
# 检查编译器
arm-vita-eabi-gcc --version

# 检查 vita-makepkg
vita-makepkg --version
```

### 3. 编译项目

```bash
# 进入项目目录
cd borealis_template

# 初始化子模块
git submodule update --init --recursive

# 创建构建目录
mkdir -p build_psv && cd build_psv

# 配置 CMake
cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake \
  -DPLATFORM_PSV=ON \
  -DUSE_GXM=ON

# 编译
make -j$(nproc)
```

### 4. 生成的文件

编译成功后，你会在 `build_psv/` 目录下找到：

- `borealis_demo.velf` - PSV ELF 可执行文件
- `borealis_demo.self` - SELF 格式文件  
- `borealis_demo.vpk` - VPK 安装包（可直接安装到 PSV）

## 故障排除

### fmt 库编译错误

如果遇到 `flockfile`/`funlockfile` 相关错误，检查 `library/borealis/library/lib/extern/fmt/include/fmt/format-inl.h` 文件中是否有以下修复：

```cpp
#ifndef __vita__  // PSV platform doesn't support file locking
template <typename F> auto flockfile(F* f) -> decltype(_lock_file(f)) {
  _lock_file(f);
}
template <typename F> auto funlockfile(F* f) -> decltype(_unlock_file(f)) {
  _unlock_file(f);
}
#endif
```

### 缺少依赖

如果编译时缺少某些库，可以使用 vdpm 安装：

```bash
# 安装常用依赖
vdpm SDL2
vdpm zlib
vdpm libpng
```

## 项目结构

- `demo/` - 演示应用源代码
- `library/borealis/` - Borealis UI 框架
- `resources/` - 资源文件（字体、图片等）
- `build_psv/` - PSV 构建输出目录

## 更多信息

- [VitaSDK 官方文档](https://vitasdk.org/)
- [Borealis UI 框架](https://github.com/natinusala/borealis)
- [PlayStation Vita 开发者社区](https://discord.gg/JXEKeg6)
