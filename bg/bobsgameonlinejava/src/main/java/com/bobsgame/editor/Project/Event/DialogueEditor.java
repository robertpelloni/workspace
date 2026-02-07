package com.bobsgame.editor.Project.Event;

import java.awt.BorderLayout;

import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Image;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;
import java.awt.image.ImageObserver;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.WindowConstants;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.bobsgame.EditorMain;



//===============================================================================================
public class DialogueEditor extends JDialog implements ActionListener, TextListener, ItemListener, ImageObserver, KeyListener, DocumentListener
{//===============================================================================================




	public JTextArea textArea;
	public DialoguePreviewPanel previewPanel;

	public JTextField commentTextField, captionTextField;


	public JButton
					pauseClearButton,
					pauseButton,
					clearButton,
					newLineButton,
					selectBox0Button,
					selectBox1Button,
					close1Button,
					keepOpenAfterButton,
					noCancelButton,

					playerNameButton,
					currentSpriteBoxNameButton,
					walkToXYButton,
					walkToAreaButton,
					fadeOutButton,
					fadeInButton,
					toggleLetterboxButton,
					playSoundButton,
					playMusicButton,

					setSpriteBox0ToSpriteButton,
					setSpriteBox1ToSpriteButton,
					setSpriteBox0ToEntityButton,
					setSpriteBox1ToEntityButton,

					auxilaryStringButton,

					cam0Button,
					cam1Button,
					camNPCButton,
					shakeButton,
					delayButton,
					pitchButton,
					openKeyboardButton,
					answerButton,
					fontBobButton,
					fontSmallButton,
					fontNormalButton,
					fontLargeButton,
					fontColorBlackButton,
					fontColorWhiteButton,
					fontColorGrayButton,
					fontColorRedButton,
					fontColorOrangeButton,
					fontColorYellowButton,
					fontColorGreenButton,
					fontColorBlueButton,
					fontColorPurpleButton,
					fontColorPinkButton

					;




	public JButton
					doneButton,
					cancelButton
					;




	public Dialogue currentDialogue = null;




	//===============================================================================================
	public DialogueEditor(Frame f)
	{//===============================================================================================

		super(f, "Dialogue Editor", true);

		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);


		setLayout(new BorderLayout());



		Color panelColor = Color.DARK_GRAY;
		Color buttonTextColor = Color.black;
		Color buttonBackgroundColor = Color.black;
		Color labelTextColor = Color.white;


		setBackground(panelColor);

		JPanel everythingPanel = new JPanel(new BorderLayout());
		everythingPanel.setBorder(EditorMain.border);
		everythingPanel.setBackground(panelColor);



		JPanel topPanel = new JPanel(new BorderLayout());
		topPanel.setBackground(panelColor);

		JPanel buttonPanel = new JPanel();
		buttonPanel.setBackground(panelColor);
			buttonPanel.setBorder(EditorMain.border);
			buttonPanel.setLayout(new BoxLayout(buttonPanel,BoxLayout.X_AXIS));
				doneButton = new JButton("Done");
				doneButton.addActionListener(this);
				doneButton.setBackground(Color.GREEN);

				cancelButton = new JButton("Cancel");
				cancelButton.addActionListener(this);
				cancelButton.setBackground(Color.RED);


			buttonPanel.add(Box.createHorizontalGlue());
			buttonPanel.add(doneButton);
			buttonPanel.add(cancelButton);


		topPanel.add(buttonPanel,BorderLayout.NORTH);



		JPanel dialogueNamePanel = new JPanel();
		dialogueNamePanel.setLayout(new BoxLayout(dialogueNamePanel,BoxLayout.X_AXIS));
		dialogueNamePanel.setBackground(panelColor);


		JPanel captionPanel = new JPanel();
		captionPanel.setBackground(panelColor);
		JLabel captionLabel = new JLabel("Dialogue Caption:");
		captionLabel.setForeground(labelTextColor);
		captionTextField = new JTextField();
		captionTextField.setColumns(50);
		captionTextField.setFont(new Font("Tahoma", Font.PLAIN, 11));
		captionPanel.add(captionLabel);
		captionPanel.add(captionTextField);

		JPanel commentPanel = new JPanel();
		commentPanel.setBackground(panelColor);
		JLabel commentLabel = new JLabel("Dialogue Comment:");
		commentLabel.setForeground(labelTextColor);
		commentTextField = new JTextField();
		commentTextField.setColumns(50);
		commentTextField.setFont(new Font("Tahoma", Font.PLAIN, 11));
		commentPanel.add(commentLabel);
		commentPanel.add(commentTextField);

		dialogueNamePanel.add(captionPanel);
		dialogueNamePanel.add(commentPanel);

		topPanel.add(dialogueNamePanel,BorderLayout.SOUTH);


		everythingPanel.add(topPanel,BorderLayout.NORTH);






		textArea = new JTextArea();
		textArea.setBackground(new Color(24,24,24));
		textArea.setForeground(Color.LIGHT_GRAY);
		textArea.setFont(new Font("Tahoma", Font.PLAIN, 14));
		textArea.setCaretColor(Color.white);
		textArea.getCaret().setBlinkRate(100);
		textArea.getDocument().addDocumentListener(this);


		everythingPanel.add(textArea,BorderLayout.CENTER);

		previewPanel = new DialoguePreviewPanel();
		everythingPanel.add(previewPanel, BorderLayout.SOUTH);





		Font dialogueEditorCommandButtonsFont = EditorMain.bobsgameFont;



		JPanel leftPanel = new JPanel();
		leftPanel.setBorder(EditorMain.border);
		leftPanel.setLayout(new GridLayout(0,2,0,0));
		leftPanel.setBackground(panelColor);

