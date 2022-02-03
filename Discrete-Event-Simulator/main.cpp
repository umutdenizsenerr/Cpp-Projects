#include "Hacker.h"
#include "Desk.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <vector>
#include <queue>
#include "Event.h"
#include <iomanip>
using namespace std;
struct CompareTime { 
    bool operator()(Event const e1, Event const e2) 
    { 
       if(e1.eventTime-e2.eventTime==0.00000){
       	return e1.hackerId>e2.hackerId;
       }

        return e1.eventTime > e2.eventTime; 

    } 
}; 
struct CompareHacker
{
	    bool operator()(Hacker const *h1, Hacker const *h2) 
    { 
       if(h1->nOfCommits==h2->nOfCommits){
       	if(h1->queueEntranceTime2==h2->queueEntranceTime2){
       	return h1->idNumber>h2->idNumber;
       }
       	else{
       		return h1->queueEntranceTime2>h2->queueEntranceTime2;
       	}
       }
        return h2->nOfCommits > h1->nOfCommits; 
    } 
	
};


int main(int argc, char* argv[]) {

	string infile_name = argv[1];
	
	string outfile_name = argv[2];
 	
 	ifstream infile ;
	
	infile.open(infile_name);
	
	ofstream outfile ;
	
	outfile.open(outfile_name);
	
	string numOfHackers;

	infile>>numOfHackers;

	vector<Hacker*> hackerPtrVector;
	
	
	
	int maxLengthOfStickerQueue=0;
	int maxLengthOfHoodieQueue=0;
	float avgNumOfGifts =0;
	int numOfGifts = 0;
	float waitingTimeStickerQueue=0;
	float waitingTimeHoodieQueue=0;
	float avgWaitingTimeStickerQueue=0;
	float avgWaitingTimeHoodieQueue=0;
	float avgNumOfCommits=0;
	int numOfLengthCommits=0;
	float avgNumOfLengthCommits=0;
	float turnAroundTime = 0;
	float avgTurnAroundTime=0;
	int totalNumOfInvAttempstoStickerQueue = 0;
	int totalNumOfInvAttempstogetGift = 0;
	float totalSeconds = 0;

	int nOfHackers = stoi(numOfHackers);

	//to take hackers from input file
	for(int i = 1 ; i<=nOfHackers ; i++){
		string arrT ;
		infile>> arrT;
		float arrTime = stof(arrT);
		
		Hacker *hacker = new Hacker(i,0,arrTime,false,false,0,0,0,0,0,0,0);
		hackerPtrVector.push_back(hacker);

	}

	priority_queue<Event,vector<Event>,CompareTime> eventsHeap;
	string scodeCommitEvents ;
	infile>> scodeCommitEvents;

	int nOfCommitEvents = stoi(scodeCommitEvents);

//to take commit events from input
	for(int i = 0 ; i< nOfCommitEvents ; i++){
		
		
			string sID, sLengthCommit,sTime ;
			
			infile>>sID>>sLengthCommit>>sTime;

			int idNo = stoi(sID);
			int lengthCommit = stoi(sLengthCommit);
			numOfLengthCommits+=lengthCommit;
			float commitTime = stof(sTime); 

			if(lengthCommit>=20){
			Event newEvent = Event(idNo,commitTime,"Commit");
			eventsHeap.push(newEvent);
		}


	
 }
 

 

string queueEntrance,strNumOfStickerDesks,strNumOfHoodieDesks;

infile>>queueEntrance;

int queueEntranceEvents = stoi(queueEntrance);


//to take sticker queue entrance events
for(int i = 0 ; i<queueEntranceEvents ; i++){
	string idNumberStr, queueEntranceTimeStr;

	infile>>idNumberStr>>queueEntranceTimeStr;

	int idNumber = stoi(idNumberStr);
	float queueEntranceTime = stof(queueEntranceTimeStr);


		
	Event newEvent = Event(idNumber,queueEntranceTime,"stickerQueueEntrance");
	eventsHeap.push(newEvent);

	}

priority_queue <Hacker*,vector<Hacker*>,CompareHacker> hoodieQueue;
queue<Hacker*> stickerQueue;
vector<Desk*> stickerDeskVecPtr;
vector<Desk*> hoodieDeskVecPtr;
	infile>>strNumOfStickerDesks;
	int numOfStickerDesks = stoi(strNumOfStickerDesks);
	
	//to create sticker desks
	for(int i=1 ; i<=numOfStickerDesks ; i++){
		string strStickerDeskTime;
		infile>>strStickerDeskTime;
		float stickerDeskTime = stof(strStickerDeskTime);
		Desk *desk = new Desk (i,stickerDeskTime,true);
		stickerDeskVecPtr.push_back(desk);
	}

	infile>>strNumOfHoodieDesks;
	int numOfHoodieDesks = stoi(strNumOfHoodieDesks);
	
	//to create hoodie desks
	for(int i=1 ; i<=numOfHoodieDesks ; i++){
		string strHoodieDeskTime;
		infile>>strHoodieDeskTime;
		float hoodieDeskTime = stof(strHoodieDeskTime);
		Desk *desk = new Desk (i,hoodieDeskTime,true);
		hoodieDeskVecPtr.push_back(desk);
	
	}

Event lastEvent = Event(0,0,""); //to assign the event that will happen
while(!eventsHeap.empty()){

			Hacker *h = hackerPtrVector[eventsHeap.top().hackerId-1];

				lastEvent=eventsHeap.top();
				if(lastEvent.eventTime-totalSeconds>0.000001){
				totalSeconds=lastEvent.eventTime;}
				eventsHeap.pop();
			if(lastEvent.type=="Commit"){
				h->nOfCommits ++;

				

			}
			else if(lastEvent.type=="stickerQueueEntrance"){
			
								
						if(h->nOfGifts<3&&h->nOfCommits>2){
						
						turnAroundTime-=lastEvent.eventTime;
						
						stickerQueue.push(h);
				
						bool b = true; //to determine whether hacker will wait in  sticker queue or not
						for(Desk *d : stickerDeskVecPtr){
								if(d->isAvailable){
									//if one of the sticker desks is available hacker goes directly to sticker desk
									Event stickerQueueExit = Event(h->idNumber,lastEvent.eventTime,"stickerQueueExit");
									eventsHeap.push(stickerQueueExit);
									b=false;
									break;
								}

						}
							if(b){
								h->queueEntranceTime1=lastEvent.eventTime;
								h->canTake = true; //to determine whether hacker will wait in sticker queue or not
							
								
							}	
	
						}	
						else if(h->nOfCommits<3){
							totalNumOfInvAttempstoStickerQueue++;
						}
						else if(h->nOfGifts>=3){
							totalNumOfInvAttempstogetGift++;
						}
										
				
			}
		else if (lastEvent.type=="stickerQueueExit"){
					
								if(!stickerQueue.empty()){	
									
									for(Desk *d : stickerDeskVecPtr){

										if(d->isAvailable){
									
											d->isAvailable=false;
											d->idNo=stickerQueue.front()->idNumber;
											Event hoodieQueueEntrance = Event(stickerQueue.front()->idNumber,lastEvent.eventTime+d->deskTime,"hoodieQueueEntrance");
											eventsHeap.push(hoodieQueueEntrance);
								if(stickerQueue.size()>maxLengthOfStickerQueue&&stickerQueue.front()->canTake){
									maxLengthOfStickerQueue=stickerQueue.size();
															}
											
											if(stickerQueue.front()->canTake){ 
											stickerQueue.front()->waitingTime+=lastEvent.eventTime-stickerQueue.front()->queueEntranceTime1;
											stickerQueue.front()->canTake=false;
										}
										stickerQueue.pop();
											break;
									}
								
								}		
								
								
							
												
					
									}

		}
		else if(lastEvent.type=="hoodieQueueEntrance"){
		
			for(Desk *sDesk : stickerDeskVecPtr){
							if(h->idNumber==sDesk->idNo){
								sDesk->isAvailable=true;
								if(!stickerQueue.empty()){
								//let first hacker in sticker queue to enter sticker desk
								Event stickQueueEnt = Event(stickerQueue.front()->idNumber,lastEvent.eventTime,"stickerQueueExit");
								eventsHeap.push(stickQueueEnt);
								
								
							
							}
							break;
							}
						}
				
			
				bool a = true; //to determine whether hacker will wait in  hoodie queue or not
				for(Desk *d:hoodieDeskVecPtr){
					
					if(d->isAvailable){
						
							//if one of the desk is available hacker goes directly to hoodie desk
			
							Event hoodieQueueExit = Event(h->idNumber,lastEvent.eventTime,"hoodieQueueExit");
						
							eventsHeap.push(hoodieQueueExit);
						
							a=false;
							break;

					}
				}
				if(a){
							
					h->canTake2=true; //to determine whether hacker will wait in hoodie queue or not
					h->queueEntranceTime2=lastEvent.eventTime;
			
					}
					hoodieQueue.push(h);
				
	}

				else if (lastEvent.type=="hoodieQueueExit"){
						
						
				
								if(!hoodieQueue.empty()){	
									for(Desk *d : hoodieDeskVecPtr){

										if(d->isAvailable){
											d->isAvailable=false;
											d->idNo=hoodieQueue.top()->idNumber;
											
											
											Event hoodieDeskExit = Event(hoodieQueue.top()->idNumber,lastEvent.eventTime+d->deskTime,"hoodieDeskExit");
											
											eventsHeap.push(hoodieDeskExit);
												if(hoodieQueue.size()>maxLengthOfHoodieQueue&&hoodieQueue.top()->canTake2){
														
														maxLengthOfHoodieQueue=hoodieQueue.size();
													}
												if(hoodieQueue.top()->canTake2){

											hoodieQueue.top()->waitingTime2+=lastEvent.eventTime-hoodieQueue.top()->queueEntranceTime2;
											
											hoodieQueue.top()->canTake2=false;
										}

											hoodieQueue.pop();
									
											break;
									}
								
								}						
								
												
					
									}
							}
				else if (lastEvent.type=="hoodieDeskExit"){
							h->nOfGifts++;
							turnAroundTime+=lastEvent.eventTime;
							numOfGifts++;
							for(Desk *sDesk : hoodieDeskVecPtr){
							if(h->idNumber==sDesk->idNo){
								sDesk->isAvailable=true;
								if(!hoodieQueue.empty()){	
								Event hoodieQueueEnt = Event(hoodieQueue.top()->idNumber,lastEvent.eventTime,"hoodieQueueExit"); //let first hacker in hoodie queue to enter hoodie desk
								eventsHeap.push(hoodieQueueEnt);
							
							}
								break;
							}
						}

				}
				
		
	

}
int spentMostTimeID=1 ;
float mostTime = 0;
float leastTime = 99999999;

int spentLeastTimeID=-1;
for(Hacker *h:hackerPtrVector){
	waitingTimeStickerQueue+=h->waitingTime;
	
	waitingTimeHoodieQueue+=h->waitingTime2;

	if(((h->waitingTime+h->waitingTime2)-mostTime)>0.00001){
		
		mostTime=h->waitingTime+h->waitingTime2;
		spentMostTimeID=h->idNumber;

	}
	if(h->nOfGifts==3){
	
	
		if(leastTime-(h->waitingTime+h->waitingTime2)>0.00001){
	
			if(h->waitingTime+h->waitingTime2>=0){
			leastTime=h->waitingTime+h->waitingTime2;

			spentLeastTimeID=h->idNumber;
		}
		}
	}

}
if(leastTime==99999999){
	leastTime=-1;
}

avgTurnAroundTime=(float)turnAroundTime/(float)numOfGifts;
avgNumOfGifts=(float)numOfGifts/(float)nOfHackers;
avgWaitingTimeHoodieQueue=float(waitingTimeHoodieQueue)/(float)numOfGifts;
avgWaitingTimeStickerQueue=(float) waitingTimeStickerQueue/(float)numOfGifts;
avgNumOfCommits=(float) nOfCommitEvents/float(nOfHackers);
avgNumOfLengthCommits=(float) numOfLengthCommits/float(nOfCommitEvents);
outfile<<maxLengthOfStickerQueue<<"\n"<< maxLengthOfHoodieQueue<<"\n"<<fixed<< setprecision(3)<<avgNumOfGifts<<endl;
outfile<<avgWaitingTimeStickerQueue<<"\n"
<<avgWaitingTimeHoodieQueue<<"\n"<<avgNumOfCommits<<"\n"<<avgNumOfLengthCommits<<
"\n"<<avgTurnAroundTime<<"\n"<<totalNumOfInvAttempstoStickerQueue
<<"\n"<<totalNumOfInvAttempstogetGift<<"\n"
<<spentMostTimeID<<" "<<mostTime<<"\n"<<spentLeastTimeID<<" "<<leastTime<<"\n"<<totalSeconds;



hackerPtrVector.clear();
stickerDeskVecPtr.clear();
hoodieDeskVecPtr.clear();






















	infile.close();
	outfile.close();
    return 0;
}