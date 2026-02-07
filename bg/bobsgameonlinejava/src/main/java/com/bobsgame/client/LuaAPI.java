package com.bobsgame.client;

import com.bobsgame.client.engine.game.ClientGameEngine;
//import se.krka.kahlua.integration.annotations.LuaMethod;

public class LuaAPI {
	public static ClientGameEngine G = null;

	public LuaAPI(ClientGameEngine g) {
		G = g;
	}

	//@LuaMethod(name = "movePlayer", global = true)
	public void movePlayer(int dir) {
		//player().move(dir);
	}
}