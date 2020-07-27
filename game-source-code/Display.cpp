#include "Display.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <thread>
#include <chrono>
Display::Display() {
}

Display::Display(int wid, int hght, int blockSize, std::string title): _width(wid), _height(hght), _blockSize(blockSize), _win{sf::VideoMode(wid,hght), title,sf::Style::Titlebar|sf::Style::Resize}
{
}

void Display::RenderSplash(std::shared_ptr<SplashScreen> splash) {
	_win.clear(sf::Color::Black);
	if(!_splashFont.loadFromFile(splash->getFont())) {
		// error handling
	}
	_splashText.setFont(_splashFont);
	_splashText.setFillColor(_splashTextColour);
	_splashText.setCharacterSize(_splashTitleSize);
	_splashText.setString(splash->getTitle());
	_win.draw(_splashText);
	
	_splashText.setFont(_splashFont);
	_splashText.setFillColor(_splashTextColour);
	_splashText.setCharacterSize(_splashTextSize);
	_splashText.setString(splash->getText());
	_win.draw(_splashText);
	_win.display();
}

std::string Display::RenderEndGame(std::shared_ptr<EndGame> endGame, std::shared_ptr<Score> score) {
		bool entering=true;
		EventManager _eventMan;
		std::string name("AAA");
		std::vector<int> position{0,0,0};
		int column=0;
		std::string Possibilities("ABCDEFGHiJKLMNoPqRSTuvWxYz");
		
	
	_win.clear(sf::Color::Black);
	if(!_endFont.loadFromFile(endGame->getFont())) {
		// error handling
	}
	_endText.setFont(_endFont);
	_endText.setCharacterSize(_endTextSize);
	_endText.setString(endGame->getText());
	if(endGame->getText() == "You Win") {
		_endText.setColor(sf::Color::Green);
	

	_endText.setPosition(sf::Vector2f(_width/2 - 70, _height/2 - 150));
	_win.draw(_endText);
	_endText.setString("Your score is: "+std::to_string(score->getScore()));
	_endText.setPosition(sf::Vector2f(_width/2 -150, _height/2 -130));
	_win.draw(_endText);
	_endText.setString("Enter your name:");
		_endText.setPosition(sf::Vector2f(_width/2 -150, _height/2-80));
	_win.draw(_endText);
	_endText.setString(name);
	_endText.setPosition(sf::Vector2f(_width/2 -60, _height/2-50));
	_win.draw(_endText);
	_endText.setString("The left and right arrows change");
	_endText.setPosition(sf::Vector2f(_width/2 -300, _height/2-20));
	_win.draw(_endText);
		_endText.setString("the position selected");
	_endText.setPosition(sf::Vector2f(_width/2 -200, _height/2+10));
	_win.draw(_endText);
	_endText.setString("The up and down arrows change");
	_endText.setPosition(sf::Vector2f(_width/2 -300, _height/2+40));
	_win.draw(_endText);
		_endText.setString("the letter selected");
	_endText.setPosition(sf::Vector2f(_width/2 -200, _height/2+70));
	_win.draw(_endText);
		_endText.setString("The Left control button saves your selection");
	_endText.setPosition(sf::Vector2f(_width/2 -400, _height/2+100));
	_win.draw(_endText);
	_win.display();
		
	while(entering){

				
	if (auto evt = _eventMan.handleInputs(); evt!=Action::None&&entering==true){
	
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			
			switch(evt){
				case Action::Up:
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				position[column]=(position[column]+1)%(Possibilities.size());
				name[column]=Possibilities[position[column]];
				break;
				case Action::Down:
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				if (position[column]>0){
				position[column]-=1;
				}else{
					position[column]=Possibilities.size()-1;
				}
				name[column]=Possibilities[position[column]];
				break;
				case Action::Left:
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				if (column>0){
				column-=1;
				}else{
					column=position.size()-1;
				}
				break;
				case Action::Right:
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				column=(column+1)%(3);
				break;
				case Action::Shoot:
				entering=false;
				break;
				case Action::None:
				break;
				}

		_win.clear(sf::Color::Black);
	for (int i=0;i<3;i++){
	_endText.setString(name[i]);
	_endText.setPosition(sf::Vector2f(_width/2 -60+i*25, _height/2+30));
	if (i==column){
		_endText.setColor(sf::Color::Red);
		_win.draw(_endText);
		_endText.setColor(sf::Color::Green);
	}
	else{
	_win.draw(_endText);
	
	}
	}
	if(!_endFont.loadFromFile(endGame->getFont())) {
		// error handling
	}
	_endText.setFont(_endFont);
	_endText.setCharacterSize(_endTextSize);
	_endText.setString(endGame->getText());
	if(endGame->getText() == "You Win") {
		_endText.setColor(sf::Color::Green);
	}
	else {
		_endText.setColor(sf::Color::Red);
	}
	_endText.setPosition(sf::Vector2f(_width/2 - 70, _height/2 - 70));
	_win.draw(_endText);
	_endText.setString("Your score is: "+std::to_string(score->getScore()));
	_endText.setPosition(sf::Vector2f(_width/2 -150, _height/2 -40));
	_win.draw(_endText);
	_endText.setString("Enter your name:");
		_endText.setPosition(sf::Vector2f(_width/2 -150, _height/2));
	_win.draw(_endText);
		
		_win.display();
		}
				
	}
	
	return name;
	}
	
		else {
		_endText.setColor(sf::Color::Red);
		_endText.setPosition(sf::Vector2f(_width/2 - 70, _height/2 - 70));
		_win.draw(_endText);
		_win.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		return "---";
	}
	
		
}


