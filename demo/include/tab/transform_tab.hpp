/*
    变换效果标签页头文件 (TransformTab)
    
    这个文件定义了一个有趣的变换效果演示页面，就像是一个魔法实验室！
    你可以通过各种滑条来改变图片的外观：旋转、缩放、倾斜等
    
    主要包含两个类：
    1. TransformBox - 可以进行各种变换的图片盒子（就像魔法画框）
    2. TransformTab - 整个变换实验页面（就像魔法实验室）
    
    这个页面可以让小朋友：
    - 学习2D图形变换的概念（旋转、缩放、倾斜）
    - 通过交互式滑条实时看到变换效果
    - 了解动画系统是如何工作的
    
    版权所有 2024 xfangfang
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * TransformBox 类 - 可变换的图片盒子
 * 
 * 这个类继承自 brls::Image（图片组件）
 * 它是一个特殊的图片，可以进行各种2D变换操作
 * 就像是一个魔法画框，可以让里面的图片旋转、缩放、倾斜
 */
class TransformBox: public brls::Image {
  public:
    /*
     * 绘制函数 - 负责在屏幕上画出变换后的图片
     * 这个函数会在每一帧被调用，应用所有的变换效果
     * 
     * 参数解释：
     * NVGcontext* vg - 绘图上下文（就像画家的调色板和画笔）
     * x, y - 绘制位置坐标
     * width, height - 绘制尺寸
     * style - 样式信息
     * ctx - 框架上下文
     */
    void draw(NVGcontext* vg, float x, float y, float width, float height, brls::Style style, brls::FrameContext* ctx) override;

    /*
     * 静态创建函数
     * XML解析器调用这个函数来创建TransformBox的实例
     */
    static brls::View* create();

    /*
     * 变换设置函数 - 就像给魔法画框施放不同的魔法咒语
     */
    void setRotate(float deg);     // 设置旋转角度（单位：度）
    void setSkewX(float deg);      // 设置X轴倾斜角度（让图片向左或右倾斜）
    void setSkewY(float deg);      // 设置Y轴倾斜角度（让图片向上或下倾斜）
    void setScaleX(float size);    // 设置X轴缩放比例（让图片变宽或变窄）
    void setScaleY(float size);    // 设置Y轴缩放比例（让图片变高或变矮）
    void setFontScaleX(float size); // 设置字体X轴缩放
    void setFontScaleY(float size); // 设置字体Y轴缩放

  private:
    /*
     * 私有成员变量 - 存储所有变换参数
     * 这些变量记录了当前的变换状态，就像是魔法咒语的配方
     */
    float skew_x{}, skew_y{};           // 倾斜角度（默认为0）
    float rotate{};                     // 旋转角度（默认为0）
    float scale_x{1}, scale_y{1};       // 缩放比例（默认为1，即原始大小）
    float font_scale_x{1}, font_scale_y{1}; // 字体缩放比例
};

/*
 * TransformTab 类 - 变换效果标签页
 * 
 * 这个类继承自 brls::Box（盒子容器）
 * 它包含了TransformBox和各种控制滑条，让用户可以交互式地改变变换效果
 * 就像是一个魔法实验室的控制台，有很多旋钮和按钮
 */
class TransformTab : public brls::Box
{
  public:
    /*
     * 构造函数
     * 初始化整个变换实验页面，设置所有滑条和按钮的行为
     */
    TransformTab();

    /*
     * 静态创建函数
     * XML解析器调用这个函数来创建TransformTab的实例
     */
    static brls::View* create();

  private:
    /*
     * BRLS_BIND 宏 - 组件绑定
     * 将XML中定义的UI组件绑定到C++变量
     */
    BRLS_BIND(TransformBox, box, "box");        // 绑定可变换的图片盒子

    /*
     * 变换控制滑条 - 就像魔法实验室里的各种旋钮
     */
    BRLS_BIND(brls::SliderCell, transX, "transX");   // X轴平移滑条
    BRLS_BIND(brls::SliderCell, transY, "transY");   // Y轴平移滑条
    BRLS_BIND(brls::SliderCell, scaleX, "scaleX");   // X轴缩放滑条
    BRLS_BIND(brls::SliderCell, scaleY, "scaleY");   // Y轴缩放滑条
    BRLS_BIND(brls::SliderCell, skewX, "skewX");     // X轴倾斜滑条
    BRLS_BIND(brls::SliderCell, skewY, "skewY");     // Y轴倾斜滑条
    BRLS_BIND(brls::SliderCell, rotate, "rotate");   // 旋转滑条

    /*
     * 尺寸控制滑条
     */
    BRLS_BIND(brls::SliderCell, boxWidth, "width");   // 宽度滑条
    BRLS_BIND(brls::SliderCell, boxHeight, "height"); // 高度滑条

    /*
     * 字体缩放滑条
     */
    BRLS_BIND(brls::SliderCell, fontScaleX, "fontScaleX"); // 字体X轴缩放滑条
    BRLS_BIND(brls::SliderCell, fontScaleY, "fontScaleY"); // 字体Y轴缩放滑条

    /*
     * 控制按钮
     */
    BRLS_BIND(brls::Button, reset, "reset");  // 重置按钮（恢复所有设置到初始状态）
    BRLS_BIND(brls::Button, play, "play");    // 播放按钮（播放预设动画）

    /*
     * 静态辅助函数
     * 用于注册滑条组件的通用配置
     * 
     * 参数：
     * cell - 滑条组件
     * init - 初始值
     * title - 滑条标题
     * cb - 值改变时的回调函数
     */
    static void registerCell(brls::SliderCell* cell, float init, const std::string& title, const std::function<float(float)>& cb);

    /*
     * 动画对象 - 用于创建平滑的动画效果
     * Animatable类可以让数值平滑地从一个值变化到另一个值
     * 就像是让魔法变换过程更加流畅自然
     */
    brls::Animatable aniX, aniY;    // X和Y轴动画
    brls::Animatable skew, skew2;   // 倾斜动画
};
