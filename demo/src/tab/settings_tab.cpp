/*
    设置标签页实现文件
    
    这个文件展示了各种设置组件的使用，包括：
    - 单选按钮 (Radio button)
    - 开关按钮 (Switch)  
    - 选择器 (Selector)
    - 输入框 (Input)
    - 滑条 (Slider)
    - 通知 (Notification)
    等等
    
    版权所有 2021 natinusala
    使用 Apache 2.0 许可证
*/

#include "tab/settings_tab.hpp"

using namespace brls::literals;  // 使用Borealis字面量，支持 "_i18n" 语法

// 全局变量：记录单选按钮的状态
bool radioSelected = false;

/*
 * 通知消息数组
 * 这些是点击通知按钮时会随机显示的消息
 */
static std::vector<std::string> NOTIFICATIONS = {
    "你的头发很酷",
    "我喜欢你的鞋子", 
    "borealis是由nanovg驱动的",
    "三角力量是内部工作",
    "Pozznx将在一天十二小时后触发",
    "极光？在这个时候，在这个年份，在游戏市场的这一部分，完全位于你的Switch内？！",
    "我可以看看吗？",
    "嗯，蒸汉堡！",
    "你好\n世界！"
};

/*
 * SettingsTab 构造函数
 * 初始化所有设置项和它们的行为
 */
