/*
    版权声明 (Copyright 2020-2021 natinusala, Copyright 2019 p-sam)
    这是一个使用 Apache 2.0 许可证的开源项目
    
    这个文件是 PSVita 演示程序的主入口点
    - 展示了如何使用 Borealis UI 框架
    - 包含了各种UI组件的示例
    - 适合初学者学习 PSVita 应用开发
*/

// 如果是安卓或苹果平台，需要包含SDL的主函数支持
#if defined(ANDROID) || defined(IOS)
#include <SDL2/SDL_main.h>
#endif

// 引入必要的头文件
#include <borealis.hpp>     // Borealis UI框架 - 这是制作漂亮界面的工具包
#include <cstdlib>          // C标准库 - 包含基本功能
#include <string>           // 字符串处理

// 引入我们自己写的界面组件
#include "view/captioned_image.hpp"     // 带标题的图片组件
#include "view/pokemon_view.hpp"        // 宝可梦展示组件
#include "tab/components_tab.hpp"       // 组件展示标签页
#include "tab/transform_tab.hpp"        // 变换效果标签页
#include "tab/recycling_list_tab.hpp"   // 循环列表标签页
#include "tab/settings_tab.hpp"         // 设置标签页
#include "tab/text_test_tab.hpp"        // 文本测试标签页
#include "activity/main_activity.hpp"   // 主界面活动

// PSVita平台专用设置
#if defined(__PSV__) && defined(BOREALIS_USE_OPENGL)
// 设置PSVita的内存堆大小为2MB，这是OpenGL正常工作所需要的
extern "C" unsigned int sceLibcHeapSize = 2 * 1024 * 1024;
#endif

// 使用Borealis的国际化功能，让我们可以支持多种语言
using namespace brls::literals; // 这样我们就可以使用 "_i18n" 来翻译文字

