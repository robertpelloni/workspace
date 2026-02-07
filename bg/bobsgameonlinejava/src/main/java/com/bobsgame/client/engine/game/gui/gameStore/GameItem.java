package com.bobsgame.client.engine.game.gui.gameStore;



import com.bobsgame.client.LWJGLUtils;

import de.matthiasmann.twl.Button;
import de.matthiasmann.twl.DialogLayout;
import de.matthiasmann.twl.GUI;
import de.matthiasmann.twl.Label;
import de.matthiasmann.twl.TextArea;
import de.matthiasmann.twl.Widget;
import de.matthiasmann.twl.textarea.SimpleTextAreaModel;
import de.matthiasmann.twl.theme.AnimatedImage;


//=========================================================================================================================
public class GameItem extends DialogLayout
{//=========================================================================================================================




	public Label gameTitleLabel = null;

	public TextArea textArea;
	public SimpleTextAreaModel textAreaModel;

	Widget iconWidget;
	AnimatedImage gamePreview;

	DialogLayout thisDialogLayout;

	Button buyButton;
	Label priceLabel;



	//=========================================================================================================================
	public GameItem()
	{//=========================================================================================================================




		setTheme("gameContainerDialogLayout");

		thisDialogLayout = this;



		gameTitleLabel = new Label("Tetrid");
		gameTitleLabel.setCanAcceptKeyboardFocus(false);
		gameTitleLabel.setTheme("gameLabel");

		textAreaModel = new SimpleTextAreaModel();

		textArea = new TextArea(textAreaModel);
		textArea.setCanAcceptKeyboardFocus(false);
		textArea.setTheme("gameTextArea");


		textArea.setBorderSize(0, 0);




		buyButton = new Button("Buy now!");
		buyButton.setCanAcceptKeyboardFocus(false);
		buyButton.setTheme("oppositeThemeButton");

		priceLabel = new Label("$0.99");
		priceLabel.setCanAcceptKeyboardFocus(false);
		priceLabel.setTheme("priceLabel");



		//TODO: need to figure out how to alter the texture this points to. if i use the same size texture for all games it should work fine!


		iconWidget = new Widget()
		{

			public void paint(GUI gui)
			{
				super.paint(gui);

				//this was how i figured out how to force it to animate
				//gamePreview.draw(getAnimationState(),getInnerX(),getInnerY(),128,128);

			}

			public void layout()
			{
				gamePreview = (AnimatedImage)LWJGLUtils.TWLthemeManager.getImage("gamePreviewAnimation");

				//if i set the background image in layout it works, if not it doesn't.
				setBackground(gamePreview);

				setMinSize(200,200);
				setMaxSize(200,200);
				adjustSize();

				//force text area to fit the rest of the width without creating a horizontal scrollbar
				int w = thisDialogLayout.getWidth()-128-165;
				if(w<0)w=128;
				textArea.setMinSize(w, 0);

			}

		};

		iconWidget.setCanAcceptKeyboardFocus(false);
		iconWidget.setTheme("widget");


		setCanAcceptKeyboardFocus(false);
		setHorizontalGroup
		(


			createParallelGroup
			(
					createParallelGroup(gameTitleLabel),
					createSequentialGroup().addWidget(iconWidget).addGap(10).addWidget(textArea),
					createSequentialGroup().addGap().addWidget(priceLabel).addGap(20).addWidget(buyButton)
			)


		);

		setVerticalGroup
		(
				createSequentialGroup(
						createParallelGroup(gameTitleLabel),
						createParallelGroup(iconWidget, textArea),
						createSequentialGroup().addGap(),
						createParallelGroup(priceLabel, buyButton)
						)


		);



	}


	public void setText(String text)
	{
		textAreaModel.setText(text,false);

	}


/*
	public void layout()
	{
		//textArea.setMinSize(512, 512);

		//iconWidget.setMinSize(512, 512);
		//iconWidget.setMaxSize(64,64);
		//iconWidget.setMinSize(64,64);
		//iconWidget.setSize(64,64);
		//iconWidget.adjustSize();



		//textArea.adjustSize();

		//doLayout();

		super.layout();

	}
*/




}
