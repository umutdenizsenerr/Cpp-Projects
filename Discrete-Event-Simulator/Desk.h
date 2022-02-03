using namespace std;

#ifndef DESK_H
#define DESK_H



 class Desk{

public:
	
	Desk(int _idNo,float _deskTime,bool _isAvailable);
	bool operator<(const Desk &other);
	//bool operator=(const Desk &other);
	bool isAvailable;
	float deskTime;
	int idNo;

};
#endif
Desk::Desk(int _idNo,float _deskTime,bool _isAvailable){

this-> isAvailable= _isAvailable;
this-> idNo=_idNo;
this->deskTime=_deskTime;

}
bool Desk::operator<(const Desk& other){
 
 return other.idNo < this->idNo;
//shows priority

}
//bool Desk::operator=(const Desk& other){
// this->deskTime = other.deskTime;
// this->isAvailable = other.isAvailable;}

