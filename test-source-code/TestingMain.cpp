#include "../game-source-code/Game.h"
#include "../game-source-code/Display.h"
#include "../game-source-code/Centipede.h"
#include "../game-source-code/EventManager.h"
#include "../game-source-code/Player.h"
#include "../game-source-code/DDTBomb.h"
#include "../game-source-code/Score.h"
#include "../game-source-code/DataManager.h"
#include "../game-source-code/Laser.h"
#include "../game-source-code/SplashScreen.h"
#include "../game-source-code/EndGame.h"
#include <windows.h>
#include "../game-source-code/EntityManager.h"
#include "../game-source-code/Entity.h"
#include "../game-source-code/Mushroom.h"
#include "memory"
#include <iostream>
#include <chrono>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


/////////////////////////////////////////////////
///////////// Tests for player class ////////////
/////////////////////////////////////////////////


TEST_CASE("Player's initial position can be set and queried") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto [x,y]=player->getPosition();
	CHECK_EQ(x_Pos,x);
	CHECK_EQ(y_Pos,y);
}

TEST_CASE("Player's position can be changed in both x and y") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto width = 800;
	auto height = 600;
	player->setMovements(1,1);
	player->move(width,height);
	auto [x,y]=player->getPosition();
	CHECK_EQ(x_Pos+1,x);
	CHECK_EQ(y_Pos+1,y);
}

TEST_CASE("Player's position can be changed in x only") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto width = 800;
	auto height = 600;
	player->setMovements(1,0);
	player->move(width,height);
	auto [x,y]=player->getPosition();
	CHECK_EQ(x_Pos+1,x);
	CHECK_EQ(y_Pos,y);
}

TEST_CASE("Player's position can be changed in y only") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto width = 800;
	auto height = 600;
	player->setMovements(0,1);
	player->move(width,height);
	auto [x,y]=player->getPosition();
	CHECK_EQ(x_Pos,x);
	CHECK_EQ(y_Pos+1,y);
}



 TEST_CASE("Player's position can't exceed the player area bounds on the left and bottom") {
 	auto x_Pos=5;
 	auto y_Pos=550;
 	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
 	auto width = 800;
 	auto height = 600;
 	player->setMovements(-10,10);
 	player->move(width,height);
 	auto [x,y]=player->getPosition();
 	CHECK_EQ(x_Pos,x);
 	CHECK_EQ(y_Pos,y);
 }

 TEST_CASE("Player's position can't exceed the player area bounds on the right and top of its playing area") {
 	auto x_Pos=775;
 	auto y_Pos=480;
 	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
 	auto width = 800;
 	auto height = 600;
 	player->setMovements(10,-10);
 	player->move(width,height);
 	auto [x,y]=player->getPosition();
 	CHECK_EQ(x_Pos,x);
 	CHECK_EQ(y_Pos,y);
 }
 
 
 TEST_CASE("Player is initialised with three health points") {
 	auto x_Pos=775;
 	auto y_Pos=480;
 	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
 	CHECK_EQ(3,player->getHealth());
 }



/////////////////////////////////////////////////
//////////// Tests for display class ////////////
/////////////////////////////////////////////////

TEST_CASE("Display opens and it's status can be queried") {
	auto title="Test Display";
	std::unique_ptr<Display>_disp(new Display(800, 600, 16,title));
	CHECK(_disp->windowStatus());
	_disp->closeWindow();
}

TEST_CASE("A closed display can be queried as closed.") {
	auto title="Test Display";
	std::unique_ptr<Display>_disp(new Display(800, 600, 16,title));
	_disp->closeWindow();
	CHECK_FALSE(_disp->windowStatus());
}



/////////////////////////////////////////////////
///////// Tests for event manager class /////////
/////////////////////////////////////////////////

TEST_CASE("Simulate an 'Up arrow key press' ") {
	std::unique_ptr<EventManager> _ev;
	INPUT keyboardInput;
    keyboardInput.type = INPUT_KEYBOARD;
    keyboardInput.ki.wScan = 0; 
    keyboardInput.ki.time = 0;
    keyboardInput.ki.dwExtraInfo = 0;
    keyboardInput.ki.wVk = 0x26; // virtual-key code for the "up" key
    keyboardInput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &keyboardInput, sizeof(INPUT)); //press key
	auto movement=_ev->handleInputs();
    keyboardInput.ki.dwFlags = KEYEVENTF_KEYUP; //  key release
    SendInput(1, &keyboardInput, sizeof(INPUT));
	CHECK_EQ(Action::Up,movement);
	
	}


