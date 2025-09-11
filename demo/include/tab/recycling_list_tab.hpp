/*
    循环列表标签页头文件 (RecyclingListTab)
    
    这个文件定义了一个可循环利用的列表组件，就像是一个智能的图书管理系统
    它能够高效地显示大量数据，而不会让程序变慢
    
    主要包含以下几个类：
    1. RecyclerHeader - 列表分组标题（就像书架上的分类标签）
    2. RecyclerCell - 列表中的每一项（就像书架上的每一本书）
    3. DataSource - 数据提供者（就像图书管理员，知道所有书的信息）
    4. RecyclingListTab - 整个列表页面（就像整个图书馆）
    
    "循环利用"的概念：
    - 当列表很长时，只创建能在屏幕上看到的几个列表项
    - 当用户滚动时，移出屏幕的项目会被重新利用来显示新内容
    - 这样既节省内存，又保持流畅的滚动体验
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * RecyclerHeader 类 - 循环列表的分组标题
 * 
 * 这个类继承自 brls::RecyclerHeader
 * 用来显示列表分组的标题，就像书店里的"科幻小说"、"历史书籍"等分类标签
 * 目前这个类是空的，使用默认的标题样式
 */
class RecyclerHeader
    : public brls::RecyclerHeader
{
    // 暂时没有自定义内容，使用父类的默认实现
};

/*
 * RecyclerCell 类 - 循环列表的单个列表项
 * 
 * 这个类继承自 brls::RecyclerCell
 * 每个列表项都是这个类的一个实例，就像书架上的每一本书
 * 包含图片、文字和装饰元素
 */
class RecyclerCell
    : public brls::RecyclerCell
{
  public:
    /*
     * 构造函数
     * 初始化列表项的外观和行为
     */
    RecyclerCell();

    /*
     * BRLS_BIND 宏 - 组件绑定
     * 将XML中定义的UI组件绑定到C++变量，方便在代码中操作
     */
    BRLS_BIND(brls::Rectangle, accent, "brls/sidebar/item_accent");  // 强调色矩形（装饰条）
    BRLS_BIND(brls::Label, label, "title");                         // 标题文字标签
    BRLS_BIND(brls::Image, image, "image");                         // 图片组件

    /*
     * 静态创建函数
     * RecyclerFrame会调用这个函数来创建新的列表项
     * 就像工厂里的生产线，每次需要新产品时就调用这个函数
     */
    static RecyclerCell* create();
};

/*
 * DataSource 类 - 数据源管理器
 * 
 * 这个类继承自 brls::RecyclerDataSource
 * 它是整个列表的"大脑"，负责管理所有数据和回答各种问题：
 * - 一共有多少组数据？
 * - 每组有多少项？
 * - 第X组第Y项应该显示什么内容？
 * - 用户点击了某一项后应该做什么？
 */
class DataSource
    : public brls::RecyclerDataSource
{
  public:
    /*
     * 返回有多少个分组
     * 就像问图书管理员："图书馆一共有多少个分类？"
     */
    int numberOfSections(brls::RecyclerFrame* recycler) override;
    
    /*
     * 返回指定分组中有多少行数据
     * 就像问："科幻小说分类里有多少本书？"
     */
    int numberOfRows(brls::RecyclerFrame* recycler, int section) override;
    
    /*
     * 为指定位置创建列表单元格
     * 就像问："请给我科幻小说分类的第5本书的信息"
     */
    brls::RecyclerCell* cellForRow(brls::RecyclerFrame* recycler, brls::IndexPath index) override;
    
    /*
     * 处理用户选择某一项的事件
     * 就像用户说："我要借这本书"时的处理流程
     */
    void didSelectRowAt(brls::RecyclerFrame* recycler, brls::IndexPath indexPath) override;
    
    /*
     * 返回分组的标题文字
     * 就像返回"科幻小说"、"历史书籍"这样的分类名称
     */
    std::string titleForHeader(brls::RecyclerFrame* recycler, int section) override;
};

/*
 * RecyclingListTab 类 - 循环列表标签页
 * 
 * 这是整个列表页面的主容器，继承自 brls::Box
 * 它包含了循环列表组件，并将数据源连接到列表上
 * 就像是整个图书馆的主建筑，里面包含了书架和管理系统
 */
class RecyclingListTab : public brls::Box
{
  public:
    /*
     * 构造函数
     * 初始化整个列表页面，设置数据源和样式
     */
    RecyclingListTab();

    /*
     * 静态创建函数
     * XML解析器调用这个函数来创建RecyclingListTab的实例
     */
    static brls::View* create();

  private:
    /*
     * BRLS_BIND 宏 - 绑定循环列表组件
     * 将XML中的RecyclerFrame组件绑定到C++变量
     */
    BRLS_BIND(brls::RecyclerFrame, recycler, "recycler");
};
