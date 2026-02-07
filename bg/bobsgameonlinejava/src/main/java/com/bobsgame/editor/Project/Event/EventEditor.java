package com.bobsgame.editor.Project.Event;

import java.awt.BorderLayout;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GridLayout;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.ConstructorProperties;
import java.util.ArrayList;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultCellEditor;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.DropMode;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.ListSelectionModel;
import javax.swing.TransferHandler;
import javax.swing.UIManager;

import javax.swing.border.BevelBorder;
import javax.swing.border.Border;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.DefaultHighlighter;
import javax.swing.text.Highlighter;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellEditor;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeCellEditor;
import javax.swing.tree.TreePath;


import com.bobsgame.EditorMain;
import com.bobsgame.editor.Dialogs.StringDialog;
import com.bobsgame.editor.MapCanvas.MapCanvas;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.GameMapObject;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.editor.Project.Map.MapState;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.EventData.EventScriptCommand;


//===============================================================================================
public class EventEditor extends JPanel implements ActionListener, ListSelectionListener, TreeModelListener, CaretListener, TreeSelectionListener
{//===============================================================================================







	/**
	 *
	 */
	private static final long serialVersionUID = 1L;





	public Event currentEvent = null;





//	JButton allDoorsButton;
//	JButton allWarpsButton;
//	JButton gameStringsButton;
//	JButton dialoguesButton;
//	JButton eventsButton;
//	JButton flagsButton;
//	JButton skillsButton;
//	JButton gamesButton;
//	JButton itemsButton;
//	JButton mapAreasButton;
//	JButton mapDoorsButton;
//	JButton mapEntitiesButton;
//	JButton mapLightsButton;
//	JButton mapsButton;
//	JButton musicButton;
//	JButton npcsButton;
//	JButton soundsButton;
//	JButton spritesButton;
//	JButton mapStatesButton;


	JButton customValueButton;

	GameObject selectedObject = null;

	JLabel allDoorsLabel;
	JLabel allWarpsLabel;
	JLabel gameStringsLabel;
	JLabel dialoguesLabel;
	JLabel eventsLabel;
	JLabel flagsLabel;
	JLabel skillsLabel;
	JLabel gamesLabel;
	JLabel itemsLabel;
	JLabel mapAreasLabel;
	JLabel allAreasLabel;
	JLabel mapDoorsLabel;
	JLabel mapEntitiesLabel;
	JLabel mapLightsLabel;
	JLabel mapsLabel;
	JLabel musicLabel;
	JLabel npcsLabel;
	JLabel soundsLabel;
	JLabel spritesLabel;
	JLabel mapStatesLabel;


	JList<Door> allDoorsList;
	JList<Area> allWarpsList;
	JList<GameString> gameStringsList;
	JList<Dialogue> dialoguesList;
	JList<Event> eventsList;
	JList<Flag> flagsList;
	JList<Skill> skillsList;
	JList<Sprite> gamesList;
	JList<Sprite> itemsList;
	JList<Area> mapAreasList;
	JList<Area> allAreasList;
	JList<Door> mapDoorsList;
	JList<Entity> mapEntitiesList;
	JList<Light> mapLightsList;
	JList<Map> mapsList;
	JList<Music> musicList;
	JList<Sprite> npcsList;
	JList<Sound> soundsList;
	JList<Sprite> spritesList;
	JList<MapState> mapStatesList;


	DefaultListModel<Entity> mapEntitiesListModel;
	DefaultListModel<Area> mapAreasListModel;
	DefaultListModel<Area> allAreasListModel;
	DefaultListModel<Door> mapDoorsListModel;
	DefaultListModel<Door> allDoorsListModel;
	DefaultListModel<Light> mapLightsListModel;
	DefaultListModel<Area> allWarpsListModel;
	DefaultListModel<Sprite> spritesListModel;
	DefaultListModel<Sprite> npcsListModel;
	DefaultListModel<Map> mapsListModel;
	DefaultListModel<Sprite> itemsListModel;
	DefaultListModel<Sprite> gamesListModel;
	DefaultListModel<Music> musicListModel;
	DefaultListModel<Sound> soundsListModel;
	DefaultListModel<Flag> flagsListModel;
	DefaultListModel<Skill> skillsListModel;
	DefaultListModel<Dialogue> dialoguesListModel;
	DefaultListModel<MapState> mapStatesListModel;
	DefaultListModel<GameString> gameStringsListModel;
	DefaultListModel<Event> eventsListModel;


	JTextField allDoorsFilterTextField;
	JTextField allWarpsFilterTextField;
	JTextField gameStringsFilterTextField;
	JTextField dialoguesFilterTextField;
	JTextField eventsFilterTextField;
	JTextField flagsFilterTextField;
	JTextField skillsFilterTextField;
	JTextField gamesFilterTextField;
	JTextField itemsFilterTextField;
	JTextField mapAreasFilterTextField;
	JTextField allAreasFilterTextField;
	JTextField mapDoorsFilterTextField;
	JTextField mapEntitiesFilterTextField;
	JTextField mapLightsFilterTextField;
	JTextField mapsFilterTextField;
	JTextField musicFilterTextField;
	JTextField npcsFilterTextField;
	JTextField soundsFilterTextField;
	JTextField spritesFilterTextField;
	JTextField mapStatesFilterTextField;


	String allDoorsFilterLastString = "";
	String allWarpsFilterLastString = "";
	String gameStringsFilterLastString = "";
	String dialoguesFilterLastString = "";
	String eventsFilterLastString = "";
	String flagsFilterLastString = "";
	String skillsFilterLastString = "";
	String gamesFilterLastString = "";
	String itemsFilterLastString = "";
	String mapAreasFilterLastString = "";
	String allAreasFilterLastString = "";
	String mapDoorsFilterLastString = "";
	String mapEntitiesFilterLastString = "";
	String mapLightsFilterLastString = "";
	String mapsFilterLastString = "";
	String musicFilterLastString = "";
	String npcsFilterLastString = "";
	String soundsFilterLastString = "";
	String spritesFilterLastString = "";
	String mapStatesFilterLastString = "";



	JPanel mapEntitiesPanel;
	JPanel mapAreasPanel;
	JPanel allAreasPanel;
	JPanel mapDoorsPanel;
	JPanel allDoorsPanel;
	JPanel mapLightsPanel;
	JPanel allWarpsPanel;
	JPanel spritesPanel;
	JPanel npcsPanel;
	JPanel mapsPanel;
	JPanel itemsPanel;
	JPanel gamesPanel;
	JPanel musicPanel;
	JPanel soundsPanel;
	JPanel flagsPanel;
	JPanel skillsPanel;
	JPanel dialoguesPanel;
	JPanel mapStatesPanel;
	JPanel gameStringsPanel;
	JPanel eventsPanel;



	JTabbedPane objectTabsPane;

	JPanel entitiesTab;
	JPanel areasTab;
	JPanel doorsTab;
	JPanel lightsTab;
	JPanel warpsTab;
	JPanel spritesTab;
	JPanel mapsTab;
	JPanel itemsGamesTab;
	JPanel soundsMusicTab;
	JPanel flagsTab;
	JPanel skillsTab;
	JPanel dialoguesTab;
	JPanel mapStatesTab;
	JPanel gameStringsTab;
	JPanel eventsTab;
	JPanel customValueTab;




	JTextField customValueTextField;


	JPanel spritePreviewPanel;
	JPanel thisPlayerButtonPanel;


	JScrollPane dialoguesListScroller;
	JButton createNewDialogueButton;
	JButton editSelectedDialogueButton;
	JTextArea dialoguePreviewTextArea;
	DialogueEditor dialogueEditor;


	JButton newFlagButton;
	JButton newSkillButton;
	JButton addTHISButton;
	JButton addPLAYERButton;

	JButton addSelectedObjectButton;




	//--------------------
	//tree
	//--------------------

	JTree tree;


	DefaultMutableTreeNode rootNode;
	DefaultTreeModel treeModel;


	JScrollPane treeView;
	JPanel treePanel;

	JButton treeDuplicateButton;
	JButton treeMoveUpButton;
	JButton treeMoveDownButton;
	JButton treeDeleteButton;

	JButton addInstructionButton;
	JTextField editInstructionTextField;
	Highlighter hilit;
	Highlighter.HighlightPainter painter;
	JLabel errorLabel;



	JList<EventScriptCommand> qualifierList;
	JList<EventScriptCommand> commandList;

	DefaultListModel<EventScriptCommand> commandListModel;
	DefaultListModel<EventScriptCommand> qualifierListModel;

	JButton addQualifierButton;
	JButton addCommandButton;

	boolean lastSelectedFromQualifierList = false;
	boolean lastSelectedFromCommandList = false;


	JPanel listsPanel;
	JTextField qualifierListFilterTextField;
	JTextField commandListFilterTextField;

	String qualifierListFilterLastString = "";
	String commandListFilterLastString = "";


	Font listFont;


	JPanel topPanel;

	public ArrayList<EventParameter> parameterList = new ArrayList<EventParameter>();


	Frame f = null;

	Map currentMap = null;



//	//===============================================================================================
//	public EventEditor()
//	{//===============================================================================================
//		this(null);
//	}



	//===============================================================================================
	public EventEditor(Frame f)
	{//===============================================================================================

		this.f = f;

		listFont = new Font("Lucida Console", Font.PLAIN, 12);

		dialogueEditor = new DialogueEditor(f);


		setLayout(new BorderLayout());


		//------------------------------
		//set up tree
		//------------------------------




		treePanel = new JPanel(new BorderLayout());


		initializeTree("");


		JPanel treeButtonsPanel = new JPanel();

		treeDuplicateButton = new JButton("Duplicate");
		treeDuplicateButton.addActionListener(this);
		treeMoveUpButton = new JButton("Move Up");
		treeMoveUpButton.addActionListener(this);
		treeMoveDownButton = new JButton("Move Down");
		treeMoveDownButton.addActionListener(this);
		treeDeleteButton = new JButton("Delete");
		treeDeleteButton.addActionListener(this);

		treeButtonsPanel.add(treeDuplicateButton);
		treeButtonsPanel.add(treeMoveUpButton);
		treeButtonsPanel.add(treeMoveDownButton);
		treeButtonsPanel.add(treeDeleteButton);

		treePanel.add(treeView, BorderLayout.CENTER);
		treePanel.add(treeButtonsPanel, BorderLayout.SOUTH);
		add(treePanel,BorderLayout.CENTER);



		qualifierListModel = new DefaultListModel<EventScriptCommand>();
		qualifierList = new JList<EventScriptCommand>(qualifierListModel);
		qualifierList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		qualifierList.setLayoutOrientation(JList.VERTICAL);
		qualifierList.setVisibleRowCount(100);
		qualifierList.setForeground(Color.BLACK);
		qualifierList.setFont(listFont);
		qualifierList.setFixedCellHeight(16);
		qualifierList.addListSelectionListener(this);
		JScrollPane qualifierListScroller = new JScrollPane(qualifierList,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);




		qualifierListScroller.setMinimumSize(new Dimension(300, 200));
		qualifierListScroller.setMaximumSize(new Dimension(300, 400));
		qualifierListScroller.setPreferredSize(new Dimension(300, 400));
		qualifierListScroller.setSize(new Dimension(300, 400));


		commandListModel = new DefaultListModel<EventScriptCommand>();
		commandList = new JList<EventScriptCommand>(commandListModel);
		commandList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		commandList.setLayoutOrientation(JList.VERTICAL);
		commandList.setVisibleRowCount(100);
		commandList.setForeground(Color.BLACK);
		commandList.setFont(listFont);
		commandList.setFixedCellHeight(16);
		commandList.addListSelectionListener(this);
		JScrollPane commandListScroller = new JScrollPane(commandList,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);


		commandListScroller.setMinimumSize(new Dimension(300, 200));
		commandListScroller.setMaximumSize(new Dimension(300, 400));
		commandListScroller.setPreferredSize(new Dimension(300, 400));
		commandListScroller.setSize(new Dimension(300, 400));


		//Font fonts = GraphicsEnvironment.getLocalGraphicsEnvironment().getAllFonts();

		//for(int i=0;i<fonts.length;i++)
			//System.out.println(fontsi.getFontName());






		objectTabsPane = new JTabbedPane();

		initializeTabs();


		JPanel qualifierListFilterPanel = new JPanel();
		qualifierListFilterTextField = new JTextField("",20);
		qualifierListFilterTextField.addCaretListener(this);

		qualifierListFilterPanel.add(new JLabel("Filter:"));
		qualifierListFilterPanel.add(qualifierListFilterTextField);


		JPanel commandListFilterPanel = new JPanel();
		commandListFilterTextField = new JTextField("",20);
		commandListFilterTextField.addCaretListener(this);

		commandListFilterPanel.add(new JLabel("Filter:"));
		commandListFilterPanel.add(commandListFilterTextField);


		JPanel qualifierListPanel = new JPanel(new BorderLayout());
		qualifierListPanel.add(qualifierListFilterPanel,BorderLayout.NORTH);
		qualifierListPanel.add(qualifierListScroller,BorderLayout.CENTER);

		JPanel commandListPanel = new JPanel(new BorderLayout());
		commandListPanel.add(commandListFilterPanel,BorderLayout.NORTH);
		commandListPanel.add(commandListScroller,BorderLayout.CENTER);


		listsPanel = new JPanel();
		listsPanel.setLayout(new BorderLayout());


		listsPanel.add(qualifierListPanel,  BorderLayout.WEST);
		listsPanel.add(commandListPanel,  BorderLayout.CENTER);
		listsPanel.add(objectTabsPane,  BorderLayout.EAST);

		add(listsPanel,BorderLayout.EAST);



		fillQualifierList();
		fillCommandList();






		topPanel = new JPanel(new BorderLayout());


		JPanel editPanel = new JPanel();
		editInstructionTextField = new JTextField(60);
		editInstructionTextField.setFont(new Font("Lucida Console", Font.BOLD, 16));
		editInstructionTextField.setEditable(false);
		editInstructionTextField.setHorizontalAlignment(JTextField.RIGHT);


		hilit = new DefaultHighlighter();
		painter = new DefaultHighlighter.DefaultHighlightPainter(Color.RED);
		editInstructionTextField.setHighlighter(hilit);






		addInstructionButton = new JButton("Add Instruction To Tree");
		addInstructionButton.addActionListener(this);
		addInstructionButton.setFont(new Font("Tahoma", Font.BOLD, 14));
		addInstructionButton.setVisible(false);

		errorLabel = new JLabel("", JLabel.RIGHT);
		errorLabel.setForeground(Color.MAGENTA);
		errorLabel.setFont(new Font("Tahoma", Font.BOLD, 16));


		editPanel.add(addInstructionButton);
		editPanel.add(editInstructionTextField);


		addSelectedObjectButton = new JButton("Add Selected Object");
		addSelectedObjectButton.addActionListener(this);
		addSelectedObjectButton.setFont(new Font("Tahoma", Font.BOLD, 14));
		editPanel.add(addSelectedObjectButton);



		topPanel.add(editPanel, BorderLayout.EAST);
		topPanel.add(errorLabel, BorderLayout.CENTER);


		add(topPanel,BorderLayout.NORTH);


		fillAllLists();


		setMinimumSize(new Dimension(800,100));
		setMaximumSize(new Dimension(1800,1000));
		setPreferredSize(new Dimension(1400,400));
		setSize(new Dimension(1400,400));



	}



