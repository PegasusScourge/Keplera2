#pragma once

/* INCLUDE */
#include <SDL.h>
#include <chrono>

/* DECLARATIONS */
using namespace std;

namespace maths {

	/* A vector class */
	class Vector2D {
	public:
		float x = 0.0;
		float y = 0.0;

		Vector2D();

		/* Std operator overloads */
		Vector2D operator+(const Vector2D& param);
		Vector2D operator-(const Vector2D& param);
		Vector2D operator/(const Vector2D& param);
		Vector2D operator*(const Vector2D& param);
		Vector2D operator*(const float& param);
		Vector2D operator/(const float& param);
		Vector2D operator-(const float& param);
		Vector2D operator+(const float& param);

		/* Dot product calculation */
		float dot(Vector2D& param);

		/* Get the magnitude */
		float magnitude();
	};

	/* Uses the chrono timing to count in nanoseconds */
	using sclk = chrono::steady_clock;

	class Timer {
		//Private members
		chrono::time_point<sclk> startT;

		bool running = false;

	public:

		/* Starts the timer */
		void start();

		/* Checks the time on the timer (elapsed) */
		unsigned int getElapsed();
		float getElapsedMillis();

		/* Stops the timer */
		void stop();

		/* Restarts the timer */
		void restart();
	};

	/* Uses the SDL timing abilities to run a stopwatch */
	class Stopwatch {
		//Private members
		Uint32 tickStart = 0;
		Uint32 tickEnd = 0;

		bool running = false;

	public:

		/* Start the stopwatch */
		void start(unsigned int);

		/* Checks the time on the stopwatch */
		unsigned int getElapsed();

		/* Checks if the stopwatch has elapsed */
		bool hasElapsed();

		/* Prematurely terminates the stopwatch */
		void stop();
	};

}