		JLabel pauseClearButtonLabel = new JLabel("Pause and clear (new page)",JLabel.RIGHT);
		pauseClearButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		pauseClearButtonLabel.setForeground(labelTextColor);
		pauseClearButton = new JButton("<.> <PAUSECLEAR>");
		pauseClearButton.setFont(new Font("Arial", Font.BOLD, 11));
		pauseClearButton.setBackground(buttonBackgroundColor);
		pauseClearButton.setForeground(buttonTextColor);
		pauseClearButton.setFocusable(false);
		pauseClearButton.addActionListener(this);
		leftPanel.add(pauseClearButtonLabel);
		leftPanel.add(pauseClearButton);

		JLabel pauseButtonLabel = new JLabel("Pause without clearing text",JLabel.RIGHT);
		pauseButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		pauseButtonLabel.setForeground(labelTextColor);
		pauseButton = new JButton("<PAUSE>");
		pauseButton.setFont(new Font("Arial", Font.BOLD, 11));
		pauseButton.setBackground(buttonBackgroundColor);
		pauseButton.setForeground(buttonTextColor);
		pauseButton.setFocusable(false);
		pauseButton.addActionListener(this);
		leftPanel.add(pauseButtonLabel);
		leftPanel.add(pauseButton);

		JLabel clearButtonLabel = new JLabel("Clear text without pausing",JLabel.RIGHT);
		clearButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		clearButtonLabel.setForeground(labelTextColor);
		clearButton = new JButton("<CLEAR>");
		clearButton.setFont(new Font("Arial", Font.BOLD, 11));
		clearButton.setBackground(buttonBackgroundColor);
		clearButton.setForeground(buttonTextColor);
		clearButton.setFocusable(false);
		clearButton.addActionListener(this);
		leftPanel.add(clearButtonLabel);
		leftPanel.add(clearButton);

		JLabel newLineButtonLabel = new JLabel("Set cursor to next line",JLabel.RIGHT);
		newLineButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		newLineButtonLabel.setForeground(labelTextColor);
		newLineButton = new JButton("<NEWLINE> <NEXTLINE> (\\n)");
		newLineButton.setFont(new Font("Arial", Font.BOLD, 11));
		newLineButton.setBackground(buttonBackgroundColor);
		newLineButton.setForeground(buttonTextColor);
		newLineButton.setFocusable(false);
		newLineButton.addActionListener(this);
		leftPanel.add(newLineButtonLabel);
		leftPanel.add(newLineButton);



		JLabel selectBox0ButtonLabel = new JLabel("Select Box 0 (bottom)",JLabel.RIGHT);
		selectBox0ButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		selectBox0ButtonLabel.setForeground(labelTextColor);
		selectBox0Button = new JButton("<0>");
		selectBox0Button.setFont(new Font("Arial", Font.BOLD, 11));
		selectBox0Button.setBackground(buttonBackgroundColor);
		selectBox0Button.setForeground(buttonTextColor);
		selectBox0Button.setFocusable(false);
		selectBox0Button.addActionListener(this);
		leftPanel.add(selectBox0ButtonLabel);
		leftPanel.add(selectBox0Button);

		JLabel selectBox1ButtonLabel = new JLabel("Select Box 1 (top) (opens box)",JLabel.RIGHT);
		selectBox1ButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		selectBox1ButtonLabel.setForeground(labelTextColor);
		selectBox1Button = new JButton("<1>");
		selectBox1Button.setFont(new Font("Arial", Font.BOLD, 11));
		selectBox1Button.setBackground(buttonBackgroundColor);
		selectBox1Button.setForeground(buttonTextColor);
		selectBox1Button.setFocusable(false);
		selectBox1Button.addActionListener(this);
		leftPanel.add(selectBox1ButtonLabel);
		leftPanel.add(selectBox1Button);

		JLabel close1ButtonLabel = new JLabel("Close Box 1 (top)",JLabel.RIGHT);
		close1ButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		close1ButtonLabel.setForeground(labelTextColor);
		close1Button = new JButton("<CLOSE1>");
		close1Button.setFont(new Font("Arial", Font.BOLD, 11));
		close1Button.setBackground(buttonBackgroundColor);
		close1Button.setForeground(buttonTextColor);
		close1Button.setFocusable(false);
		close1Button.addActionListener(this);
		leftPanel.add(close1ButtonLabel);
		leftPanel.add(close1Button);

		JLabel keepOpenAfterButtonLabel = new JLabel("Keep text box open for more text",JLabel.RIGHT);
		keepOpenAfterButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		keepOpenAfterButtonLabel.setForeground(labelTextColor);
		keepOpenAfterButton = new JButton("<KEEPOPENAFTER>");
		keepOpenAfterButton.setFont(new Font("Arial", Font.BOLD, 11));
		keepOpenAfterButton.setBackground(buttonBackgroundColor);
		keepOpenAfterButton.setForeground(buttonTextColor);
		keepOpenAfterButton.setFocusable(false);
		keepOpenAfterButton.addActionListener(this);
		leftPanel.add(keepOpenAfterButtonLabel);
		leftPanel.add(keepOpenAfterButton);

		JLabel noCancelButtonLabel = new JLabel("Don't allow text to be cancelled",JLabel.RIGHT);
		noCancelButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		noCancelButtonLabel.setForeground(labelTextColor);
		noCancelButton = new JButton("<NOCANCEL>");
		noCancelButton.setFont(new Font("Arial", Font.BOLD, 11));
		noCancelButton.setBackground(buttonBackgroundColor);
		noCancelButton.setForeground(buttonTextColor);
		noCancelButton.setFocusable(false);
		noCancelButton.addActionListener(this);
		leftPanel.add(noCancelButtonLabel);
		leftPanel.add(noCancelButton);




		JLabel playerNameButtonLabel = new JLabel("Insert Player Name",JLabel.RIGHT);
		playerNameButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		playerNameButtonLabel.setForeground(labelTextColor);
		playerNameButton = new JButton("<PLAYERNAME>");
		playerNameButton.setFont(new Font("Arial", Font.BOLD, 11));
		playerNameButton.setBackground(buttonBackgroundColor);
		playerNameButton.setForeground(buttonTextColor);
		playerNameButton.setFocusable(false);
		playerNameButton.addActionListener(this);
		leftPanel.add(playerNameButtonLabel);
		leftPanel.add(playerNameButton);