	//===============================================================================================
	private void initializeTabs()
	{//===============================================================================================

		Font labelFont = new Font("Tahoma", Font.BOLD, 14);
		Font filterTextFont = new Font("Tahoma", Font.PLAIN, 9);
		Font filterLabelFont = new Font("Tahoma", Font.PLAIN, 9);
		Color tabBackgroundColor = Color.black;
		int filterTextSize = 20;

		//----------------------------------------------------------------------

		mapEntitiesLabel = new JLabel("MapEntities");
		mapEntitiesLabel.setFont(labelFont);
		mapEntitiesFilterTextField = new JTextField(filterTextSize);
		mapEntitiesFilterTextField.setFont(filterTextFont);
		mapEntitiesFilterTextField.addCaretListener(this);

		mapEntitiesListModel = new DefaultListModel<Entity>();
		mapEntitiesList = new JList<Entity>(mapEntitiesListModel); //data has type Object
		mapEntitiesList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapEntitiesList.setLayoutOrientation(JList.VERTICAL);
		mapEntitiesList.setVisibleRowCount(100);
		mapEntitiesList.setForeground(Color.BLACK);
		mapEntitiesList.setFont(listFont);
		mapEntitiesList.setFixedCellHeight(16);
		mapEntitiesList.addListSelectionListener(this);
		mapEntitiesList.setCellRenderer(new NameCellRenderer());
		JScrollPane mapEntitiesListScroller = new JScrollPane(mapEntitiesList);


		//mapEntitiesButton = new JButton("Add MapEntity");
		//mapEntitiesButton.addActionListener(this);

		mapEntitiesPanel = new JPanel();
		mapEntitiesPanel.setLayout(new BoxLayout(mapEntitiesPanel, BoxLayout.Y_AXIS));
		mapEntitiesPanel.setBackground(Color.WHITE);
		mapEntitiesPanel.add(mapEntitiesLabel);
		mapEntitiesPanel.add(mapEntitiesListScroller);


		JPanel mapEntitiesButtonPanel = new JPanel();
		JLabel mapEntitiesFilterLabel = new JLabel("Filter:");

		//mapEntitiesButtonPanel.add(mapEntitiesButton);
		mapEntitiesButtonPanel.add(mapEntitiesFilterLabel);
		mapEntitiesButtonPanel.add(mapEntitiesFilterTextField);

		mapEntitiesPanel.add(mapEntitiesButtonPanel);

		//----------------------------------------------------------------------


		entitiesTab = new JPanel(new BorderLayout());
		entitiesTab.setBackground(tabBackgroundColor);




		addTHISButton = new JButton("this.entity");
		addTHISButton.addActionListener(this);
		addTHISButton.setFont(new Font("Tahoma", Font.BOLD, 11));
		addTHISButton.setForeground(Color.BLUE);

		addPLAYERButton = new JButton("Player()");
		addPLAYERButton.addActionListener(this);
		addPLAYERButton.setFont(new Font("Tahoma", Font.BOLD, 11));
		addPLAYERButton.setForeground(new Color(160,0,150));

		thisPlayerButtonPanel = new JPanel(new GridLayout(1,0,4,0));
		thisPlayerButtonPanel.add(addPLAYERButton);
		thisPlayerButtonPanel.add(addTHISButton);




		entitiesTab.add(thisPlayerButtonPanel,BorderLayout.NORTH);
		entitiesTab.add(mapEntitiesPanel,BorderLayout.CENTER);

		objectTabsPane.addTab("Entities", null, entitiesTab);

		//----------------------------------------------------------------------


		mapAreasLabel = new JLabel("MapAreas");
		mapAreasLabel.setFont(labelFont);
		mapAreasFilterTextField = new JTextField(filterTextSize);
		mapAreasFilterTextField.setFont(filterTextFont);
		mapAreasFilterTextField.addCaretListener(this);



		mapAreasListModel = new DefaultListModel<Area>();
		mapAreasList = new JList<Area>(mapAreasListModel); //data has type Object
		mapAreasList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapAreasList.setLayoutOrientation(JList.VERTICAL);
		mapAreasList.setVisibleRowCount(100);
		mapAreasList.setForeground(Color.BLACK);
		mapAreasList.setFont(listFont);
		mapAreasList.setFixedCellHeight(16);
		mapAreasList.addListSelectionListener(this);
		mapAreasList.setCellRenderer(new NameCellRenderer());
		JScrollPane mapAreasListScroller = new JScrollPane(mapAreasList);


		//mapAreasButton = new JButton("Add MapArea");
		//mapAreasButton.addActionListener(this);

		mapAreasPanel = new JPanel();
		mapAreasPanel.setLayout(new BoxLayout(mapAreasPanel, BoxLayout.Y_AXIS));
		mapAreasPanel.setBackground(Color.WHITE);
		mapAreasPanel.add(mapAreasLabel);
		mapAreasPanel.add(mapAreasListScroller);


		JPanel mapAreasButtonPanel = new JPanel();
		JLabel mapAreasFilterLabel = new JLabel("Filter:");

		//mapAreasButtonPanel.add(mapAreasButton);
		mapAreasButtonPanel.add(mapAreasFilterLabel);
		mapAreasButtonPanel.add(mapAreasFilterTextField);

		mapAreasPanel.add(mapAreasButtonPanel);

		//----------------------------------------------------------------------


		allAreasLabel = new JLabel("All Areas");
		allAreasLabel.setFont(labelFont);
		allAreasFilterTextField = new JTextField(filterTextSize);
		allAreasFilterTextField.setFont(filterTextFont);
		allAreasFilterTextField.addCaretListener(this);


		allAreasListModel = new DefaultListModel<Area>();
		allAreasList = new JList<Area>(allAreasListModel); //data has type Object
		allAreasList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		allAreasList.setLayoutOrientation(JList.VERTICAL);
		allAreasList.setVisibleRowCount(100);
		allAreasList.setForeground(Color.BLACK);
		allAreasList.setFont(listFont);
		allAreasList.setFixedCellHeight(16);
		allAreasList.addListSelectionListener(this);
		allAreasList.setCellRenderer(new LongTypeNameCellRenderer());
		JScrollPane allAreasListScroller = new JScrollPane(allAreasList);

		//allAreasButton = new JButton("Add Area");
		//allAreasButton.addActionListener(this);

		allAreasPanel = new JPanel();
		allAreasPanel.setLayout(new BoxLayout(allAreasPanel, BoxLayout.Y_AXIS));
		allAreasPanel.setBackground(Color.WHITE);
		allAreasPanel.add(allAreasLabel);
		allAreasPanel.add(allAreasListScroller);


		JPanel allAreasButtonPanel = new JPanel();
		JLabel allAreasFilterLabel = new JLabel("Filter:");

		//allAreasButtonPanel.add(allAreasButton);
		allAreasButtonPanel.add(allAreasFilterLabel);
		allAreasButtonPanel.add(allAreasFilterTextField);

		allAreasPanel.add(allAreasButtonPanel);


		//----------------------------------------------------------------------

		areasTab = new JPanel(new GridLayout(0,1,0,4));
		areasTab.setBackground(tabBackgroundColor);

		areasTab.add(mapAreasPanel);
		areasTab.add(allAreasPanel);

		objectTabsPane.addTab("Areas", null, areasTab);

		//----------------------------------------------------------------------


		mapDoorsLabel = new JLabel("MapDoors");
		mapDoorsLabel.setFont(labelFont);
		mapDoorsFilterTextField = new JTextField(filterTextSize);
		mapDoorsFilterTextField.setFont(filterTextFont);
		mapDoorsFilterTextField.addCaretListener(this);



		mapDoorsListModel = new DefaultListModel<Door>();
		mapDoorsList = new JList<Door>(mapDoorsListModel); //data has type Object
		mapDoorsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapDoorsList.setLayoutOrientation(JList.VERTICAL);
		mapDoorsList.setVisibleRowCount(100);
		mapDoorsList.setForeground(Color.BLACK);
		mapDoorsList.setFont(listFont);
		mapDoorsList.setFixedCellHeight(16);
		mapDoorsList.addListSelectionListener(this);
		mapDoorsList.setCellRenderer(new NameCellRenderer());
		JScrollPane mapDoorsListScroller = new JScrollPane(mapDoorsList);

		//mapDoorsButton = new JButton("Add MapDoor");
	//	mapDoorsButton.addActionListener(this);

		mapDoorsPanel = new JPanel();
		mapDoorsPanel.setLayout(new BoxLayout(mapDoorsPanel, BoxLayout.Y_AXIS));
		mapDoorsPanel.setBackground(Color.WHITE);
		mapDoorsPanel.add(mapDoorsLabel);
		mapDoorsPanel.add(mapDoorsListScroller);


		JPanel mapDoorsButtonPanel = new JPanel();
		JLabel mapDoorsFilterLabel = new JLabel("Filter:");

		//mapDoorsButtonPanel.add(mapDoorsButton);
		mapDoorsButtonPanel.add(mapDoorsFilterLabel);
		mapDoorsButtonPanel.add(mapDoorsFilterTextField);

		mapDoorsPanel.add(mapDoorsButtonPanel);


		//----------------------------------------------------------------------


		allDoorsLabel = new JLabel("All Doors");
		allDoorsLabel.setFont(labelFont);
		allDoorsFilterTextField = new JTextField(filterTextSize);
		allDoorsFilterTextField.setFont(filterTextFont);
		allDoorsFilterTextField.addCaretListener(this);


		allDoorsListModel = new DefaultListModel<Door>();
		allDoorsList = new JList<Door>(allDoorsListModel); //data has type Object
		allDoorsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		allDoorsList.setLayoutOrientation(JList.VERTICAL);
		allDoorsList.setVisibleRowCount(100);
		allDoorsList.setForeground(Color.BLACK);
		allDoorsList.setFont(listFont);
		allDoorsList.setFixedCellHeight(16);
		allDoorsList.addListSelectionListener(this);
		allDoorsList.setCellRenderer(new DestinationNameCellRenderer());
		JScrollPane allDoorsListScroller = new JScrollPane(allDoorsList);

		//allDoorsButton = new JButton("Add Door");
		//allDoorsButton.addActionListener(this);

		allDoorsPanel = new JPanel();
		allDoorsPanel.setLayout(new BoxLayout(allDoorsPanel, BoxLayout.Y_AXIS));
		allDoorsPanel.setBackground(Color.WHITE);
		allDoorsPanel.add(allDoorsLabel);
		allDoorsPanel.add(allDoorsListScroller);


		JPanel allDoorsButtonPanel = new JPanel();
		JLabel allDoorsFilterLabel = new JLabel("Filter:");

		//allDoorsButtonPanel.add(allDoorsButton);
		allDoorsButtonPanel.add(allDoorsFilterLabel);
		allDoorsButtonPanel.add(allDoorsFilterTextField);

		allDoorsPanel.add(allDoorsButtonPanel);

		//----------------------------------------------------------------------

		doorsTab = new JPanel(new GridLayout(0,1,0,4));
		doorsTab.setBackground(tabBackgroundColor);

		doorsTab.add(mapDoorsPanel);
		doorsTab.add(allDoorsPanel);

		objectTabsPane.addTab("Doors", null, doorsTab);

		//----------------------------------------------------------------------



		mapLightsLabel = new JLabel("MapLights");
		mapLightsLabel.setFont(labelFont);
		mapLightsFilterTextField = new JTextField(filterTextSize);
		mapLightsFilterTextField.setFont(filterTextFont);
		mapLightsFilterTextField.addCaretListener(this);


		mapLightsListModel = new DefaultListModel<Light>();
		mapLightsList = new JList<Light>(mapLightsListModel); //data has type Object
		mapLightsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapLightsList.setLayoutOrientation(JList.VERTICAL);
		mapLightsList.setVisibleRowCount(100);
		mapLightsList.setForeground(Color.BLACK);
		mapLightsList.setFont(listFont);
		mapLightsList.setFixedCellHeight(16);
		mapLightsList.addListSelectionListener(this);
		mapLightsList.setCellRenderer(new NameCellRenderer());
		JScrollPane mapLightsListScroller = new JScrollPane(mapLightsList);

		//mapLightsButton = new JButton("Add MapLight");
		//mapLightsButton.addActionListener(this);

		mapLightsPanel = new JPanel();
		mapLightsPanel.setLayout(new BoxLayout(mapLightsPanel, BoxLayout.Y_AXIS));
		mapLightsPanel.setBackground(Color.WHITE);
		mapLightsPanel.add(mapLightsLabel);
		mapLightsPanel.add(mapLightsListScroller);


		JPanel mapLightsButtonPanel = new JPanel();
		JLabel mapLightsFilterLabel = new JLabel("Filter:");

		//mapLightsButtonPanel.add(mapLightsButton);
		mapLightsButtonPanel.add(mapLightsFilterLabel);
		mapLightsButtonPanel.add(mapLightsFilterTextField);

		mapLightsPanel.add(mapLightsButtonPanel);

		//----------------------------------------------------------------------



		lightsTab = new JPanel(new GridLayout(0,1,0,4));
		lightsTab.setBackground(tabBackgroundColor);
		lightsTab.add(mapLightsPanel);

		objectTabsPane.addTab("Lights", null, lightsTab);

		//----------------------------------------------------------------------


		allWarpsLabel = new JLabel("All Warps");
		allWarpsLabel.setFont(labelFont);
		allWarpsFilterTextField = new JTextField(filterTextSize);
		allWarpsFilterTextField.setFont(filterTextFont);
		allWarpsFilterTextField.addCaretListener(this);


		allWarpsListModel = new DefaultListModel<Area>();
		allWarpsList = new JList<Area>(allWarpsListModel); //data has type Object
		allWarpsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		allWarpsList.setLayoutOrientation(JList.VERTICAL);
		allWarpsList.setVisibleRowCount(100);
		allWarpsList.setForeground(Color.BLACK);
		allWarpsList.setFont(listFont);
		allWarpsList.setFixedCellHeight(16);
		allWarpsList.addListSelectionListener(this);
		allWarpsList.setCellRenderer(new DestinationNameCellRenderer());
		JScrollPane allWarpsListScroller = new JScrollPane(allWarpsList);

		//allWarpsButton = new JButton("Add Warp");
		//allWarpsButton.addActionListener(this);

		allWarpsPanel = new JPanel();
		allWarpsPanel.setLayout(new BoxLayout(allWarpsPanel, BoxLayout.Y_AXIS));
		allWarpsPanel.setBackground(Color.WHITE);
		allWarpsPanel.add(allWarpsLabel);
		allWarpsPanel.add(allWarpsListScroller);


		JPanel allWarpsButtonPanel = new JPanel();
		JLabel allWarpsFilterLabel = new JLabel("Filter:");

		//allWarpsButtonPanel.add(allWarpsButton);
		allWarpsButtonPanel.add(allWarpsFilterLabel);
		allWarpsButtonPanel.add(allWarpsFilterTextField);

		allWarpsPanel.add(allWarpsButtonPanel);

		//----------------------------------------------------------------------

		warpsTab = new JPanel(new GridLayout(0,1,0,4));
		warpsTab.setBackground(tabBackgroundColor);
		objectTabsPane.addTab("Warps", null, warpsTab);
		warpsTab.add(allWarpsPanel);

		//----------------------------------------------------------------------

		spritesLabel = new JLabel("Sprites");
		spritesLabel.setFont(labelFont);
		spritesFilterTextField = new JTextField(filterTextSize);
		spritesFilterTextField.setFont(filterTextFont);
		spritesFilterTextField.addCaretListener(this);



		spritesListModel = new DefaultListModel<Sprite>();
		spritesList = new JList<Sprite>(spritesListModel); //data has type Object
		spritesList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		spritesList.setLayoutOrientation(JList.VERTICAL);
		spritesList.setVisibleRowCount(100);
		spritesList.setForeground(Color.BLACK);
		spritesList.setFont(listFont);
		spritesList.setFixedCellHeight(16);
		spritesList.addListSelectionListener(this);
		spritesList.setCellRenderer(new NameCellRenderer());
		JScrollPane spritesListScroller = new JScrollPane(spritesList);

		//spritesButton = new JButton("Add Sprite");
		//spritesButton.addActionListener(this);

		spritesPanel = new JPanel();
		spritesPanel.setLayout(new BoxLayout(spritesPanel, BoxLayout.Y_AXIS));
		spritesPanel.setBackground(Color.WHITE);
		spritesPanel.add(spritesLabel);
		spritesPanel.add(spritesListScroller);


		JPanel spritesButtonPanel = new JPanel();
		JLabel spritesFilterLabel = new JLabel("Filter:");

		//spritesButtonPanel.add(spritesButton);
		spritesButtonPanel.add(spritesFilterLabel);
		spritesButtonPanel.add(spritesFilterTextField);

		spritesPanel.add(spritesButtonPanel);


		//----------------------------------------------------------------------


		npcsLabel = new JLabel("NPCs");
		npcsLabel.setFont(labelFont);
		npcsFilterTextField = new JTextField(filterTextSize);
		npcsFilterTextField.setFont(filterTextFont);
		npcsFilterTextField.addCaretListener(this);



		npcsListModel = new DefaultListModel<Sprite>();
		npcsList = new JList<Sprite>(npcsListModel); //data has type Object
		npcsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		npcsList.setLayoutOrientation(JList.VERTICAL);
		npcsList.setVisibleRowCount(100);
		npcsList.setForeground(Color.BLACK);
		npcsList.setFont(listFont);
		npcsList.setFixedCellHeight(16);
		npcsList.addListSelectionListener(this);
		npcsList.setCellRenderer(new NameCellRenderer());
		JScrollPane npcsListScroller = new JScrollPane(npcsList);


		//npcsButton = new JButton("Add NPC");
		//npcsButton.addActionListener(this);

		npcsPanel = new JPanel();
		npcsPanel.setLayout(new BoxLayout(npcsPanel, BoxLayout.Y_AXIS));
		npcsPanel.setBackground(Color.WHITE);
		npcsPanel.add(npcsLabel);
		//npcsPanel.add(npcsComboBox);
		npcsPanel.add(npcsListScroller);


		JPanel npcsButtonPanel = new JPanel();
		JLabel npcsFilterLabel = new JLabel("Filter:");

		//npcsButtonPanel.add(npcsButton);
		npcsButtonPanel.add(npcsFilterLabel);
		npcsButtonPanel.add(npcsFilterTextField);

		npcsPanel.add(npcsButtonPanel);


		//----------------------------------------------------------------------

		spritePreviewPanel = new JPanel();

		spritePreviewPanel.setMinimumSize(new Dimension(300,100));
		spritePreviewPanel.setMaximumSize(new Dimension(400,100));
		spritePreviewPanel.setPreferredSize(new Dimension(400,100));
		spritePreviewPanel.setSize(new Dimension(400,100));


		spritesTab = new JPanel(new BorderLayout());
		objectTabsPane.addTab("Sprites", null, spritesTab);
		spritesTab.add(spritePreviewPanel, BorderLayout.NORTH);

		JPanel spritesListsPanel = new JPanel(new GridLayout(0,1,0,4));

		spritesListsPanel.add(spritesPanel);
		spritesListsPanel.add(npcsPanel);

		spritesTab.add(spritesListsPanel, BorderLayout.CENTER);

		//----------------------------------------------------------------------


		mapsLabel = new JLabel("Maps");
		mapsLabel.setFont(labelFont);
		mapsFilterTextField = new JTextField(filterTextSize);
		mapsFilterTextField.setFont(filterTextFont);
		mapsFilterTextField.addCaretListener(this);


		mapsListModel = new DefaultListModel<Map>();
		mapsList = new JList<Map>(mapsListModel); //data has type Object
		mapsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapsList.setLayoutOrientation(JList.VERTICAL);
		mapsList.setVisibleRowCount(100);
		mapsList.setForeground(Color.BLACK);
		mapsList.setFont(listFont);
		mapsList.setFixedCellHeight(16);
		mapsList.addListSelectionListener(this);
		mapsList.setCellRenderer(new NameCellRenderer());
		JScrollPane mapsListScroller = new JScrollPane(mapsList);

		//mapsButton = new JButton("Add Map");
		//mapsButton.addActionListener(this);

		mapsPanel = new JPanel();
		mapsPanel.setLayout(new BoxLayout(mapsPanel, BoxLayout.Y_AXIS));
		mapsPanel.setBackground(Color.WHITE);
		mapsPanel.add(mapsLabel);
		mapsPanel.add(mapsListScroller);


		JPanel mapsButtonPanel = new JPanel();
		JLabel mapsFilterLabel = new JLabel("Filter:");

		//mapsButtonPanel.add(mapsButton);
		mapsButtonPanel.add(mapsFilterLabel);
		mapsButtonPanel.add(mapsFilterTextField);

		mapsPanel.add(mapsButtonPanel);

		//----------------------------------------------------------------------

		mapsTab = new JPanel(new GridLayout(0,1,0,4));
		mapsTab.setBackground(tabBackgroundColor);
		objectTabsPane.addTab("Maps", null, mapsTab);
		mapsTab.add(mapsPanel);

		//----------------------------------------------------------------------


		itemsLabel = new JLabel("Items");
		itemsLabel.setFont(labelFont);
		itemsFilterTextField = new JTextField(filterTextSize);
		itemsFilterTextField.setFont(filterTextFont);
		itemsFilterTextField.addCaretListener(this);


		itemsListModel = new DefaultListModel<Sprite>();
		itemsList = new JList<Sprite>(itemsListModel); //data has type Object
		itemsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		itemsList.setLayoutOrientation(JList.VERTICAL);
		itemsList.setVisibleRowCount(100);
		itemsList.setForeground(Color.BLACK);
		itemsList.setFont(listFont);
		itemsList.setFixedCellHeight(16);
		itemsList.addListSelectionListener(this);
		itemsList.setCellRenderer(new NameCellRenderer());
		JScrollPane itemsListScroller = new JScrollPane(itemsList);

		//itemsButton = new JButton("Add Item");
		//itemsButton.addActionListener(this);

		itemsPanel = new JPanel();
		itemsPanel.setLayout(new BoxLayout(itemsPanel, BoxLayout.Y_AXIS));
		itemsPanel.setBackground(Color.WHITE);
		itemsPanel.add(itemsLabel);
		itemsPanel.add(itemsListScroller);


		JPanel itemsButtonPanel = new JPanel();
		JLabel itemsFilterLabel = new JLabel("Filter:");

		//itemsButtonPanel.add(itemsButton);
		itemsButtonPanel.add(itemsFilterLabel);
		itemsButtonPanel.add(itemsFilterTextField);

		itemsPanel.add(itemsButtonPanel);


		//----------------------------------------------------------------------


		gamesLabel = new JLabel("Games");
		gamesLabel.setFont(labelFont);
		gamesFilterTextField = new JTextField(filterTextSize);
		gamesFilterTextField.setFont(filterTextFont);
		gamesFilterTextField.addCaretListener(this);


		gamesListModel = new DefaultListModel<Sprite>();
		gamesList = new JList<Sprite>(gamesListModel); //data has type Object
		gamesList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		gamesList.setLayoutOrientation(JList.VERTICAL);
		gamesList.setVisibleRowCount(100);
		gamesList.setForeground(Color.BLACK);
		gamesList.setFont(listFont);
		gamesList.setFixedCellHeight(16);
		gamesList.addListSelectionListener(this);
		gamesList.setCellRenderer(new NameCellRenderer());
		JScrollPane gamesListScroller = new JScrollPane(gamesList);

		//gamesButton = new JButton("Add Game");
		//gamesButton.addActionListener(this);

		gamesPanel = new JPanel();
		gamesPanel.setLayout(new BoxLayout(gamesPanel, BoxLayout.Y_AXIS));
		gamesPanel.setBackground(Color.WHITE);
		gamesPanel.add(gamesLabel);
		gamesPanel.add(gamesListScroller);


		JPanel gamesButtonPanel = new JPanel();
		JLabel gamesFilterLabel = new JLabel("Filter:");

		//gamesButtonPanel.add(gamesButton);
		gamesButtonPanel.add(gamesFilterLabel);
		gamesButtonPanel.add(gamesFilterTextField);

		gamesPanel.add(gamesButtonPanel);

		//----------------------------------------------------------------------


		itemsGamesTab = new JPanel(new GridLayout(0,1,0,4));
		itemsGamesTab.setBackground(tabBackgroundColor);
		itemsGamesTab.add(itemsPanel);
		itemsGamesTab.add(gamesPanel);

		objectTabsPane.addTab("Items/Games", null, itemsGamesTab);

		//----------------------------------------------------------------------


		soundsLabel = new JLabel("Sounds");
		soundsLabel.setFont(labelFont);
		soundsFilterTextField = new JTextField(filterTextSize);
		soundsFilterTextField.setFont(filterTextFont);
		soundsFilterTextField.addCaretListener(this);


		soundsListModel = new DefaultListModel<Sound>();
		soundsList = new JList<Sound>(soundsListModel); //data has type Object
		soundsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		soundsList.setLayoutOrientation(JList.VERTICAL);
		soundsList.setVisibleRowCount(100);
		soundsList.setForeground(Color.BLACK);
		soundsList.setFont(listFont);
		soundsList.setFixedCellHeight(16);
		soundsList.addListSelectionListener(this);
		soundsList.setCellRenderer(new NameCellRenderer());
		JScrollPane soundsListScroller = new JScrollPane(soundsList);

		//soundsButton = new JButton("Add Sound");
		//soundsButton.addActionListener(this);

		soundsPanel = new JPanel();
		soundsPanel.setLayout(new BoxLayout(soundsPanel, BoxLayout.Y_AXIS));
		soundsPanel.setBackground(Color.WHITE);
		soundsPanel.add(soundsLabel);
		soundsPanel.add(soundsListScroller);


		JPanel soundsButtonPanel = new JPanel();
		JLabel soundsFilterLabel = new JLabel("Filter:");

		//soundsButtonPanel.add(soundsButton);
		soundsButtonPanel.add(soundsFilterLabel);
		soundsButtonPanel.add(soundsFilterTextField);

		soundsPanel.add(soundsButtonPanel);


		//----------------------------------------------------------------------


		musicLabel = new JLabel("Music");
		musicLabel.setFont(labelFont);
		musicFilterTextField = new JTextField(filterTextSize);
		musicFilterTextField.setFont(filterTextFont);
		musicFilterTextField.addCaretListener(this);


		musicListModel = new DefaultListModel<Music>();
		musicList = new JList<Music>(musicListModel); //data has type Object
		musicList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		musicList.setLayoutOrientation(JList.VERTICAL);
		musicList.setVisibleRowCount(100);
		musicList.setForeground(Color.BLACK);
		musicList.setFont(listFont);
		musicList.setFixedCellHeight(16);
		musicList.addListSelectionListener(this);
		musicList.setCellRenderer(new NameCellRenderer());
		JScrollPane musicListScroller = new JScrollPane(musicList);

		//musicButton = new JButton("Add Music");
		//musicButton.addActionListener(this);

		musicPanel = new JPanel();
		musicPanel.setLayout(new BoxLayout(musicPanel, BoxLayout.Y_AXIS));
		musicPanel.setBackground(Color.WHITE);
		musicPanel.add(musicLabel);
		musicPanel.add(musicListScroller);


		JPanel musicButtonPanel = new JPanel();
		JLabel musicFilterLabel = new JLabel("Filter:");

		//musicButtonPanel.add(musicButton);
		musicButtonPanel.add(musicFilterLabel);
		musicButtonPanel.add(musicFilterTextField);

		musicPanel.add(musicButtonPanel);

		//----------------------------------------------------------------------

		soundsMusicTab = new JPanel(new GridLayout(0,1,0,4));
		soundsMusicTab.setBackground(tabBackgroundColor);
		soundsMusicTab.add(soundsPanel);
		soundsMusicTab.add(musicPanel);

		objectTabsPane.addTab("Sounds/Music", null, soundsMusicTab);

		//----------------------------------------------------------------------


		flagsLabel = new JLabel("Flags");
		flagsLabel.setFont(labelFont);
		flagsFilterTextField = new JTextField(filterTextSize);
		flagsFilterTextField.setFont(filterTextFont);
		flagsFilterTextField.addCaretListener(this);


		flagsListModel = new DefaultListModel<Flag>();
		flagsList = new JList<Flag>(flagsListModel); //data has type Object
		flagsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		flagsList.setLayoutOrientation(JList.VERTICAL);
		flagsList.setVisibleRowCount(100);
		flagsList.setForeground(Color.BLACK);
		flagsList.setFont(listFont);
		flagsList.setFixedCellHeight(16);
		flagsList.addListSelectionListener(this);
		flagsList.setCellRenderer(new NameCellRenderer());
		JScrollPane flagsListScroller = new JScrollPane(flagsList);

		//flagsButton = new JButton("Add Flag");
		//flagsButton.addActionListener(this);

		flagsPanel = new JPanel();
		flagsPanel.setLayout(new BoxLayout(flagsPanel, BoxLayout.Y_AXIS));
		flagsPanel.setBackground(Color.WHITE);
		flagsPanel.add(flagsLabel);

		flagsPanel.add(flagsListScroller);


		JPanel flagsButtonPanel = new JPanel();
		JLabel flagsFilterLabel = new JLabel("Filter:");

		//flagsButtonPanel.add(flagsButton);
		flagsButtonPanel.add(flagsFilterLabel);
		flagsButtonPanel.add(flagsFilterTextField);

		flagsPanel.add(flagsButtonPanel);

		//----------------------------------------------------------------------



		JPanel newFlagButtonPanel = new JPanel();

		newFlagButton = new JButton("Create New Flag");
		newFlagButton.addActionListener(this);
		newFlagButton.setForeground(Color.BLACK);
		newFlagButton.setFont(new Font("Tahoma", Font.PLAIN, 9));

		newFlagButtonPanel.add(Box.createHorizontalGlue());
		newFlagButtonPanel.add(newFlagButton);
		newFlagButtonPanel.add(Box.createHorizontalGlue());

		flagsTab = new JPanel(new BorderLayout());
		flagsTab.setBackground(tabBackgroundColor);
		flagsTab.add(flagsPanel, BorderLayout.CENTER);
		flagsTab.add(newFlagButtonPanel, BorderLayout.SOUTH);


		objectTabsPane.addTab("Flags", null, flagsTab);

		//----------------------------------------------------------------------


		skillsLabel = new JLabel("Skills");
		skillsLabel.setFont(labelFont);
		skillsFilterTextField = new JTextField(filterTextSize);
		skillsFilterTextField.setFont(filterTextFont);
		skillsFilterTextField.addCaretListener(this);


		skillsListModel = new DefaultListModel<Skill>();
		skillsList = new JList<Skill>(skillsListModel); //data has type Object
		skillsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		skillsList.setLayoutOrientation(JList.VERTICAL);
		skillsList.setVisibleRowCount(100);
		skillsList.setForeground(Color.BLACK);
		skillsList.setFont(listFont);
		skillsList.setFixedCellHeight(16);
		skillsList.addListSelectionListener(this);
		skillsList.setCellRenderer(new NameCellRenderer());
		JScrollPane skillsListScroller = new JScrollPane(skillsList);

		//skillsButton = new JButton("Add Skill");
		//skillsButton.addActionListener(this);

		skillsPanel = new JPanel();
		skillsPanel.setLayout(new BoxLayout(skillsPanel, BoxLayout.Y_AXIS));
		skillsPanel.setBackground(Color.WHITE);
		skillsPanel.add(skillsLabel);

		skillsPanel.add(skillsListScroller);


		JPanel skillsButtonPanel = new JPanel();
		JLabel skillsFilterLabel = new JLabel("Filter:");

		//skillsButtonPanel.add(skillsButton);
		skillsButtonPanel.add(skillsFilterLabel);
		skillsButtonPanel.add(skillsFilterTextField);

		skillsPanel.add(skillsButtonPanel);

		//----------------------------------------------------------------------



		JPanel newSkillButtonPanel = new JPanel();

		newSkillButton = new JButton("Create New Skill");
		newSkillButton.addActionListener(this);
		newSkillButton.setForeground(Color.BLACK);
		newSkillButton.setFont(new Font("Tahoma", Font.PLAIN, 9));

		newSkillButtonPanel.add(Box.createHorizontalGlue());
		newSkillButtonPanel.add(newSkillButton);
		newSkillButtonPanel.add(Box.createHorizontalGlue());

		skillsTab = new JPanel(new BorderLayout());
		skillsTab.setBackground(tabBackgroundColor);
		skillsTab.add(skillsPanel, BorderLayout.CENTER);
		skillsTab.add(newSkillButtonPanel, BorderLayout.SOUTH);


		objectTabsPane.addTab("Skills", null, skillsTab);

		//----------------------------------------------------------------------

		dialoguesLabel = new JLabel("Dialogues");
		dialoguesLabel.setFont(labelFont);
		dialoguesFilterTextField = new JTextField(filterTextSize);
		dialoguesFilterTextField.setFont(filterTextFont);
		dialoguesFilterTextField.addCaretListener(this);


		dialoguesListModel = new DefaultListModel<Dialogue>();
		dialoguesList = new JList<Dialogue>(dialoguesListModel); //data has type Object
		dialoguesList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		dialoguesList.setLayoutOrientation(JList.VERTICAL);
		dialoguesList.setVisibleRowCount(100);
		dialoguesList.setForeground(Color.BLACK);
		dialoguesList.setFont(listFont);
		dialoguesList.setFixedCellHeight(16);
		dialoguesList.addListSelectionListener(this);
		dialoguesList.setCellRenderer(new DialogueCellRenderer());

		dialoguesListScroller = new JScrollPane(dialoguesList);

		//dialoguesButton = new JButton("Add Dialogue");
		//dialoguesButton.addActionListener(this);

		dialoguesPanel = new JPanel();
		dialoguesPanel.setLayout(new BoxLayout(dialoguesPanel, BoxLayout.Y_AXIS));
		dialoguesPanel.setBackground(Color.WHITE);
		dialoguesPanel.add(dialoguesLabel);
		dialoguesPanel.add(dialoguesListScroller);


		JPanel dialoguesButtonPanel = new JPanel();
		JLabel dialoguesFilterLabel = new JLabel("Filter:");

		//dialoguesButtonPanel.add(dialoguesButton);
		dialoguesButtonPanel.add(dialoguesFilterLabel);
		dialoguesButtonPanel.add(dialoguesFilterTextField);

		dialoguesPanel.add(dialoguesButtonPanel);

		//----------------------------------------------------------------------


		dialoguesTab = new JPanel(new GridLayout(0,1,0,4));
		dialoguesTab.setBackground(tabBackgroundColor);


		JPanel dialoguesPreviewPanel = new JPanel(new BorderLayout());
			JPanel dialoguePreviewButtonsPanel = new JPanel();
			JLabel dialoguePreviewLabel = new JLabel("Dialogue Preview");
			createNewDialogueButton = new JButton("Create New Dialogue");
			createNewDialogueButton.setForeground(Color.BLACK);
			createNewDialogueButton.setFont(new Font("Tahoma", Font.PLAIN, 9));
			createNewDialogueButton.addActionListener(this);
			editSelectedDialogueButton = new JButton("Edit Selected Dialogue");
			editSelectedDialogueButton.setForeground(Color.BLACK);
			editSelectedDialogueButton.setFont(new Font("Tahoma", Font.PLAIN, 9));
			editSelectedDialogueButton.addActionListener(this);
			dialoguePreviewButtonsPanel.add(createNewDialogueButton);
			dialoguePreviewButtonsPanel.add(editSelectedDialogueButton);
			dialoguePreviewButtonsPanel.add(dialoguePreviewLabel);
			dialoguePreviewTextArea = new JTextArea();
			dialoguePreviewTextArea.setLineWrap(true);
			dialoguePreviewTextArea.setWrapStyleWord(true);
			dialoguePreviewTextArea.setEditable(false);
			dialoguePreviewTextArea.setBackground(new Color(24,24,24));
			dialoguePreviewTextArea.setForeground(Color.LIGHT_GRAY);
			dialoguePreviewTextArea.setFont(new Font("Tahoma", Font.PLAIN, 11));
		dialoguesPreviewPanel.add(dialoguePreviewButtonsPanel, BorderLayout.NORTH);
		dialoguesPreviewPanel.add(dialoguePreviewTextArea, BorderLayout.CENTER);

		dialoguesTab.add(dialoguesPanel);
		dialoguesTab.add(dialoguesPreviewPanel);


		objectTabsPane.addTab("Dialogues", null, dialoguesTab);

		//----------------------------------------------------------------------

		mapStatesLabel = new JLabel("MapStates");
		mapStatesLabel.setFont(labelFont);
		mapStatesFilterTextField = new JTextField(filterTextSize);
		mapStatesFilterTextField.setFont(filterTextFont);
		mapStatesFilterTextField.addCaretListener(this);


		mapStatesListModel = new DefaultListModel<MapState>();
		mapStatesList = new JList<MapState>(mapStatesListModel); //data has type Object
		mapStatesList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		mapStatesList.setLayoutOrientation(JList.VERTICAL);
		mapStatesList.setVisibleRowCount(100);
		mapStatesList.setForeground(Color.BLACK);
		mapStatesList.setFont(listFont);
		mapStatesList.setFixedCellHeight(16);
		mapStatesList.addListSelectionListener(this);
		mapStatesList.setCellRenderer(new LongTypeNameCellRenderer());
		JScrollPane statesListScroller = new JScrollPane(mapStatesList);

		//mapStatesButton = new JButton("Add State");
		//mapStatesButton.addActionListener(this);

		mapStatesPanel = new JPanel();
		mapStatesPanel.setLayout(new BoxLayout(mapStatesPanel, BoxLayout.Y_AXIS));
		mapStatesPanel.setBackground(Color.WHITE);
		mapStatesPanel.add(mapStatesLabel);
		mapStatesPanel.add(statesListScroller);


		JPanel statesButtonPanel = new JPanel();
		JLabel statesFilterLabel = new JLabel("Filter:");

		//statesButtonPanel.add(mapStatesButton);
		statesButtonPanel.add(statesFilterLabel);
		statesButtonPanel.add(mapStatesFilterTextField);

		mapStatesPanel.add(statesButtonPanel);

		//----------------------------------------------------------------------

		mapStatesTab = new JPanel(new GridLayout(0,1,0,4));
		mapStatesTab.setBackground(tabBackgroundColor);
		mapStatesTab.add(mapStatesPanel);

		objectTabsPane.addTab("MapStates", null, mapStatesTab);

		//----------------------------------------------------------------------

		gameStringsLabel = new JLabel("Existing Game Strings");
		gameStringsLabel.setFont(labelFont);
		gameStringsFilterTextField = new JTextField(filterTextSize);
		gameStringsFilterTextField.setFont(filterTextFont);
		gameStringsFilterTextField.addCaretListener(this);


		gameStringsListModel = new DefaultListModel<GameString>();
		gameStringsList = new JList<GameString>(gameStringsListModel); //data has type Object
		gameStringsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		gameStringsList.setLayoutOrientation(JList.VERTICAL);
		gameStringsList.setVisibleRowCount(100);
		gameStringsList.setForeground(Color.BLACK);
		gameStringsList.setFont(listFont);
		gameStringsList.setFixedCellHeight(16);
		gameStringsList.addListSelectionListener(this);
		gameStringsList.setCellRenderer(new GameStringCellRenderer());
		JScrollPane gameStringsListScroller = new JScrollPane(gameStringsList);

		//gameStringsButton = new JButton("Add String/GameString");
		//gameStringsButton.addActionListener(this);

		gameStringsPanel = new JPanel();
		gameStringsPanel.setLayout(new BoxLayout(gameStringsPanel, BoxLayout.Y_AXIS));
		gameStringsPanel.setBackground(Color.WHITE);
		gameStringsPanel.add(gameStringsLabel);
		gameStringsPanel.add(gameStringsListScroller);


		JPanel gameStringsButtonPanel = new JPanel();
		JLabel gameStringsFilterLabel = new JLabel("Filter:");

		//gameStringsButtonPanel.add(gameStringsButton);
		gameStringsButtonPanel.add(gameStringsFilterLabel);
		gameStringsButtonPanel.add(gameStringsFilterTextField);

		gameStringsPanel.add(gameStringsButtonPanel);

		//----------------------------------------------------------------------

		gameStringsTab = new JPanel(new GridLayout(0,1,0,4));
		gameStringsTab.setBackground(tabBackgroundColor);
		gameStringsTab.add(gameStringsPanel);

		objectTabsPane.addTab("GameStrings", null, gameStringsTab);
		//----------------------------------------------------------------------


		eventsLabel = new JLabel("Events");
		eventsLabel.setFont(labelFont);
		eventsFilterTextField = new JTextField(filterTextSize);
		eventsFilterTextField.setFont(filterTextFont);
		eventsFilterTextField.addCaretListener(this);


		eventsListModel = new DefaultListModel<Event>();
		eventsList = new JList<Event>(eventsListModel); //data has type Object
		eventsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		eventsList.setLayoutOrientation(JList.VERTICAL);
		eventsList.setVisibleRowCount(100);
		eventsList.setForeground(Color.BLACK);
		eventsList.setFont(listFont);
		eventsList.setFixedCellHeight(16);
		eventsList.addListSelectionListener(this);
		eventsList.setCellRenderer(new NameCellRenderer());
		JScrollPane eventsListScroller = new JScrollPane(eventsList);

		//eventsButton = new JButton("Add Event");
		//eventsButton.addActionListener(this);

		eventsPanel = new JPanel();
		eventsPanel.setLayout(new BoxLayout(eventsPanel, BoxLayout.Y_AXIS));
		eventsPanel.setBackground(Color.WHITE);
		eventsPanel.add(eventsLabel);

		eventsPanel.add(eventsListScroller);


		JPanel eventsButtonPanel = new JPanel();
		JLabel eventsFilterLabel = new JLabel("Filter:");

		//eventsButtonPanel.add(eventsButton);
		eventsButtonPanel.add(eventsFilterLabel);
		eventsButtonPanel.add(eventsFilterTextField);

		eventsPanel.add(eventsButtonPanel);

		//----------------------------------------------------------------------


		eventsTab = new JPanel(new GridLayout(0,1,0,4));
		eventsTab.setBackground(tabBackgroundColor);
		eventsTab.add(eventsPanel);

		objectTabsPane.addTab("Events", null, eventsTab);

		//----------------------------------------------------------------------



		JPanel customValuePanel = new JPanel();
		customValuePanel.setLayout(new BoxLayout(customValuePanel, BoxLayout.Y_AXIS));

		customValueButton = new JButton("Add Custom Value");
		customValueButton.addActionListener(this);
		customValueTextField = new JTextField(30);
		customValueTextField.setMaximumSize(new Dimension(400,60));

		customValuePanel.add(new JLabel("For BOOL, INT, FLOAT, STRING"));
		customValuePanel.add(Box.createVerticalGlue());
		customValuePanel.add(customValueTextField);
		customValuePanel.add(customValueButton);
		customValuePanel.add(Box.createVerticalGlue());

		customValueTab = new JPanel(new GridLayout(0,1,0,4));
		customValueTab.setBackground(tabBackgroundColor);
		customValueTab.add(customValuePanel);

		objectTabsPane.addTab("Custom Value", null, customValueTab);

		//----------------------------------------------------------------------


	}