TEST_CASE("Simulate a 'Right arrow and up arrow key press' ") {
	std::unique_ptr<EventManager> _ev;
	INPUT keyboardInput;
    keyboardInput.type = INPUT_KEYBOARD;
    keyboardInput.ki.wScan = 0; 
    keyboardInput.ki.time = 0;
    keyboardInput.ki.dwExtraInfo = 0;
    keyboardInput.ki.wVk = 0x26; 
    keyboardInput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &keyboardInput, sizeof(INPUT)); //press key
	INPUT keyboardInput2;
	keyboardInput2.type = INPUT_KEYBOARD;
    keyboardInput2.ki.wScan = 0; 
    keyboardInput2.ki.time = 0;
    keyboardInput2.ki.dwExtraInfo = 0;
    keyboardInput2.ki.wVk = 0x27; // virtual-key code for the "Rihgt" key
    keyboardInput2.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &keyboardInput2, sizeof(INPUT)); //press key
	
	auto movement=_ev->handleInputs();
	
    keyboardInput.ki.dwFlags = KEYEVENTF_KEYUP; //  key release
    SendInput(1, &keyboardInput, sizeof(INPUT));
	keyboardInput2.ki.dwFlags = KEYEVENTF_KEYUP; //  key release
    SendInput(1, &keyboardInput2, sizeof(INPUT));
	CHECK_EQ(Action::UpRight,movement);
	
	}
	
TEST_CASE("Simulate a 'Left control button press' to shoot") {
	std::unique_ptr<EventManager> _ev;
	INPUT keyboardInput;
    keyboardInput.type = INPUT_KEYBOARD;
    keyboardInput.ki.wScan = 0; 
    keyboardInput.ki.time = 0;
    keyboardInput.ki.dwExtraInfo = 0;
    keyboardInput.ki.wVk = 0xA2; // virtual-key code for the "up" key
    keyboardInput.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &keyboardInput, sizeof(INPUT)); //press key
	auto movement=_ev->handleInputs();
    keyboardInput.ki.dwFlags = KEYEVENTF_KEYUP; //  key release
    SendInput(1, &keyboardInput, sizeof(INPUT));
	CHECK_EQ(Action::Shoot,movement);
	
	}

/////////////////////////////////////////////////
/////////// Tests for centipede class ///////////
//////////////////////////////////////////////////

TEST_CASE("Centepede Moves across the row initially during one timestep") {
	
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);

	auto cen = *(cent->getCentipede());
	auto head = cen.begin();
	auto initialx=std::get<0>(head->getPosit());
	auto initialy=std::get<1>(head->getPosit());
	cent->setPrevPosition(cent->getPosition());
	cent->move(800,600);	
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	auto Finalx=std::get<0>(head2->getPosit());
	auto Finaly=std::get<1>(head2->getPosit());
	CHECK_EQ(initialx+1,Finalx);
	CHECK_EQ(initialy,Finaly);
}
//
TEST_CASE("Centepede Moves down when it reaches the end of the window") {
	
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto cen = *(cent->getCentipede());
	auto head = cen.begin();
	auto initialy=std::get<1>(head->getPosit());
	cent->setPrevPosition(cent->getPosition());
		for (int i=0;i<60;i++){
	cent->move(800,600);
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	auto Finaly=std::get<1>(head2->getPosit());
	CHECK_EQ(initialy+1,Finaly);
}

TEST_CASE("Centepede Moves left after reaching the end of the window") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto cen = *(cent->getCentipede());
	auto head = cen.begin();
	int initialx;
	auto initialy=std::get<1>(head->getPosit());
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialx=std::get<0>(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	auto Finalx=std::get<0>(head2->getPosit());
	auto Finaly=std::get<1>(head2->getPosit());
	CHECK_EQ(initialy+1,Finaly);
	CHECK_EQ(initialx-1,Finalx);
}

TEST_CASE("A Centipede head can be destroyed when hit resulting in a new Centipede") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto ogCen = *(cent->getCentipede());
	auto ogHead = ogCen.begin();
	auto newCent=cent->destroySegment(1);
	auto cen = *(newCent->getCentipede());
	auto head = cen.begin();
	auto OGHeadX=std::get<0>(ogHead->getPosit());
	auto OGHeadY=std::get<1>(ogHead->getPosit());
	auto NewHeadX=std::get<0>(head->getPosit());
	auto NewHeadY=std::get<1>(head->getPosit());
	CHECK_EQ(NewHeadY,OGHeadY);
	CHECK_EQ(NewHeadX,OGHeadX-2);
}

