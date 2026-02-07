package com.bobsgame.client.state;

public class StateManager {
	public State currentState;

	public StateManager() {

	}

	public State getState() {
		return currentState;
	}

	public void setState(State s) {
		currentState = s;
	}

	public void update() {
		currentState.update();
	}

	public void render() {
		currentState.render();
	}
}