void Display::setup() {
	_win.clear(sf::Color::Black);
	_textureBCK.loadFromFile(_backFile);
	_background.setTexture(_textureBCK);
	_textureCentiiter.loadFromFile("resources/EvilCenti.png");
	
	_texturePlay.loadFromFile("resources/Shooter_SpriteSheet.png");	
	_spritePlay.setTexture(_texturePlay);
	_textureCenti.loadFromFile("resources/1.png");
	textureHbar.loadFromFile("resources/heart.png");
	_textureMush3.loadFromFile("resources/Mush3.png");
	_textureMush2.loadFromFile("resources/Mush2.png");
	_textureMush1.loadFromFile("resources/Mush1.png");
	_textureLas.loadFromFile("resources/11_fire_spritesheet.png");
	_textureDDT.loadFromFile("resources/power-up.png");
	_textureExplosion.loadFromFile("resources/explosion4.png");
	_win.draw(_background);
	_win.display();
}

void Display::resetScreen() {
	_win.clear(sf::Color::Black);
	_win.draw(_background);
}



bool Display::windowStatus() {
	return _win.isOpen();
}

bool Display::checkEvent() {
	return _win.pollEvent(_event);
}

bool Display::eventClosed() {
	if(_event.type == sf::Event::Closed) {
		return true;
	}
	return false;
}

void Display::closeWindow() {
	_win.close();
}

void Display::display() {
	_win.display();
}

void Display::Render(std::shared_ptr<Entity> ent) {
	switch(ent->getType()) {
		case Type::Play:
			RenderPlayer(ent);
			break;
		case Type::Cent:
			RenderCentipede(ent);
			break;
		case Type::Las:
			RenderLaser(ent);
			break;
		case Type::Mush:
			RenderMushroom(ent);
			break;
		case Type::DDT:
			RenderDDT(ent);
			break;
		case Type::NoType:
			break;
	}
}

void Display::RenderCentipede(std::shared_ptr<Entity> cent) {
	auto cen = *(cent->getCentipede());
	auto head = cen.begin();
	_spriteC.setTexture(_textureCenti);
	sf::Sprite _spriteCH;
	_spriteCH.setTexture(_textureCentiiter);

		sf::IntRect subRect2;
		subRect2.left=14;
		subRect2.top=1;
		subRect2.height=16;
		subRect2.width=20;
		_spriteC.setTextureRect(subRect2);
		_spriteC.setColor(sf::Color::Green);
	for(auto iter = cen.begin()+1; iter != cen.end(); ++iter) {
		_spriteC.setPosition(sf::Vector2f(std::get<0>(iter->getPosit()) * _blockSize, 
				std::get<1>(iter->getPosit()) * _blockSize));
		_win.draw(_spriteC);
	}
	
	
	auto iter = cen.begin();
	auto dir = cent->getDirection();
	
	sf::IntRect subRect3;
	subRect3.left=100;
	subRect3.top=20;
	subRect3.height=360;
	subRect3.width=300;
	_spriteCH.setTextureRect(subRect3);
	_spriteCH.setPosition(std::get<0>(head->getPosit()) * _blockSize,
		std::get<1>(head->getPosit()) * _blockSize);
	_spriteCH.setRotation(270);
	_spriteCH.scale(0.07f,0.07f);

		switch(dir) {
			case Direction::Up:
				// will change later when centipede can move up
				break;
			
			case Direction::Down:
					_spriteCH.setRotation(180);
					_spriteCH.setPosition(std::get<0>(iter->getPosit()) * _blockSize+25,
					std::get<1>(iter->getPosit()) * _blockSize+10);
				break;
				
			case Direction::Left: 
					_spriteCH.setRotation(270);
					_spriteCH.setPosition(std::get<0>(iter->getPosit()) * _blockSize-4,
					std::get<1>(iter->getPosit()) * _blockSize);
					_spriteCH.scale(-1.0f,1.0f);
				break;
				
			case Direction::Right: 
					_spriteCH.setRotation(90);
					_spriteCH.setPosition(std::get<0>(iter->getPosit()) * _blockSize+25,
					std::get<1>(iter->getPosit()) * _blockSize);

				break;
		}
	_win.draw(_spriteCH);
}

