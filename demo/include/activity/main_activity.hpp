/*
    主界面活动类定义文件
    
    这个文件定义了程序的主界面活动(MainActivity)
    Activity(活动)就像是手机APP中的一个页面
    比如微信的聊天页面、朋友圈页面等都是不同的Activity
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证
*/

#pragma once  // 确保这个头文件只被包含一次，避免重复定义

#include <borealis.hpp>  // 引入Borealis UI框架

/*
 * MainActivity 类 - 主界面活动
 * 
 * 这个类继承自 brls::Activity，就像小孩继承父母的特征一样
 * 它会拥有Activity的所有基本功能，比如显示界面、处理按键等
 */
class MainActivity : public brls::Activity
{
  public:
    /*
     * CONTENT_FROM_XML_RES 宏定义
     * 
     * 这行代码的意思是："这个Activity的界面内容来自XML文件"
     * XML文件就像是界面的设计图纸，描述了：
     * - 按钮放在哪里
     * - 文字显示什么内容  
     * - 图片如何排列
     * - 颜色和大小等样式
     * 
     * "activity/main.xml" 是XML文件的路径
     * 就像告诉程序："去activity文件夹里找main.xml这张设计图"
     */
    CONTENT_FROM_XML_RES("activity/main.xml");
};
