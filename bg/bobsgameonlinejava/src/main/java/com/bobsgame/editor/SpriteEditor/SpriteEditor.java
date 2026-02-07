package com.bobsgame.editor.SpriteEditor;

import java.io.*;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;



import com.bobsgame.EditorMain;
import com.bobsgame.editor.InfoLabelPanel;
//import com.bobsgame.editor.MultipleTileEditor.MTECanvas;
import com.bobsgame.editor.Dialogs.NumberDialog;
import com.bobsgame.editor.Dialogs.RenameWindow;

import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.editor.Project.Sprite.SpritePalette;


//===============================================================================================
public class SpriteEditor extends JFrame implements ActionListener, ItemListener, KeyListener, MenuListener, ListSelectionListener, CaretListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public EditorMain E;
	private SESizeWindow SSW;
	private RenameWindow RW;
	private FileDialog filedialog;
	public static SECanvas editCanvas;
	public static SEFrameCanvas frameCanvas;
	protected JPanel topButtonPanel;
	protected static JPanel centerPanel;


	public static SEControlPanel controlPanel;
	public static SELayerPanel layerPanel;
	public static SEToolsPanel toolsPanel;
	public static SEHistoryPanel historyPanel;

	public static SEFrameControlPanel frameControlPanel;

	protected JPanel spriteButtonsPanel, paletteSelectPanel;

	private BoxLayout blayout;



	public JComboBox<String>
	//spriteChoice,
	spritePaletteChoice
	;



	protected JButton
	newSprite,
	renameSprite,
	resizeSprite,
	duplicateSprite,
	deleteSprite,
	newPalette,
	renamePalette,
	duplicatePalette,
	deletePalette,
	moveUpButton,
	moveDownButton,
	moveUpTenButton,
	moveDownTenButton
	;




	public JScrollPane editCanvasScrollPane;
	public static JScrollPane frameScrollPane;
	public JMenuBar menuBar;
	public JMenu fileMenu, spriteMenu, spacerMenu,closeMenu, helpSpriteMenu;

	public JMenuItem
	saveProject,
	loadProject,
	importAseprite,
	nextSpriteHelpMenu,
	nextFrameHelpMenu,
	removeUnusedSpritePalCols,
	mergeDuplicateSpritePalCols,
	sortSpritePalHSB,
	mergeSpritePalH,
	mergeSpritePalS,
	mergeSpritePalB,
	brightenSpritePalHSB,
	darkenSpritePalHSB,
	roundSpritePalHSB,
	openSpriteBitmapSplicer,
	sendSpriteToTiles,
	saveAllSpritesToPNG,
	saveRandomSpritesToPNG,
	saveSelectedSpriteToPNG,
	saveSelectedSpriteToHQ2XPNG,
	saveAllSpritesToHQ2XPNG,
	copySelectedSpriteToHQ2XSprite,
	saveSelectedSpriteToSpriteSheetPNG,
	importSpriteSheetPNG,
	moveSpriteUp,
	moveSpriteDown
	;


	JList<Sprite> spriteList;
	DefaultListModel<Sprite> spriteListModel;

	JCheckBox showNPCsCheckBox;
	JCheckBox showItemsCheckBox;
	JCheckBox showGamesCheckBox;
	JCheckBox showRandomsCheckBox;
	JCheckBox showDoorsCheckBox;
	JCheckBox showKidsCheckBox;
	JCheckBox showAdultsCheckBox;
	JCheckBox showMalesCheckBox;
	JCheckBox showFemalesCheckBox;
	JCheckBox showCarsCheckBox;
	JCheckBox showAnimalsCheckBox;

	JTextField filterTextField;
	String lastFilterString = "";


	public static JCheckBoxMenuItem
	showGrid,
	showHitBox,
	showUtilityPoint,
	mirrorMode,
	mirrorYMode,
	onionSkinMode

	;

	public InfoLabelPanel infoLabel;



	//===============================================================================================
	public SpriteEditor(EditorMain e)
	{//===============================================================================================

		super("Sprite Editor");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		E = e;

		menuBar = new JMenuBar();

		fileMenu = new JMenu("File");
		saveProject = new JMenuItem("Save Project (.sprproj)...");
		saveProject.addActionListener(this);
		loadProject = new JMenuItem("Open Project (.sprproj)...");
		loadProject.addActionListener(this);
		fileMenu.add(saveProject);
		fileMenu.add(loadProject);

		importAseprite = new JMenuItem("Import Aseprite (.ase)...");
		importAseprite.addActionListener(this);
		fileMenu.add(importAseprite);

		spriteMenu = new JMenu("Sprite Tools");
		spacerMenu = new JMenu("");

		closeMenu = new JMenu("Close -------------------------------------");

		closeMenu.addMenuListener(this);


		helpSpriteMenu = new JMenu(" ? ");

		menuBar.add(closeMenu);
		menuBar.add(fileMenu);
		//menuBar.add(spacerMenu);
		menuBar.add(spriteMenu);
		menuBar.add(helpSpriteMenu);


		moveSpriteUp = new JMenuItem("Move Sprite Up");
		moveSpriteUp.addActionListener(this);
		moveSpriteUp.setEnabled(true);
		moveSpriteUp.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_COMMA,InputEvent.CTRL_DOWN_MASK));

		moveSpriteDown = new JMenuItem("Move Sprite Down");
		moveSpriteDown.addActionListener(this);
		moveSpriteDown.setEnabled(true);
		moveSpriteDown.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_PERIOD,InputEvent.CTRL_DOWN_MASK));

		showGrid = new JCheckBoxMenuItem("Show Grid", false);
		showGrid.addItemListener(this);

		showHitBox = new JCheckBoxMenuItem("Show Hit Box", true);
		showHitBox.addItemListener(this);

		showUtilityPoint = new JCheckBoxMenuItem("Show Utility Point", true);
		showUtilityPoint.addItemListener(this);


		mirrorMode = new JCheckBoxMenuItem("Mirror Mode (X)", false);
		mirrorMode.addItemListener(this);
		mirrorMode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_M,InputEvent.CTRL_DOWN_MASK));

		mirrorYMode = new JCheckBoxMenuItem("Mirror Mode (Y)", false);
		mirrorYMode.addItemListener(this);
		mirrorYMode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_M,InputEvent.CTRL_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK));

		onionSkinMode = new JCheckBoxMenuItem("Onion Skinning", false);
		onionSkinMode.addItemListener(this);
		onionSkinMode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O,InputEvent.CTRL_DOWN_MASK));

		openSpriteBitmapSplicer = new JMenuItem("Load Bitmap Splicer");
		openSpriteBitmapSplicer.addActionListener(this);
		openSpriteBitmapSplicer.setEnabled(true);

		sendSpriteToTiles = new JMenuItem("Send Sprite To Tiles");
		sendSpriteToTiles.addActionListener(this);
		sendSpriteToTiles.setEnabled(true);
		sendSpriteToTiles.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_T,InputEvent.CTRL_DOWN_MASK));


		saveSelectedSpriteToPNG = new JMenuItem("Export Selected Sprite To PNG");
		saveSelectedSpriteToPNG.addActionListener(this);
		saveSelectedSpriteToPNG.setEnabled(true);

		saveSelectedSpriteToSpriteSheetPNG = new JMenuItem("Export Selected Sprite To Sprite Sheet PNG");
		saveSelectedSpriteToSpriteSheetPNG.addActionListener(this);
		saveSelectedSpriteToSpriteSheetPNG.setEnabled(true);
		saveSelectedSpriteToSpriteSheetPNG.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_P,InputEvent.CTRL_DOWN_MASK));

		importSpriteSheetPNG = new JMenuItem("Import Sprite Sheet PNG");
		importSpriteSheetPNG.addActionListener(this);
		importSpriteSheetPNG.setEnabled(true);


		saveAllSpritesToPNG = new JMenuItem("Export All Sprites To PNGs");
		saveAllSpritesToPNG.addActionListener(this);
		saveAllSpritesToPNG.setEnabled(true);

		saveRandomSpritesToPNG = new JMenuItem("Export Random Sprites To PNGs");
		saveRandomSpritesToPNG.addActionListener(this);
		saveRandomSpritesToPNG.setEnabled(true);

		copySelectedSpriteToHQ2XSprite = new JMenuItem("Duplicate Selected Sprite To HQ2XSprite");
		copySelectedSpriteToHQ2XSprite.addActionListener(this);
		copySelectedSpriteToHQ2XSprite.setEnabled(true);

		saveSelectedSpriteToHQ2XPNG = new JMenuItem("Export Selected Sprite To HQ2X PNG");
		saveSelectedSpriteToHQ2XPNG.addActionListener(this);
		saveSelectedSpriteToHQ2XPNG.setEnabled(true);

		saveAllSpritesToHQ2XPNG = new JMenuItem("Export All Sprites To HQ2X PNGs");
		saveAllSpritesToHQ2XPNG.addActionListener(this);
		saveAllSpritesToHQ2XPNG.setEnabled(true);

		removeUnusedSpritePalCols = new JMenuItem("Remove Unused Sprite Palette Colors");
		removeUnusedSpritePalCols.addActionListener(this);
		removeUnusedSpritePalCols.setEnabled(true);

		mergeDuplicateSpritePalCols = new JMenuItem("Merge Duplicate Sprite Palette Colors");
		mergeDuplicateSpritePalCols.addActionListener(this);
		mergeDuplicateSpritePalCols.setEnabled(true);

		sortSpritePalHSB = new JMenuItem("Sort Sprite Palette Colors by GRAY/HSB");
		sortSpritePalHSB.addActionListener(this);
		sortSpritePalHSB.setEnabled(true);

		mergeSpritePalH = new JMenuItem("Merge Sprite Palette Colors (HSB) H Within Percent...");
		mergeSpritePalH.addActionListener(this);
		mergeSpritePalH.setEnabled(true);

		mergeSpritePalS = new JMenuItem("Merge Sprite Palette Colors (HSB) S Within Percent...");
		mergeSpritePalS.addActionListener(this);
		mergeSpritePalS.setEnabled(true);

		mergeSpritePalB = new JMenuItem("Merge Sprite Palette Colors (HSB) B Within Percent...");
		mergeSpritePalB.addActionListener(this);
		mergeSpritePalB.setEnabled(true);

		brightenSpritePalHSB = new JMenuItem("Brighten Sprite Palette Colors (HSB)...");
		brightenSpritePalHSB.addActionListener(this);
		brightenSpritePalHSB.setEnabled(true);

		darkenSpritePalHSB = new JMenuItem("Darken Sprite Palette Colors (HSB)...");
		darkenSpritePalHSB.addActionListener(this);
		darkenSpritePalHSB.setEnabled(true);

		roundSpritePalHSB = new JMenuItem("Round Sprite Palette Colors (HSB)...");
		roundSpritePalHSB.addActionListener(this);
		roundSpritePalHSB.setEnabled(true);



		spriteMenu.add(showGrid);
		spriteMenu.add(showHitBox);
		spriteMenu.add(showUtilityPoint);
		spriteMenu.add(mirrorMode);
		spriteMenu.add(mirrorYMode);
		spriteMenu.add(onionSkinMode);
		spriteMenu.addSeparator();


		spriteMenu.add(moveSpriteUp);
		spriteMenu.add(moveSpriteDown);
		spriteMenu.addSeparator();

		spriteMenu.add(openSpriteBitmapSplicer);
		spriteMenu.add(sendSpriteToTiles);
		spriteMenu.addSeparator();

		spriteMenu.add(saveSelectedSpriteToPNG);
		spriteMenu.add(saveSelectedSpriteToSpriteSheetPNG);
		spriteMenu.add(importSpriteSheetPNG);
		spriteMenu.add(saveAllSpritesToPNG);
		spriteMenu.add(saveRandomSpritesToPNG);
		spriteMenu.add(copySelectedSpriteToHQ2XSprite);
		spriteMenu.add(saveSelectedSpriteToHQ2XPNG);
		spriteMenu.add(saveAllSpritesToHQ2XPNG);
		spriteMenu.addSeparator();



		spriteMenu.add(removeUnusedSpritePalCols);
		spriteMenu.add(mergeDuplicateSpritePalCols);
		spriteMenu.addSeparator();

		spriteMenu.add(sortSpritePalHSB);
		spriteMenu.add(roundSpritePalHSB);
		spriteMenu.add(mergeSpritePalH);
		spriteMenu.add(mergeSpritePalS);
		spriteMenu.add(mergeSpritePalB);
		spriteMenu.addSeparator();

		spriteMenu.add(brightenSpritePalHSB);
		spriteMenu.add(darkenSpritePalHSB);

		nextSpriteHelpMenu = new JMenuItem("[pgup][pgdn] Next/Previous Sprite");
		nextSpriteHelpMenu.setEnabled(false);
		helpSpriteMenu.add(nextSpriteHelpMenu);

		nextFrameHelpMenu = new JMenuItem("[a][s] Next/Previous Frame");
		nextFrameHelpMenu.setEnabled(false);
		helpSpriteMenu.add(nextFrameHelpMenu);

		helpSpriteMenu.add(new JMenuItem("[ctrl][f] Flip Horizontal"));
		helpSpriteMenu.add(new JMenuItem("[ctrl][r] Flip Vertical"));

		//add(menuBar,BorderLayout.NORTH);
		//setMenuBar(menuBar);






		topButtonPanel = new JPanel();
		blayout = new BoxLayout(topButtonPanel, BoxLayout.X_AXIS);
		topButtonPanel.setLayout(blayout);

		//spriteSelectPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));
		//spriteSelectPanel.setBorder(EditorMain.border);


			//spriteChoice = new Choice();
			//spriteChoice.addItemListener(this);
			//spriteChoice.setFocusable(false);

			//spriteChoice = new JComboBox<String>();
			//spriteChoice.addItemListener(this);
			//spriteChoice.setEditable(false);
			//spriteChoice.setMaximumRowCount(50);
			//spriteChoice.setFloatBuffered(false);
			//spriteChoice.setFocusable(false);

		//spriteSelectPanel.add(spriteChoice);



		paletteSelectPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 1));
		paletteSelectPanel.setBorder(EditorMain.border);

			//spritePaletteChoice = new Choice();
			//spritePaletteChoice.addItemListener(this);
			//spritePaletteChoice.setFocusable(false);
			spritePaletteChoice = new JComboBox<String>();
			spritePaletteChoice.setBackground(EditorMain.comboboxBackgroundColor);
			spritePaletteChoice.addItemListener(this);
			spritePaletteChoice.setEditable(false);
			spritePaletteChoice.setMaximumRowCount(50);
			spritePaletteChoice.setDoubleBuffered(false);

		paletteSelectPanel.add(spritePaletteChoice);

			newPalette = new JButton("New");
			newPalette.addActionListener(this);

		paletteSelectPanel.add(newPalette);

			renamePalette = new JButton("Rename");
			renamePalette.addActionListener(this);

		paletteSelectPanel.add(renamePalette);

			duplicatePalette = new JButton("Duplicate");
			duplicatePalette.addActionListener(this);

		paletteSelectPanel.add(duplicatePalette);

			deletePalette = new JButton("Delete");
			deletePalette.addActionListener(this);

		paletteSelectPanel.add(deletePalette);



		//topButtonPanel.add(spriteSelectPanel);

		toolsPanel = new SEToolsPanel(this);
		topButtonPanel.add(toolsPanel);

		topButtonPanel.add(paletteSelectPanel);

		JPanel topPanel = new JPanel(new GridLayout(0,1,0,0));
		topPanel.add(menuBar);
		topPanel.add(topButtonPanel);







		editCanvas = new SECanvas(this);
		frameCanvas = new SEFrameCanvas(this);
		filedialog = new FileDialog(this, "Select File", FileDialog.LOAD);
		SSW = new SESizeWindow(this);
		RW = new RenameWindow(this);




		centerPanel = new JPanel(new BorderLayout());
		frameScrollPane = new JScrollPane(frameCanvas, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		frameScrollPane.setFocusable(false);
		frameScrollPane.getViewport().setFocusable(false);
		frameScrollPane.setWheelScrollingEnabled(false);
		frameScrollPane.getViewport().setBackground(Color.DARK_GRAY);
		frameScrollPane.validate();
		centerPanel.add(frameScrollPane, BorderLayout.NORTH);


		editCanvasScrollPane = new JScrollPane(editCanvas);
		editCanvasScrollPane.getViewport().setBackground(Color.DARK_GRAY);
		centerPanel.add(editCanvasScrollPane, BorderLayout.CENTER);





		infoLabel = new InfoLabelPanel("Sprite Editor", E);
		infoLabel.setBackground(Color.BLACK);
		infoLabel.setForeground(Color.WHITE);
		infoLabel.text.setFont(new Font("Tahoma", Font.BOLD, 16));


		controlPanel = new SEControlPanel(this);
		layerPanel = new SELayerPanel(this);
		historyPanel = new SEHistoryPanel(this);

		JTabbedPane layerHistoryTabs = new JTabbedPane();
		layerHistoryTabs.addTab("Layers", layerPanel);
		layerHistoryTabs.addTab("History", historyPanel);

		JPanel rightPanel = new JPanel(new BorderLayout());
		rightPanel.add(controlPanel, BorderLayout.CENTER);
		rightPanel.add(layerHistoryTabs, BorderLayout.SOUTH);


		JPanel leftPanel = new JPanel(new BorderLayout());
		frameControlPanel = new SEFrameControlPanel(this);

		leftPanel.setPreferredSize(new Dimension(300,2000));
		leftPanel.setMaximumSize(new Dimension(300,2000));
		leftPanel.add(frameControlPanel,BorderLayout.CENTER);



		Font buttonFont = new Font("Tahoma", Font.PLAIN, 9);
		spriteButtonsPanel = new JPanel(new GridLayout(0,1));
		spriteButtonsPanel.setBorder(EditorMain.border);

			newSprite = new JButton("New");
			newSprite.setFont(buttonFont);
			newSprite.addActionListener(this);

		spriteButtonsPanel.add(newSprite);

			renameSprite = new JButton("Rename");
			renameSprite.setFont(buttonFont);
			renameSprite.addActionListener(this);

		spriteButtonsPanel.add(renameSprite);

			resizeSprite = new JButton("Resize");
			resizeSprite.setFont(buttonFont);
			resizeSprite.addActionListener(this);

		spriteButtonsPanel.add(resizeSprite);

			duplicateSprite = new JButton("Duplicate");
			duplicateSprite.setFont(buttonFont);
			duplicateSprite.addActionListener(this);

		spriteButtonsPanel.add(duplicateSprite);

			deleteSprite = new JButton("Delete");
			deleteSprite.setFont(buttonFont);
			deleteSprite.addActionListener(this);

		spriteButtonsPanel.add(deleteSprite);



		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);
		spriteListModel = new DefaultListModel<Sprite>();
		spriteList = new JList<Sprite>(spriteListModel);
		spriteList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		spriteList.setLayoutOrientation(JList.VERTICAL);
		spriteList.setVisibleRowCount(500);
		spriteList.setForeground(Color.BLACK);
		spriteList.setFont(listFont);
		spriteList.setFixedCellHeight(16);
		spriteList.addListSelectionListener(this);
		spriteList.setFocusable(false);

		spriteList.setCellRenderer(new NameCellRenderer());
		JScrollPane spriteListScroller = new JScrollPane(spriteList);
		spriteListScroller.setBorder(EditorMain.border);
		spriteListScroller.setFocusable(false);

		spriteListScroller.setMaximumSize(new Dimension(260,2000));

		JPanel spriteListPanel = new JPanel();
		spriteListPanel.setBorder(EditorMain.border);
		spriteListPanel.setLayout(new BoxLayout(spriteListPanel,BoxLayout.Y_AXIS));
		spriteListPanel.add(Box.createRigidArea(new Dimension(100,0)));



		JPanel spriteFilterStuffPanel = new JPanel();
		spriteFilterStuffPanel.setBorder(EditorMain.border);
		spriteFilterStuffPanel.setLayout(new BoxLayout(spriteFilterStuffPanel,BoxLayout.Y_AXIS));

		JPanel checkBoxPanel = new JPanel(new GridLayout(0,3));
		checkBoxPanel.setBorder(EditorMain.border);

		showNPCsCheckBox = new JCheckBox("NPCs");
		showNPCsCheckBox.setSelected(false);
		showNPCsCheckBox.addItemListener(this);
		checkBoxPanel.add(showNPCsCheckBox);

		showItemsCheckBox = new JCheckBox("Items");
		showItemsCheckBox.setSelected(false);
		showItemsCheckBox.addItemListener(this);
		checkBoxPanel.add(showItemsCheckBox);

		showGamesCheckBox = new JCheckBox("Games");
		showGamesCheckBox.setSelected(false);
		showGamesCheckBox.addItemListener(this);
		checkBoxPanel.add(showGamesCheckBox);

		showRandomsCheckBox = new JCheckBox("Randoms");
		showRandomsCheckBox.setSelected(false);
		showRandomsCheckBox.addItemListener(this);
		checkBoxPanel.add(showRandomsCheckBox);

		showDoorsCheckBox = new JCheckBox("Doors");
		showDoorsCheckBox.setSelected(false);
		showDoorsCheckBox.addItemListener(this);
		checkBoxPanel.add(showDoorsCheckBox);

		showKidsCheckBox = new JCheckBox("Kids");
		showKidsCheckBox.setSelected(false);
		showKidsCheckBox.addItemListener(this);
		checkBoxPanel.add(showKidsCheckBox);

		showAdultsCheckBox = new JCheckBox("Adults");
		showAdultsCheckBox.setSelected(false);
		showAdultsCheckBox.addItemListener(this);
		checkBoxPanel.add(showAdultsCheckBox);

		showMalesCheckBox = new JCheckBox("Males");
		showMalesCheckBox.setSelected(false);
		showMalesCheckBox.addItemListener(this);
		checkBoxPanel.add(showMalesCheckBox);

		showFemalesCheckBox = new JCheckBox("Females");
		showFemalesCheckBox.setSelected(false);
		showFemalesCheckBox.addItemListener(this);
		checkBoxPanel.add(showFemalesCheckBox);

		showCarsCheckBox = new JCheckBox("Cars");
		showCarsCheckBox.setSelected(false);
		showCarsCheckBox.addItemListener(this);
		checkBoxPanel.add(showCarsCheckBox);

		showAnimalsCheckBox = new JCheckBox("Animals");
		showAnimalsCheckBox.setSelected(false);
		showAnimalsCheckBox.addItemListener(this);
		checkBoxPanel.add(showAnimalsCheckBox);


		JPanel filterPanel = new JPanel();
		JLabel filterLabel = new JLabel("Filter");
		filterTextField = new JTextField(20);
		filterTextField.addCaretListener(this);
		filterPanel.add(filterLabel);
		filterPanel.add(filterTextField);



		JPanel reorderPanel = new JPanel(new GridLayout(0,2));
		reorderPanel.setBorder(EditorMain.border);

		moveUpButton = new JButton("Up");
		moveUpButton.setFont(buttonFont);
		moveUpButton.addActionListener(this);
		moveDownButton = new JButton("Down");
		moveDownButton.setFont(buttonFont);
		moveDownButton.addActionListener(this);
		moveUpTenButton = new JButton("Up 10");
		moveUpTenButton.setFont(buttonFont);
		moveUpTenButton.addActionListener(this);
		moveDownTenButton = new JButton("Down 10");
		moveDownTenButton.setFont(buttonFont);
		moveDownTenButton.addActionListener(this);

		reorderPanel.add(moveUpButton);
		reorderPanel.add(moveDownButton);
		reorderPanel.add(moveUpTenButton);
		reorderPanel.add(moveDownTenButton);


		spriteFilterStuffPanel.add(filterPanel);
		spriteFilterStuffPanel.add(checkBoxPanel);

		spriteListPanel.add(spriteButtonsPanel);
		spriteListPanel.add(spriteFilterStuffPanel);
		spriteListPanel.add(reorderPanel);
		spriteListPanel.add(spriteListScroller);




		rightPanel.add(spriteListPanel,BorderLayout.EAST);



		setLayout(new BorderLayout());
		add(topPanel, BorderLayout.NORTH);
		add(leftPanel, BorderLayout.WEST);
		add(rightPanel, BorderLayout.EAST);
		add(centerPanel, BorderLayout.CENTER);
		add(infoLabel, BorderLayout.SOUTH);



		updateInfo();






		setLocation(65, 0);
		setSize(EditorMain.getScreenWidth()-360, EditorMain.getScreenHeight()-40);


		setFocusable(true);
		addKeyListener(this);
		recursivelyAddKeyListener(this);
		recursivelyRemoveKeyListener(topPanel);


	}
	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{

			c[i].removeKeyListener(this);

			if(
					c[i].getClass()!=TextArea.class&&
					c[i].getClass()!=TextField.class
			)
			{
				c[i].setFocusable(true);
				c[i].addKeyListener(this);

			}

			if(c[i].getClass().equals(JPanel.class))
			{
				recursivelyAddKeyListener((Container) c[i]);
			}

		}

	}


	//===============================================================================================
	public void recursivelyRemoveKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{

			c[i].removeKeyListener(this);
			c[i].setFocusable(false);

			if(c[i].getClass().equals(JPanel.class))
			{
				recursivelyRemoveKeyListener((Container) c[i]);
			}
		}
	}



	//===============================================================================================
	public void showSpriteEditor()
	{//===============================================================================================
		updateInfo();
		editCanvas.repaintBufferImage();
		editCanvas.repaint();
		repaint();
		setVisible(true);

	}



	//===============================================================================================
	public void disableButtons()
	{//===============================================================================================
		newSprite.setEnabled(true);

		renameSprite.setEnabled(false);
		resizeSprite.setEnabled(false);
		duplicateSprite.setEnabled(false);
		deleteSprite.setEnabled(false);
		newPalette.setEnabled(true);

		renamePalette.setEnabled(false);
		duplicatePalette.setEnabled(false);
		deletePalette.setEnabled(false);

	}



	//===============================================================================================
	public void updateInfo()
	{//===============================================================================================


		Sprite spriteChoiceSelected = spriteList.getSelectedValue();

		disableButtons();



		spriteListModel.removeAllElements();
		for(int i=0;i<Project.getNumSprites();i++)
		{
			Sprite s = Project.getSprite(i);

			if(showNPCsCheckBox.isSelected()==false||s.isNPC()==true)
			if(showItemsCheckBox.isSelected()==false||s.isItem()==true)
			if(showGamesCheckBox.isSelected()==false||s.isGame()==true)
			if(showRandomsCheckBox.isSelected()==false||s.isRandom()==true)
			if(showDoorsCheckBox.isSelected()==false||s.isDoor()==true)
			if(showKidsCheckBox.isSelected()==false||s.isKid()==true)
			if(showAdultsCheckBox.isSelected()==false||s.isAdult()==true)
			if(showMalesCheckBox.isSelected()==false||s.isMale()==true)
			if(showFemalesCheckBox.isSelected()==false||s.isFemale()==true)
			if(showCarsCheckBox.isSelected()==false||s.isCar()==true)
			if(showAnimalsCheckBox.isSelected()==false||s.isAnimal()==true)
			spriteListModel.addElement(s);

		}


		filterDestinationList();


		spritePaletteChoice.removeAllItems();

		for(int i = 0; i < Project.getNumSpritePalettes(); i++)
		{
			spritePaletteChoice.addItem(Project.getSpritePalette(i).name);
		}
		if(Project.getNumSprites() > 0)
		{

			renameSprite.setEnabled(true);
			resizeSprite.setEnabled(true);
			duplicateSprite.setEnabled(true);
			deleteSprite.setEnabled(true);
			sendSpriteToTiles.setEnabled(true);


			if(spriteChoiceSelected!=null&&spriteListModel.contains(spriteChoiceSelected))
			spriteList.setSelectedValue(spriteChoiceSelected,true);
			else spriteList.setSelectedIndex(0);



			Project.setSelectedSprite(spriteList.getSelectedValue());
			getSprite().setFrame(0);
			editCanvas.editBufferImage=null;
			frameControlPanel.updateSpriteInfo();
			frameControlPanel.updateFrames();
			layerPanel.updateLayerList();
			editCanvas.repaintBufferImage();
			//editCanvas.initUndo();
			editCanvas.repaint();

			setFrameCanvasHeight();



		}
		if(Project.getNumSpritePalettes() > 0)
		{
			renamePalette.setEnabled(true);
			duplicatePalette.setEnabled(true);
			deletePalette.setEnabled(true);
			spritePaletteChoice.setSelectedItem(Project.getSelectedSpritePaletteName());
		}
		refreshTopPanelLayout();
		repaint();
	}



	//===============================================================================================
	public void refreshTopPanelLayout()
	{//===============================================================================================
		blayout.invalidateLayout(topButtonPanel);
		topButtonPanel.validate();
		//spriteChoice.validate();
		spritePaletteChoice.validate();
		spriteButtonsPanel.validate();
		paletteSelectPanel.validate();

	}




	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == newSprite)newSprite();
		else if(ae.getSource() == renameSprite)renameSprite();
		else if(ae.getSource() == resizeSprite)resizeSprite();
		else if(ae.getSource() == duplicateSprite)duplicateSprite();
		else if(ae.getSource() == deleteSprite)deleteSprite();

		else if(ae.getSource() == newPalette)newPalette();
		else if(ae.getSource() == renamePalette)renamePalette();
		else if(ae.getSource() == duplicatePalette)duplicatePalette();
		else if(ae.getSource() == deletePalette)deletePalette();
		else if(ae.getSource() == openSpriteBitmapSplicer)bitmapSprite();
		else if(ae.getSource() == sendSpriteToTiles)sendToTiles();

		else if(ae.getSource() == saveProject)saveProjectAction();
		else if(ae.getSource() == loadProject)loadProjectAction();
		else if(ae.getSource() == importAseprite)importAsepriteAction();

		else if(ae.getSource() == moveSpriteUp)moveSpriteUp();
		else if(ae.getSource() == moveSpriteDown)moveSpriteDown();

		else if(ae.getSource() == moveUpButton)moveSpriteUp();
		else if(ae.getSource() == moveDownButton)moveSpriteDown();
		else if(ae.getSource() == moveUpTenButton){for(int i=0;i<10;i++)moveSpriteUp();}
		else if(ae.getSource() == moveDownTenButton){for(int i=0;i<10;i++)moveSpriteDown();}


		else if(ae.getSource() == copySelectedSpriteToHQ2XSprite)copySelectedSpriteToHQ2XSprite();
		else if(ae.getSource() == saveSelectedSpriteToPNG)saveSelectedSpriteToPNG();
		else if(ae.getSource() == saveSelectedSpriteToSpriteSheetPNG)saveSelectedSpriteToSpriteSheetPNG();
		else if(ae.getSource() == importSpriteSheetPNG)importSpriteSheetPNG();
		else if(ae.getSource() == saveAllSpritesToPNG)saveAllSpritesToPNG();
		else if(ae.getSource() == saveRandomSpritesToPNG)saveRandomSpritesToPNG();
		else if(ae.getSource() == saveSelectedSpriteToHQ2XPNG)saveSelectedSpriteToHQ2XPNG();
		else if(ae.getSource() == saveAllSpritesToHQ2XPNG)saveAllSpritesToHQ2XPNG();


		else if(ae.getSource() == removeUnusedSpritePalCols)removeUnusedSpritePalCols();
		else if(ae.getSource() == mergeDuplicateSpritePalCols)mergeDuplicateSpritePalCols();
		else if(ae.getSource() == sortSpritePalHSB)sortSpritePalHSB();
		else if(ae.getSource() == mergeSpritePalH)mergeSpritePalH();
		else if(ae.getSource() == mergeSpritePalS)mergeSpritePalS();
		else if(ae.getSource() == mergeSpritePalB)mergeSpritePalB();
		else if(ae.getSource() == brightenSpritePalHSB)brightenSpritePalHSB();
		else if(ae.getSource() == darkenSpritePalHSB)darkenSpritePalHSB();
		else if(ae.getSource() == roundSpritePalHSB)roundSpritePalHSB();


	}


	//===============================================================================================
	public static Sprite getSprite()
	{//===============================================================================================

		return Project.getSelectedSprite();
	}

	//===============================================================================================
	public static void setFrameCanvasHeight()
	{//===============================================================================================
		int w = getSprite().wP()*4;
		int h = getSprite().hP()*4;
		int f = getSprite().frames();


		Dimension frameCanvasSize = new Dimension((w*f)+(f*1),h+40);
		frameCanvas.setSize(frameCanvasSize);
		frameCanvas.setMaximumSize(frameCanvasSize);
		frameCanvas.setMinimumSize(frameCanvasSize);
		frameCanvas.setPreferredSize(frameCanvasSize);

		frameCanvas.repaint();
		frameScrollPane.validate();
		//if(frameCanvas.getHeight()+22<600)frameScrollPane.setPreferredSize(new Dimension(frameScrollPane.getWidth(),frameCanvas.getHeight()+22));
		//frameScrollPane.validate();
		centerPanel.validate();

	}

	//===============================================================================================
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================
//		if(ie.getSource() == spriteChoice)
//		{
//			if(ie.getItem().equals(Project.getSelectedSpriteName())==false)//dont change to the sprite we're already on
//			if(spriteChoice.getSelectedIndex() >= 0)
//			{
//				Project.setSelectedSpriteIndex(spriteChoice.getSelectedIndex());
//				getSprite().setFrame(0);
//				editCanvas.editBufferImage=null;
//				frameControlPanel.updateSpriteInfo();
//				frameControlPanel.updateFrames();
//				editCanvas.repaintBufferImage();
//				editCanvas.initUndo();
//				editCanvas.repaint();
//
//
//
//				setFrameCanvasHeight();
//
//
//
//			}
//		}
//		else
		if(ie.getSource() == spritePaletteChoice)
		{
			if(spritePaletteChoice.getSelectedIndex() >= 0)
			{
				Project.setSelectedSpritePaletteIndex(spritePaletteChoice.getSelectedIndex());
				controlPanel.paletteCanvas.setColorsPerColumn();

				setFrameCanvasHeight();

			}
			controlPanel.repaint();
			editCanvas.repaintBufferImage();
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == showGrid)
		{
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == showHitBox)
		{
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == showUtilityPoint)
		{
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == mirrorMode)
		{
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == mirrorYMode)
		{
			editCanvas.repaint();
		}
		else
		if(ie.getSource() == onionSkinMode)
		{
			editCanvas.repaintBufferImage();
			editCanvas.repaint();
		}
		else
		{
			if(
					ie.getSource() ==  showNPCsCheckBox
					||ie.getSource() ==   showItemsCheckBox
					||ie.getSource() ==   showGamesCheckBox
					||ie.getSource() ==   showRandomsCheckBox
					||ie.getSource() ==   showDoorsCheckBox
					||ie.getSource() ==   showKidsCheckBox
					||ie.getSource() ==   showAdultsCheckBox
					||ie.getSource() ==   showMalesCheckBox
					||ie.getSource() ==   showFemalesCheckBox
					||ie.getSource() ==   showCarsCheckBox
					||ie.getSource() ==   showAnimalsCheckBox

			)updateInfo();


		}

	}
	//===============================================================================================
	public void moveSpriteUp()
	{//===============================================================================================

		Sprite selected = spriteList.getSelectedValue();
		int selectedIndex = spriteList.getSelectedIndex();

		if(selected!=null&&selectedIndex>0)
		{
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(selected==Project.getSprite(i))
				{
					Project.setSelectedSpriteIndex(i);

					if(i==1||i==Project.getNumSprites()-1)Project.moveSpriteUp();
					else
					while(Project.getSprite(Project.getSelectedSpriteIndex()+1)!=spriteListModel.getElementAt(selectedIndex-1))Project.moveSpriteUp();

					spriteListModel.remove(selectedIndex);
					spriteListModel.add(selectedIndex-1,selected);
					spriteList.setSelectedValue(selected,true);
					break;
				}
			}
		}
		editCanvas.repaintBufferImage();
		//editCanvas.initUndo();
		editCanvas.repaint();
	}
	//===============================================================================================
	public void moveSpriteDown()
	{//===============================================================================================

		Sprite selected = spriteList.getSelectedValue();
		int selectedIndex = spriteList.getSelectedIndex();

		if(selected!=null&&selectedIndex<spriteListModel.getSize()-1)
		{
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(selected==Project.getSprite(i))
				{
					Project.setSelectedSpriteIndex(i);

					if(i==0||i==Project.getNumSprites()-2)Project.moveSpriteDown();
					else
					while(Project.getSprite(Project.getSelectedSpriteIndex()-1)!=spriteListModel.getElementAt(selectedIndex+1))Project.moveSpriteDown();

					spriteListModel.remove(selectedIndex);
					spriteListModel.add(selectedIndex+1, selected);
					spriteList.setSelectedValue(selected,true);
					break;

				}
			}
		}
		editCanvas.repaintBufferImage();
		//editCanvas.initUndo();
		editCanvas.repaint();
	}

	//===============================================================================================
	public void newSprite()
	{//===============================================================================================

		Sprite s = new Sprite("Sprite"+Project.getNumSprites(),1,16,32);

		spriteListModel.addElement(s);
		spriteList.setSelectedIndex(spriteListModel.size()-1);


		updateInfo();

	}


	//===============================================================================================
	public void renameSprite()
	{//===============================================================================================

		RW.show(Project.getSelectedSpriteName());
		if(!RW.wasCancelled)
		{
			getSprite().setName(RW.newName.getText());
		}
		updateInfo();
	}

	//===============================================================================================
	public void resizeSprite()
	{//===============================================================================================
		SSW.show();
	}

	//===============================================================================================
	public void duplicateSprite()
	{//===============================================================================================

		Sprite s = getSprite().duplicate();

		updateInfo();

	}



	//===============================================================================================
	public void deleteSprite()
	{//===============================================================================================
		if(Project.getNumSprites()<=1)return;

		Project.deleteSprite();
		updateInfo();

	}


	//===============================================================================================
	public void newPalette()
	{//===============================================================================================
		Project.createNewSpritePalette();
		spritePaletteChoice.addItem(Project.getSelectedSpritePaletteName());
		spritePaletteChoice.setSelectedItem(Project.getSelectedSpritePaletteName());
		updateInfo();
		controlPanel.repaint();
		editCanvas.repaintBufferImage();
		editCanvas.repaint();
	}


	//===============================================================================================
	public void renamePalette()
	{//===============================================================================================
		// RENAMING WINDOW
		RW.show(Project.getSelectedSpritePaletteName());
		if(!RW.wasCancelled)
		{
			Project.renameSpritePalette(RW.newName.getText());
		}
		updateInfo();
	}

	//===============================================================================================
	public void duplicatePalette()
	{//===============================================================================================
		Project.duplicateSpritePalette();

		updateInfo();
	}

	//===============================================================================================
	public void deletePalette()
	{//===============================================================================================
		if(Project.getNumSpritePalettes() <= 1)return;
		Project.deleteSpritePalette();
		updateInfo();
		controlPanel.repaint();
	}

	//===============================================================================================
	public void bitmapSprite()
	{//===============================================================================================
		new SEBitmapSpriteLoader(this);
	}

	//===============================================================================================
	public void sendToTiles()
	{//===============================================================================================
		getSprite().sendToTiles(E);
	}



	//===============================================================================================
	public void saveSelectedSpriteToPNG()
	{//===============================================================================================

		getSprite().outputPNG(EditorMain.getDesktopTempDirPath());

		infoLabel.setTextSuccess("Saved Sprite To PNG " + EditorMain.getDesktopTempDirPath());

	}
	//===============================================================================================
	public void saveSelectedSpriteToSpriteSheetPNG()
	{//===============================================================================================
		getSprite().outputSpriteSheetPNG(E);//EditorMain.getDesktopTempDirPath(), E);

		infoLabel.setTextSuccess("Saved Sprite To PNG " + EditorMain.getDesktopTempDirPath());
	}

	//===============================================================================================
	public void importSpriteSheetPNG()
	{//===============================================================================================












		//open file dialog
		filedialog = new FileDialog(this, "Select File", FileDialog.LOAD);
		filedialog.setTitle("Load PNG File");
		filedialog.setVisible(true);

		//load png from filename into buffered image
		BufferedImage image = null;

		try
		{
			image = ImageIO.read(new File(filedialog.getDirectory()+filedialog.getFile()));
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return;
		}



		//determine png size, width, height
		int width = image.getWidth();
		int height = image.getHeight();

		//assume 8 frames vertical, one pixel space in between

		//figure out width

		//figure out frame height

		int frameHeight = (height-7)/8;

		int frameWidth = 16;
		//if(frameHeight>32)frameWidth = 32;


		//figure out number of directions by columns

		int directions = width / frameWidth;



		//for each column, add a frame name

		//add default hit box

		//go through each frame, column by column

		//make new frame


		int framesPerDirection = 8;

		int borderSize = 1;

		int totalFrames = framesPerDirection * directions;




		Sprite s = new Sprite("Sprite" + Project.getNumSprites(), totalFrames, frameWidth, frameHeight);
		s.setIsNPC(true);
		s.setHasShadow(true);

		Project.setSelectedSpriteIndex(Project.getNumSprites()-1);


			for(int f = 0; f < totalFrames; f++)
			{

				//initialize the full cropped sprite
				for(int x = 0; x < frameWidth; x++)
				{
					for(int y = 0; y < frameHeight; y++)
					{
						s.setPixel(f, x, y, 0);
					}
				}


				int fx = (f / framesPerDirection) * (frameWidth + borderSize);
				int fy = ((frameHeight + borderSize) * ((f % framesPerDirection)));
				//for(int fy=0;fy<verticaldivisions;fy++)
				//{
				// For each pixel in the frame
				for(int y = 0; y < frameHeight; y++)
				{
					for(int x = 0; x < frameWidth; x++)
					{
						// Get the RGB values of the pixel
						int rgb = image.getRGB(fx + x, fy + y);
						Color c = new Color(rgb);
						int r = c.getRed();
						int g = c.getGreen();
						int b = c.getBlue();
						// Compare the values to those in the palette
						int palcol = Project.getSelectedSpritePalette().findColor(r, g, b);

						//look through palette, find color match, add if not exist.
						// If palette color doesnt exist, add it
						if(palcol == -1)
						{
							palcol = Project.getSelectedSpritePalette().addColor(r, g, b);
							if(palcol == -1)
							{
								palcol = 0;               // If palette is full, set to background color
							}
						}


						// Set the proper pixel in the new sprite object
						s.setPixel(f, x, y, palcol);


						//frame++;
					}
				}
				//}
			}





			if(frameHeight==32)
			{

				s.getData().addAnimation("Down",0,2,1,24,0);
				s.getData().addAnimation("Up",8,2,1,24,0);
				s.getData().addAnimation("Left",16,2,1,24,0);
				s.getData().addAnimation("Right",24,2,1,24,0);

				if(directions>4)
				{
					s.getData().addAnimation("UpLeft",32,2,1,24,0);
					s.getData().addAnimation("UpRight",40,2,1,24,0);
					s.getData().addAnimation("DownRight",48,2,1,24,0);
					s.getData().addAnimation("DownLeft",56,2,1,24,0);
				}
			}
			else
			{

				s.getData().addAnimation("Down",0,0,0,31,0);
				s.getData().addAnimation("Up",8,0,0,31,0);
				s.getData().addAnimation("Left",16,0,0,31,0);
				s.getData().addAnimation("Right",24,0,0,31,0);

				if(directions>4)
				{
					s.getData().addAnimation("UpLeft",32,0,0,31,0);
					s.getData().addAnimation("UpRight",40,0,0,31,0);
					s.getData().addAnimation("DownRight",48,0,0,31,0);
					s.getData().addAnimation("DownLeft",56,0,0,31,0);
				}
			}



		spriteListModel.addElement(s);
		spriteList.setSelectedIndex(spriteListModel.size()-1);


		//spriteChoice.addItem(Project.getSelectedSpriteName());
		//spriteChoice.setSelectedItem(Project.getSelectedSpriteName());
		//spriteChoice.validate();
		updateInfo();
		editCanvas.repaintBufferImage();
		//editCanvas.initUndo();
		editCanvas.repaint();

	}

	//===============================================================================================
	public void saveAllSpritesToPNG()
	{//===============================================================================================
		for(int q = 0; q < Project.getNumSprites(); q++)
		{
			Project.getSprite(q).outputPNG(EditorMain.getFileDialogDirectoryPath());
		}

		infoLabel.setTextSuccess("Saved all Sprites To PNG " + EditorMain.getFileDialogDirectoryPath());

	}

	//===============================================================================================
	public void saveRandomSpritesToPNG()
	{//===============================================================================================
		for(int q = 0; q < Project.getNumSprites(); q++)
		{
			Sprite s = Project.getSprite(q);
			if(s.isRandom()) {
				s.outputPNG(EditorMain.getFileDialogDirectoryPath());
			}
		}

		infoLabel.setTextSuccess("Saved Random Sprites To PNG " + EditorMain.getFileDialogDirectoryPath());

	}

	//===============================================================================================
	public void copySelectedSpriteToHQ2XSprite()
	{//===============================================================================================

		getSprite().duplicateToHQ2XSprite();


		updateInfo();

		infoLabel.setTextSuccess("Duplicated Sprite to HQ2X Sprite");

	}

	//===============================================================================================
	public void saveSelectedSpriteToHQ2XPNG()
	{//===============================================================================================

		getSprite().outputHQ2XPNG(EditorMain.getFileDialogDirectoryPath(), E);


		infoLabel.setTextSuccess("Saved Sprite To HQ2X PNG " + EditorMain.getFileDialogDirectoryPath());

	}
	//===============================================================================================
	public void saveAllSpritesToHQ2XPNG()
	{//===============================================================================================
		for(int q = 0; q < Project.getNumSprites(); q++)
		{
			Project.getSprite(q).outputHQ2XPNG(EditorMain.getFileDialogDirectoryPath(), E);
		}

		infoLabel.setTextSuccess("Saved All Sprites To HQ2X PNG " + EditorMain.getFileDialogDirectoryPath());

	}

	//===============================================================================================
	public SpritePalette getSpritePal()
	{//===============================================================================================
		return Project.getSelectedSpritePalette();
	}

	//===============================================================================================
	public void sortSpritePalHSB()
	{//===============================================================================================


		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		for(int c1 = start; c1 < end; c1++) //sort hue
		{
			for(int c2 = end - 1; c2 > c1; c2--)
			{
				if((getSpritePal().hsbi[c2][0] < getSpritePal().hsbi[c1][0]))
				{

					getSpritePal().swapColor(c1, c2);
					swapSpriteColorsEverySprite(c2, c1);
				}
			}
		}

		for(int c1 = start; c1 < end; c1++) //sort s
		{
			for(int c2 = end - 1; c2 > c1; c2--)
			{
				if((getSpritePal().hsbi[c2][0]) == (getSpritePal().hsbi[c1][0])
					&& getSpritePal().hsbi[c2][1] <= getSpritePal().hsbi[c1][1])
				{

					getSpritePal().swapColor(c1, c2);
					swapSpriteColorsEverySprite(c2, c1);
				}
			}
		}

		for(int c1 = start; c1 < end; c1++) //sort b
		{
			for(int c2 = end - 1; c2 > c1; c2--)
			{
				if((getSpritePal().hsbi[c2][0]) == (getSpritePal().hsbi[c1][0])
					&& (getSpritePal().hsbi[c2][1]) == (getSpritePal().hsbi[c1][1])
					&& getSpritePal().hsbi[c2][2] <= getSpritePal().hsbi[c1][2])
				{
					getSpritePal().swapColor(c1, c2);
					swapSpriteColorsEverySprite(c2, c1);
				}
			}
		}

		controlPanel.repaint();
		infoLabel.setTextSuccess("Sorted Sprite Palette Colors By HSB");
	}



	//===============================================================================================
	public void mergeSpritePalH()
	{//===============================================================================================


		NumberDialog nd = new NumberDialog(new Frame(), "Within Amt 1-255");
		nd.text.setText("16");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		int c1 = 0;
		int c2 = 0;
		for(c1 = start; c1 < end; c1++) //sort hue
		{
			for(c2 = end - 1; c2 > c1; c2--)
			{
				if(getSpritePal().hsbi[c2][0] < getSpritePal().hsbi[c1][0])
				{

					if(((getSpritePal().hsbi[c1][0]) != 0 || (getSpritePal().hsbi[c1][1]) != 0 || (getSpritePal().hsbi[c1][2]) != 0)
						&& ((getSpritePal().hsbi[c2][0]) != 0 || (getSpritePal().hsbi[c2][1]) != 0 || (getSpritePal().hsbi[c2][2]) != 0))
					{
						if(((getSpritePal().hsbi[c1][0]) - (getSpritePal().hsbi[c2][0])) <= amount)
						{

							getSpritePal().hsbi[c2][0] += ((getSpritePal().hsbi[c1][0] - getSpritePal().hsbi[c2][0]) / 2);

							for(int a = start; a > getSpritePal().numColors; a++)
							{
								if(a != c1
									&& (getSpritePal().hsbi[a][0]) == (getSpritePal().hsbi[c1][0]))
								{
									getSpritePal().hsbi[a][0] = getSpritePal().hsbi[c2][0];
								}

							}

							getSpritePal().hsbi[c1][0] = getSpritePal().hsbi[c2][0];
						}
					}
				}
			}
		}

		for(int f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);

		}

		controlPanel.repaint();

		infoLabel.setTextSuccess("Merged Sprite Palette H By " + amount);
	}

	//===============================================================================================
	public void mergeSpritePalS()
	{//===============================================================================================


		NumberDialog nd = new NumberDialog(new Frame(), "Within Amt 1-255");
		nd.text.setText("16");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		for(int c1 = start; c1 < end; c1++) //sort s
		{
			for(int c2 = end - 1; c2 > c1; c2--)
			{
				if((getSpritePal().hsbi[c2][0]) == (getSpritePal().hsbi[c1][0])
					&& getSpritePal().hsbi[c2][1] < getSpritePal().hsbi[c1][1])
				{
					if(((getSpritePal().hsbi[c1][0]) != 0 || (getSpritePal().hsbi[c1][1]) != 0 || (getSpritePal().hsbi[c1][2]) != 0)
						&& ((getSpritePal().hsbi[c2][0]) != 0 || (getSpritePal().hsbi[c2][1]) != 0 || (getSpritePal().hsbi[c2][2]) != 0))
					{
						if(((((getSpritePal().hsbi[c1][1])) - ((getSpritePal().hsbi[c2][1]))) <= amount))
						{

							getSpritePal().hsbi[c2][1] += ((getSpritePal().hsbi[c1][1] - getSpritePal().hsbi[c2][1]) / 2);

							for(int a = start; a > getSpritePal().numColors; a++)
							{
								if(a != c1
									&& (getSpritePal().hsbi[a][0]) == (getSpritePal().hsbi[c1][0])
									&& (getSpritePal().hsbi[a][1]) == (getSpritePal().hsbi[c1][1]))
								{
									getSpritePal().hsbi[a][1] = getSpritePal().hsbi[c2][1];
								}

							}

							getSpritePal().hsbi[c1][1] = getSpritePal().hsbi[c2][1];
						}
					}
				}
			}
		}

		for(int f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);
		}

		controlPanel.repaint();
		infoLabel.setTextSuccess("Merged Sprite Palette S By " + amount);
	}

	//===============================================================================================
	public void mergeSpritePalB()
	{//===============================================================================================


		NumberDialog nd = new NumberDialog(new Frame(), "Within Amt 1-255");
		nd.text.setText("16");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		for(int c1 = start; c1 < end; c1++) //sort b
		{
			for(int c2 = end - 1; c2 > c1; c2--)
			{
				if((getSpritePal().hsbi[c2][0]) == (getSpritePal().hsbi[c1][0])
					&& (getSpritePal().hsbi[c2][1]) == (getSpritePal().hsbi[c1][1])
					&& getSpritePal().hsbi[c2][2] < getSpritePal().hsbi[c1][2])
				{
					if(((getSpritePal().hsbi[c1][0]) != 0 || (getSpritePal().hsbi[c1][1]) != 0 || (getSpritePal().hsbi[c1][2]) != 0)
						&& ((getSpritePal().hsbi[c2][0]) != 0 || (getSpritePal().hsbi[c2][1]) != 0 || (getSpritePal().hsbi[c2][2]) != 0))
					{
						if((((getSpritePal().hsbi[c1][2]) - (getSpritePal().hsbi[c2][2])) <= amount))
						{

							getSpritePal().hsbi[c2][2] += ((getSpritePal().hsbi[c1][2] - getSpritePal().hsbi[c2][2]) / 2);
							getSpritePal().hsbi[c1][2] = getSpritePal().hsbi[c2][2];
						}
					}
				}
			}
		}

		for(int f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);
		}

		controlPanel.repaint();
		infoLabel.setTextSuccess("Merged Sprite Palette S By " + amount);
	}

	//===============================================================================================
	public void brightenSpritePalHSB()
	{//===============================================================================================


		NumberDialog nd = new NumberDialog(new Frame(), "Add (Out of 255)");
		nd.text.setText("8");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		for(int c1 = start; c1 < end; c1++)
		{
			if(getSpritePal().hsbi[c1][2] + (amount) < 255)
			{
				getSpritePal().hsbi[c1][2] += (amount);
			}
			else
			{
				getSpritePal().hsbi[c1][2] = 255;
			}
		}

		for(int f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);
		}

		controlPanel.repaint();
		infoLabel.setTextSuccess("Brightened Sprite Palette HSB By " + amount);
	}





	//===============================================================================================
	public void darkenSpritePalHSB()
	{//===============================================================================================

		NumberDialog nd = new NumberDialog(new Frame(), "Subtract (Out of 255)");
		nd.text.setText("8");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		for(int c1 = start; c1 < end; c1++)
		{
			if(getSpritePal().hsbi[c1][2] - amount > 0)
			{
				getSpritePal().hsbi[c1][2] -= amount;
			}
			else
			{
				getSpritePal().hsbi[c1][2] = 0;
			}
		}

		for(int f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);
		}

		controlPanel.repaint();
		infoLabel.setTextSuccess("Darkened Sprite Palette HSB By " + amount);
	}







	//===============================================================================================
	public void roundSpritePalHSB()
	{//===============================================================================================

		NumberDialog nd = new NumberDialog(this, "Round to Amt/255");
		nd.text.setText("16");
		nd.show();
		int amount = Integer.parseInt(nd.text.getText());

		NumberDialog ndhsb = new NumberDialog(this, "[0]H [1]S [2]B");
		ndhsb.text.setText("0");
		ndhsb.show();
		int hsbn = Integer.parseInt(ndhsb.text.getText());

		NumberDialog ndstart = new NumberDialog(new Frame(), "Start at Palette Number");
		ndstart.text.setText("48");
		ndstart.show();
		int start = Integer.parseInt(ndstart.text.getText());

		NumberDialog ndend = new NumberDialog(new Frame(), "Up to (Not Including) Palette Number");
		ndend.text.setText("240");
		ndend.show();
		int end = Integer.parseInt(ndend.text.getText());

		int f = 0;

		int c1 = 0;
		//int c2 = 0;

		for(c1 = start; c1 < end; c1++) //sort hue
		{
			if(((getSpritePal().hsbi[c1][0]) != 0 || (getSpritePal().hsbi[c1][1]) != 0 || (getSpritePal().hsbi[c1][2]) != 0))
			{
				if((getSpritePal().hsbi[c1][hsbn]) % amount != 0)
				{
					if(((getSpritePal().hsbi[c1][hsbn]) % amount) < (amount / 2))
					{
						getSpritePal().hsbi[c1][hsbn] = (((getSpritePal().hsbi[c1][hsbn]) / amount) * amount);
					}
					else
					{
						getSpritePal().hsbi[c1][hsbn] = ((((getSpritePal().hsbi[c1][hsbn]) / amount) + 1) * amount);
					}

					if(getSpritePal().hsbi[c1][hsbn] < 0)
					{
						getSpritePal().hsbi[c1][hsbn] = 0;
					}
					if(getSpritePal().hsbi[c1][hsbn] > 255)
					{
						getSpritePal().hsbi[c1][hsbn] = 255;
					}
				}
			}
		}

		for(f = start; f < end; f++)
		{
			int h = getSpritePal().hsbi[f][0];
			int s = getSpritePal().hsbi[f][1];
			int b = getSpritePal().hsbi[f][2];
			getSpritePal().setColorDataFromHSBData(f, h, s, b);
		}
	}

	//===============================================================================================
	public void removeUnusedSpritePalCols()
	{//===============================================================================================

		removeUnusedSpriteColors();
		controlPanel.repaint();
		infoLabel.setTextSuccess("Removed Unused Sprite Colors");
	}

	//===============================================================================================
	public void mergeDuplicateSpritePalCols()
	{//===============================================================================================

		getSpritePal().mergeDuplicateSpriteColors();
		controlPanel.repaint();
		infoLabel.setTextSuccess("Merged Duplicate Sprite Colors");
	}

	//===============================================================================================
	public void removeUnusedSpriteColors()
	{//===============================================================================================
		for(int p = 0; p < getSpritePal().numColors; p++)
		{
			int used = 0;

			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				for(int f = 0; f < Project.getSprite(i).frames(); f++)
				{
					for(int x = 0; x < Project.getSprite(i).wP(); x++)
					{
						for(int y = 0; y < Project.getSprite(i).hP(); y++)
						{
							if(Project.getSprite(i).getPixel(f, x, y) == p)
							{
								used = 1;
							}
						}
					}
				}
			}

			if(used == 0)
			{
				getSpritePal().deleteColor(p);
			}
		}
	}
	//===============================================================================================
	public void swapSpriteColorsEverySprite(int origCol, int newCol)
	{//===============================================================================================
		for(int i = 0; i < Project.getNumSprites(); i++)
		{
			Project.getSprite(i).swapSpriteColors(origCol, newCol);
		}
	}
	@Override
	public void keyTyped(KeyEvent e)
	{
		// TODO Auto-generated method stub

	}
	@Override
	public void keyPressed(KeyEvent e)
	{
		editCanvas.keyPressed(e);

	}
	@Override
	public void keyReleased(KeyEvent e)
	{
		// TODO Auto-generated method stub

	}
	@Override
	public void menuSelected(MenuEvent e)
	{

		if(e.getSource() == closeMenu)
		{
			setVisible(false);
		}


	}
	@Override
	public void menuDeselected(MenuEvent e)
	{


	}
	@Override
	public void menuCanceled(MenuEvent e)
	{


	}

	//===============================================================================================
	public void filterDestinationList()
	{//===============================================================================================

		if(filterTextField.getText().length()>0)
		{

			for(int i=0;i < spriteListModel.getSize();i++)
			{
				if(spriteListModel.getElementAt(i).name().toLowerCase().contains((CharSequence)filterTextField.getText().toLowerCase())==false){spriteListModel.remove(i);i--;}
			}
		}
	}

	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================
		if(e.getSource()==filterTextField)
		{
			if(e.getSource()==filterTextField)
			{

				if(filterTextField.getText().length()>lastFilterString.length())
				{
					lastFilterString=filterTextField.getText();
					filterDestinationList();

				}
				else
				{
					lastFilterString=filterTextField.getText();
					updateInfo();

				}
			}
		}
	}

	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================
		if(e.getSource() == spriteList)
		{

			if(e.getValueIsAdjusting()==true)return;

			if(spriteList.getSelectedValue()==Project.getSelectedSprite())return;

			if(spriteList.getSelectedIndex()==-1)return;


			spriteList.ensureIndexIsVisible(spriteList.getSelectedIndex());

			Project.setSelectedSprite(spriteList.getSelectedValue());
			getSprite().setFrame(0);
			editCanvas.editBufferImage=null;
			frameControlPanel.updateSpriteInfo();
			frameControlPanel.updateFrames();
			editCanvas.repaintBufferImage();
			//editCanvas.initUndo();
			editCanvas.repaint();

			setFrameCanvasHeight();

		}

	}

	//===============================================================================================
	public void saveProjectAction()
	{//===============================================================================================
		JFileChooser chooser = new JFileChooser(EditorMain.getFileDialogDirectoryPath());
		chooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Sprite Project (*.sprproj)", "sprproj"));
		int returnVal = chooser.showSaveDialog(this);
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			File file = chooser.getSelectedFile();
			if(!file.getName().endsWith(".sprproj")) {
				file = new File(file.getAbsolutePath() + ".sprproj");
			}
			try {
				com.bobsgame.editor.Project.Sprite.SpriteProject.save(getSprite(), file);
				infoLabel.setTextSuccess("Saved project to " + file.getName());
			} catch (Exception e) {
				e.printStackTrace();
				infoLabel.setText("Error saving project: " + e.getMessage());
			}
		}
	}

	//===============================================================================================
	public void loadProjectAction()
	{//===============================================================================================
		JFileChooser chooser = new JFileChooser(EditorMain.getFileDialogDirectoryPath());
		chooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Sprite Project (*.sprproj)", "sprproj"));
		int returnVal = chooser.showOpenDialog(this);
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			try {
				Sprite s = com.bobsgame.editor.Project.Sprite.SpriteProject.load(chooser.getSelectedFile());

				spriteListModel.addElement(s);
				spriteList.setSelectedValue(s, true);

				updateInfo();
				infoLabel.setTextSuccess("Loaded project from " + chooser.getSelectedFile().getName());

			} catch (Exception e) {
				e.printStackTrace();
				infoLabel.setText("Error loading project: " + e.getMessage());
			}
		}
	}

	//===============================================================================================
	public void importAsepriteAction() {
		JFileChooser chooser = new JFileChooser(EditorMain.getFileDialogDirectoryPath());
		chooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("Aseprite Files (*.ase, *.aseprite)", "ase", "aseprite"));
		int returnVal = chooser.showOpenDialog(this);
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			try {
				Sprite s = com.bobsgame.editor.Project.Sprite.AsepriteImporter.importSprite(chooser.getSelectedFile());

				spriteListModel.addElement(s);
				spriteList.setSelectedValue(s, true);

				updateInfo();
				infoLabel.setTextSuccess("Imported Aseprite file: " + chooser.getSelectedFile().getName());

			} catch (Exception e) {
				e.printStackTrace();
				infoLabel.setText("Error importing Aseprite file: " + e.getMessage());
			}
		}
	}

	//===============================================================================================
	class NameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public NameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);


			if(((Sprite)value).eventData()!=null)setForeground(Color.RED);

			setText((value == null) ? "" : ((Sprite)value).name());
			return this;
		}
	}



}








