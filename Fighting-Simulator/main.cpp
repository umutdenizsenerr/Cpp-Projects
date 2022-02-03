#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <vector>
using namespace std;


// to order characters alphabetcally
 void makeAlphabeticOrder(vector<Character*> v1){
	

for (int i = 0 ; i<v1.size()-1 ; i++){
	if(*v1[i+1]<*v1[i]){

		swap(*v1[i],*v1[i+1]);
		i=-1;
	}
		
	

}
 	
 }
 //to find new character instead of dead character
 Character* findNewCharacter(Character* c, vector<Character*> v){

int idx = 0;
int j = 0 ;
for (int i = 0; i < v.size(); ++i)
{
	if((*v[i]).name==(*c).name){
		idx = i;
	}
}
		
		while(((!(*v[idx+j]).isAlive))&&((idx+j)<v.size()-1)){

			 j++;

			} 
			if((*v[idx+j]).isAlive){
				return v[idx+j];
			}
			if(!(*v[idx+j]).isAlive){

				int m = 0;
		while((!(*v[idx-m]).isAlive)&&(idx-m)>-1){
			 m++;

			} 
			return v[idx-m];

 }
}

 bool contains (Character* c , vector<Character*> v){
 	
int a = 0;
 	for(Character* k : v){
 		if(k==c){
 		a++;
 	}
 	

 	}
 	return a>=1;
 }