TEST_CASE("If a Centepede is hit in a middle segment it results in a new centipede being created at the segment preceding the segment hit") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto ogCen = *(cent->getCentipede());
	auto ogHead = ogCen.begin();
	auto newCent=cent->destroySegment(2);
	auto cen = *(newCent->getCentipede());
	auto head = cen.begin();
	auto OGHeadX=std::get<0>(ogHead->getPosit());
	auto OGHeadY=std::get<1>(ogHead->getPosit());
	auto NewHeadX=std::get<0>(head->getPosit());
	auto NewHeadY=std::get<1>(head->getPosit());
	CHECK_EQ(NewHeadY,OGHeadY);
	CHECK_EQ(NewHeadX,OGHeadX-3);
}

TEST_CASE("A Centipede's tail can be hit") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto ogCen = *(cent->getCentipede());
	auto OneBeforetail=ogCen.end()-2;
	auto OGHeadX=std::get<0>(OneBeforetail->getPosit());
	auto OGHeadY=std::get<1>(OneBeforetail->getPosit());
	cent->checkDestroy(0,0);
	auto cen = *(cent->getCentipede());
	auto tailCent = *(cent->getCentipede());
	auto tail=tailCent.end()-1;
	auto NewHeadX=std::get<0>(tail->getPosit());
	auto NewHeadY=std::get<1>(tail->getPosit());
	CHECK_EQ(NewHeadY,OGHeadY);
	CHECK_EQ(NewHeadX,OGHeadX);
}

TEST_CASE("A Centipede consisting of a head is recognised when shot") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 0, 0,-1, Direction::Right, Direction::NoDir);
	CHECK_EQ(-99,cent->checkDestroy(0,0));
}

TEST_CASE("The Centipede segment to be destroyed when hit at a coordinate can be obtained") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	CHECK_EQ(5,cent->checkDestroy(1,0));
}

TEST_CASE("Multiple Centipede segments can be destroyed by a DDTBomb") {
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	auto ogCen = *(cent->getCentipede());
	auto ogHead = ogCen.begin();
	auto newCent=cent->centBlast(0,2);
	auto cen = *(newCent->getCentipede());
	auto head = cen.begin();
	auto OGHeadX=std::get<0>(ogHead->getPosit());
	auto OGHeadY=std::get<1>(ogHead->getPosit());
	auto NewHeadX=std::get<0>(head->getPosit());
	auto NewHeadY=std::get<1>(head->getPosit());
	CHECK_EQ(NewHeadY,OGHeadY);
	CHECK_EQ(NewHeadX,OGHeadX-3);
}

TEST_CASE("A centipedeBlock can be initialised at a position") {
	int x=0;
	int y=0;
	centipedeBlock cent(x,y);
	auto [getX,getY]=cent.getPosit();
	CHECK_EQ(y,getY);
	CHECK_EQ(x,getX);
}

/////////////////////////////////////////////////
////////////// Tests for laser class ////////////
/////////////////////////////////////////////////

TEST_CASE("Laser can be initialised at the position from which it is shot position") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto [x,y]=player->getPosition();
	std::shared_ptr<Entity> laser = std::make_shared<Laser>(x,y);	
	auto [xlas,ylas]=laser->getPosition();
	
	CHECK_EQ(x_Pos,xlas);
	CHECK_EQ(y_Pos,ylas);
}

TEST_CASE("Moves vertically with each timestep") {
	
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto [x,y]=player->getPosition();
	std::shared_ptr<Entity> laser = std::make_shared<Laser>(x,y);	
	laser->move(800,600);
	auto [xlas,ylas]=laser->getPosition();
	CHECK_EQ(x_Pos,xlas);
	CHECK_EQ(y_Pos-16,ylas);
}


TEST_CASE("Moves vertically and consistently during repeated timestep") {
	auto x_Pos=400;
	auto y_Pos=480;
	std::shared_ptr<Entity> player=std::make_shared<Player>(x_Pos,y_Pos);
	auto [x,y]=player->getPosition();
	std::shared_ptr<Entity> laser = std::make_shared<Laser>(x,y);	
	laser->move(800,600);
	laser->move(800,600);
	auto [xlas,ylas]=laser->getPosition();
	CHECK_EQ(x_Pos,xlas);
	CHECK_EQ(y_Pos-16*2,ylas);;
}

