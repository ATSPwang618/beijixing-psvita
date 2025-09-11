/*
    循环列表标签页实现文件
    
    这个文件展示了如何使用RecyclerView（循环视图）来显示列表数据
    RecyclerView是一种高效的列表组件，类似于手机APP中的滚动列表
    它可以显示大量数据而不会消耗太多内存
    
    版权所有 2020-2021 natinusala
    使用 Apache 2.0 许可证
*/

#include "tab/recycling_list_tab.hpp"
#include "view/pokemon_view.hpp"

// 全局宝可梦数据数组，存储所有要显示的宝可梦
std::vector<Pokemon> pokemons;

/*
 * RecyclerCell 类 - 循环列表单元格
 * 每一行列表项都是一个RecyclerCell
 * 就像表格中的一行，可以显示图片、文字等内容
 */
RecyclerCell::RecyclerCell()
{
    // 从XML文件加载单元格的布局设计
    this->inflateFromXMLRes("xml/cells/cell.xml");
}

/*
 * 创建新的RecyclerCell实例
 * RecyclerView会调用这个函数来创建新的列表项
 */
RecyclerCell* RecyclerCell::create()
{
    return new RecyclerCell();
}

/*
 * 数据源类的各种方法
 * DataSource负责告诉RecyclerView要显示什么内容
 * 就像是列表的数据管理员
 */

/*
 * 返回有多少个分组(Section)
 * 分组就像是把列表分成几个部分，每个部分有自己的标题
 */
int DataSource::numberOfSections(brls::RecyclerFrame* recycler)
{
    return 2;  // 返回2个分组
}

/*
 * 返回指定分组中有多少行数据
 * 每一行对应一个宝可梦
 */
int DataSource::numberOfRows(brls::RecyclerFrame* recycler, int section)
{
    return pokemons.size();  // 返回宝可梦数组的大小
}

/*
 * 返回分组的标题文字
 * 第一个分组没有标题，其他分组显示"Section #X"
 */
std::string DataSource::titleForHeader(brls::RecyclerFrame* recycler, int section) 
{
    if (section == 0)
        return "";  // 第一个分组没有标题
    return "Section #" + std::to_string(section+1);  // 其他分组显示编号
}

/*
 * 为指定位置创建列表单元格
 * 这个函数负责创建每一行要显示的内容
 * 
 * 参数：
 * recycler - RecyclerView对象
 * indexPath - 位置信息，包含分组号(section)和行号(row)
 */
brls::RecyclerCell* DataSource::cellForRow(brls::RecyclerFrame* recycler, brls::IndexPath indexPath)
{
    // 从回收池中获取一个可重用的单元格（提高性能）
    RecyclerCell* item = (RecyclerCell*)recycler->dequeueReusableCell("Cell");
    
    // 设置单元格显示的宝可梦名字
    item->label->setText(pokemons[indexPath.row].name);
    
    // 设置单元格显示的宝可梦缩略图
    item->image->setImageFromRes("img/pokemon/thumbnails/" + pokemons[indexPath.row].id + ".png");
    
    return item;  // 返回配置好的单元格
}

/*
 * 用户点击列表项时的处理函数
 * 当用户选择某个宝可梦时，会显示宝可梦的详细页面
 */
void DataSource::didSelectRowAt(brls::RecyclerFrame* recycler, brls::IndexPath indexPath)
{
    /*
     * 下面这行被注释的代码用于调试，可以在日志中显示被选中的项目
     */
//    brls::Logger::info("Item Index(" + std::to_string(index.section) + ":" + std::to_string(index.row) + ") selected.");
    
    // 创建并显示选中宝可梦的详细视图
    recycler->present(new PokemonView(pokemons[indexPath.row]));
}

/*
 * RecyclingListTab 构造函数
 * 初始化循环列表标签页
 */
RecyclingListTab::RecyclingListTab()
{
    // 从XML文件加载标签页布局
    this->inflateFromXMLRes("xml/tabs/recycling_list.xml");
    
    /*
     * 准备宝可梦数据
     * 这里我们手动添加一些宝可梦作为演示数据
     */
    pokemons.clear();  // 清空数组
    pokemons.push_back(Pokemon("001", "妙蛙种子"));    // 添加宝可梦数据
    pokemons.push_back(Pokemon("004", "小火龙"));
    pokemons.push_back(Pokemon("007", "杰尼龟"));
    pokemons.push_back(Pokemon("011", "铁甲蛹"));
    pokemons.push_back(Pokemon("014", "大针蜂"));
    pokemons.push_back(Pokemon("017", "比比鸟"));
    pokemons.push_back(Pokemon("021", "烈雀"));
    pokemons.push_back(Pokemon("024", "阿柏怪"));
    pokemons.push_back(Pokemon("027", "穿山鼠"));

    /*
     * 配置RecyclerView
     */
    recycler->estimatedRowHeight = 70;  // 设置每行的预估高度为70像素
    
    // 注册单元格类型，告诉RecyclerView如何创建不同类型的单元格
    recycler->registerCell("Header", []() { return RecyclerHeader::create(); });  // 注册头部单元格
    recycler->registerCell("Cell", []() { return RecyclerCell::create(); });      // 注册普通单元格
    
    // 设置数据源，RecyclerView会从这里获取要显示的数据
    recycler->setDataSource(new DataSource());
}

/*
 * 静态创建函数
 * XML解析器调用这个函数来创建RecyclingListTab的新实例
 */
brls::View* RecyclingListTab::create()
{
    // XML引擎调用这个函数来创建新的RecyclingListTab
    return new RecyclingListTab();
}
