/*
    变换效果标签页实现文件 (TransformTab)
    
    这个文件实现了一个神奇的2D图形变换实验室！
    小朋友可以通过拖动滑条来实时看到图片的各种变换效果
    
    支持的变换类型：
    1. 平移 (Translation) - 让图片移动位置
    2. 缩放 (Scale) - 让图片变大或变小
    3. 旋转 (Rotation) - 让图片转圈圈
    4. 倾斜 (Skew) - 让图片倾斜变形
    5. 尺寸调整 - 改变图片本身的大小
    
    还包含动画功能：
    - 播放按钮：自动播放一段预设的变换动画
    - 重置按钮：把所有设置恢复到初始状态
    
    这就像是一个魔法工作台，每个滑条都是不同的魔法咒语！
    
    版权所有 2024 xfangfang
    使用 Apache 2.0 许可证
*/

#include "tab/transform_tab.hpp"  // 引入变换标签页头文件

/*
 * 常量定义 - 这些是魔法工作台的基本设置
 * 使用#define定义常量是C++的传统做法，就像给常用的数字起个好记的名字
 */
#define POINTER_SIZE 20      // 滑条指针大小（那个可拖动的小圆点）
#define BOX_SIZE 100         // 变换盒子的基础大小（100像素）
#define CONTAINER_SIZE 400   // 容器大小（400像素，给变换留出足够空间）
#define ANIMATION 4000       // 动画持续时间（4000毫秒 = 4秒）

/*
 * TransformTab 构造函数
 * 这是变换实验室的初始化过程，设置所有滑条和按钮的行为
 */
TransformTab::TransformTab()
{
    /*
     * 从XML文件加载页面布局
     * 就像按照设计图纸来布置实验室的各种设备
     */
    this->inflateFromXMLRes("xml/tabs/transform.xml");

    /*
     * 配置播放按钮
     * 当用户点击播放按钮时，会自动播放一段预设的变换动画
     * 就像按下魔法水晶球，自动展示各种魔法效果
     */
    play->registerClickAction([this](...)
        {
            aniX.stop();
            aniY.stop();
            skew.stop();
            skew2.stop();

            aniX.reset(0);
            aniX.addStep(1.0, ANIMATION, brls::EasingFunction::exponentialOut);
            aniX.addStep(0, ANIMATION, brls::EasingFunction::cubicIn);
            aniX.addStep(0.5, ANIMATION, brls::EasingFunction::exponentialOut);
            aniX.addStep(0, ANIMATION, brls::EasingFunction::cubicIn);
            aniX.setTickCallback([this](){transX->slider->setProgress(aniX);});

            aniY.reset(0);
            aniY.addStep(1.0, ANIMATION, brls::EasingFunction::bounceOut);
            aniY.addStep(0.0, ANIMATION, brls::EasingFunction::cubicIn);
            aniY.addStep(1.0, ANIMATION, brls::EasingFunction::bounceOut);
            aniY.addStep(0.0, ANIMATION, brls::EasingFunction::cubicIn);
            aniY.setTickCallback([this](){transY->slider->setProgress(aniY);});

            skew.reset(0);
            skew.addStep(1, ANIMATION, brls::EasingFunction::bounceOut);
            skew.addStep(0, ANIMATION, brls::EasingFunction::cubicIn);
            skew.setTickCallback([this](){
                    skewY->slider->setProgress(skew);
                    scaleX->slider->setProgress(1 - skew);
                });

            skew2.reset(0);
            skew2.addStep(0, ANIMATION * 2);
            skew2.addStep(1, ANIMATION, brls::EasingFunction::bounceOut);
            skew2.addStep(0, ANIMATION, brls::EasingFunction::cubicIn);
            skew2.setTickCallback([this](){
                    skewX->slider->setProgress(skew2);
                    scaleY->slider->setProgress(1 - skew2);
                });

            aniX.start();
            aniY.start();
            skew.start();
            skew2.start();

            return true; });

    reset->registerClickAction([this](...)
        {
            aniX.stop();
            aniY.stop();
            skew.stop();
            skew2.stop();

            transX->slider->setProgress(0);
            transY->slider->setProgress(0);
            scaleX->slider->setProgress(1);
            scaleY->slider->setProgress(1);
            skewX->slider->setProgress(0);
            skewY->slider->setProgress(0);
            rotate->slider->setProgress(0);
            boxWidth->slider->setProgress(1);
            boxHeight->slider->setProgress(1);
            fontScaleX->slider->setProgress(1);
            fontScaleY->slider->setProgress(1);
            return true; });

    registerCell(transX, 0, "transX", [this](float value)
        { box->setTranslationX((CONTAINER_SIZE - BOX_SIZE) * value); return value; });

    registerCell(transY, 0, "transY", [this](float value)
        { box->setTranslationY((CONTAINER_SIZE - BOX_SIZE) * value); return value; });

    registerCell(scaleX, 1, "scaleX", [this](float value)
        { value = value * 2 - 1;
        box->setScaleX(value); return value; });

    registerCell(scaleY, 1, "scaleY", [this](float value)
        { value = value * 2 - 1;
        box->setScaleY(value); return value; });

    registerCell(skewX, 0, "skewX", [this](float value)
        { box->setSkewX(value * NVG_PI); return value; });

    registerCell(skewY, 0, "skewY", [this](float value)
        { box->setSkewY(value * NVG_PI); return value; });

    registerCell(rotate, 0, "rotate", [this](float value)
        { box->setRotate(value * NVG_PI * 2); return value; });

    registerCell(boxWidth, 1, "width", [this](float value)
        { box->setWidth(value * BOX_SIZE); return value; });

    registerCell(boxHeight, 1, "height", [this](float value)
        { box->setHeight(value * BOX_SIZE); return value; });

    registerCell(fontScaleX, 1, "fontSX", [this](float value)
        { value = value * 2 - 1;
        box->setFontScaleX(value); return value; });

    registerCell(fontScaleY, 1, "fontSY", [this](float value)
        { value = value * 2 - 1;
        box->setFontScaleY(value); return value; });
}