		JLabel currentSpriteBoxNameButtonLabel = new JLabel("Insert Current Text Box Sprite Name",JLabel.RIGHT);
		currentSpriteBoxNameButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		currentSpriteBoxNameButtonLabel.setForeground(labelTextColor);
		currentSpriteBoxNameButton = new JButton("<CURRENTSPRITEBOXNAME>");
		currentSpriteBoxNameButton.setFont(new Font("Arial", Font.BOLD, 11));
		currentSpriteBoxNameButton.setBackground(buttonBackgroundColor);
		currentSpriteBoxNameButton.setForeground(buttonTextColor);
		currentSpriteBoxNameButton.setFocusable(false);
		currentSpriteBoxNameButton.addActionListener(this);
		leftPanel.add(currentSpriteBoxNameButtonLabel);
		leftPanel.add(currentSpriteBoxNameButton);

		JLabel walkToXYButtonLabel = new JLabel("Instruct Current Text Box Sprite To Walk To XY",JLabel.RIGHT);
		walkToXYButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		walkToXYButtonLabel.setForeground(labelTextColor);
		walkToXYButton = new JButton("<WALKTOXY:px,py>");
		walkToXYButton.setFont(new Font("Arial", Font.BOLD, 11));
		walkToXYButton.setBackground(buttonBackgroundColor);
		walkToXYButton.setForeground(buttonTextColor);
		walkToXYButton.setFocusable(false);
		walkToXYButton.addActionListener(this);
		leftPanel.add(walkToXYButtonLabel);
		leftPanel.add(walkToXYButton);

		JLabel walkToAreaButtonLabel = new JLabel("Instruct Current Text Box Sprite To Walk To Area",JLabel.RIGHT);
		walkToAreaButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		walkToAreaButtonLabel.setForeground(labelTextColor);
		walkToAreaButton = new JButton("<WALKTOAREA:areaName>");
		walkToAreaButton.setFont(new Font("Arial", Font.BOLD, 11));
		walkToAreaButton.setBackground(buttonBackgroundColor);
		walkToAreaButton.setForeground(buttonTextColor);
		walkToAreaButton.setFocusable(false);
		walkToAreaButton.addActionListener(this);
		leftPanel.add(walkToAreaButtonLabel);
		leftPanel.add(walkToAreaButton);

		JLabel fadeOutButtonLabel = new JLabel("Fade Screen To Black",JLabel.RIGHT);
		fadeOutButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fadeOutButtonLabel.setForeground(labelTextColor);
		fadeOutButton = new JButton("<FADEOUT>");
		fadeOutButton.setFont(new Font("Arial", Font.BOLD, 11));
		fadeOutButton.setBackground(buttonBackgroundColor);
		fadeOutButton.setForeground(buttonTextColor);
		fadeOutButton.setFocusable(false);
		fadeOutButton.addActionListener(this);
		leftPanel.add(fadeOutButtonLabel);
		leftPanel.add(fadeOutButton);

		JLabel fadeInButtonLabel = new JLabel("Fade Screen From Black",JLabel.RIGHT);
		fadeInButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fadeInButtonLabel.setForeground(labelTextColor);
		fadeInButton = new JButton("<FADEIN>");
		fadeInButton.setFont(new Font("Arial", Font.BOLD, 11));
		fadeInButton.setBackground(buttonBackgroundColor);
		fadeInButton.setForeground(buttonTextColor);
		fadeInButton.setFocusable(false);
		fadeInButton.addActionListener(this);
		leftPanel.add(fadeInButtonLabel);
		leftPanel.add(fadeInButton);

		JLabel toggleLetterboxButtonLabel = new JLabel("Toggle Letterbox",JLabel.RIGHT);
		toggleLetterboxButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		toggleLetterboxButtonLabel.setForeground(labelTextColor);
		toggleLetterboxButton = new JButton("<TOGGLELETTERBOX>");
		toggleLetterboxButton.setFont(new Font("Arial", Font.BOLD, 11));
		toggleLetterboxButton.setBackground(buttonBackgroundColor);
		toggleLetterboxButton.setForeground(buttonTextColor);
		toggleLetterboxButton.setFocusable(false);
		toggleLetterboxButton.addActionListener(this);
		leftPanel.add(toggleLetterboxButtonLabel);
		leftPanel.add(toggleLetterboxButton);

		JLabel playSoundButtonLabel = new JLabel("Play Sound",JLabel.RIGHT);
		playSoundButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		playSoundButtonLabel.setForeground(labelTextColor);
		playSoundButton = new JButton("<PLAYSOUND:soundName>");
		playSoundButton.setFont(new Font("Arial", Font.BOLD, 11));
		playSoundButton.setBackground(buttonBackgroundColor);
		playSoundButton.setForeground(buttonTextColor);
		playSoundButton.setFocusable(false);
		playSoundButton.addActionListener(this);
		leftPanel.add(playSoundButtonLabel);
		leftPanel.add(playSoundButton);


		JLabel playMusicButtonLabel = new JLabel("Play Music",JLabel.RIGHT);
		playMusicButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		playMusicButtonLabel.setForeground(labelTextColor);
		playMusicButton = new JButton("<PLAYMUSIC:musicName>");
		playMusicButton.setFont(new Font("Arial", Font.BOLD, 11));
		playMusicButton.setBackground(buttonBackgroundColor);
		playMusicButton.setForeground(buttonTextColor);
		playMusicButton.setFocusable(false);
		playMusicButton.addActionListener(this);
		leftPanel.add(playMusicButtonLabel);
		leftPanel.add(playMusicButton);


