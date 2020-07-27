#include "DataManager.h"
#include <iostream>
#include <ios>
DataManager::DataManager()
{
	std::ifstream file;
	file.open(_scoreFile);
	std::string name;
	int score;
	if (!file)
		std::cout<<"File Unreadable";
	while(file>>name>>score){
		_names.push_back(name);
		_scores.push_back(score);
	}
	file.close();
}

void DataManager::updateHighScores(int score,std::string name){
	int i;
	bool erased=true;
	if(name!="---"){
	for(i=0;i<_names.size();i++){
		if ((score>=_scores[i])&&(erased)){
			_names.insert(_names.begin()+i,name);
			_scores.insert(_scores.begin()+i,score);
			_names.pop_back();
			_scores.pop_back();
			erased=false;
		}
	}
	updateFile();
	
	}

}

void DataManager::updateFile(){
	std::ofstream outFile;
	outFile.open("resources/HighScores.txt",std::ofstream::trunc);
	for(int i=0;i<_names.size();i++){
		if (i==4){
			outFile<<_names[i]<<" "<<_scores[i];
		}else{
			outFile<<_names[i]<<" "<<_scores[i]<<std::endl;
		}
	}
	outFile.close();
}

std::tuple<std::vector <std::string> ,std::vector <int>> DataManager::getScores(){
	return {_names,_scores};
}

DataManager::~DataManager()
{
}

