#pragma once
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <vector>
#include <map>
#include <deque>
#include <functional>
#include <string>
#include <algorithm>
#include "speaker.hpp"
using namespace std;

//设计演讲管理类
class SpeechManager
{
public:
    SpeechManager();

    //显示菜单
    void showMenu();

    //退出系统
    void exitSystem();

    //初始化比赛信息
    void initSpeech();

    //
    void startSpeech();
    
    //创建12名选手
    void createSpeaker();

    //抽签功能
    void speechDraw();

    //比赛实现
    void speechContest();

    //保存文件
    void saveData();

    //读取文件
    void readRecord();

    //显示获奖记录
    void showRecord();

    //判断文件是否为空的标志
    bool fileIsEmpty;

    map<int,vector<string> > m_Record;

    ~SpeechManager();

    //成员属性
    vector<int> v1;

    vector<int> v2;

    vector<int> victory;

    map<int,Speaker> mSpeakers;

    int mIndex;
};