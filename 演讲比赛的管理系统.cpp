#include "speechManager.cpp"

int main()
{
    SpeechManager sm;

    int select = 0;

    while(true)
    {
        sm.showMenu();

        cin >> select;

        cout << endl;

        switch(select)
        {
            case 1://开始比赛
            //测试：
            // for(vector<int>::iterator it = sm.v1.begin();it != sm.v1.end();it++)
            // {
            //     cout << *it <<" "<< endl;
            // }
            sm.startSpeech();
            break;
            case 2://查看记录
            if(sm.fileIsEmpty)
            {
                cout << "文件不存在或为空" << endl;
            }
            else
            {
                sm.showRecord();
            }
            break;
            case 3://清空记录
            break;
            case 0://退出系统
            sm.exitSystem();
            break;
        }
    }
    
    return 0;
}