void Display::RenderLaser(std::shared_ptr<Entity> las) {
	
	sf::IntRect subRect;
	sf::Sprite _laserSprite;
	_laserSprite.setTexture(_textureLas);
	subRect.left=440;
	subRect.top=300;
	subRect.height=120;
	subRect.width=50;
	_laserSprite.setPosition(sf::Vector2f(std::get<0>(las->getPosition()),std::get<1>(las->getPosition())));
	_laserSprite.scale(0.5f,0.5f);
	_laserSprite.setColor(sf::Color::Red);
	_laserSprite.setTextureRect(subRect);
	_win.draw(_laserSprite);

}

void Display::RenderPlayer(std::shared_ptr<Entity> play) {
	auto _pos = sf::Vector2f(std::get<0>(play->getPosition()),std::get<1>(play->getPosition()));
	sf::IntRect subRect;
	subRect.left=13;
	subRect.top=1;
	subRect.height=20;
	subRect.width=24;
	_spritePlay.setPosition(_pos);
	_spritePlay.setTextureRect(subRect);
	_win.draw(_spritePlay);
	
	RenderHealthBar(play);
	
}
	

void Display::RenderHealthBar(std::shared_ptr<Entity> play){
	if(play->getHealth()==3){
	
	
	sf::Sprite Hbar;
	Hbar.setTexture(textureHbar);
	sf::IntRect subRectHBar;
	subRectHBar.left=0;
	subRectHBar.top=0;
	subRectHBar.height=20;
	subRectHBar.width=17;
	Hbar.setPosition(sf::Vector2f(_width-20,_height-20));
	Hbar.setTextureRect(subRectHBar);
	_win.draw(Hbar);
	Hbar.setPosition(sf::Vector2f(_width-38,_height-20));
	_win.draw(Hbar);
	Hbar.setPosition(sf::Vector2f(_width-56,_height-20));
	_win.draw(Hbar);
	}
	if(play->getHealth()==2){
	sf::Sprite Hbar;
	Hbar.setTexture(textureHbar);
	sf::IntRect subRectHBar;
	subRectHBar.left=0;
	subRectHBar.top=0;
	subRectHBar.height=20;
	subRectHBar.width=17;
	Hbar.setPosition(sf::Vector2f(_width-20,_height-20));
	Hbar.setTextureRect(subRectHBar);
	_win.draw(Hbar);
	Hbar.setPosition(sf::Vector2f(_width-38,_height-20));
	_win.draw(Hbar);
	subRectHBar.left=17*4-3;
	Hbar.setTextureRect(subRectHBar);
	Hbar.setPosition(sf::Vector2f(_width-56,_height-20));
	_win.draw(Hbar);
	}
	if(play->getHealth()==1){
	sf::Sprite Hbar;
	Hbar.setTexture(textureHbar);
	sf::IntRect subRectHBar;
	subRectHBar.left=0;
	subRectHBar.top=0;
	subRectHBar.height=20;
	subRectHBar.width=17;
	Hbar.setPosition(sf::Vector2f(_width-20,_height-20));
	Hbar.setTextureRect(subRectHBar);
	_win.draw(Hbar);
	subRectHBar.left=17*4-3;
	Hbar.setTextureRect(subRectHBar);
	Hbar.setPosition(sf::Vector2f(_width-38,_height-20));
	_win.draw(Hbar);
	Hbar.setPosition(sf::Vector2f(_width-56,_height-20));
	_win.draw(Hbar);
	}
}