void TransformTab::registerCell(brls::SliderCell* cell, float init, const std::string& title, const std::function<float(float)>& cb)
{
    cell->setDetailText(fmt::format("{:.2f}", cb(init)));
    cell->slider->setPointerSize(POINTER_SIZE);
    cell->init(title, init, [cb, cell](float value)
        { cell->setDetailText(fmt::format("{:.2f}", cb(value))); });
}

brls::View* TransformTab::create()
{
    return new TransformTab();
}

void TransformBox::draw(NVGcontext* vg, float x, float y, float width, float height, brls::Style style, brls::FrameContext* ctx)
{
    float centerX = width * fabs(scale_x) / 2, centerY = height * fabs(scale_y) / 2;
    nvgSave(vg);
    nvgTranslate(vg, x + centerX, y + centerY);
    nvgRotate(vg, rotate);
    nvgSkewX(vg, skew_x);
    nvgSkewY(vg, skew_y);
    nvgScale(vg, scale_x, scale_y);
    brls::Image::draw(vg, -centerX, -centerY, width, height, style, ctx);
    nvgTranslate(vg, -centerX, -centerY);
    nvgScale(vg, font_scale_x, font_scale_y);
    nvgText(vg, 4, 18, "demo", nullptr);
    nvgRestore(vg);
}

void TransformBox::setRotate(float deg)
{
    rotate = deg;
}

void TransformBox::setSkewX(float deg)
{
    skew_x = deg;
}

void TransformBox::setSkewY(float deg)
{
    skew_y = deg;
}

void TransformBox::setScaleX(float value)
{
    scale_x = value;
}

void TransformBox::setScaleY(float value)
{
    scale_y = value;
}

void TransformBox::setFontScaleX(float size)
{
    font_scale_x = size;
}

void TransformBox::setFontScaleY(float size)
{
    font_scale_y = size;
}

brls::View* TransformBox::create()
{
    return new TransformBox();
}