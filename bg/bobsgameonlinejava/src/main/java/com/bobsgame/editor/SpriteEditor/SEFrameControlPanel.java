package com.bobsgame.editor.SpriteEditor;

import java.awt.BorderLayout;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;

import java.awt.SystemColor;

import java.awt.Transparency;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.image.BufferedImage;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.Timer;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.editor.Project.Sprite.SpritePalette;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.SpriteAnimationSequence;


//===============================================================================================
public class SEFrameControlPanel extends JPanel implements ActionListener, MouseWheelListener, ItemListener, KeyListener, CaretListener
{//===============================================================================================


	public EditorMain E;
	public SpriteEditor SE;
	/*
	public boolean isNPC = false;
	public String displayName = "";
	public boolean hasShadow = false;
	public int hitSizeX=0;
	public int hitSizeY=0;
	public int feetPositionX=0;
	public int feetPositionY=0;
	public int animDirections=0;
	 */




	public JCheckBox
	isNPCCheckbox,

	isKidCheckbox,
	isAdultCheckbox,
	isMaleCheckbox,
	isFemaleCheckbox,
	isCarCheckbox,
	isAnimalCheckbox,

	isDoorCheckbox,
	isItemCheckbox,
	isGameCheckbox,
	forceHQ2XCheckbox,
	hasShadowCheckbox,
	isRandomCheckbox,
	exportMD5Checkbox

	//,
	//showHitBoundsCheckbox,
	//showUtilityOffsetCheckbox
	;

	//public JLabel numFramesText, widthHeightText;


	public JPanel animationPanel;

	//public JPanel numFramesPanel;
	//public JPanel widthHeightPanel;

	private JTextField
	sequenceTextField,
	fpsTextField,
	displayNameText,
	gamePriceText,
	//hitBoxLeftOffsetText,
	//hitBoxRightOffsetText,
	//hitBoxTopOffsetText,
	//hitBoxBottomOffsetText,
	//utilityOffsetXText,
	//utilityOffsetYText,
	frameNameTextField
	;

	public JTextArea itemGameDescriptionText;


	private Timer timer;
	private JButton startAnimatingButton, stopAnimatingButton;

	private BufferedImage sequenceFrameImages[];
	private String parsedSequenceFramesText[];

	private int numParsedFrames;
	private int currentFrame;

	private int Anim_x = 0;
	private int Anim_y = 0;
	private int Anim_zoom = 6;


	protected JButton
	newFrameBefore,
	newFrameAfter,
	duplicateFrame,
	deleteFrame,
	nextFrame,
	previousFrame,
	moveRight,
	moveLeft,
	addEditEventButton;
	;



	protected JLabel frameNumber;
	public SpriteEventEditor spriteEventEditor;
	public SETimelinePanel timelinePanel;
	public SEAnimationListPanel animationListPanel;


