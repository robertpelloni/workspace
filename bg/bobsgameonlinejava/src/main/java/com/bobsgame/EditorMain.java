package com.bobsgame;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EtchedBorder;

import com.bobsgame.editor.InfoLabelPanel;
import org.lwjgl.openal.AL;

import com.bobsgame.audio.AudioUtils;
import com.bobsgame.editor.ControlPanel.ControlPanel;
import com.bobsgame.editor.Dialogs.RenameWindow;
import com.bobsgame.editor.Dialogs.YesNoWindow;
import com.bobsgame.editor.MapCanvas.MapCanvas;
import com.bobsgame.editor.MultipleTileEditor.*;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.AudioEditor;
import com.bobsgame.editor.Project.ProjectCutsceneEditWindow;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.MapState;
import com.bobsgame.editor.SpriteEditor.SpriteEditor;
import com.bobsgame.editor.TileCanvas.TileCanvas;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.Utils;

public class EditorMain extends JFrame implements ActionListener, ItemListener, WindowListener, KeyListener, MouseWheelListener {
	public static void main(String[] args) {
		//System.out.println("starting...");
		new EditorMain();
	}

	public static String exportDirectory = System.getProperties().getProperty("user.home")+"\\Desktop\\bgEditor_Output\\";
	public static String defaultProjectFolder = "F:\\source\\bobsgame\\workspace\\_gfx\\_____MAPS\\";
	public static String serverDataDir = "F:\\source\\bobsgame\\workspace\\BobsGameServer\\src\\main\\resources\\data\\";
	public static String htdocsZippedAssetsDir = "C:\\xampp\\htdocs\\z\\";
	public static String oggEncPath = "F:\\source\\bobsgame\\workspace\\_sfx\\oggenc2.exe";
	public static String lameEncoderPath = "F:\\source\\bobsgame\\workspace\\_sfx\\lame.exe";
	public static String clientPreloadedAssetsDir = "F:\\source\\bobsgame\\workspace\\BobsGameOnline\\src\\main\\resources\\";
	public static String androidProjectAssetsDir = "F:\\source\\bobsgame\\workspace\\bg-android\\assets\\";


	public static boolean soundWasInitialized = false;

	public static JFileChooser fileChooser;
	private RenameWindow rename;

	private JMenuBar menuBar;
	private JMenu fileMenu, editMenu, spritesMenu, tilesetMenu, mapMenu, stateMenu, helpMenu, paletteMenu, optionsMenu, soundAndMusicMenu, cutsceneMenu;
	private JMenuItem

	//FILE MENU
		newProject,
		openProject,
		mergeProject,
		saveProject,
		exportProject,
		exportProjectAsGameData,
		exportProjectToWorkspaceLibGDXAssetsFolderForHTML5,
		exit,



	//EDIT MENU
		editUndo,
		editRedo,


	//TILESET MENU
		moveUnusedTilesToBottom,
		removeUnusedTiles,
		crunchTileset,
		mergeDuplicateTiles,
		mergeBlankTiles,
		countUsedTilesSelectedMap,
		countUsedTilesWholeTileset,
		removeBlankRows,
		mergeDuplicatesAndRemoveEmptySpacePastSelectedTile,
		insertTilesetRows,
		findFirstMapWithSelectedTile,
		listDoorsThatAreBroken,
		importImageToTileset,



	//MAP MENU
		previewMapInClient,
		newMap,
		renameMap,
		duplicateMap,
		resizeMap,
		deleteMap,
		moveMapUp,
		moveMapDown,
		viewZoomIn,
		viewZoomOut,

		saveCurrentMapPNGForEachLayer,
		saveAllMapsPNGForEachLayer,

		saveCurrentMapCombinedLayersToPNG,
		saveAllMapsCombinedLayersToPNG,

		saveCurrentMapCombinedLayersToHQ2XPNG,
		saveAllMapsCombinedLayersToHQ2XPNG,

		findLeastUsedTileOnMap,
		copySelectionCoordsToClipboard,
		toggleLightBlackMasking,
		toggleLightScreenBlending,
		toggleAreaSpriteInfo,
		toggleAreaOutlines,
		toggleRandomPointOfInterestLines,
		toggleTileEditMode,
		toggleAutoTileMode,



	//STATE MENU
		newState,
		duplicateState,
		renameState,
		deleteState,
		moveStateUp,
		moveStateDown,


	//PALETTE MENU
		newPalette,
		renamePalette,
		duplicatePalette,
		deletePalette,
		removeUnusedPaletteColors,
		mergeDuplicatePaletteColors,
		setBlankTilesToSelectedColor,
		sortPaletteHSB,
		mergePaletteH,
		mergePaletteS,
		mergePaletteB,
		brightenPaletteHSB,
		darkenPaletteHSB,
		roundPaletteHSB,
		standardizePaletteRangeHSB,
		findLeastUsedColor,
		findFirstTileUsingSelectedColor,



	//SPRITE MENU
		openSpriteEditor,
		toggleMoveEntityByPixel,


	//SOUNDS AND MUSIC MENU
		openSoundAndMusicEditor,


	//SOUNDS AND MUSIC MENU
	openCutsceneEditor;

	private JCheckBoxMenuItem

		viewMapGrid,
		viewTileGrid,
		bufferCheck,
		previewMode,
		soundsOnOff;

	public static JScrollPane mapScrollPane;
	public static JScrollPane tileScrollPane;

	public JPanel panel, topPanel, menuPanel, mapChoicePanel, paletteChoicePanel, infoLabelPanel, stateChoicePanel;


	private BoxLayout boxLayout;

	public JComboBox<String> paletteChoice, mapChoice, stateChoice; //tilesetChoice,



	public static ControlPanel controlPanel;
	public static MapCanvas mapCanvas;
	public static TileCanvas tileCanvas;
	public static JComponent lastActiveCanvas;
	public static SpriteEditor spriteEditor;
	public static MultipleTileEditor multipleTileEditor;

	public static InfoLabelPanel infoLabel;
	public JLabel statsLabel;
	public JLabel tilesetLabel, mapLabel, paletteLabel, stateLabel;

	public Project project;
	public boolean project_loaded = false;


	public static Frame frame = null;

	public static AudioEditor soundAndMusicEditor;
	public static ProjectCutsceneEditWindow projectCutsceneEditWindow;

	public static Color comboboxBackgroundColor = Color.black;

	public static Font bobsgameFont = new Font("Tahoma",Font.PLAIN,11);

	public static Border border;


	public static AudioUtils audioUtils;


	//===============================================================================================
	public EditorMain()
	{//===============================================================================================

		super("bgEdit v0.1.2");



		try
		{
			//LookAndFeelInfo[] info = UIManager.getInstalledLookAndFeels();

			//for(int i=0;i<info.length;i++)System.out.println(info[i].getName());

			//UIManager.setLookAndFeel(info[1].getClassName());//nimbus

			//UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());//metal/java

			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());//win7



//			for(LookAndFeelInfo info : UIManager.getInstalledLookAndFeels())
//			{
//				if("Nimbus".equals(info.getName()))
//				{
//					UIManager.setLookAndFeel(info.getClassName());
//					break;
//				}
//			}

			/*

			UIManager.put("nimbusBase", new Color(0,255,0));//comboboxes,selected menus,scrollbars

			UIManager.put("nimbusBlueGrey", new Color(0,0,0));//scrollbar background, unselected menus/menubar.

			UIManager.put("control", new Color(0,0,0));//panels

			UIManager.put("nimbusFocus", new Color(255,0,255));//focus rectangle around buttons


			UIManager.put("nimbusSelectionBackground", new Color(0,0,0));//background of comboboxes

			UIManager.put("nimbusBorder", new Color(100,100,100));//listbox borders
			UIManager.put("info", new Color(0,255,0));//tooltip

			UIManager.put("nimbusLightBackground", new Color(64,64,64));//combobox selected text, listbox background

			UIManager.put("nimbusSelection", new Color(0,255,0));//mouseover menu item


			UIManager.put("nimbusRed", new Color(0,255,0));//??
			UIManager.put("nimbusOrange", new Color(0,255,0));//??
			UIManager.put("nimbusGreen", new Color(0,255,0));//??
			UIManager.put("nimbusInfoBlue", new Color(0,255,0));//??
			UIManager.put("nimbusAlertYellow", new Color(0,255,0));//??

			UIManager.put("textForeground", new Color(0,255,0));//label text
			UIManager.put("textBackground", new Color(255,0,255));//??
			UIManager.put("background", new Color(255,0,255)); //??
			UIManager.put("focus", new Color(255,0,255)); //??

			UIManager.put("text", new Color(0,255,0));
			UIManager.put("nimbusSelectedText", new Color(255,0,255));
			UIManager.put("nimbusDisabledText", new Color(64,64,64));
			UIManager.put("infoText", new Color(255,0,255));
			UIManager.put("menuText", new Color(255,0,255));
			UIManager.put("menu", new Color(255,0,255));
			UIManager.put("MenuBar:Menu[Enabled].textForeground", new Color(0,255,0));
			UIManager.put("MenuItem[Enabled].textForeground", new Color(0,0,0));
			UIManager.put("Menu[Enabled].textForeground", new Color(0,255,0));
			UIManager.put("CheckBoxMenuItem[Enabled].textForeground", new Color(0,0,0));

			UIManager.put("MenuItem.background", new Color(0,0,0));

			UIManager.put("MenuBar:Menu[Selected].textForeground", new Color(255,0,255));
			UIManager.put("MenuItem[MouseOver].textForeground", new Color(255,0,255));
			UIManager.put("Menu[Enabled+Selected].textForeground", new Color(255,0,255));
			UIManager.put("CheckBoxMenuItem[MouseOver].textForeground", new Color(255,0,255));
			UIManager.put("CheckBoxMenuItem[Disabled].textForeground", new Color(255,0,255));


			UIManager.put("scrollbar", new Color(255,0,255));
			UIManager.put("controlText", new Color(255,0,255));
			UIManager.put("controlHighlight", new Color(255,0,255));
			UIManager.put("controlLHighlight", new Color(255,0,255));
			UIManager.put("controlShadow", new Color(255,0,255));
			UIManager.put("controlDkShadow", new Color(255,0,255));
			UIManager.put("textHighlight", new Color(255,0,255));
			UIManager.put("textHighlightText", new Color(255,0,255));
			UIManager.put("textInactiveText", new Color(255,0,255));
			UIManager.put("desktop", new Color(255,0,255));
			UIManager.put("activeCaption", new Color(255,0,255));
			UIManager.put("inactiveCaption", new Color(255,0,255));






			UIManager.put("InternalFrame.titleFont", EditorMain.bobsgameFont); //??
			UIManager.put("defaultFont", EditorMain.bobsgameFont); //??
			UIManager.put("font", EditorMain.bobsgameFont); //??
			UIManager.put("MenuItem.titleFont", EditorMain.bobsgameFont); //??
			UIManager.put("Panel.font", EditorMain.bobsgameFont);
			UIManager.put("Label.font", EditorMain.bobsgameFont);
			UIManager.put("Button.font", EditorMain.bobsgameFont);
			UIManager.put("ComboBox.font", EditorMain.bobsgameFont);
			UIManager.put("Menu.font", EditorMain.bobsgameFont);
			UIManager.put("MenuItem.font", EditorMain.bobsgameFont);
			UIManager.put("Component.font", EditorMain.bobsgameFont);
			UIManager.put("ComponentUI.font", EditorMain.bobsgameFont);
			UIManager.put("Object.font", EditorMain.bobsgameFont);




			UIManager.put("FilePane.viewType", FilePane.VIEWTYPE_DETAILS);
			*/


			SwingUtilities.updateComponentTreeUI(this);



		}
		catch(Exception ex)
		{
			System.out.println("Could not set Look And Feel");
		}



		border = BorderFactory.createEtchedBorder(EtchedBorder.LOWERED);//createLineBorder(new Color(32,32,32), 1, false);//createEtchedBorder(EtchedBorder.LOWERED,Color.DARK_GRAY,new Color(32,32,32));//createLineBorder(Color.DARK_GRAY, 1, false);//(BevelBorder.LOWERED, Color.GRAY, );//(EtchedBorder.LOWERED);



		frame = this;

		/*

		frame = new Frame();



		frame.setVisible(true);
		//Graphics g = frame.getGraphics();
		GraphicsConfiguration g = frame.getGraphicsConfiguration();
		while(g==null)
		{
			g = frame.getGraphicsConfiguration();
		}

		//System.out.println(g.getBufferCapabilities().);
		//g.getColorModel().;
		//g.getImageCapabilities().;

		frame.setVisible(false);

		g = this.getGraphicsConfiguration();
		while(g==null)
		{
			g = this.getGraphicsConfiguration();
		}

		*/



		setFocusable(true);
		addKeyListener(this);
		addMouseWheelListener(this);
		addWindowListener(this);

		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		project = new Project(this);


		fileChooser = new JFileChooser(EditorMain.defaultProjectFolder);//(this, "Select File", FileDialog.LOAD);


		fileChooser.getFileView();
		//FilePane.setViewType(FilePane.VIEWTYPE_DETAILS);




		rename = new RenameWindow(this);
		spriteEditor = new SpriteEditor(this);
		multipleTileEditor = new MultipleTileEditor(this);

		soundAndMusicEditor = new AudioEditor();
		projectCutsceneEditWindow = new ProjectCutsceneEditWindow();


		fileMenu = new JMenu("File");
		editMenu = new JMenu("Edit");
		spritesMenu = new JMenu("Sprite Editor");
		tilesetMenu = new JMenu("Tileset Tools");
		mapMenu = new JMenu("Map Tools");
		stateMenu = new JMenu("State Tools");
		paletteMenu = new JMenu("Palette Tools");
		helpMenu = new JMenu(" ? ");
		optionsMenu = new JMenu("Options");
		soundAndMusicMenu = new JMenu("Sounds And Music");
		cutsceneMenu = new JMenu("Project Cutscenes");