SettingsTab::SettingsTab()
{
    // 从XML文件加载设置页面布局
    this->inflateFromXMLRes("xml/tabs/settings.xml");

    /*
     * 配置单选按钮组件
     * 单选按钮可以在选中/未选中之间切换
     */
    radio->title->setText("单选按钮");        // 设置标题
    radio->setSelected(radioSelected);        // 设置初始状态
    radio->registerClickAction([this](brls::View* view) {  // 注册点击事件
        radioSelected = !radioSelected;      // 切换状态
        this->radio->setSelected(radioSelected);  // 更新显示
        return true;
    });

    /*
     * 配置布尔开关组件
     * 这是一个简单的开关，可以打开或关闭某个功能
     */
    boolean->title->setText("开关按钮");

    /*
     * 配置调试层开关
     * 这个开关可以开启/关闭调试信息显示
     */
    debug->init("调试层",                                    // 开关标题
                brls::Application::isDebuggingViewEnabled(), // 当前状态
                [](bool value){                              // 状态改变时的回调函数
        brls::Application::enableDebuggingView(value);      // 启用/禁用调试视图
        brls::sync([value](){                               // 异步执行日志记录
            brls::Logger::info("{} 调试层", value ? "打开" : "关闭");
        });
    });

    /*
     * 配置底部栏显示开关
     * 控制是否显示应用底部的导航栏
     */
    bottomBar->init("底部栏", 
                    !brls::AppletFrame::HIDE_BOTTOM_BAR,    // 当前状态（取反因为变量含义相反）
                    [](bool value){                         // 状态改变回调
        brls::AppletFrame::HIDE_BOTTOM_BAR = !value;       // 设置隐藏状态
        // 获取所有活动页面并更新底部栏显示状态
        auto stack = brls::Application::getActivitiesStack();
        for (auto& activity : stack) {
            auto* frame = dynamic_cast<brls::AppletFrame*>(
                activity->getContentView());
            if (!frame) continue;
            // 根据设置显示或隐藏底部栏
            frame->setFooterVisibility(!value ? brls::Visibility::GONE
                                             : brls::Visibility::VISIBLE);
        }
    });

    /*
     * 配置FPS显示开关
     * 控制是否在屏幕上显示帧率信息
     */
    fps->init("帧率显示", 
              brls::Application::getFPSStatus(),           // 获取当前FPS显示状态
              [](bool value){                              // 状态改变回调
        brls::Application::setFPSStatus(value);           // 设置FPS显示状态
    });

    /*
     * 配置垂直同步间隔选择器
     * 这个设置影响画面刷新的同步方式，数值越高帧率越低但越稳定
     */
    swapInterval->init("垂直同步间隔",                      // 标题
                       {"0", "1", "2", "3", "4"},           // 可选值列表
                       1,                                   // 默认选中第1项（索引从0开始）
                       [](int selected) {},                 // 选择时的即时回调（这里为空）
                       [](int selected) {                   // 选择确认后的回调
        brls::Application::setSwapInterval(selected);      // 设置垂直同步间隔
    });

    /*
     * 配置窗口置顶开关
     * 控制程序窗口是否始终显示在其他窗口之上
     */
    alwaysOnTop->init("窗口置顶", 
                      false,                                // 默认关闭
                      [](bool value){                       // 状态改变回调
        brls::Application::getPlatform()->setWindowAlwaysOnTop(value);  // 设置窗口置顶
    });

    /*
     * 配置选择器组件
     * 选择器可以从多个选项中选择一个，类似于下拉菜单
     */
    selector->init("选择器",                                // 标题
                   { "测试 1", "测试 2", "测试 3", "测试 4", "测试 5", 
                     "测试 6", "测试 7", "测试 8", "测试 9", "测试 10", 
                     "测试 11", "测试 12", "测试 13" },        // 选项列表
                   0,                                       // 默认选中第0项
                   [](int selected) {                       // 选择时的即时回调（这里为空）
    }, 
    [](int selected) {                                      // 选择确认后的回调
        // 显示一个对话框，告诉用户选择了哪个选项
        auto dialog = new brls::Dialog(fmt::format("选择了 {}", selected));
        dialog->addButton("hints/ok"_i18n, []() {});       // 添加确定按钮
        dialog->open();                                     // 显示对话框
    });

    /*
     * 配置文本输入框
     * 用户可以输入自定义的文本内容
     */
    input->init(
        "输入文本",                                         // 标题
        "https://github.com",                              // 默认值
        [](std::string text) {                             // 输入完成后的回调函数
            // 这里可以处理用户输入的文本，目前为空
        },
        "占位符文本",                                       // 占位符（输入框为空时显示的提示文字）
        "提示信息"                                          // 提示信息
    );

    /*
     * 配置数字输入框
     * 专门用于输入数字的输入框
     */
    inputNumeric->init(
        "输入数字",                                         // 标题
        2448,                                              // 默认数值
        [](int number) {                                   // 输入完成后的回调函数
            // 这里可以处理用户输入的数字，目前为空
        },
        "数字提示"                                          // 提示信息
    );

    /*
     * 显示网络信息
     * 这些是只读的信息显示，展示当前设备的网络配置
     */
    ipAddress->setDetailText(brls::Application::getPlatform()->getIpAddress());  // 显示IP地址
    dnsServer->setDetailText(brls::Application::getPlatform()->getDnsServer());  // 显示DNS服务器

    /*
     * 为输入框注册X键动作
     * 按X键可以在浏览器中打开输入框中的链接
     */
    input->registerAction("hints/open"_i18n,               // 动作名称（从翻译文件获取）
                          brls::BUTTON_X,                   // 触发按键：X键
                          [](brls::View* view) {            // 按键时执行的代码
        // 将view转换为DetailCell类型，获取其详细文本
        brls::DetailCell *cell = dynamic_cast<brls::DetailCell *>(view);
        // 在浏览器中打开该链接
        brls::Application::getPlatform()->openBrowser(cell->detail->getFullText());
        return true;
    }, false, false, brls::SOUND_CLICK);                   // 播放点击音效

    /*
     * 配置亮度滑条
     * 用户可以通过拖动滑条来调节屏幕亮度
     */
    float brightness = brls::Application::getPlatform()->getBacklightBrightness();  // 获取当前亮度
    slider->init("屏幕亮度",                                // 标题
                 brightness,                               // 当前亮度值
                 [this](float value){                      // 滑条值改变时的回调
        brls::Application::getPlatform()->setBacklightBrightness(value);  // 设置新的亮度值
        slider->setDetailText(fmt::format("{:.2f}", value));              // 更新显示的数值
    });
    slider->setDetailText(fmt::format("{:.2f}", brightness));             // 设置初始显示数值

    /*
     * 配置通知按钮
     * 点击后会随机显示一条通知消息
     */
    notify->registerClickAction([](...){                   // 注册点击事件（使用...表示忽略参数）
        // 从通知数组中随机选择一条消息
        std::string notification = NOTIFICATIONS[std::rand() % NOTIFICATIONS.size()];
        // 显示通知
        brls::Application::notify(notification);
        return true;
    });
}

/*
 * 静态创建函数
 * XML解析器调用这个函数来创建SettingsTab的新实例
 */
brls::View* SettingsTab::create()
{
    return new SettingsTab();
}