		JLabel setSpriteBox0ToSpriteButtonLabel = new JLabel("Set Sprite Box 0 (Bottom) To Sprite",JLabel.RIGHT);
		setSpriteBox0ToSpriteButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		setSpriteBox0ToSpriteButtonLabel.setForeground(labelTextColor);
		setSpriteBox0ToSpriteButton = new JButton("<SETSPRITEBOX0TOSPRITE:spriteName>");
		setSpriteBox0ToSpriteButton.setFont(new Font("Arial", Font.BOLD, 11));
		setSpriteBox0ToSpriteButton.setBackground(buttonBackgroundColor);
		setSpriteBox0ToSpriteButton.setForeground(buttonTextColor);
		setSpriteBox0ToSpriteButton.setFocusable(false);
		setSpriteBox0ToSpriteButton.addActionListener(this);
		leftPanel.add(setSpriteBox0ToSpriteButtonLabel);
		leftPanel.add(setSpriteBox0ToSpriteButton);

		JLabel setSpriteBox1ToSpriteButtonLabel = new JLabel("Set Sprite Box 1 (Top) To Sprite",JLabel.RIGHT);
		setSpriteBox1ToSpriteButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		setSpriteBox1ToSpriteButtonLabel.setForeground(labelTextColor);
		setSpriteBox1ToSpriteButton = new JButton("<SETSPRITEBOX1TOSPRITE:spriteName>");
		setSpriteBox1ToSpriteButton.setFont(new Font("Arial", Font.BOLD, 11));
		setSpriteBox1ToSpriteButton.setBackground(buttonBackgroundColor);
		setSpriteBox1ToSpriteButton.setForeground(buttonTextColor);
		setSpriteBox1ToSpriteButton.setFocusable(false);
		setSpriteBox1ToSpriteButton.addActionListener(this);
		leftPanel.add(setSpriteBox1ToSpriteButtonLabel);
		leftPanel.add(setSpriteBox1ToSpriteButton);


		JLabel setSpriteBox0ToEntityButtonLabel = new JLabel("Set Sprite Box 0 (Bottom) To Entity",JLabel.RIGHT);
		setSpriteBox0ToEntityButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		setSpriteBox0ToEntityButtonLabel.setForeground(labelTextColor);
		setSpriteBox0ToEntityButton = new JButton("<SETSPRITEBOX0TOENTITY:entityName>");
		setSpriteBox0ToEntityButton.setFont(new Font("Arial", Font.BOLD, 11));
		setSpriteBox0ToEntityButton.setBackground(buttonBackgroundColor);
		setSpriteBox0ToEntityButton.setForeground(buttonTextColor);
		setSpriteBox0ToEntityButton.setFocusable(false);
		setSpriteBox0ToEntityButton.addActionListener(this);
		leftPanel.add(setSpriteBox0ToEntityButtonLabel);
		leftPanel.add(setSpriteBox0ToEntityButton);

		JLabel setSpriteBox1ToEntityButtonLabel = new JLabel("Set Sprite Box 1 (Top) To Entity",JLabel.RIGHT);
		setSpriteBox1ToEntityButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		setSpriteBox1ToEntityButtonLabel.setForeground(labelTextColor);
		setSpriteBox1ToEntityButton = new JButton("<SETSPRITEBOX1TOENTITY:entityName>");
		setSpriteBox1ToEntityButton.setFont(new Font("Arial", Font.BOLD, 11));
		setSpriteBox1ToEntityButton.setBackground(buttonBackgroundColor);
		setSpriteBox1ToEntityButton.setForeground(buttonTextColor);
		setSpriteBox1ToEntityButton.setFocusable(false);
		setSpriteBox1ToEntityButton.addActionListener(this);
		leftPanel.add(setSpriteBox1ToEntityButtonLabel);
		leftPanel.add(setSpriteBox1ToEntityButton);


		JLabel auxilaryStringButtonLabel = new JLabel("Print Auxilary String Variable",JLabel.RIGHT);
		auxilaryStringButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		auxilaryStringButtonLabel.setForeground(labelTextColor);
		auxilaryStringButton = new JButton("<PRINTAUXSTRING>");
		auxilaryStringButton.setFont(new Font("Arial", Font.BOLD, 11));
		auxilaryStringButton.setBackground(buttonBackgroundColor);
		auxilaryStringButton.setForeground(buttonTextColor);
		auxilaryStringButton.setFocusable(false);
		auxilaryStringButton.addActionListener(this);
		leftPanel.add(auxilaryStringButtonLabel);
		leftPanel.add(auxilaryStringButton);




		JLabel cam0ButtonLabel = new JLabel("Force focus camera on speaker 0 (bottom)",JLabel.RIGHT);
		cam0ButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		cam0ButtonLabel.setForeground(labelTextColor);
		cam0Button = new JButton("<CAM0>");
		cam0Button.setFont(new Font("Arial", Font.BOLD, 11));
		cam0Button.setBackground(buttonBackgroundColor);
		cam0Button.setForeground(buttonTextColor);
		cam0Button.setFocusable(false);
		cam0Button.addActionListener(this);
		leftPanel.add(cam0ButtonLabel);
		leftPanel.add(cam0Button);

		JLabel cam1ButtonLabel = new JLabel("Force focus camera on speaker 1 (top)",JLabel.RIGHT);
		cam1ButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		cam1ButtonLabel.setForeground(labelTextColor);
		cam1Button = new JButton("<CAM1>");
		cam1Button.setFont(new Font("Arial", Font.BOLD, 11));
		cam1Button.setBackground(buttonBackgroundColor);
		cam1Button.setForeground(buttonTextColor);
		cam1Button.setFocusable(false);
		cam1Button.addActionListener(this);
		leftPanel.add(cam1ButtonLabel);
		leftPanel.add(cam1Button);

