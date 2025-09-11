/*
    带标题图片组件头文件 (CaptionedImage)
    
    这个文件定义了一个特殊的图片组件，它不仅能显示图片，还能显示图片的标题文字
    就像是图书馆里的书，既有封面图片，又有书名标签
    
    用途举例：
    - 游戏角色展示（图片+角色名）
    - 相册应用（照片+照片描述）
    - 商品展示（商品图+商品名）
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证 - 这是一个开源许可证，允许任何人免费使用这些代码
*/

#pragma once  // 这行代码确保这个头文件只被包含一次，就像确保同一本书不会被借阅两次

#include <borealis.hpp>  // 引入Borealis UI框架，这是制作用户界面的工具包

/*
 * CaptionedImage 类 - 带标题的图片组件
 * 
 * 这个类继承自 brls::Box（盒子容器）
 * 继承就像小孩继承父母的特征一样，CaptionedImage拥有Box的所有基本功能
 * 同时还增加了自己的特殊功能：同时显示图片和标题
 */
class CaptionedImage : public brls::Box
{
  public:  // public表示这些内容是公开的，外部代码可以使用
    /*
     * 构造函数声明
     * 构造函数是创建这个组件时自动调用的特殊函数
     * 就像盖房子时的地基建设，为组件做好准备工作
     */
    CaptionedImage();

    /*
     * 当子组件获得焦点时的处理函数
     * 焦点就像是手电筒的光束，指向当前选中的组件
     * 当用户用手柄或键盘选中这个图片时，这个函数会被调用
     * 
     * 参数解释：
     * directChild - 直接的子组件（图片或标签）
     * focusedView - 实际获得焦点的组件
     * override - 表示这个函数重写了父类的同名函数
     */
    void onChildFocusGained(brls::View* directChild, brls::View* focusedView) override;

    /*
     * 当子组件失去焦点时的处理函数
     * 当用户把选择移动到其他地方时，这个函数会被调用
     * 就像手电筒的光束移开了，这个组件不再被"照亮"
     */
    void onChildFocusLost(brls::View* directChild, brls::View* focusedView) override;

    /*
     * 静态创建函数
     * static 关键字表示这个函数属于整个类，而不是某个具体的对象
     * XML解析器会调用这个函数来创建CaptionedImage的新实例
     * 就像工厂里的模具，用来批量生产相同的产品
     */
    static brls::View* create();

  private:  // private表示这些内容是私有的，只有这个类内部可以使用
    /*
     * BRLS_BIND 宏 - 神奇的连接魔法！
     * 
     * 这些宏将XML文件中定义的组件连接到C++代码中的变量
     * 就像给玩具贴上名字标签，这样我们就能在代码中通过名字找到它们
     * 
     * 格式说明：BRLS_BIND(组件类型, 变量名, "XML中的ID名字")
     */
    BRLS_BIND(brls::Image, image, "image");  // 连接图片组件，给它起名叫image
    BRLS_BIND(brls::Label, label, "label");  // 连接文字标签，给它起名叫label
};
