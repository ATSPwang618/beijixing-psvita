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
     * 绑定按钮点击事件 - 方法1：使用宏
     * BRLS_REGISTER_CLICK_BY_ID 是一个便捷的宏
     * 它的作用是："当ID为button_primary的按钮被点击时，调用onPrimaryButtonClicked方法"
     * 
     * 参数说明：
     * "button_primary" - 按钮的ID，就像人的身份证号一样用来识别
     * this->onPrimaryButtonClicked - 点击时要执行的函数
     */
    BRLS_REGISTER_CLICK_BY_ID("button_primary", this->onPrimaryButtonClicked);

    /*
     * 绑定按钮点击事件 - 方法2：直接获取按钮对象
     * 这种方法更灵活，可以设置更多参数
     */
    // 根据ID获取高亮按钮的引用，就像通过门牌号找到房子
    brls::Button* highlightButton = (brls::Button*)this->getView("button_highlight");
    
    // 为按钮注册一个动作，参数说明：
    // "Honk" - 动作的名称(随便起的名字)
    // brls::BUTTON_A - 触发条件：按A键  
    // [](brls::View* view) { return true; } - 点击时执行的代码(这里只是返回true)
    // false - 是否重复触发
    // false - 是否需要按住
    // brls::SOUND_HONK - 播放的音效：喇叭声
    highlightButton->registerAction(
        "Honk", brls::BUTTON_A, [](brls::View* view) { return true; }, false, false, brls::SOUND_HONK);

    /*
     * 连接滑条和进度文字显示
     * 当用户拖动滑条时，数字会实时更新
     */
    // 设置进度文字的初始值：滑条当前进度×100，转换为百分比
    progress->setText(std::to_string((int)(slider->getProgress() * 100)));
    
    // 监听滑条进度变化事件
    // 每当滑条被拖动时，这个函数就会被调用
    slider->getProgressEvent()->subscribe([this](float progress) {
        // 更新进度文字显示：进度值×100，显示为百分比
        this->progress->setText(std::to_string((int)(progress * 100)));
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
