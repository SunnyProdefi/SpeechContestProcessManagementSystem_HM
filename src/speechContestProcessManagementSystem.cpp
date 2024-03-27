#include "speechManager.h"
#include <iostream>
using namespace std;

int main() {
  SpeechManager sm;
  int choice = 0;
  while (true) {
    sm.showMenu();
    cout << "Please enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1: // Start a speech contest
      sm.startSpeech();
      break;
    case 2: // View previous records
      sm.showRecord();
      break;
    case 3: // Clear game records
      sm.clearRecord();
      break;
    case 0: // Exit the competition program
      sm.exitSystem();
      break;
    default:
      cout << "Invalid input, please try again!" << endl;
      system("cls");
      break;
    }
  }
  system("pause");
  return 0;
}
