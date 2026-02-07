package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;
import com.bobsgame.shared.BobColor;

public class ServersHaveShutDownState extends State {
	public ServersHaveShutDownState() {

	}

	@Override
	public void update() {

	}

	@Override
	public void render() {
		ClientMain.glowTileBackground.render();

		GLUtils.drawFilledRect(0, 0, 0, 0, LWJGLUtils.SCREEN_SIZE_X, 0, LWJGLUtils.SCREEN_SIZE_Y, 0.5f);
		GLUtils.drawOutlinedString("The servers have shut down for updating.", LWJGLUtils.SCREEN_SIZE_X / 2 - 60, LWJGLUtils.SCREEN_SIZE_Y / 2 - 12, BobColor.white);
		GLUtils.drawOutlinedString("Your progress was saved. Please reload the client.", LWJGLUtils.SCREEN_SIZE_X / 2 - 70, LWJGLUtils.SCREEN_SIZE_Y / 2 + 12, BobColor.gray);
	}

	@Override
	public void cleanup() {

	}
}