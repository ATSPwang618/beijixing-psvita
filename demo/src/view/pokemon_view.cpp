/*
    宝可梦视图组件实现文件
    
    这个文件展示了如何创建一个自定义的视图组件
    用来显示宝可梦的详细信息，包括图片、名称、描述等
    
    版权所有 2021 XITRIX
    使用 Apache 2.0 许可证
*/

#include "view/pokemon_view.hpp"

#include <borealis/core/i18n.hpp>  // 国际化支持

using namespace brls::literals;  // 使用Borealis的字面量，支持 "_i18n" 语法

/*
 * 关闭视图的辅助函数
 * 这个函数可以被其他地方调用来关闭宝可梦视图
 */
bool dismissView(brls::View* view, PokemonView* pock)
{
    return true;  // 返回true表示成功处理
}

/*
 * PokemonView 构造函数
 * 创建宝可梦视图时会调用这个函数来初始化界面
 * 
 * 参数：
 * Pokemon pokemon - 要显示的宝可梦数据
 */
PokemonView::PokemonView(Pokemon pokemon)
    : pokemon(pokemon)  // 保存传入的宝可梦数据
{
    /*
     * 从XML文件加载视图布局
     * 就像按照设计图纸来装修房间
     */
    this->inflateFromXMLRes("xml/views/pokemon.xml");

    /*
     * 定义关闭动作的Lambda函数
     * Lambda函数就像是一个小的匿名函数，可以直接在这里定义
     * [this] 表示捕获当前对象的指针
     */
    auto dismissAction = [this](View* view) {
        this->dismiss();  // 关闭当前视图
        return true;      // 返回true表示处理成功
    };

    /*
     * 创建关闭提示标签
     * 显示按键提示，告诉用户如何关闭这个页面
     */
    brls::Label* label = new brls::Label();
    // 设置标签文字：显示RB按键图标 + "关闭"文字（俄语）
    label->setText(brls::Hint::getKeyIcon(brls::ControllerButton::BUTTON_RB) + " Закрыть");
    label->setFontSize(24);           // 设置字体大小为24像素
    label->setMargins(0, 12, 0, 12);  // 设置边距：上下12像素，左右0像素

    /*
     * 创建容器盒子来放置标签
     * Box就像是一个容器，可以装其他UI组件
     */
    brls::Box* holder = new brls::Box();
    holder->addView(label);                                                    // 将标签添加到容器中
    holder->setFocusable(true);                                               // 设置容器可以获得焦点
    holder->addGestureRecognizer(new brls::TapGestureRecognizer(holder));     // 添加触摸手势识别

    // 注册点击事件：当用户点击时执行关闭动作
    holder->registerClickAction(dismissAction);
    // 注册按键事件：当用户按RB键时执行关闭动作
    holder->registerAction("Close", brls::ControllerButton::BUTTON_RB, dismissAction, true);
    // 为整个视图也注册RB键关闭事件
    registerAction("Close", brls::ControllerButton::BUTTON_RB, dismissAction, true);

    /*
     * 设置AppletFrame（应用框架）的属性
     * AppletFrame是顶部的标题栏区域
     */
    getAppletFrameItem()->title = pokemon.name;  // 设置标题为宝可梦的名字
    // 设置标题栏图标：从资源文件加载宝可梦图片
    getAppletFrameItem()->setIconFromRes("img/pokemon/" + pokemon.id + ".png");
    
    /*
     * 下面这行被注释了，如果启用的话会在标题栏显示提示视图
     */
//    getAppletFrameItem()->hintView = holder;

    /*
     * 设置主要的宝可梦图片
     * image 是通过BRLS_BIND绑定的图片组件
     */
    image->setImageFromRes("img/pokemon/" + pokemon.id + ".png");

    /*
     * 设置宝可梦的描述文字
     * description 是通过BRLS_BIND绑定的文字标签组件
     */
    description->setText("这是一只名叫 " + pokemon.name + " 的宝可梦\n收集所有宝可梦来成为萨满王!");

    /*
     * 为关闭按钮注册点击事件
     * 通过ID "close_button" 找到按钮，然后设置点击行为
     */
    this->getView("close_button")->registerAction(
        "hints/ok"_i18n,           // 动作名称（从翻译文件获取）
        brls::BUTTON_A,            // 触发按键：A键
        [this](brls::View* view) { // 点击时执行的代码
            this->dismiss();       // 关闭当前视图
            return true;           // 返回true表示处理成功
        },
        false,                     // 不重复触发
        false,                     // 不需要按住
        brls::SOUND_BACK          // 播放返回音效
    );
}

/*
 * 静态创建函数
 * XML解析器调用这个函数来创建PokemonView的新实例
 * 
 * 注意：这个版本使用默认构造函数，实际项目中可能需要传入宝可梦数据
 */
brls::View* PokemonView::create()
{
    // XML引擎调用这个函数来创建新的PokemonView
    // 这里使用默认构造函数，实际使用时可能需要修改
    return new PokemonView();
}
