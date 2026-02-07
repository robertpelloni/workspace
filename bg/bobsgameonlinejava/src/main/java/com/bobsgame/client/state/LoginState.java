package com.bobsgame.client.state;

import com.bobsgame.client.LWJGLUtils;

import de.matthiasmann.twl.GUI;

public class LoginState extends State {
	public GUI loginScreenGUI = null;
	public LoginScreen loginScreen = null;

	public LoginState() {
		loginScreen = new LoginScreen();

		loginScreenGUI = new GUI(loginScreen, LWJGLUtils.TWLrenderer);
		loginScreenGUI.applyTheme(LWJGLUtils.TWLthemeManager);
	}

	public void update() {
		loginScreen.update();
	}

	public void render() {
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		{
			loginScreen.renderBefore();
			loginScreenGUI.update();
			loginScreen.render();
		}
		//SlickCallable.enterSafeBlock();
	}

	public void cleanup() {
		loginScreenGUI.destroy();
	}
}