//////////////////////////
//////// Mushroom ////////
//////////////////////////

TEST_CASE("Can initialise a mushroom at a position"){
	
	std::shared_ptr<Entity> mushroom=std::make_shared<Mushroom>(20, 0);
	auto [x,y]=mushroom->getPosition();
	CHECK_EQ(x,20);
	CHECK_EQ(y,0);
}

TEST_CASE("Mushroom is initialised with health"){
	
	std::shared_ptr<Entity> mushroom=std::make_shared<Mushroom>(20, 0);
	auto [x,y]=mushroom->getPosition();
	
	CHECK_EQ(mushroom->getHealth(),4);
}


TEST_CASE("Mushroom's health is three and it has zero health after being hit four times'"){
	
	std::shared_ptr<Entity> mushroom=std::make_shared<Mushroom>(20, 0);
	auto [x,y]=mushroom->getPosition();
		for (int i=0;i<4;i++){
		mushroom->decreaseHealth();
	}
	CHECK_EQ(mushroom->getHealth(),0);
}

///////////////////////////////
///// Collision detection /////
//////////////////////////////

TEST_CASE("Collisions between the Centipede and player are detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> player=std::make_shared<Player>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2);
	initialPos2.push_back(player->getPosition());
	initialPos2.push_back(player->getPosition());
	std::unique_ptr<Collision> _colide;
	CHECK(_colide->checkCollision(initialPos2,initialPos1));
}

TEST_CASE("Collisions between the Centipede and player not occupying the same area are not detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> player=std::make_shared<Player>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2-100);
	initialPos2.push_back(player->getPosition());
	initialPos2.push_back(player->getPosition());
	std::unique_ptr<Collision> _colide;
	CHECK_FALSE(_colide->checkCollision(initialPos2,initialPos1));
}

TEST_CASE("Collisions between the Centipede and a Mushroom are detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> mush=std::make_shared<Mushroom>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2);
	initialPos2.push_back(mush->getPosition());
	initialPos2.push_back(mush->getPosition());
	std::unique_ptr<Collision> _colide;
	CHECK(_colide->checkCollision(initialPos2,initialPos1));
}

TEST_CASE("Collisions between the Centipede and a Mushroom not occupying the same area are not detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> mush=std::make_shared<Mushroom>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2-100);
	initialPos2.push_back(mush->getPosition());
	initialPos2.push_back(mush->getPosition());
	std::unique_ptr<Collision> _colide;
	CHECK_FALSE(_colide->checkCollision(initialPos2,initialPos1));
}


TEST_CASE("Collisions between the Centipede and a Laser are detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> las=std::make_shared<Laser>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2+5);
	initialPos2.push_back(las->getPosition());
	las->move(800,600);
	initialPos2.push_back(las->getPosition());
	
	std::get<0>(initialPos1[0])=std::get<0>(initialPos1[0])-20;
	std::get<1>(initialPos1[0])=std::get<1>(initialPos1[0])-15;
	std::get<0>(initialPos1[1])=std::get<0>(initialPos1[1])+20;
	std::get<1>(initialPos1[1])=std::get<1>(initialPos1[1])+15;
	std::unique_ptr<Collision> _colide;
	CHECK(_colide->checkCollision(initialPos2,initialPos1));
}

TEST_CASE("Collisions between the Centipede and a Laser not occupying the same area are not detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	std::shared_ptr<Entity> cent=std::make_shared<Centipede>(0, 0, 6, 0,-1, Direction::Right, Direction::NoDir);
	cent->setPrevPosition(cent->getPosition());
	for (int i=0;i<70;i++){
		cent->move(800,600);
		if (i==68){
			auto cenInt = *(cent->getCentipede());
			auto headInt = cenInt.begin();
			initialPos1.push_back(headInt->getPosit());
		}
	}
	auto cen2 = *(cent->getCentipede());
	auto head2 = cen2.begin();
	initialPos1.push_back(head2->getPosit());
		std::shared_ptr<Entity> las=std::make_shared<Laser>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2-5);
	initialPos2.push_back(las->getPosition());
	las->move(800,600);
	initialPos2.push_back(las->getPosition());
	
	std::get<0>(initialPos1[0])=std::get<0>(initialPos1[0])-20;
	std::get<1>(initialPos1[0])=std::get<1>(initialPos1[0])-15;
	std::get<0>(initialPos1[1])=std::get<0>(initialPos1[1])+20;
	std::get<1>(initialPos1[1])=std::get<1>(initialPos1[1])+15;
	std::unique_ptr<Collision> _colide;
	CHECK_FALSE(_colide->checkCollision(initialPos2,initialPos1));
}