		JLabel camNPCButtonLabel = new JLabel("Force focus camera on NPC:name",JLabel.RIGHT);
		camNPCButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		camNPCButtonLabel.setForeground(labelTextColor);
		camNPCButton = new JButton("<CAMNPC:name>");
		camNPCButton.setFont(new Font("Arial", Font.BOLD, 11));
		camNPCButton.setBackground(buttonBackgroundColor);
		camNPCButton.setForeground(buttonTextColor);
		camNPCButton.setFocusable(false);
		camNPCButton.addActionListener(this);
		leftPanel.add(camNPCButtonLabel);
		leftPanel.add(camNPCButton);

		JLabel delayButtonLabel = new JLabel("Delay text for x ms",JLabel.RIGHT);
		delayButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		delayButtonLabel.setForeground(labelTextColor);
		delayButton = new JButton("<DELAY:ms>");
		delayButton.setFont(new Font("Arial", Font.BOLD, 11));
		delayButton.setBackground(buttonBackgroundColor);
		delayButton.setForeground(buttonTextColor);
		delayButton.setFocusable(false);
		delayButton.addActionListener(this);
		leftPanel.add(delayButtonLabel);
		leftPanel.add(delayButton);

		JLabel shakeButtonLabel = new JLabel("Shake textbox and camera for x ms",JLabel.RIGHT);
		shakeButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		shakeButtonLabel.setForeground(labelTextColor);
		shakeButton = new JButton("<SHAKE:ms>");
		shakeButton.setFont(new Font("Arial", Font.BOLD, 11));
		shakeButton.setBackground(buttonBackgroundColor);
		shakeButton.setForeground(buttonTextColor);
		shakeButton.setFocusable(false);
		shakeButton.addActionListener(this);
		leftPanel.add(shakeButtonLabel);
		leftPanel.add(shakeButton);


		JLabel pitchButtonLabel = new JLabel("Set current text box pitch to x hz",JLabel.RIGHT);
		pitchButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		pitchButtonLabel.setForeground(labelTextColor);
		pitchButton = new JButton("<PITCH:hz>");
		pitchButton.setFont(new Font("Arial", Font.BOLD, 11));
		pitchButton.setBackground(buttonBackgroundColor);
		pitchButton.setForeground(buttonTextColor);
		pitchButton.setFocusable(false);
		pitchButton.addActionListener(this);
		leftPanel.add(pitchButtonLabel);
		leftPanel.add(pitchButton);

		JLabel openKeyboardButtonLabel = new JLabel("Open keyboard and wait for input",JLabel.RIGHT);
		openKeyboardButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		openKeyboardButtonLabel.setForeground(labelTextColor);
		openKeyboardButton = new JButton("<KEYBOARD>");
		openKeyboardButton.setFont(new Font("Arial", Font.BOLD, 11));
		openKeyboardButton.setBackground(buttonBackgroundColor);
		openKeyboardButton.setForeground(buttonTextColor);
		openKeyboardButton.setFocusable(false);
		openKeyboardButton.addActionListener(this);
		leftPanel.add(openKeyboardButtonLabel);
		leftPanel.add(openKeyboardButton);

		JLabel answerButtonLabel = new JLabel("Open answer panel and wait for selected answer",JLabel.RIGHT);
		answerButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		answerButtonLabel.setForeground(labelTextColor);
		answerButton = new JButton("<Q:A:A:A>");
		answerButton.setFont(new Font("Arial", Font.BOLD, 11));
		answerButton.setBackground(buttonBackgroundColor);
		answerButton.setForeground(buttonTextColor);
		answerButton.setFocusable(false);
		answerButton.addActionListener(this);
		leftPanel.add(answerButtonLabel);
		leftPanel.add(answerButton);


		JLabel fontNormalButtonLabel = new JLabel("Normal Font",JLabel.RIGHT);
		fontNormalButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontNormalButtonLabel.setForeground(labelTextColor);
		fontNormalButton = new JButton("<FONTNORMAL>");
		fontNormalButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontNormalButton.setBackground(buttonBackgroundColor);
		fontNormalButton.setForeground(buttonTextColor);
		fontNormalButton.setFocusable(false);
		fontNormalButton.addActionListener(this);
		leftPanel.add(fontNormalButtonLabel);
		leftPanel.add(fontNormalButton);


		JLabel fontSmallButtonLabel = new JLabel("Small Font",JLabel.RIGHT);
		fontSmallButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontSmallButtonLabel.setForeground(labelTextColor);
		fontSmallButton = new JButton("<FONTSMALL>");
		fontSmallButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontSmallButton.setBackground(buttonBackgroundColor);
		fontSmallButton.setForeground(buttonTextColor);
		fontSmallButton.setFocusable(false);
		fontSmallButton.addActionListener(this);
		leftPanel.add(fontSmallButtonLabel);
		leftPanel.add(fontSmallButton);


		JLabel fontLargeButtonLabel = new JLabel("Large Font",JLabel.RIGHT);
		fontLargeButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontLargeButtonLabel.setForeground(labelTextColor);
		fontLargeButton = new JButton("<FONTLARGE>");
		fontLargeButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontLargeButton.setBackground(buttonBackgroundColor);
		fontLargeButton.setForeground(buttonTextColor);
		fontLargeButton.setFocusable(false);
		fontLargeButton.addActionListener(this);
		leftPanel.add(fontLargeButtonLabel);
		leftPanel.add(fontLargeButton);


		JLabel fontBobButtonLabel = new JLabel("Bob Font",JLabel.RIGHT);
		fontBobButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontBobButtonLabel.setForeground(labelTextColor);
		fontBobButton = new JButton("<FONTBOB>");
		fontBobButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontBobButton.setBackground(buttonBackgroundColor);
		fontBobButton.setForeground(buttonTextColor);
		fontBobButton.setFocusable(false);
		fontBobButton.addActionListener(this);
		leftPanel.add(fontBobButtonLabel);
		leftPanel.add(fontBobButton);


