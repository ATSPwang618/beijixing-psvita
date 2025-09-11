/*
    带标题图片组件实现文件 (CaptionedImage)
    
    这个文件实现了一个有趣的图片组件：当你选中图片时，会显示图片的标题；
    当你离开时，标题就会隐藏起来。就像是一个害羞的小标签，只有在被关注时才出现！
    
    这种设计在很多地方都能看到：
    - 游戏主菜单：选中游戏图标时显示游戏名称
    - 照片应用：选中照片时显示照片信息
    - 文件浏览器：选中文件时显示文件名
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证
*/

#include "view/captioned_image.hpp"  // 引入我们的头文件定义

/*
 * CaptionedImage 构造函数
 * 这是创建带标题图片组件时的初始化过程，就像是搭积木时的第一步
 */
CaptionedImage::CaptionedImage()
{
    /*
     * 从XML文件加载组件布局
     * 这就像是按照说明书来组装玩具
     * XML文件就是我们的"说明书"，告诉程序怎么排列图片和文字
     */
    this->inflateFromXMLRes("xml/views/captioned_image.xml");

    /*
     * 隐藏标题标签
     * 刚创建时，标题是隐藏的，只有当用户选中图片时才会显示
     * 就像是一个害羞的小朋友，一开始不敢露面
     * [] {} 是一个空的回调函数，表示隐藏完成后不需要做其他事情
     */
    this->label->hide([] {});

    /*
     * 转发XML属性到图片组件
     * 当在XML中设置图片的属性时，我们需要把这些设置传递给实际的图片组件
     * 就像是传话游戏，把消息从一个人传给另一个人
     */
    this->forwardXMLAttribute("scalingType", this->image);    // 图片缩放类型
    this->forwardXMLAttribute("image", this->image);          // 图片路径
    this->forwardXMLAttribute("focusUp", this->image);        // 向上导航
    this->forwardXMLAttribute("focusRight", this->image);     // 向右导航
    this->forwardXMLAttribute("focusDown", this->image);      // 向下导航
    this->forwardXMLAttribute("focusLeft", this->image);      // 向左导航
    this->forwardXMLAttribute("imageWidth", this->image, "width");   // 图片宽度
    this->forwardXMLAttribute("imageHeight", this->image, "height"); // 图片高度

    /*
     * 转发XML属性到标签组件
     * "caption"属性会变成标签的"text"属性，就像是给照片写说明文字
     */
    this->forwardXMLAttribute("caption", this->label, "text");

    /*
     * 添加手势识别器
     * 这让组件可以响应触摸操作（在支持触摸的设备上）
     * TapGestureRecognizer 就像是一个"点击侦探"，专门监听用户的点击行为
     * 参数说明：
     * - this: 手势的目标是当前组件
     * - TapGestureConfig: 手势配置，这里设置为静音（不播放声音）
     */
    this->addGestureRecognizer(new brls::TapGestureRecognizer(this, brls::TapGestureConfig(false, brls::SOUND_NONE, brls::SOUND_NONE, brls::SOUND_NONE)));
}

/*
 * 当子组件获得焦点时的处理函数
 * 当用户用手柄或键盘选中这个图片时，这个函数会被调用
 * 就像是手电筒照亮了这个组件，我们需要让标题显示出来
 */
void CaptionedImage::onChildFocusGained(brls::View* directChild, brls::View* focusedView)
{
    /*
     * 首先调用父类的同名函数
     * 这确保了基本的焦点处理逻辑能够正常工作
     * 就像是继承了爸爸妈妈的好习惯，然后再加上自己的特色
     */
    Box::onChildFocusGained(directChild, focusedView);

    /*
     * 显示标题标签
     * 当组件被选中时，标题就像一个害羞的小朋友终于愿意出来打招呼
     * [] {} 是一个空的回调函数，表示显示完成后不需要做其他事情
     */
    this->label->show([] {});
}

/*
 * 当子组件失去焦点时的处理函数
 * 当用户把选择移动到其他地方时，这个函数会被调用
 * 就像是手电筒的光束移开了，我们需要让标题重新隐藏起来
 */
void CaptionedImage::onChildFocusLost(brls::View* directChild, brls::View* focusedView)
{
    /*
     * 首先调用父类的同名函数
     * 确保基本的焦点处理逻辑能够正常工作
     */
    Box::onChildFocusLost(directChild, focusedView);

    /*
     * 隐藏标题标签
     * 当组件不再被选中时，标题就像害羞的小朋友又躲起来了
     * 这种设计让界面保持简洁，只在需要时显示额外信息
     */
    this->label->hide([] {});
}

/*
 * 静态创建函数
 * 这个函数被XML解析器调用，用来创建CaptionedImage的新实例
 * 就像是工厂里的生产线，每次调用都会制造出一个新的组件
 */
brls::View* CaptionedImage::create()
{
    /*
     * 使用new关键字创建一个新的CaptionedImage对象
     * new就像是魔法咒语，能够变出新的东西
     * 返回的指针会被UI系统管理，我们不需要担心内存清理
     */
    return new CaptionedImage();
}