void Display::RenderMushroom(std::shared_ptr<Entity> mush) {
	auto health = mush->getHealth();
	auto xPos = std::get<0>(mush->getPosition())*_blockSize;
	auto yPos = std::get<1>(mush->getPosition())*_blockSize;
	sf::Sprite MushroomSprite;
	if (health==4){
		MushroomSprite.setTexture(_textureMush3);
		MushroomSprite.setPosition(sf::Vector2f(xPos,
		yPos));
		MushroomSprite.setScale(0.2f,0.15f);
	}
	if(health==3){
		MushroomSprite.setTexture(_textureMush2);
		MushroomSprite.setPosition(sf::Vector2f(xPos,
		yPos));
		MushroomSprite.setScale(0.2f,0.15f);
	}
	if (health==2){
		MushroomSprite.setTexture(_textureMush1);
		MushroomSprite.setPosition(sf::Vector2f(xPos,
		yPos));
		MushroomSprite.setScale(0.2f,0.15f);
	}
	if (health==1){
		MushroomSprite.setTexture(_textureMush1);
		MushroomSprite.setPosition(sf::Vector2f(xPos,
		yPos));
		MushroomSprite.setScale(0.2f,0.15f);
		MushroomSprite.setColor(sf::Color::Cyan);
	}
	_win.draw(MushroomSprite);
}

void Display::RenderScore(std::shared_ptr<Score> score){
	sf::Text text;
	sf::Font font;
	font.loadFromFile("resources/Starjedi.ttf");
	text.setFont(font);
	text.setCharacterSize(18);
	std::string displayedSCore("Score: ");
	displayedSCore+=std::to_string(score->getScore());
	text.setString(displayedSCore);
	text.setColor(sf::Color::Green);

	text.setPosition(sf::Vector2f(10, _height-30));
	_win.draw(text);
}

void Display::RenderHighScores(std::shared_ptr<DataManager> man){
	sf::Text text;
	sf::Font font;
	_win.clear(sf::Color::Black);
	auto[names,scores]=man->getScores();
	font.loadFromFile("resources/Starjedi.ttf");
	text.setFont(font);
	text.setCharacterSize(18);
	std::string displayedSCore("High Scores: ");
	text.setString(displayedSCore);
	text.setColor(sf::Color::Green);

	text.setPosition(sf::Vector2f(_width/2-70, _height/2-70));
	_win.draw(text);
	
	
	for(int i=0;i<names.size();i++){
		std::string name(names[i]+"    "+std::to_string(scores[i]));
		text.setString(name);
			text.setCharacterSize(18-i*2);
		text.setPosition(sf::Vector2f(_width/2-70, _height/2+(i+1)*25-70));
		_win.draw(text);
	}
	_win.display();
}

void Display::RenderDDT(std::shared_ptr<Entity> ddt){
	sf::Sprite DDT;
	auto _pos = sf::Vector2f(std::get<0>(ddt->getPosition()),std::get<1>(ddt->getPosition()));
	DDT.setPosition(_pos);
	sf::IntRect subRect;
	if (!ddt->hasExploded()){
	DDT.setTexture(_textureDDT);
	sf::IntRect subRect;

	subRect.left=16;
	subRect.top=0;
	subRect.height=16;
	subRect.width=16;
	DDT.setTextureRect(subRect);
	_win.draw(DDT);
	}else{

	DDT.setTexture(_textureExplosion);
	if(ddt->getTime()<2){
//		_pos.x-=20;
		_pos.y+=20;
		DDT.setPosition(_pos);
		subRect.left=2000;
		subRect.top=1100;
		subRect.height=240;
		subRect.width=370;
		DDT.setTextureRect(subRect);
	}
	if(ddt->getTime()<4){
		_pos.x-=45;
		_pos.y-=30;
		DDT.setPosition(_pos);
		subRect.left=3200;
		subRect.top=1650;
		subRect.height=240;
		subRect.width=240;
		DDT.setTextureRect(subRect);
	}else{
		_pos.x-=100;
		_pos.y-=90;
		DDT.setPosition(_pos);
		subRect.left=1000;
		subRect.top=2000;
		subRect.height=400;
		subRect.width=400;
		DDT.setTextureRect(subRect);
	}
	ddt->incrimentTime();
	DDT.scale(0.5f,0.5f);
//	DDT.setTextureRect(subRect);
	_win.draw(DDT);
}

	
	}



