/*
    主界面活动实现文件 (MainActivity)
    
    这个文件非常简单，因为MainActivity的所有内容都在XML文件中定义了
    这是一种常见的设计模式：将界面布局和逻辑代码分离
    
    就像是一个空房子：
    - C++代码是房子的结构框架
    - XML文件是房子的装修和家具摆放
    
    MainActivity使用了CONTENT_FROM_XML_RES宏，这意味着：
    - 界面布局完全由XML文件描述
    - 所有的标签页、按钮、组件都在XML中定义
    - C++代码只需要包含头文件就足够了
    
    这种方式的好处：
    1. 界面和逻辑分离，代码更清晰
    2. 设计师可以直接修改XML而不需要碰C++代码
    3. 更容易维护和修改界面布局
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证
*/

#include "activity/main_activity.hpp"  // 引入主界面活动的头文件

/*
 * 注意：这个.cpp文件几乎是空的！
 * 
 * 这是因为MainActivity使用了CONTENT_FROM_XML_RES宏
 * 所有的界面内容和行为都在以下地方定义：
 * 
 * 1. 头文件 (main_activity.hpp) - 定义了类结构
 * 2. XML文件 (activity/main.xml) - 定义了界面布局
 * 3. 各个标签页的C++文件 - 定义了具体功能
 * 
 * 这就像是一个乐高积木盒：
 * - MainActivity是盒子本身
 * - 各个标签页是不同的积木块
 * - XML文件是积木的摆放说明书
 */
