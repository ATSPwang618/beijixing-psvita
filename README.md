# PlayStation Vita 编译指南

## 项目要求

- Ubuntu 20.04 LTS 或更高版本
- 至少 2GB 可用磁盘空间
- 网络连接（用于下载依赖）
- 本项目包含完整的库链接，不需要再额外进行子模块的下载
- 一次克隆即可使用，方便代码小白直接编辑
- 去除了原版无用的大量垃圾信息，去除了子模块的链接，全部整合进本仓库

  ps：
  
  吐槽一下，原版各种嵌套，生怕小白看懂了一样，我实在是受不了，直接整合全部模块
  
  后续开发大家可以只用这个仓库进行开发，不需要下载额外的内容

## 快速开始

本项目使用vitasdk：

来自123云盘VIP会员的分享：vitasdk-complete.tar.gz

链   接：https://www.123865.com/s/eAc0jv-gP9AA?pwd=YlTe

提取码：YlTe

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
cd beijixin-psvita

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


