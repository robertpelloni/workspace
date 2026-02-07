package com.bobsgame.client.state;

public class State {
	public static long lastTicks = 0; // updated once per frame from main loop
	public static long mainTicksPassed = 0; // updated once per frame from main loop
	public static boolean callNanoTimeForEachCall = false;

	public float engineSpeed = 1.0f;

	public void setEngineSpeed(float f) {
		engineSpeed = f;
	}

	public long engineTicksPassed() {
		if (callNanoTimeForEachCall == true) {
			long ticks = System.nanoTime() / 1000 / 1000;
			return (long) ((ticks - lastTicks) * engineSpeed);
		} else {
			return (long) (mainTicksPassed * engineSpeed);
		}
	}

	public long realWorldTicksPassed() {
		if (callNanoTimeForEachCall == true) {
			long ticks = System.nanoTime() / 1000 / 1000;
			return (ticks - lastTicks);
		} else {
			return mainTicksPassed;
		}
	}

	public void update() {

	}

	public void render() {

	}

	public void cleanup() {

	}
}