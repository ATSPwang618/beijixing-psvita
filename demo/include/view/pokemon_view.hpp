/*
    宝可梦视图组件头文件
    
    这个文件定义了宝可梦相关的类：
    1. Pokemon类 - 存储宝可梦数据的简单数据类
    2. PokemonView类 - 显示宝可梦信息的UI组件
    
    版权所有 2021 XITRIX
    使用 Apache 2.0 许可证
*/

#pragma once  // 防止头文件重复包含

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * Pokemon 类 - 宝可梦数据类
 * 
 * 这是一个简单的数据类，用来存储宝可梦的基本信息
 * 就像是宝可梦的身份证，记录了它的基本属性
 */
class Pokemon
{
  public:
    std::string id;    // 宝可梦的编号（如"001", "002"等）
    std::string name;  // 宝可梦的名字（如"皮卡丘", "妙蛙种子"等）

    /*
     * Pokemon 构造函数
     * 创建一个新的宝可梦对象时调用
     * 
     * 参数：
     * std::string id - 宝可梦编号
     * std::string name - 宝可梦名字
     */
    Pokemon(std::string id, std::string name)
        : id(id)      // 初始化编号
        , name(name)  // 初始化名字
    {
        // 构造函数体为空，所有初始化都在上面的初始化列表中完成
    }
};

/*
 * PokemonView 类 - 宝可梦显示视图
 * 
 * 这个类继承自brls::Box，用来显示宝可梦的详细信息
 * 包括宝可梦的图片、名字、描述等内容
 */
class PokemonView : public brls::Box
{
  public:
    /*
     * 带参数的构造函数
     * 使用指定的宝可梦数据创建视图
     */
    PokemonView(Pokemon pokemon);
    
    /*
     * 默认构造函数
     * 如果没有提供宝可梦数据，就使用默认的宝可梦
     * 这里使用了"构造函数委托"技术，调用另一个构造函数
     */
    PokemonView()
        : PokemonView(Pokemon("001", "默认宝可梦"))  // 创建一个默认的宝可梦
    {
        // 构造函数体为空，实际工作由被委托的构造函数完成
    }

    /*
     * 静态创建函数
     * XML解析器会调用这个函数来创建PokemonView的实例
     */
    static brls::View* create();

  private:
    /*
     * 私有成员变量和绑定
     */
    Pokemon pokemon;  // 存储要显示的宝可梦数据
    
    /*
     * BRLS_BIND 宏 - 将XML中的组件绑定到C++变量
     * 这样我们就可以在C++代码中直接操作XML中定义的组件
     */
    BRLS_BIND(brls::Image, image, "image");              // 绑定宝可梦图片组件
    BRLS_BIND(brls::Label, description, "description");  // 绑定描述文字标签
};
