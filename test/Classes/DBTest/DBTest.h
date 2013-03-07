#ifndef _DBTest_H_
#define _DBTest_H_

#include "../testBasic.h"

using namespace std;
USING_NS_CC;


enum
{
    DB_CREATE_DATABASE_LAYER = 0,
	DB_SQL_FILE_LAYER,
	DB_TRANSACTION_LAYER,
    DB_LAYER_COUNT,
};


// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
class DBTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class DBDemo : public CCLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
	
    virtual string title();
    virtual string subtitle();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class DBCreateDatabase : public DBDemo
{
public:
    virtual void onEnter();
    virtual string subtitle();
};

class DBSQLFile : public DBDemo
{
public:
    virtual void onEnter();
    virtual string subtitle();
};

class DBTransaction : public DBDemo
{
public:
    virtual void onEnter();
    virtual string subtitle();
};

#endif
