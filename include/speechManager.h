#pragma once
#include "speaker.h"
#include <map>
#include <vector>

using namespace std;
class SpeechManager {
public:
  SpeechManager();

  void showMenu();

  void exitSystem();

  ~SpeechManager();

  void initSpeech();

  void createSpeaker();

  void startSpeech();

  void speechDraw();

  void speechContest();

  void showScore();

  void saveRecord();

  void loadRecord();

  void showRecord();

  void clearRecord();

  vector<int> v1;
  vector<int> v2;
  vector<int> v3;

  map<int, Speaker> m_Speaker;
  int m_Index;

  bool fileIsEmpty;
  map<int, vector<string>> m_Record;
};