// 程序的主函数 - 这里是程序开始运行的地方
int main(int argc, char* argv[])
{
    /*
     * 解析命令行参数 - 这些是启动程序时可以给的选项
     * 就像在电脑上运行程序时可以加 -h 显示帮助一样
     */
    
    // 推荐在真正的应用中使用INFO级别的日志
    for (int i = 1; i < argc; i++) {  // 遍历所有命令行参数
        if (std::strcmp(argv[i], "-d") == 0) { 
            // 如果用户输入了 -d 参数，就开启调试模式
            // 调试模式会显示更多详细信息，帮助我们找bug
            brls::Logger::setLogLevel(brls::LogLevel::LOG_DEBUG);
        } else if (std::strcmp(argv[i], "-o") == 0) {
            // 如果用户输入了 -o 参数，就把日志保存到文件
            const char* path = (i + 1 < argc) ? argv[++i] : "borealis.log";
            brls::Logger::setLogOutput(std::fopen(path, "w+"));
        } else if (std::strcmp(argv[i], "-v") == 0) {
            // 如果用户输入了 -v 参数，就开启调试视图
            // 这会在屏幕上显示一些开发者才需要的信息
            brls::Application::enableDebuggingView(true);
        }
    }

    // 根据平台设置日志输出路径
    brls::Logger::setLogLevel(brls::LogLevel::LOG_DEBUG);
    
#ifdef _WIN32
    // Windows平台：输出到exe所在目录
    brls::Logger::setLogOutput(std::fopen("borealis_debug.log", "w+"));
#elif defined(__psp2__)
    // PSVita平台：输出到指定路径
    brls::Logger::setLogOutput(std::fopen("ux0:data/borealis_debug.log", "w+"));
#else
    // 其他平台：输出到当前目录
    brls::Logger::setLogOutput(std::fopen("borealis_debug.log", "w+"));
#endif
    
    brls::Application::enableDebuggingView(true);
    
    // 添加启动日志
    brls::Logger::info("=== Beijixing PSVita Demo 启动 ===");
#ifdef _WIN32
    brls::Logger::info("平台: Windows");
#elif defined(__psp2__)
    brls::Logger::info("平台: PlayStation Vita");
#else
    brls::Logger::info("平台: 其他");
#endif
    brls::Logger::info("日志级别: DEBUG");

    /*
     * 初始化应用程序和国际化系统
     * 这就像开机启动各种系统一样重要
     */
    brls::Logger::info("开始初始化 Borealis 应用程序...");
    if (!brls::Application::init())  // 尝试初始化Borealis框架
    {
        // 如果初始化失败，就打印错误信息并退出程序
        brls::Logger::error("无法初始化 Borealis 应用程序");
        return EXIT_FAILURE;  // 告诉系统程序运行失败了
    }
    brls::Logger::info("Borealis 应用程序初始化成功");

    // 创建程序窗口，标题从翻译文件中获取
    brls::Logger::info("创建程序窗口...");
    try {
        brls::Application::createWindow("demo/title"_i18n);
        brls::Logger::info("程序窗口创建成功");
    } catch (const std::exception& e) {
        brls::Logger::error("创建窗口失败: {}", e.what());
        return EXIT_FAILURE;
    }

    // 设置界面主题为深色模式（就像手机的夜间模式）
    brls::Logger::info("设置界面主题为深色模式...");
    brls::Application::getPlatform()->setThemeVariant(brls::ThemeVariant::DARK);

    // 设置全局退出功能
    // 如果设为true，按START键就会退出程序
    brls::Application::setGlobalQuit(false);

    /*
     * 注册自定义的界面组件
     * 这就像告诉系统："我创造了新的UI组件，你要认识它们"
     * XML文件中就可以使用这些组件名字来创建界面
     */
    brls::Logger::info("注册自定义界面组件...");
    try {
        brls::Application::registerXMLView("CaptionedImage", CaptionedImage::create);      // 带标题的图片
        brls::Application::registerXMLView("RecyclingListTab", RecyclingListTab::create);  // 可回收的列表页面
        brls::Application::registerXMLView("ComponentsTab", ComponentsTab::create);        // 组件展示页面  
        brls::Application::registerXMLView("TransformTab", TransformTab::create);          // 变换效果页面
        brls::Application::registerXMLView("TransformBox", TransformBox::create);          // 变换盒子组件
        brls::Application::registerXMLView("PokemonView", PokemonView::create);            // 宝可梦展示组件
        brls::Application::registerXMLView("SettingsTab", SettingsTab::create);            // 设置页面
        brls::Application::registerXMLView("TextTestTab", TextTestTab::create);            // 文字测试页面
        brls::Logger::info("界面组件注册成功");
    } catch (const std::exception& e) {
        brls::Logger::error("注册界面组件失败: {}", e.what());
        return EXIT_FAILURE;
    }

    /*
     * 自定义主题颜色
     * 就像给房间刷不同颜色的墙一样，让界面更漂亮
     */
    brls::Logger::info("设置自定义主题颜色...");
    // 为带标题图片设置专用颜色 - 浅色主题用青色
    brls::Theme::getLightTheme().addColor("captioned_image/caption", nvgRGB(2, 176, 183));
    // 深色主题用蓝色
    brls::Theme::getDarkTheme().addColor("captioned_image/caption", nvgRGB(51, 186, 227));

    /*
     * 自定义样式参数
     * 这些数字控制界面元素的大小和间距，就像调整家具摆放一样
     */
    brls::Logger::info("设置自定义样式参数...");
    brls::getStyle().addMetric("about/padding_top_bottom", 50);  // 关于页面上下内边距：50像素
    brls::getStyle().addMetric("about/padding_sides", 75);       // 关于页面左右内边距：75像素  
    brls::getStyle().addMetric("about/description_margin", 50);  // 描述文字的外边距：50像素

    /*
     * 创建并启动主界面
     * 这就像打开程序的第一个窗口
     */
    brls::Logger::info("创建并启动主界面...");
    try {
        brls::Application::pushActivity(new MainActivity());
        brls::Logger::info("主界面创建成功");
    } catch (const std::exception& e) {
        brls::Logger::error("创建主界面失败: {}", e.what());
        return EXIT_FAILURE;
    }

    /*
     * 运行程序的主循环
     * 这个循环会一直运行，处理用户的操作（按键、触摸等）
     * 就像人的心跳一样，一直在工作直到程序结束
     */
    brls::Logger::info("启动主循环...");
    try {
        while (brls::Application::mainLoop())
            ;  // 空循环体，所有工作都在mainLoop()函数里完成
        brls::Logger::info("主循环正常结束");
    } catch (const std::exception& e) {
        brls::Logger::error("主循环异常: {}", e.what());
        return EXIT_FAILURE;
    }

    // 程序正常结束，返回成功状态
    brls::Logger::info("=== Beijixing PSVita Demo 正常结束 ===");
    
    // 添加快速退出机制，避免析构时卡住
#ifdef _WIN32
    // Windows平台使用快速退出，避免UI框架析构时的死锁问题
    std::exit(EXIT_SUCCESS);
#else
    return EXIT_SUCCESS;
#endif
}

#ifdef __WINRT__
#include <borealis/core/main.hpp>
#endif
