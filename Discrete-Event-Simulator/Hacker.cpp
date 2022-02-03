#include "Hacker.h"
#include <iostream>
#include <string>
#include <map>
#include <queue>
Hacker::Hacker(int _idNumber, int _nOfCommits,float _arrTime,bool _canTake,bool _canTake2,int _nOfGifts,float _waitingTime,float _waitingTime2,float _turnAroundTime,float _queueEntranceTime1,float _queueEntranceTime2,int _deskID){
	this->deskID = _deskID;
	this->canTake2 = _canTake2;
	this->turnAroundTime=_turnAroundTime;
	this->waitingTime2 = _waitingTime2;
	this->nOfCommits = _nOfCommits;
	this->idNumber = _idNumber;
	this -> arrTime = _arrTime;
	this->canTake=_canTake;
	this->nOfGifts=_nOfGifts;
	this -> waitingTime = _waitingTime;
	this->queueEntranceTime1=_queueEntranceTime1;
	this->queueEntranceTime2=_queueEntranceTime2;

	
}	
bool Hacker::operator<(const Hacker &other) {
	
	return this->nOfCommits<other.nOfCommits;
	

}
bool Hacker::operator==(const Hacker &other) {
	
	return this->nOfCommits==other.nOfCommits;
	

}