TEST_CASE("Collisions between a DDTBomb and a Laser are detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	DDTBomb ddt(20,25);
	initialPos1.push_back(ddt.getPosition());
	initialPos1.push_back(ddt.getPosition());
	std::shared_ptr<Entity> las=std::make_shared<Laser>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2+5);
	initialPos2.push_back(las->getPosition());
	las->move(800,600);
	initialPos2.push_back(las->getPosition());
	
	std::get<0>(initialPos1[0])=std::get<0>(initialPos1[0])-20;
	std::get<1>(initialPos1[0])=std::get<1>(initialPos1[0])-15;
	std::get<0>(initialPos1[1])=std::get<0>(initialPos1[1])+20;
	std::get<1>(initialPos1[1])=std::get<1>(initialPos1[1])+15;
	std::unique_ptr<Collision> _colide;
	CHECK(_colide->checkCollision(initialPos2,initialPos1));
}



TEST_CASE("Collisions between a DDTBomb and a Laser not occupying the same area are not detected"){
	std::vector<std::tuple<int,int>> initialPos1;
	std::vector<std::tuple<int,int>> initialPos2;
	DDTBomb ddt(20,25);
	initialPos1.push_back(ddt.getPosition());
	initialPos1.push_back(ddt.getPosition());
	std::shared_ptr<Entity> las=std::make_shared<Laser>((std::get<0>(initialPos1[0])+std::get<0>(initialPos1[1]))/2,(std::get<1>(initialPos1[0])+std::get<1>(initialPos1[1]))/2-5);
	initialPos2.push_back(las->getPosition());
	las->move(800,600);
	initialPos2.push_back(las->getPosition());
	
	std::get<0>(initialPos1[0])=std::get<0>(initialPos1[0])-20;
	std::get<1>(initialPos1[0])=std::get<1>(initialPos1[0])-15;
	std::get<0>(initialPos1[1])=std::get<0>(initialPos1[1])+20;
	std::get<1>(initialPos1[1])=std::get<1>(initialPos1[1])+15;
	std::unique_ptr<Collision> _colide;
	CHECK_FALSE(_colide->checkCollision(initialPos2,initialPos1));
}


/////////////////////////////
///////// DDT Bomb //////////
/////////////////////////////

TEST_CASE("A DDT bomb can be initialised at a position"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	auto [x,y]=DDT->getPosition();
	CHECK_EQ(x,xPos);
	CHECK_EQ(y,yPos);
}

TEST_CASE("A DDT bomb's Blast Radius can be queried"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	CHECK_EQ(80,DDT->getBlastRadius());
}

TEST_CASE("A DDT bomb is initialised as not having exploded"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	CHECK_FALSE(DDT->hasExploded());
}

TEST_CASE("A DDT bomb can be set to have exploded"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	DDT->setExploded();
	CHECK(DDT->hasExploded());
}

TEST_CASE("A DDT bomb's explosion animation time rendered can be queried"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	CHECK_EQ(0,DDT->getTime());
}

TEST_CASE("The time rendered for a DDT bomb's explosion animation  can be incremented and queried"){
	int xPos=20;
	int yPos=0;
	std::shared_ptr<Entity> DDT=std::make_shared<DDTBomb>(xPos, yPos);
	DDT->incrimentTime();
	CHECK_EQ(1,DDT->getTime());
}

/////////////////////////////
/////// Score Class /////////
/////////////////////////////

TEST_CASE("The Players score is initialised at zero"){
	Score score;
	
	CHECK_EQ(0,score.getScore());
}

TEST_CASE("The Players score can be incremented by a Mushroom kill"){
	Score score;
	int scoreForKillingMush=10;
	std::vector<entityShot> shot {entityShot::Mush};
	score.updateScore(shot);
	CHECK_EQ(scoreForKillingMush,score.getScore());
}

