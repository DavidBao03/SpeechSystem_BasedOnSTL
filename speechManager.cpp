#include "speechManager.hpp"
#include "speaker.hpp"

SpeechManager::SpeechManager()
{
    this->initSpeech();

    this->createSpeaker();
}

void SpeechManager::showMenu()
{
    cout << "**********************************" << endl; 	
    cout << "**********欢迎参加演讲比赛********" << endl;
    cout << "**********1、开始演讲比赛*********" << endl; 	
    cout << "**********2、查看往届记录*********" << endl;
    cout << "**********3、清空比赛记录*********" << endl; 	
    cout << "**********0、退出系比赛统*********" << endl;
    cout << "**********************************" << endl; 	
    cout << endl;
}

void SpeechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->victory.clear();
    this->mSpeakers.clear();

    this->mIndex = 0;
}

void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for(int i = 0 ; i < 12 ; i++)
    {
        Speaker p;
        p.name = "选手";
        p.name += nameSeed[i];
        
        for(int j = 0 ; j < 2 ; j++)
        {
            p.score[j] = 0;
        }

        v1.push_back(i+10001);

        mSpeakers.insert(make_pair(i+10001,p));
    }
}

void SpeechManager::startSpeech()
{
    this->mIndex++;
    this->speechDraw();
    this->speechContest();
}

void SpeechManager::speechDraw()
{
    if(this->mIndex == 1)
    {
        cout << "第一轮抽签的结果如下： " << endl;

        shuffle(v1.begin(),v1.end(),default_random_engine(time(0)));

        for(vector<int>::iterator it = v1.begin();it!= this->v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "第二轮抽签的结果如下： " << endl;

        shuffle(v2.begin(),v2.end(),default_random_engine(time(0)));

        for(vector<int>::iterator it = v2.begin();it !=v2.end();it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void SpeechManager::speechContest()
{
    cout << "第" << this->mIndex << "轮比赛正式开始" << endl;

    multimap<double,int,greater<double> > groups; //临时小组容器

    vector<int> v_Src; //比赛选手容器

    int num = 0; //记录比赛人员个数

    if(this->mIndex == 1)
    {
        v_Src = v1;
    }
    else
    {
        v_Src.resize(v2.size());
        v_Src = v2;
    }

    for(vector<int>::iterator it = v_Src.begin() ; it != v_Src.end() ; it++)
    {
        num++;

        deque<double> d;

        //打分
        for(int i = 0 ; i < 10 ; i++)
        {
            d.push_back((rand()%401+600)/10.0f);
        }

        sort(d.begin(),d.end(),greater<double>());

        d.pop_front();
        d.pop_back();

        double sum = accumulate(d.begin(),d.end(),0.0f);

        double avg = sum / (double)d.size();

        //cout << "编号： " << *it << " 得分： " << avg << endl;

        this->mSpeakers[*it].score[this->mIndex-1] = avg;

        groups.insert(make_pair(avg,*it));

        if(num % 6 == 0)
        {
            cout << "第" << num/6 <<"小组的成绩如下： " << endl;

            for(multimap<double,int,greater<double> >::iterator itm = groups.begin(); itm != groups.end() ; itm++)
            {
                cout << "编号： " << itm->second << "姓名： " << this->mSpeakers[itm->second].name 
                << "分数： " << itm->first << endl;
            }

            int count = 0;

            if(this->mIndex == 1)
            {
                 cout << "成功晋级的选手是： " << endl;
            }
            else
            {
                cout << "获得冠军，亚军，季军的选手分别是： " << endl;
            }

            for(multimap<double,int,greater<double> >::iterator itm = groups.begin(); itm != groups.end()&&count < 3 ; itm++,count++)
            {
                if(this->mIndex == 1)
                {               
                    cout << "编号： " << itm->second << "姓名： " << this->mSpeakers[itm->second].name 
                    << "分数： " << itm->first << endl;
                    v2.push_back(itm->second);
                }
                else
                {
                    cout << "编号： " << itm->second << "姓名： " << this->mSpeakers[itm->second].name 
                    << "分数： " << itm->first << endl;
                    victory.push_back(itm->second);
                }
            }

            groups.clear();
            this->saveData();
        }
    }
    cout << "第" << this->mIndex << "轮比赛完毕" << endl;
}

void SpeechManager::saveData()
{
    ofstream ofs;
    ofs.open("record.txt",ios::out|ios::app);

    for(vector<int>::iterator it = victory.begin();it != victory.end();it++)
    {
        ofs << *it << " " << mSpeakers[*it].score[1] << endl;
    }

    ofs.close();
}

void SpeechManager::readRecord()
{
    ifstream ifs("record.txt",ios::in);

    if(!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;

    ifs.putback(ch);
    
    string str;

    int index = 0;

    while(ifs >> str)
    {
        vector<string> data;

        for(int i = 0 ; i < 6 ;i++)
        {
            data.push_back(str);
            if(i != 5)
            {
                ifs >> str;
            }
        }    
        this->m_Record.insert(make_pair(index,data));
        index++;
    }  

    ifs.close();
}

void SpeechManager::showRecord()
{
    this->readRecord();
    for(int i = 0;i < this->m_Record.size();i++)
    {
        cout << "第" << (i+1) << "届的冠军，亚军，季军分别为： " << endl;
        cout << "冠军编号： " << this->m_Record[i][0] << " 得分： " << this->m_Record[i][1] << endl;
        cout << "亚军编号： " << this->m_Record[i][2] << " 得分： " << this->m_Record[i][3] << endl;
        cout << "季军编号： " << this->m_Record[i][4] << " 得分： " << this->m_Record[i][5] << endl;
    }
}

void SpeechManager::exitSystem()
{
    system("clear");
    cout << "感谢使用" << endl;
    exit(0);
}

SpeechManager::~SpeechManager()
{

}