	//===============================================================================================
	public SEFrameControlPanel(SpriteEditor se)
	{//===============================================================================================

		SE = se;
		E=se.E;

		setLayout(new BorderLayout());

		spriteEventEditor = new SpriteEventEditor();
		timelinePanel = new SETimelinePanel(se);
		animationListPanel = new SEAnimationListPanel(se);

		JPanel spriteInfoPanel = new JPanel();
		spriteInfoPanel.setLayout(new BoxLayout(spriteInfoPanel,BoxLayout.Y_AXIS));
		spriteInfoPanel.setBorder(EditorMain.border);


//		JPanel showHitBoundsPanel = new JPanel();
//		showHitBoundsPanel.setBackground(Color.DARK_GRAY);
//		JLabel showHitBoundsLabel = new JLabel("Show Hit Box? ", JLabel.RIGHT);
//		showHitBoundsLabel.setForeground(Color.WHITE);
//		showHitBoundsCheckbox = new JCheckBox();
//		showHitBoundsCheckbox.setSelected(true);
//		showHitBoundsCheckbox.addItemListener(this);
//		showHitBoundsPanel.add(showHitBoundsLabel);
//		showHitBoundsPanel.add(showHitBoundsCheckbox);
//		spriteInfoPanel.add(showHitBoundsPanel);
//
//		JPanel showUtilityOffsetPointPanel = new JPanel();
//		showUtilityOffsetPointPanel.setBackground(Color.DARK_GRAY);
//		JLabel showUtilityOffsetPointLabel = new JLabel("Show Utility Offset Point? ", JLabel.RIGHT);
//		showUtilityOffsetPointLabel.setForeground(Color.WHITE);
//		showUtilityOffsetCheckbox = new JCheckBox();
//		showUtilityOffsetCheckbox.setSelected(true);
//		showUtilityOffsetCheckbox.addItemListener(this);
//		showUtilityOffsetPointPanel.add(showUtilityOffsetPointLabel);
//		showUtilityOffsetPointPanel.add(showUtilityOffsetCheckbox);
//		spriteInfoPanel.add(showUtilityOffsetPointPanel);

//		numFramesPanel = new JPanel();
//		numFramesPanel.setBackground(Color.GRAY);
//		JLabel numFramesLabel = new JLabel("Num Frames: ", JLabel.RIGHT);
//		numFramesLabel.setFont(new Font("Arial", Font.BOLD, 12));
//		numFramesText = new JLabel("00000");
//		numFramesText.setFont(new Font("Arial", Font.BOLD, 14));
//		numFramesText.setForeground(Color.GREEN);
//		numFramesPanel.add(numFramesLabel);
//		numFramesPanel.add(numFramesText);
//		spriteInfoPanel.add(numFramesPanel);
//
//		widthHeightPanel = new JPanel();
//		widthHeightPanel.setBackground(Color.GRAY);
//		JLabel widthHeightLabel = new JLabel("Width x Height: ", JLabel.RIGHT);
//		widthHeightLabel.setFont(new Font("Arial", Font.BOLD, 12));
//		widthHeightText = new JLabel("-1");
//		widthHeightText.setFont(new Font("Arial", Font.BOLD, 14));
//		widthHeightText.setForeground(Color.GREEN);
//		widthHeightPanel.add(widthHeightLabel);
//		widthHeightPanel.add(widthHeightText);
//		spriteInfoPanel.add(widthHeightPanel);


		JPanel displayNamePanel = new JPanel();
		displayNamePanel.setLayout(new BoxLayout(displayNamePanel,BoxLayout.Y_AXIS));
		displayNamePanel.setBorder(EditorMain.border);


				JLabel displayNameLabel = new JLabel("Display Name:", JLabel.LEFT);
				displayNameLabel.setFont(new Font("Tahoma", Font.BOLD, 14));
				displayNameText = new JTextField("",20);
				displayNameText.addCaretListener(this);
				displayNameText.setFont(new Font("Tahoma", Font.BOLD, 14));
				displayNamePanel.add(displayNameLabel);
				displayNamePanel.add(displayNameText);
				//displayNamePanel.add(Box.createHorizontalGlue());


		spriteInfoPanel.add(displayNamePanel);






		JPanel itemGamePanel = new JPanel();
		itemGamePanel.setLayout(new BoxLayout(itemGamePanel,BoxLayout.Y_AXIS));
		itemGamePanel.setBorder(EditorMain.border);


			JPanel isItemPanel = new JPanel();
			isItemCheckbox = new JCheckBox("Is Item?");
			isItemCheckbox.addItemListener(this);
			isItemPanel.add(isItemCheckbox);
			isItemPanel.add(Box.createHorizontalGlue());
			itemGamePanel.add(isItemPanel);


			JPanel isGamePanel = new JPanel();
			isGameCheckbox = new JCheckBox("Is Game? (Also Item)");
			isGameCheckbox.addItemListener(this);
			isGamePanel.add(isGameCheckbox);
			isGamePanel.add(Box.createHorizontalGlue());
			itemGamePanel.add(isGamePanel);


			JPanel itemGameDescriptionPanel = new JPanel();
			itemGameDescriptionPanel.setLayout(new BoxLayout(itemGameDescriptionPanel,BoxLayout.Y_AXIS));

				JLabel itemGameDescriptionLabel = new JLabel("Item/Game Description: ", JLabel.LEFT);
				//itemGameDescriptionLabel.setFont(new Font("Arial", Font.BOLD, 11));


				itemGameDescriptionText = new JTextArea();
				itemGameDescriptionText.setLineWrap(true);
				itemGameDescriptionText.setWrapStyleWord(true);
				itemGameDescriptionText.setEditable(true);
				//itemGameDescriptionText.setBackground(new Color(24,24,24));
				//itemGameDescriptionText.setForeground(Color.LIGHT_GRAY);
				itemGameDescriptionText.setFont(new Font("Tahoma", Font.PLAIN, 9));
				itemGameDescriptionText.addCaretListener(this);

				Dimension textBoxSize = new Dimension(300,200);
				itemGameDescriptionText.setSize(textBoxSize);
				itemGameDescriptionText.setPreferredSize(textBoxSize);
				itemGameDescriptionText.setMinimumSize(textBoxSize);
				itemGameDescriptionText.setMaximumSize(textBoxSize);

				itemGameDescriptionPanel.add(itemGameDescriptionLabel);
				itemGameDescriptionPanel.add(itemGameDescriptionText);

			itemGamePanel.add(itemGameDescriptionPanel);



			JPanel gamePricePanel = new JPanel();
			JLabel gamePriceLabel = new JLabel("Game Price: $", JLabel.LEFT);

			gamePriceText = new JTextField("",5);
			gamePriceText.addCaretListener(this);
			gamePricePanel.add(gamePriceLabel);
			gamePricePanel.add(gamePriceText);
			gamePricePanel.add(Box.createHorizontalGlue());

			itemGamePanel.add(gamePricePanel);

		spriteInfoPanel.add(itemGamePanel);

//		JPanel utilityOffsetPanel = new JPanel();
//		utilityOffsetPanel.setBorder(EditorMain.border);
//
//			JPanel utilityOffsetXPanel = new JPanel();
//			JLabel utilityOffsetXLabel = new JLabel("Utility Offset X: ", JLabel.RIGHT);
//			utilityOffsetXText = new JTextField("",3);
//			utilityOffsetXText.addCaretListener(this);
//			utilityOffsetXPanel.add(utilityOffsetXLabel);
//			utilityOffsetXPanel.add(utilityOffsetXText);
//			utilityOffsetPanel.add(utilityOffsetXPanel);
//
//			JPanel utilityOffsetYPanel = new JPanel();
//			utilityOffsetYPanel.setBackground(Color.LIGHT_GRAY);
//			JLabel utilityOffsetYLabel = new JLabel("Utility Offset Y: ", JLabel.RIGHT);
//			utilityOffsetYText = new JTextField("",3);
//			utilityOffsetYText.addCaretListener(this);
//			utilityOffsetYPanel.add(utilityOffsetYLabel);
//			utilityOffsetYPanel.add(utilityOffsetYText);
//			utilityOffsetPanel.add(utilityOffsetYPanel);
//
//		spriteInfoPanel.add(utilityOffsetPanel);





		JPanel npcOptionsPanel = new JPanel();
		npcOptionsPanel.setLayout(new BoxLayout(npcOptionsPanel,BoxLayout.Y_AXIS));
		npcOptionsPanel.setBorder(EditorMain.border);


			JPanel isDoorPanel = new JPanel();
			isDoorCheckbox = new JCheckBox("Is Door? (Name Must Start With Door)");
			isDoorCheckbox.addItemListener(this);
			isDoorPanel.add(isDoorCheckbox);
			isDoorPanel.add(Box.createHorizontalGlue());
			npcOptionsPanel.add(isDoorPanel);


			JPanel isNPCPanel = new JPanel();
			//JLabel isNPCLabel = new JLabel("Is NPC? ", JLabel.RIGHT);
			isNPCCheckbox = new JCheckBox("Is NPC? (Export Persistent MapCharacter, Has Shadow)");
			isNPCCheckbox.addItemListener(this);
			//isNPCPanel.add(isNPCLabel);
			isNPCPanel.add(isNPCCheckbox);
			isNPCPanel.add(Box.createHorizontalGlue());
			npcOptionsPanel.add(isNPCPanel);

			JPanel hasShadowPanel = new JPanel();
			//hasShadowPanel.setBackground(Color.LIGHT_GRAY);
			//JLabel hasShadowLabel = new JLabel("Has Shadow? ", JLabel.RIGHT);
			hasShadowCheckbox = new JCheckBox("Has Shadow?");
			hasShadowCheckbox.addItemListener(this);
			//hasShadowPanel.add(hasShadowLabel);
			hasShadowPanel.add(hasShadowCheckbox);
			hasShadowPanel.add(Box.createHorizontalGlue());
			npcOptionsPanel.add(hasShadowPanel);


			JPanel forceHQ2XPanel = new JPanel();
			forceHQ2XCheckbox = new JCheckBox("Force HQ2X In Client");
			forceHQ2XCheckbox.addItemListener(this);
			forceHQ2XPanel.add(forceHQ2XCheckbox);
			forceHQ2XPanel.add(Box.createHorizontalGlue());
			npcOptionsPanel.add(forceHQ2XPanel);



		spriteInfoPanel.add(npcOptionsPanel);




		JPanel randomOptionsPanel = new JPanel();
		randomOptionsPanel.setLayout(new BoxLayout(randomOptionsPanel,BoxLayout.Y_AXIS));
		randomOptionsPanel.setBorder(EditorMain.border);



			JPanel isRandomPanel = new JPanel();


			isRandomCheckbox = new JCheckBox("Is Random?");
			isRandomCheckbox.addItemListener(this);
			isRandomPanel.add(isRandomCheckbox);
			isRandomPanel.add(Box.createHorizontalGlue());
			randomOptionsPanel.add(isRandomPanel);


			JLabel randomExplanationLabel = new JLabel("(Randoms Use Uniform Colors, Preload MD5)");
			randomExplanationLabel.setFont(new Font("Tahoma",Font.PLAIN,9));
			randomExplanationLabel.setForeground(Color.GRAY);
			randomOptionsPanel.add(randomExplanationLabel);


			randomOptionsPanel.add(new JLabel(""));



			JPanel exportMD5Panel = new JPanel();
			//JLabel exportMD5Label = new JLabel("Export MD5 To Client ", JLabel.RIGHT);
			exportMD5Checkbox = new JCheckBox("Export MD5 To Client (Preload)");
			exportMD5Checkbox.addItemListener(this);
			//exportMD5Panel.add(exportMD5Label);
			exportMD5Panel.add(exportMD5Checkbox);
			exportMD5Panel.add(Box.createHorizontalGlue());
			randomOptionsPanel.add(exportMD5Panel);

		spriteInfoPanel.add(randomOptionsPanel);






		JPanel npcTypePanel = new JPanel();
		npcTypePanel.setLayout(new BoxLayout(npcTypePanel,BoxLayout.Y_AXIS));
		npcTypePanel.setBorder(EditorMain.border);

//			GroupLayout npcTypePanelLayout = new GroupLayout(npcTypePanel);
//			npcTypePanel.setLayout(npcTypePanelLayout);
//
//			npcTypePanelLayout.setAutoCreateGaps(true);
//			npcTypePanelLayout.setAutoCreateContainerGaps(true);

			JPanel isKidPanel = new JPanel();
			//JLabel isKidLabel = new JLabel("Is Kid?", JLabel.RIGHT);
			isKidCheckbox = new JCheckBox("Is Kid?");
			isKidCheckbox.addItemListener(this);
			//isKidPanel.add(isKidLabel);
			isKidPanel.add(isKidCheckbox);
			isKidPanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isKidPanel);