TEST_CASE("The Players score can be incremented by a Centipede Segment kill"){
	Score score;
	int scoreForKillingCent=25;
	std::vector<entityShot> shot {entityShot::Centi};
	score.updateScore(shot);
	CHECK_EQ(scoreForKillingCent,score.getScore());
}

TEST_CASE("The Players score can be incremented by a DDT kill"){
	Score score;
	int scoreForKillingDDT=5;
	std::vector<entityShot> shot {entityShot::DDT};
	score.updateScore(shot);
	CHECK_EQ(scoreForKillingDDT,score.getScore());
}

TEST_CASE("The Players score is decremented if they are killed"){
	Score score;
	int dyingPenalty=-50;
	std::vector<entityShot> shot {entityShot::Play};
	score.updateScore(shot);
	CHECK_EQ(dyingPenalty,score.getScore());
}

TEST_CASE("Compound scoring for one timestep is possible"){
	Score score;
	int dyingPenalty=-50;
	int scoreForKillingDDT=5;
	int scoreForKillingCent=25;
	int scoreForKillingMush=10;
	auto expected=dyingPenalty+2*scoreForKillingDDT+2*scoreForKillingCent+scoreForKillingMush;
	std::vector<entityShot> shot {entityShot::Play,entityShot::DDT,entityShot::DDT,entityShot::Centi,entityShot::Centi,entityShot::Mush};
	score.updateScore(shot);
	CHECK_EQ(expected,score.getScore());
}

//////////////////////////////
/////// Data Manager /////////
//////////////////////////////

TEST_CASE("A new Highscore can be added"){
	DataManager data;
	auto[namesReset,scoresReset]=data.getScores();
	data.updateHighScores(10000,"Vader");
	auto[names,scores]=data.getScores();
	std::ofstream outFile;
	outFile.open("../executables/resources/HighScores.txt",std::ofstream::trunc);
	for(int i=0;i<namesReset.size();i++){
		if (i==4){
			outFile<<namesReset[i]<<" "<<scoresReset[i];
		}else{
			outFile<<namesReset[i]<<" "<<scoresReset[i]<<std::endl;
		}
	}
	outFile.close();
	CHECK_EQ(10000,scores[0]);
	

}

TEST_CASE("A score that is too low is not added to the high scores"){
	DataManager data;
	auto[namesReset,scoresReset]=data.getScores();
	data.updateHighScores(0,"Jar-Jr");
	auto[names,scores]=data.getScores();
	CHECK(scoresReset[scoresReset.size()]>0);
	
	std::ofstream outFile;
	outFile.open("../executables/resources/HighScores.txt",std::ofstream::trunc);
	for(int i=0;i<namesReset.size();i++){
		if (i==4){
			outFile<<namesReset[i]<<" "<<scoresReset[i];
		}else{
			outFile<<namesReset[i]<<" "<<scoresReset[i]<<std::endl;
		}
	}
	outFile.close();

}

TEST_CASE("A new Highscore can be added in the middle of the highscores"){
	DataManager data;
	auto[names,scores]=data.getScores();
	data.updateHighScores(scores[1]+1,"Yoda");
	auto[namesFinal,scoresFinal]=data.getScores();
	CHECK_EQ(scores[1]+1,scoresFinal[1]);
	CHECK_EQ(scores[1],scoresFinal[2]);
	
	std::ofstream outFile;
	outFile.open("../executables/resources/HighScores.txt",std::ofstream::trunc);
	for(int i=0;i<names.size();i++){
		if (i==4){
			outFile<<names[i]<<" "<<scores[i];
		}else{
			outFile<<names[i]<<" "<<scores[i]<<std::endl;
		}
	}
	outFile.close();
}

////////////////////////////////
///////// Entity Manager ///////
////////////////////////////////

TEST_CASE("Entity manager initialises a vector of movable entities"){
	EntityManager entMan;
	entMan.setup(800,600);
	auto [move,immove]=entMan.getEntities();
	CHECK(move->size()>0);
}

TEST_CASE("Entity manager initialises a random vector of immovable mushroom entities"){
	EntityManager entMan;
	entMan.setup(800,600);
	auto [move,immove]=entMan.getEntities();
	CHECK(immove->size()>0);
}