	//===============================================================================================
	class GameStringCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public GameStringCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : "["+((GameString)value).id()+"] "+((GameString)value).text());
				return this;
		}
	}

	//===============================================================================================
	class DialogueCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public DialogueCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : makeDialogueListString(((Dialogue)value)));
				return this;
		}
	}

	//===============================================================================================
	class DestinationNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public DestinationNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : ((GameMapObject)value).map().name()+"."+((GameObject)value).name());
				return this;
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
				setText((value == null) ? "" : ((GameObject)value).name());
				return this;
		}
	}


	//===============================================================================================
	class ShortTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public ShortTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : ((GameObject)value).getShortTypeName());
				return this;
		}
	}

	//===============================================================================================
	class LongTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public LongTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : ((GameObject)value).getLongTypeName());
				return this;
		}
	}




	//===============================================================================================
	private void initializeTree(String name)
	{//===============================================================================================


		tree = null;
		rootNode = null;
		treeModel = null;

		if(treeView!=null)treePanel.remove(treeView);
		treeView = null;


		rootNode = new DefaultMutableTreeNode(new EventCommand(name,null,EventCommand.TYPE_COMMAND));
		treeModel = new DefaultTreeModel(rootNode);
		treeModel.addTreeModelListener(this);


		tree = new JTree(treeModel);
		tree.addTreeSelectionListener(this);

		tree.setDragEnabled(true);
		//tree.setLargeModel(true);
		tree.setRowHeight(20);
		tree.setRootVisible(true);
		tree.setShowsRootHandles(true);
		tree.setExpandsSelectedPaths(true);
		tree.setBackground(Color.DARK_GRAY);
		tree.setForeground(Color.BLACK);
		tree.setDropMode(DropMode.ON);
		tree.setEditable(true);
		tree.setToggleClickCount(0);

		tree.setTransferHandler
		(


				new TransferHandler()
				{


					public boolean canImport(TransferHandler.TransferSupport info)
					{

						// we only import Strings
						if(!info.isDataFlavorSupported(DataFlavor.stringFlavor))
						{
							return false;
						}

						JTree.DropLocation dl=(JTree.DropLocation)info.getDropLocation();

//						if(dl.getIndex()==-1)
//						{
//							return false;
//						}

						return true;
					}




					public boolean importData(TransferHandler.TransferSupport info)
					{
						if(!info.isDrop())
						{
							return false;
						}

						//Check for String flavor
						if(!info.isDataFlavorSupported(DataFlavor.stringFlavor))
						{
							System.out.println("Tree doesn't accept a drop of this type.");
							return false;
						}

						JTree.DropLocation dl=(JTree.DropLocation)info.getDropLocation();
						DefaultTreeModel listModel=(DefaultTreeModel)tree.getModel();

						TreePath path = dl.getPath();
						int childIndex = dl.getChildIndex();

						//Get the current string under the drop.
						String value=(String)path.toString();

						//Get the string that is being dropped.
						Transferable t=info.getTransferable();

						String data;
						try
						{
							data=(String)t.getTransferData(DataFlavor.stringFlavor);
						}
						catch(Exception e)
						{
							return false;
						}








						DefaultMutableTreeNode selectedNode = null;
						if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return false;}//tree.setSelectionRow(tree.getRowCount()-1);
						selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
						if(selectedNode.isRoot()){errorLabel.setText("Cannot Move Root");return false;}

						for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
						int row = tree.getSelectionRows()[0];



						//get node dropped on
						DefaultMutableTreeNode droppedNode = null;


						if(childIndex!=-1)
						{
							droppedNode = (DefaultMutableTreeNode) path.getPathComponent(childIndex);
						}
						else
						{
							droppedNode = (DefaultMutableTreeNode) path.getLastPathComponent();
						}



						//remove selected node
						treeModel.removeNodeFromParent(selectedNode);


						//if we're adding to a command, we want to add AFTER it.
						if(droppedNode.getUserObject().toString().contains("==")==false)
						{

							DefaultMutableTreeNode parent = (DefaultMutableTreeNode) droppedNode.getParent();
							if(parent==null)parent = rootNode;

							//we want to insert the command after this object in its parent
							treeModel.insertNodeInto(selectedNode, parent, parent.getIndex(droppedNode)+1);
						}
						else
						//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
						{
							treeModel.insertNodeInto(selectedNode, droppedNode, 0);
						}

						for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

						tree.setSelectionPath(new TreePath(selectedNode.getPath()));


						return false;
					}




					public int getSourceActions(JComponent c)
					{
						return COPY;
					}




					protected Transferable createTransferable(JComponent c)
					{
						JTree tree=(JTree)c;
						DefaultMutableTreeNode selectedNode = null;
						selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();

						return new StringSelection(((EventCommand)selectedNode.getUserObject()).toSaveString());
					}


				}


		);


		tree.setDropMode(DropMode.ON_OR_INSERT);

		MyTreeCellRenderer renderer =  new MyTreeCellRenderer();
		renderer.setLeafIcon(null);
		renderer.setOpenIcon(null);
		renderer.setClosedIcon(null);
		renderer.setBorder(new BevelBorder(BevelBorder.RAISED, Color.LIGHT_GRAY, Color.GRAY));
		renderer.setFont(new Font("Tahoma", Font.BOLD, 11));
		tree.setCellRenderer(renderer);

		MyTreeCellEditor editor = new MyTreeCellEditor(tree,renderer);
		tree.setCellEditor(editor);


		treeView = new JScrollPane(tree,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

		treeView.setMinimumSize(new Dimension(600,100));
		treeView.setMaximumSize(new Dimension(600,400));
		treeView.setPreferredSize(new Dimension(600,400));
		treeView.setSize(new Dimension(600,400));


		treePanel.add(treeView);

		for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

		tree.setSelectionRow(0);
		//tree.setSelectionRow(tree.getRowCount()-1);
	}






	//===============================================================================================
	public void moveSelectedNodeUp()
	{//===============================================================================================

			DefaultMutableTreeNode selectedNode = null;
			if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return;}//tree.setSelectionRow(tree.getRowCount()-1);
			selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
			if(selectedNode.isRoot()){errorLabel.setText("Cannot Move Root");return;}

			for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
			int row = tree.getSelectionRows()[0];

			//get node from selected

			DefaultMutableTreeNode newNode = selectedNode;


			//get node above selected
			tree.setSelectionRow(row-1);
			DefaultMutableTreeNode oneAboveNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();

			if(oneAboveNode.isRoot())return;

			//get node two above selected so we can insert after it
			tree.setSelectionRow(row-2);
			DefaultMutableTreeNode twoAboveNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();



			//remove selected node
			treeModel.removeNodeFromParent(selectedNode);


			//if we're adding to a command, we want to add AFTER it.
			if(twoAboveNode.getUserObject().toString().contains("==")==false)
			{

				DefaultMutableTreeNode parent = (DefaultMutableTreeNode) twoAboveNode.getParent();
				if(parent==null)parent = rootNode;

				//we want to insert the command after this object in its parent
				treeModel.insertNodeInto(newNode, parent, parent.getIndex(twoAboveNode)+1);
			}
			else
			//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
			{
				treeModel.insertNodeInto(newNode, twoAboveNode, 0);
			}

			for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

			tree.setSelectionPath(new TreePath(newNode.getPath()));

	}
	//===============================================================================================
	public void moveSelectedNodeDown()
	{//===============================================================================================

		DefaultMutableTreeNode selectedNode = null;
		if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return;}//tree.setSelectionRow(tree.getRowCount()-1);
		selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
		if(selectedNode.isRoot()){errorLabel.setText("Cannot Move Root");return;}

		for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
		int row = tree.getSelectionRows()[0];

		//get node from selected

		DefaultMutableTreeNode newNode = selectedNode;

		int maxRows = tree.getRowCount();
		if(row>=maxRows-1)return;


		//remove selected node
		treeModel.removeNodeFromParent(selectedNode);

		//get node below selected (is on deleted row now)
		tree.setSelectionRow(row);

		while(tree.getSelectionPath()==null){row--;tree.setSelectionRow(row);}

		DefaultMutableTreeNode belowNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();



		//if we're adding to a command, we want to add AFTER it.
		if(belowNode.getUserObject().toString().contains("==")==false)
		{

			DefaultMutableTreeNode parent = (DefaultMutableTreeNode) belowNode.getParent();
			if(parent==null)parent = rootNode;

			//we want to insert the command after this object in its parent
			treeModel.insertNodeInto(newNode, parent, parent.getIndex(belowNode)+1);
		}
		else
		//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
		{
			treeModel.insertNodeInto(newNode, belowNode, 0);
		}

		for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

		tree.setSelectionPath(new TreePath(newNode.getPath()));

	}


	//===============================================================================================
	class MyTreeCellRenderer extends DefaultTreeCellRenderer
	{//===============================================================================================

		private static final long serialVersionUID = 1L;


		public MyTreeCellRenderer()
		{

		}

		public Component getTreeCellRendererComponent(
							JTree tree,
							Object value,
							boolean sel,
							boolean expanded,
							boolean leaf,
							int row,
							boolean hasFocus)
		{

			super.getTreeCellRendererComponent(
							tree, value, sel,
							expanded, leaf, row,
							hasFocus);

			DefaultMutableTreeNode node = (DefaultMutableTreeNode)value;


			//if(node.getUserObject().toString().contains(" == TRUE")){setForeground(new Color(0,255,0));}
			//if(node.getUserObject().toString().contains(" == FALSE")){setForeground(new Color(255,0,0));}
			if(node.getUserObject().toString().contains("ERROR")==true){setForeground(new Color(255,0,0));}



			return this;
		}




//		public Color getBackgroundSelectionColor()
//		{
//			if(getForeground()!=(Color.BLACK))return new Color(0,0,0);
////			if(isRoot)return Color.GRAY;
////			if(isBoolYes)return new Color(0,64,0);
////			if(isBoolNo)return new Color(64,0,0);
//
//
//			return backgroundSelectionColor;
//		}

//		public Color getBackgroundNonSelectionColor()
//		{
//			if(getForeground()!=(Color.BLACK))return new Color(0,0,0);
////			if(isError)return new Color(150,0,0);
////			if(isRoot)return Color.LIGHT_GRAY;
////			if(isBoolYes)return new Color(0,0,0);
////			if(isBoolNo)return new Color(0,0,0);
//
//
//			return backgroundNonSelectionColor;
//		}
//
//		public Color getTextSelectionColor()
//		{
//			if(isError)return new Color(0,0,0);
//			if(isRoot)return Color.BLACK;
//			if(isBoolYes)return new Color(0,255,0);
//			if(isBoolNo)return new Color(255,0,0);
//
//
//			return textSelectionColor;
//		}
//
//		public Color getTextNonSelectionColor()
//		{
//			if(isError)return new Color(0,0,0);
//			if(isRoot)return Color.BLACK;
//			if(isBoolYes)return new Color(0,255,0);
//			if(isBoolNo)return new Color(255,0,0);
//
//
//			return textNonSelectionColor;
//		}
	}

	class MyCellEditor extends DefaultCellEditor
	{


		@ConstructorProperties({"component"})
		public MyCellEditor(final JTextField textField)
		{
			super(textField);

			editorComponent = textField;
			this.clickCountToStart = 2;

			delegate = new EditorDelegate()
			{

				public void setValue(Object value)
				{
					String s = "";

					if(value!=null)s = value.toString();

					textField.setText(s);
				}


				public Object getCellEditorValue()
				{
					String s = textField.getText();

					EventCommand e = EventCommand.parseEventCommandFromCommandString(s);

					return e;
				}

			};

			textField.addActionListener(delegate);

		}


		public Component getTreeCellEditorComponent(JTree tree, Object value, boolean isSelected, boolean expanded, boolean leaf, int row)
		{

			String stringValue = ((EventCommand)((DefaultMutableTreeNode)value).getUserObject()).toSaveString();

			delegate.setValue(stringValue);

			return editorComponent;

		}

	}

	//===============================================================================================
	class MyTreeCellEditor extends DefaultTreeCellEditor
	{//===============================================================================================





		/**
		 * Constructs a <code>DefaultTreeCellEditor</code>
		 * object for a JTree using the specified renderer and
		 * a default editor. (Use this constructor for normal editing.)
		 *
		 * @param tree      a <code>JTree</code> object
		 * @param renderer  a <code>DefaultTreeCellRenderer</code> object
		 */
		public MyTreeCellEditor(JTree tree, MyTreeCellRenderer renderer)
		{
			super(tree, renderer, null);
		}




		/**
		 * This is invoked if a <code>TreeCellEditor</code>
		 * is not supplied in the constructor.
		 * It returns a <code>TextField</code> editor.
		 * @return a new <code>TextField</code> editor
		 */
		protected TreeCellEditor createTreeCellEditor()
		{
			Border aBorder = UIManager.getBorder("Tree.editorBorder");

			MyCellEditor editor = new MyCellEditor(new DefaultTextField(aBorder));

			// One click to edit.
			editor.setClickCountToStart(1);
			return editor;
		}







	}


	//===============================================================================================
	public void editEvent(Map map, Event event)
	{//===============================================================================================


		currentMap = map;//can be null, will use to populate the map-specific lists.


		currentEvent = event;
		if(currentEvent==null)return;



		initializeTree(event.name());

		if(currentEvent.text()!=null)
		if(currentEvent.text().length()>2)
			parseEventString(currentEvent.text());



		fillAllLists();

		for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
		tree.setSelectionRow(tree.getRowCount()-1);


	}



	//===============================================================================================
	private void parseEventString(String s)
	{//===============================================================================================


		//{disableMenus,disablePlayerControls,enablePlayerControls,enableRandomSpawn,makeCaption,setClockNormal,if(isSpriteSpawned(Sprite0) == TRUE){},if(isSpriteSpawned(Sprite0) == FALSE){disablePlayerControls}}


		//s = replaceIDsWithObjectNames(s);


		DefaultMutableTreeNode currentParent = rootNode;



		s = s.substring(1, s.length()-1);//split off { }, string now looks like "command,command,if(qualifier == TRUE){command,command}"



		while(s.length()>0)
		{


			//System.out.println(s);

			if(s.startsWith("}"))
			{
				if(s.startsWith("},"))s = s.substring(2);
				else if(s.startsWith("}"))s = s.substring(1);

				currentParent = (DefaultMutableTreeNode) currentParent.getParent();

			}
			else
			if(s.startsWith("if("))
			{
				//handle qualifier

				s = s.substring(3);//split off if(, string looks like "qualifier == TRUE){command,command}"

				String qualifier = s.substring(0,s.indexOf("{")-1);//get qualifier
				s = s.substring(s.indexOf("{")+1);//string now looks like "command,command}"

				EventCommand e = EventCommand.parseEventCommandFromCommandString(qualifier);

				DefaultMutableTreeNode qualifierNode = new DefaultMutableTreeNode(e);
				currentParent.add(qualifierNode);


				currentParent = qualifierNode;

			}
			else
			{
				if(s.indexOf(",")!=-1)//there is another instruction
				{

					if(s.indexOf("}")!=-1&&s.indexOf("}")<s.indexOf(",")) //looks like "command()},command()
					{

						String command = s.substring(0,s.indexOf("}"));//get command
						s = s.substring(s.indexOf("}"));//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(command);

						currentParent.add(new DefaultMutableTreeNode(e));

					}
					else
					if(s.indexOf("),")!=-1&&s.indexOf("),")<s.indexOf("}"))//looks like "command(),command()}"
					{

						String command = s.substring(0,s.indexOf("),")+1);//get command
						s = s.substring(s.indexOf("),")+2);//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(command);

						currentParent.add(new DefaultMutableTreeNode(e));
					}
					else//looks like "command,command}"
					{
						String command = s.substring(0,s.indexOf(","));//get command
						s = s.substring(s.indexOf(",")+1);//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(command);

						currentParent.add(new DefaultMutableTreeNode(e));

					}

				}
				else
				{

					if(s.indexOf("}")!=-1)//looks like "command}" or "command}if(thing){}" or "command}}}"
					{

						String command = s.substring(0,s.indexOf("}"));//get command
						s = s.substring(s.indexOf("}"));//split off command and comma

						EventCommand e = EventCommand.parseEventCommandFromCommandString(command);

						currentParent.add(new DefaultMutableTreeNode(e));

					}
					else //looks like "command"
					{
						String command = s;

						s=s.substring(command.length());

						EventCommand e = EventCommand.parseEventCommandFromCommandString(command);

						currentParent.add(new DefaultMutableTreeNode(e));
					}
				}

			}
		}



	}



	//===============================================================================================
	public void storeEventTreeInString()
	{//===============================================================================================
		//String text = textArea.getText().replace("\r","");
		//text = text.replace("\n","<NEWLINE>");
		//text = text.replace("<NEWLINE><NEWLINE>","<.>");

		//currentDialogue.text = text;
		//currentEvent.comment = commentTextField.getText();
		//currentEvent.gameString = gameStringTextField.getText();


		if(currentEvent!=null)
		{

			String s = "";
			s = recursivelyAddChildrenToString(((DefaultMutableTreeNode) treeModel.getRoot()), s);





			System.out.println(s);


			//s = replaceObjectNamesWithIDs(s);

			//System.out.println(s);

			//System.out.println(((DefaultMutableTreeNode) treeModel.getRoot()).breadthFirstEnumeration().toString());
			//System.out.println(((DefaultMutableTreeNode) treeModel.getRoot()).depthFirstEnumeration().toString());
			//System.out.println(((DefaultMutableTreeNode) treeModel.getRoot()).preorderEnumeration().toString());


			currentEvent.setText(s);

			currentEvent = null;
		}

	}

	//===============================================================================================
	private String recursivelyAddChildrenToString(DefaultMutableTreeNode parent, String s)
	{//===============================================================================================

		s = s.concat("{");

		int parentChildCount = treeModel.getChildCount(parent);
		//System.out.println(""+parentChildCount);

		for(int i = 0; i<parentChildCount; i++)
		{
			DefaultMutableTreeNode child = (DefaultMutableTreeNode)treeModel.getChild(parent, i);

			String saveString = ((EventCommand)child.getUserObject()).toSaveString();

			if(saveString.contains(" == "))s = s.concat("if(");

			s = s.concat(saveString);

			if(saveString.contains(" == "))s = s.concat(")");

			int childChildCount = treeModel.getChildCount(child);

			if(childChildCount>0)
			{
				s = recursivelyAddChildrenToString(child,s);
			}
			else
			{
				if(saveString.contains(" == "))s = s.concat("{}");

				if(i<parentChildCount-1)s = s.concat(",");
			}

		}
		s = s.concat("}");

		return s;

	}

	/*
	//===============================================================================================
	private String replaceObjectNamesWithIDs(String s)
	{//===============================================================================================



		String output = "";

		while(
				s.contains("ENTITY.")
				||s.contains("AREA.")
				||s.contains("DOOR.")
				||s.contains("LIGHT.")
				||s.contains("SPRITE.")
				||s.contains("MAP.")
				||s.contains("ITEM.")
				||s.contains("GAME.")
				||s.contains("SOUND.")
				||s.contains("MUSIC.")
				||s.contains("FLAG.")
				||s.contains("SKILL.")
				||s.contains("DIALOGUE.")
				||s.contains("STATE.")
				||s.contains("GAMESTRING.")
				||s.contains("EVENT.")

		)
		{



			Integer entityIndex = new Integer(s.indexOf("ENTITY."));
			Integer areaIndex = new Integer(s.indexOf("AREA."));
			Integer doorIndex = new Integer(s.indexOf("DOOR."));
			Integer lightIndex = new Integer(s.indexOf("LIGHT."));
			Integer spriteIndex = new Integer(s.indexOf("SPRITE."));
			Integer mapIndex = new Integer(s.indexOf("MAP."));
			Integer itemIndex = new Integer(s.indexOf("ITEM."));
			Integer gameIndex = new Integer(s.indexOf("GAME."));
			Integer soundIndex = new Integer(s.indexOf("SOUND."));
			Integer musicIndex = new Integer(s.indexOf("MUSIC."));
			Integer flagIndex = new Integer(s.indexOf("FLAG."));
			Integer skillIndex = new Integer(s.indexOf("SKILL."));
			Integer dialogueIndex = new Integer(s.indexOf("DIALOGUE."));
			Integer stateIndex = new Integer(s.indexOf("STATE."));
			Integer gameStringIndex = new Integer(s.indexOf("GAMESTRING."));
			Integer eventIndex = new Integer(s.indexOf("EVENT."));


			ArrayList<Integer> sortList = new ArrayList<Integer>();

				sortList.add(entityIndex);
				sortList.add(areaIndex);
				sortList.add(doorIndex);
				sortList.add(lightIndex);
				sortList.add(spriteIndex);
				sortList.add(mapIndex);
				sortList.add(itemIndex);
				sortList.add(gameIndex);
				sortList.add(soundIndex);
				sortList.add(musicIndex);
				sortList.add(flagIndex);
				sortList.add(skillIndex);
				sortList.add(dialogueIndex);
				sortList.add(stateIndex);
				sortList.add(gameStringIndex);
				sortList.add(eventIndex);

				for(int i=0;i<sortList.size();i++)if(sortList.get(i).intValue()==-1){sortList.remove(i);i--;}

				int smallestIndex = 0;
				int smallestValue = s.length();
				for(int i=0;i<sortList.size();i++)
				{
					if(sortList.get(i).intValue()<smallestValue&&sortList.get(i).intValue()>-1)
					{
						smallestIndex = i;
					}
				}

				//System.out.println("Before Clip :"+s);

				output = output.concat(s.substring(0,sortList.get(smallestIndex).intValue()));//output: function(
				s = s.substring(sortList.get(smallestIndex).intValue());//s: ENTITY.name) or ENTITY.name,

				//System.out.println("After Clip To THING.name)  : "+s);

				String nameString = "";



				char clipChar = ' ';
				if(s.indexOf(',')!=-1&&s.indexOf(')')!=-1&&s.indexOf(',')<s.indexOf(')'))clipChar=',';
				if(s.indexOf(',')!=-1&&s.indexOf(')')!=-1&&s.indexOf(')')<s.indexOf(','))clipChar=')';
				if(s.indexOf(',')==-1&&s.indexOf(')')!=-1)clipChar=')';
				if(s.indexOf(')')==-1&&s.indexOf(',')!=-1)clipChar=',';




				nameString = s.substring(s.indexOf(".")+1,s.indexOf(clipChar));// nameString: mapName.entityName
				s = s.substring(s.indexOf(clipChar));//s: ), or ,THING.thing)

				//System.out.println("After Clip To ) or , : "+s);


//
//				try
//				{
//					int i = Integer.parseInt(nameString);
//
//					//we hit a THING.number
//
//					output = output.concat(nameString);//just append the number
//
//					continue;
//
//
//				}
//				catch(NumberFormatException e)
//				{
//
//					//this is what we want
//
//				}

				if(sortList.get(smallestIndex)==entityIndex)
				{

					String mapName = nameString.substring(0,nameString.indexOf("."));//get map name
					nameString = nameString.substring(nameString.indexOf(".")+1);//split off "mapName."

					Map m = Project.getMapByName(mapName);
					Entity e = m.getEntityByName(nameString);

					if(e!=null)output = output.concat(e.getIDString());
					else output = output.concat(nameString);

					continue;

				}
				if(sortList.get(smallestIndex)==areaIndex)
				{

					String mapName = nameString.substring(0,nameString.indexOf("."));//get map name
					nameString = nameString.substring(nameString.indexOf(".")+1);//split off "mapName."

					Map m = Project.getMapByName(mapName);
					Area a = m.getAreaByName(nameString);

					if(a!=null)output = output.concat(a.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==doorIndex)
				{

					String mapName = nameString.substring(0,nameString.indexOf("."));//get map name
					nameString = nameString.substring(nameString.indexOf(".")+1);//split off "mapName."

					Map m = Project.getMapByName(mapName);
					Door d = m.getDoorByName(nameString);

					if(d!=null)output = output.concat(d.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==lightIndex)
				{

					String mapName = nameString.substring(0,nameString.indexOf("."));//get map name
					nameString = nameString.substring(nameString.indexOf(".")+1);//split off "mapName."

					Map m = Project.getMapByName(mapName);
					Light l = m.getLightByName(nameString);

					if(l!=null)output = output.concat(l.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==spriteIndex)
				{

					Sprite sprite = Project.getSpriteByName(nameString);

					if(sprite!=null)output = output.concat(sprite.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==mapIndex)
				{
					Map m = Project.getMapByName(nameString);

					if(m!=null)output = output.concat(m.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==itemIndex)
				{
					Sprite sprite = Project.getSpriteByName(nameString);

					if(sprite!=null)output = output.concat(sprite.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==gameIndex)
				{
					Sprite sprite = Project.getSpriteByName(nameString);

					if(sprite!=null)output = output.concat(sprite.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==soundIndex)
				{

					Sound sound = Project.getSoundByName(nameString);

					if(sound!=null)output = output.concat(sound.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==musicIndex)
				{
					Music music = Project.getMusicByName(nameString);

					if(music!=null)output = output.concat(music.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==flagIndex)
				{
					Flag flag = Project.getFlagByName(nameString);

					if(flag!=null)output = output.concat(flag.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==skillIndex)
				{
					Skill skill = Project.getSkillByName(nameString);

					if(skill!=null)output = output.concat(skill.getIDString());
					else output = output.concat(nameString);
					continue;

				}
				if(sortList.get(smallestIndex)==dialogueIndex)
				{
					//dialogue is already always DIALOGUE.id so nameString is just id

					output = output.concat("DIALOGUE."+nameString);
					continue;
				}

				if(sortList.get(smallestIndex)==stateIndex)
				{
					String mapName = nameString.substring(0,nameString.indexOf("."));//get map name
					nameString = nameString.substring(nameString.indexOf(".")+1);//split off "mapName."

					Map m = Project.getMapByName(mapName);
					State state = m.getStateByName(nameString);

					if(state!=null)output = output.concat(state.getIDString());
					else output = output.concat(nameString);
					continue;
				}

				if(sortList.get(smallestIndex)==gameStringIndex)
				{
					//gameString is already always GAMESTRING.id so nameString is just id

					output = output.concat("GAMESTRING."+nameString);
					continue;
				}

				if(sortList.get(smallestIndex)==eventIndex)
				{
					//event is already always EVENT.id so nameString is just id

					output = output.concat("EVENT."+nameString);
					continue;
				}

		}

		output = output.concat(s);

		//System.out.println("Output : "+output);

		return output;
	}
	//===============================================================================================
	private String replaceIDsWithObjectNames(String s)
	{//===============================================================================================



		return s;
	}

*/

	//===============================================================================================
	public void fillQualifierList()
	{//===============================================================================================

		qualifierListModel.clear();


		for(int i=0;i<EventData.qualifierList.size();i++)
		qualifierListModel.addElement(EventData.qualifierList.get(i));

		filterCommandList(qualifierListModel, qualifierListFilterTextField);

	}



	//===============================================================================================
	public void fillCommandList()
	{//===============================================================================================

		commandListModel.clear();


		for(int i=0;i<EventData.commandList.size();i++)
			commandListModel.addElement(EventData.commandList.get(i));

		filterCommandList(commandListModel, commandListFilterTextField);
	}




	//===============================================================================================
	private void fillMapEntitiesList()
	{//===============================================================================================
		mapEntitiesListModel.removeAllElements();

		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumEntities();i++)
		{
			if(mapEntitiesFilterTextField.getText().length()==0||currentMap.getEntity(i).name().toLowerCase().contains((CharSequence)mapEntitiesFilterTextField.getText().toLowerCase())==true)
			mapEntitiesListModel.addElement(currentMap.getEntity(i));
		}
		mapEntitiesList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillMapAreasList()
	{//===============================================================================================
		mapAreasListModel.removeAllElements();
		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumAreas();i++)
		{
			if(mapAreasFilterTextField.getText().length()==0||currentMap.getArea(i).name().toLowerCase().contains((CharSequence)mapAreasFilterTextField.getText().toLowerCase())==true)
			mapAreasListModel.addElement(currentMap.getArea(i));
		}
		mapAreasList.validate();
		objectTabsPane.validate();
	}

	//===============================================================================================
	private void fillAllAreasList()
	{//===============================================================================================
		allAreasListModel.removeAllElements();

		for(int m=0;m<Project.getNumMaps();m++)
		{
			for(int i=0;i<Project.getMap(m).getNumAreas();i++)
			{
				if(allAreasFilterTextField.getText().length()==0||Project.getMap(m).getArea(i).name().toLowerCase().contains((CharSequence)allAreasFilterTextField.getText().toLowerCase())==true)
				allAreasListModel.addElement(Project.getMap(m).getArea(i));
			}
		}

		allAreasList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillMapDoorsList()
	{//===============================================================================================
		mapDoorsListModel.removeAllElements();
		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumDoors();i++)
		{
			if(mapDoorsFilterTextField.getText().length()==0||currentMap.getDoor(i).name().toLowerCase().contains((CharSequence)mapDoorsFilterTextField.getText().toLowerCase())==true)
			mapDoorsListModel.addElement(currentMap.getDoor(i));
		}
		mapDoorsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillMapLightsList()
	{//===============================================================================================
		mapLightsListModel.removeAllElements();
		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumLights();i++)
		{
			if(mapLightsFilterTextField.getText().length()==0||currentMap.getLight(i).name().toLowerCase().contains((CharSequence)mapLightsFilterTextField.getText().toLowerCase())==true)
			mapLightsListModel.addElement(currentMap.getLight(i));
		}
		mapLightsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillAllDoorsList()
	{//===============================================================================================
		allDoorsListModel.removeAllElements();
		for(int m=0;m<Project.getNumMaps();m++)
		for(int i=0;i<Project.getMap(m).getNumDoors();i++)
		{
			if(allDoorsFilterTextField.getText().length()==0||(Project.getMap(m).getDoor(i).getLongTypeName().toLowerCase()).contains((CharSequence)allDoorsFilterTextField.getText().toLowerCase())==true)
			allDoorsListModel.addElement(Project.getMap(m).getDoor(i));
		}
		allDoorsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillAllWarpsList()
	{//===============================================================================================

		allWarpsListModel.removeAllElements();

		for(int m=0;m<Project.getNumMaps();m++)
		for(int i=0;i<Project.getMap(m).getNumAreas();i++)
		{
			if(Project.getMap(m).getArea(i).isWarpArea())
				if(allWarpsFilterTextField.getText().length()==0||(Project.getMap(m).name().toLowerCase()+"."+Project.getMap(m).getArea(i).name().toLowerCase()).contains((CharSequence)allWarpsFilterTextField.getText().toLowerCase())==true)
			allWarpsListModel.addElement(Project.getMap(m).getArea(i));
		}

		allWarpsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillSpritesList()
	{//===============================================================================================
		spritesListModel.removeAllElements();
		for(int i=0;i<Project.getNumSprites();i++)
		{
			if(Project.getSprite(i).isNPC()==false)
				if(spritesFilterTextField.getText().length()==0||Project.getSprite(i).name().toLowerCase().contains((CharSequence)spritesFilterTextField.getText().toLowerCase())==true)
			spritesListModel.addElement(Project.getSprite(i));
		}
		spritesList.validate();
		objectTabsPane.validate();
	}



	//===============================================================================================
	private void fillNPCsList()
	{//===============================================================================================
		npcsListModel.removeAllElements();

		for(int i=0;i<Project.getNumSprites();i++)
		{
			if(Project.getSprite(i).isNPC()==true)
			{
				if(npcsFilterTextField.getText().length()==0||Project.getSprite(i).name().toLowerCase().contains((CharSequence)npcsFilterTextField.getText().toLowerCase())==true)
					npcsListModel.addElement(Project.getSprite(i));
			}
		}

		npcsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillMapsList()
	{//===============================================================================================

		mapsListModel.removeAllElements();
		for(int i=0;i<Project.getNumMaps();i++)
		{
			if(mapsFilterTextField.getText().length()==0||Project.getMap(i).name().toLowerCase().contains((CharSequence)mapsFilterTextField.getText().toLowerCase())==true)
			mapsListModel.addElement(Project.getMap(i));
		}

		mapsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillItemsList()
	{//===============================================================================================
		itemsListModel.removeAllElements();
		for(int i=0;i<Project.getNumSprites();i++)
		{
			if(Project.getSprite(i).isItem()==true)
			{
				if(itemsFilterTextField.getText().length()==0||Project.getSprite(i).name().toLowerCase().contains((CharSequence)itemsFilterTextField.getText().toLowerCase())==true)
					itemsListModel.addElement(Project.getSprite(i));
			}
		}

		itemsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillGamesList()
	{//===============================================================================================
		gamesListModel.removeAllElements();
		for(int i=0;i<Project.getNumSprites();i++)
		{
			if(Project.getSprite(i).isGame()==true)
			{
				if(gamesFilterTextField.getText().length()==0||Project.getSprite(i).name().toLowerCase().contains((CharSequence)gamesFilterTextField.getText().toLowerCase())==true)
				gamesListModel.addElement(Project.getSprite(i));
			}
		}

		gamesList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillSoundsList()
	{//===============================================================================================
		soundsListModel.removeAllElements();
		for(int i=0;i<Project.soundList.size();i++)
		{
			Sound f = Project.soundList.get(i);
			if(soundsFilterTextField.getText().length()==0||f.name().toLowerCase().contains((CharSequence)soundsFilterTextField.getText().toLowerCase())==true)
			soundsListModel.addElement(f);
		}

		soundsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillMusicList()
	{//===============================================================================================
		musicListModel.removeAllElements();
		for(int i=0;i<Project.musicList.size();i++)
		{
			Music f = Project.musicList.get(i);
			if(musicFilterTextField.getText().length()==0||f.name().toLowerCase().contains((CharSequence)musicFilterTextField.getText().toLowerCase())==true)
			musicListModel.addElement(f);
		}

		musicList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillFlagsList()
	{//===============================================================================================
		flagsListModel.removeAllElements();
		for(int i=0;i<Project.flagList.size();i++)
		{
			Flag f = Project.flagList.get(i);
			if(flagsFilterTextField.getText().length()==0||f.name().toLowerCase().contains((CharSequence)flagsFilterTextField.getText().toLowerCase())==true)
			flagsListModel.addElement(f);
		}

		flagsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillSkillsList()
	{//===============================================================================================
		skillsListModel.removeAllElements();
		for(int i=0;i<Project.skillList.size();i++)
		{
			Skill f = Project.skillList.get(i);
			if(skillsFilterTextField.getText().length()==0||f.name().toLowerCase().contains((CharSequence)skillsFilterTextField.getText().toLowerCase())==true)
			skillsListModel.addElement(f);
		}

		skillsList.validate();
		objectTabsPane.validate();
	}


	//===============================================================================================
	private void fillDialoguesList()
	{//===============================================================================================
		dialoguesListModel.removeAllElements();
		for(int i=0;i<Project.dialogueList.size();i++)
		{

			Dialogue d = Project.dialogueList.get(i);

			if(dialoguesFilterTextField.getText().length()==0||d.text().toLowerCase().contains((CharSequence)dialoguesFilterTextField.getText().toLowerCase())==true)
			dialoguesListModel.addElement(d);
		}

		dialoguePreviewTextArea.setMinimumSize(new Dimension(300,100));
		dialoguePreviewTextArea.setMaximumSize(new Dimension(400,100));
		dialoguePreviewTextArea.setPreferredSize(new Dimension(400,100));
		dialoguePreviewTextArea.setSize(new Dimension(400,100));


		dialoguesListScroller.setMinimumSize(new Dimension(400,100));
		dialoguesListScroller.setMaximumSize(new Dimension(400,400));
		dialoguesListScroller.setPreferredSize(new Dimension(400,400));
		dialoguesListScroller.setSize(new Dimension(400,400));

		dialoguesListScroller.validate();
		dialoguesList.validate();
		objectTabsPane.validate();
	}

	//===============================================================================================
	private void fillMapStatesList()
	{//===============================================================================================
		mapStatesListModel.removeAllElements();
		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumStates();i++)
		{
			MapState mapState = currentMap.getState(i);
			if(mapStatesFilterTextField.getText().length()==0||mapState.name().toLowerCase().contains((CharSequence)mapStatesFilterTextField.getText().toLowerCase())==true)
			mapStatesListModel.addElement(mapState);
		}

		mapStatesList.validate();
		objectTabsPane.validate();
	}
	//===============================================================================================
	private void fillGameStringsList()
	{//===============================================================================================
		gameStringsListModel.removeAllElements();
		for(int i=0;i<Project.gameStringList.size();i++)
		{
			GameString gameString = Project.gameStringList.get(i);
			if(gameStringsFilterTextField.getText().length()==0||gameString.text().toLowerCase().contains((CharSequence)gameStringsFilterTextField.getText().toLowerCase())==true)
			gameStringsListModel.addElement(gameString);
		}

		gameStringsList.validate();
		objectTabsPane.validate();
	}
	//===============================================================================================
	private void fillEventsList()
	{//===============================================================================================
		eventsListModel.removeAllElements();
		if(currentMap==null)return;
		for(int i=0;i<currentMap.getNumEvents();i++)
		{
			Event event = currentMap.getEvent(i);
			if(eventsFilterTextField.getText().length()==0||event.name().toLowerCase().contains((CharSequence)eventsFilterTextField.getText().toLowerCase())==true)
			eventsListModel.addElement(event);
		}

		for(int i=0;i<Project.cutsceneEventList.size();i++)
		{
			Event event = Project.cutsceneEventList.get(i);

			if(event.type()==EventData.TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
			if(eventsFilterTextField.getText().length()==0||event.name().toLowerCase().contains((CharSequence)eventsFilterTextField.getText().toLowerCase())==true)
			eventsListModel.addElement(event);
		}

		eventsList.validate();
		objectTabsPane.validate();
	}

	//===============================================================================================
	private void fillAllLists()
	{//===============================================================================================

		fillMapEntitiesList();
		fillMapAreasList();
		fillAllAreasList();
		fillMapDoorsList();
		fillMapLightsList();
		fillAllDoorsList();
		fillAllWarpsList();
		fillSpritesList();
		fillNPCsList();
		fillMapsList();
		fillItemsList();
		fillGamesList();
		fillSoundsList();
		fillMusicList();
		fillFlagsList();
		fillSkillsList();
		fillDialoguesList();
		fillMapStatesList();
		fillGameStringsList();
		fillEventsList();
	}

	//===============================================================================================

	private void filterCommandList(DefaultListModel<EventScriptCommand> jl, JTextField tf)
	{//===============================================================================================
		if(tf.getText().length()>0)
		{
			for(int i=0;i < jl.getSize();i++)
			{
				if(jl.get(i).getCommandWithArguments().toLowerCase().contains((CharSequence)tf.getText().toLowerCase())==false){jl.remove(i);i--;}
			}
		}
		listsPanel.validate();

	}

	//===============================================================================================
	private void filterList(DefaultListModel<?> jl, JTextField tf)
	{//===============================================================================================
		if(tf.getText().length()>0)
		{
			for(int i=0;i < jl.getSize();i++)
			{
				if(((GameObject)jl.get(i)).getShortTypeName().toLowerCase().contains((CharSequence)tf.getText().toLowerCase())==false){jl.remove(i);i--;}
			}
		}
		listsPanel.validate();
		objectTabsPane.validate();
	}

	//===============================================================================================
	private void setAllListsGray()
	{//===============================================================================================
		mapEntitiesList.setBackground(defaultListColor);
		mapAreasList.setBackground(defaultListColor);
		allAreasList.setBackground(defaultListColor);
		mapDoorsList.setBackground(defaultListColor);
		mapLightsList.setBackground(defaultListColor);
		allDoorsList.setBackground(defaultListColor);
		allWarpsList.setBackground(defaultListColor);
		spritesList.setBackground(defaultListColor);
		npcsList.setBackground(defaultListColor);
		mapsList.setBackground(defaultListColor);
		itemsList.setBackground(defaultListColor);
		gamesList.setBackground(defaultListColor);
		soundsList.setBackground(defaultListColor);
		musicList.setBackground(defaultListColor);
		flagsList.setBackground(defaultListColor);
		skillsList.setBackground(defaultListColor);
		dialoguesList.setBackground(defaultListColor);
		mapStatesList.setBackground(defaultListColor);
		gameStringsList.setBackground(defaultListColor);
		eventsList.setBackground(defaultListColor);

		mapEntitiesPanel.setBackground(defaultPanelColor);
		mapAreasPanel.setBackground(defaultPanelColor);
		allAreasPanel.setBackground(defaultPanelColor);
		mapDoorsPanel.setBackground(defaultPanelColor);
		mapLightsPanel.setBackground(defaultPanelColor);
		allDoorsPanel.setBackground(defaultPanelColor);
		allWarpsPanel.setBackground(defaultPanelColor);
		spritesPanel.setBackground(defaultPanelColor);
		npcsPanel.setBackground(defaultPanelColor);
		mapsPanel.setBackground(defaultPanelColor);
		itemsPanel.setBackground(defaultPanelColor);
		gamesPanel.setBackground(defaultPanelColor);
		soundsPanel.setBackground(defaultPanelColor);
		musicPanel.setBackground(defaultPanelColor);
		flagsPanel.setBackground(defaultPanelColor);
		skillsPanel.setBackground(defaultPanelColor);
		dialoguesPanel.setBackground(defaultPanelColor);
		mapStatesPanel.setBackground(defaultPanelColor);
		gameStringsPanel.setBackground(defaultPanelColor);
		eventsPanel.setBackground(defaultPanelColor);

//		mapEntitiesButton.setBackground(defaultButtonColor);
//		mapAreasButton.setBackground(defaultButtonColor);
//		mapDoorsButton.setBackground(defaultButtonColor);
//		mapLightsButton.setBackground(defaultButtonColor);
//		allDoorsButton.setBackground(defaultButtonColor);
//		allWarpsButton.setBackground(defaultButtonColor);
//		spritesButton.setBackground(defaultButtonColor);
//		npcsButton.setBackground(defaultButtonColor);
//		mapsButton.setBackground(defaultButtonColor);
//		itemsButton.setBackground(defaultButtonColor);
//		gamesButton.setBackground(defaultButtonColor);
//		soundsButton.setBackground(defaultButtonColor);
//		musicButton.setBackground(defaultButtonColor);
//		flagsButton.setBackground(defaultButtonColor);
//		skillsButton.setBackground(defaultButtonColor);
//		dialoguesButton.setBackground(defaultButtonColor);
//		mapStatesButton.setBackground(defaultButtonColor);
//		gameStringsButton.setBackground(defaultButtonColor);
//		eventsButton.setBackground(defaultButtonColor);

		mapEntitiesLabel.setForeground(defaultLabelColor);
		mapAreasLabel.setForeground(defaultLabelColor);
		allAreasLabel.setForeground(defaultLabelColor);
		mapDoorsLabel.setForeground(defaultLabelColor);
		mapLightsLabel.setForeground(defaultLabelColor);
		allDoorsLabel.setForeground(defaultLabelColor);
		allWarpsLabel.setForeground(defaultLabelColor);
		spritesLabel.setForeground(defaultLabelColor);
		npcsLabel.setForeground(defaultLabelColor);
		mapsLabel.setForeground(defaultLabelColor);
		itemsLabel.setForeground(defaultLabelColor);
		gamesLabel.setForeground(defaultLabelColor);
		soundsLabel.setForeground(defaultLabelColor);
		musicLabel.setForeground(defaultLabelColor);
		flagsLabel.setForeground(defaultLabelColor);
		skillsLabel.setForeground(defaultLabelColor);
		dialoguesLabel.setForeground(defaultLabelColor);
		mapStatesLabel.setForeground(defaultLabelColor);
		gameStringsLabel.setForeground(defaultLabelColor);
		eventsLabel.setForeground(defaultLabelColor);
	}


	Color defaultLabelColor = Color.BLACK;
	Color defaultPanelColor = Color.LIGHT_GRAY;
	Color defaultListColor = Color.GRAY;
	Color defaultButtonColor = Color.GRAY;

	Color highlightedPanelColor = Color.BLACK;
	Color highlightedLabelColor = Color.GREEN;
	Color highlightedListColor = new Color(240,255,240);
	Color highlightedButtonColor = new Color(0,255,0);
	//===============================================================================================
	private void selectDoorsTab()
	{//===============================================================================================
		setAllListsGray();


		objectTabsPane.setSelectedComponent(doorsTab);

		//mapDoorsButton.setBackground(highlightedButtonColor);
		mapDoorsPanel.setBackground(highlightedPanelColor);
		mapDoorsList.setBackground(highlightedListColor);
		mapDoorsLabel.setForeground(highlightedLabelColor);

		//allDoorsButton.setBackground(highlightedButtonColor);
		allDoorsPanel.setBackground(highlightedPanelColor);
		allDoorsList.setBackground(highlightedListColor);
		allDoorsLabel.setForeground(highlightedLabelColor);
	}

	//===============================================================================================
	private void selectEntitiesTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(entitiesTab);

		//mapEntitiesButton.setBackground(highlightedButtonColor);
		mapEntitiesPanel.setBackground(highlightedPanelColor);
		mapEntitiesList.setBackground(highlightedListColor);
		mapEntitiesLabel.setForeground(highlightedLabelColor);

		mapLightsPanel.setBackground(highlightedPanelColor);
		mapLightsList.setBackground(highlightedListColor);
		mapLightsLabel.setForeground(highlightedLabelColor);
	}

	//===============================================================================================
	private void selectAreasTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(areasTab);

		//mapAreasButton.setBackground(highlightedButtonColor);
		mapAreasPanel.setBackground(highlightedPanelColor);
		mapAreasList.setBackground(highlightedListColor);
		mapAreasLabel.setForeground(highlightedLabelColor);

		allAreasPanel.setBackground(highlightedPanelColor);
		allAreasList.setBackground(highlightedListColor);
		allAreasLabel.setForeground(highlightedLabelColor);
	}

	//===============================================================================================
	private void selectLightsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(lightsTab);

		//mapLightsButton.setBackground(highlightedButtonColor);
		mapLightsPanel.setBackground(highlightedPanelColor);
		mapLightsList.setBackground(highlightedListColor);
		mapLightsLabel.setForeground(highlightedLabelColor);

	}


	//===============================================================================================
	private void selectWarpsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(warpsTab);

		//allWarpsButton.setBackground(highlightedButtonColor);
		allWarpsPanel.setBackground(highlightedPanelColor);
		allWarpsList.setBackground(highlightedListColor);
		allWarpsLabel.setForeground(highlightedLabelColor);
	}

	//===============================================================================================
	private void selectSpritesTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(spritesTab);

		//spritesButton.setBackground(highlightedButtonColor);
		spritesPanel.setBackground(highlightedPanelColor);
		spritesList.setBackground(highlightedListColor);
		spritesLabel.setForeground(highlightedLabelColor);

		//npcsButton.setBackground(highlightedButtonColor);
		npcsPanel.setBackground(highlightedPanelColor);
		npcsList.setBackground(highlightedListColor);
		npcsLabel.setForeground(highlightedLabelColor);
	}
	//===============================================================================================
	private void selectMapsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(mapsTab);

		//mapsButton.setBackground(highlightedButtonColor);
		mapsPanel.setBackground(highlightedPanelColor);
		mapsList.setBackground(highlightedListColor);
		mapsLabel.setForeground(highlightedLabelColor);

	}

	//===============================================================================================
	private void selectItemsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(itemsGamesTab);

		//itemsButton.setBackground(highlightedButtonColor);
		itemsPanel.setBackground(highlightedPanelColor);
		itemsList.setBackground(highlightedListColor);
		itemsLabel.setForeground(highlightedLabelColor);

	}
	//===============================================================================================
	private void selectGamesTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(itemsGamesTab);

		//gamesButton.setBackground(highlightedButtonColor);
		gamesPanel.setBackground(highlightedPanelColor);
		gamesList.setBackground(highlightedListColor);
		gamesLabel.setForeground(highlightedLabelColor);

	}
	//===============================================================================================
	private void selectSoundsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(soundsMusicTab);


		//soundsButton.setBackground(highlightedButtonColor);
		soundsPanel.setBackground(highlightedPanelColor);
		soundsList.setBackground(highlightedListColor);
		soundsLabel.setForeground(highlightedLabelColor);

	}
	//===============================================================================================
	private void selectMusicTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(soundsMusicTab);


		//musicButton.setBackground(highlightedButtonColor);
		musicPanel.setBackground(highlightedPanelColor);
		musicList.setBackground(highlightedListColor);
		musicLabel.setForeground(highlightedLabelColor);

	}
	//===============================================================================================
	private void selectFlagsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(flagsTab);


		//flagsButton.setBackground(highlightedButtonColor);
		flagsPanel.setBackground(highlightedPanelColor);
		flagsList.setBackground(highlightedListColor);
		flagsLabel.setForeground(highlightedLabelColor);

	}
	//===============================================================================================
	private void selectSkillsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(skillsTab);

		//skillButton.setBackground(highlightedButtonColor);
		skillsPanel.setBackground(highlightedPanelColor);
		skillsList.setBackground(highlightedListColor);
		skillsLabel.setForeground(highlightedLabelColor);
	}
	//===============================================================================================
	private void selectDialoguesTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(dialoguesTab);


		//dialoguesButton.setBackground(highlightedButtonColor);
		dialoguesPanel.setBackground(highlightedPanelColor);
		dialoguesList.setBackground(highlightedListColor);
		dialoguesLabel.setForeground(highlightedLabelColor);

	}

	//===============================================================================================
	private void selectMapStatesTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(mapStatesTab);


		//mapStatesButton.setBackground(highlightedButtonColor);
		mapStatesPanel.setBackground(highlightedPanelColor);
		mapStatesList.setBackground(highlightedListColor);
		mapStatesLabel.setForeground(highlightedLabelColor);

	}

	//===============================================================================================
	private void selectGameStringsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(gameStringsTab);


		//gameStringsButton.setBackground(highlightedButtonColor);
		gameStringsPanel.setBackground(highlightedPanelColor);
		gameStringsList.setBackground(highlightedListColor);
		gameStringsLabel.setForeground(highlightedLabelColor);

	}


	//===============================================================================================
	private void selectEventsTab()
	{//===============================================================================================
		setAllListsGray();

		objectTabsPane.setSelectedComponent(eventsTab);


		//eventsButton.setBackground(highlightedButtonColor);
		eventsPanel.setBackground(highlightedPanelColor);
		eventsList.setBackground(highlightedListColor);
		eventsLabel.setForeground(highlightedLabelColor);

	}

	//===============================================================================================
	private void selectCustomValueTab()
	{//===============================================================================================
		objectTabsPane.setSelectedComponent(customValueTab);
	}







	//===============================================================================================
	public void replaceSelectedText(GameObject o)
	{//===============================================================================================

		//replace selected text from editTextField
		String replace = editInstructionTextField.getSelectedText();

		if(replace!=null)parameterList.add(new EventParameter(replace,o));

		if(replace!=null)editInstructionTextField.setText(editInstructionTextField.getText().replaceFirst(replace, o.name()));

		selectVariableStrings();
	}

	//===============================================================================================
	public void replaceSelectedText(String s)
	{//===============================================================================================

		//replace selected text from editTextField
		String replace = editInstructionTextField.getSelectedText();

		if(replace!=null)parameterList.add(new EventParameter(replace,s));

		if(replace!=null)editInstructionTextField.setText(editInstructionTextField.getText().replaceFirst(replace, s));

		selectVariableStrings();
	}

	int selectionStart = 0;
	int selectionEnd = 0;


	//===============================================================================================
	public boolean selectString(String s, String sel)
	{//===============================================================================================

		if(s.contains(sel))
		{

			if(s.indexOf(sel)<editInstructionTextField.getSelectionStart())
			{

				hilit.removeAllHighlights();

				selectionStart = s.indexOf(sel);
				editInstructionTextField.setSelectionStart(selectionStart);

				String endString = s.substring(selectionStart);

				int lengthUntilNextCommand = 99;
				lengthUntilNextCommand = endString.length();
				if(endString.indexOf("_")!=-1&&endString.indexOf("_")<lengthUntilNextCommand)lengthUntilNextCommand = endString.indexOf("_");

				selectionEnd = selectionStart+lengthUntilNextCommand;
				editInstructionTextField.setSelectionEnd(selectionEnd);//s.indexOf(sel)+sel.length());//this doesn't work for OBJECTn with a variable on the end


				try
				{
					hilit.addHighlight(selectionStart, selectionEnd, painter);
				}
				catch (BadLocationException e)
				{
					e.printStackTrace();
				}



				return true;
			}
		}
		return false;
	}

	//===============================================================================================
	public void selectVariableStrings()
	{//===============================================================================================

		String s = editInstructionTextField.getText();
		s = s.replaceAll(" ","");

		editInstructionTextField.setText(s);

		editInstructionTextField.setSelectionStart(s.length()-1);
		editInstructionTextField.setSelectionEnd(s.length()-1);

		boolean selected=false;

		if(selectString(s, "DOOR")){selectDoorsTab();selected=true;}
		if(selectString(s, "MAP")){selectMapsTab();selected=true;}
		if(selectString(s, "LIGHT")){selectLightsTab();selected=true;}
		if(selectString(s, "DIALOGUE")){selectDialoguesTab();selected=true;}
		if(selectString(s, "AREA")){selectAreasTab();selected=true;}
		if(selectString(s, "WARP")){selectWarpsTab();selected=true;}
		if(selectString(s, "ENTITY")){selectEntitiesTab();selected=true;}
		if(selectString(s, "SPRITE")){selectSpritesTab();selected=true;}

		if(selectString(s, "ITEM")){selectItemsTab();selected=true;}
		if(selectString(s, "GAME")){selectGamesTab();selected=true;}
		if(selectString(s, "SOUND")){selectSoundsTab();selected=true;}
		if(selectString(s, "MUSIC")){selectMusicTab();selected=true;}
		if(selectString(s, "FLAG")){selectFlagsTab();selected=true;}
		if(selectString(s, "STATE")){selectMapStatesTab();selected=true;}
		if(selectString(s, "STRING")){selectCustomValueTab();selected=true;}
		if(selectString(s, "EVENT")){selectEventsTab();selected=true;}

		if(selectString(s, "INT")){selectCustomValueTab();selected=true;}
		if(selectString(s, "FLOAT")){selectCustomValueTab();selected=true;}
		if(selectString(s, "BOOL")){selectCustomValueTab();selected=true;}
		if(selectString(s, "SKILL")){selectSkillsTab();selected=true;}

		if(selected==true)
		{
			editInstructionTextField.setSelectionStart(selectionStart);
			editInstructionTextField.setSelectionEnd(selectionEnd);
			addInstructionButton.setForeground(Color.GRAY);
			addInstructionButton.setBackground(Color.RED);
		}


		if(selected==false)
		{
			hilit.removeAllHighlights();
			setAllListsGray();
			addInstructionButton.setVisible(true);
			addInstructionButton.setForeground(Color.BLACK);
			addInstructionButton.setBackground(Color.GREEN);
			errorLabel.setText("");
			topPanel.doLayout();
		}

	}



	//===============================================================================================
	public String makeDialogueListString(Dialogue d)
	{//===============================================================================================

		return "["+d.id()+"] ["+d.caption()+"] "+d.text();
	}