			JPanel isAdultPanel = new JPanel();
			//JLabel isAdultLabel = new JLabel("Is Adult? ", JLabel.RIGHT);
			isAdultCheckbox = new JCheckBox("Is Adult?");
			isAdultCheckbox.addItemListener(this);
			//isAdultPanel.add(isAdultLabel);
			isAdultPanel.add(isAdultCheckbox);
			isAdultPanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isAdultPanel);

			JPanel isMalePanel = new JPanel();
			//JLabel isMaleLabel = new JLabel("Is Male? ", JLabel.RIGHT);
			isMaleCheckbox = new JCheckBox("Is Male?");
			isMaleCheckbox.addItemListener(this);
			//isMalePanel.add(isMaleLabel);
			isMalePanel.add(isMaleCheckbox);
			isMalePanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isMalePanel);

			JPanel isFemalePanel = new JPanel();
			//JLabel isFemaleLabel = new JLabel("Is Female? ", JLabel.RIGHT);
			isFemaleCheckbox = new JCheckBox("Is Female?");
			isFemaleCheckbox.addItemListener(this);
			//isFemalePanel.add(isFemaleLabel);
			isFemalePanel.add(isFemaleCheckbox);
			isFemalePanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isFemalePanel);

			JPanel isCarPanel = new JPanel();
			//JLabel isCarLabel = new JLabel("Is Car? ", JLabel.RIGHT);
			isCarCheckbox = new JCheckBox("Is Car?");
			isCarCheckbox.addItemListener(this);
			//isCarPanel.add(isCarLabel);
			isCarPanel.add(isCarCheckbox);
			isCarPanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isCarPanel);

			JPanel isAnimalPanel = new JPanel();
			//JLabel isAnimalLabel = new JLabel("Is Animal? ", JLabel.RIGHT);
			isAnimalCheckbox = new JCheckBox("Is Animal?");
			isAnimalCheckbox.addItemListener(this);
			//isAnimalPanel.add(isAnimalLabel);
			isAnimalPanel.add(isAnimalCheckbox);
			isAnimalPanel.add(Box.createHorizontalGlue());
			npcTypePanel.add(isAnimalPanel);