TEST_CASE("Entity manager initialises a Player,Centipede and Mushroom at startup"){
	EntityManager entMan;
	entMan.setup(800,600);
	bool Play=false;
	bool Cent=false;
	bool mush=false;
	auto entities=entMan.getEntities();
	
for(auto m: *(std::get<0>(entities))) {
		if (m->getType()==Type::Cent)
			Cent=true;
		if (m->getType()==Type::Play)
			Play=true;
	}
	
for(auto m: *(std::get<1>(entities))) {
		if (m->getType()==Type::Mush)
			mush=true;
	}
	
	CHECK(Cent);
	CHECK(mush);
	CHECK(Play);
}

TEST_CASE("Entity manager generates a random mushroom field"){
	EntityManager entMan;
	entMan.setup(800,600);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	EntityManager entMan2;
	entMan2.setup(800,600);
	auto [move1,immove1]=entMan.getEntities();
	auto [move2,immove2]=entMan2.getEntities();
immove1->at(1)->getPosition();
int equalCount=0;
	for(auto  m=0;m<immove1->size();m++) {
		auto mush1Pos=(immove1->at(m)->getPosition());
		auto mush2Pos=(immove2->at(m)->getPosition());
		std::get<0>(mush1Pos);
		if ((std::get<0>(mush1Pos)==std::get<0>(mush2Pos))&&(std::get<1>(mush1Pos)==std::get<1>(mush2Pos))){
			equalCount++;
			}

		}
	CHECK(equalCount==0);
}

TEST_CASE("DDT Bombs are randomly generated at random positions"){
	EntityManager entMan;
	entMan.setup(800,600);
	EntityManager entMan2;
	entMan2.setup(800,600);
	int DDTCount=0;
	int ddtAddCount=0;
	bool sameDDT=false;

	while (DDTCount==0){
		entMan.update(800,600);
		auto [move1,immove1]=entMan.getEntities();
		if ((immove1->at(immove1->size()-1)->getType()==Type::DDT)&&(immove1->at(immove1->size()-2)->getType()==Type::DDT))
			DDTCount=2;
			ddtAddCount++;
			}
	auto [move1,immove1]=entMan.getEntities();
	auto DDT1Pos=(immove1->at(immove1->size()-1)->getPosition());
	auto DDT2Pos=(immove1->at(immove1->size()-2)->getPosition());
		
	if ((std::get<0>(DDT1Pos)==std::get<0>(DDT2Pos))&&(std::get<1>(DDT1Pos)==std::get<1>(DDT2Pos))){
		sameDDT=true;
		}
	CHECK(ddtAddCount>2);
	CHECK_FALSE(sameDDT);
}

TEST_CASE("Entity manager updates the Centipede position with each timestep"){
	EntityManager entMan;
	entMan.setup(800,600);
	bool sameCent=false;
	auto [move1,immove1]=entMan.getEntities();
	auto initialCent=(move1->at(1)->getCentipede());
	auto head = initialCent->begin();
	auto pos1=head->getPosit();
	entMan.update(800,600);
	entMan.update(800,600);
	entMan.update(800,600);
	entMan.update(800,600);
	auto [move2,immove2]=entMan.getEntities();
	auto finalCent=(move2->at(1)->getCentipede());
	auto head2 = finalCent->begin();
	auto pos2=head2->getPosit();

	if ((std::get<0>(pos1)==std::get<0>(pos2))&&(std::get<1>(pos1)==std::get<1>(pos2))){
		sameCent=true;
		}
		
	CHECK_FALSE(sameCent);
}


TEST_CASE("If the player does not move, the centipede will hit the player and decrease it's health after enough time-steps"){
	EntityManager entMan;
	entMan.setup(800,600);
	for(int i=1;i<2000;i++){
		entMan.update(800,600);
			}

	auto [move1,immove1]=entMan.getEntities();
	auto health=(move1->at(0)->getHealth());	
	CHECK(health<3);
}

////////////////////////////////
////////// SplashScreen ////////
////////////////////////////////
TEST_CASE("The splashscreen returns the title"){
	SplashScreen splash(600,800);
	CHECK_EQ(splash.getTitle(),"\t\t\tCentipede Wars ");
	}
	
////////////////////////////////
////////// EndGame test ////////
////////////////////////////////
TEST_CASE("The EndGame class returns the correct text in th event of a win"){
	EndGame end(600,800);
	end.chooseText(true);
	CHECK_EQ(end.getText(),"You Win");
	}
	
TEST_CASE("The EndGame class returns the correct text in th event of a loss"){
	EndGame end(600,800);
	end.chooseText(false);
	CHECK_EQ(end.getText(),"You Lose");
	}