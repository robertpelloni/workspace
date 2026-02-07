package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.client.Texture;
import com.bobsgame.ClientMain;
import com.bobsgame.client.GLUtils;

public class TitleScreenState extends State {
	public TitleScreenState() {

	}

	int frame = 0;
	int ticks = 0;

	int count = 0;

	public void update() {
		ticks += engineTicksPassed();
		if (ticks > 30) {
			ticks = 0;
			frame++;
			if (frame >= ClientMain.glowTileBackground.glowTileFramesTexture.length) {
				frame = 0;
				count++;
			}
		}

		if (count > 2) {
//			ClientMain.clientMain.createNewAccountState.cancelButton.setEnabled(false);
//			ClientMain.clientMain.createNewAccountState.cancelButton.setVisible(false);
//			ClientMain.clientMain.createNewAccountState.cancelButton.setActivated(true);
			ClientMain.clientMain.stateManager.setState(ClientMain.clientMain.createNewAccountState);
		}
	}

	public void render() {
		Texture t = ClientMain.glowTileBackground.bgScrollTexture;

		Texture over = ClientMain.glowTileBackground.glowTileFramesTexture[frame];

		float screenWidth = LWJGLUtils.SCREEN_SIZE_X;
		float screenHeight = LWJGLUtils.SCREEN_SIZE_Y;

		float scale = 2.0f;

		float x0 = screenWidth / 2 - (t.getImageWidth() * scale) / 2;
		float x1 = x0 + (t.getImageWidth() * scale);

		float y0 = screenHeight / 2 - (t.getImageHeight() * scale) / 2;
		float y1 = y0 + (t.getImageHeight() * scale);

		GLUtils.drawTexture(t, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_NEAREST);
		GLUtils.drawTexture(over, x0, x1, y0, y1, 1.0f, GLUtils.FILTER_NEAREST);
	}
}
