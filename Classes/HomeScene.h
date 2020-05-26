#pragma once
#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

class  HomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void callBack1(cocos2d::Ref* pSender);

    void callBack2(cocos2d::Ref* pSender,cocos2d::Sprite* sprite);

    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
};
#endif //__HOME_SCENE_H__