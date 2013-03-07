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
#ifndef __CCStatement_h__
#define __CCStatement_h__

#include "cocos2d.h"

struct sqlite3_stmt;
using namespace std;

NS_CC_BEGIN

class CCDatabase;

/**
 * SQL statement encapsulation
 */
class CC_DLL CCStatement : public CCObject {
	friend class CCDatabase;

private:
	/**
	 * sqlite3的语句对象
	 */
    sqlite3_stmt* m_statement;

    /**
     * 查询字符串
     */
    string m_query;

    /**
     * 被引用的次数
     */
    int m_useCount;

private:
    CCStatement();

public:
    virtual ~CCStatement();

    /**
     * 设置查询语句
     *
     * @param q 查询语句，其内容会被复制，因此方法返回后可以立刻释放
     */
    void setQuery(string q) { m_query = q; }

    /**
     * 获得查询语句
     *
     * @return 查询语句
     */
    const string& getQuery() { return m_query; }

    /**
     * 设置底层的语句对象
     *
     * @param s sqlite3_stmt结构指针
     */
    void setStatement(sqlite3_stmt* s);

    /**
     * 得到底层的语句对象
     *
     * @return sqlite3_stmt结构指针
     */
    sqlite3_stmt* getStatement() { return m_statement; }

    /**
     * 关闭底层的语句对象
     */
    void close();

    /**
     * 重置底层的语句对象
     */
    void reset();
};

NS_CC_END

#endif // __CCStatement_h__
