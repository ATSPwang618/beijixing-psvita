/*
    文本测试标签页实现文件 (TextTestTab)
    
    这个文件实现了一个文字效果实验室，让用户可以通过各种控制项
    来实时调整文字的显示效果，学习文字排版的基本概念
    
    主要功能：
    - 调整文字容器的宽度和高度
    - 选择文字的水平和垂直对齐方式
    - 切换单行和多行显示模式
    
    就像是在玩一个文字排版游戏，通过拖动滑条和选择选项
    来看文字在不同设置下的显示效果
    
    版权所有 2024 xfangfang
    使用 Apache 2.0 许可证
*/

#include "tab/text_test_tab.hpp"  // 引入文本测试标签页的头文件

/*
 * 滑条注册辅助函数
 * 这是一个工具函数，用来简化滑条组件的设置过程
 * 就像是一个通用的滑条配置模板
 * 
 * 参数说明：
 * cell - 要配置的滑条组件
 * init - 滑条的初始值（0.0到1.0之间）
 * title - 滑条显示的标题
 * cb - 回调函数，当滑条值改变时会被调用
 */
static void registerSliderCell(brls::SliderCell* cell, float init, const std::string& title, const std::function<int(float)>& cb)
{
    /*
     * 使用初始值调用回调函数，获得初始结果
     * 这样可以确保滑条的显示文字和实际效果是同步的
     */
    int res = cb(init);
    
    /*
     * 设置滑条的详细信息文字
     * 如果结果是0，显示"auto"（自动）；否则显示具体数值
     * fmt::format 是一个格式化字符串的函数，类似printf
     */
    cell->setDetailText(res == 0 ? "auto" : fmt::format("{}", res));
    
    /*
     * 设置滑条指针的大小
     * 指针就是滑条上那个可以拖动的小圆点
     */
    cell->slider->setPointerSize(20);
    
    /*
     * 初始化滑条组件
     * 设置标题、初始值和值改变时的回调函数
     */
    cell->init(title, init, [cb, cell](float value)
        {
            /*
             * 当滑条值改变时执行这个函数
             * [cb, cell] 是捕获列表，表示这个Lambda函数可以使用cb和cell变量
             */
            int res = cb(value);  // 调用回调函数处理新值
            cell->setDetailText(res == 0 ? "auto" : fmt::format("{}", res));  // 更新显示文字
        });
}

/*
 * TextTestTab 构造函数
 * 这是文字实验室的初始化过程，设置所有控制组件的行为
 */
TextTestTab::TextTestTab()
{
    /*
     * 从XML文件加载页面布局
     * 就像按照设计图纸来布置实验室的各种设备
     */
    this->inflateFromXMLRes("xml/tabs/text_test.xml");

    /*
     * 配置宽度滑条
     * 用户拖动这个滑条可以改变文字容器的宽度
     * 就像调整相框的宽度来看照片的显示效果
     */
    registerSliderCell(width, 1.0f, "width", [this](float value)
        {
            /*
             * 将滑条值（0-1）转换为实际像素值（0-400）
             * 0表示自动宽度，其他值表示具体的像素宽度
             */
            value *= 400;
            label->setWidth(value <= 0.0f ? brls::View::AUTO : value);
            return value;
        });

    /*
     * 配置高度滑条
     * 用户拖动这个滑条可以改变文字容器的高度
     * 当高度为自动时，单行模式开关会显示；设置固定高度时会隐藏
     */
    registerSliderCell(height, 0.0f, "height", [this](float value)
        {
            value *= 400;  // 转换为像素值
            
            /*
             * 根据高度设置来控制单行模式开关的显示/隐藏
             * 只有在自动高度时才需要单行模式选项
             */
            singleLine->setVisibility(value <= 0.0f ? brls::Visibility::VISIBLE : brls::Visibility::GONE);
            label->setHeight(value <= 0.0f ? brls::View::AUTO : value);
            return value;
        });

    /*
     * 配置垂直对齐选择器
     * 让用户选择文字在容器中的垂直位置
     * 就像选择文字是贴着天花板、悬在半空还是贴着地板
     */
    vertical->init("verticalAlign", { "baseline", "top", "center", "bottom" }, 2, [this](int value)
        {
            /*
             * 将选择的索引转换为对应的对齐枚举值
             * 0=baseline(基线), 1=top(顶部), 2=center(中心), 3=bottom(底部)
             */
            label->setVerticalAlign((brls::VerticalAlign)value);
            return value;
        });

    /*
     * 配置水平对齐选择器
     * 让用户选择文字在容器中的水平位置
     * 就像选择文字是靠左边、居中还是靠右边
     */
    horizontal->init("horizontalAlign", { "left", "center", "right" }, 0, [this](int value)
        {
            /*
             * 将选择的索引转换为对应的对齐枚举值
             * 0=left(左对齐), 1=center(居中), 2=right(右对齐)
             */
            label->setHorizontalAlign((brls::HorizontalAlign)value);
            return value;
        });

    /*
     * 配置单行模式开关
     * 控制文字是只显示一行还是可以换行显示
     * 就像决定文字是排成一条长龙还是可以换行排列
     */
    singleLine->init("singleLine", false, [this](bool value)
        {
            /*
             * 设置文字标签的单行模式
             * true=单行模式（超出部分会被截断）
             * false=多行模式（自动换行显示）
             */
            label->setSingleLine(value);
            return value;
        });
}

/*
 * 静态创建函数
 * XML解析器调用这个函数来创建TextTestTab的新实例
 * 就像工厂生产线，每次调用都制造一个新的文字实验室
 */
brls::View* TextTestTab::create()
{
    /*
     * 使用new关键字创建新的TextTestTab对象
     * 返回的指针会被UI系统管理
     */
    return new TextTestTab();
}