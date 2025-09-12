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
cd beijixing-psvita

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

## Windows 64位应用构建指南

### 环境要求

- Ubuntu 20.04 LTS 或更高版本 (推荐使用WSL2或Linux虚拟机)
- MinGW-w64 交叉编译工具链
- CMake 3.16 或更高版本
- 至少 1GB 可用磁盘空间

### 1. 安装MinGW-w64工具链（重要：需要POSIX线程支持）

```bash
# 更新包列表
sudo apt-get update

# 安装支持POSIX线程的MinGW-w64工具链
sudo apt-get install -y gcc-mingw-w64-x86-64-posix g++-mingw-w64-x86-64-posix

# 设置使用POSIX版本的编译器（重要步骤！）
sudo update-alternatives --set x86_64-w64-mingw32-gcc /usr/bin/x86_64-w64-mingw32-gcc-posix
sudo update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

# 验证安装（应该显示 "10-posix" 版本）
x86_64-w64-mingw32-gcc --version
```


### 2. 构建步骤

```bash
# 创建构建目录
mkdir -p build_windows && cd build_windows

# 配置CMake (使用MinGW工具链)
cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=../library/borealis/library/lib/extern/SDL/build-scripts/cmake-toolchain-mingw64-x86_64.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DPLATFORM_DESKTOP=ON

# 编译项目
make -j$(nproc)

# 复制资源文件
cp -r ../resources .
```

### 3. 生成的文件

编译成功后，你会在 `build_windows/` 目录下找到：

- `borealis_demo.exe` - Windows 64位可执行文件 (约8.6MB)
- `resources/` - 资源文件目录


最终分发包包含：
- `borealis_demo.exe` - 主程序
- `resources/` - 资源文件

### Windows构建故障排除

#### 1. std::mutex 编译错误（常见问题）
**错误现象**：出现 `'mutex' in namespace 'std' does not name a type` 等错误

**解决方案**：
```bash
# 问题原因：MinGW默认使用win32线程模型，不支持C++11标准线程库
# 解决：安装并切换到POSIX线程版本

sudo apt-get install -y gcc-mingw-w64-x86-64-posix g++-mingw-w64-x86-64-posix
sudo update-alternatives --set x86_64-w64-mingw32-gcc /usr/bin/x86_64-w64-mingw32-gcc-posix
sudo update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

# 验证切换成功（应该显示"10-posix"而不是"10-win32"）
x86_64-w64-mingw32-gcc --version

# 清理之前的构建缓存
rm -rf build_windows
mkdir build_windows && cd build_windows
```

#### 2. MinGW工具链问题
```bash
# 如果编译器不存在
sudo apt-get install gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64

# 如果出现链接错误，可以尝试静态链接
cmake .. -DCMAKE_TOOLCHAIN_FILE=... -DCMAKE_EXE_LINKER_FLAGS="-static"
```

#### 3. 构建注意事项
- ✅ **必须使用POSIX线程版本的MinGW**：win32版本不支持C++11线程
- ✅ **CMake会自动检测pthread支持**：配置成功会显示"Found Threads: TRUE"
- ✅ **项目使用静态链接**：生成的exe不需要额外DLL文件
- ✅ **支持多核编译**：使用 `make -j$(nproc)` 加速编译

## 项目结构

- `demo/` - 演示应用源代码
- `library/borealis/` - Borealis UI 框架
- `resources/` - 资源文件（字体、图片等）
- `build_psv/` - PSV 构建输出目录
- `Windows/` - Windows构建相关文件
  - `borealis_demo.exe` - Windows 64位可执行文件 (8.6MB)
  - `borealis-demo-windows.zip` - 完整分发包 (5.3MB)
  - `build_windows.sh` - Windows自动化构建脚本
  - `start.bat` - Windows启动脚本
  - `resources/` - Windows版本资源文件

## 构建成功验证

### PSV 版本验证
```bash
cd build_psv
ls -la *.v*  # 应该看到 .velf, .self, .vpk 文件
```

### Windows 版本验证
```bash
cd build_windows
file borealis_demo.exe  # 应该显示 "PE32+ executable (GUI) x86-64, for MS Windows"
ls -lh borealis_demo.exe  # 应该约8.6MB
```


