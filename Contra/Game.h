#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QLabel>

namespace Contra
{
	class Game;
	class Bill;
	enum class GameState { READY, RUNNING, PAUSED, GAME_OVER, GAME_CLEAR, TITLE_SCREEN };
}

class Contra::Game : public QGraphicsView
{
	Q_OBJECT

private:

	// game attributes
	QTimer			_engine;
	GameState		_state;
	QGraphicsScene* _world;
	Bill* _player;
	QRectF			_view_rect;
	int				_view_left_margin;

	// per-frame controls flags
	bool			_left_pressed;
	bool			_right_pressed;
	bool			_down_pressed;
	bool			_jump_pressed;
	bool			_fire_pressed;
	bool            _up_pressed;

	// singleton
	static Game* _uniqueInstance;
	Game();

public:

	static Game* instance();

	// getters / setters
	QGraphicsScene* world() { return _world; }
	QRectF wiewRect() { return _view_rect; }
	Bill* player() { return _player; }
	double aspectRatio() { return 16 * 1.1 / 15; }
	void moveView(QPointF p) { _view_rect.moveTopLeft(p); }
	void setViewLeftMargin(int m) { _view_left_margin = m; }

	// event handlers
	virtual void keyPressEvent(QKeyEvent* e) override;
	virtual void keyReleaseEvent(QKeyEvent* e) override;
	virtual void wheelEvent(QWheelEvent* e) override;
	virtual void resizeEvent(QResizeEvent* event) override;

public slots:

	void reset();
	void welcome();
	void start();
	void nextFrame();
	void togglePause();
	void centerView();
	void restoreDefaultView();
	void gameClear() { _state = GameState::GAME_CLEAR; }
	void gameOver() { _state = GameState::GAME_OVER; }
	void gameEnd();

};