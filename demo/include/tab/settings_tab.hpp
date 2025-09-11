/*
    设置标签页头文件 (SettingsTab)
    
    这个文件定义了一个完整的设置页面，就像手机里的"设置"应用一样
    包含了各种设置选项：开关、输入框、滑条、通知等
    
    这个页面展示了如何制作用户设置界面，包括：
    - 单选按钮：从多个选项中选择一个（就像选择喜欢的颜色）
    - 开关按钮：打开或关闭某个功能（就像电灯开关）
    - 选择器：从下拉列表中选择（就像选择生日日期）
    - 输入框：让用户输入文字或数字（就像填写姓名）
    - 滑条：通过拖动来调整数值（就像调节音量）
    - 通知：向用户显示消息（就像收到短信提醒）
    
    版权所有 2021 natinusala
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含，确保每个头文件只被读取一次

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * SettingsTab 类 - 设置标签页
 * 
 * 这个类继承自 brls::Box（盒子容器）
 * Box是一个基础容器，可以在里面放置各种UI组件
 * 就像是一个大盒子，里面可以装很多小玩具（各种设置选项）
 */
class SettingsTab : public brls::Box
{
  public:  // public表示外部代码可以访问这些内容
    /*
     * 构造函数声明
     * 构造函数负责初始化设置页面的所有组件和它们的行为
     */
    SettingsTab();

    /*
     * BRLS_BIND 宏 - 组件绑定魔法！
     * 
     * 这些宏将XML文件中定义的设置组件绑定到C++代码中的变量
     * 每一行都像是给一个设置项贴上名字标签，方便在代码中操作
     * 
     * 格式：BRLS_BIND(组件类型, 变量名, "XML中的ID")
     */
    
    /*
     * 单选按钮组件 (RadioCell)
     * 用于从多个选项中选择一个，就像考试时的单选题
     * 例如：选择主题颜色、选择语言等
     */
    BRLS_BIND(brls::RadioCell, radio, "radio");
    
    /*
     * 布尔开关组件 (BooleanCell) 
     * 用于打开或关闭某个功能，就像房间里的电灯开关
     */
    BRLS_BIND(brls::BooleanCell, boolean, "boolean");      // 通用开关
    BRLS_BIND(brls::BooleanCell, debug, "debug");          // 调试模式开关
    BRLS_BIND(brls::BooleanCell, bottomBar, "bottomBar");  // 底部栏显示开关
    BRLS_BIND(brls::BooleanCell, alwaysOnTop, "alwaysOnTop"); // 窗口置顶开关
    BRLS_BIND(brls::BooleanCell, fps, "fps");              // 帧率显示开关
    
    /*
     * 选择器组件 (SelectorCell)
     * 提供下拉列表供用户选择，就像选择生日时的年月日选择器
     */
    BRLS_BIND(brls::SelectorCell, selector, "selector");           // 通用选择器
    BRLS_BIND(brls::SelectorCell, swapInterval, "swapInterval");   // 屏幕刷新间隔选择器
    
    /*
     * 输入框组件 (InputCell)
     * 让用户输入文字信息，就像填写表格时的姓名栏
     */
    BRLS_BIND(brls::InputCell, input, "input");
    
    /*
     * 数字输入框组件 (InputNumericCell) 
     * 专门用于输入数字，就像设置闹钟时间
     */
    BRLS_BIND(brls::InputNumericCell, inputNumeric, "inputNumeric");
    
    /*
     * 详细信息显示组件 (DetailCell)
     * 用于显示只读信息，就像查看手机的序列号
     */
    BRLS_BIND(brls::DetailCell, ipAddress, "ipAddress");   // IP地址显示
    BRLS_BIND(brls::DetailCell, dnsServer, "dnsServer");   // DNS服务器显示
    BRLS_BIND(brls::DetailCell, notify, "notify");         // 通知按钮
    
    /*
     * 滑条组件 (SliderCell)
     * 通过拖动来调整数值，就像调节音量大小的滑条
     */
    BRLS_BIND(brls::SliderCell, slider, "slider");

    /*
     * 静态创建函数
     * XML解析器调用这个函数来创建SettingsTab的新实例
     */
    static brls::View* create();
};
