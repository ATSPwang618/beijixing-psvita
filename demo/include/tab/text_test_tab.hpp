/*
    文本测试标签页头文件 (TextTestTab)
    
    这个文件定义了一个用来测试文字显示效果的实验页面
    就像是一个文字魔法实验室，可以调整文字的各种属性
    
    通过这个页面，小朋友可以学习：
    - 文字是如何在屏幕上显示的
    - 不同的对齐方式有什么效果（居左、居中、居右）
    - 单行和多行文字的区别
    - 如何调整文字容器的大小
    
    这就像是在玩文字排版游戏，通过调整各种设置来看文字的变化
    
    版权所有 2024 xfangfang
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * TextTestTab 类 - 文本测试标签页
 * 
 * 这个类继承自 brls::Box（盒子容器）
 * 它包含了各种控制组件，让用户可以实时调整文字的显示效果
 * 就像是一个文字排版工作台，有各种工具来调整文字的外观
 */
class TextTestTab : public brls::Box
{
  public:
    /*
     * 构造函数
     * 初始化文本测试页面，设置所有控制组件的行为和初始值
     */
    TextTestTab();

    /*
     * 静态创建函数
     * XML解析器调用这个函数来创建TextTestTab的实例
     */
    static brls::View* create();

  private:
    /*
     * BRLS_BIND 宏 - 组件绑定
     * 将XML中定义的UI组件绑定到C++变量，方便在代码中操作
     */
    
    /*
     * 尺寸控制滑条
     * 让用户可以调整文字容器的大小，看看文字如何适应不同的空间
     */
    BRLS_BIND(brls::SliderCell, width, "width");    // 宽度滑条（让文字容器变宽或变窄）
    BRLS_BIND(brls::SliderCell, height, "height");  // 高度滑条（让文字容器变高或变矮）
    
    /*
     * 文字显示模式开关
     * 控制文字是显示在一行还是可以换行显示
     */
    BRLS_BIND(brls::BooleanCell, singleLine, "singleLine");  // 单行模式开关（true=单行，false=多行）
    
    /*
     * 文字对齐方式选择器
     * 让用户选择文字在容器中的对齐方式
     */
    BRLS_BIND(brls::SelectorCell, horizontal, "horizontal");  // 水平对齐选择器（左对齐、居中、右对齐等）
    BRLS_BIND(brls::SelectorCell, vertical, "vertical");      // 垂直对齐选择器（顶部对齐、居中、底部对齐等）
    
    /*
     * 文字标签组件
     * 这是实际显示文字的组件，所有的设置都会应用到这个标签上
     */
    BRLS_BIND(brls::Label, label, "label");  // 文字标签（展示各种文字效果的舞台）
};