//	//===============================================================================================
//	public Dialogue getDialogueFromSelectedListString(String dialogueString)
//	{//===============================================================================================
//
//		dialogueString = dialogueString.substring(1,dialogueString.indexOf(']'));//clip off [] from [number]
//		int dialogueID = Integer.parseInt(dialogueString);
//		Dialogue selectedDialogue = Project.getDialogueByID(dialogueID);
//
//		return selectedDialogue;
//
//	}

	//===============================================================================================
	public void createNewDialogue()
	{//===============================================================================================

		//open dialogue editor
		dialogueEditor.createNewDialogue();

		Dialogue d = dialogueEditor.currentDialogue;
		dialoguesListModel.addElement(d);

		dialoguesList.setSelectedIndex(dialoguesListModel.getSize()-1);

	}

	//===============================================================================================
	public void editSelectedDialogue()
	{//===============================================================================================
		if(dialoguesList.getSelectedIndex()>=0)
		{
			//open dialogue editor

			Dialogue selectedDialogue = dialoguesList.getSelectedValue();// getDialogueFromSelectedListString(dialoguesList.getSelectedValue().toString());

			dialogueEditor.editDialogue(selectedDialogue);

			int i = dialoguesList.getSelectedIndex();
			dialoguesListModel.remove(i);

			Dialogue d = dialogueEditor.currentDialogue;
			dialoguesListModel.add(i,d);

			dialoguesList.setSelectedIndex(i);
		}

	}



	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================


		if(e.getSource()==qualifierListFilterTextField)
		{

			if(qualifierListFilterTextField.getText().length()>qualifierListFilterLastString.length())
			{
				qualifierListFilterLastString=qualifierListFilterTextField.getText();
				filterCommandList(qualifierListModel, qualifierListFilterTextField);
			}
			else
			{
				qualifierListFilterLastString=qualifierListFilterTextField.getText();
				fillQualifierList();
			}
		}
		if(e.getSource()==commandListFilterTextField)
		{

			if(commandListFilterTextField.getText().length()>commandListFilterLastString.length())
			{
				commandListFilterLastString=commandListFilterTextField.getText();
				filterCommandList(commandListModel, commandListFilterTextField);
			}
			else
			{
				commandListFilterLastString=commandListFilterTextField.getText();
				fillCommandList();
			}
		}




		if(e.getSource()==mapEntitiesFilterTextField)
		{

			if(mapEntitiesFilterTextField.getText().length()>mapEntitiesFilterLastString.length())
			{
				mapEntitiesFilterLastString=mapEntitiesFilterTextField.getText();
				filterList(mapEntitiesListModel, mapEntitiesFilterTextField);
			}
			else
			{
				mapEntitiesFilterLastString=mapEntitiesFilterTextField.getText();
				fillMapEntitiesList();
			}
		}



		if(e.getSource()==mapAreasFilterTextField)
		{

			if(mapAreasFilterTextField.getText().length()>mapAreasFilterLastString.length())
			{
				mapAreasFilterLastString=mapAreasFilterTextField.getText();
				filterList(mapAreasListModel, mapAreasFilterTextField);
			}
			else
			{
				mapAreasFilterLastString=mapAreasFilterTextField.getText();
				fillMapAreasList();
			}
		}

		if(e.getSource()==allAreasFilterTextField)
		{

			if(allAreasFilterTextField.getText().length()>allAreasFilterLastString.length())
			{
				allAreasFilterLastString=allAreasFilterTextField.getText();
				filterList(allAreasListModel, allAreasFilterTextField);
			}
			else
			{
				allAreasFilterLastString=allAreasFilterTextField.getText();
				fillAllAreasList();
			}
		}

		if(e.getSource()==mapDoorsFilterTextField)
		{

			if(mapDoorsFilterTextField.getText().length()>mapDoorsFilterLastString.length())
			{
				mapDoorsFilterLastString=mapDoorsFilterTextField.getText();
				filterList(mapDoorsListModel, mapDoorsFilterTextField);
			}
			else
			{
				mapDoorsFilterLastString=mapDoorsFilterTextField.getText();
				fillMapDoorsList();
			}
		}


		if(e.getSource()==mapLightsFilterTextField)
		{

			if(mapLightsFilterTextField.getText().length()>mapLightsFilterLastString.length())
			{
				mapLightsFilterLastString=mapLightsFilterTextField.getText();
				filterList(mapLightsListModel, mapLightsFilterTextField);
			}
			else
			{
				mapLightsFilterLastString=mapLightsFilterTextField.getText();
				fillMapLightsList();
			}
		}

		if(e.getSource()==allDoorsFilterTextField)
		{

			if(allDoorsFilterTextField.getText().length()>allDoorsFilterLastString.length())
			{
				allDoorsFilterLastString=allDoorsFilterTextField.getText();
				filterList(allDoorsListModel, allDoorsFilterTextField);
			}
			else
			{
				allDoorsFilterLastString=allDoorsFilterTextField.getText();
				fillAllDoorsList();
			}
		}



		if(e.getSource()==allWarpsFilterTextField)
		{

			if(allWarpsFilterTextField.getText().length()>allWarpsFilterLastString.length())
			{
				allWarpsFilterLastString=allWarpsFilterTextField.getText();
				filterList(allWarpsListModel, allWarpsFilterTextField);
			}
			else
			{
				allWarpsFilterLastString=allWarpsFilterTextField.getText();
				fillAllWarpsList();
			}
		}


		if(e.getSource()==spritesFilterTextField)
		{

			if(spritesFilterTextField.getText().length()>spritesFilterLastString.length())
			{
				spritesFilterLastString=spritesFilterTextField.getText();
				filterList(spritesListModel, spritesFilterTextField);
			}
			else
			{
				spritesFilterLastString=spritesFilterTextField.getText();
				fillSpritesList();
			}
		}

		if(e.getSource()==npcsFilterTextField)
		{

			if(npcsFilterTextField.getText().length()>npcsFilterLastString.length())
			{
				npcsFilterLastString=npcsFilterTextField.getText();
				filterList(npcsListModel, npcsFilterTextField);
			}
			else
			{
				npcsFilterLastString=npcsFilterTextField.getText();
				fillNPCsList();
			}
		}

		if(e.getSource()==mapsFilterTextField)
		{

			if(mapsFilterTextField.getText().length()>mapsFilterLastString.length())
			{
				mapsFilterLastString=mapsFilterTextField.getText();
				filterList(mapsListModel, mapsFilterTextField);
			}
			else
			{
				mapsFilterLastString=mapsFilterTextField.getText();
				fillMapsList();
			}
		}

		if(e.getSource()==itemsFilterTextField)
		{

			if(itemsFilterTextField.getText().length()>itemsFilterLastString.length())
			{
				itemsFilterLastString=itemsFilterTextField.getText();
				filterList(itemsListModel, itemsFilterTextField);
			}
			else
			{
				itemsFilterLastString=itemsFilterTextField.getText();
				fillItemsList();
			}
		}

		if(e.getSource()==gamesFilterTextField)
		{

			if(gamesFilterTextField.getText().length()>gamesFilterLastString.length())
			{
				gamesFilterLastString=gamesFilterTextField.getText();
				filterList(gamesListModel, gamesFilterTextField);
			}
			else
			{
				gamesFilterLastString=gamesFilterTextField.getText();
				fillGamesList();
			}
		}

		if(e.getSource()==soundsFilterTextField)
		{

			if(soundsFilterTextField.getText().length()>soundsFilterLastString.length())
			{
				soundsFilterLastString=soundsFilterTextField.getText();
				filterList(soundsListModel, soundsFilterTextField);
			}
			else
			{
				soundsFilterLastString=soundsFilterTextField.getText();
				fillSoundsList();
			}
		}

		if(e.getSource()==musicFilterTextField)
		{

			if(musicFilterTextField.getText().length()>musicFilterLastString.length())
			{
				musicFilterLastString=musicFilterTextField.getText();
				filterList(musicListModel, musicFilterTextField);
			}
			else
			{
				musicFilterLastString=musicFilterTextField.getText();
				fillMusicList();
			}
		}

		if(e.getSource()==flagsFilterTextField)
		{

			if(flagsFilterTextField.getText().length()>flagsFilterLastString.length())
			{
				flagsFilterLastString=flagsFilterTextField.getText();
				filterList(flagsListModel, flagsFilterTextField);
			}
			else
			{
				flagsFilterLastString=flagsFilterTextField.getText();
				fillFlagsList();
			}
		}

		if(e.getSource()==skillsFilterTextField)
		{

			if(skillsFilterTextField.getText().length()>skillsFilterLastString.length())
			{
				skillsFilterLastString=skillsFilterTextField.getText();
				filterList(skillsListModel, skillsFilterTextField);
			}
			else
			{
				skillsFilterLastString=skillsFilterTextField.getText();
				fillSkillsList();
			}
		}

		if(e.getSource()==dialoguesFilterTextField)
		{

			if(dialoguesFilterTextField.getText().length()>dialoguesFilterLastString.length())
			{
				dialoguesFilterLastString=dialoguesFilterTextField.getText();
				filterList(dialoguesListModel, dialoguesFilterTextField);
			}
			else
			{
				dialoguesFilterLastString=dialoguesFilterTextField.getText();
				fillDialoguesList();
			}
		}

		if(e.getSource()==mapStatesFilterTextField)
		{

			if(mapStatesFilterTextField.getText().length()>mapStatesFilterLastString.length())
			{
				mapStatesFilterLastString=mapStatesFilterTextField.getText();
				filterList(mapStatesListModel, mapStatesFilterTextField);
			}
			else
			{
				mapStatesFilterLastString=mapStatesFilterTextField.getText();
				fillMapStatesList();
			}
		}

		if(e.getSource()==gameStringsFilterTextField)
		{

			if(gameStringsFilterTextField.getText().length()>gameStringsFilterLastString.length())
			{
				gameStringsFilterLastString=gameStringsFilterTextField.getText();
				filterList(gameStringsListModel, gameStringsFilterTextField);
			}
			else
			{
				gameStringsFilterLastString=gameStringsFilterTextField.getText();
				fillGameStringsList();
			}
		}

		if(e.getSource()==eventsFilterTextField)
		{

			if(eventsFilterTextField.getText().length()>eventsFilterLastString.length())
			{
				eventsFilterLastString=eventsFilterTextField.getText();
				filterList(eventsListModel, eventsFilterTextField);
			}
			else
			{
				eventsFilterLastString=eventsFilterTextField.getText();
				fillEventsList();
			}
		}

	}




	//===============================================================================================
	public boolean checkError(String s)
	{//===============================================================================================


		/*

		if(s.contains("ENTITY."))
		{
			s = s.substring(s.indexOf(".")+1);//split off "ENTITY."

			String mapName = s.substring(0,s.indexOf("."));//get map name
			s = s.substring(s.indexOf(".")+1);//split off "mapName."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			Map m = Project.getMapByName(mapName);

			for(int i=0;i<m.getNumEntities();i++)
			{

				if(m.getEntity(i).getName().equals(s))return false;
			}

			return true;

		}

		if(s.contains("AREA."))
		{
			s = s.substring(s.indexOf(".")+1);//split off "AREA."
			String mapName = s.substring(0,s.indexOf("."));//get map name
			s = s.substring(s.indexOf(".")+1);//split off "mapName."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			Map m = Project.getMapByName(mapName);

			for(int i=0;i<m.getNumAreas();i++)
			{

				if(m.getArea(i).getName().equals(s))return false;
			}

			return true;

		}

		if(s.contains("DOOR."))
		{
			s = s.substring(s.indexOf(".")+1);//split off "DOOR."
			String mapName = s.substring(0,s.indexOf("."));//get map name
			s = s.substring(s.indexOf(".")+1);//split off "mapName."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			Map m = Project.getMapByName(mapName);

			for(int i=0;i<m.getNumDoors();i++)
			{

				if(m.getDoor(i).getName().equals(s))return false;
			}

			return true;

		}

		if(s.contains("LIGHT."))
		{

			s = s.substring(s.indexOf(".")+1);//split off "LIGHT."
			String mapName = s.substring(0,s.indexOf("."));//get map name
			s = s.substring(s.indexOf(".")+1);//split off "mapName."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			Map m = Project.getMapByName(mapName);

			for(int i=0;i<m.getNumLights();i++)
			{

				if(m.getLight(i).getName().equals(s))return false;
			}

			return true;
		}

		if(s.contains("SPRITE."))
		{

			s = s.substring(s.indexOf(".")+1);//split off "SPRITE."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			for(int i=0;i<Project.getNumSprites();i++)
			{
				if(Project.getSprite(i).getName().equals(s))return false;
			}

			return true;

		}

		if(s.contains("MAP."))
		{

			s = s.substring(s.indexOf(".")+1);//split off "MAP."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"


			for(int i=0;i<Project.getNumMaps();i++)
			{

				if(Project.getMap(i).getName().equals(s))return false;
			}

			return true;
		}

		if(s.contains("ITEM."))
		{
			s = s.substring(s.indexOf(".")+1);//split off "ITEM."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			for(int i=0;i<Project.getNumSprites();i++)
			{

				if(Project.getSprite(i).getName().equals(s))return false;
			}

			return true;

		}

		if(s.contains("GAME."))
		{

			s = s.substring(s.indexOf(".")+1);//split off "GAME."

			if(s.contains(")"))s = s.substring(0,s.indexOf(")"));//split off ") == TRUE"

			for(int i=0;i<Project.getNumSprites();i++)
			{

				if(Project.getSprite(i).getName().equals(s))return false;
			}

			return true;
		}


		if(s.contains("SOUND."))
		{
			s = s.substring(s.indexOf(".")+1);

		}


		if(s.contains("MUSIC."))
		{
			s = s.substring(s.indexOf(".")+1);

		}


		if(s.contains("FLAG."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		if(s.contains("SKILL."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		if(s.contains("DIALOGUE."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		if(s.contains("STATE."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		if(s.contains("GAMESTRING."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		if(s.contains("EVENT."))
		{
			s = s.substring(s.indexOf(".")+1);

		}

		*/

		return false;

	}





	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================


		if(ae.getSource() == createNewDialogueButton)
		{
			createNewDialogue();
		}

		if(ae.getSource() == editSelectedDialogueButton)
		{
			editSelectedDialogue();

		}


		if(ae.getSource() == newFlagButton)
		{

			StringDialog sd = new StringDialog(f);
			sd.show("");

			flagsListModel.addElement(new Flag(sd.newName.getText()));
			flagsList.setSelectedIndex(flagsListModel.size()-1);
		}

		if(ae.getSource() == newSkillButton)
		{

			StringDialog sd = new StringDialog(f);
			sd.show("");

			skillsListModel.addElement(new Skill(sd.newName.getText()));
			skillsList.setSelectedIndex(skillsListModel.size()-1);
		}

		if(ae.getSource() == addSelectedObjectButton)
		{
			if(selectedObject!=null)replaceSelectedText(selectedObject);
			selectedObject=null;

			mapEntitiesList.getSelectionModel().clearSelection();
			mapAreasList.getSelectionModel().clearSelection();
			allAreasList.getSelectionModel().clearSelection();
			mapDoorsList.getSelectionModel().clearSelection();
			mapLightsList.getSelectionModel().clearSelection();
			allDoorsList.getSelectionModel().clearSelection();
			allWarpsList.getSelectionModel().clearSelection();
			spritesList.getSelectionModel().clearSelection();
			npcsList.getSelectionModel().clearSelection();
			mapsList.getSelectionModel().clearSelection();
			itemsList.getSelectionModel().clearSelection();
			gamesList.getSelectionModel().clearSelection();
			soundsList.getSelectionModel().clearSelection();
			musicList.getSelectionModel().clearSelection();
			mapStatesList.getSelectionModel().clearSelection();
			gameStringsList.getSelectionModel().clearSelection();
			eventsList.getSelectionModel().clearSelection();
			dialoguesList.getSelectionModel().clearSelection();
		}

		if(ae.getSource() == addTHISButton)
		{
			replaceSelectedText("THIS");
		}

		if(ae.getSource() == addPLAYERButton)
		{
			replaceSelectedText("PLAYER");
		}

