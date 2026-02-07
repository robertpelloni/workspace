package com.bobsgame.client.engine.game.gui.stuffMenu.subMenus;
import com.bobsgame.client.LWJGLUtils;
import java.util.ArrayList;


import com.bobsgame.client.engine.game.Item;
import com.bobsgame.client.engine.game.gui.stuffMenu.SubPanel;


import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.TextArea;
import de.matthiasmann.twl.textarea.SimpleTextAreaModel;




//=========================================================================================================================
public class ItemsPanel extends SubPanel
{//=========================================================================================================================




	DialogLayout[] itemDialogLayout;

	Group horizontalGroup = null;
	Group verticalGroup = null;




	//=========================================================================================================================
	public ItemsPanel()
	{//=========================================================================================================================

		super();


		horizontalGroup = insideLayout.createParallelGroup();
		verticalGroup = insideLayout.createSequentialGroup();



		//for each item in ItemManager.itemList, make a dialogLayout, fill it with name and description

		//if there are no items, make one that says no items.



		insideLayout.setHorizontalGroup
		(
			horizontalGroup
		);

		insideLayout.setVerticalGroup
		(
			verticalGroup
		);



	}


	//=========================================================================================================================
	public void updateItems()
	{//=========================================================================================================================


		ArrayList<Item> items = new ArrayList<Item>();

		for(int i=0;i<EventManager().itemList.size();i++)
		{
			if(EventManager().itemList.get(i).getHaveItemValue_S()==true)
			{
				items.add(EventManager().itemList.get(i));
			}
		}


		itemDialogLayout = new DialogLayout[items.size()];

		for(int n=0;n<items.size();n++)
		{
			itemDialogLayout[n] = new DialogLayout();
			itemDialogLayout[n].setCanAcceptKeyboardFocus(false);
			itemDialogLayout[n].setTheme("itemBox");


			Item i = items.get(n);
			Label nameLabel = new Label(i.name());
			nameLabel.setCanAcceptKeyboardFocus(false);
			nameLabel.setTheme("itemLabel");


			//Label descriptionLabel = new Label(i.description);
			//descriptionLabel.setCanAcceptKeyboardFocus(false);
			//descriptionLabel.setTheme("");


			SimpleTextAreaModel textAreaModel = new SimpleTextAreaModel();


			TextArea textArea = new TextArea(textAreaModel);
			textArea.setTheme("textarea");

			textArea.setBorderSize(0, 0);
			textArea.setCanAcceptKeyboardFocus(false);

			textAreaModel.setText(i.description(),false);



			itemDialogLayout[n].setHorizontalGroup
			(
				itemDialogLayout[n].createParallelGroup(nameLabel,textArea)
			);

			itemDialogLayout[n].setVerticalGroup
			(
				itemDialogLayout[n].createSequentialGroup(nameLabel,textArea)
			);

		}


		insideLayout.removeAllChildren();

		horizontalGroup = insideLayout.createParallelGroup(itemDialogLayout);
		verticalGroup = insideLayout.createSequentialGroup(itemDialogLayout).addGap();

		insideLayout.setHorizontalGroup
		(
			horizontalGroup
		);

		insideLayout.setVerticalGroup
		(
			verticalGroup
		);


	}




	//=========================================================================================================================
	public void layout()
	{//=========================================================================================================================




		if(itemDialogLayout==null)updateItems();

		for(int i=0;i<itemDialogLayout.length;i++)
		{
			itemDialogLayout[i].setMaxSize((int)((LWJGLUtils.SCREEN_SIZE_X*StuffMenu().subPanelScreenWidthPercent)*0.80f), 500);
		}


		super.layout();

	}

	//=========================================================================================================================
	public void setVisible(boolean b)
	{//=========================================================================================================================

		if(b==true)updateItems();
		super.setVisible(b);




	}






}
