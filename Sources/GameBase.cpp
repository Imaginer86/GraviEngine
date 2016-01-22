//#include "GameBase.h"
//#include <string>
//#include <fstream>

// GameBase::GameBase()
// {
// 
// }
// 
// GameBase::~GameBase()
// {
// 
// }
// 
// void GameBase::Release() /* delete the masses created */
// {
// 
// }
// 
// 
// void GameBase::Init() /* this method will call the init() method of every mass */
// {
// 
// }
// 
// void GameBase::Update(float32 dt)
// {
// 	dt;
// }
// 
// void GameBase::Draw()
// {
// 
// }
// 
// bool GameBase::SaveData()
// {
// 	return true;
// }
// 
// bool GameBase::LoadData(unsigned fileNum)
// {	
// 	gSceneNum = fileNum;
// 
// 	std::string fileNumstr = std::to_string(fileNum);
// 	std::string fileName = "data//data" + fileNumstr + ".dat";
// 	std::ifstream dataFile(fileName, std::ios::in);
// 
// 	if (!dataFile.is_open())
// 		return false;
// 
// 	dataFile.close();
// 	return true;
// }