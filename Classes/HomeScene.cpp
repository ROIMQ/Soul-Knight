#include"HomeScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
Scene* HomeScene::createScene()
{
    return HomeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //设置背景图片 
    auto homeMap = Sprite::create("Map/Home.png");//记得要改一下路径
    if (homeMap == nullptr)
    {
        problemLoading("'Map/Home.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        homeMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(homeMap, 0);
    }
    //设置背景音乐
    auto audio = SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("Music/Home.mp3", true); // set the background music and continuously play it.
    //设置回退按钮
    auto turnBack = ui::Button::create("Map/turn_back.png", "Map/turn_back.png", "Map/turn_back.png");
    turnBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        auto audio = SimpleAudioEngine::getInstance();//定义变量须放在switch外面
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            audio->playBackgroundMusic("Music/Forest.mp3");
            Director::getInstance()->popScene();//返回LoadingScene
            break;
        default:
            break;
        }
        });
    turnBack->setPosition(Vec2(970, 10));
    turnBack->setAnchorPoint(Vec2(0, 0));
    this->addChild(turnBack,1);
    //设置传送门
    auto door = Sprite::create("Map/door.png");
    door->setPosition(Vec2(605, 710));
    this->addChild(door, 2);
    auto moveRepeat = MoveBy::create(0.8, Vec2(0, 12));//设置动作
    door->runAction(RepeatForever::create(Sequence::create(moveRepeat, moveRepeat->reverse(), NULL)));//永远执行，来回抖动
    //设置菜单隐藏项
    auto transParentPicture = Sprite::create("Map/transparent_picture.png");
    transParentPicture->setPosition(Vec2(100, 580));
    transParentPicture ->setAnchorPoint(Vec2(0, 1));
    //隐藏
    auto hide = CCHide::create();
    transParentPicture->runAction(hide);
    this->addChild(transParentPicture, 3);
    //定义隐藏显现监听器
    auto listener1 = EventListenerCustom::create("hideAndShowEvent", [&](EventCustom* event_)mutable {
        Sprite* sprite = static_cast<Sprite*>(event_->getCurrentTarget());
        log("myself listener");
        auto hide = CCHide::create();
        auto show = CCShow::create();
        if (sprite->isVisible())
            sprite->runAction(hide);
        else
            sprite->runAction(show);
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, transParentPicture);
    //控制菜单
    auto intercalateItem= MenuItemImage::create("Map/intercalate.png", "Map/catercalate.png", CC_CALLBACK_1(HomeScene::callBack1, this));
    intercalateItem->setPosition(Vec2(50,550));
    auto menu1 = Menu::create(intercalateItem, nullptr);
    menu1->setPosition(Vec2::ZERO);//
    this->addChild(menu1, 4);
    //音乐菜单
    auto closeMusic = Sprite::create("Map/music_control2.png");
    auto closeMusicItem = MenuItemImage::create("Map/music_control1.png", "Map/music_control1.png",
        [&](cocos2d::Ref* pSender) {
            EventCustom event("closeAndResumeEvent");
            _eventDispatcher->dispatchEvent(&event);
        }
        );
    closeMusicItem->setPosition(Vec2(1150,540));
    closeMusic->setPosition(Vec2(1150, 540));
    auto menu2 = Menu::create(closeMusicItem, nullptr);
    menu2->setPosition(Vec2::ZERO);//
    this->addChild(menu2, 4);
    this->addChild(closeMusic, 5);
    closeMusic->runAction(hide->clone());
    //定义音乐暂停与恢复监听器
    auto listener2 = EventListenerCustom::create("closeAndResumeEvent", [&](EventCustom* event_)mutable {
        Sprite* sprite = static_cast<Sprite*>(event_->getCurrentTarget());
        auto hide = CCHide::create();
        auto show = CCShow::create();
        auto audio = SimpleAudioEngine::getInstance();
        if (audio->isBackgroundMusicPlaying())
        {
            sprite->runAction(show);
            audio->pauseBackgroundMusic();
        }
        else
        {
            sprite->runAction(hide);
            audio->resumeBackgroundMusic();
        }
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, closeMusic);
    //设置精灵
    auto ant1 = Sprite::create("Map/ant1.png");//ant1
    ant1->setPosition(Vec2(770, 440));
    ant1->setScale(0.7);
    this->addChild(ant1,5);
    auto ant3 = Sprite::create("Map/ant2.png");//ant3
    ant3->setPosition(Vec2(318, 620));
    ant3->setScale(0.7);
    ant3->setAnchorPoint(Vec2(0, 0));
    this->addChild(ant3,5);
    auto Knight = Sprite::create("Map/Knight.png");//骑士
	Knight->setPosition(Vec2(770, 620));
	Knight->setScale(0.7);
	Knight->setAnchorPoint(Vec2(0, 0));
    this->addChild(Knight,5);
    auto Ranger = Sprite::create("Map/Ranger.png");//游侠
	Ranger->setPosition(Vec2(1030, 200));
	Ranger->setScale(0.7);
	Ranger->setAnchorPoint(Vec2(0, 0));
    this->addChild(Ranger, 5);
    //模拟抖动动作
    auto scaleTo1 = ScaleTo::create(0.3, 0.67, 0.77);
    auto scaleTo2 = ScaleTo::create(0.3, 0.72, 0.68);
    auto scaleTo3 = ScaleTo::create(0.3, 0.72, 0.73);
    ant1->runAction(RepeatForever::create(Sequence::create(scaleTo1, scaleTo2, NULL)));//永远执行，来回抖动
    ant3->runAction(RepeatForever::create(Sequence::create(scaleTo3, scaleTo2, NULL)->clone()));
    Knight->runAction(RepeatForever::create(Sequence::create(scaleTo3, scaleTo2, NULL)->clone()));
	Ranger->runAction(RepeatForever::create(Sequence::create(scaleTo3, scaleTo2, NULL)->clone()));
    return true;
}

void HomeScene::callBack1(cocos2d::Ref* pSender)
{
    EventCustom event("hideAndShowEvent");
    _eventDispatcher->dispatchEvent(&event);
}
