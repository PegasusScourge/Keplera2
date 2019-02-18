//Get our header
#include "Maths.h"

/* CODE */
using namespace std;

namespace maths {

	Vector2D::Vector2D() {
		x = 0;
		y = 0;
	}

	/* Stopwatch class definitions */
	void Stopwatch::start(unsigned int duration) {
		tickStart = SDL_GetTicks();
		tickEnd = tickStart + duration;
		running = true;
	}

	unsigned int Stopwatch::getElapsed() {
		if (running)
			return (SDL_GetTicks() - tickStart);
		return -1;
	}

	bool Stopwatch::hasElapsed() {
		if (running && SDL_GetTicks() >= tickEnd)
			return true;
		return false;
	}

	void Stopwatch::stop() {
		running = false;
	}

	/* Timer class definitions */
	void Timer::start() {
		startT = sclk::now();
		running = true;
	}

	unsigned int Timer::getElapsed() {
		if (running)
			return chrono::duration_cast<chrono::nanoseconds>(sclk::now() - startT).count();
		return -1;
	}

	float Timer::getElapsedMillis() {
		return getElapsed() / 1000000.0;
	}

	void Timer::stop() {
		running = false;
	}

	void Timer::restart() {
		this->stop();
		this->start();
	}

	/* Vector class definitions*/
	Vector2D Vector2D::operator+(const Vector2D& param) {
		Vector2D n;
		n.x = x + param.x;
		n.y = y + param.y;
		return n;
	}

	Vector2D Vector2D::operator-(const Vector2D& param) {
		Vector2D n;
		n.x = x - param.x;
		n.y = y - param.y;
		return n;
	}

	Vector2D Vector2D::operator/(const Vector2D& param) {
		Vector2D n;
		n.x = x / param.x;
		n.y = y / param.y;
		return n;
	}

	Vector2D Vector2D::operator*(const Vector2D& param) {
		Vector2D n;
		n.x = x * param.x;
		n.y = y * param.y;
		return n;
	}

	Vector2D Vector2D::operator*(const float& param) {
		Vector2D n;
		n.x = x * param;
		n.y = y * param;
		return n;
	}

	Vector2D Vector2D::operator/(const float& param) {
		Vector2D n;
		n.x = x / param;
		n.y = y / param;
		return n;
	}

	Vector2D Vector2D::operator+(const float& param) {
		Vector2D n;
		n.x = x + param;
		n.y = y + param;
		return n;
	}

	Vector2D Vector2D::operator-(const float& param) {
		Vector2D n;
		n.x = x - param;
		n.y = y - param;
		return n;
	}

	float Vector2D::dot(Vector2D& param) {
		return (x*param.x) + (y*param.y);
	}

	float Vector2D::magnitude() {
		return (float)sqrt(pow(x,2.0) + pow(y,2.0));
	}
}