		menuBar = new JMenuBar();
		menuBar.setBackground(Color.BLACK);
		menuBar.setFont(EditorMain.bobsgameFont);


		menuBar.add(fileMenu);
		menuBar.add(editMenu);
		menuBar.add(paletteMenu);
		menuBar.add(tilesetMenu);
		menuBar.add(mapMenu);
		menuBar.add(stateMenu);
		menuBar.add(spritesMenu);
		menuBar.add(helpMenu);
		menuBar.add(optionsMenu);
		menuBar.add(soundAndMusicMenu);
		menuBar.add(cutsceneMenu);





		//--------------------------------------------------------------
		//FILE MENU
		//--------------------------------------------------------------

				newProject = new JMenuItem("New Project");
				newProject.addActionListener(this);

				//--------------------------------------------------------------

				openProject = new JMenuItem("Open Project...");
				openProject.addActionListener(this);

				//--------------------------------------------------------------

				mergeProject = new JMenuItem("Merge Project...");
				mergeProject.addActionListener(this);

				//--------------------------------------------------------------

				saveProject = new JMenuItem("Save Project As...");
				saveProject.addActionListener(this);
				saveProject.setEnabled(false);

				//--------------------------------------------------------------

				exportProject = new JMenuItem("Export Project To htdocs/z/[assets].zip And workspace/[project]/res/objectData");
				exportProject.addActionListener(this);

				//--------------------------------------------------------------
				exportProjectAsGameData = new JMenuItem("Export MINIGAME ASSETS To htdocs/z/gameData");
				exportProjectAsGameData.addActionListener(this);
				//--------------------------------------------------------------


				exportProjectToWorkspaceLibGDXAssetsFolderForHTML5 = new JMenuItem("Export MINIGAME ASSETS To LibGDX Android Asset Folder");
				exportProjectToWorkspaceLibGDXAssetsFolderForHTML5.addActionListener(this);
				//--------------------------------------------------------------


				exit = new JMenuItem("Exit (no autosave)");
				exit.addActionListener(this);



				fileMenu.add(newProject);
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------
				fileMenu.add(openProject);
				fileMenu.add(mergeProject);
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------
				fileMenu.add(saveProject);
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//fileMenu.add(new JMenuSpacer(""));
				//fileMenu.add(new JMenuSpacer(""));
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------

				fileMenu.add(exportProject);
				//fileMenu.add(new JMenuSpacer(""));
				fileMenu.add(exportProjectAsGameData);
				fileMenu.add(exportProjectToWorkspaceLibGDXAssetsFolderForHTML5);
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//fileMenu.add(new JMenuSpacer(""));
				//fileMenu.add(new JMenuSpacer(""));
				//--------------------------------------------------------------
				fileMenu.add(exit);



		//--------------------------------------------------------------
		//EDIT MENU
		//--------------------------------------------------------------
				editUndo = new JMenuItem("Undo");//,new JMenuShortcut(KeyEvent.VK_Z, false));
				editUndo.addActionListener(this);
				editUndo.setEnabled(true);

				editRedo = new JMenuItem("Redo");//,new JMenuShortcut(KeyEvent.VK_Y, false));
				editRedo.addActionListener(this);
				editRedo.setEnabled(true);

				editMenu.add(editUndo);
				editMenu.add(editRedo);





		//--------------------------------------------------------------
		//TILESET MENU
		//--------------------------------------------------------------


				//renameTileset = new JMenuItem("Rename Current Tile Set");
				//renameTileset.addActionListener(this);
				//renameTileset.setEnabled(true);


				//--------------------------------------------------------------

				viewTileGrid = new JCheckBoxMenuItem("View Tile Grid", true);
				viewTileGrid.addItemListener(this);

				//--------------------------------------------------------------

				insertTilesetRows = new JMenuItem("Insert Blank Rows at Selected Tile...");
				insertTilesetRows.addActionListener(this);
				insertTilesetRows.setEnabled(true);
				//--------------------------------------------------------------

				removeUnusedTiles = new JMenuItem("Remove Unused Tiles (Set To Blank)");
				removeUnusedTiles.addActionListener(this);
				removeUnusedTiles.setEnabled(true);

				crunchTileset = new JMenuItem("Crunch Tileset Upwards (Remove All Blank Tiles)");
				crunchTileset.addActionListener(this);
				crunchTileset.setEnabled(true);

				moveUnusedTilesToBottom = new JMenuItem("Move Unused Tiles To Bottom");
				moveUnusedTilesToBottom.addActionListener(this);
				moveUnusedTilesToBottom.setEnabled(true);

				mergeDuplicateTiles = new JMenuItem("Merge Duplicate Tiles");
				mergeDuplicateTiles.addActionListener(this);
				mergeDuplicateTiles.setEnabled(true);

				mergeBlankTiles = new JMenuItem("Merge Blank Tiles");
				mergeBlankTiles.addActionListener(this);
				mergeBlankTiles.setEnabled(true);

				removeBlankRows = new JMenuItem("Remove Blank Rows");
				removeBlankRows.addActionListener(this);
				removeBlankRows.setEnabled(true);

				mergeDuplicatesAndRemoveEmptySpacePastSelectedTile = new JMenuItem("Merge Duplicates And Remove Empty Space Past Selected Tile");
				mergeDuplicatesAndRemoveEmptySpacePastSelectedTile.addActionListener(this);
				mergeDuplicatesAndRemoveEmptySpacePastSelectedTile.setEnabled(true);

				countUsedTilesWholeTileset = new JMenuItem("Count Used Tiles On All Tileset Maps (console out)");
				countUsedTilesWholeTileset.addActionListener(this);
				countUsedTilesWholeTileset.setEnabled(true);

				findFirstMapWithSelectedTile = new JMenuItem("Find First Map/Position Using Selected Tile (console out)");
				findFirstMapWithSelectedTile.addActionListener(this);
				findFirstMapWithSelectedTile.setEnabled(true);


				setBlankTilesToSelectedColor = new JMenuItem("Set Blank Tiles To Selected Color");
				setBlankTilesToSelectedColor.addActionListener(this);
				setBlankTilesToSelectedColor.setEnabled(true);

				listDoorsThatAreBroken = new JMenuItem("List Doors That Are Broken");
				listDoorsThatAreBroken.addActionListener(this);
				listDoorsThatAreBroken.setEnabled(true);

				importImageToTileset = new JMenuItem("Import Image to Tileset...");
				importImageToTileset.addActionListener(this);
				importImageToTileset.setEnabled(true);


				//tilesetMenu.add(newTileset);
				//tilesetMenu.add(renameTileset);
				//tilesetMenu.add(resizeTileset);
				//tilesetMenu.add(deleteTileset);
				//tilesetMenu.add(duplicateTileset);
				//--------------------------------------------------------------
				tilesetMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				tilesetMenu.add(viewTileGrid);
				//--------------------------------------------------------------
				tilesetMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				tilesetMenu.add(insertTilesetRows);
				//--------------------------------------------------------------
				tilesetMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				tilesetMenu.add(removeUnusedTiles);
				tilesetMenu.add(crunchTileset);
				tilesetMenu.add(moveUnusedTilesToBottom);
				tilesetMenu.add(mergeDuplicateTiles);
				tilesetMenu.add(mergeBlankTiles);
				tilesetMenu.add(removeBlankRows);
				tilesetMenu.add(mergeDuplicatesAndRemoveEmptySpacePastSelectedTile);
				tilesetMenu.add(countUsedTilesWholeTileset);
				tilesetMenu.add(findFirstMapWithSelectedTile);
				tilesetMenu.add(setBlankTilesToSelectedColor);
				tilesetMenu.add(listDoorsThatAreBroken);
				tilesetMenu.add(importImageToTileset);






