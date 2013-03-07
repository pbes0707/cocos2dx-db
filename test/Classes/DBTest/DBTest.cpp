#include "DBTest.h"
#include "../testResource.h"
#include "cocos2d.h"

TESTLAYER_CREATE_FUNC(DBCreateDatabase);
TESTLAYER_CREATE_FUNC(DBSQLFile);
TESTLAYER_CREATE_FUNC(DBTransaction);

static NEWTESTFUNC createFunctions[] = {
    CF(DBCreateDatabase),
	CF(DBSQLFile),
	CF(DBTransaction)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void DBTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}


std::string DBDemo::title()
{
    return "DBTest";
}

std::string DBDemo::subtitle()
{
    return "";
}

void DBDemo::onEnter()
{
    CCLayer::onEnter();

    // add title and subtitle
    std::string str = title();
    const char * pTitle = str.c_str();
    CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

    std::string strSubtitle = subtitle();
    if( ! strSubtitle.empty() ) 
    {
        CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
    }    

    // add menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(DBDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(DBDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(DBDemo::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);
}

void DBDemo::onExit()
{
    CCLayer::onExit();
}

void DBDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new DBTestScene();
    s->addChild( restartAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void DBDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new DBTestScene();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void DBDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new DBTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// Create Database
//
//------------------------------------------------------------------
void DBCreateDatabase::onEnter()
{
    DBDemo::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
}

std::string DBCreateDatabase::subtitle()
{
    return "Create Database";
}

//------------------------------------------------------------------
//
// SQL File
//
//------------------------------------------------------------------
void DBSQLFile::onEnter()
{
    DBDemo::onEnter();
	
    CCSize s = CCDirector::sharedDirector()->getWinSize();
}

std::string DBSQLFile::subtitle()
{
    return "SQL File";
}

//------------------------------------------------------------------
//
// Transaction
//
//------------------------------------------------------------------
void DBTransaction::onEnter()
{
    DBDemo::onEnter();
	
    CCSize s = CCDirector::sharedDirector()->getWinSize();
}

std::string DBTransaction::subtitle()
{
    return "Transaction";
}