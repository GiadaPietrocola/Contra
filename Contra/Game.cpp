#include <QApplication>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QOpenGLWidget>
#include <QGraphicsPixmapItem>
#include "Game.h"
#include "GameConfig.h"
#include "Loader.h"
#include "Bill.h"
#include "Bullet.h"
#include "Sprites.h"
#include "Elements.h"
#include "Sounds.h"

using namespace Contra;

// singleton
Game* Game::_uniqueInstance = 0;
Game* Game::instance()
{
	if (_uniqueInstance == 0)
		_uniqueInstance = new Game();
	return _uniqueInstance;
}

Game::Game() : QGraphicsView()
{
	// setup world
	_world = new QGraphicsScene();
	_world->setSceneRect(0, 0, TILE * 10, TILE * 9-2);
	setScene(_world);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setInteractive(false);

	// setup game engine
	QObject::connect(&_engine, SIGNAL(timeout()), this, SLOT(nextFrame()));
	_engine.setTimerType(Qt::PreciseTimer);
	_engine.setInterval(1000 / FPS);

	// enable OpenGL rendering
	QOpenGLWidget* gl = new QOpenGLWidget();
	setViewport(gl);

	reset();
}

void Game::centerView()
{
	_view_rect.moveLeft(std::max(_view_rect.x(), _player->x() - _view_left_margin));
	setSceneRect(_view_rect);
}

void Game::restoreDefaultView()
{
	_view_rect = QRectF(0, 0, 10 * TILE, 9.2 * TILE);
	_view_left_margin = 4.5 * TILE;
}

void Game::reset()
{
	_state = GameState::READY;
	_engine.stop();
	_world->clear();
	_world->setBackgroundBrush(QBrush(Qt::black));
	_player = 0;
	restoreDefaultView();
	_left_pressed = false;
	_right_pressed = false;
	_jump_pressed = false;
	_fire_pressed = false;
	_down_pressed = false;
	_up_pressed = false;
	Sounds::instance()->stopMusic("GameOver");
	Sounds::instance()->stopMusic("Jungle");
	Sounds::instance()->playMusic("Title", true);
	setSceneRect(QRectF());
	centerOn(0, 0);


	QTimer::singleShot(0, this, &Game::welcome);
}

void Game::welcome()
{
	if (_state == GameState::READY)
	{
		_state = GameState::TITLE_SCREEN;
		_world->clear();
		_engine.start();
		Loader::load(0);
	}
}

void Game::start()
{
	if (_state == GameState::TITLE_SCREEN)
	{
		_state = GameState::RUNNING;
		_world->clear();
		_engine.start();
		_player = Loader::load(1);
		centerView();
		Sounds::instance()->stopMusic("Title");
		Sounds::instance()->playMusic("Jungle", true);
	}

}

void Game::togglePause()
{
	if (_state == GameState::RUNNING)
	{
		Sounds::instance()->stopMusic("Jungle");
		Sounds::instance()->playMusic("Pause", false);
		_engine.stop();
		_state = GameState::PAUSED;
	}
	else if (_state == GameState::PAUSED)
	{
		_engine.start();
		_state = GameState::RUNNING;
		Sounds::instance()->playMusic("Jungle", false);
	}
}

// main game loop
void Game::nextFrame()
{
	if (_state != GameState::RUNNING && _state != GameState::TITLE_SCREEN)
		return;

	if (_state == GameState::RUNNING) {
		if (!_player->isDying()) {
			// process inputs
			if (_up_pressed && _left_pressed && _right_pressed) {
				_player->move(Direction::NONE);
				_player->viewDirection(Direction::UP);
			}
			else if (_left_pressed && _right_pressed) {
				_player->move(Direction::NONE);
			}
			else if (_up_pressed && _down_pressed) {
				_player->viewDirection(Direction::NONE);
			}
			else if (_up_pressed && _right_pressed) {
				_player->move(Direction::RIGHT);
				_player->viewDirection(Direction::UP_RIGHT);
			}
			else if (_up_pressed && _left_pressed) {
				_player->move(Direction::LEFT);
				_player->viewDirection(Direction::UP_LEFT);
			}
			else if (_down_pressed && _right_pressed && !_player->hiding()) {
				_player->move(Direction::RIGHT);
				_player->viewDirection(Direction::DOWN_RIGHT);
				_player->liedown(false);
			}
			else if (_down_pressed && _left_pressed && !_player->hiding()) {
				_player->move(Direction::LEFT);
				_player->viewDirection(Direction::DOWN_LEFT);
				_player->liedown(false);
			}
			else if (_left_pressed) {
				_player->move(Direction::LEFT);
			}
			else if (_right_pressed) {
				_player->move(Direction::RIGHT);
			}
			else if (_up_pressed) {
				_player->viewDirection(Direction::UP);
				_player->move(Direction::NONE);
			}
			else if (_down_pressed && !_jump_pressed){
				_player->liedown(true);
			}
			else if (_down_pressed && _jump_pressed){
				_player->godown();
				_jump_pressed = false;
			}
			else {
				_player->move(Direction::NONE);
				_player->liedown(false);
			}

			if(!player()->isDying()) {
				centerView();
			}

			if (_jump_pressed && !_down_pressed){
				_player->jump();
				_jump_pressed = false;
			}
			else if (_fire_pressed){
				_player->fire();
			}
		}
		else if (!_player->midair())
			_player->move(Direction::NONE);

		// player cannot go back the view's left limit
		if (_player->x() < _view_rect.x()){
			_player->setX(_view_rect.x());
			_player->velClipX(0);
		}
		if (_player->x() > 133*TILE){
			_player->setX(133 * TILE);
			_player->velClipX(0);
		}
		if (_player->isDead() && !_player->isVisible()) {
			gameOver();
		}
		if (_player->getVictory()) {
			gameClear();
		}
		if (_state == GameState::GAME_OVER || _state == GameState::GAME_CLEAR)
			gameEnd();

	}

	// advance game
	for (auto item : _world->items())
	{
		Object* obj = dynamic_cast<Object*>(item);

		if (obj && !obj->isDead()) 
		{
			obj->advance();			 // physics, collision detection and resolution, game logic
			obj->animate();			 // animation
			obj->updateSchedulers(); // game logic
			//obj->paint();			 // graphics, automatically called by Qt
		}
	}

	update();

	FRAME_COUNT++;
}