//			npcTypePanelLayout.setHorizontalGroup(
//					npcTypePanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING, true)
//					.addComponent(isKidPanel)
//					.addComponent(isAdultPanel)
//					.addComponent(isMalePanel)
//					.addComponent(isFemalePanel)
//					.addComponent(isCarPanel)
//					.addComponent(isAnimalPanel)
//
//					);
//
//			npcTypePanelLayout.setVerticalGroup(
//					npcTypePanelLayout.createSequentialGroup()
//					.addComponent(isKidPanel)
//					.addComponent(isAdultPanel)
//					.addComponent(isMalePanel)
//					.addComponent(isFemalePanel)
//					.addComponent(isCarPanel)
//					.addComponent(isAnimalPanel)
//					);


		spriteInfoPanel.add(npcTypePanel);



		JPanel eventPanel = new JPanel();
		eventPanel.setLayout(new BoxLayout(eventPanel,BoxLayout.Y_AXIS));
		eventPanel.setBorder(EditorMain.border);

			addEditEventButton = new JButton("Add Event To Sprite");
			addEditEventButton.setFont(new Font("Tahoma",Font.PLAIN,16));
			addEditEventButton.setForeground(Color.GRAY);
			addEditEventButton.addActionListener(this);

			eventPanel.add(Box.createHorizontalGlue());
			eventPanel.add(addEditEventButton);
			eventPanel.add(Box.createHorizontalGlue());

			spriteInfoPanel.add(eventPanel);








		/*JPanel animDirectionsPanel = new JPanel();
		animDirectionsPanel.setBackground(Color.LIGHT_GRAY);
		JLabel animDirectionsLabel = new JLabel("Anim Directions: ", JLabel.RIGHT);
		animDirectionsText = new JLabel("-1");
		animDirectionsPanel.add(animDirectionsLabel);
		animDirectionsPanel.add(animDirectionsText);
		topPanel.add(animDirectionsPanel);*/








			JPanel framePanel = new JPanel(new GridLayout(0, 1));




			JPanel frameNamePanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));

			JLabel frameNameLabel = new JLabel("Frame Sequence Name:");
			frameNamePanel.add(frameNameLabel);

			frameNameTextField = new JTextField("",20);
			frameNameTextField.addCaretListener(this);

			frameNameTextField.addKeyListener(this);
			frameNameTextField.setForeground(Color.GRAY);

			frameNamePanel.add(frameNameTextField);
	framePanel.add(frameNamePanel);


				JPanel framePrevNextPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));

				previousFrame = new JButton("[a] Prev");
					previousFrame.setFocusable(false);
					previousFrame.addActionListener(this);
					framePrevNextPanel.add(previousFrame);

					frameNumber = new JLabel("Frame #0");
					framePrevNextPanel.add(frameNumber);

					nextFrame = new JButton("Next [s]");
					nextFrame.setFocusable(false);
					nextFrame.addActionListener(this);
					framePrevNextPanel.add(nextFrame);

			framePanel.add(framePrevNextPanel);







					JLabel hitBoxOffsetLabel = new JLabel("[h] Set HitBox from selection.", JLabel.CENTER);
					hitBoxOffsetLabel.setForeground(Color.GRAY);
			framePanel.add(hitBoxOffsetLabel);

				JLabel utilOffsetLabel = new JLabel("[u] Set Utility Point from selection.", JLabel.CENTER);
				utilOffsetLabel.setForeground(Color.GRAY);
			framePanel.add(utilOffsetLabel);