		JLabel fontColorWhiteButtonLabel = new JLabel("White Text (Default)",JLabel.RIGHT);
		fontColorWhiteButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorWhiteButtonLabel.setForeground(labelTextColor);
		fontColorWhiteButton = new JButton("<WHITE>");
		fontColorWhiteButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorWhiteButton.setBackground(buttonBackgroundColor);
		fontColorWhiteButton.setForeground(buttonTextColor);
		fontColorWhiteButton.setFocusable(false);
		fontColorWhiteButton.addActionListener(this);
		leftPanel.add(fontColorWhiteButtonLabel);
		leftPanel.add(fontColorWhiteButton);

		JLabel fontColorBlackButtonLabel = new JLabel("Black Text",JLabel.RIGHT);
		fontColorBlackButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorBlackButtonLabel.setForeground(labelTextColor);
		fontColorBlackButton = new JButton("<BLACK>");
		fontColorBlackButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorBlackButton.setBackground(buttonBackgroundColor);
		fontColorBlackButton.setForeground(Color.DARK_GRAY);
		fontColorBlackButton.setFocusable(false);
		fontColorBlackButton.addActionListener(this);
		leftPanel.add(fontColorBlackButtonLabel);
		leftPanel.add(fontColorBlackButton);

		JLabel fontColorGrayButtonLabel = new JLabel("Gray Text",JLabel.RIGHT);
		fontColorGrayButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorGrayButtonLabel.setForeground(labelTextColor);
		fontColorGrayButton = new JButton("<GRAY>");
		fontColorGrayButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorGrayButton.setBackground(buttonBackgroundColor);
		fontColorGrayButton.setForeground(Color.GRAY);
		fontColorGrayButton.setFocusable(false);
		fontColorGrayButton.addActionListener(this);
		leftPanel.add(fontColorGrayButtonLabel);
		leftPanel.add(fontColorGrayButton);

		JLabel fontColorRedButtonLabel = new JLabel("Red Text",JLabel.RIGHT);
		fontColorRedButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorRedButtonLabel.setForeground(labelTextColor);
		fontColorRedButton = new JButton("<RED>");
		fontColorRedButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorRedButton.setBackground(buttonBackgroundColor);
		fontColorRedButton.setForeground(Color.RED);
		fontColorRedButton.setFocusable(false);
		fontColorRedButton.addActionListener(this);
		leftPanel.add(fontColorRedButtonLabel);
		leftPanel.add(fontColorRedButton);

		JLabel fontColorOrangeButtonLabel = new JLabel("Orange Text",JLabel.RIGHT);
		fontColorOrangeButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorOrangeButtonLabel.setForeground(labelTextColor);
		fontColorOrangeButton = new JButton("<ORANGE>");
		fontColorOrangeButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorOrangeButton.setBackground(buttonBackgroundColor);
		fontColorOrangeButton.setForeground(Color.ORANGE);
		fontColorOrangeButton.setFocusable(false);
		fontColorOrangeButton.addActionListener(this);
		leftPanel.add(fontColorOrangeButtonLabel);
		leftPanel.add(fontColorOrangeButton);

		JLabel fontColorYellowButtonLabel = new JLabel("Yellow Text",JLabel.RIGHT);
		fontColorYellowButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorYellowButtonLabel.setForeground(labelTextColor);
		fontColorYellowButton = new JButton("<YELLOW>");
		fontColorYellowButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorYellowButton.setBackground(buttonBackgroundColor);
		fontColorYellowButton.setForeground(Color.YELLOW);
		fontColorYellowButton.setFocusable(false);
		fontColorYellowButton.addActionListener(this);
		leftPanel.add(fontColorYellowButtonLabel);
		leftPanel.add(fontColorYellowButton);

		JLabel fontColorGreenButtonLabel = new JLabel("Green Text",JLabel.RIGHT);
		fontColorGreenButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorGreenButtonLabel.setForeground(labelTextColor);
		fontColorGreenButton = new JButton("<GREEN>");
		fontColorGreenButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorGreenButton.setBackground(buttonBackgroundColor);
		fontColorGreenButton.setForeground(Color.GREEN);
		fontColorGreenButton.setFocusable(false);
		fontColorGreenButton.addActionListener(this);
		leftPanel.add(fontColorGreenButtonLabel);
		leftPanel.add(fontColorGreenButton);

		JLabel fontColorBlueButtonLabel = new JLabel("Blue Text",JLabel.RIGHT);
		fontColorBlueButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorBlueButtonLabel.setForeground(labelTextColor);
		fontColorBlueButton = new JButton("<BLUE>");
		fontColorBlueButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorBlueButton.setBackground(buttonBackgroundColor);
		fontColorBlueButton.setForeground(Color.BLUE);
		fontColorBlueButton.setFocusable(false);
		fontColorBlueButton.addActionListener(this);
		leftPanel.add(fontColorBlueButtonLabel);
		leftPanel.add(fontColorBlueButton);

		JLabel fontColorPurpleButtonLabel = new JLabel("Purple Text",JLabel.RIGHT);
		fontColorPurpleButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorPurpleButtonLabel.setForeground(labelTextColor);
		fontColorPurpleButton = new JButton("<PURPLE>");
		fontColorPurpleButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorPurpleButton.setBackground(buttonBackgroundColor);
		fontColorPurpleButton.setForeground(new Color(150,00,255));
		fontColorPurpleButton.setFocusable(false);
		fontColorPurpleButton.addActionListener(this);
		leftPanel.add(fontColorPurpleButtonLabel);
		leftPanel.add(fontColorPurpleButton);