void Game::keyPressEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	// game controls
	if (e->key() == Qt::Key_S)
		start();
	else if (e->key() == Qt::Key_R)
		reset();
	else if (e->key() == Qt::Key_P)
		togglePause();
	else if (e->key() == Qt::Key_C)
	{
		for (auto item : _world->items())
			if (dynamic_cast<Object*>(item))
				dynamic_cast<Object*>(item)->toggleCollider();
	}
	else if (e->key() == Qt::Key_Minus)
		_engine.setInterval(250);
	else if (e->key() == Qt::Key_Plus)
		_engine.setInterval(1000 / FPS);

	// player controls
	if (_state == GameState::RUNNING && _player)
	{
		if (e->key() == Qt::Key_Left)
			_left_pressed = true;
		else if (e->key() == Qt::Key_Right)
			_right_pressed = true;
		else if (e->key() == Qt::Key_Space)
			_jump_pressed = true;
		else if (e->key() == Qt::Key_Down)
			_down_pressed = true;
		else if (e->key() == Qt::Key_F)
			_fire_pressed = true;
		else if (e->key() == Qt::Key_Up)
			_up_pressed = true;

		// cheats
		else if (e->key() == Qt::Key_I)
			player()->SetInvincible();
	}
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
	if (e->isAutoRepeat())
		return;

	// player controls
	if (_state == GameState::RUNNING && _player)
	{
		if (e->key() == Qt::Key_Left) {
			_left_pressed = false;
			_player->viewDirection(Direction::NONE);
		}
		else if (e->key() == Qt::Key_Right) {
			_right_pressed = false;
			_player->viewDirection(Direction::NONE);
		}
		else if (e->key() == Qt::Key_Space)
			_jump_pressed = false;
		else if (e->key() == Qt::Key_F)
			_fire_pressed = false;
		else if (e->key() == Qt::Key_Down) {
			_down_pressed = false;
			_player->viewDirection(Direction::NONE);
		}
		else if (e->key() == Qt::Key_Up) {
			_up_pressed = false;
			_player->viewDirection(Direction::NONE);
		}
	}
}


void Game::wheelEvent(QWheelEvent* e)
{
	if (e->angleDelta().y() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1, 1 / 1.1);
}

void Game::resizeEvent(QResizeEvent* evt)
{
	fitInView(0, 0, TILE * 10 - 4, TILE * 9.2 - 4);
}

void Game::gameEnd()
{
	if (_state != GameState::GAME_CLEAR && _state != GameState::GAME_OVER)
		return;

	_engine.stop();
	togglePause();

	Sounds::instance()->stopMusic("Jungle");

	if (_state == GameState::GAME_CLEAR)
	{
		Sounds::instance()->stopMusic("Jungle");
		Sounds::instance()->playMusic("Victory", false);
	}
	else {
		Sounds::instance()->playMusic("GameOver", false);
	}
	
	_world->clear();

	QGraphicsPixmapItem* screen = _world->addPixmap(_state == GameState::GAME_CLEAR ? Sprites::instance()->getTexture("game_win_screen") : Sprites::instance()->getTexture("game_over_screen"));
	screen->setY(0);

	setSceneRect(QRectF());
	centerOn(0, 0);

	new Text(std::to_string(player()->Score()));

}