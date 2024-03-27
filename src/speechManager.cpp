#include "speechManager.h"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric> // 包含accumulate头文件
#include <random>  // 包含random头文件
#include <vector>

using namespace std;
SpeechManager::SpeechManager() {
  // Initialize the speech manager
  cout << "SpeechManager constructor called!" << endl;
  this->initSpeech();
  this->createSpeaker();
  this->loadRecord();
}

SpeechManager::~SpeechManager() {
  // Deconstruct the speech manager
  cout << "SpeechManager destructor called!" << endl;
}

void SpeechManager::showMenu() {
  cout << "******************************************************" << endl;
  cout << "**********  Welcome to the speech contest ************" << endl;
  cout << "**********  1. Start a speech contest ****************" << endl;
  cout << "**********  2. View previous records *****************" << endl;
  cout << "**********  3. Clear game records ********************" << endl;
  cout << "**********  0. Exit the competition program **********" << endl;
  cout << endl;
}

void SpeechManager::exitSystem() {
  cout << "Exiting the competition program..." << endl;
  system("pause");
  exit(0);
}

void SpeechManager::initSpeech() {
  this->v1.clear();
  this->v2.clear();
  this->v3.clear();
  this->m_Speaker.clear();
  this->m_Index = 1;
  this->m_Record.clear();
}

void SpeechManager::createSpeaker() {
  string nameSeed = "ABCDEFGHIJKL";
  for (int i = 0; i < nameSeed.size(); i++) {
    string name = "Speaker ";
    name += nameSeed[i];
    Speaker sp;
    sp.m_Name = name;
    for (int j = 0; j < 2; j++) {
      sp.m_Score[j] = 0;
    }
    this->v1.push_back(i + 10001);
    this->m_Speaker.insert(make_pair(i + 10001, sp));
  }
  cout << "Speaker information has been initialized!" << endl;
  // system("pause");
  // cout << endl;
  // cout << "The current speaker information is as follows:" << endl;
  // for (map<int, Speaker>::iterator it = m_Speaker.begin();
  //      it != m_Speaker.end(); it++) {
  //   cout << "Speaker ID: " << it->first
  //        << " Speaker name: " << it->second.m_Name
  //        << " First round score: " << it->second.m_Score[0]
  //        << " Second round score: " << it->second.m_Score[1] << endl;
  // }
  system("pause");
  cout << endl;
}

void SpeechManager::startSpeech() {
  // 第一轮开始比赛

  // 1、抽签
  this->speechDraw();
  // 2、比赛
  this->speechContest();
  // 3、显示晋级结果
  this->showScore();
  // 第二轮开始比赛
  this->m_Index++;
  // 1、抽签
  this->speechDraw();
  // 2、比赛
  this->speechContest();
  // 3、显示最终结果
  this->showScore();
  // 4、保存分数
  this->saveRecord();

  this->initSpeech();
  this->createSpeaker();
  this->loadRecord();

  cout << "This competition is over!" << endl;
  system("pause");
  system("cls");
}

void SpeechManager::speechDraw() {
  cout << "The drawing process is about to begin!" << endl;
  cout << "---------------------------------" << endl;
  cout << "The first round of the drawing is as follows:" << endl;

  // 创建一个随机数发生器
  random_device rd;
  mt19937 g(rd());

  if (this->m_Index == 1) {
    // 使用shuffle来随机排列vector中的元素
    shuffle(v1.begin(), v1.end(), g);

    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  } else {
    // 第二个向量的处理不需要特定的随机数生成器
    shuffle(v2.begin(), v2.end(), g);

    for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
      cout << *it << " ";
    }
    cout << endl;
  }
  cout << "---------------------------------" << endl;
  system("pause");
}

