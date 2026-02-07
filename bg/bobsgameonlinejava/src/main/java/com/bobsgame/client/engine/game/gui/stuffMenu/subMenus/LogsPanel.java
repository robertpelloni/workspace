package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;

import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;

import de.matthiasmann.twl.Label;


//=========================================================================================================================
public class LogsPanel extends SubPanel
{//=========================================================================================================================



	//=========================================================================================================================
	public LogsPanel()
	{//=========================================================================================================================

		super();


		//TODO: connect to server and get last x logs






		Label label = new Label("Logs");
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