//		if(ae.getSource() == mapEntitiesButton)
//		{
//			if(mapEntitiesList.getSelectedValue()!=null)replaceSelectedText(mapEntitiesList.getSelectedValue());
//
//		}
//
//		if(ae.getSource() == mapAreasButton)
//		{
//
//			if(mapAreasList.getSelectedValue()!=null)replaceSelectedText(mapAreasList.getSelectedValue());
//		}
//		if(ae.getSource() == mapDoorsButton)
//		{
//
//			if(mapDoorsList.getSelectedValue()!=null)replaceSelectedText(mapDoorsList.getSelectedValue());
//		}
//		if(ae.getSource() == mapLightsButton)
//		{
//
//			if(mapLightsList.getSelectedValue()!=null)replaceSelectedText(mapLightsList.getSelectedValue());
//		}
//		if(ae.getSource() == allDoorsButton)
//		{
//
//			if(allDoorsList.getSelectedValue()!=null)replaceSelectedText(allDoorsList.getSelectedValue());
//		}
//		if(ae.getSource() == allWarpsButton)
//		{
//
//			if(allWarpsList.getSelectedValue()!=null)replaceSelectedText(allWarpsList.getSelectedValue());
//		}
//		if(ae.getSource() == spritesButton)
//		{
//
//			if(spritesList.getSelectedValue()!=null)replaceSelectedText(spritesList.getSelectedValue());
//		}
//		if(ae.getSource() == npcsButton)
//		{
//
//			if(npcsList.getSelectedValue()!=null)replaceSelectedText(npcsList.getSelectedValue());
//		}
//		if(ae.getSource() == mapsButton)
//		{
//
//			if(mapsList.getSelectedValue()!=null)replaceSelectedText(mapsList.getSelectedValue());
//		}
//
//		if(ae.getSource() == itemsButton)
//		{
//
//			if(itemsList.getSelectedValue()!=null)replaceSelectedText(itemsList.getSelectedValue());
//		}
//		if(ae.getSource() == gamesButton)
//		{
//
//			if(gamesList.getSelectedValue()!=null)replaceSelectedText(gamesList.getSelectedValue());
//		}
//		if(ae.getSource() == soundsButton)
//		{
//
//			if(soundsList.getSelectedValue()!=null)replaceSelectedText(soundsList.getSelectedValue());
//		}
//		if(ae.getSource() == musicButton)
//		{
//
//			if(musicList.getSelectedValue()!=null)replaceSelectedText(musicList.getSelectedValue());
//		}
//		if(ae.getSource() == flagsButton)
//		{
//
//			if(flagsList.getSelectedValue()!=null)replaceSelectedText(flagsList.getSelectedValue());
//		}
//		if(ae.getSource() == skillsButton)
//		{
//
//			if(skillsList.getSelectedValue()!=null)replaceSelectedText(skillsList.getSelectedValue());
//		}
//		if(ae.getSource() == dialoguesButton)
//		{
//
//			if(dialoguesList.getSelectedValue()!=null)
//			{
//				//Dialogue d = getDialogueFromSelectedListString(dialoguesList.getSelectedValue());
//				//replaceSelectedText("DIALOGUE."+d.id);
//				replaceSelectedText(dialoguesList.getSelectedValue());
//			}
//		}
//		if(ae.getSource() == mapStatesButton)
//		{
//			if(mapStatesList.getSelectedValue()!=null)replaceSelectedText(mapStatesList.getSelectedValue());
//		}
//
//		if(ae.getSource() == gameStringsButton)
//		{
//			if(gameStringsList.getSelectedValue()!=null)replaceSelectedText(gameStringsList.getSelectedValue());
//		}
//		if(ae.getSource() == eventsButton)
//		{
//
//			if(eventsList.getSelectedValue()!=null)replaceSelectedText(eventsList.getSelectedValue());
//		}
//
//

		if(ae.getSource() == customValueButton)
		{
			String t = customValueTextField.getText();
			if(t.length()>0)
			{
				if(t.toUpperCase().equals("TRUE"))t = "TRUE";
				if(t.toUpperCase().equals("FALSE"))t = "FALSE";

				replaceSelectedText(t);

			}
			customValueTextField.setText("");
		}