int main(int argc, char* argv[]) {


	string infile_name = argv[1];
	
	string outfile_name = argv[2];
 	
 	ifstream infile ;
	
	infile.open(infile_name);
	
	ofstream outfile ;
	
	outfile.open(outfile_name);
	
	string MaxRounds ;

	int nOfCasualities = 0; 
	int nOfCom1 = 5;
	int nOfCom2 = 5;
	
	string Winner ="Draw";
	 infile >> MaxRounds ;
	 int nMaxRounds = stoi(MaxRounds);
	
	vector<string> words;
	vector<Character> characterVector;
	string line;
	getline(infile,line);
	
	for(int i = 0 ; i<10 ; i++){
	 	
	 	getline(infile,line);
	 	
	 	istringstream iss(line);
	 	
	 	while(iss){
		string word;

	 	iss>>word;
	 	
	 	words.push_back(word);
	 	if(!iss){
	 		words.clear();
	 	}

	 	}

	 	string name = words[0];
	 	string type = words[1];
	 	int attackP = stoi(words[2]);
	 	int defenseP = stoi(words[3]);
	 	int initialH = stoi (words[4]);
	 	Character char1 = Character(name,type,attackP,defenseP,initialH,nMaxRounds);
	 	characterVector.push_back(char1);
}
vector <Character*> characterVectorPtr;
vector <Character> copyCharacterVector;
//to store their initial order
for(int i = 0 ; i<characterVector.size() ; i++){
copyCharacterVector.push_back(characterVector[i]);

}
// to use pointer
for(int i = 0 ; i<characterVector.size() ; i++){
 characterVectorPtr.push_back(&characterVector[i]);

}
vector <Character*> community1Vec;
vector <Character*> community2Vec;
//to seperate them into 2 community
for(int i = 0 ; i<5 ; i++){
	community1Vec.push_back(characterVectorPtr[i]);
	community2Vec.push_back( characterVectorPtr[i+5]) ;
}

makeAlphabeticOrder(community1Vec);
makeAlphabeticOrder(community2Vec);


bool canAttack = false;
int roundNum = 0; 
bool isFinished = false;
	 while(getline(infile,line)&&!(isFinished)){
	 	roundNum++;

	 	istringstream iss(line);
	 	
	 	while(iss){
		string word;

	 	iss>>word;
	 	words.push_back(word);
	 	if(!iss){
	 		words.clear();
	 	}

	 	
	 }
		string attackerName = words[0];
		string defenderName = words[1];
		string Special = words[2];
		bool ifSpecial;
		Character* lastKilledCom1;
		Character* lastKilledCom2;
		if(Special=="NO-SPECIAL"){
			ifSpecial=false;
		}
		if (Special=="SPECIAL"){
			ifSpecial=true;
		}


		for(Character* attacker : characterVectorPtr){

		
			if((*attacker).name==attackerName){
				bool attMemberCom1 = contains((attacker),community1Vec);
				bool attMemberCom2 = contains((attacker),community2Vec); 

				if(attMemberCom1){
					if(!(*attacker).isAlive){
						attacker = findNewCharacter(attacker,community1Vec);

					}
					canAttack=true;
							if(ifSpecial){

					if((*attacker).type=="Elves"&&(*attacker).nRoundsSinceSpecial>10){
						
						
						for(Character* c : community1Vec){
							if((*c).type == "Hobbit"){
								int health = (*attacker).remainingHealth/2;
								(*c).remainingHealth+=health;
								(*attacker).remainingHealth= health;
								(*attacker).nRoundsSinceSpecial=0;
								
							}

						}
					}
					
					if((*attacker).type=="Wizards"&&nOfCom1!=5&&(*attacker).nRoundsSinceSpecial>50){
						
						(*lastKilledCom1).isAlive=true;
						(*lastKilledCom1).remainingHealth=(*lastKilledCom1).healthHistory[0];
						(*attacker).nRoundsSinceSpecial=0;
						nOfCom1++;
						nOfCasualities--;

					}
				
					
				}
				for(Character* defender : community2Vec){
		

					if((*defender).name==defenderName){
							if(!(*defender).isAlive){
								defender = findNewCharacter(defender,community2Vec);
							}

								int damage = ((*attacker)).attack-(*defender).defense;
								if((*attacker).type=="Dwarfs"&&(*attacker).nRoundsSinceSpecial>20&&ifSpecial){
									damage*=2;
								}
								if(damage>0){
									if((*defender).remainingHealth-damage>0){
									(*defender).remainingHealth-=damage;


												}
									else{
										(*defender).remainingHealth=0;
										
										(*defender).isAlive=false;
										lastKilledCom2 = defender;
										(*lastKilledCom2).nRoundsSinceSpecial=0;
										nOfCom2--;
										nOfCasualities++;
										if((*defender).type=="Hobbit"||nOfCom2==1){
											Winner = "Community-1";
											isFinished=true;
											break;
											}

										}
								}


							}
							}
						}
			if(attMemberCom2&&canAttack){
				if(!(*attacker).isAlive){
						attacker = findNewCharacter(attacker,community2Vec);
						
					}
					if(ifSpecial){

					if((*attacker).type=="Elves"&&(*attacker).nRoundsSinceSpecial>10){
						
						
						for(Character* c : community2Vec){
							if((*c).type == "Hobbit"){
								int health = (*attacker).remainingHealth/2;
								(*c).remainingHealth+=health;
								(*attacker).remainingHealth= health;
								(*attacker).nRoundsSinceSpecial=0;
								
							}

						}
					}
					
					if((*attacker).type=="Wizards"&&nOfCom2!=5&&(*attacker).nRoundsSinceSpecial>50){
				
						(*lastKilledCom2).isAlive=true;
						(*lastKilledCom2).remainingHealth=(*lastKilledCom2).healthHistory[0];
						(*attacker).nRoundsSinceSpecial=0;
						nOfCom2++;
						nOfCasualities--;
					}
					
				}
				for(Character* defender : community1Vec ){
		

					if((*defender).name==defenderName){
							if(!(*defender).isAlive){
								defender = findNewCharacter(defender,community1Vec);
							}
								
								int damage = (*attacker).attack-(*defender).defense;
								if((*attacker).type=="Dwarfs"&&(*attacker).nRoundsSinceSpecial>20&&ifSpecial){
									damage*=2;
								}
								if(damage>0){
									if((*defender).remainingHealth-damage>0){
									(*defender).remainingHealth-=damage;
								

												}
									else{
										(*defender).remainingHealth=0;
										(*defender).isAlive=false;
										lastKilledCom1=defender;
										(*lastKilledCom1).nRoundsSinceSpecial=0;
										nOfCasualities++;
										nOfCom1--;
											if((*defender).type=="Hobbit"||nOfCom1==1){
											Winner = "Community-2";

											isFinished = true;
											break;
											}
											
											}
								}


							}
						}
					}
				}
			}
	
for (int i = 0; i < characterVectorPtr.size(); ++i)

						{
			
					 	(*characterVectorPtr[i]).nRoundsSinceSpecial++;
		(*characterVectorPtr[i]).healthHistory[roundNum]=(*characterVectorPtr[i]).remainingHealth;
			
			}
				}
				

for(int i = 0 ; i<copyCharacterVector.size(); i++){

	for (int j = 0; j <characterVectorPtr.size(); ++j)
	{
		if(copyCharacterVector[i].name == (*characterVectorPtr[j]).name){

		swap(characterVectorPtr[i],characterVectorPtr[j]);
		
	}
		}
}
	 
	 outfile<< Winner <<"\n"<<roundNum<<"\n"<<nOfCasualities<<endl;
	 for (int i = 0; i <characterVectorPtr.size(); ++i)
	 {
	 	outfile<<(*characterVectorPtr[i]).name<<" ";
	 	for (int j = 0; j <=roundNum ; ++j)
	 	{
	 		outfile<<((*characterVectorPtr[i]).healthHistory[j])<<" ";
	 		
	 		
	 	}
	 	outfile<<endl;
	 	 }
	



	characterVectorPtr.clear();
	copyCharacterVector.clear();
	words.clear();
	infile.close();
	outfile.close();

    return 0;
}