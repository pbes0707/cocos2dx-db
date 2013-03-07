/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-db
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __CCResultSet_h__
#define __CCResultSet_h__

#include "cocos2d.h"

using namespace std;

NS_CC_BEGIN

class CCDatabase;
class CCStatement;

/**
 * @class CCResultSet
 *
 * 封装sqlite3返回的结果集
 */
class CC_DLL CCResultSet : public CCObject {
	friend class CCDatabase;

private:
	/**
	 * 相关的\link CCDatabase CCDatabase\endlink
	 */
    CCDatabase* m_db;

    /**
     * 语句对象
     */
    CCStatement* m_statement;

    /**
     * 结果集列名
     */
	typedef vector<string> StringList;
    StringList m_columnNames;

    /**
     * 查询语句
     */
    string m_sql;

protected:
    /**
     * 构造函数
     *
     * @param db 相关的\link CCDatabase CCDatabase\endlink对象
     * @param statement 查询语句对象
     */
    CCResultSet(CCDatabase* db, CCStatement* statement);

    /**
     * 静态构造函数
     *
     * @param db 相关的\link CCDatabase CCDatabase\endlink对象
     * @param statement 查询语句对象
     * @return \link CCResultSet CCResultSet\endlink
     */
    static CCResultSet* make(CCDatabase* db, CCStatement* statement);

    /**
     * 关闭结果集, 关闭后的结果集不能再被使用。一般不需要主动调用这个方法，因为
     * 析构函数中会调用close
     */
    void close();

public:
    virtual ~CCResultSet();

    /**
     * 光标切换到下一行结果
     *
     * @return true表示成功切换到下一行，false表示无更多数据
     */
    bool next();

    /**
     * 是否还有更多结果
     *
     * @return true表示还有更多结果
     */
    bool hasAnotherRow();

    /**
     * 得到结果集中的列数
     *
     * @return 结果集中的列数
     */
    int columnCount();

    /**
     * 检查某列是否为空值
     *
     * @param columnIdx 列索引
     * @return true表示该行为空
     */
    bool columnIndexIsNull(int columnIdx);

    /**
     * 检查某列是否为空值
     *
     * @param columnName 列名称
     * @return true表示该行为空
     */
    bool columnIsNull(string columnName);

    /**
     * 根据列名得到列索引
     *
     * @param columnName 列名称
     * @return 列索引，从0开始
     */
    int columnIndexForName(string columnName);

    /**
     * 根据列索引得到列名
     *
     * @param columnIdx 列索引
     * @return 列名, 如果索引无效，返回NULL。调用者不需要负责释放指针
     */
    string columnNameForIndex(int columnIdx);

    /**
     * 得到某列的整形数据, 该列的类型如果不是整形，则会被自动转换成整形
     *
     * @param columnName 列名
     * @return 整形数值
     */
    int intForColumn(string columnName);

    /**
     * 得到某列的整形数据, 该列的类型如果不是整形，则会被自动转换成整形
     *
     * @param columnIdx 列索引
     * @return 整形数值
     */
    int intForColumnIndex(int columnIdx);

    /**
     * 得到某列的长整形数据, 该列的类型如果不是长整形，则会被自动转换成64位整数形式，再转换为长整形
     *
     * @param columnName 列名
     * @return 长整形数值
     */
    long longForColumn(string columnName);

    /**
     * 得到某列的长整形数据, 该列的类型如果不是长整形，则会被自动转换成64位整数形式，再转换为长整形
     *
     * @param columnIdx 列索引
     * @return 长整形数值
     */
    long longForColumnIndex(int columnIdx);

    /**
     * 得到某列的64位整数数据, 该列的类型如果不是64位整数，则会被自动转换成64位整数形式
     *
     * @param columnName 列名
     * @return 64位整数值
     */
    int64_t int64ForColumn(string columnName);

    /**
     * 得到某列的64位整数数据, 该列的类型如果不是64位整数，则会被自动转换成64位整数形式
     *
     * @param columnIdx 列索引
     * @return 64位整数值
     */
    int64_t int64ForColumnIndex(int columnIdx);

    /**
     * 得到某列的布尔数据, 该列的类型如果不是布尔，则会被自动转换成整数形式，再判断整数值是否非0
     *
     * @param columnName 列名
     * @return 布尔值
     */
    bool boolForColumn(string columnName);

    /**
     * 得到某列的布尔数据, 该列的类型如果不是布尔，则会被自动转换成整数形式，再判断整数值是否非0
     *
     * @param columnIdx 列索引
     * @return 布尔值
     */
    bool boolForColumnIndex(int columnIdx);

    /**
     * 得到某列的浮点数据, 该列的类型如果不是浮点，则会被自动转换成浮点形式
     *
     * @param columnName 列名
     * @return 浮点值
     */
    double doubleForColumn(string columnName);

    /**
     * 得到某列的浮点数据, 该列的类型如果不是浮点，则会被自动转换成浮点形式
     *
     * @param columnIdx 列索引
     * @return 浮点值
     */
    double doubleForColumnIndex(int columnIdx);

    /**
     * 得到某列的字符串数据，该列的类型如果不是字符串，则会被自动转换成字符串形式
     *
     * @param columnName 列名
     * @return 字符串数据，调用者要负责释放该指针
     */
    string stringForColumn(string columnName);

    /**
     * 得到某列的字符串数据，该列的类型如果不是字符串，则会被自动转换成字符串形式
     *
     * @param columnIdx 列索引
     * @return 字符串数据，调用者要负责释放该指针
     */
    string stringForColumnIndex(int columnIdx);

    /**
     * 得到某列的二进制数据，该列的类型如果不是二进制数据，则会被自动转换成二进制形式
     *
     * @param columnName 列名
     * @param outLen 用来返回数据长度，不能为NULL
     * @return 二进制数据，这份数据是数据库中内容的拷贝，所以调用者要负责释放该指针
     */
    const void* dataForColumn(string columnName, size_t* outLen);

    /**
     * 得到某列的二进制数据，该列的类型如果不是二进制数据，则会被自动转换成二进制形式
     *
     * @param columnIdx 列索引
     * @param outLen 用来返回数据长度，不能为NULL
     * @return 二进制数据，这份数据是数据库中内容的拷贝，所以调用者要负责释放该指针
     */
    const void* dataForColumnIndex(int columnIdx, size_t* outLen);

    /**
     * 得到某列的二进制数据，该列的类型如果不是二进制数据，则会被自动转换成二进制形式
     *
     * @param columnName 列名
     * @param outLen 用来返回数据长度，不能为NULL
     * @return 二进制数据，这份数据是数据库中的内容，所以调用者不需要释放该指针
     */
    const void* dataNoCopyForColumn(string columnName, size_t* outLen);

    /**
     * 得到某列的二进制数据，该列的类型如果不是二进制数据，则会被自动转换成二进制形式
     *
     * @param columnIdx 列索引
     * @param outLen 用来返回数据长度，不能为NULL
     * @return 二进制数据，这份数据是数据库中的内容，所以调用者不需要释放该指针
     */
    const void* dataNoCopyForColumnIndex(int columnIdx, size_t* outLen);

    /*
     * getter and setter
     */

    CCDatabase* getDatabase() { return m_db; }
    CCStatement* getStatement() { return m_statement; }
};

NS_CC_END

#endif // __CCResultSet_h__