//
//		if(ae.getSource() == treeEditButton)
//		{
//
//			DefaultMutableTreeNode selectedNode = null;
//			if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return;}//tree.setSelectionRow(tree.getRowCount()-1);
//			selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
//			if(selectedNode.isRoot()){errorLabel.setText("Cannot Edit Root");return;}
//			if(selectedNode.getChildCount()>0){errorLabel.setText("Node Has Children");return;}
//			if(selectedNode.getUserObject().toString().contains(" == ")){errorLabel.setText("Can't Edit Qualifier");return;}
//
//			for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
//			int row = tree.getSelectionRows()[0];
//
//
//			String editString = selectedNode.getUserObject().toString();
//			editString = editString.replaceAll(" ","");
//			if(editString.indexOf("_")!=-1)editString = editString.substring(0,editString.indexOf("_"));
//			//editInstructionTextField.setText(selectedNode.getUserObject().toString());
//
//			treeModel.removeNodeFromParent(selectedNode);
//
//			tree.setSelectionRow(row-1);
//
//			lastSelectedFromQualifierList = false;
//			lastSelectedFromCommandList = true;
//
//			int editIndex = 0;
//			Enumeration<EventScriptCommand> en = commandListModel.elements();
//			for(int i=0;en.hasMoreElements();i++)
//			{
//				if(en.nextElement().getCommand().startsWith(editString)){editIndex=i;break;}
//			}
//			commandList.setSelectedIndex(editIndex);
//
//		}


		if(ae.getSource() == treeDuplicateButton)
		{

			DefaultMutableTreeNode selectedNode = null;
			if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return;}//tree.setSelectionRow(tree.getRowCount()-1);
			selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
			if(selectedNode.isRoot()){errorLabel.setText("Cannot Duplicate Root");return;}
			if(selectedNode.getChildCount()>0){errorLabel.setText("Node Has Children");return;}
			if(selectedNode.getUserObject().toString().contains(" == ")){errorLabel.setText("Can't Duplicate Qualifier");return;}

			for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);


			DefaultMutableTreeNode top = null;
			DefaultMutableTreeNode node = null;

			if(tree.getSelectionPath()==null)return;//tree.setSelectionRow(tree.getRowCount()-1);

			top = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();

			String s = ((EventCommand)selectedNode.getUserObject()).toSaveString();
			EventCommand e = EventCommand.parseEventCommandFromCommandString(s);
			node = new DefaultMutableTreeNode(e);

			//if we're adding to a command, we want to add AFTER it.
			if(top.getUserObject().toString().contains("==")==false)
			{

				DefaultMutableTreeNode parent = (DefaultMutableTreeNode) top.getParent();
				if(parent==null)parent = rootNode;

				//we want to insert the command after this object in its parent
				treeModel.insertNodeInto(node, parent, parent.getIndex(top)+1);
			}
			else
			//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
			{
				treeModel.insertNodeInto(node, top, 0);
			}

			for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

			tree.setSelectionPath(new TreePath(node.getPath()));

		}


		if(ae.getSource() == treeMoveUpButton)
		{
			moveSelectedNodeUp();
		}

		if(ae.getSource() == treeMoveDownButton)
		{
			moveSelectedNodeDown();
		}

		if(ae.getSource() == treeDeleteButton)
		{
			DefaultMutableTreeNode selectedNode = null;
			if(tree.getSelectionPath()==null){errorLabel.setText("No Selection");return;}//tree.setSelectionRow(tree.getRowCount()-1);
			selectedNode = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
			if(selectedNode.isRoot()){errorLabel.setText("Cannot Delete Root");return;}
			if(selectedNode.getChildCount()>0){errorLabel.setText("Node Has Children");return;}
			//if(selectedNode.getUserObject().toString().contains(" == ")){errorLabel.setText("Node Is Qualifier");return;}

			treeModel.removeNodeFromParent(selectedNode);
		}


		if(ae.getSource() == addInstructionButton)
		{

			if(tree.getSelectionPath()==null)
			{
				errorLabel.setText("Select a node to add to.");
				topPanel.doLayout();
				return;
			}
			else
			{
				errorLabel.setText("");
				topPanel.doLayout();
			}


			if(editInstructionTextField.getText().length()<2)return;

			selectVariableStrings();

			addInstructionButton.setVisible(false);

			String s = editInstructionTextField.getSelectedText();
			if(s!=null)
			{
				errorLabel.setText("Replace \""+s+"\" with a value.");
				topPanel.doLayout();
				return;
			}
			else
			{
				errorLabel.setText("");
				topPanel.doLayout();
			}

			if(lastSelectedFromQualifierList)
			{
				//add twice, once == TRUE, once == FALSE
				DefaultMutableTreeNode top = null;
				DefaultMutableTreeNode node = null;

				if(tree.getSelectionPath()==null)return;//tree.setSelectionRow(tree.getRowCount()-1);

				top = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();

				String qualifierString = qualifierList.getSelectedValue().getCommand();
				qualifierString = qualifierString.replaceAll(" ","");
				if(qualifierString.indexOf("_")!=-1)qualifierString = qualifierString.substring(0,qualifierString.indexOf("_"));
				node = new DefaultMutableTreeNode(new EventCommand(qualifierString,parameterList, EventCommand.TYPE_QUALIFIER_TRUE));
				//node = new DefaultMutableTreeNode(editInstructionTextField.getText() + " == TRUE");


				//if we're adding to a command, we want to add AFTER it.
				if(top.getUserObject().toString().contains("==")==false)
				{

					DefaultMutableTreeNode parent = (DefaultMutableTreeNode) top.getParent();
					if(parent==null)parent = rootNode;

					//we want to insert the command after this object in its parent
					treeModel.insertNodeInto(node, parent, parent.getIndex(top)+1);
				}
				else
				//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
				{
					treeModel.insertNodeInto(node, top, 0);
				}

				for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

				tree.setSelectionPath(new TreePath(node.getPath()));



				//now we've selected the one we just put in there, and we want to put a FALSE directly after it

				top = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();


				node = new DefaultMutableTreeNode(new EventCommand(qualifierString,parameterList, EventCommand.TYPE_QUALIFIER_FALSE));
				//node = new DefaultMutableTreeNode(editInstructionTextField.getText() + " == FALSE");


				DefaultMutableTreeNode parent = (DefaultMutableTreeNode) top.getParent();
				if(parent==null)parent = rootNode;

				//we want to insert the command after this object in its parent
				treeModel.insertNodeInto(node, parent, parent.getIndex(top)+1);

				for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);

				tree.setSelectionPath(new TreePath(node.getPath()));


				editInstructionTextField.setText("");

			}



			if(lastSelectedFromCommandList)
			{
				//add once

				DefaultMutableTreeNode top = null;
				DefaultMutableTreeNode node = null;

				if(tree.getSelectionPath()==null)return;//tree.setSelectionRow(tree.getRowCount()-1);


				top = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();


				String commandString = commandList.getSelectedValue().getCommand();
				commandString = commandString.replaceAll(" ","");
				if(commandString.indexOf("_")!=-1)commandString = commandString.substring(0,commandString.indexOf("_"));

				node = new DefaultMutableTreeNode(new EventCommand(commandString,parameterList, EventCommand.TYPE_COMMAND));
				//node = new DefaultMutableTreeNode(editInstructionTextField.getText());



				//if we're adding to a command, we want to add AFTER it.
				if(top.getUserObject().toString().contains("==")==false)
				{

					DefaultMutableTreeNode parent = (DefaultMutableTreeNode) top.getParent();
					if(parent==null)parent = rootNode;

					//we want to insert the command after this object in its parent
					treeModel.insertNodeInto(node, parent, parent.getIndex(top)+1);

					//((DefaultMutableTreeNode) top.getParent()).insert(node,top.getParent().getIndex(top)+1);
				}
				else
				//if we're adding to a qualifier (if(Something)==true) we want to add INSIDE of it.
				{

					treeModel.insertNodeInto(node, top, 0);


				}

				//for(int i=0;i<tree.getRowCount();i++)tree.collapseRow(i);

				for(int i=0;i<tree.getRowCount();i++)tree.expandRow(i);
				//tree.validate();

				tree.setSelectionPath(new TreePath(node.getPath()));

				//tree.setSelectionRow(tree.getSelectionPath().getPathCount());
				//tree.setSelectionRow(treeModel.getPathToRoot(node).length);

				editInstructionTextField.setText("");

			}


		}

	}





	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================


		if(e.getSource() == qualifierList)
		{
			lastSelectedFromQualifierList=true;
			lastSelectedFromCommandList=false;

			if(qualifierList.getSelectedValue()==null)return;

			editInstructionTextField.setText(qualifierList.getSelectedValue().getCommandWithArguments());

			parameterList = new ArrayList<EventParameter>();

			selectVariableStrings();
		}


		if(e.getSource() == commandList)
		{
			lastSelectedFromQualifierList=false;
			lastSelectedFromCommandList=true;

			if(commandList.getSelectedValue()==null)return;

			editInstructionTextField.setText(commandList.getSelectedValue().getCommandWithArguments());

			parameterList = new ArrayList<EventParameter>();

			selectVariableStrings();
		}





		if(e.getSource() == mapEntitiesList)
		{
			if(mapEntitiesList.getSelectedValue()!=null)
			{
				selectedObject = mapEntitiesList.getSelectedValue();
				focusOnEntityInMapCanvas((Entity) mapEntitiesList.getSelectedValue());

			}
		}
		if(e.getSource() == mapAreasList)
		{
			if(mapAreasList.getSelectedValue()!=null)
			{
				selectedObject = mapAreasList.getSelectedValue();
				focusOnAreaInMapCanvas((Area) mapAreasList.getSelectedValue());

			}
		}
		if(e.getSource() == allAreasList)
		{
			if(allAreasList.getSelectedValue()!=null)
			{
				selectedObject = allAreasList.getSelectedValue();
				//focusOnAreaInMapCanvas((Area) allAreasList.getSelectedValue());

			}
		}
		if(e.getSource() == mapDoorsList)
		{
			if(mapDoorsList.getSelectedValue()!=null)
			{
				selectedObject = mapDoorsList.getSelectedValue();
				focusOnDoorInMapCanvas((Door) mapDoorsList.getSelectedValue());

			}
		}
		if(e.getSource() == mapLightsList)
		{
			if(mapLightsList.getSelectedValue()!=null)
			{
				selectedObject = mapLightsList.getSelectedValue();
				focusOnLightInMapCanvas((Light) mapLightsList.getSelectedValue());

			}
		}
		if(e.getSource() == allDoorsList)
		{
			if(allDoorsList.getSelectedValue()!=null)
			{
				selectedObject = allDoorsList.getSelectedValue();

			}
		}
		if(e.getSource() == allWarpsList)
		{
			if(allWarpsList.getSelectedValue()!=null)
			{
				selectedObject = allWarpsList.getSelectedValue();

			}
		}
		if(e.getSource() == spritesList)
		{
			if(spritesList.getSelectedValue()!=null)
			{
				selectedObject = spritesList.getSelectedValue();
				drawSpritePreview((Sprite) spritesList.getSelectedValue());

			}
		}
		if(e.getSource() == npcsList)
		{
			if(npcsList.getSelectedValue()!=null)
			{
				selectedObject = npcsList.getSelectedValue();
				drawSpritePreview((Sprite) npcsList.getSelectedValue());

			}
		}
		if(e.getSource() == mapsList)
		{
			if(mapsList.getSelectedValue()!=null)
			{
				selectedObject = mapsList.getSelectedValue();

			}
		}

		if(e.getSource() == itemsList)
		{
			if(itemsList.getSelectedValue()!=null)
			{
				selectedObject = itemsList.getSelectedValue();
				drawSpritePreview((Sprite) itemsList.getSelectedValue());

			}
		}
		if(e.getSource() == gamesList)
		{
			if(gamesList.getSelectedValue()!=null)
			{
				selectedObject = gamesList.getSelectedValue();
				drawSpritePreview((Sprite) gamesList.getSelectedValue());

			}
		}
		if(e.getSource() == soundsList)
		{
			if(soundsList.getSelectedValue()!=null)
			{
				selectedObject = soundsList.getSelectedValue();
				playSoundPreview((Sound) soundsList.getSelectedValue());

			}
		}
		if(e.getSource() == musicList)
		{
			if(musicList.getSelectedValue()!=null)
			{
				selectedObject = musicList.getSelectedValue();
				playMusicPreview((Music) musicList.getSelectedValue());

			}
		}
		if(e.getSource() == flagsList)
		{
			if(flagsList.getSelectedValue()!=null)
			{
				selectedObject = flagsList.getSelectedValue();
				flagsList.getSelectionModel().clearSelection();

			}
		}

		if(e.getSource() == skillsList)
		{
			if(skillsList.getSelectedValue()!=null)
			{
				selectedObject = skillsList.getSelectedValue();
				skillsList.getSelectionModel().clearSelection();

			}
		}
		if(e.getSource() == mapStatesList)
		{
			if(mapStatesList.getSelectedValue()!=null)
			{
				selectedObject = mapStatesList.getSelectedValue();

			}
		}
		if(e.getSource() == gameStringsList)
		{
			if(gameStringsList.getSelectedValue()!=null)
			{
				selectedObject = gameStringsList.getSelectedValue();

			}
		}
		if(e.getSource() == eventsList)
		{
			if(eventsList.getSelectedValue()!=null)
			{
				selectedObject = eventsList.getSelectedValue();

			}
		}
		if(e.getSource() == dialoguesList)
		{
			if(dialoguesList.getSelectedValue()!=null)
			{

				selectedObject = dialoguesList.getSelectedValue();


				dialoguePreviewTextArea.setText("");
				if(dialoguesList.getSelectedIndex()>=0)
				{
					Dialogue d = (Dialogue) dialoguesList.getSelectedValue();//getDialogueFromSelectedListString(dialoguesList.getSelectedValue().toString());

					String s = d.text().replace("<.>", "\n\n").replace("<NEWLINE>", "\n");

					dialoguePreviewTextArea.setText(d.caption()+"\n"+"//"+d.comment()+"\n"+s);

				}


			}

		}


	}







	//===============================================================================================
	@Override
	public void valueChanged(TreeSelectionEvent e)
	{//===============================================================================================


		//if i select a node with an object in it, open to the object tab and select that object so i can read it.


		DefaultMutableTreeNode node = (DefaultMutableTreeNode)e.getPath().getLastPathComponent();
		if(node!=null)
		{
			EventCommand ec = ((EventCommand)node.getUserObject());

			if(ec.parameterList!=null)
			{
				for(int i=0;i<ec.parameterList.size();i++)
				{
					EventParameter ep = ec.parameterList.get(i);

					if(ep.object!=null)
					{
						if(ep.typeString.startsWith("ITEM")){selectItemsTab();itemsList.setSelectedValue(ep.object,true);}
						if(ep.typeString.startsWith("GAME")){selectGamesTab();gamesList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(GameString.class)){selectGameStringsTab();gameStringsList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Dialogue.class)){selectDialoguesTab();dialoguesList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Area.class))
						{
							selectAreasTab();

							if(mapAreasListModel.contains(ep.object))mapAreasList.setSelectedValue(ep.object,true);
							if(allAreasListModel.contains(ep.object))allAreasList.setSelectedValue(ep.object,true);

						}
						else if(ep.object.getClass().equals(Entity.class)){selectEntitiesTab();mapEntitiesList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Door.class))
						{
							selectDoorsTab();

							if(mapDoorsListModel.contains(ep.object))mapDoorsList.setSelectedValue(ep.object,true);
							if(allDoorsListModel.contains(ep.object))allDoorsList.setSelectedValue(ep.object,true);

						}
						else if(ep.object.getClass().equals(Light.class)){selectLightsTab();mapLightsList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Sprite.class)){selectSpritesTab();spritesList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Sound.class)){selectSoundsTab();soundsList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Music.class)){selectMusicTab();musicList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(MapState.class)){selectMapStatesTab();mapStatesList.setSelectedValue(ep.object,true);}
						else if(ep.object.getClass().equals(Event.class)){selectEventsTab();eventsList.setSelectedValue(ep.object,true);}
					}
				}

			}



