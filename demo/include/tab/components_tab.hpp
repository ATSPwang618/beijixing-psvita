/*
    组件展示标签页头文件
    
    这个文件定义了ComponentsTab类，用于展示各种UI组件
    让开发者了解如何使用按钮、滑条、下拉菜单等界面元素
    
    版权所有 2021 natinusala
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * ComponentsTab 类 - 组件展示标签页
 * 
 * 这个类继承自brls::Box，Box就像是一个容器盒子
 * 可以在里面放入各种UI组件，比如按钮、文字、图片等
 */
class ComponentsTab : public brls::Box
{
  public:
    /*
     * 构造函数声明
     * 构造函数在创建对象时自动调用，用来初始化对象
     */
    ComponentsTab();

    /*
     * 静态创建函数
     * static关键字表示这个函数属于类，而不属于具体的对象
     * XML解析器会调用这个函数来创建ComponentsTab的实例
     */
    static brls::View* create();

  private:
    /*
     * BRLS_BIND 宏 - 绑定XML中的组件到C++变量
     * 
     * 这些宏将XML文件中定义的组件绑定到C++代码中的变量
     * 就像给组件起一个C++中的名字，方便我们在代码中操作它们
     * 
     * 格式：BRLS_BIND(组件类型, 变量名, "XML中的ID")
     */
    BRLS_BIND(brls::Label, progress, "progress");   // 绑定进度文字标签
    BRLS_BIND(brls::Slider, slider, "slider");      // 绑定滑条组件
    
    /*
     * 按钮点击事件处理函数声明
     * 当主按钮被点击时，这个函数会被调用
     * 
     * 参数：
     * brls::View* view - 被点击的组件的指针
     * 
     * 返回值：
     * bool - true表示事件处理成功，false表示失败
     */
    bool onPrimaryButtonClicked(brls::View* view);
};
