#include <string>
#include <map>
#include <queue>

using namespace std;

#ifndef HACKER_H
#define HACKER_H



class Hacker{

public:
bool canTake,canTake2;
int idNumber, nOfCommits,nOfGifts ;
float arrTime;
float waitingTime;
float waitingTime2,queueEntranceTime1,queueEntranceTime2;
float turnAroundTime;
int deskID;
Hacker(int _idNumber,int _nOfCommits, float _arrTime,bool _canTake,bool _canTake2,int _nOfGifts,float _waitingTime,float _waitingTime2,float _turnAroundTime,float _queueEntranceTime1,float _queueEntranceTime2,int _deskID);
bool operator<(const Hacker &other);
bool operator==(const Hacker &other); 

};




















#endif