//					JPanel hitBoxLeftOffsetPanel = new JPanel();
//					JLabel hitBoxLeftOffsetLabel = new JLabel("Sequence HitBox Left Offset: ");
//					hitBoxLeftOffsetText = new JTextField("",3);
//					hitBoxLeftOffsetText.addCaretListener(this);
//					hitBoxLeftOffsetPanel.add(hitBoxLeftOffsetLabel);
//					hitBoxLeftOffsetPanel.add(hitBoxLeftOffsetText);
//			framePanel.add(hitBoxLeftOffsetPanel);
//
//					JPanel hitBoxRightOffsetPanel = new JPanel();
//					hitBoxRightOffsetPanel.setBackground(Color.LIGHT_GRAY);
//					JLabel hitBoxRightOffsetLabel = new JLabel("Sequence HitBox Right Offset: ");
//					hitBoxRightOffsetText = new JTextField("",3);
//					hitBoxRightOffsetText.addCaretListener(this);
//					hitBoxRightOffsetPanel.add(hitBoxRightOffsetLabel);
//					hitBoxRightOffsetPanel.add(hitBoxRightOffsetText);
//			framePanel.add(hitBoxRightOffsetPanel);
//
//					JPanel hitSizeTopPanel = new JPanel();
//					JLabel hitSizeTopLabel = new JLabel("Sequence HitBox Top Offset: ");
//					hitBoxTopOffsetText = new JTextField("",3);
//					hitBoxTopOffsetText.addCaretListener(this);
//					hitSizeTopPanel.add(hitSizeTopLabel);
//					hitSizeTopPanel.add(hitBoxTopOffsetText);
//			framePanel.add(hitSizeTopPanel);
//
//					JPanel hitSizeBottomPanel = new JPanel();
//					hitSizeBottomPanel.setBackground(Color.LIGHT_GRAY);
//					JLabel hitSizeBottomLabel = new JLabel("Sequence HitBox Bottom Offset: ");
//					hitBoxBottomOffsetText = new JTextField("",3);
//					hitBoxBottomOffsetText.addCaretListener(this);
//					hitSizeBottomPanel.add(hitSizeBottomLabel);
//					hitSizeBottomPanel.add(hitBoxBottomOffsetText);
//			framePanel.add(hitSizeBottomPanel);


					JPanel frameDupDelPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));

					duplicateFrame = new JButton("Duplicate");
					duplicateFrame.addActionListener(this);
					frameDupDelPanel.add(duplicateFrame);

					deleteFrame = new JButton("Delete");
					deleteFrame.addActionListener(this);
					frameDupDelPanel.add(deleteFrame);

			framePanel.add(frameDupDelPanel);

				JPanel frameNewPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));

					newFrameBefore = new JButton("<- Insert New");
					newFrameBefore.addActionListener(this);
					frameNewPanel.add(newFrameBefore);

					newFrameAfter = new JButton("Insert New ->");
					newFrameAfter.addActionListener(this);
					frameNewPanel.add(newFrameAfter);

			framePanel.add(frameNewPanel);


				JPanel frameMoveButtonsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));
					moveLeft = new JButton("<- Move Frame");
					moveLeft.addActionListener(this);
					frameMoveButtonsPanel.add(moveLeft);

					moveRight = new JButton("Move Frame ->");
					moveRight.addActionListener(this);
					frameMoveButtonsPanel.add(moveRight);

			framePanel.add(frameMoveButtonsPanel);



			JPanel animControls = new JPanel(new GridLayout(0, 1));


			JLabel sequenceLabel = new JLabel("Anim Sequence i.e. \"0,1,2,1\"");
			animControls.add(sequenceLabel);

				sequenceTextField = new JTextField("0", 8);
				sequenceTextField.addCaretListener(this);

			animControls.add(sequenceTextField);

				JPanel fpsPanel = new JPanel();
					JLabel fpsLabel = new JLabel("FPS: ");

					fpsTextField = new JTextField("10", 2);
					fpsTextField.addCaretListener(this);

				fpsPanel.add(fpsLabel);
				fpsPanel.add(fpsTextField);

				JPanel startStopPanel = new JPanel();
					timer = new Timer(100, this);

					startAnimatingButton = new JButton("Start Anim");
					startAnimatingButton.addActionListener(this);

				startStopPanel.add(startAnimatingButton);

					stopAnimatingButton = new JButton("Stop Anim");
					stopAnimatingButton.addActionListener(this);

				startStopPanel.add(stopAnimatingButton);

			animControls.add(fpsPanel);
			animControls.add(startStopPanel);



		JPanel frameAnimPanel = new JPanel(new BorderLayout());
		frameAnimPanel.setBorder(EditorMain.border);

		frameAnimPanel.add(framePanel, BorderLayout.NORTH);

		JPanel centerInfoPanel = new JPanel(new BorderLayout());
		centerInfoPanel.add(spriteInfoPanel, BorderLayout.CENTER);
		centerInfoPanel.add(animationListPanel, BorderLayout.SOUTH);

		frameAnimPanel.add(centerInfoPanel, BorderLayout.CENTER);
		frameAnimPanel.add(animControls, BorderLayout.SOUTH);


		add(frameAnimPanel, BorderLayout.NORTH);
		//add(spriteInfoPanel, BorderLayout.SOUTH);




		animationPanel = new JPanel()
		{
			public void paint(Graphics G)
			{
				if(sequenceFrameImages != null && sequenceFrameImages[currentFrame] != null)
				{

					int sizex = getSprite().wP();
					int sizey = getSprite().hP();

					G.setColor(Color.BLACK);
					G.fillRect(0, 0, animationPanel.getWidth(), animationPanel.getHeight());
					G.setColor(getSpritePal().getColor(0));
					G.fillRect(Anim_x, Anim_y, (sizex*Anim_zoom), (sizey*Anim_zoom));
					G.drawImage(sequenceFrameImages[currentFrame], Anim_x, Anim_y, Anim_x + (sizex*Anim_zoom), Anim_y + (sizey*Anim_zoom), 0, 0, sizex, sizey, this);
					int loc = sequenceTextField.getText().indexOf(parsedSequenceFramesText[currentFrame]);
					sequenceTextField.select(loc, loc + parsedSequenceFramesText[currentFrame].length());

				}
			}

		};


		animationPanel.setBorder(EditorMain.border);
		//animationPanel.setBackground(Color.BLACK);


		add(animationPanel, BorderLayout.CENTER);
		add(timelinePanel, BorderLayout.SOUTH);




		addMouseWheelListener(this);






	}





	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		if(ae.getSource() == previousFrame)previousFrame();
		else if(ae.getSource() == nextFrame)nextFrame();
		else if(ae.getSource() == newFrameBefore)newFrameBefore();
		else if(ae.getSource() == newFrameAfter)newFrameAfter();
		else if(ae.getSource() == duplicateFrame)duplicateFrame();
		else if(ae.getSource() == deleteFrame)deleteFrame();
		else if(ae.getSource() == moveLeft)moveLeft();
		else if(ae.getSource() == moveRight)moveRight();
		else if(ae.getSource() == timer)
		{
			currentFrame++;
			if(currentFrame == numParsedFrames)
			{
				currentFrame = 0;
			}
			repaint();
		}
		else if(ae.getSource() == startAnimatingButton)
		{

			buildSequence();
			sequenceTextField.setEditable(false);
			timer.start();
		}
		else if(ae.getSource() == stopAnimatingButton)
		{
			timer.stop();
			sequenceTextField.setEditable(true);
		}
		else if(ae.getSource() == addEditEventButton)
		{
			if(getSprite().eventData()==null)
			{

				Event event = new Event(EventData.TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING,getSprite().name(),"","{if(isPlayerTouchingAnyEntityUsingThisSprite() == TRUE){}}");


				getSprite().setEventData(event.getData());

				spriteEventEditor.showSpriteEventEditorWindow();

				addEditEventButton.setForeground(Color.RED);
				addEditEventButton.setBackground(Color.RED);
				addEditEventButton.setText("Edit Sprite Event");
			}
			else
			{
				//Event event = Project.getEventByID(getSprite().eventID);

				spriteEventEditor.showSpriteEventEditorWindow();

			}

		}

	}




	//===============================================================================================
	public void mouseWheelMoved(MouseWheelEvent mwe)
	{//===============================================================================================

		if(mwe.getWheelRotation() > 0)
		{
			Anim_zoom += 1;
		}
		if(mwe.getWheelRotation() < 0)
		{
			Anim_zoom -= 1;
		}
	}

	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================



		if(ie.getSource() == isDoorCheckbox)
		{
			//update the selected sprite info
			getSprite().setIsDoor(isDoorCheckbox.isSelected());


			if(isDoorCheckbox.isSelected()==true)
			{
				exportMD5Checkbox.setSelected(true);
				isNPCCheckbox.setSelected(false);
				isRandomCheckbox.setSelected(false);
				hasShadowCheckbox.setSelected(false);
				if(getSprite().name().startsWith("Door")==false)getSprite().setName("Door"+getSprite().name());
			}
		}
		else
		if(ie.getSource() == isNPCCheckbox)
		{
			//update the selected sprite info
			getSprite().setIsNPC(isNPCCheckbox.isSelected());

			//all npcs should have shadows
			if(isNPCCheckbox.isSelected()==true)hasShadowCheckbox.setSelected(true);
		}
		else
		if(ie.getSource() == hasShadowCheckbox)
		{
			getSprite().setHasShadow(hasShadowCheckbox.isSelected());
		}
		else
		if(ie.getSource() == isKidCheckbox)getSprite().setIsKid(isKidCheckbox.isSelected());
		else
		if(ie.getSource() == isAdultCheckbox)getSprite().setIsAdult(isAdultCheckbox.isSelected());
		else
		if(ie.getSource() == isMaleCheckbox)getSprite().setIsMale(isMaleCheckbox.isSelected());
		else
		if(ie.getSource() == isFemaleCheckbox)getSprite().setIsFemale(isFemaleCheckbox.isSelected());
		else
		if(ie.getSource() == isCarCheckbox)
		{
			getSprite().setIsCar(isCarCheckbox.isSelected());

			if(isCarCheckbox.isSelected()==true)forceHQ2XCheckbox.setSelected(true);
		}
		else
		if(ie.getSource() == isAnimalCheckbox)getSprite().setIsAnimal(isAnimalCheckbox.isSelected());
		else

		if(ie.getSource() == forceHQ2XCheckbox)getSprite().setForceHQ2X(forceHQ2XCheckbox.isSelected());
		else
		if(ie.getSource() == exportMD5Checkbox)getSprite().setForceMD5Export(exportMD5Checkbox.isSelected());
		else
		if(ie.getSource() == isItemCheckbox)getSprite().setIsItem(isItemCheckbox.isSelected());
		else
		if(ie.getSource() == isGameCheckbox)
		{
			getSprite().setIsGame(isGameCheckbox.isSelected());

			if(isGameCheckbox.isSelected()==true)isItemCheckbox.setSelected(true);

		}
		else

		if(ie.getSource() == isRandomCheckbox)
		{
			getSprite().setIsRandom(isRandomCheckbox.isSelected());


			if(isRandomCheckbox.isSelected()==true)
			{

				//go through all pixels of this sprite, for each color, look for that color from num_Colors->num_Colors-128.
				//if it exists, set the pixel to that color. if it doesn't exist, find the first open slot there, set it to this color, and set pixel to that.

				for(int f = 0; f < getSprite().frames(); f++)
				{
					for(int x = 0; x < getSprite().wP(); x++)
					{
						for(int y = 0; y < getSprite().hP(); y++)
						{

							int oldIndex = getSprite().getPixel(f, x, y);

							if(oldIndex!=0 && oldIndex < Project.getSelectedSpritePalette().numColors-128)
							{

								Color c = Project.getSelectedSpritePalette().getColor(oldIndex);

								int index = Project.getSelectedSpritePalette().findRandomColor(c.getRed(), c.getGreen(), c.getBlue());

								if(index==-1)index = Project.getSelectedSpritePalette().addRandomColor(c.getRed(), c.getGreen(), c.getBlue());

								getSprite().swapSpriteColors(oldIndex, index);

							}
						}
					}
				}

				exportMD5Checkbox.setSelected(true);
			}
		}




		if(ie.getSource().getClass().equals(JCheckBox.class))
		{
			if(((JCheckBox)ie.getSource()).isSelected()==true)((JCheckBox)ie.getSource()).setBackground(new Color(150,225,150));
			else ((JCheckBox)ie.getSource()).setBackground(SystemColor.menu);
		}


	}

	//===============================================================================================
	public void updateSpriteInfo()
	{//===============================================================================================

		timelinePanel.updateTimeline();
		animationListPanel.updateList();

		//update all the textfields based on the selected sprite
		displayNameText.setText(getSprite().displayName());
//		hitBoxLeftOffsetText.setText(""+getSprite().frameSequenceHitBoxLeftOffset[getSprite().getCurrentSequenceName()]);
//		hitBoxRightOffsetText.setText(""+getSprite().frameSequenceHitBoxRightOffset[getSprite().getCurrentSequenceName()]);
//		hitBoxTopOffsetText.setText(""+getSprite().frameSequenceHitBoxTopOffset[getSprite().getCurrentSequenceName()]);
//		hitBoxBottomOffsetText.setText(""+getSprite().frameSequenceHitBoxBottomOffset[getSprite().getCurrentSequenceName()]);
//		utilityOffsetXText.setText(""+getSprite().utilityPointOffsetX);
//		utilityOffsetYText.setText(""+getSprite().utilityPointOffsetY);
		//animDirectionsText.setText(""+getSprite().animDirections);
		isNPCCheckbox.setSelected(getSprite().isNPC());

		isKidCheckbox.setSelected(getSprite().isKid());
		isAdultCheckbox.setSelected(getSprite().isAdult());
		isMaleCheckbox.setSelected(getSprite().isMale());
		isFemaleCheckbox.setSelected(getSprite().isFemale());
		isCarCheckbox.setSelected(getSprite().isCar());
		isAnimalCheckbox.setSelected(getSprite().isAnimal());


		forceHQ2XCheckbox.setSelected(getSprite().forceHQ2X());
		exportMD5Checkbox.setSelected(getSprite().forceMD5Export());
		isItemCheckbox.setSelected(getSprite().isItem());
		isGameCheckbox.setSelected(getSprite().isGame());
		isDoorCheckbox.setSelected(getSprite().isDoor());
		itemGameDescriptionText.setText(""+getSprite().itemGameDescription());
		gamePriceText.setText(""+getSprite().gamePrice());



		if(getSprite().eventData()!=null)
		{
			addEditEventButton.setForeground(Color.RED);
			addEditEventButton.setBackground(Color.RED);
			addEditEventButton.setText("Edit Sprite Event");
		}
		else
		{

			addEditEventButton.setForeground(Color.GRAY);
			addEditEventButton.setBackground(Color.GRAY);
			addEditEventButton.setText("Add Event To Sprite");

		}


		hasShadowCheckbox.setSelected(getSprite().hasShadow());
		isRandomCheckbox.setSelected(getSprite().isRandom());

		//numFramesText.setText(""+getSprite().getNumFrames());
		//numFramesPanel.validate();
		//widthHeightText.setText(""+getSprite().getWidth()+" x "+getSprite().getHeight());
		//widthHeightPanel.validate();

		SpriteAnimationSequence a = getSprite().getAnimationForExactFrameOrNull(getSprite().getSelectedFrameIndex());
		if(a==null)
		{
			frameNameTextField.setText("");

		}
		else
		{
			frameNameTextField.setText(""+a.frameSequenceName);

		}
		frameNameTextField.setForeground(Color.GRAY);

		String allFramesString = "0";
		for(int i=1;i<getSprite().frames();i++)allFramesString = allFramesString.concat(","+i);
		sequenceTextField.setText(allFramesString);

		timer.start();


		SpriteEditor.setFrameCanvasHeight();

		SpriteEditor.frameCanvas.repaint();
	}

	//===============================================================================================
	public void updateFrames()
	{//===============================================================================================

		previousFrame.setEnabled(false);
		nextFrame.setEnabled(false);
		moveLeft.setEnabled(false);
		newFrameBefore.setEnabled(false);
		duplicateFrame.setEnabled(false);
		deleteFrame.setEnabled(false);
		moveRight.setEnabled(false);

		if(Project.getNumSprites() > 0)
		{
			if(getSprite().frames() > 0)
			{
				frameNumber.setText("Frame #" + getSprite().getSelectedFrameIndex());
				if(getSprite().getSelectedFrameIndex() > 0)
				{
					previousFrame.setEnabled(true);
					moveLeft.setEnabled(true);
				}
				if(getSprite().getSelectedFrameIndex() < getSprite().frames() - 1)
				{
					nextFrame.setEnabled(true);
					moveRight.setEnabled(true);
				}
				duplicateFrame.setEnabled(true);
				deleteFrame.setEnabled(true);
			}
			newFrameBefore.setEnabled(true);
		}

		repaint();


		SpriteEditor.frameCanvas.scrollToFrame(getSprite().getSelectedFrameIndex());
	}


	//===============================================================================================
	public Sprite getSprite()
	{//===============================================================================================

		return Project.getSelectedSprite();
	}

	//===============================================================================================
	public SpritePalette getSpritePal()
	{//===============================================================================================
		return Project.getSelectedSpritePalette();
	}




	//===============================================================================================
	public void setFPS()
	{//===============================================================================================
		if(Integer.parseInt(fpsTextField.getText()) > 30)
		{
			fpsTextField.setText("30");
		}
		int delay = 1000 / (Integer.parseInt(fpsTextField.getText()));
		timer.setDelay(delay);
	}

	//===============================================================================================
	public void buildSequence()
	{//===============================================================================================
		parsedSequenceFramesText = sequenceTextField.getText().split(",");
		numParsedFrames = parsedSequenceFramesText.length;


		sequenceFrameImages = new BufferedImage[numParsedFrames];


		for(int f = 0; f < numParsedFrames; f++)
		{
			sequenceFrameImages[f] = getGraphicsConfiguration().createCompatibleImage(getSprite().wP(), getSprite().hP(), Transparency.BITMASK);

			//fill it with background color
			Graphics G = sequenceFrameImages[f].getGraphics();
			G.setColor(Project.getSelectedSpritePalette().getColor(0));
			G.fillRect(0, 0, getSprite().wP(), getSprite().hP());


			int spriteFrame = 0;
			if(parsedSequenceFramesText.length > 1)
			{
				spriteFrame = Integer.parseInt(parsedSequenceFramesText[f]);
			}


			if(spriteFrame<getSprite().frames())
			{
				for(int x = 0; x < getSprite().wP(); x++)
					for(int y = 0; y < getSprite().hP(); y++)
					{
						int pixel = getSprite().getPixel(spriteFrame, x, y);
						if(pixel != 0)
						{
							G.setColor(Project.getSelectedSpritePalette().getColor(pixel));
							G.fillRect(x, y, 1, 1);
						}
					}
			}
		}
		currentFrame = 0;
	}


	//===============================================================================================
	public void previousFrame()
	{//===============================================================================================
		getSprite().previousFrame();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();
	}


	//===============================================================================================
	public void nextFrame()
	{//===============================================================================================
		getSprite().nextFrame();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();
	}


	//===============================================================================================
	public void newFrameBefore()
	{//===============================================================================================
		getSprite().insertFrame();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();

	}


	//===============================================================================================
	public void newFrameAfter()
	{//===============================================================================================
		getSprite().insertFrameAfter();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();

	}


	//===============================================================================================
	public void duplicateFrame()
	{//===============================================================================================
		getSprite().duplicateFrame();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();
	}


	//===============================================================================================
	public void deleteFrame()
	{//===============================================================================================
		getSprite().deleteFrame();

		updateSpriteInfo();
		updateFrames();

		SpriteEditor.editCanvas.repaintBufferImage();
		SpriteEditor.editCanvas.repaint();
	}

	//===============================================================================================
	public void moveLeft()
	{//===============================================================================================
		getSprite().moveFrameLeft();

		updateSpriteInfo();
		updateFrames();
	}

	//===============================================================================================
	public void moveRight()
	{//===============================================================================================
		getSprite().moveFrameRight();

		updateSpriteInfo();
		updateFrames();
	}



	@Override
	public void keyTyped(KeyEvent e)
	{
		// TODO Auto-generated method stub

	}



	@Override
	public void keyPressed(KeyEvent e)
	{

		if(e.getSource() == frameNameTextField)
		{

			if(e.getKeyCode() == KeyEvent.VK_ENTER)
			{

				frameNameTextField.setForeground(Color.GRAY);

				//if(frameNameTextField.getText().length()>0)
				{
					SpriteAnimationSequence a = getSprite().getAnimationForExactFrameOrNull(getSprite().getSelectedFrameIndex());

					if(a!=null)
					{
						//if no name
						if(frameNameTextField.getText().length()==0)
						{
							//delete animation if exists
							getSprite().animationList().remove(a);
						}
						else
						{
							//set animation name
							a.frameSequenceName = frameNameTextField.getText();
						}

					}

					if(a==null)
					{
						//if no name
						if(frameNameTextField.getText().length()==0)
						{
							//do nothing
						}
						else
						{
							//create new animation
							getSprite().getData().addAnimation(frameNameTextField.getText(),getSprite().getSelectedFrameIndex(),0,0,0,0);
						}

					}

				}

				SpriteEditor.editCanvas.repaint();
				SpriteEditor.frameCanvas.repaint();
			}

			return;
		}

		if(e.getSource()==frameNameTextField)
		{
			return;
		}


		if(e.getSource() == sequenceTextField)
		{
			return;
		}
		else if(e.getSource() == fpsTextField)
		{
			return;
		}
		else if(e.getSource() == displayNameText)
		{
			return;
		}
		else if(e.getSource() == itemGameDescriptionText)
		{
			return;
		}
		else if(e.getSource() == gamePriceText)
		{
			return;
		}


		SpriteEditor.editCanvas.keyPressed(e);

	}



	@Override
	public void keyReleased(KeyEvent e)
	{
		// TODO Auto-generated method stub

	}
	@Override
	public void caretUpdate(CaretEvent e)
	{


		if(e.getSource()==frameNameTextField)
		{
			frameNameTextField.setForeground(Color.RED);
		}


		if(e.getSource() == sequenceTextField)
		{
			//timer.stop();
			buildSequence();
			//timer.start();
		}
		else if(e.getSource() == fpsTextField)
		{
			//timer.stop();
			setFPS();
			//timer.start();
		}
		else if(e.getSource() == displayNameText)
		{
			if(displayNameText.getText().length()>0)
			getSprite().setDisplayName(displayNameText.getText());
		}
		else if(e.getSource() == itemGameDescriptionText)
		{
			if(itemGameDescriptionText.getText().length()>0)
			getSprite().setItemGameDescription(itemGameDescriptionText.getText().replaceAll("\n", ""));
		}
		else if(e.getSource() == gamePriceText)
		{
			if(gamePriceText.getText().length()>0)
			{
				float d = -1;
				try{d = Float.parseFloat(gamePriceText.getText());}catch(Exception ex){d=-1;}
				if(d!=-1)getSprite().setGamePrice(d);
			}

		}



	}











}
