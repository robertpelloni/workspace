package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;
import com.bobsgame.shared.BobColor;

public class YouWillBeNotifiedState extends State {
	public YouWillBeNotifiedState() {

	}
	
	@Override
	public void update() {

	}

	@Override
	public void render() {
		ClientMain.glowTileBackground.render();

		String text = "To be continued...";

		GLUtils.drawFilledRect(0, 0, 0, 0, LWJGLUtils.SCREEN_SIZE_X, 0, LWJGLUtils.SCREEN_SIZE_Y, 0.5f);
		GLUtils.drawOutlinedString(text, LWJGLUtils.SCREEN_SIZE_X / 2 - GLUtils.font.getWidth(text) / 2, LWJGLUtils.SCREEN_SIZE_Y / 2, BobColor.white);
	}

	@Override
	public void cleanup() {

	}
}
