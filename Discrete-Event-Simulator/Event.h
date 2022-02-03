#include <string>
#include <map>
#include <queue>
using namespace std;

#ifndef EVENT_H
#define EVENT_H



 class Event{

public:
	
	Event(int _hackerId,float _eventTime,string _type);
	bool operator<(const Event& other);
	string type;

	float eventTime;
	int hackerId;

};
#endif

 Event::Event(int _hackerId,float _eventTime, string _type){
 this->type=_type;

this->eventTime=_eventTime;
this->hackerId=_hackerId;

}
bool Event::operator<(const Event& other){
 
 return other.eventTime < this->eventTime;
//shows priority

}