//			if(.toString().contains("DIALOGUE."))
//			{
//				String s = node.getUserObject().toString();
//				s = s.substring(s.indexOf(".")+1);
//				s = s.substring(0, s.indexOf(")"));
//
//				int dialogueID = Integer.parseInt(s);
//
//				Dialogue selectedDialogue = Project.getDialogueByID(dialogueID);
//
//				selectDialoguesTab();
//				dialoguesList.setSelectedIndex(dialogueID);
//
//			}
		}

	}




	//===============================================================================================
	@Override
	public void treeNodesChanged(TreeModelEvent e)
	{//===============================================================================================


	}




	//===============================================================================================
	@Override
	public void treeNodesInserted(TreeModelEvent e)
	{//===============================================================================================


	}




	//===============================================================================================
	@Override
	public void treeNodesRemoved(TreeModelEvent e)
	{//===============================================================================================


	}




	//===============================================================================================
	@Override
	public void treeStructureChanged(TreeModelEvent e)
	{//===============================================================================================


	}





	//===============================================================================================
	private void playMusicPreview(Music music)
	{//===============================================================================================





	}
	//===============================================================================================
	private void playSoundPreview(Sound sound)
	{//===============================================================================================




	}


	//===============================================================================================
	private void drawSpritePreview(Sprite s)
	{//===============================================================================================




		//repaint panel with selected sprite
		Graphics G = spritePreviewPanel.getGraphics();

		G.setColor(Color.WHITE);
		G.fillRect(0, 0, spritePreviewPanel.getWidth(), spritePreviewPanel.getHeight());




		G.drawImage(s.getFrameImage(0), 0,0,s.wP()*2,s.hP()*2,this);







	}
	//===============================================================================================
	private void focusOnLightInMapCanvas(Light l)
	{//===============================================================================================

		if(currentMap==null)return;

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())
		{
			//need to find the area by name
			//get the area index in map

			int index = -1;

			for(int i=0;i<currentMap.getNumLights();i++)
			{
				Light a = currentMap.getLight(i);

				if(a==l){index = i;break;}

			}

			if(index==-1)return;

			//select the area layer if enabled
			MapCanvas.selectedLayer=MapData.MAP_LIGHT_LAYER;


			//select action on map and repaint
			currentMap.setSelectedLightIndex(index);

			EditorMain.mapCanvas.scrollToTop(currentMap.getSelectedLight());

		}

	}
	//===============================================================================================
	private void focusOnDoorInMapCanvas(Door d)
	{//===============================================================================================

		if(currentMap==null)return;


		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())
		{
			//need to find the area by name
			//get the area index in map

			int index = -1;

			for(int i=0;i<currentMap.getNumDoors();i++)
			{
				Door a = currentMap.getDoor(i);

				if(a==d){index = i;break;}

			}

			if(index==-1)return;


			//select the area layer if enabled
			MapCanvas.selectedLayer=MapData.MAP_DOOR_LAYER;


			//select action on map and repaint
			currentMap.setSelectedDoorIndex(index);

			EditorMain.mapCanvas.scrollToTop(currentMap.getSelectedDoor());

		}

	}
	//===============================================================================================
	private void focusOnAreaInMapCanvas(Area a)
	{//===============================================================================================

		if(currentMap==null)return;

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
		{
			//need to find the area by name
			//get the area index in map

			int index = -1;

			for(int i=0;i<currentMap.getNumAreas();i++)
			{
				Area b = currentMap.getArea(i);

				if(b==a){index = i;break;}

			}

			if(index==-1)return;

			//select the area layer if enabled
			MapCanvas.selectedLayer=MapData.MAP_AREA_LAYER;


			//select action on map and repaint
			currentMap.setSelectedAreaIndex(index);

			EditorMain.mapCanvas.scrollToTop(currentMap.getSelectedArea());

		}

	}
	//===============================================================================================
	private void focusOnEntityInMapCanvas(Entity e)
	{//===============================================================================================

		if(currentMap==null)return;

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
		{
			//need to find the area by name
			//get the area index in map

			int index = -1;

			for(int i=0;i<currentMap.getNumEntities();i++)
			{
				Entity a = currentMap.getEntity(i);

				if(a==e){index = i;break;}

			}

			if(index==-1)return;

			//select the area layer if enabled
			MapCanvas.selectedLayer=MapData.MAP_ENTITY_LAYER;


			//select action on map and repaint
			currentMap.setSelectedEntityIndex(index);

			EditorMain.mapCanvas.scrollToTop(currentMap.getSelectedEntity());

		}
	}










}
