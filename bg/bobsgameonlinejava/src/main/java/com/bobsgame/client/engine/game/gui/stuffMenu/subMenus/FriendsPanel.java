package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;

import de.matthiasmann.twl.Label;

//=========================================================================================================================
public class FriendsPanel extends SubPanel
{//=========================================================================================================================




	//=========================================================================================================================
	public FriendsPanel()
	{//=========================================================================================================================


		super();



		Label label = new Label("Friends");
		label.setCanAcceptKeyboardFocus(false);

		insideLayout.setHorizontalGroup
		(
				insideLayout.createParallelGroup(label)
		);

		insideLayout.setVerticalGroup
		(
				insideLayout.createSequentialGroup(label)
		);


	}





}
