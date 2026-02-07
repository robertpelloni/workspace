package com.bobsgame.client.state;



import com.bobsgame.client.LWJGLUtils;

import de.matthiasmann.twl.GUI;


//=========================================================================================================================
public class CreateNewAccountState extends State
{//=========================================================================================================================


	public CreateNewAccount createNewAccount = null;
	public GUI createNewAccountGUI = null;

	//=========================================================================================================================
	public CreateNewAccountState()
	{//=========================================================================================================================


		createNewAccount = new CreateNewAccount();

		createNewAccountGUI = new GUI(createNewAccount, LWJGLUtils.TWLrenderer);
		createNewAccountGUI.applyTheme(LWJGLUtils.TWLthemeManager);

	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================

		createNewAccount.update();

	}


	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================
		//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
		{
			createNewAccount.renderBefore();
			createNewAccountGUI.update();
			createNewAccount.render();
		}
		//SlickCallable.enterSafeBlock();

	}


	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================
		createNewAccountGUI.destroy();

	}



}
