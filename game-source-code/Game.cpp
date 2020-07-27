#include "Game.h"
#include <chrono>
#include <thread>
#include <SFML/Window.hpp>

Game::Game(int width, int height, int blockSize, std::string title): _width(width), _height(height), _blockSize(blockSize), _splash(width, height), _endGame(width, height), _window(width, height, blockSize), _disp(width, height, blockSize, title)
{
}

void Game::setup() {
	_disp.setup();
	
	_entityMan.setup(_width, _height);

	_clock.restart();
	_timer = 0.0f;
	
	// setup initial window and run entity manager setup
	// get entities and call entity render function (pass display reference) to render all to screen
}

void Game::splash() {
	_disp.RenderSplash(std::make_shared<SplashScreen>(_splash));
	while (_disp.windowStatus()) {		
		while(_disp.checkEvent()) {
			_score->updateScore(_entityMan.getEntityshot());
			if (auto evt = _eventMan.handleInputs(); evt == Action::Shoot) {
				return;
			}
			if(auto evt = _eventMan.handleInputs(); evt == Action::Close){
				_disp.closeWindow();
			}
		}
		
		if(_disp.eventClosed()) {
		}
	}
}

void Game::play() {
	while (_disp.windowStatus()) {		
		while(_disp.checkEvent()) {
			_score->updateScore(_entityMan.getEntityshot());
			if (auto evt = _eventMan.handleInputs(); evt != Action::None) {
				_entityMan.handleEvent(evt);
			}
			if(auto evt = _eventMan.handleInputs(); evt == Action::Close){
				_disp.closeWindow();
			}
		}
		
		if(!_end) {
			update();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(500)); //to allow the shoot button to be released
			auto name=_disp.RenderEndGame(std::make_shared<EndGame>(_endGame),_score);
			_dataManager->updateHighScores(_score->getScore(),name);
			_disp.RenderHighScores(_dataManager);
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			_disp.closeWindow(); //window closes once high scores have been viewed
		}
		
		if(_disp.eventClosed()) {
		}
	}
}

void Game::update() {
	
	if(_timer >= _timestep) {
		// get current co-ordinates of everything
		// update everything using entity manager, check centipede wall collide
		// get new co-ordinates of everything
		// check for collision in entity manager using collision class (take appropriate actions using helper functions in entity manager
		
		
		
		//render everything

		renderAll();
		auto horz = std::get<0>(_window.getDimensions());
		auto vert = std::get<1>(_window.getDimensions());
		_entityMan.update(horz, vert);

		// update timer
		if(_entityMan.checkWin()) {
			_end = true;
			_endGame.chooseText(true);
		}
		else if(_entityMan.checkLoss()) {
			_end = true;
			_endGame.chooseText(false);
		}

		_timer -= _timestep;
	}
	resetClock();
}



void Game::resetClock() {
	_timer += _clock.restart().asSeconds();
}

void Game::renderAll() {
	auto entities = _entityMan.getEntities();
	_disp.resetScreen();
	
	for(auto m: *(std::get<0>(entities))) {
		_disp.Render(m);
	}
	for(auto m: *(std::get<1>(entities))) {
		_disp.Render(m);
	}
	
	_disp.RenderScore(_score);

	
	_disp.display();
}