void SpeechManager::speechContest() {
  cout << "The " << this->m_Index
       << " round of the speech contest is about to begin!" << endl;
  multimap<double, int, greater<double>> groupScore;
  int num = 0;       // 记录人员的次数
  vector<int> v_Src; // 临时容器，存放小组成绩
  if (this->m_Index == 1) {
    v_Src = v1;
  } else {
    v_Src = v2;
  }
  for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
    num++;
    deque<double> d;
    for (int i = 0; i < 10; i++) {
      double score = (rand() % 401 + 600) / 10.f;
      d.push_back(score);
    }
    sort(d.begin(), d.end(), greater<double>());
    d.pop_front();
    d.pop_back();
    double sum = accumulate(d.begin(), d.end(), 0.0f);
    double avg = sum / (double)d.size();
    this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
    groupScore.insert(make_pair(avg, *it));
    if (num % 6 == 0) {
      cout << "The " << num / 6 << " group results are as follows:" << endl;
      for (multimap<double, int, greater<double>>::iterator it =
               groupScore.begin();
           it != groupScore.end(); it++) {
        cout << "Speaker ID: " << it->second << " Score: " << it->first << endl;
      }
      int count = 0;
      for (multimap<double, int, greater<double>>::iterator it =
               groupScore.begin();
           it != groupScore.end() && count < 3; it++, count++) {
        if (this->m_Index == 1) {
          v2.push_back((*it).second);
        } else {
          v3.push_back((*it).second);
        }
      }
      groupScore.clear();
      cout << endl;
    }
  }
  cout << "The " << this->m_Index << " round of the speech contest has ended!"
       << endl;
  system("pause");
}

void SpeechManager::showScore() {
  cout << "The final results are as follows:" << endl;
  vector<int> v;
  if (this->m_Index == 1) {
    v = v2;
  } else {
    v = v3;
  }
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    cout << "Speaker ID: " << *it
         << " First round score: " << this->m_Speaker[*it].m_Score[0]
         << " Second round score: " << this->m_Speaker[*it].m_Score[1] << endl;
  }
  cout << endl;
  system("pause");
  system("cls");
  this->showMenu();
}

void SpeechManager::saveRecord() {
  ofstream ofs;
  ofs.open("speech.csv", ios::out | ios::app);
  for (auto it = v3.begin(); it != v3.end(); it++) {
    ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
  }
  ofs << endl;
  ofs.close();
  cout << "Record has been saved" << endl;
  this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {
  ifstream ifs("speech.csv", ios::in);
  if (!ifs.is_open()) {
    cout << "File does not exist!" << endl;
    this->fileIsEmpty = true;
    ifs.close();
    return;
  }
  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    cout << "File is empty!" << endl;
    this->fileIsEmpty = true;
    ifs.close();
    return;
  }
  this->fileIsEmpty = false;
  ifs.putback(ch);
  string data;
  int index = 0;
  while (ifs >> data) {
    vector<string> v;
    int pos = -1;
    int start = 0;
    while (true) {
      pos = data.find(",", start);
      if (pos == -1) {
        break;
      }
      string temp = data.substr(start, pos - start);
      v.push_back(temp);
      start = pos + 1;
    }
    this->m_Record.insert(make_pair(index, v));
    index++;
  }
  ifs.close();
}

void SpeechManager::showRecord() {
  if (this->fileIsEmpty) {
    cout << "File does not exist or is empty!" << endl;
  } else {
    for (int i = 0; i < this->m_Record.size(); i++) {
      cout << "The " << i + 1 << " round results are as follows:" << endl;
      cout << "First place: Speaker ID: " << this->m_Record[i][0]
           << " Score: " << this->m_Record[i][1] << endl;
      cout << "Second place: Speaker ID: " << this->m_Record[i][2]
           << " Score: " << this->m_Record[i][3] << endl;
      cout << "Third place: Speaker ID: " << this->m_Record[i][4]
           << " Score: " << this->m_Record[i][5] << endl;
      cout << endl;
    }
  }
  system("pause");
  system("cls");
  this->showMenu();
}

void SpeechManager::clearRecord() {
  cout << "Are you sure you want to clear all records? (Y/N)" << endl;
  char c;
  cin >> c;
  if (c != 'Y' && c != 'y') {
    return;
  } else {
    ofstream ofs("speech.csv", ios::trunc);
    ofs.close();
    this->initSpeech();
    this->createSpeaker();
    this->loadRecord();
    cout << "All records have been cleared!" << endl;
  }
}