		//--------------------------------------------------------------
		//MAP MENU
		//--------------------------------------------------------------
				previewMapInClient = new JMenuItem("Preview Map In Client");
				previewMapInClient.addActionListener(this);
				previewMapInClient.setEnabled(true);
				previewMapInClient.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F11,0));

				newMap = new JMenuItem("New Map");
				newMap.addActionListener(this);
				newMap.setEnabled(true);

				resizeMap = new JMenuItem("Resize Current Map");
				resizeMap.addActionListener(this);
				resizeMap.setEnabled(true);

				renameMap = new JMenuItem("Rename Current Map");
				renameMap.addActionListener(this);
				renameMap.setEnabled(true);

				deleteMap = new JMenuItem("Delete Current Map");
				deleteMap.addActionListener(this);
				deleteMap.setEnabled(true);

				duplicateMap = new JMenuItem("Duplicate Current Map");
				duplicateMap.addActionListener(this);
				duplicateMap.setEnabled(true);


				moveMapUp = new JMenuItem("Move Map Up");
				moveMapUp.addActionListener(this);
				moveMapUp.setEnabled(true);
				moveMapUp.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_COMMA,InputEvent.CTRL_DOWN_MASK));

				moveMapDown = new JMenuItem("Move Map Down");
				moveMapDown.addActionListener(this);
				moveMapDown.setEnabled(true);
				moveMapDown.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_PERIOD,InputEvent.CTRL_DOWN_MASK));

				//--------------------------------------------------------------

				viewMapGrid = new JCheckBoxMenuItem("View Map Grid", false);
				viewMapGrid.addItemListener(this);

				viewZoomIn = new JMenuItem("Zoom In");//,new JMenuShortcut(KeyEvent.VK_EQUALS, false));
				viewZoomIn.addActionListener(this);
				viewZoomIn.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_EQUALS,InputEvent.CTRL_DOWN_MASK));

				viewZoomOut = new JMenuItem("Zoom Out");//,new JMenuShortcut(KeyEvent.VK_MINUS, false));
				viewZoomOut.addActionListener(this);
				viewZoomOut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_MINUS,InputEvent.CTRL_DOWN_MASK));

				//--------------------------------------------------------------

				bufferCheck = new JCheckBoxMenuItem("Buffer Individual Layers on/off (Memory Used * 16)", false);
				bufferCheck.addItemListener(this);

				previewMode = new JCheckBoxMenuItem("Preview Mode on/off", false);
				previewMode.addItemListener(this);

				//--------------------------------------------------------------

				countUsedTilesSelectedMap = new JMenuItem("Count Used Tiles On Current Map (console out)");
				countUsedTilesSelectedMap.addActionListener(this);
				countUsedTilesSelectedMap.setEnabled(true);

				findLeastUsedTileOnMap = new JMenuItem("Find Least Used Tile[s] On Map...");
				findLeastUsedTileOnMap.addActionListener(this);
				findLeastUsedTileOnMap.setEnabled(true);



				//--------------------------------------------------------------

				copySelectionCoordsToClipboard = new JMenuItem("[k] Copy Selection Coords To Clipboard (x1*8,y1*8,x2*8-1,y2*8-1)");
				copySelectionCoordsToClipboard.addActionListener(this);
				copySelectionCoordsToClipboard.setEnabled(true);

				//--------------------------------------------------------------

				saveCurrentMapPNGForEachLayer = new JMenuItem("Save Current Map To Separate PNG For Each Layer");
				saveCurrentMapPNGForEachLayer.addActionListener(this);
				saveCurrentMapPNGForEachLayer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F12,InputEvent.CTRL_DOWN_MASK));

				saveAllMapsPNGForEachLayer = new JMenuItem("Save *All* Maps To Separate PNG For Each Layer");
				saveAllMapsPNGForEachLayer.addActionListener(this);

				//--------------------------------------------------------------

				saveCurrentMapCombinedLayersToPNG = new JMenuItem("Save Current Map Combined Over/Under Layers To PNGs [01345,678]");
				saveCurrentMapCombinedLayersToPNG.addActionListener(this);


				saveAllMapsCombinedLayersToPNG = new JMenuItem("Save *All* Maps Combined Over/Under Layers To PNGs [01345,678]");
				saveAllMapsCombinedLayersToPNG.addActionListener(this);


				saveCurrentMapCombinedLayersToHQ2XPNG = new JMenuItem("Save Current Map Combined Over/Under Layers To HQ2X PNGs [01345,678]");
				saveCurrentMapCombinedLayersToHQ2XPNG.addActionListener(this);
				saveCurrentMapCombinedLayersToHQ2XPNG.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F12, InputEvent.CTRL_DOWN_MASK));


				saveAllMapsCombinedLayersToHQ2XPNG = new JMenuItem("Save *All* Maps Combined Over/Under Layers To HQ2X PNGs [01345,678]");
				saveAllMapsCombinedLayersToHQ2XPNG.addActionListener(this);

				//--------------------------------------------------------------

				toggleLightBlackMasking = new JCheckBoxMenuItem("Light Black Masking", false);
				toggleLightBlackMasking.addItemListener(this);

				toggleLightScreenBlending = new JCheckBoxMenuItem("Light Screen Blending", true);
				toggleLightScreenBlending.addItemListener(this);

				toggleAreaSpriteInfo = new JCheckBoxMenuItem("Always Show All Sprite/Area Info", false);
				toggleAreaSpriteInfo.addItemListener(this);
				toggleAreaSpriteInfo.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I, InputEvent.CTRL_DOWN_MASK));

				toggleAreaOutlines = new JCheckBoxMenuItem("Always Show Area Outlines If Area Layer Enabled", true);
				toggleAreaOutlines.addItemListener(this);

				toggleRandomPointOfInterestLines = new JCheckBoxMenuItem("Show Random Point Of Interest Lines", false);
				toggleRandomPointOfInterestLines.addItemListener(this);

				toggleTileEditMode = new JCheckBoxMenuItem("Edit Tiles Instanced", false);
				toggleTileEditMode.addItemListener(this);
				toggleTileEditMode.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, InputEvent.CTRL_DOWN_MASK));

				toggleAutoTileMode = new JCheckBoxMenuItem("Auto-Tile (4-bit)", false);
				toggleAutoTileMode.addItemListener(this);

				mapMenu.add(previewMapInClient);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(newMap);
				mapMenu.add(resizeMap);
				mapMenu.add(renameMap);
				mapMenu.add(deleteMap);
				mapMenu.add(duplicateMap);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(moveMapUp);
				mapMenu.add(moveMapDown);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(viewMapGrid);
				mapMenu.add(viewZoomIn);
				mapMenu.add(viewZoomOut);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(bufferCheck);
				mapMenu.add(previewMode);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(countUsedTilesSelectedMap);
				mapMenu.add(findLeastUsedTileOnMap);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(copySelectionCoordsToClipboard);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(saveCurrentMapPNGForEachLayer);
				mapMenu.add(saveAllMapsPNGForEachLayer);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(saveCurrentMapCombinedLayersToPNG);
				mapMenu.add(saveAllMapsCombinedLayersToPNG);

				mapMenu.add(saveCurrentMapCombinedLayersToHQ2XPNG);
				mapMenu.add(saveAllMapsCombinedLayersToHQ2XPNG);
				//--------------------------------------------------------------
				mapMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				mapMenu.add(toggleLightBlackMasking);
				mapMenu.add(toggleLightScreenBlending);
				mapMenu.add(toggleAreaSpriteInfo);
				mapMenu.add(toggleAreaOutlines);
				mapMenu.add(toggleRandomPointOfInterestLines);
				mapMenu.add(toggleTileEditMode);
				mapMenu.add(toggleAutoTileMode);


				//--------------------------------------------------------------
				//STATE MENU
				//--------------------------------------------------------------


				newState = new JMenuItem("Create Blank State");
				newState.addActionListener(this);
				newState.setEnabled(true);
				stateMenu.add(newState);

				stateMenu.add(new JMenuSpacer("---"));

				duplicateState = new JMenuItem("Duplicate Current State");
				duplicateState.addActionListener(this);
				duplicateState.setEnabled(true);
				stateMenu.add(duplicateState);

				renameState = new JMenuItem("Rename Current State");
				renameState.addActionListener(this);
				renameState.setEnabled(true);
				stateMenu.add(renameState);

				stateMenu.add(new JMenuSpacer("---"));

				deleteState = new JMenuItem("Delete Current State");
				deleteState.addActionListener(this);
				deleteState.setEnabled(true);
				stateMenu.add(deleteState);

				stateMenu.add(new JMenuSpacer("---"));

				moveStateUp = new JMenuItem("Move Current State Up");
				moveStateUp.addActionListener(this);
				moveStateUp.setEnabled(true);
				stateMenu.add(moveStateUp);

				moveStateDown = new JMenuItem("Move Current State Down");
				moveStateDown.addActionListener(this);
				moveStateDown.setEnabled(true);
				stateMenu.add(moveStateDown);


		//--------------------------------------------------------------
		//PALETTE MENU
		//--------------------------------------------------------------

				newPalette = new JMenuItem("New Palette");
				newPalette.addActionListener(this);
				newPalette.setEnabled(true);

				renamePalette = new JMenuItem("Rename Current Palette");
				renamePalette.addActionListener(this);
				renamePalette.setEnabled(true);

				deletePalette = new JMenuItem("Delete Current Palette");
				deletePalette.addActionListener(this);
				deletePalette.setEnabled(true);

				duplicatePalette = new JMenuItem("Duplicate Current Palette");
				duplicatePalette.addActionListener(this);
				duplicatePalette.setEnabled(true);
				//--------------------------------------------------------------

				removeUnusedPaletteColors = new JMenuItem("Remove Unused Palette Colors");
				removeUnusedPaletteColors.addActionListener(this);
				removeUnusedPaletteColors.setEnabled(true);

				mergeDuplicatePaletteColors = new JMenuItem("Merge Duplicate Palette Colors");
				mergeDuplicatePaletteColors.addActionListener(this);
				mergeDuplicatePaletteColors.setEnabled(true);

				findFirstTileUsingSelectedColor = new JMenuItem("Find First Tile Using Selected Color");
				findFirstTileUsingSelectedColor.addActionListener(this);
				findFirstTileUsingSelectedColor.setEnabled(true);

				findLeastUsedColor = new JMenuItem("Find Least Used Colors...");
				findLeastUsedColor.addActionListener(this);
				findLeastUsedColor.setEnabled(true);

				//--------------------------------------------------------------

				sortPaletteHSB = new JMenuItem("Sort Palette Colors by GRAY/HSB");
				sortPaletteHSB.addActionListener(this);
				sortPaletteHSB.setEnabled(true);

				roundPaletteHSB = new JMenuItem("Round Palette Colors (H/S/B)...");
				roundPaletteHSB.addActionListener(this);
				roundPaletteHSB.setEnabled(true);

				standardizePaletteRangeHSB = new JMenuItem("Standardize Palette Hue/Saturation Between Range...");
				standardizePaletteRangeHSB.addActionListener(this);
				standardizePaletteRangeHSB.setEnabled(true);

				mergePaletteH = new JMenuItem("Merge Palette Colors (HSB) H Within Percent...");
				mergePaletteH.addActionListener(this);
				mergePaletteH.setEnabled(true);

				mergePaletteS = new JMenuItem("Merge Palette Colors (HSB) S Within Percent...");
				mergePaletteS.addActionListener(this);
				mergePaletteS.setEnabled(true);

				mergePaletteB = new JMenuItem("Merge Palette Colors (HSB) B Within Percent...");
				mergePaletteB.addActionListener(this);
				mergePaletteB.setEnabled(true);

				//--------------------------------------------------------------

				brightenPaletteHSB = new JMenuItem("Brighten Palette Colors (HSB)...");
				brightenPaletteHSB.addActionListener(this);
				brightenPaletteHSB.setEnabled(true);

				darkenPaletteHSB = new JMenuItem("Darken Palette Colors (HSB)...");
				darkenPaletteHSB.addActionListener(this);
				darkenPaletteHSB.setEnabled(true);



				paletteMenu.add(newPalette);
				paletteMenu.add(renamePalette);
				paletteMenu.add(deletePalette);
				paletteMenu.add(duplicatePalette);
				//--------------------------------------------------------------
				paletteMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				paletteMenu.add(removeUnusedPaletteColors);
				paletteMenu.add(mergeDuplicatePaletteColors);
				paletteMenu.add(findFirstTileUsingSelectedColor);
				paletteMenu.add(findLeastUsedColor);
				//--------------------------------------------------------------
				paletteMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				paletteMenu.add(sortPaletteHSB);
				paletteMenu.add(roundPaletteHSB);
				paletteMenu.add(standardizePaletteRangeHSB);
				paletteMenu.add(mergePaletteH);
				paletteMenu.add(mergePaletteS);
				paletteMenu.add(mergePaletteB);
				//--------------------------------------------------------------
				paletteMenu.add(new JMenuSpacer("---"));
				//--------------------------------------------------------------
				paletteMenu.add(brightenPaletteHSB);
				paletteMenu.add(darkenPaletteHSB);

		//--------------------------------------------------------------




		//--------------------------------------------------------------
		//SPRITES MENU
		//--------------------------------------------------------------


				openSpriteEditor = new JMenuItem("Open Sprite Editor");
				openSpriteEditor.addActionListener(this);

				toggleMoveEntityByPixel = new JCheckBoxMenuItem("Move Map Sprites By Pixel", false);
				toggleMoveEntityByPixel.addItemListener(this);

				spritesMenu.add(openSpriteEditor);
				spritesMenu.add(toggleMoveEntityByPixel);

		//--------------------------------------------------------------
		//SOUNDS AND MUSIC MENU
		//--------------------------------------------------------------

				openSoundAndMusicEditor = new JMenuItem("Open Sounds And Music Editor");
				openSoundAndMusicEditor.addActionListener(this);

				soundAndMusicMenu.add(openSoundAndMusicEditor);


		//--------------------------------------------------------------
		//CUTSCENE MENU
		//--------------------------------------------------------------

				openCutsceneEditor = new JMenuItem("Open Project Cutscene Editor");
				openCutsceneEditor.addActionListener(this);

				cutsceneMenu.add(openCutsceneEditor);
		//--------------------------------------------------------------
		//HELP MENU
		//--------------------------------------------------------------



				JMenuItem pgupdownLabel = new JMenuItem("[PgUp][PgDn] Next/previous Map");
				pgupdownLabel.setEnabled(false);
				helpMenu.add(pgupdownLabel);

				JMenuItem nextState = new JMenuItem("[Home/End] Next/previous Map STATE");
				nextState.setEnabled(false);
				helpMenu.add(nextState);

				helpMenu.add(new JMenuSpacer("---"));

				JMenuItem udlrLabel = new JMenuItem("[UDLR] Navigate selected tile on tileset");
				udlrLabel.setEnabled(false);
				helpMenu.add(udlrLabel);

				JMenuItem numpadplusminusColorLabel = new JMenuItem("[NumPad+-] Previous/Next Color");
				numpadplusminusColorLabel.setEnabled(false);
				helpMenu.add(numpadplusminusColorLabel);

				JMenuItem tileFocus = new JMenuItem("[f] Tile Focus: Scroll/Focus tileset view on selected tile");
				tileFocus.setEnabled(false);
				helpMenu.add(tileFocus);

				JMenuItem tileFill = new JMenuItem("[t] Tile Fill: Fill map selection with selected tile- If area on Tiles is selected it will paste from tileset selection to map selection.");
				tileFill.setEnabled(false);
				helpMenu.add(tileFill);

				JMenuItem panMap = new JMenuItem("[Shift + MiddleClickDrag] Pan Map around.");
				panMap.setEnabled(false);
				helpMenu.add(panMap);

				JMenuItem zoomLock = new JMenuItem("[L + MiddleClickDrag] Hold L while selecting to set LOCK on zoom to keep camera locked on a particular area, hold L and MiddleClick to disable.");
				zoomLock.setEnabled(false);
				helpMenu.add(zoomLock);

				helpMenu.add(new JMenuSpacer("---"));

				JMenuItem moveAllLayers = new JMenuItem("Hold [A][LeftClick-Drag] Map Selection to move All Layers. [A][Ctrl][CXV] to Copy/Cut/Paste All TILE Layers AND OBJECTS. [A][RightClick-Drag] To Move-Copy.");
				moveAllLayers.setEnabled(false);
				helpMenu.add(moveAllLayers);

				helpMenu.add(new JMenuSpacer("---"));

				JMenuItem mteLabel = new JMenuItem("[MiddleClick-Drag] Select area on Tiles or Map and [Float-RightClick] to open in MTE");
				mteLabel.setEnabled(false);
				helpMenu.add(mteLabel);

				JMenuItem combineAllLayers = new JMenuItem("[a] Hold [a] (All Layers) and [Float-RightClick] Map Selection for all ENABLED layers combined as new tiles (appended at bottom of Tiles) and open in MTE. *Does not replace tiles on map");
				combineAllLayers.setEnabled(false);
				helpMenu.add(combineAllLayers);


				JMenuItem makeUniqueTiles = new JMenuItem("[CTRL-RightClick] Make new unique tiles: Duplicate selected tiles on SELECTED layer, replace tiles on map, and open in MTE");
				makeUniqueTiles.setEnabled(false);
				helpMenu.add(makeUniqueTiles);

				JMenuItem mashTiles = new JMenuItem("[m] (Mash) Combine tiles on ENABLED layers into new tiles on the bottommost ENABLED layer, and deletes all tiles on ENABLED layers above it");
				mashTiles.setEnabled(false);
				helpMenu.add(mashTiles);

				JMenuItem bracketLabel = new JMenuItem("[{][}] Move selected tiles on SELECTED layer up/down a layer. Skips special layers. Doesn't care if layer is enabled. *Won't move if existing tiles are on target layer.");
				bracketLabel.setEnabled(false);
				helpMenu.add(bracketLabel);

				JMenuItem shadowTiles = new JMenuItem("[s] Create Shadow Tiles: Combine tiles on ENABLED layers into *FLIPPED BLACK* tiles on *SELECTED SHADOW* layer, must have shadow layer selected and enabled.");
				shadowTiles.setEnabled(false);
				helpMenu.add(shadowTiles);

				helpMenu.add(new JMenuSpacer("---"));

				JMenuItem autoSwitch = new JMenuItem("[a] If on Area/Entity/Door/Light layer:  Hold [a] and [LeftClick] on area/light/entity/door to switch to that layer and select object under cursor, [MiddleClick] to edit.");
				autoSwitch.setEnabled(false);
				helpMenu.add(autoSwitch);

				JMenuItem createArea = new JMenuItem("If on Area/Light layer: [MiddleClick-Drag] a selection, and [MiddleClick] it to create a new area/light and open in area/light editor");
				createArea.setEnabled(false);
				helpMenu.add(createArea);

				JMenuItem createEntity = new JMenuItem("If on Door/Entity layer: [RightClick] to open Sprite/Door selection dialog and place a new Entity/Npc/Door");
				createEntity.setEnabled(false);
				helpMenu.add(createEntity);

				JMenuItem objectControls = new JMenuItem("If on Area/Light/Entity layer: [MiddleClick] to edit, [LeftClick] to move, [RightClick-Drag] to copy, [Del] to delete selected");
				objectControls.setEnabled(false);
				helpMenu.add(objectControls);

				JMenuItem moveArea = new JMenuItem("If selected Area/Entity, [udlr] moves selected Area/Entity on Map.");
				moveArea.setEnabled(false);
				helpMenu.add(moveArea);

				JMenuItem resizeArea = new JMenuItem("If selected Area, [CTRL]-[udlr] expands/resizes selected Area on Map.");
				resizeArea.setEnabled(false);
				helpMenu.add(resizeArea);

				JMenuItem addConnection = new JMenuItem("If selected Area/Door/Entity, hold [Shift-Drag] to add connection to another Object. (Used for walking paths)");
				addConnection.setEnabled(false);
				helpMenu.add(addConnection);


				JMenuItem quickWaypoint = new JMenuItem("If selected Area/Door/Entity, [CTRL-Drag] to create and add a new quick waypoint area for walking paths");
				quickWaypoint.setEnabled(false);
				helpMenu.add(quickWaypoint);

				helpMenu.add(new JMenuSpacer("---"));


				JMenuItem moveObject = new JMenuItem("If selected Area/Door/Entity/Light, [Shift-Home/End] to Move Object to Next/Previous State, [Ctrl-Home/End] To Copy");
				moveObject.setEnabled(false);
				helpMenu.add(moveObject);

				JMenuItem moveSelectionObjects = new JMenuItem("If Selection Box on Map, [Shift-Home/End] to Move ALL Objects in Selection to Next/Previous State, [Ctrl-Home/End] To Copy");
				moveSelectionObjects.setEnabled(false);
				helpMenu.add(moveSelectionObjects);


				helpMenu.add(new JMenuSpacer("---"));

				JMenuItem nLabel = new JMenuItem("[n] Output combined enabled layers into COLLADA texture and quad for import into sketchup");
				nLabel.setEnabled(false);
				helpMenu.add(nLabel);




		//--------------------------------------------------------------
		//OPTIONS MENU
		//--------------------------------------------------------------


				soundsOnOff = new JCheckBoxMenuItem("Beep When Finished Task", true);
				soundsOnOff.addItemListener(this);


				optionsMenu.add(soundsOnOff);







		//--------------------------------------------------------------
		//TILESET PANEL
		//--------------------------------------------------------------

				//tilesetLabel = new JLabel("Tileset");



				//tilesetChoice = new JComboBox();
				//tilesetChoice.setEditable(false);
				//tilesetChoice.addItemListener(this);
				//tilesetChoice.setForeground(Color.RED);



				//tilesetChoicePanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 0));
				//tilesetChoicePanel.setBorder(EditorMain.border);

				//tilesetChoicePanel.add(tilesetLabel);
				//tilesetChoicePanel.add(tilesetChoice);



				Font choiceFont = new Font("Tahoma",Font.BOLD,16);

		//--------------------------------------------------------------
		//MAP PANEL
		//--------------------------------------------------------------

				mapLabel = new JLabel("Map");
				mapLabel.setFont(choiceFont);
				//mapLabel.setForeground(Color.WHITE);



				mapChoice = new JComboBox<String>();
				mapChoice.setBackground(EditorMain.comboboxBackgroundColor);
				mapChoice.addItemListener(this);
				//mapChoice.addKeyListener(this);//bob9-29-05
				mapChoice.addMouseWheelListener(this);//bob9-29-05

				mapChoice.setEditable(false);
				mapChoice.setMaximumRowCount(50);
				mapChoice.setDoubleBuffered(false);
				mapChoice.setFocusable(false);
				//mapChoice.setFont(choiceFont);


				mapChoicePanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 0));
				//mapChoicePanel.setBorder(EditorMain.border);
				//mapChoicePanel.setBackground(Color.BLACK);

				mapChoicePanel.add(mapLabel);
				mapChoicePanel.add(mapChoice);

				mapChoicePanel.add(Box.createRigidArea(new Dimension(60,30)));

		//--------------------------------------------------------------
		//STATE PANEL
		//--------------------------------------------------------------

				stateLabel = new JLabel("State");
				stateLabel.setFont(choiceFont);
				//stateLabel.setForeground(Color.WHITE);


				stateChoice = new JComboBox<String>();
				stateChoice.setBackground(EditorMain.comboboxBackgroundColor);
				stateChoice.addItemListener(this);
				//stateChoice.addKeyListener(this);//bob9-29-05
				stateChoice.addMouseWheelListener(this);//bob9-29-05

				stateChoice.setEditable(false);
				stateChoice.setMaximumRowCount(50);
				stateChoice.setDoubleBuffered(false);
				stateChoice.setFocusable(false);
				//stateChoice.setFont(choiceFont);


				stateChoicePanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 0));
				//stateChoicePanel.setBorder(EditorMain.border);
				//stateChoicePanel.setBackground(Color.BLACK);

				stateChoicePanel.add(stateLabel);
				stateChoicePanel.add(stateChoice);
				stateChoicePanel.add(Box.createRigidArea(new Dimension(1,30)));

				mapChoicePanel.add(stateChoicePanel);

		//--------------------------------------------------------------
		//PALETTE PANEL
		//--------------------------------------------------------------

				paletteLabel = new JLabel("Palette");
				paletteLabel.setFont(choiceFont);
				//paletteLabel.setForeground(Color.WHITE);

				paletteChoice = new JComboBox<String>();
				paletteChoice.setBackground(EditorMain.comboboxBackgroundColor);
				paletteChoice.setEditable(false);
				paletteChoice.setMaximumRowCount(50);
				paletteChoice.setDoubleBuffered(false);
				paletteChoice.setFocusable(false);
				paletteChoice.addItemListener(this);
				//paletteChoice.setFont(choiceFont);

				paletteChoicePanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 0));
				//paletteChoicePanel.setBorder(EditorMain.border);
				//paletteChoicePanel.setBackground(Color.BLACK);

				paletteChoicePanel.add(paletteLabel);
				paletteChoicePanel.add(paletteChoice);
				paletteChoicePanel.add(Box.createRigidArea(new Dimension(1,30)));


		//--------------------------------------------------------------
		//MENU AND CHOICE PANEL
		//--------------------------------------------------------------


				topPanel = new JPanel();
				boxLayout = new BoxLayout(topPanel, BoxLayout.X_AXIS);
				topPanel.setLayout(boxLayout);

				topPanel.add(Box.createRigidArea(new Dimension(200,1)));
				//topPanel.add(tilesetChoicePanel);
				topPanel.add(mapChoicePanel);
				//topPanel.add(stateChoicePanel);
				//topPanel.add(Box.createRigidArea(new Dimension(300,0)));
				topPanel.add(paletteChoicePanel);


				menuPanel = new JPanel();
				menuPanel.setLayout(new BorderLayout());
				menuPanel.add(menuBar, BorderLayout.NORTH);
				menuPanel.add(topPanel, BorderLayout.CENTER);





		//--------------------------------------------------------------
		//MAP PANE
		//--------------------------------------------------------------

				mapCanvas = new MapCanvas(this);

				//mapCanvas.setSize(240, 160);
				//mapCanvas.addKeyListener(this);

				//mapCanvas.addMouseWheelListener(this);
				//mapCanvas.addKeyListener(this);

				//mapCanvas.setFloatBuffered(true);
				mapCanvas.setBackground(Color.DARK_GRAY);


				//mapScrollPane = new JScrollPane(mapCanvas,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
				//mapScrollPane.setWheelScrollingEnabled(false);
				//mapScrollPane.getViewport().setBackground(Color.DARK_GRAY);
				//mapScrollPane.setViewportView(mapCanvas);
				//mapScrollPane.getViewport().addKeyListener(this);//bob9-29-05
				//mapScrollPane.getViewport().addMouseWheelListener(this);//bob9-29-05
				//mapScrollPane.getViewport().setView(mapCanvas);

				mapScrollPane = new JScrollPane(mapCanvas,ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);//ScrollPane.SCROLLBARS_ALWAYS
				mapScrollPane.setWheelScrollingEnabled(false);
				mapScrollPane.setBackground(Color.DARK_GRAY);
				//mapScrollPane.setFloatBuffered(true);
				mapScrollPane.setFocusable(true);
				mapScrollPane.addKeyListener(this);//bob9-29-05
				//mapScrollPane.addMouseWheelListener(this);//bob9-29-05


				//mapScrollPane.getViewport().setFloatBuffered(true);
				mapScrollPane.getViewport().setFocusable(true);
				mapScrollPane.getViewport().addKeyListener(this);
				//mapScrollPane.getViewport().addMouseWheelListener(this);
				mapScrollPane.getViewport().setBackground(Color.DARK_GRAY);
				mapScrollPane.getViewport().setScrollMode(JViewport.SIMPLE_SCROLL_MODE);



				//mapScrollPane.addMouseListener(mapCanvas);



		//--------------------------------------------------------------
		//TILE PANE
		//--------------------------------------------------------------


				tileCanvas = new TileCanvas();


				tileScrollPane = new JScrollPane(tileCanvas,ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

				tileScrollPane.setSize(TileCanvas.WIDTH_TILES*TileCanvas.TILE_SIZE+22, 20);//was 150, 20
				tileScrollPane.setPreferredSize(new Dimension(TileCanvas.WIDTH_TILES*TileCanvas.TILE_SIZE+22, 20));//was 150, 20
				tileScrollPane.setMaximumSize(new Dimension(TileCanvas.WIDTH_TILES*TileCanvas.TILE_SIZE+22, 20));//was 150, 20
				tileScrollPane.setMinimumSize(new Dimension(TileCanvas.WIDTH_TILES*TileCanvas.TILE_SIZE+22, 20));//was 150, 20

				tileScrollPane.setFocusable(false);
				tileScrollPane.addKeyListener(tileCanvas);
				tileScrollPane.getViewport().setFocusable(true);
				tileScrollPane.getViewport().addKeyListener(tileCanvas);
				tileScrollPane.getViewport().setScrollMode(JViewport.SIMPLE_SCROLL_MODE);

				//tileScrollPane.add(tileCanvas);




		//--------------------------------------------------------------
		//CONTROL PANEL PANE
		//--------------------------------------------------------------
				controlPanel = new ControlPanel(this);

		//--------------------------------------------------------------
		//INFO LABEL PANE
		//--------------------------------------------------------------
				infoLabelPanel = new JPanel(new BorderLayout());
				infoLabelPanel.setForeground(Color.WHITE);
				infoLabelPanel.setBackground(Color.DARK_GRAY);


				statsLabel = new JLabel();
				statsLabel.setFont(new Font("Tahoma", Font.BOLD, 14));
				statsLabel.setForeground(Color.WHITE);
				statsLabel.setBackground(Color.BLACK);


				infoLabel = new InfoLabelPanel("", this);
				infoLabel.text.setFont(new Font("Tahoma", Font.BOLD, 16));
				infoLabel.setText("Ready!");

				infoLabelPanel.add(infoLabel, BorderLayout.CENTER);



				infoLabelPanel.add(statsLabel, BorderLayout.EAST);


		panel = new JPanel(new BorderLayout());

			panel.add(mapScrollPane, BorderLayout.CENTER);
			panel.add(tileScrollPane, BorderLayout.WEST);
			panel.add(controlPanel, BorderLayout.EAST);
			panel.add(menuPanel, BorderLayout.NORTH);
			panel.add(infoLabelPanel, BorderLayout.SOUTH);





		setLayout(new BorderLayout());
		add(panel, BorderLayout.CENTER);

		setLocation(60, 0);
		//setSize(2560-430, 1600-50);
		//setSize(1920-430, 1200-50);

		setSize(getScreenWidth()-370, getScreenHeight()-50);

		setVisible(true);
		toFront();



		repaint();
		topPanel.repaint();

		validate();



		//recursivelyAddKeyListener(mapScrollPane);
		//recursivelyAddKeyListener(mapScrollPane.getViewport());
		//recursivelyAddKeyListener(mapCanvas);
		//recursivelyAddKeyListener(controlPanel);


		//newProject();

		openProject("demo.zip");
		mapChoice.setSelectedIndex(1);


	}

	public static int getScreenWidth()
	{

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		int w = (int)screenSize.getWidth();
		//int h = (int)screenSize.getHeight();
		return w;
	}

	public static int getScreenHeight()
	{

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		//int w = (int)screenSize.getWidth();
		int h = (int)screenSize.getHeight();
		return h;
	}

	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{

			//if(c[i]!=tileScrollPane&&c[i]!=tileCanvas)
			{
				c[i].removeKeyListener(this);
				c[i].addKeyListener(this);
			}


			//if(c[i]!=tileScrollPane&&c[i]!=tileCanvas)
			if(c[i].getClass().equals(JPanel.class)||c[i].getClass().equals(JComponent.class)||c[i].getClass().equals(JScrollPane.class))
			{
				recursivelyAddKeyListener((Container) c[i]);
			}

		}

	}



	//===============================================================================================
	public void haltListeners()
	{//===============================================================================================

		setEnabled(false);

		// Menus
		fileMenu.setEnabled(false);
		editMenu.setEnabled(false);
		spritesMenu.setEnabled(false);
		tilesetMenu.setEnabled(false);
		mapMenu.setEnabled(false);
		paletteMenu.setEnabled(false);
		helpMenu.setEnabled(false);
		optionsMenu.setEnabled(false);

		// Choices
		paletteChoice.setEnabled(false);
		//tilesetChoice.setEnabled(false);
		mapChoice.setEnabled(false);
		stateChoice.setEnabled(false);

	}


	//===============================================================================================
	public void restartListeners()
	{//===============================================================================================

		// Menus
		fileMenu.setEnabled(true);
		editMenu.setEnabled(true);
		spritesMenu.setEnabled(true);
		tilesetMenu.setEnabled(true);
		mapMenu.setEnabled(true);
		paletteMenu.setEnabled(true);
		helpMenu.setEnabled(true);
		optionsMenu.setEnabled(true);


		// Choices
		paletteChoice.setEnabled(true);
		//tilesetChoice.setEnabled(true);
		mapChoice.setEnabled(true);
		stateChoice.setEnabled(true);

		setEnabled(true);

	}




	//===============================================================================================
	public void refreshTopPanelLayout()
	{//===============================================================================================


		//tilesetChoicePanel.doLayout();
		//mapChoice.setSize(new Dimension(mapChoice.getWidth(),600));
		mapChoicePanel.validate();
		stateChoicePanel.validate();
		paletteChoicePanel.validate();

		//tilesetChoice.doLayout();
		mapChoice.doLayout();
		stateChoice.doLayout();
		paletteChoice.doLayout();



		boxLayout.invalidateLayout(topPanel);
		topPanel.validate();


	}


	//===============================================================================================
	public void renameMap()
	{//===============================================================================================
		// RENAMING WINDOW
		rename.show(project.getSelectedMapName());
		if(!rename.wasCancelled)
		{
			Project.getSelectedMap().setName(rename.newName.getText());
		}
		int i = mapChoice.getSelectedIndex();
		mapChoice.insertItemAt(project.getSelectedMapName(), i);
		mapChoice.removeItemAt(i + 1);
		mapChoice.setSelectedIndex(i);
		refreshTopPanelLayout();
	}


	//===============================================================================================
	public void renameState()
	{//===============================================================================================
		// RENAMING WINDOW
		rename.show(Project.getSelectedMap().getSelectedState().name());
		if(!rename.wasCancelled)
		{
			Project.getSelectedMap().getSelectedState().setName(rename.newName.getText());
		}
		int i = stateChoice.getSelectedIndex();
		stateChoice.insertItemAt(Project.getSelectedMap().getSelectedState().name(), i);
		stateChoice.removeItemAt(i + 1);
		stateChoice.setSelectedIndex(i);
		refreshTopPanelLayout();
	}

	//===============================================================================================
	public void renamePalette()
	{//===============================================================================================
		// RENAMING WINDOW
		rename.show(project.getSelectedPaletteName());
		if(!rename.wasCancelled)
		{
			project.renamePalette(rename.newName.getText());
		}
		int i = paletteChoice.getSelectedIndex();
		paletteChoice.insertItemAt(project.getSelectedPaletteName(), i);
		paletteChoice.removeItemAt(i + 1);

		paletteChoice.setSelectedIndex(i);
		refreshTopPanelLayout();
	}

	//===============================================================================================
	public void moveMapUp()
	{//===============================================================================================

		project.moveMapUp();
		int selectedMap = Project.getSelectedMapIndex();

		mapChoice.removeAllItems();

		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}

		mapChoice.setSelectedIndex(selectedMap);
		mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}
	//===============================================================================================
	public void moveMapDown()
	{//===============================================================================================

		project.moveMapDown();
		int selectedMap = Project.getSelectedMapIndex();

		mapChoice.removeAllItems();

		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}

		mapChoice.setSelectedIndex(selectedMap);
		mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}

	//===============================================================================================
	public void moveStateUp()
	{//===============================================================================================

		int k = Project.getSelectedMap().getSelectedStateIndex();

		if(k<2)return;

		MapState s = Project.getSelectedMap().getSelectedState();

		Project.getSelectedMap().removeSelectedState();

		Project.getSelectedMap().addState(k-1,s);




		stateChoice.removeAllItems();

		for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
		{
			stateChoice.addItem(Project.getSelectedMap().getState(i).name());
		}

		stateChoice.setSelectedIndex(k);
		stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}
	//===============================================================================================
	public void moveStateDown()
	{//===============================================================================================

		int k = Project.getSelectedMap().getSelectedStateIndex();

		if(k==Project.getSelectedMap().getNumStates()-1)return;

		MapState s = Project.getSelectedMap().getSelectedState();

		Project.getSelectedMap().removeSelectedState();

		Project.getSelectedMap().addState(k+1,s);



		stateChoice.removeAllItems();

		for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
		{
			stateChoice.addItem(Project.getSelectedMap().getState(i).name());
		}

		stateChoice.setSelectedIndex(k);
		stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}

	//===============================================================================================
	public void duplicateState()
	{//===============================================================================================

		Project.getSelectedMap().duplicateState();
		int selectedState = Project.getSelectedMap().getSelectedStateIndex();

		stateChoice.removeAllItems();

		for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
		{
			stateChoice.addItem(Project.getSelectedMap().getState(i).name());
		}

		stateChoice.setSelectedIndex(selectedState);
		stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}

	//===============================================================================================
	public void duplicateMap()
	{//===============================================================================================

		project.duplicateMap();
		int selectedMap = Project.getSelectedMapIndex();

		mapChoice.removeAllItems();

		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}

		mapChoice.setSelectedIndex(selectedMap);
		mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
	}

	//===============================================================================================
	public void duplicatePalette()
	{//===============================================================================================
		project.duplicatePalette();
		paletteChoice.addItem(project.getSelectedPaletteName());
		paletteChoice.setSelectedItem(project.getSelectedPaletteName());
		itemStateChanged(new ItemEvent(paletteChoice, ItemEvent.ITEM_STATE_CHANGED, "", ItemEvent.SELECTED));
	}




	//===============================================================================================
	public void deleteMap()
	{//===============================================================================================

		if(Project.getNumMaps() <= 1)return;


		int i = mapChoice.getSelectedIndex();
		mapChoice.removeItemAt(i);

		project.deleteMap();

		mapChoice.setSelectedIndex(Project.getSelectedMapIndex());
		itemStateChanged(new ItemEvent(mapChoice, ItemEvent.ITEM_STATE_CHANGED, "", ItemEvent.SELECTED));

		refreshTopPanelLayout();
	}


	//===============================================================================================
	public void deleteState()
	{//===============================================================================================

		if(Project.getSelectedMap().getNumStates() <= 1)return;

		Project.getSelectedMap().removeSelectedState();
		int i = stateChoice.getSelectedIndex();
		stateChoice.removeItemAt(i);


		stateChoice.setSelectedIndex(Project.getSelectedMap().getSelectedStateIndex());
		itemStateChanged(new ItemEvent(stateChoice, ItemEvent.ITEM_STATE_CHANGED, "", ItemEvent.SELECTED));

		refreshTopPanelLayout();
	}

	//===============================================================================================
	public void deletePalette()
	{//===============================================================================================

		if(Project.getNumPalettes() <= 1)return;

		project.deletePalette();
		int i = paletteChoice.getSelectedIndex();
		paletteChoice.removeItemAt(i);


		paletteChoice.setSelectedIndex(0);
		itemStateChanged(new ItemEvent(paletteChoice, ItemEvent.ITEM_STATE_CHANGED, "", ItemEvent.SELECTED));

		refreshTopPanelLayout();
	}


	//===============================================================================================
	public void newProject()
	{//===============================================================================================

		boolean result = true;

		if(project_loaded)
		{
			//new yesno dialog
			YesNoWindow ynw = new YesNoWindow(this, "There is a project open. Are you sure?");
			ynw.setVisible(true);
			result = ynw.result;
		}

		if(result==true)
		{
			paletteChoice.removeAllItems();
			mapChoice.removeAllItems();
			stateChoice.removeAllItems();

			project = new Project(this,"Project");
			project_loaded = true;

			restartListeners();

			mapChoice.addItem(project.getSelectedMapName());
			paletteChoice.addItem(project.getSelectedPaletteName());
			stateChoice.addItem(Project.getSelectedMap().getSelectedState().name());


			saveProject.setEnabled(true);

			refreshTopPanelLayout();
			tileCanvas.updateAllTiles();
			tileCanvas.paint();
			controlPanel.repaint();

			mapCanvas.setSizedoLayout();
			mapCanvas.zoomOut();
			mapCanvas.zoomIn();
			mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
			//mapCanvas.fillUndoArray();

		}
	}



	//===============================================================================================
	public void appendNewMap()
	{//===============================================================================================

		Project.appendNewMap();

		int selectedMap = Project.getSelectedMapIndex();

		mapChoice.removeAllItems();


		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}


		mapChoice.setSelectedIndex(selectedMap);
		mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();

	}


	//===============================================================================================
	public void newState()
	{//===============================================================================================

		Project.getSelectedMap().addState("State"+Project.getSelectedMap().getNumStates());

		int selectedState = Project.getSelectedMap().getSelectedStateIndex();

		stateChoice.removeAllItems();
		for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
		{
			stateChoice.addItem(Project.getSelectedMap().getState(i).name());
		}


		stateChoice.setSelectedIndex(selectedState);
		stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());

		refreshTopPanelLayout();
		mapCanvas.setSizedoLayout();

		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();

	}

	//===============================================================================================
	public void newPalette()
	{//===============================================================================================
		project.createNewPalette();
		paletteChoice.addItem(project.getSelectedPaletteName());
		paletteChoice.setSelectedItem(project.getSelectedPaletteName());


		refreshTopPanelLayout();
		controlPanel.repaint();
		tileCanvas.updateAllTiles();
		tileCanvas.paint();
		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();

	}

	//===============================================================================================
	public void openProject(String s)
	{//===============================================================================================
		if(project_loaded)
		{
		}		// Ask to save previous project		*** ADD LATER ***



		// Halt listeners to prevent errors on float clicking to open
		haltListeners();




//		filedialog.setDialogType(JFileChooser.OPEN_DIALOG);
//		filedialog.showOpenDialog(this);
//		filedialog.getSelectedFile()
//		filedialog.getSelectedFile().getName()
//		filedialog.getSelectedFile().getParentFile().getPath()
		//filedialog.setMode(FileDialog.SAVE);
		//filedialog.setVisible(true);
//		filedialog.showSaveDialog(this);
	//
//		String filename = filedialog.getSelectedFile().getName();
	//
//		String directory = filedialog.getCurrentDirectory().getPath();
	//
//		String directory1 = filedialog.getSelectedFile().getParentFile().getPath();
//		String directory2 = filedialog.getCurrentDirectory().getPath();
//		System.out.println(directory1);
//		System.out.println(directory2);

		//filedialog.setMode(FileDialog.LOAD);
		//filedialog.setVisible(true);


		if(s==null)
		{
			int val = fileChooser.showOpenDialog(this);

			//fileChooser.firePropertyChange("viewType",FilePane.VIEWTYPE_LIST,FilePane.VIEWTYPE_LIST);

			if(val==JFileChooser.APPROVE_OPTION)
			{

				paletteChoice.removeAllItems();
				mapChoice.removeAllItems();
				stateChoice.removeAllItems();




				project = new Project(getFileDialogFileName(), getFileDialogDirectoryPath(), this);
			}
			else
			{
				restartListeners();
				return;
			}
		}
		else
		{

			paletteChoice.removeAllItems();
			mapChoice.removeAllItems();
			stateChoice.removeAllItems();

			project = new Project(s, "./", this);
		}



		project_loaded = true;



		restartListeners();




		saveProject.setEnabled(true);


		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}
		if(Project.getNumMaps() > 0)
		{
			mapChoice.setSelectedIndex(mapChoice.getItemCount() - 1);//project.getSelectedMapIndex());
		}


		for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
		{
			stateChoice.addItem(Project.getSelectedMap().getState(i).name());
		}
		stateChoice.setSelectedIndex(0);


		for(int i = 0; i < Project.getNumPalettes(); i++)
		{
			paletteChoice.addItem(Project.getPalette(i).name);
		}
		if(Project.getNumPalettes() > 0)
		{
			paletteChoice.setSelectedIndex(paletteChoice.getItemCount() - 1);//project.getSelectedPaletteIndex());
		}



		refreshTopPanelLayout();

		controlPanel.repaint();

		tileCanvas.setSizedoLayout();
		tileCanvas.updateAllTiles();
		//tileCanvas.paintBuffer();
		tileCanvas.paint();


		mapCanvas.setSizedoLayout();
		mapCanvas.zoomOut();
		mapCanvas.zoomIn();
		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();




	}

	//===============================================================================================
	public void mergeProject(String s)
	{//===============================================================================================
		if(s==null)
		{
			int val = fileChooser.showOpenDialog(this);

			if(val==JFileChooser.APPROVE_OPTION)
			{
				project.merge(getFileDialogFileName(), getFileDialogDirectoryPath());
			}
			else
			{
				return;
			}
		}
		else
		{
			project.merge(s, "./");
		}

		// Refresh UI after merge
		paletteChoice.removeAllItems();
		mapChoice.removeAllItems();
		stateChoice.removeAllItems();

		for(int i = 0; i < Project.getNumMaps(); i++)
		{
			mapChoice.addItem(Project.getMap(i).name());
		}
		if(Project.getNumMaps() > 0)
		{
			mapChoice.setSelectedIndex(Project.getSelectedMapIndex());
		}

		if(Project.getSelectedMap() != null) {
			for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
			{
				stateChoice.addItem(Project.getSelectedMap().getState(i).name());
			}
			if(stateChoice.getItemCount() > 0) stateChoice.setSelectedIndex(Project.getSelectedMap().getSelectedStateIndex());
		}

		for(int i = 0; i < Project.getNumPalettes(); i++)
		{
			paletteChoice.addItem(Project.getPalette(i).name);
		}
		if(Project.getNumPalettes() > 0)
		{
			paletteChoice.setSelectedIndex(Project.getSelectedPaletteIndex());
		}

		refreshTopPanelLayout();
		controlPanel.repaint();
		tileCanvas.setSizedoLayout();
		tileCanvas.updateAllTiles();
		tileCanvas.paint();
		mapCanvas.setSizedoLayout();
		mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		//mapCanvas.fillUndoArray();
		
		infoLabel.setTextSuccess("Merged Project Successfully");
	}

	//===============================================================================================
	public void saveProject()
	{//===============================================================================================



		//JFileChooser swingFileDialog = new JFileChooser();
		int val = fileChooser.showSaveDialog(this);

		if(val!=JFileChooser.APPROVE_OPTION)return;

		String filename = fileChooser.getSelectedFile().getName();
		String directory = fileChooser.getCurrentDirectory().getPath()+"\\";

		//filedialog.setMode(FileDialog.SAVE);
		//filedialog.setVisible(true);

		//String filename = filedialog.getFile();
		//String directory = filedialog.getDirectory();

		if(filename==null)return;

		if(filename.isEmpty())return;

		if(filename.endsWith(".zip"))filename=filename.substring(0, filename.length()-".zip".length());//remove ".zip"

		//if(filename.endsWith(".h")==false)filename=filename.concat(".h");//append ".h" if doesnt exist


		project.save(directory + filename, filename);
		infoLabel.setTextSuccess("Saved All to File: " + directory + filename);
	}







	//===============================================================================================
	public void viewSpriteEditor()
	{//===============================================================================================
		spriteEditor.showSpriteEditor();

		if(spriteEditor.getExtendedState() == Frame.ICONIFIED)
		{
			spriteEditor.setExtendedState(Frame.NORMAL);
		}

	}





	//===============================================================================================
	public void mapChoice()
	{//===============================================================================================

		//stop all current map mapsprite frame and animation timers

		if(Project.getSelectedMap()!=null)
		{
			for(int n=0;n<Project.getSelectedMap().getNumEntities();n++)
			{
				if(Project.getSelectedMap().getEntity(n).animatingThroughAllFrames())
				{
					Project.getSelectedMap().getEntity(n).frameTimer.stop();
					Project.getSelectedMap().getEntity(n).startAnimationTimer.stop();
				}
			}

		}


		if(mapChoice.getSelectedIndex()>=0)
		{
			Project.setSelectedMapIndex(mapChoice.getSelectedIndex());


			stateChoice.removeAllItems();
			for(int i = 0; i < Project.getSelectedMap().getNumStates(); i++)
			{
				stateChoice.addItem(Project.getSelectedMap().getState(i).name());
			}

			if(stateChoice.getItemCount()>0)stateChoice.setSelectedIndex(Project.getSelectedMap().getSelectedStateIndex());

			refreshTopPanelLayout();

			mapCanvas.setSizedoLayout();
			mapCanvas.zoomOut();
			mapCanvas.zoomIn();

			//definitely have to update everything
			mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
			//mapCanvas.fillUndoArray();

			//start all mapsprite animation timers
			for(int n=0;n<Project.getSelectedMap().getNumEntities();n++)
			{
				if(Project.getSelectedMap().getEntity(n).animatingThroughAllFrames())
				{
					Project.getSelectedMap().getEntity(n).startAnimationTimer.start();
				}
			}

			if(Project.getSelectedMap().mapNote().length()>0)ControlPanel.openNoteEditorButton.setBackground(Color.GREEN);
			else ControlPanel.openNoteEditorButton.setBackground(Color.GRAY);
		}
	}


	//===============================================================================================
	public void stateChoice()
	{//===============================================================================================

		//stop all current map mapsprite frame and animation timers

		if(Project.getSelectedMap()!=null)
		{
			for(int n=0;n<Project.getSelectedMap().getNumEntities();n++)
			{
				if(Project.getSelectedMap().getEntity(n).animatingThroughAllFrames())
				{
					Project.getSelectedMap().getEntity(n).frameTimer.stop();
					Project.getSelectedMap().getEntity(n).startAnimationTimer.stop();
				}
			}

		}

		if(stateChoice.getSelectedIndex()>=0)
		{
			if(stateChoice.getSelectedIndex()==0)
			{
				stateChoice.setForeground(Color.BLACK);
				stateChoicePanel.setBackground(mapChoicePanel.getBackground());
			}
			else
			{
				stateChoice.setForeground(Color.RED);
				stateChoicePanel.setBackground(new Color(230,150,150));
			}


			Project.getSelectedMap().setSelectedState(stateChoice.getSelectedIndex());
			refreshTopPanelLayout();
			mapCanvas.setSizedoLayout();

			//definitely have to update everything
			mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
			//mapCanvas.fillUndoArray();

			//start all mapsprite animation timers
			for(int n=0;n<Project.getSelectedMap().getNumEntities();n++)
			{
				if(Project.getSelectedMap().getEntity(n).animatingThroughAllFrames())
				{
					Project.getSelectedMap().getEntity(n).startAnimationTimer.start();
				}
			}

			if(Project.getSelectedMap().mapNote().length()>0)ControlPanel.openNoteEditorButton.setBackground(Color.GREEN);
			else ControlPanel.openNoteEditorButton.setBackground(Color.GRAY);
		}
	}


	//===============================================================================================
	public void paletteChoice()
	{//===============================================================================================

		if(paletteChoice.getSelectedIndex()>=0)
		{
			project.setSelectedPaletteIndex(paletteChoice.getSelectedIndex());
			tileCanvas.updateAllTiles();
			tileCanvas.paint();
			controlPanel.repaint();

			//definitely have to update everything
			mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
			//mapCanvas.fillUndoArray();

		}
	}


	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================




		if(ae.getSource() == moveUnusedTilesToBottom)Project.tileset.moveUnusedTilesToBottom(this);
		else if(ae.getSource() == removeUnusedTiles)Project.tileset.removeUnusedTiles(this);
		else if(ae.getSource() == crunchTileset)Project.tileset.crunchTiles(this);
		else if(ae.getSource() == mergeDuplicateTiles)Project.tileset.mergeDuplicateTiles(this);
		else if(ae.getSource() == mergeBlankTiles)Project.tileset.mergeBlankTiles(this);
		else if(ae.getSource() == setBlankTilesToSelectedColor)Project.tileset.setBlankTilesToSelectedColor(this);
		else if(ae.getSource() == removeBlankRows)Project.tileset.removeBlankRows(this);
		else if(ae.getSource() == mergeDuplicatesAndRemoveEmptySpacePastSelectedTile)Project.tileset.mergeDuplicatesAndRemoveEmptySpacePastSelectedTile(this);
		else if(ae.getSource() == countUsedTilesSelectedMap)project.countUsedTilesSelectedMap();
		else if(ae.getSource() == findLeastUsedTileOnMap)project.findLeastUsedTileOnSelectedMap(this);
		else if(ae.getSource() == countUsedTilesWholeTileset)project.countUsedTilesAllMaps();
		else if(ae.getSource() == findFirstMapWithSelectedTile)project.findFirstMapWithSelectedTile(this);
		else if(ae.getSource() == findFirstTileUsingSelectedColor)Project.tileset.findFirstTileUsingSelectedColor(this);
		else if(ae.getSource() == listDoorsThatAreBroken)project.listDoorsThatAreBroken();
		else if(ae.getSource() == findLeastUsedColor)Project.tileset.findLeastUsedColor(this);
		else if(ae.getSource() == removeUnusedPaletteColors)Project.tileset.removeUnusedPaletteColors(this);
		else if(ae.getSource() == mergeDuplicatePaletteColors)Project.tileset.mergeDuplicatePaletteColors(this);
		else if(ae.getSource() == sortPaletteHSB)Project.getSelectedPalette().sortPaletteHSB(this);
		else if(ae.getSource() == mergePaletteH)Project.getSelectedPalette().mergePaletteH(this);
		else if(ae.getSource() == mergePaletteS)Project.getSelectedPalette().mergePaletteS(this);
		else if(ae.getSource() == mergePaletteB)Project.getSelectedPalette().mergePaletteB(this);
		else if(ae.getSource() == brightenPaletteHSB)Project.getSelectedPalette().brightenPaletteHSB(this);
		else if(ae.getSource() == darkenPaletteHSB)Project.getSelectedPalette().darkenPaletteHSB(this);
		else if(ae.getSource() == roundPaletteHSB)Project.getSelectedPalette().roundPaletteHSB(this);
		else if(ae.getSource() == standardizePaletteRangeHSB)Project.getSelectedPalette().standardizePaletteRangeHSB(this);
		else if(ae.getSource() == resizeMap)mapCanvas.mapSizeWindow.show();
		else if(ae.getSource() == renameMap)renameMap();
		else if(ae.getSource() == renamePalette)renamePalette();
		else if(ae.getSource() == duplicateMap)duplicateMap();
		else if(ae.getSource() == moveMapUp)moveMapUp();
		else if(ae.getSource() == moveMapDown)moveMapDown();

		else if(ae.getSource() == newState)newState();
		else if(ae.getSource() == duplicateState)duplicateState();
		else if(ae.getSource() == renameState)renameState();
		else if(ae.getSource() == deleteState)deleteState();
		else if(ae.getSource() == moveStateUp)moveStateUp();
		else if(ae.getSource() == moveStateDown)moveStateDown();

		else if(ae.getSource() == duplicatePalette)duplicatePalette();
		else if(ae.getSource() == insertTilesetRows)Project.tileset.insertTilesetRows(this);
		else if(ae.getSource() == importImageToTileset)Project.tileset.importImageToTileset(this);
		else if(ae.getSource() == deleteMap)deleteMap();
		else if(ae.getSource() == deletePalette)deletePalette();
		else if(ae.getSource() == viewZoomIn)mapCanvas.zoomIn();
		else if(ae.getSource() == viewZoomOut)mapCanvas.zoomOut();
		else if(ae.getSource() == exit)exit();
		else if(ae.getSource() == newProject)newProject();

		else if(ae.getSource() == previewMapInClient)project.previewMapInClient();
		else if(ae.getSource() == newMap)appendNewMap();
		else if(ae.getSource() == newPalette)newPalette();
		else if(ae.getSource() == openProject)openProject(null);
		else if(ae.getSource() == mergeProject)mergeProject(null);
		else if(ae.getSource() == saveProject)saveProject();

		else if(ae.getSource() == saveCurrentMapPNGForEachLayer)project.saveCurrentMapPNGForEachLayer();
		else if(ae.getSource() == saveAllMapsPNGForEachLayer)project.saveAllMapsPNGForEachLayer();

		else if(ae.getSource() == saveCurrentMapCombinedLayersToPNG)project.saveCurrentMapCombinedLayersToPNG();
		else if(ae.getSource() == saveAllMapsCombinedLayersToPNG)project.saveAllMapsCombinedLayersToPNG();

		else if(ae.getSource() == saveCurrentMapCombinedLayersToHQ2XPNG)project.saveCurrentMapCombinedLayersToHQ2XPNG();
		else if(ae.getSource() == saveAllMapsCombinedLayersToHQ2XPNG)project.saveAllMapsCombinedLayersToHQ2XPNG();


		else if(ae.getSource() == exportProject)project.exportProject();
		else if(ae.getSource() == exportProjectAsGameData)project.exportProjectAsGameDataFile();
		else if(ae.getSource() == exportProjectToWorkspaceLibGDXAssetsFolderForHTML5)project.exportProjectToWorkspaceLibGDXAssetsFolderForHTML5();

		else if(ae.getSource() == editUndo) {
			if (lastActiveCanvas == tileCanvas) tileCanvas.undo();
			else mapCanvas.undo();
		}
		else if(ae.getSource() == editRedo) {
			if (lastActiveCanvas == tileCanvas) tileCanvas.redo();
			else mapCanvas.redo();
		}
		else if(ae.getSource() == openSpriteEditor)viewSpriteEditor();
		else if(ae.getSource() == openSoundAndMusicEditor)soundAndMusicEditor.showSoundAndMusicEditor();
		else if(ae.getSource() == openCutsceneEditor)projectCutsceneEditWindow.showProjectCutsceneEditorWindow();
		else if(ae.getSource() == copySelectionCoordsToClipboard)mapCanvas.mapSelectionArea.copySelectionCoordsToClipboard();

	}


	//===============================================================================================
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================


		if(ie.getSource() == mapChoice){if(ie.getItem().equals(project.getSelectedMapName())==false)mapChoice();}
		else if(ie.getSource() == stateChoice){if(ie.getItem().equals(Project.getSelectedMap().getSelectedState().name())==false)stateChoice();}
		else if(ie.getSource() == paletteChoice){if(ie.getItem().equals(project.getSelectedPaletteName())==false)paletteChoice();}

		else if(ie.getSource() == viewTileGrid)tileCanvas.toggleTileGrid(this);
		else if(ie.getSource() == viewMapGrid)mapCanvas.toggleMapGrid();

		else if(ie.getSource() == bufferCheck)mapCanvas.toggleLayerImageBuffer();
		else if(ie.getSource() == previewMode)mapCanvas.togglePreviewMode();
		else if(ie.getSource() == soundsOnOff)infoLabel.toggleSoundsOnOff();

		else if(ie.getSource() == toggleLightBlackMasking)mapCanvas.toggleLightBlackMasking();
		else if(ie.getSource() == toggleLightScreenBlending)mapCanvas.toggleLightScreenBlending();
		else if(ie.getSource() == toggleMoveEntityByPixel)mapCanvas.toggleMoveEntityByPixel();
		else if(ie.getSource() == toggleAreaSpriteInfo) {MapCanvas.alwaysShowAreaAndSpriteInfo = !MapCanvas.alwaysShowAreaAndSpriteInfo;mapCanvas.repaint();}
		else if(ie.getSource() == toggleAreaOutlines) {MapCanvas.alwaysShowAreaOutlines = !MapCanvas.alwaysShowAreaOutlines;mapCanvas.repaint();}
		else if(ie.getSource() == toggleRandomPointOfInterestLines) {MapCanvas.drawRandomPointOfInterestLines = !MapCanvas.drawRandomPointOfInterestLines;mapCanvas.repaint();}
		else if(ie.getSource() == toggleTileEditMode) {MapCanvas.tileEditMode = !MapCanvas.tileEditMode;}
		else if(ie.getSource() == toggleAutoTileMode) {MapCanvas.autoTileMode = !MapCanvas.autoTileMode;}
	}




	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================
		if(ke.getKeyCode() == KeyEvent.VK_DELETE)
		{
			if(MapCanvas.selectedLayer==MapData.MAP_DOOR_LAYER && controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())
			{
				mapCanvas.deleteSelectedDoor();

			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER && controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
			{
				mapCanvas.deleteSelectedEntity();

			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_LIGHT_LAYER && controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())
			{
				mapCanvas.deleteSelectedLight();

			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER && controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
			{
				mapCanvas.deleteSelectedArea();

			}
			else
			{
				//mapCanvas.fillUndoArray();
				mapCanvas.mapSelectionArea.delete();
			}
		}

		if(ke.getKeyCode() == KeyEvent.VK_X && ke.isControlDown())
		{
			mapCanvas.mapSelectionArea.cut();
		}

		if(ke.getKeyCode() == KeyEvent.VK_V && ke.isControlDown())
		{
			//mapCanvas.fillUndoArray();
			mapCanvas.mapSelectionArea.paste();
		}

		if(ke.getKeyCode() == KeyEvent.VK_C && ke.isControlDown())
		{
			if(ke.isShiftDown())
			{
				mapCanvas.mapSelectionArea.copyEnabledLayers();
			}
			else
			{
				mapCanvas.mapSelectionArea.copy();
			}
		}


		if(ke.getKeyCode() == KeyEvent.VK_Z && ke.isControlDown())
		{
			mapCanvas.undo();
		}

		if(ke.getKeyCode() == KeyEvent.VK_Y && ke.isControlDown())
		{
			mapCanvas.redo();
		}

		if(ke.getKeyCode() == KeyEvent.VK_MINUS)
		{
			mapCanvas.zoomOut();
		}

		if(ke.getKeyCode() == KeyEvent.VK_EQUALS)
		{
			mapCanvas.zoomIn();

		}






		if(ke.getKeyCode() == KeyEvent.VK_BACK_QUOTE)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())controlPanel.toggleSoloLayerCheckbox(0);
				else controlPanel.toggleLayerCheckbox(0);
			}
			else controlPanel.setSelectedLayerIfEnabled(0);
		}

		if(ke.getKeyCode() == KeyEvent.VK_1 || ke.getKeyCode() == KeyEvent.VK_NUMPAD1)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())controlPanel.toggleSoloLayerCheckbox(1);
				else controlPanel.toggleLayerCheckbox(1);
			}
			else controlPanel.setSelectedLayerIfEnabled(1);
		}

		if(ke.getKeyCode() == KeyEvent.VK_2 || ke.getKeyCode() == KeyEvent.VK_NUMPAD2)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())controlPanel.toggleSoloLayerCheckbox(2);
				else controlPanel.toggleLayerCheckbox(2);
			}
			else controlPanel.setSelectedLayerIfEnabled(2);
		}

		if(ke.getKeyCode() == KeyEvent.VK_3 || ke.getKeyCode() == KeyEvent.VK_NUMPAD3)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(3);
				}
				else
				controlPanel.toggleLayerCheckbox(3);
			}
			else controlPanel.setSelectedLayerIfEnabled(3);
		}

		if(ke.getKeyCode() == KeyEvent.VK_4 || ke.getKeyCode() == KeyEvent.VK_NUMPAD4)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(4);
				}
				else
				controlPanel.toggleLayerCheckbox(4);
			}
			else controlPanel.setSelectedLayerIfEnabled(4);
		}

		if(ke.getKeyCode() == KeyEvent.VK_5 || ke.getKeyCode() == KeyEvent.VK_NUMPAD5)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(5);
				}
				else
				controlPanel.toggleLayerCheckbox(5);
			}
			else controlPanel.setSelectedLayerIfEnabled(5);
		}

		if(ke.getKeyCode() == KeyEvent.VK_6 || ke.getKeyCode() == KeyEvent.VK_NUMPAD6)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(6);
				}
				else
				controlPanel.toggleLayerCheckbox(6);
			}
			else controlPanel.setSelectedLayerIfEnabled(6);
		}

		if(ke.getKeyCode() == KeyEvent.VK_7 || ke.getKeyCode() == KeyEvent.VK_NUMPAD7)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(7);
				}
				else
				controlPanel.toggleLayerCheckbox(7);
			}
			else controlPanel.setSelectedLayerIfEnabled(7);
		}


		if(ke.getKeyCode() == KeyEvent.VK_8 || ke.getKeyCode() == KeyEvent.VK_NUMPAD8)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(8);
				}
				else
				controlPanel.toggleLayerCheckbox(8);
			}
			else controlPanel.setSelectedLayerIfEnabled(8);
		}

		if(ke.getKeyCode() == KeyEvent.VK_9 || ke.getKeyCode() == KeyEvent.VK_NUMPAD9)
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(9);
				}
				else
				controlPanel.toggleLayerCheckbox(9);
			}
			else controlPanel.setSelectedLayerIfEnabled(9);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F1)//sprite layer
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_ENTITY_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_ENTITY_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_ENTITY_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F2)//light mask
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_LIGHT_MASK_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_LIGHT_MASK_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_LIGHT_MASK_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F3)//lights
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_LIGHT_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_LIGHT_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_LIGHT_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F4)//fx
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_CAMERA_BOUNDS_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_CAMERA_BOUNDS_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_CAMERA_BOUNDS_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F5)//hit
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_HIT_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_HIT_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_HIT_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F6)//actions
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_AREA_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_AREA_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_AREA_LAYER);
		}

		if(ke.getKeyCode() == KeyEvent.VK_F7)//doors
		{
			if(ke.isControlDown())
			{
				if(ke.isShiftDown())
				{
					controlPanel.toggleSoloLayerCheckbox(MapData.MAP_DOOR_LAYER);
				}
				else
				controlPanel.toggleLayerCheckbox(MapData.MAP_DOOR_LAYER);
			}
			else controlPanel.setSelectedLayerIfEnabled(MapData.MAP_DOOR_LAYER);
		}






		if(ke.getKeyCode() == KeyEvent.VK_A)
		{

			if(MapCanvas.selectedAllLayers==false)
			{
				controlPanel.allLayersLabel.setForeground(Color.GREEN);
				MapCanvas.selectedAllLayers = true;
				mapCanvas.repaint();
			}
		}

		if(ke.getKeyCode() == KeyEvent.VK_L)
		{

			if(MapCanvas.lockPressed==false)
			{
				MapCanvas.lockPressed = true;
				mapCanvas.repaint();
			}
		}

		if(ke.getKeyCode() == KeyEvent.VK_F)
		{

			EditorMain.tileCanvas.scrollToSelectedTile();

		}

		if(ke.getKeyCode() == KeyEvent.VK_T)
		{
			mapCanvas.fillSelectionWithSelectedTile();
		}


		if(ke.getKeyCode() == KeyEvent.VK_UP)
		{

			if(mapCanvas.previewMode == 1)
			{
				mapCanvas.previewY -= 8;
				mapCanvas.repaint();
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
				{
					//if action selected
					if(Project.getSelectedMap().getSelectedAreaIndex()!=-1)
					{
						if(ke.isControlDown())
						{
							Area a = Project.getSelectedMap().getSelectedArea();

							//move action up 8 pixels, add 8 height
							a.setYPixels(a.yP()-8);
							a.setHeightPixels(a.hP()+8);
						}
						else
						{
							//move action up 8 pixels
							Area a = Project.getSelectedMap().getSelectedArea();
							a.setYPixels(a.yP()-8);
						}
						mapCanvas.repaint();
					}
				}
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
				{
					//if sprite selected
					if(Project.getSelectedMap().getSelectedEntityIndex()!=-1)
					{
						Entity e = Project.getSelectedMap().getSelectedEntity();

						//move sprite up 8 pixels
						e.setYPixels(e.yP()-8);

						int sx = e.xT();
						int sy = e.yT()+1;
						int sw = e.wT()+1;
						int sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

						sx = e.xT();
						sy = e.yT();
						sw = e.wT()+1;
						sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);
						mapCanvas.repaint();
					}
				}
			}
			else
			{
				tileCanvas.moveTileCursorUp();

			}

		}

		if(ke.getKeyCode() == KeyEvent.VK_DOWN)
		{

			if(mapCanvas.previewMode == 1)
			{
				mapCanvas.previewY += 8;
				mapCanvas.repaint();
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
				{
					//if action selected
					if(Project.getSelectedMap().getSelectedAreaIndex()!=-1)
					{
						if(ke.isControlDown())
						{
							Area a = Project.getSelectedMap().getSelectedArea();

							//move action down 8 pixels, add 8 height
							//Project.getSelectedMap().getSelectedArea().mapY-=8;
							a.setHeightPixels(a.hP()+8);
						}
						else
						{
							//move action down 8 pixels
							Area a = Project.getSelectedMap().getSelectedArea();
							a.setYPixels(a.yP()+8);
						}
						mapCanvas.repaint();
					}
				}
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
				{
					//if sprite selected
					if(Project.getSelectedMap().getSelectedEntityIndex()!=-1)
					{
						Entity e = Project.getSelectedMap().getSelectedEntity();

						//move sprite down 8 pixels
						e.setYPixels(e.yP()+8);

						int sx = e.xT();
						int sy = e.yT()-1;
						int sw = e.wT()+1;
						int sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

						sx = e.xT();
						sy = e.yT();
						sw = e.wT()+1;
						sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);
						mapCanvas.repaint();
					}
				}
			}
			else
			{
				tileCanvas.moveTileCursorDown();
			}

		}

		if(ke.getKeyCode() == KeyEvent.VK_RIGHT)
		{

			if(mapCanvas.previewMode == 1)
			{
				mapCanvas.previewX += 8;
				mapCanvas.repaint();
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
				{
					//if action selected
					if(Project.getSelectedMap().getSelectedAreaIndex()!=-1)
					{
						if(ke.isControlDown())
						{
							Area a = Project.getSelectedMap().getSelectedArea();
							//add 8 width
							//Project.getSelectedMap().getSelectedArea().mapX+=8;
							a.setWidthPixels(a.wP()+8);
						}
						else
						{
							//move action right 8 pixels
							Area a = Project.getSelectedMap().getSelectedArea();
							a.setXPixels(a.xP()+8);
						}
						mapCanvas.repaint();
					}
				}
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
				{
					//if sprite selected
					if(Project.getSelectedMap().getSelectedEntityIndex()!=-1)
					{
						Entity e = Project.getSelectedMap().getSelectedEntity();

						//move sprite right 8 pixels
						e.setXPixels(e.xP()+8);

						int sx = e.xT()-1;
						int sy = e.yT();
						int sw = e.wT()+1;
						int sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

						sx = e.xT();
						sy = e.yT();
						sw = e.wT()+1;
						sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);
						mapCanvas.repaint();
					}
				}
			}
			else
			{
				tileCanvas.moveTileCursorRight();
			}

		}

		if(ke.getKeyCode() == KeyEvent.VK_LEFT)
		{

			if(mapCanvas.previewMode == 1)
			{
				mapCanvas.previewX -= 8;
				mapCanvas.repaint();
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
				{
					//if action selected
					if(Project.getSelectedMap().getSelectedAreaIndex()!=-1)
					{
						if(ke.isControlDown())
						{
							Area a = Project.getSelectedMap().getSelectedArea();
							//move action left 8 pixels, add 8 width
							a.setXPixels(a.xP()-8);
							a.setWidthPixels(a.wP()+8);
						}
						else
						{
							//move action left 8 pixels
							Area a = Project.getSelectedMap().getSelectedArea();
							a.setXPixels(a.xP()-8);
						}
						mapCanvas.repaint();
					}
				}
			}
			else
			if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
			{
				if(controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
				{
					//if sprite selected
					if(Project.getSelectedMap().getSelectedEntityIndex()!=-1)
					{

						Entity e = Project.getSelectedMap().getSelectedEntity();

						//move sprite left 8 pixels
						e.setXPixels(e.xP()-8);


						int sx = e.xT()+1;
						int sy = e.yT();
						int sw = e.wT()+1;
						int sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

						sx = e.xT();
						sy = e.yT();
						sw = e.wT()+1;
						sh = e.hT()+1;

						for(int x=sx;x<sx+sw;x++)
						for(int y=sy;y<sy+sh;y++)
							mapCanvas.paintTileXY(MapData.MAP_ENTITY_LAYER,x,y);

						mapCanvas.repaint();
					}
				}
			}
			else
			{
				tileCanvas.moveTileCursorLeft();
			}

		}

		if(ke.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{

			if(mapChoice.getSelectedIndex() - 1 >= 0)
			{
				mapChoice.setSelectedIndex(mapChoice.getSelectedIndex() - 1);
			}
			mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());
			//itemStateChanged(new ItemEvent(mapChoice,701,"",1));

		}

		if(ke.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{

			if(mapChoice.getSelectedIndex() + 1 < mapChoice.getItemCount())
			{
				mapChoice.setSelectedIndex(mapChoice.getSelectedIndex() + 1);
			}
			mapChoice.paintImmediately(0, 0, mapChoice.getWidth(), mapChoice.getHeight());
			//itemStateChanged(new ItemEvent(mapChoice,701,"",1));

		}


		if(ke.getKeyCode() == KeyEvent.VK_HOME)
		{

			if(Project.getSelectedMap().getSelectedStateIndex()>0)
			{


				int prevState = Project.getSelectedMap().getSelectedStateIndex()-1;

				if(ke.isControlDown())
				{
					if(mapCanvas.mapSelectionArea.isShowing)
					{

						int sX1 = mapCanvas.mapSelectionArea.x1;
						int sX2 = mapCanvas.mapSelectionArea.x2;
						int sY1 = mapCanvas.mapSelectionArea.y1;
						int sY2 = mapCanvas.mapSelectionArea.y2;

						if(MapCanvas.selectedLayer!=MapData.MAP_LIGHT_LAYER){sX1*=8;sX2*=8;sY1*=8;sY2*=8;}

						//copy all areas/lights/doors/sprites under selection area into previous state
						for(int i=0; i<Project.getSelectedMap().getNumAreas(); i++)
						{
							Area a = Project.getSelectedMap().getArea(i);

							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyAreaToState(i,prevState);}
						}


						for(int i=0; i<Project.getSelectedMap().getNumEntities(); i++)
						{
							Entity a = Project.getSelectedMap().getEntity(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyEntityToState(i,prevState);}
						}

						for(int i=0; i<Project.getSelectedMap().getNumLights(); i++)
						{
							Light a = Project.getSelectedMap().getLight(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyLightToState(i,prevState);}
						}
					}
					else
					{
						//copy selected areas/lights/doors/sprites under selection area into previous state
						if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
						Project.getSelectedMap().copyAreaToState(Project.getSelectedMap().getSelectedAreaIndex(),prevState);


						if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
						Project.getSelectedMap().copyEntityToState(Project.getSelectedMap().getSelectedEntityIndex(),prevState);

						if(MapCanvas.selectedLayer==MapData.MAP_LIGHT_LAYER)
						Project.getSelectedMap().copyLightToState(Project.getSelectedMap().getSelectedLightIndex(),prevState);
					}

				}
				else
				if(ke.isShiftDown())
				{
					if(mapCanvas.mapSelectionArea.isShowing)
					{

						int sX1 = mapCanvas.mapSelectionArea.x1;
						int sX2 = mapCanvas.mapSelectionArea.x2;
						int sY1 = mapCanvas.mapSelectionArea.y1;
						int sY2 = mapCanvas.mapSelectionArea.y2;

						if(MapCanvas.selectedLayer!=MapData.MAP_LIGHT_LAYER){sX1*=8;sX2*=8;sY1*=8;sY2*=8;}

						//move all areas/lights/doors/sprites under selection area into previous state
						for(int i=0; i<Project.getSelectedMap().getNumAreas(); i++)
						{
							Area a = Project.getSelectedMap().getArea(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveAreaToState(i,prevState);i--;}
						}


						for(int i=0; i<Project.getSelectedMap().getNumEntities(); i++)
						{
							Entity a = Project.getSelectedMap().getEntity(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveEntityToState(i,prevState);i--;}
						}

						for(int i=0; i<Project.getSelectedMap().getNumLights(); i++)
						{
							Light a = Project.getSelectedMap().getLight(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveLightToState(i,prevState);i--;}
						}
					}
					else
					{
						//move selected areas/lights/doors/sprites under selection area into previous state
						if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
						Project.getSelectedMap().moveAreaToState(Project.getSelectedMap().getSelectedAreaIndex(),prevState);


						if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
						Project.getSelectedMap().moveEntityToState(Project.getSelectedMap().getSelectedEntityIndex(),prevState);

						if(MapCanvas.selectedLayer==MapData.MAP_LIGHT_LAYER)
						Project.getSelectedMap().moveLightToState(Project.getSelectedMap().getSelectedLightIndex(),prevState);
					}

					Project.getSelectedMap().setSelectedAreaIndex(-1);
					Project.getSelectedMap().setSelectedDoorIndex(-1);
					Project.getSelectedMap().setSelectedEntityIndex(-1);
					Project.getSelectedMap().setSelectedLightIndex(-1);
					mapCanvas.repaint();
				}
				else
				{

					if(stateChoice.getSelectedIndex() > 0)
					{
						stateChoice.setSelectedIndex(stateChoice.getSelectedIndex() - 1);
					}
					stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());
					//itemStateChanged(new ItemEvent(stateChoice,701,"",1));
				}


			}

		}

		if(ke.getKeyCode() == KeyEvent.VK_END)
		{

			if(Project.getSelectedMap().getSelectedStateIndex()<Project.getSelectedMap().getNumStates()-1)
			{

				int nextState = Project.getSelectedMap().getSelectedStateIndex()+1;

				if(ke.isControlDown())
				{
					if(mapCanvas.mapSelectionArea.isShowing)
					{

						int sX1 = mapCanvas.mapSelectionArea.x1;
						int sX2 = mapCanvas.mapSelectionArea.x2;
						int sY1 = mapCanvas.mapSelectionArea.y1;
						int sY2 = mapCanvas.mapSelectionArea.y2;

						if(MapCanvas.selectedLayer!=MapData.MAP_LIGHT_LAYER){sX1*=8;sX2*=8;sY1*=8;sY2*=8;}

						//copy all areas/lights/doors/sprites under selection area into Next state
						for(int i=0; i<Project.getSelectedMap().getNumAreas(); i++)
						{
							Area a = Project.getSelectedMap().getArea(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyAreaToState(i,nextState);}
						}


						for(int i=0; i<Project.getSelectedMap().getNumEntities(); i++)
						{
							Entity a = Project.getSelectedMap().getEntity(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyEntityToState(i,nextState);}
						}

						for(int i=0; i<Project.getSelectedMap().getNumLights(); i++)
						{
							Light a = Project.getSelectedMap().getLight(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().copyLightToState(i,nextState);}
						}

					}
					else
					{
						//copy selected areas/lights/doors/sprites under selection area into Next state
						if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
						Project.getSelectedMap().copyAreaToState(Project.getSelectedMap().getSelectedAreaIndex(),nextState);

						if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
						Project.getSelectedMap().copyEntityToState(Project.getSelectedMap().getSelectedEntityIndex(),nextState);

						if(MapCanvas.selectedLayer==MapData.MAP_LIGHT_LAYER)
						Project.getSelectedMap().copyLightToState(Project.getSelectedMap().getSelectedLightIndex(),nextState);

					}

				}
				else
				if(ke.isShiftDown())
				{
					if(mapCanvas.mapSelectionArea.isShowing)
					{

						int sX1 = mapCanvas.mapSelectionArea.x1;
						int sX2 = mapCanvas.mapSelectionArea.x2;
						int sY1 = mapCanvas.mapSelectionArea.y1;
						int sY2 = mapCanvas.mapSelectionArea.y2;

						if(MapCanvas.selectedLayer!=MapData.MAP_LIGHT_LAYER){sX1*=8;sX2*=8;sY1*=8;sY2*=8;}

						//move all areas/lights/doors/sprites under selection area into Next state
						for(int i=0; i<Project.getSelectedMap().getNumAreas(); i++)
						{
							Area a = Project.getSelectedMap().getArea(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveAreaToState(i,nextState);i--;}
						}


						for(int i=0; i<Project.getSelectedMap().getNumEntities(); i++)
						{
							Entity a = Project.getSelectedMap().getEntity(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveEntityToState(i,nextState);i--;}
						}

						for(int i=0; i<Project.getSelectedMap().getNumLights(); i++)
						{
							Light a = Project.getSelectedMap().getLight(i);
							if(a.xP()<sX2&&a.xP()+a.wP()>sX1&&a.yP()<sY2&&a.yP()+a.hP()>sY1)
								{Project.getSelectedMap().moveLightToState(i,nextState);i--;}
						}
					}
					else
					{
						//move selected areas/lights/doors/sprites under selection area into Next state
						if(MapCanvas.selectedLayer==MapData.MAP_AREA_LAYER)
						Project.getSelectedMap().moveAreaToState(Project.getSelectedMap().getSelectedAreaIndex(),nextState);


						if(MapCanvas.selectedLayer==MapData.MAP_ENTITY_LAYER)
						Project.getSelectedMap().moveEntityToState(Project.getSelectedMap().getSelectedEntityIndex(),nextState);

						if(MapCanvas.selectedLayer==MapData.MAP_LIGHT_LAYER)
						Project.getSelectedMap().moveLightToState(Project.getSelectedMap().getSelectedLightIndex(),nextState);
					}

					Project.getSelectedMap().setSelectedAreaIndex(-1);
					Project.getSelectedMap().setSelectedDoorIndex(-1);
					Project.getSelectedMap().setSelectedEntityIndex(-1);
					Project.getSelectedMap().setSelectedLightIndex(-1);
					mapCanvas.repaint();
				}
				else
				{


					if(stateChoice.getSelectedIndex() < stateChoice.getItemCount()-1)
					{
						stateChoice.setSelectedIndex(stateChoice.getSelectedIndex() + 1);
					}
					stateChoice.paintImmediately(0, 0, stateChoice.getWidth(), stateChoice.getHeight());
					//itemStateChanged(new ItemEvent(stateChoice,701,"",1));
				}

			}
		}



		if(ke.getKeyCode() == KeyEvent.VK_ADD)
		{
			if(controlPanel.paletteCanvas.colorSelected < Project.getSelectedPalette().numColors-1)
			{
				controlPanel.paletteCanvas.selectColor(controlPanel.paletteCanvas.colorSelected + 1);
			}
		}



		if(ke.getKeyCode() == KeyEvent.VK_SUBTRACT)
		{
			if(controlPanel.paletteCanvas.colorSelected > 0)
			{
				controlPanel.paletteCanvas.selectColor(controlPanel.paletteCanvas.colorSelected - 1);
			}
		}




	}

	//===============================================================================================
	public void keyReleased(KeyEvent ke)
	{//===============================================================================================

		if(ke.getKeyCode() == KeyEvent.VK_A)
		{
			if(MapCanvas.selectedAllLayers == true)
			{
				MapCanvas.selectedAllLayers = false;
				controlPanel.allLayersLabel.setForeground(Color.GRAY);
				mapCanvas.repaint();
			}
		}

		if(ke.getKeyCode() == KeyEvent.VK_L)
		{
			if(MapCanvas.lockPressed == true)
			{
				MapCanvas.lockPressed = false;
			}
		}

		if(ke.getKeyCode() == KeyEvent.VK_S)
		{
			if(mapCanvas.mapSelectionArea.isShowing)mapCanvas.combineSelectedTilesOnActiveLayersIntoFlippedShadowTilesOnSelectedShadowLayer();
		}

		if(ke.getKeyCode() == KeyEvent.VK_K)
		{
			mapCanvas.mapSelectionArea.copySelectionCoordsToClipboard();
		}

		if(ke.getKeyCode() == KeyEvent.VK_M)
		{
			if(mapCanvas.mapSelectionArea.isShowing)mapCanvas.combineSelectedTilesOnActiveLayersIntoNewTilesOnTheLowestLayer();
		}

		if(ke.getKeyCode() == KeyEvent.VK_N)
		{
			if(mapCanvas.mapSelectionArea.isShowing)mapCanvas.outputEnabledLayersToTexturedMesh(getFileDialogDirectoryPath());
		}

		if(ke.getKeyCode() == KeyEvent.VK_CLOSE_BRACKET)
		{
			if(mapCanvas.mapSelectionArea.isShowing)mapCanvas.shiftSelectedTilesUpALayer();
		}

		if(ke.getKeyCode() == KeyEvent.VK_OPEN_BRACKET)
		{
			if(mapCanvas.mapSelectionArea.isShowing)mapCanvas.shiftSelectedTilesDownALayer();
		}

	}

	//===============================================================================================
	public void keyTyped(KeyEvent ke)
	{//===============================================================================================
	}


	//===============================================================================================
	public void mouseWheelMoved(MouseWheelEvent mwe)
	{//===============================================================================================

		if(mwe.getWheelRotation() > 0)
		{
			mapCanvas.zoomIn();
		}

		if(mwe.getWheelRotation() < 0)
		{
			mapCanvas.zoomOut();
		}

	}


	//===============================================================================================
	public void exit()
	{//===============================================================================================

		if(soundWasInitialized==true)AudioUtils.destroy();
		System.out.println("Closing...");
		System.exit(0);

	}


	//===============================================================================================
	public void windowClosing(WindowEvent we)
	{//===============================================================================================

		if(soundWasInitialized==true)AudioUtils.destroy();
		String dirpath = getFileDialogDirectoryPath();
		if(dirpath==null)dirpath = EditorMain.exportDirectory;
		project.save(dirpath + "exitautosave.h", "exitautosave.h");
		System.out.println("Saved to exitautosave.h. Closing.");//bob 9-29-05
		System.exit(0);

	}


	//===============================================================================================
	public void windowOpened(WindowEvent we)
	{//===============================================================================================


	}


	//===============================================================================================
	public void windowClosed(WindowEvent we)
	{//===============================================================================================


	}


	//===============================================================================================
	public void windowIconified(WindowEvent we)
	{//===============================================================================================

	}


	//===============================================================================================
	public void windowDeiconified(WindowEvent we)
	{//===============================================================================================

	}


	//===============================================================================================
	public void windowActivated(WindowEvent we)
	{//===============================================================================================

	}


	//===============================================================================================
	public void windowDeactivated(WindowEvent we)
	{//===============================================================================================

	}

	//===============================================================================================
	public static String getFileDialogDirectoryPath()
	{//===============================================================================================

		String directory = fileChooser.getCurrentDirectory().getPath()+"\\";

		return directory;

	}
	//===============================================================================================
	public static String getFileDialogFileName()
	{//===============================================================================================
		String filename = fileChooser.getSelectedFile().getName();


		return filename;

	}
	//===============================================================================================
	public static String getDesktopTempDirPath()
	{//===============================================================================================
		String dirpath = EditorMain.exportDirectory;
		Utils.makeDir(dirpath);
		return dirpath;

	}

}

class JMenuSpacer extends JMenuItem {
	public JMenuSpacer(String s) {
		super.setText(s);
		super.setEnabled(false);
		super.setArmed(false);
	}
}
