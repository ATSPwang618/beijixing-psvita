/*
    组件展示标签页实现文件
    
    这个文件展示了各种UI组件的使用方法，包括：
    - 按钮(Button)
    - 滑条(Slider) 
    - 下拉菜单(Dropdown)
    - 进度显示等
    
    版权所有 2021 natinusala
    使用 Apache 2.0 许可证
*/

#include "tab/components_tab.hpp"

/*
 * ComponentsTab 构造函数
 * 构造函数就像是盖房子的过程，在这里我们：
 * 1. 从XML文件加载界面设计
 * 2. 设置按钮的点击事件
 * 3. 连接滑条和进度显示
 */
ComponentsTab::ComponentsTab()
{
    /*
     * 从XML文件加载界面
     * 就像按照设计图纸来装修房间
     * "xml/tabs/components.xml" 文件描述了这个页面的布局
     */
    this->inflateFromXMLRes("xml/tabs/components.xml");

    /*
     * 注释掉已删除的播放控制按钮引用
     * 这些功能已经转移到其他页面
     */
    // BRLS_REGISTER_CLICK_BY_ID("button_primary", this->onPrimaryButtonClicked);

    /*
     * 注释掉已删除的高亮按钮引用
     */
    // brls::Button* highlightButton = (brls::Button*)this->getView("button_highlight");
    // highlightButton->registerAction(
    //     "Honk", brls::BUTTON_A, [](brls::View* view) { return true; }, false, false, brls::SOUND_HONK);

    /*
     * 注释掉已删除的滑条和进度显示相关代码
     * 音量控制功能已经转移到其他页面
     */
    // progress->setText(std::to_string((int)(slider->getProgress() * 100)));
    // slider->getProgressEvent()->subscribe([this](float progress) {
    //     this->progress->setText(std::to_string((int)(progress * 100)));
    // });

    /*
     * 初始化音乐风格选择器
     * 让用户选择喜欢的音乐类型
     */
    music_genre_selector->init("音乐风格",
                              {"流行", "摇滚", "古典", "民谣", "电子", "爵士", "说唱", "乡村"},
                              0,
                              [](int selected) {},
                              [](int selected) {
                                  auto dialog = new brls::Dialog(fmt::format("选择了音乐风格: {}", selected));
                                  dialog->addButton("确定", []() {});
                                  dialog->open();
                              });

    /*
     * 初始化音乐年代选择器
     * 让用户选择喜欢的音乐年代
     */
    music_era_selector->init("音乐年代",
                            {"2020年代", "2010年代", "2000年代", "90年代", "80年代", "70年代", "经典老歌"},
                            0,
                            [](int selected) {},
                            [](int selected) {
                                auto dialog = new brls::Dialog(fmt::format("选择了音乐年代: {}", selected));
                                dialog->addButton("确定", []() {});
                                dialog->open();
                            });

    /*
     * 初始化音乐情绪选择器
     * 让用户选择想要的音乐氛围
     */
    music_mood_selector->init("音乐情绪",
                             {"快乐", "放松", "激动", "浪漫", "忧伤", "专注", "怀旧", "励志"},
                             0,
                             [](int selected) {},
                             [](int selected) {
                                 auto dialog = new brls::Dialog(fmt::format("选择了音乐情绪: {}", selected));
                                 dialog->addButton("确定", []() {});
                                 dialog->open();
                             });
}

// 全局变量：记录当前选中的选项索引
int selected = 0;

/*
 * 主按钮点击事件处理函数
 * 当用户点击主按钮时，这个函数会被调用
 * 它会创建并显示一个下拉菜单
 */
bool ComponentsTab::onPrimaryButtonClicked(brls::View* view)
{
    /*
     * 下面这段被注释的代码展示了另一种创建新页面的方法
     * 创建一个带框架的宝可梦视图页面
     */
    //    brls::AppletFrame* frame = new brls::AppletFrame(PokemonView::create());
    //    frame->setFooterVisibility(brls::Visibility::GONE);  // 隐藏底部栏
    //    brls::Application::pushActivity(new brls::Activity(frame));

    /*
     * 创建下拉菜单
     * 下拉菜单就像手机设置里的选择列表
     */
    brls::Dropdown* dropdown = new brls::Dropdown(
        "Test",  // 下拉菜单的标题
        // 选项列表：用户可以从这些选项中选择一个
        std::vector<std::string> { 
            "Test 1", "Test 2", "Test 3", "Test 4", "Test 5", "Test 6", 
            "Test 7", "Test 8", "Test 9", "Test 10", "Test 11", "Test 12", "Test 13" 
        }, 
        // 选择回调函数：当用户选择某个选项时执行
        [](int _selected) {
            selected = _selected;  // 记住用户选择了第几个选项
        },
        selected  // 当前选中的选项索引
    );
    
    /*
     * 这里有一段被注释的简化版本，展示了更少选项的下拉菜单
     */
    //    brls::Dropdown* dropdown = new brls::Dropdown(
    //        "Test", std::vector<std::string> { "Test 1", "Test 2", "Test 3" }, [](int _selected) {
    //            selected = _selected;
    //        },
    //        selected);
    
    // 将下拉菜单作为新的活动推入栈中，显示给用户
    brls::Application::pushActivity(new brls::Activity(dropdown));
    
    // 在日志中记录点击事件，方便调试
    brls::Logger::info("主按钮被点击了");
    
    return true;  // 返回true表示事件处理成功
}

/*
 * 静态创建函数
 * 这个函数被XML解析器调用，用来创建ComponentsTab的新实例
 * 就像工厂生产产品一样，每次调用都会创建一个新的ComponentsTab
 */
brls::View* ComponentsTab::create()
{
    // XML引擎调用这个函数来创建新的ComponentsTab
    return new ComponentsTab();
}
