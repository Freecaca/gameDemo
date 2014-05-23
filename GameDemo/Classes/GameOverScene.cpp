//
//  GameOverScene.cpp
//  GameDemo
//
//  Created by Wuzhiyong on 5/23/14.
//
//

#include "GameOverScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

//创建 GameOverScene 场景
bool GameOverScene::init()
{
    if (Scene::init()) {
        
        //添加gameOverLayer层
        this->_layer = GameOverLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }else {
        return false;
    }
}

//GameOverScene析构函数
GameOverScene::~GameOverScene() {
    if (_layer) {
        _layer->release();
        _layer =NULL;
        
    }
}

//创建 GameOverLayer 层
bool GameOverLayer::init() {
    if (! LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }
    
    auto winSize =Director::getInstance()->getVisibleSize();
    
    this->_label =LabelTTF::create("", "Marker Felt", 48);
    _label->retain();
    _label->setColor(Color3B(0, 0, 0));
    _label->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(_label);
    
    auto actionDone =CallFunc::create(CC_CALLBACK_0(GameOverLayer::gameOverDone, this));
    this->runAction(Sequence::create(DelayTime::create(3), actionDone, NULL));
    return true;
}

//GameOverLayer析构函数
GameOverLayer::~GameOverLayer() {
    if (_label) {
        _label->release();
        _label=NULL;
        
    }
}

//GameOver 场景结束
void GameOverLayer::gameOverDone() {
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