		JLabel fontColorPinkButtonLabel = new JLabel("Pink Text",JLabel.RIGHT);
		fontColorPinkButtonLabel.setFont(dialogueEditorCommandButtonsFont);
		fontColorPinkButtonLabel.setForeground(labelTextColor);
		fontColorPinkButton = new JButton("<PINK>");
		fontColorPinkButton.setFont(new Font("Arial", Font.BOLD, 11));
		fontColorPinkButton.setBackground(buttonBackgroundColor);
		fontColorPinkButton.setForeground(Color.PINK);
		fontColorPinkButton.setFocusable(false);
		fontColorPinkButton.addActionListener(this);
		leftPanel.add(fontColorPinkButtonLabel);
		leftPanel.add(fontColorPinkButton);




		everythingPanel.add(leftPanel,BorderLayout.WEST);

		add(everythingPanel,BorderLayout.CENTER);


		setSize(1500, 800);



		setLocation(400,300);

	}




	//===============================================================================================
	public void createNewDialogue()
	{//===============================================================================================

		currentDialogue = new Dialogue("","","","");
		textArea.setText("");
		commentTextField.setText("");
		captionTextField.setText("");



		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}


	}

	//===============================================================================================
	public void editDialogue(Dialogue d)
	{//===============================================================================================

		currentDialogue = d;
		textArea.setText(d.text().replace("\n\n\n", "\n\n").replace("<.>", "\n\n").replace("<NEXTLINE>","\n").replace("<NEWLINE>","\n"));
		commentTextField.setText(d.comment());
		captionTextField.setText(d.caption());



		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}


	}

	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent ke)
	{//===============================================================================================


	}


	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent ke)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void textValueChanged(TextEvent te)
	{//===============================================================================================


	}

	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		if(ae.getSource() == doneButton)
		{

			String text = textArea.getText().replace("\r","");
			text = text.replace("\n","<NEWLINE>");
			text = text.replace("<NEWLINE><NEWLINE>","<.>");
			text = text.replace("<.><.>","<.>");
			text = text.replace("<NEWLINE><.>","<.>");
			text = text.replace("<.><NEWLINE>","<.>");
			text = text.replace("\\\"","\"");
			text = text.replace(". ",".  ");
			text = text.replace("! ","!  ");
			text = text.replace("? ","?  ");
			text = text.replace("   ","  ");
			text = text.replace("   ","  ");
			text = text.replace("   ","  ");

			currentDialogue.setText(text);
			currentDialogue.setComment(commentTextField.getText());
			currentDialogue.setCaption(captionTextField.getText());
			setVisible(false);

		}

		if(ae.getSource() == cancelButton)
		{

			setVisible(false);
		}

		if(ae.getSource() == pauseClearButton){textArea.insert("<.>", textArea.getCaretPosition());}
		if(ae.getSource() == pauseButton){textArea.insert("<PAUSE>", textArea.getCaretPosition());}
		if(ae.getSource() == clearButton){textArea.insert("<CLEAR>", textArea.getCaretPosition());}
		if(ae.getSource() == newLineButton){textArea.insert("<NEWLINE>", textArea.getCaretPosition());}
		if(ae.getSource() == selectBox0Button){textArea.insert("<0>", textArea.getCaretPosition());}
		if(ae.getSource() == selectBox1Button){textArea.insert("<1>", textArea.getCaretPosition());}
		if(ae.getSource() == close1Button){textArea.insert("<CLOSE1>", textArea.getCaretPosition());}
		if(ae.getSource() == keepOpenAfterButton){textArea.insert("<KEEPOPENAFTER>", textArea.getCaretPosition());}
		if(ae.getSource() == noCancelButton){textArea.insert("<NOCANCEL>", textArea.getCaretPosition());}

		if(ae.getSource() == playerNameButton){textArea.insert("<PLAYERNAME>", textArea.getCaretPosition());}
		if(ae.getSource() == currentSpriteBoxNameButton){textArea.insert("<CURRENTSPRITEBOXNAME>", textArea.getCaretPosition());}
		if(ae.getSource() == walkToXYButton){textArea.insert("<WALKTOXY:px,py>", textArea.getCaretPosition());}
		if(ae.getSource() == walkToAreaButton){textArea.insert("<WALKTOAREA:areaName>", textArea.getCaretPosition());}
		if(ae.getSource() == fadeOutButton){textArea.insert("<FADEOUT>", textArea.getCaretPosition());}
		if(ae.getSource() == fadeInButton){textArea.insert("<FADEIN>", textArea.getCaretPosition());}
		if(ae.getSource() == toggleLetterboxButton){textArea.insert("<TOGGLELETTERBOX>", textArea.getCaretPosition());}
		if(ae.getSource() == playSoundButton){textArea.insert("<PLAYSOUND:soundName>", textArea.getCaretPosition());}
		if(ae.getSource() == playMusicButton){textArea.insert("<PLAYMUSIC:musicName>", textArea.getCaretPosition());}

		if(ae.getSource() == setSpriteBox0ToSpriteButton){textArea.insert("<SETSPRITEBOX0TOSPRITE:spriteName>", textArea.getCaretPosition());}
		if(ae.getSource() == setSpriteBox1ToSpriteButton){textArea.insert("<SETSPRITEBOX1TOSPRITE:spriteName>", textArea.getCaretPosition());}
		if(ae.getSource() == setSpriteBox0ToEntityButton){textArea.insert("<SETSPRITEBOX0TOENTITY:entityName>", textArea.getCaretPosition());}
		if(ae.getSource() == setSpriteBox1ToEntityButton){textArea.insert("<SETSPRITEBOX1TOENTITY:entityName>", textArea.getCaretPosition());}

		if(ae.getSource() == auxilaryStringButton){textArea.insert("<PRINTAUXSTRING>", textArea.getCaretPosition());}

		if(ae.getSource() == cam0Button){textArea.insert("<CAM0>", textArea.getCaretPosition());}
		if(ae.getSource() == cam1Button){textArea.insert("<CAM1>", textArea.getCaretPosition());}
		if(ae.getSource() == camNPCButton){textArea.insert("<CAMNPC:??>", textArea.getCaretPosition());}
		if(ae.getSource() == shakeButton){textArea.insert("<SHAKE:???>", textArea.getCaretPosition());}
		if(ae.getSource() == delayButton){textArea.insert("<DELAY:???>", textArea.getCaretPosition());}
		if(ae.getSource() == pitchButton){textArea.insert("<PITCH:?????>", textArea.getCaretPosition());}
		if(ae.getSource() == openKeyboardButton){textArea.insert("<KEYBOARD>", textArea.getCaretPosition());}
		if(ae.getSource() == answerButton){textArea.insert("<Q:?:?:?>", textArea.getCaretPosition());}
		if(ae.getSource() == fontBobButton){textArea.insert("<FONTBOB>", textArea.getCaretPosition());}
		if(ae.getSource() == fontSmallButton){textArea.insert("<FONTSMALL>", textArea.getCaretPosition());}
		if(ae.getSource() == fontNormalButton){textArea.insert("<FONTNORMAL>", textArea.getCaretPosition());}
		if(ae.getSource() == fontLargeButton){textArea.insert("<FONTLARGE>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorBlackButton){textArea.insert("<BLACK>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorWhiteButton){textArea.insert("<WHITE>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorGrayButton){textArea.insert("<GRAY>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorRedButton){textArea.insert("<RED>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorOrangeButton){textArea.insert("<ORANGE>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorYellowButton){textArea.insert("<YELLOW>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorGreenButton){textArea.insert("<GREEN>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorBlueButton){textArea.insert("<BLUE>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorPurpleButton){textArea.insert("<PURPLE>", textArea.getCaretPosition());}
		if(ae.getSource() == fontColorPinkButton){textArea.insert("<PINK>", textArea.getCaretPosition());}

	}



	//===============================================================================================
	@Override
	public boolean imageUpdate(Image img, int infoflags, int x, int y,
			int width, int height)
	{//===============================================================================================

		return false;
	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		previewPanel.updatePreview(textArea.getText());
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		previewPanel.updatePreview(textArea.getText());
	}

	@Override
	public void changedUpdate(DocumentEvent e) {
		previewPanel.updatePreview(textArea.getText());
	}

	//===============================================================================================
	public class DialoguePreviewPanel extends JPanel
	{//===============================================================================================
		private String text = "";

		public DialoguePreviewPanel() {
			setPreferredSize(new java.awt.Dimension(600, 150));
			setBackground(Color.BLACK);
			setBorder(javax.swing.BorderFactory.createLineBorder(Color.WHITE));
		}

		public void updatePreview(String text) {
			this.text = text;
			repaint();
		}

		@Override
		protected void paintComponent(java.awt.Graphics g) {
			super.paintComponent(g);

			g.setColor(Color.WHITE);
			g.setFont(new Font("Monospaced", Font.PLAIN, 12)); // Simulating game font

			String[] pages = text.split("<\\.>"); // Split by pages
			String lastPage = pages.length > 0 ? pages[pages.length - 1] : "";

			// Replace newlines with a split token
			String cleanText = lastPage.replace("<NEWLINE>", "\n");
			String[] lines = cleanText.split("\n");

			int startY = 20;
			int startX = 10;
			int lineHeight = 15;

			int currentY = startY;

			for(String line : lines) {
				int currentX = startX;

				// Parse color tags per line (simple approach)
				// Supports <RED>, <BLUE>, <GREEN>, <WHITE>, <BLACK>, <GRAY>, <ORANGE>, <YELLOW>, <PURPLE>, <PINK>

				// Tokenize by '<' and '>'
				// But we need to keep text between tags.
				// Regex split keeping delimiters is hard in java split

				// Manual scan
				Color currentColor = g.getColor(); // Keep previous color across lines? usually resets per box in game logic, but tags persist.
				// Let's assume it persists.

				int lastIndex = 0;
				while(lastIndex < line.length()) {
					int tagStart = line.indexOf("<", lastIndex);
					if(tagStart != -1) {
						// Draw text before tag
						if(tagStart > lastIndex) {
							String segment = line.substring(lastIndex, tagStart);
							g.setColor(currentColor);
							g.drawString(segment, currentX, currentY);
							currentX += g.getFontMetrics().stringWidth(segment);
						}

						int tagEnd = line.indexOf(">", tagStart);
						if(tagEnd != -1) {
							String tag = line.substring(tagStart, tagEnd + 1);
							// Check if color tag
							if(tag.equals("<RED>")) currentColor = Color.RED;
							else if(tag.equals("<BLUE>")) currentColor = Color.BLUE;
							else if(tag.equals("<GREEN>")) currentColor = Color.GREEN;
							else if(tag.equals("<WHITE>")) currentColor = Color.WHITE;
							else if(tag.equals("<BLACK>")) currentColor = Color.DARK_GRAY; // Black on black bg is bad, use dark gray or fix bg
							else if(tag.equals("<GRAY>")) currentColor = Color.GRAY;
							else if(tag.equals("<ORANGE>")) currentColor = Color.ORANGE;
							else if(tag.equals("<YELLOW>")) currentColor = Color.YELLOW;
							else if(tag.equals("<PURPLE>")) currentColor = new Color(150,0,255);
							else if(tag.equals("<PINK>")) currentColor = Color.PINK;
							// Else ignore (control tag)

							lastIndex = tagEnd + 1;
						} else {
							// Malformed tag, just print rest
							String segment = line.substring(lastIndex);
							g.setColor(currentColor);
							g.drawString(segment, currentX, currentY);
							break;
						}
					} else {
						// No more tags
						String segment = line.substring(lastIndex);
						g.setColor(currentColor);
						g.drawString(segment, currentX, currentY);
						break;
					}
				}

				currentY += lineHeight;
			}

			g.setColor(Color.GRAY);
			g.drawRect(0, 0, getWidth()-1, getHeight()-1);
			g.drawString("Preview (Last Page)", getWidth() - 150, getHeight() - 5);
		}
	}

}
