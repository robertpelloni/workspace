package com.bobsgame.editor.MapCanvas;

import java.awt.BorderLayout;


import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;

import java.awt.SystemColor;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Enumeration;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Event.Event;
import com.bobsgame.editor.Project.Event.EventEditor;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.shared.EventData;

//===============================================================================================
public class AreaEditWindow extends JFrame implements  ActionListener, ItemListener, KeyListener, ListSelectionListener, DocumentListener, CaretListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	JPanel warpAreaPanel;

	/*
	public int waitHereTicks = 0; //TODO: handle this in actionWindow: 0 is waypoint, -1 is stop here permanently, positive is ticks.
	public boolean randomTime = false;
	public boolean onlyOneAllowed = false;//will try to get as close to the center as possible, otherwise anywhere is allowed.
	public ArrayList<String> connections = new ArrayList<String>();//TODO: can be doors too! will need to handle renaming.

	public boolean randomNPCStayHere=false;//for cars, audience
	public float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	public boolean randomSpawnKeepTrying = true;//one shot spawn chance for cars, audience

	public boolean randomSpawnOnlyOffscreen = false;
	public boolean randomSpawnExitOnly = false;
	public int randomSpawnDelay = 0;
	public boolean randomSpawnKids = true;
	public boolean randomSpawnAdults = true;
	public boolean randomSpawnMales = true;
	public boolean randomSpawnFemales = true;
	public boolean randomSpawnCars = false;
	*/

	JCheckBox
				warpAreaCheckbox,

				isPointOfInterestForRandomNPCsCheckbox,
				isRandomNPCSpawnPointCheckbox,


				stopHereCheckbox,
				randomWaitTimeCheckbox,
				onlyOneAllowedCheckbox,
				randomNPCStayHereCheckbox,
				randomSpawnOnlyTryOnceCheckbox,
				randomSpawnOnlyOffscreenCheckbox,
				randomSpawnKidsCheckbox,
				randomSpawnAdultsCheckbox,
				randomSpawnMalesCheckbox,
				randomSpawnFemalesCheckbox,
				randomSpawnCarsCheckbox,

				autoPilotCheckbox,
				playerFaceDirectionCheckbox,
				suckPlayerIntoMiddleCheckbox

				;



	JTextField
				nameTextField,
				commentTextField,
				widthTextField,
				heightTextField,


				waitHereTicksTextField,
				randomSpawnChanceTextField,
				randomSpawnDelayTextField

				;



	JComboBox<String> directionCombobox;
	DefaultComboBoxModel<String> directionComboboxModel;


	JList<Area> warpAreaList;
	DefaultListModel<Area> warpAreaListModel;

	JList<Area> areaList;
	DefaultListModel<Area> areaListModel;

	JList<GameObject> connectionsList;
	DefaultListModel<GameObject> connectionsListModel;


	JScrollPane connectionsListScroller;

	JButton
			doneButton,
			cancelButton,
			addOrEditEventButton,
			removeConnectionButton
			;

	JPanel directionPanel;

	EditorMain E;
	int mapX = -1;
	int mapY = -1;
	int width=0;
	int height=0;


	public int editingAreaIndex = -1;

	public Event event = null;

	EventEditor eventEditor = null;

	JPanel centerPanel;

	//===============================================================================================
	public AreaEditWindow(EditorMain e)
	{//===============================================================================================

		super("Area Editor Window");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		E = e;

		eventEditor = new EventEditor(this);


		setLayout(new BorderLayout());


		JPanel everythingPanel = new JPanel(new BorderLayout());
		everythingPanel.setBorder(EditorMain.border);


			JPanel buttonPanel = new JPanel();
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


		everythingPanel.add(buttonPanel,BorderLayout.NORTH);




		//Event When Standing Here: Event Name
		//Require Button Press (Use GameString)
		//Delete Queue When Not Standing Here (Be Careful)



		JPanel npcStuffPanel = new JPanel();
		npcStuffPanel.setBorder(EditorMain.border);
		npcStuffPanel.setLayout(new GridLayout(0,1,0,0));


			JPanel namePanel = new JPanel();
			namePanel.setLayout(new BoxLayout(namePanel,BoxLayout.Y_AXIS));
			JLabel actionNameLabel = new JLabel("Area Name");
			nameTextField = new JTextField("");
			nameTextField.addCaretListener(this);
			nameTextField.addKeyListener(this);
			nameTextField.setForeground(Color.GRAY);
			nameTextField.setColumns(20);
			//nameTextField.getDocument().addDocumentListener(this);
			namePanel.add(actionNameLabel);
			namePanel.add(nameTextField);


		npcStuffPanel.add(namePanel);

			JPanel dimensionsPanel = new JPanel();

			JLabel widthLabel = new JLabel("Width");
			widthTextField = new JTextField("",4);
			dimensionsPanel.add(widthLabel);
			dimensionsPanel.add(widthTextField);

			JLabel heightLabel = new JLabel("Height");
			heightTextField = new JTextField("",4);
			dimensionsPanel.add(heightLabel);
			dimensionsPanel.add(heightTextField);

		npcStuffPanel.add(dimensionsPanel);

			JPanel commentPanel = new JPanel();
			JLabel commentLabel = new JLabel("Comments:");
			commentTextField = new JTextField("");
			commentTextField.setColumns(16);
			commentPanel.add(commentLabel);
			commentPanel.add(commentTextField);

		npcStuffPanel.add(commentPanel);








			directionPanel = new JPanel();
				JLabel directionLabel = new JLabel("NPC Stand/Spawn Direction");
				directionComboboxModel = new DefaultComboBoxModel<String>();
				directionCombobox = new JComboBox<String>(directionComboboxModel);
				directionCombobox.setBackground(EditorMain.comboboxBackgroundColor);
				directionCombobox.addItem("None");
				directionCombobox.addItem("Up");
				directionCombobox.addItem("Down");
				directionCombobox.addItem("Left");
				directionCombobox.addItem("Right");
				directionCombobox.addItemListener(this);
				directionPanel.add(directionLabel);
				directionPanel.add(directionCombobox);
				directionPanel.add(Box.createHorizontalGlue());
			npcStuffPanel.add(directionPanel);

			playerFaceDirectionCheckbox = new JCheckBox("Player Face Direction?");
			playerFaceDirectionCheckbox.addItemListener(this);
			playerFaceDirectionCheckbox.setSelected(false);
			npcStuffPanel.add(playerFaceDirectionCheckbox);

			suckPlayerIntoMiddleCheckbox = new JCheckBox("Suck Player Into Middle?");
			suckPlayerIntoMiddleCheckbox.addItemListener(this);
			suckPlayerIntoMiddleCheckbox.setSelected(false);
			npcStuffPanel.add(suckPlayerIntoMiddleCheckbox);



			stopHereCheckbox = new JCheckBox("Stop Here (Wait -1)");
			stopHereCheckbox.addItemListener(this);
			stopHereCheckbox.setSelected(false);
			npcStuffPanel.add(stopHereCheckbox);


			JPanel waitHerePanel = new JPanel();
				JLabel waitHereTicksLabel = new JLabel("Wait Here For n Ticks");
				waitHereTicksTextField = new JTextField("0",6);
				waitHereTicksTextField.getDocument().addDocumentListener(this);
				waitHerePanel.add(waitHereTicksLabel);
				waitHerePanel.add(waitHereTicksTextField);
				waitHerePanel.add(Box.createHorizontalGlue());
			npcStuffPanel.add(waitHerePanel);


			randomWaitTimeCheckbox = new JCheckBox("Random Wait Up To n Ticks");
			randomWaitTimeCheckbox.addItemListener(this);
			randomWaitTimeCheckbox.setSelected(false);
			npcStuffPanel.add(randomWaitTimeCheckbox);


			onlyOneAllowedCheckbox = new JCheckBox("Only One Allowed?");
			onlyOneAllowedCheckbox.addItemListener(this);
			onlyOneAllowedCheckbox.setSelected(false);
			npcStuffPanel.add(onlyOneAllowedCheckbox);


			autoPilotCheckbox = new JCheckBox("AutoPilot If Press Button? (Follow Path)");
			autoPilotCheckbox.addItemListener(this);
			autoPilotCheckbox.setSelected(false);
			npcStuffPanel.add(autoPilotCheckbox);



			JPanel eventButtonPanel = new JPanel();
			addOrEditEventButton = new JButton("Add New Event");
			addOrEditEventButton.addActionListener(this);
			eventButtonPanel.add(Box.createHorizontalGlue());
			eventButtonPanel.add(addOrEditEventButton);
			eventButtonPanel.add(Box.createHorizontalGlue());


			npcStuffPanel.add(eventButtonPanel);






			//npcStuffPanel.add(new JLabel());

			JPanel randomStuffPanel = new JPanel(new GridLayout(0,1,0,0));
			randomStuffPanel.setBorder(EditorMain.border);
			randomStuffPanel.setBackground(Color.LIGHT_GRAY);

			isPointOfInterestForRandomNPCsCheckbox = new JCheckBox("Point Of Interest For Random NPCs?");
			isPointOfInterestForRandomNPCsCheckbox.addItemListener(this);
			isPointOfInterestForRandomNPCsCheckbox.setSelected(false);
			randomStuffPanel.add(isPointOfInterestForRandomNPCsCheckbox);


			isRandomNPCSpawnPointCheckbox = new JCheckBox("Random NPC Spawn Point?");
			isRandomNPCSpawnPointCheckbox.addItemListener(this);
			isRandomNPCSpawnPointCheckbox.setSelected(false);
			randomStuffPanel.add(isRandomNPCSpawnPointCheckbox);


			JLabel randomSpawnDelayLabel = new JLabel("Random Spawn Ticks Between Attempts");
			randomSpawnDelayTextField = new JTextField("1000",4);
			randomStuffPanel.add(randomSpawnDelayLabel);
			randomStuffPanel.add(randomSpawnDelayTextField);

			JLabel randomSpawnChanceLabel = new JLabel("Random Spawn Chance 0.0f-1.0f");
			randomSpawnChanceTextField = new JTextField("1.0f",3);
			randomStuffPanel.add(randomSpawnChanceLabel);
			randomStuffPanel.add(randomSpawnChanceTextField);

			randomNPCStayHereCheckbox = new JCheckBox("Random Spawn Stay Here (Cars, Audience)");
			randomNPCStayHereCheckbox.addItemListener(this);
			randomNPCStayHereCheckbox.setSelected(false);
			randomStuffPanel.add(randomNPCStayHereCheckbox);

			randomSpawnOnlyTryOnceCheckbox = new JCheckBox("Random Spawn Only Try Once (Cars, Audience)");
			randomSpawnOnlyTryOnceCheckbox.addItemListener(this);
			randomSpawnOnlyTryOnceCheckbox.setSelected(false);
			randomStuffPanel.add(randomSpawnOnlyTryOnceCheckbox);

			randomSpawnOnlyOffscreenCheckbox = new JCheckBox("Random Spawn Only Offscreen");
			randomSpawnOnlyOffscreenCheckbox.addItemListener(this);
			randomSpawnOnlyOffscreenCheckbox.setSelected(false);
			randomStuffPanel.add(randomSpawnOnlyOffscreenCheckbox);


			randomSpawnKidsCheckbox = new JCheckBox("Random Spawn Kids");
			randomSpawnKidsCheckbox.addItemListener(this);
			randomSpawnKidsCheckbox.setSelected(true);
			randomStuffPanel.add(randomSpawnKidsCheckbox);

			randomSpawnAdultsCheckbox = new JCheckBox("Random Spawn Adults");
			randomSpawnAdultsCheckbox.addItemListener(this);
			randomSpawnAdultsCheckbox.setSelected(true);
			randomStuffPanel.add(randomSpawnAdultsCheckbox);

			randomSpawnMalesCheckbox = new JCheckBox("Random Spawn Males");
			randomSpawnMalesCheckbox.addItemListener(this);
			randomSpawnMalesCheckbox.setSelected(true);
			randomStuffPanel.add(randomSpawnMalesCheckbox);

			randomSpawnFemalesCheckbox = new JCheckBox("Random Spawn Females");
			randomSpawnFemalesCheckbox.addItemListener(this);
			randomSpawnFemalesCheckbox.setSelected(true);
			randomStuffPanel.add(randomSpawnFemalesCheckbox);

			randomSpawnCarsCheckbox = new JCheckBox("Random Spawn Cars");
			randomSpawnCarsCheckbox.addItemListener(this);
			randomSpawnCarsCheckbox.setSelected(false);
			randomStuffPanel.add(randomSpawnCarsCheckbox);



		JPanel npcRandomPanel = new JPanel();
		npcRandomPanel.setBorder(EditorMain.border);
		npcRandomPanel.setLayout(new BoxLayout(npcRandomPanel,BoxLayout.X_AXIS));
		npcRandomPanel.add(npcStuffPanel);
		npcRandomPanel.add(randomStuffPanel);



		everythingPanel.add(npcRandomPanel, BorderLayout.CENTER);






		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);

		warpAreaPanel = new JPanel();
		warpAreaPanel.setBorder(EditorMain.border);
		warpAreaPanel.setLayout(new BoxLayout(warpAreaPanel, BoxLayout.Y_AXIS));
		warpAreaPanel.setBackground(Color.LIGHT_GRAY);

			JPanel warpAreaCheckboxPanel = new JPanel();
				warpAreaCheckbox = new JCheckBox("Is WarpArea?");
				warpAreaCheckbox.addItemListener(this);
				warpAreaCheckbox.setSelected(false);
				JLabel warpAreaListLabel = new JLabel("Where does WarpArea go?");
			warpAreaCheckboxPanel.add(warpAreaCheckbox);
			warpAreaCheckboxPanel.add(warpAreaListLabel);

			warpAreaListModel = new DefaultListModel<Area>();
				warpAreaList = new JList<Area>(warpAreaListModel);
				warpAreaList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
				warpAreaList.setLayoutOrientation(JList.VERTICAL);
				warpAreaList.setVisibleRowCount(24);
				warpAreaList.setForeground(Color.BLACK);
				warpAreaList.setFont(listFont);
				warpAreaList.setFixedCellHeight(16);
				warpAreaList.setCellRenderer(new WarpAreaListLongTypeNameCellRenderer());
				//warpAreaList.addListSelectionListener(this);
			JScrollPane warpAreaListScroller = new JScrollPane(warpAreaList);

			warpAreaListScroller.setSize(new Dimension(380,400));
			warpAreaListScroller.setPreferredSize(new Dimension(380,400));
			warpAreaListScroller.setMaximumSize(new Dimension(380,400));
			warpAreaListScroller.setMinimumSize(new Dimension(380,100));

		warpAreaPanel.add(Box.createRigidArea(new Dimension(380,0)));
		warpAreaPanel.add(warpAreaCheckboxPanel);
		warpAreaPanel.add(warpAreaListScroller);


		JPanel connectionsPanel = new JPanel();
		connectionsPanel.setBorder(EditorMain.border);
		connectionsPanel.setLayout(new BoxLayout(connectionsPanel,BoxLayout.Y_AXIS));

			connectionsListModel = new DefaultListModel<GameObject>();
				connectionsList = new JList<GameObject>(connectionsListModel);
				connectionsList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
				connectionsList.setLayoutOrientation(JList.VERTICAL);
				connectionsList.setVisibleRowCount(24);
				connectionsList.setForeground(Color.BLACK);
				connectionsList.setFont(listFont);
				connectionsList.setFixedCellHeight(16);
				connectionsList.setCellRenderer(new AreaConnectionsListShortTypeNameCellRenderer());
				//connectionsList.addListSelectionListener(this);
			connectionsListScroller = new JScrollPane(connectionsList);

			JPanel removeConnectionsButtonPanel = new JPanel();
			removeConnectionButton = new JButton("Remove Selected Connection");
			removeConnectionButton.addActionListener(this);
			removeConnectionsButtonPanel.add(new JLabel("Assigned Connections"));
			removeConnectionsButtonPanel.add(removeConnectionButton);

		connectionsPanel.add(Box.createRigidArea(new Dimension(380,0)));
		connectionsPanel.add(removeConnectionsButtonPanel);
		connectionsPanel.add(connectionsListScroller);



		JPanel listsPanel = new JPanel(new BorderLayout());
		listsPanel.setBorder(EditorMain.border);
		listsPanel.add(warpAreaPanel, BorderLayout.WEST);
		listsPanel.add(connectionsPanel, BorderLayout.EAST);

		listsPanel.setSize(new Dimension(800,200));
		listsPanel.setPreferredSize(new Dimension(800,200));
		listsPanel.setMaximumSize(new Dimension(800,600));
		listsPanel.setMinimumSize(new Dimension(800,200));

		everythingPanel.add(listsPanel, BorderLayout.EAST);





		areaListModel = new DefaultListModel<Area>();
		areaList = new JList<Area>(areaListModel);
		areaList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		areaList.setLayoutOrientation(JList.VERTICAL);
		areaList.setVisibleRowCount(30);
		areaList.setForeground(Color.BLACK);
		areaList.setFont(listFont);
		areaList.setFixedCellHeight(16);
		areaList.addListSelectionListener(this);
		areaList.setFocusable(false);

		areaList.setCellRenderer(new AreaListNameCellRenderer());
		JScrollPane areaListScroller = new JScrollPane(areaList);

		areaListScroller.setBorder(EditorMain.border);
		areaListScroller.setFocusable(false);


		JPanel areaListPanel = new JPanel();
		areaListPanel.setLayout(new BoxLayout(areaListPanel,BoxLayout.Y_AXIS));
		areaListPanel.add(Box.createRigidArea(new Dimension(100,0)));
		areaListPanel.add(areaListScroller);


		//areaList.setMaximumSize(new Dimension(300,1000));
		areaListScroller.setPreferredSize(new Dimension(250,1));
		//areaListScroller.setMaximumSize(new Dimension(300,0));
		//areaListPanel.setMaximumSize(new Dimension(300,0));



		//JPanel eventPanel = new JPanel();
		//eventPanel.setSize(new Dimension(1800,600));
		//eventPanel.setPreferredSize(new Dimension(1800,600));
		//eventPanel.setMaximumSize(new Dimension(1800,600));
		//eventPanel.setMinimumSize(new Dimension(1800,600));

		//eventPanel.add(eventEditor);



		centerPanel = new JPanel(new BorderLayout());
		centerPanel.setBorder(EditorMain.border);
		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(eventEditor,BorderLayout.CENTER);




		add(areaListPanel,BorderLayout.WEST);
		add(centerPanel,BorderLayout.CENTER);





		setSize(EditorMain.getScreenWidth() - 460, 770);
		setLocation(20, 800);

		setFocusable(true);
		addKeyListener(this);
		recursivelyAddKeyListener(centerPanel);




	}
	//===============================================================================================
	public void recursivelyAddKeyListener(Container container)
	{//===============================================================================================
		Component[] c = container.getComponents();
		for(int i=0;i<c.length;i++)
		{




			c[i].removeKeyListener(this);


			if(
					c[i].getClass()!=JScrollPane.class
					&&c[i].getClass()!=JList.class
			)
			{

				c[i].setFocusable(true);

				c[i].addKeyListener(this);

				if(c[i].getClass().equals(JPanel.class))
				{
					recursivelyAddKeyListener((Container) c[i]);
				}
			}
			else
			{
				c[i].setFocusable(false);
			}

		}

	}



	//===============================================================================================
	public Map getMap()
	{//===============================================================================================
		return Project.getSelectedMap();

	}



	//===============================================================================================
	public void showAreaWindow(int x, int y, int w, int h)
	{//===============================================================================================
		mapX = x;
		mapY = y;
		width = w;
		height = h;


		//make new area

		Area a = new Area(getMap(),getMap().getSelectedState());

		a.setNameNoRename("Area"+(getMap().getNumAreas()));

		getMap().addArea(a);

		a.setXPixels(x);
		a.setYPixels(y);
		a.setWidthPixels(w);
		a.setHeightPixels(h);


		getMap().setSelectedAreaIndex(getMap().getNumAreas()-1);

		editingAreaIndex = getMap().getSelectedAreaIndex();


		nameTextField.setText(a.name());
		commentTextField.setText("");
		widthTextField.setText(""+width);
		heightTextField.setText(""+height);




		populateWarpAreaList();


		warpAreaList.setEnabled(false);
		warpAreaCheckbox.setSelected(false);




		addOrEditEventButton.setVisible(true);

		closeEventEditor();
		event=null;



		isPointOfInterestForRandomNPCsCheckbox.setSelected(false);
		isRandomNPCSpawnPointCheckbox.setSelected(false);
		disableRandomFields();



		directionCombobox.setSelectedIndex(0);



		randomWaitTimeCheckbox.setSelected(false);
		onlyOneAllowedCheckbox.setSelected(false);
		randomNPCStayHereCheckbox.setSelected(false);
		randomSpawnOnlyTryOnceCheckbox.setSelected(false);
		randomSpawnOnlyOffscreenCheckbox.setSelected(false);
		randomSpawnKidsCheckbox.setSelected(true);
		randomSpawnAdultsCheckbox.setSelected(true);
		randomSpawnMalesCheckbox.setSelected(true);
		randomSpawnFemalesCheckbox.setSelected(true);
		randomSpawnCarsCheckbox.setSelected(false);

		autoPilotCheckbox.setSelected(false);
		playerFaceDirectionCheckbox.setSelected(false);
		suckPlayerIntoMiddleCheckbox.setSelected(false);

		waitHereTicksTextField.setText(""+0);
		stopHereCheckbox.setSelected(false);

		randomSpawnChanceTextField.setText(""+1.0f);
		randomSpawnDelayTextField.setText(""+1000);

		connectionsListModel.removeAllElements();





		areaListModel.removeAllElements();
		for(int i=0;i<getMap().getNumAreas();i++)
		{
			areaListModel.addElement(getMap().getArea(i));
		}


		areaList.setSelectedIndex(editingAreaIndex);

		nameTextField.setForeground(Color.GRAY);

		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}
	}

	//===============================================================================================
	public void showAreaWindow()
	{//===============================================================================================

		editingAreaIndex = getMap().getSelectedAreaIndex();



		areaListModel.removeAllElements();
		for(int i=0;i<getMap().getNumAreas();i++)
		{
			areaListModel.addElement(getMap().getArea(i));
		}
		areaList.setSelectedIndex(editingAreaIndex);


		updateFieldsFromArea();

		populateLists();

		nameTextField.setForeground(Color.GRAY);

		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}

	}

	//===============================================================================================
	public void updateFieldsFromArea()
	{//===============================================================================================

		//this is called when we select the areaList.
		//dont set the fields if we are making a new action, they were already set when we opened the window.


		//System.out.println("updateFieldsFromArea()");



		Area area = getMap().getArea(editingAreaIndex);

		//fill in action name from selected action
		nameTextField.setText(area.name());

		mapX = area.xP();
		mapY = area.yP();

		width = area.wP();
		height = area.hP();


		widthTextField.setText(""+width);
		heightTextField.setText(""+height);


		commentTextField.setText(area.comment());





		populateWarpAreaList();






		if(area.isWarpArea()==true)
		{
			warpAreaCheckbox.setSelected(true);
			warpAreaList.setEnabled(true);


			//set the selected warp area to this destination.

			Enumeration<Area> e = warpAreaListModel.elements();

			for(int i=0; e.hasMoreElements(); i++)
			{
				Area temp = (Area) e.nextElement();
				if(temp==area.destinationArea())
				{
					warpAreaList.setSelectedIndex(i);
					warpAreaList.ensureIndexIsVisible(i);
				}
			}

		}
		else
		{
			warpAreaCheckbox.setSelected(false);
			warpAreaList.setEnabled(false);
		}

		directionCombobox.setSelectedIndex(area.standSpawnDirection()+1);


		isPointOfInterestForRandomNPCsCheckbox.setSelected(area.randomPointOfInterestOrExit());
		isRandomNPCSpawnPointCheckbox.setSelected(area.randomNPCSpawnPoint());
		if(area.randomNPCSpawnPoint()==true)enableRandomFields();
		else disableRandomFields();


		randomWaitTimeCheckbox.setSelected(area.randomWaitTime());
		onlyOneAllowedCheckbox.setSelected(area.onlyOneAllowed());
		randomNPCStayHereCheckbox.setSelected(area.randomNPCStayHere());
		randomSpawnOnlyTryOnceCheckbox.setSelected(area.randomSpawnOnlyTryOnce());
		randomSpawnOnlyOffscreenCheckbox.setSelected(area.randomSpawnOnlyOffscreen());
		randomSpawnKidsCheckbox.setSelected(area.randomSpawnKids());
		randomSpawnAdultsCheckbox.setSelected(area.randomSpawnAdults());
		randomSpawnMalesCheckbox.setSelected(area.randomSpawnMales());
		randomSpawnFemalesCheckbox.setSelected(area.randomSpawnFemales());
		randomSpawnCarsCheckbox.setSelected(area.randomSpawnCars());

		autoPilotCheckbox.setSelected(area.autoPilot());
		playerFaceDirectionCheckbox.setSelected(area.playerFaceDirection());
		suckPlayerIntoMiddleCheckbox.setSelected(area.suckPlayerIntoMiddle());

		waitHereTicksTextField.setText(""+area.waitHereTicks());
		if(area.waitHereTicks()==-1)stopHereCheckbox.setSelected(true);
		else stopHereCheckbox.setSelected(false);

		randomSpawnChanceTextField.setText(""+area.randomSpawnChance());
		randomSpawnDelayTextField.setText(""+area.randomSpawnDelay());






		if(area.eventData()!=null)
		{
			event = Project.getEventByID(area.eventData().id());

			if(event!=null)
			{
				if(event.name().length()==0)event.setName(Project.getSelectedMap().name()+"."+area.name()+".Event");
				eventEditor.editEvent(Project.getSelectedMap(),event);
				openEventEditor();
			}
		}
		else
		{
			closeEventEditor();
			event=null;
		}


	}

	//===============================================================================================
	public void updateAreaFromFields()
	{//===============================================================================================


		//System.out.println("updateAreaFromFields()");


		Area area = getMap().getArea(editingAreaIndex);

		String newName = nameTextField.getText();
		newName = getMap().createUniqueAreaName(newName, editingAreaIndex);

		//if this action already has a name, we opened an existing action and changed the name
		if(area.name()!=null)
		{

			if(area.name().equals(newName)==false)
			{
				area.setName(newName);
			}
		}
		else
		{
			//this action doesn't have a name, so there is nothing to rename.
			area.setNameNoRename(newName);

		}



		width = Integer.parseInt(widthTextField.getText());
		height = Integer.parseInt(heightTextField.getText());


		area.setXPixels(mapX);
		area.setYPixels(mapY);
		area.setWidthPixels(width);
		area.setHeightPixels(height);
		area.setIsWarpArea(warpAreaCheckbox.isSelected());
		area.setComment(commentTextField.getText());

		if(warpAreaCheckbox.isSelected())//if(warpAreaList.isEnabled())
		{
			if(warpAreaList.getSelectedValue()!=null)
			{
				if(warpAreaList.getSelectedValue()!=area)
				{
					//String warpAreaString = warpAreaList.getSelectedValue().toString();

					//Map tempMap = Project.getMapByName(warpAreaString.substring(0,warpAreaString.indexOf(".")));
					//Area tempArea = tempMap.getAreaByName(warpAreaString.substring(warpAreaString.indexOf(".")+1));


					area.setDestinationTYPEIDString(warpAreaList.getSelectedValue().getTYPEIDString());
					//area.destination=tempArea;
				}
				else
				{
					area.setDestinationTYPEIDString(area.getTYPEIDString());
				}
			}

		}


		area.setStandSpawnDirection(directionCombobox.getSelectedIndex()-1);

		area.setWaitHereTicks(Integer.parseInt(waitHereTicksTextField.getText()));

		area.setRandomPointOfInterestOrExit(isPointOfInterestForRandomNPCsCheckbox.isSelected());
		area.setRandomNPCSpawnPoint(isRandomNPCSpawnPointCheckbox.isSelected());
		area.setRandomWaitTime(randomWaitTimeCheckbox.isSelected());
		area.setOnlyOneAllowed(onlyOneAllowedCheckbox.isSelected());
		area.setRandomNPCStayHere(randomNPCStayHereCheckbox.isSelected());
		area.setRandomSpawnChance(Float.parseFloat(randomSpawnChanceTextField.getText()));
		area.setRandomSpawnDelay(Integer.parseInt(randomSpawnDelayTextField.getText()));
		area.setRandomSpawnOnlyTryOnce(randomSpawnOnlyTryOnceCheckbox.isSelected());
		area.setRandomSpawnOnlyOffscreen(randomSpawnOnlyOffscreenCheckbox.isSelected());
		area.setRandomSpawnKids(randomSpawnKidsCheckbox.isSelected());
		area.setRandomSpawnAdults(randomSpawnAdultsCheckbox.isSelected());
		area.setRandomSpawnMales(randomSpawnMalesCheckbox.isSelected());
		area.setRandomSpawnFemales(randomSpawnFemalesCheckbox.isSelected());
		area.setRandomSpawnCars(randomSpawnCarsCheckbox.isSelected());

		area.setAutoPilot(autoPilotCheckbox.isSelected());
		area.setPlayerFaceDirection(playerFaceDirectionCheckbox.isSelected());
		area.setSuckPlayerIntoMiddle(suckPlayerIntoMiddleCheckbox.isSelected());


		area.connectionTYPEIDList().clear();
		for(int i=0;i<connectionsListModel.getSize();i++)
		{
			area.connectionTYPEIDList().add(connectionsListModel.get(i).getTYPEIDString());
		}



		if(event!=null)
		{
			if(area.eventData().id()!=event.id())area.setEventData(event.getData());

			eventEditor.storeEventTreeInString();

			closeEventEditor();
			event = null;
		}


		//remove this area from the top of the warpAreaList, since it might not even be a warp area.
		//it is always put at the top in updateFieldsFromArea() and selected by default as "self" for areas that aren't warp areas (have no destination)
		//warpAreaListModel.removeElement(area);


	}
	//===============================================================================================
	public void populateWarpAreaList()
	{//===============================================================================================

		Area area = getMap().getArea(editingAreaIndex);

		warpAreaListModel.removeAllElements();

		//warpAreaListModel.removeElement(area);//remove this area if it exists in the list.


		if(warpAreaListModel.size()==0)//if we have never populated the warp area list, do it now (very slow) //not slow anymore!
		{
			int numAreas = Project.areaIndexList.size();
			for(int n=0;n<numAreas;n++)
			{
				Area temp = Project.areaIndexList.get(n);
				if(temp.isWarpArea()==true)
				if(temp!=area)
				warpAreaListModel.addElement(temp);
			}
		}

		warpAreaListModel.add(0,area);//add this area back to the top

		warpAreaList.setSelectedIndex(0);//select the top
	}
	//===============================================================================================
	public void populateLists()
	{//===============================================================================================

		//System.out.println("populateLists()");

		Area area = getMap().getArea(editingAreaIndex);

		connectionsListModel.removeAllElements();
		for(int i=0;i<area.connectionTYPEIDList().size();i++)
		{
			connectionsListModel.addElement(Project.getMapObjectByTYPEIDName(area.connectionTYPEIDList().get(i)));
		}
	}


	//===============================================================================================
	public void openEventEditor()
	{//===============================================================================================
		addOrEditEventButton.setVisible(false);
		centerPanel.add(eventEditor);




		setSize(EditorMain.getScreenWidth() - 460, 970);
		setLocation(20, 600);

		validate();
	}
	//===============================================================================================
	public void closeEventEditor()
	{//===============================================================================================
		addOrEditEventButton.setVisible(true);
		centerPanel.remove(eventEditor);




		validate();

	}

	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		Area area = getMap().getArea(editingAreaIndex);

		if(ae.getSource() == doneButton)
		{

			updateAreaFromFields();

			editingAreaIndex=-1;

			setVisible(false);

			//this only needs to repaint the canvas because the actions are drawn at full resolution after the map.
			EditorMain.mapCanvas.repaint();



		}
		else if(ae.getSource() == cancelButton)
		{

			//remove this area from the top of the warpAreaList, since it might not even be a warp area.
			//it is always put at the top in updateFieldsFromArea() and selected by default as "self" for areas that aren't warp areas (have no destination)
			warpAreaListModel.removeElement(area);
			setVisible(false);
		}

		if(ae.getSource() == addOrEditEventButton)
		{

			if(event==null)
			{
				event = new Event(EventData.TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING,Project.getSelectedMap().name()+"."+area.name(),"",Area.DEFAULT_AREA_EVENT_STRING);
				area.setEventData(event.getData());
				eventEditor.editEvent(Project.getSelectedMap(),event);




				openEventEditor();

			}


		}


		if(ae.getSource() == removeConnectionButton)
		{
			if(connectionsList.getSelectedIndex()>=0)
			{
				connectionsListModel.remove(connectionsList.getSelectedIndex());
			}
		}
	}
	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================



		if(ie.getSource()==warpAreaCheckbox)
		{

			Area area = getMap().getArea(editingAreaIndex);

			if(warpAreaCheckbox.isSelected()==true)
			{
				//set doorlist enabled
				warpAreaList.setEnabled(true);
				if(getMap().getArea(editingAreaIndex).arrivalXPixels()==-1)getMap().getArea(editingAreaIndex).setArrivalXPixels(mapX+width);
				if(getMap().getArea(editingAreaIndex).arrivalYPixels()==-1)getMap().getArea(editingAreaIndex).setArrivalYPixels(mapY+height);

				if(area.eventData()==null)
				{
					if(event==null)
					{
						area.createDefaultWarpAreaEvent();

						event = Project.getEventByID(area.eventData().id());
					}

				}
			}
			else
			{

				warpAreaList.setEnabled(false);
				getMap().getArea(editingAreaIndex).setDestinationTYPEIDString(getMap().getArea(editingAreaIndex).getTYPEIDString());

			}

		}


		if(ie.getSource() == stopHereCheckbox)
		{
			if(stopHereCheckbox.isSelected()==true)waitHereTicksTextField.setText("-1");
			else if(waitHereTicksTextField.getText().equals("-1"))waitHereTicksTextField.setText("0");
		}

		if(ie.getSource() == isRandomNPCSpawnPointCheckbox)
		{
			if(isRandomNPCSpawnPointCheckbox.isSelected()==true)
			{
				enableRandomFields();
				//isPointOfInterestForRandomNPCsCheckbox.setSelected(true);
				//should be an exit by default
				//this is too confusing
			}
			else disableRandomFields();
		}


		if(ie.getSource() == directionCombobox)
		{

			if(directionCombobox.getSelectedIndex()==0)directionPanel.setBackground(SystemColor.menu);
			else directionPanel.setBackground(new Color(150,225,150));

		}

		if(ie.getSource().getClass().equals(JCheckBox.class))
		{
			if(((JCheckBox)ie.getSource()).isSelected()==true)((JCheckBox)ie.getSource()).setBackground(new Color(150,225,150));
			else ((JCheckBox)ie.getSource()).setBackground(Color.LIGHT_GRAY);
		}


	}

	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================



		if(e.getSource() == areaList)
		{

			//System.out.println("valueChanged() editingAreaIndex:"+editingAreaIndex+" areaList.getSelectedIndex():"+areaList.getSelectedIndex());

			if(e.getValueIsAdjusting()==true)return;

			if(areaList.getSelectedIndex()==editingAreaIndex)return;

			if(areaList.getSelectedIndex()==-1)return;



				//save current action to vars
				updateAreaFromFields();

				editingAreaIndex = areaList.getSelectedIndex();

				areaList.ensureIndexIsVisible(areaList.getSelectedIndex());




				//update fields from selected action
				updateFieldsFromArea();



				populateLists();

				//select action on map and repaint
				getMap().setSelectedAreaIndex(editingAreaIndex);

				EditorMain.mapCanvas.scrollToTop(getMap().getSelectedArea());


				nameTextField.setForeground(Color.GRAY);


		}

	}

	//===============================================================================================
	public void disableRandomFields()
	{//===============================================================================================
		randomSpawnDelayTextField.setEnabled(false);
		randomSpawnChanceTextField.setEnabled(false);
		randomNPCStayHereCheckbox.setEnabled(false);
		randomSpawnOnlyTryOnceCheckbox.setEnabled(false);
		randomSpawnOnlyOffscreenCheckbox.setEnabled(false);

		randomSpawnKidsCheckbox.setEnabled(false);
		randomSpawnAdultsCheckbox.setEnabled(false);
		randomSpawnMalesCheckbox.setEnabled(false);
		randomSpawnFemalesCheckbox.setEnabled(false);
		randomSpawnCarsCheckbox.setEnabled(false);

		isPointOfInterestForRandomNPCsCheckbox.setText("Point Of Interest For Random NPCs?");


	}


	//===============================================================================================
	public void enableRandomFields()
	{//===============================================================================================

		randomSpawnDelayTextField.setEnabled(true);
		randomSpawnChanceTextField.setEnabled(true);
		randomNPCStayHereCheckbox.setEnabled(true);
		randomSpawnOnlyTryOnceCheckbox.setEnabled(true);
		randomSpawnOnlyOffscreenCheckbox.setEnabled(true);

		randomSpawnKidsCheckbox.setEnabled(true);
		randomSpawnAdultsCheckbox.setEnabled(true);
		randomSpawnMalesCheckbox.setEnabled(true);
		randomSpawnFemalesCheckbox.setEnabled(true);
		randomSpawnCarsCheckbox.setEnabled(true);

		isPointOfInterestForRandomNPCsCheckbox.setText("Exit (Point Of Interest if wait/stay) For Random NPCs?");

	}


	//===============================================================================================
	public void keyTyped(KeyEvent e)
	{//===============================================================================================
		// TODO Auto-generated method stub

	}



	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================


		if(ke.getSource() == nameTextField && ke.getKeyCode() == KeyEvent.VK_ENTER)
		{

			nameTextField.setForeground(Color.GRAY);

			//System.out.println("nameText changedUpdate()");


			if(nameTextField.getText().length()==0)return;

			Area area = getMap().getArea(editingAreaIndex);
			//get var name
			String oldName = area.name();

			//find var name in name list
			int selectedItem = -1;




			Enumeration<Area> enm = areaListModel.elements();

			for(int i=0; enm.hasMoreElements(); i++)
			{
				Area temp = (Area) enm.nextElement();
				if(temp.name().equals(oldName))
				{
					selectedItem = i;
					break;
				}
			}


//			Object[] listNames = areaListModel.toArray();
//
//			for(int i=0;i<listNames.length;i++)
//			{
//				if(listNames[i].toString().equals(oldName))
//				{
//					selectedItem = i;
//					break;
//				}
//			}


			if(selectedItem!=-1)
			{

				//System.out.println("found it, setting the name.");

				String name = nameTextField.getText();
				name = getMap().createUniqueAreaName(name, editingAreaIndex);


				area.setName(name);

				//this gets done when we set the index in areaList anyway
				//if(nameTextField.getText().equals(name)==false)nameTextField.setText(name);


				//update name to textFieldName
				areaListModel.add(selectedItem, area);
				areaListModel.remove(selectedItem+1);
				areaList.setSelectedIndex(selectedItem);

				validate();
			}

			return;
		}



		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			actionPerformed(new ActionEvent(doneButton,ActionEvent.ACTION_PERFORMED,""));
		}

		if(ke.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{
			if(areaList.getSelectedIndex()>0)areaList.setSelectedIndex(areaList.getSelectedIndex()-1);
			valueChanged(new ListSelectionEvent(areaList,0,areaListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(areaList,ItemEvent.ITEM_STATE_CHANGED,areaList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}


		if(ke.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{
			if(areaList.getSelectedIndex()>=0&&areaList.getSelectedIndex()<areaListModel.size()-1)areaList.setSelectedIndex(areaList.getSelectedIndex()+1);
			valueChanged(new ListSelectionEvent(areaList,0,areaListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(areaList,ItemEvent.ITEM_STATE_CHANGED,areaList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}

	}


	//===============================================================================================
	public void keyReleased(KeyEvent e)
	{//===============================================================================================
		// TODO Auto-generated method stub

	}


	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================

		if(e.getSource()==nameTextField)
		{
			nameTextField.setForeground(Color.RED);
		}

	}


	//===============================================================================================
	@Override
	public void changedUpdate(DocumentEvent e)
	{//===============================================================================================




	}

	//===============================================================================================
	@Override
	public void insertUpdate(DocumentEvent e)
	{//===============================================================================================
		changedUpdate(e);
	}

	//===============================================================================================
	@Override
	public void removeUpdate(DocumentEvent e)
	{//===============================================================================================
		changedUpdate(e);
	}


	//===============================================================================================
	class AreaListNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public AreaListNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

			if(value!=null)
			{

				setToolTipText("");

				Area a = ((Area)value);
				Area editingArea = Project.getSelectedMap().getArea(editingAreaIndex);


				if(a.isWarpArea())
				{
					setForeground(Color.BLUE);
					setToolTipText("Is WarpArea");

					if(a.destinationTYPEIDString() == a.getTYPEIDString()){setForeground(new Color(255,127,127));setToolTipText("Is Warp Area and Destination is self!");}
					if(a.eventData()!=null && Project.getEventByID(a.eventData().id()).text().contains("enterThisWarp")==false){setForeground(Color.ORANGE);setToolTipText("Event does not contain enterThisWarp");}

					if(a.eventData()==null){setForeground(Color.RED);setToolTipText("Is Warp Area and Has no Event. eventID == -1");}
				}
				else
				{
					if(a.eventData()!=null){setForeground(Color.GREEN);setToolTipText("Is Area and Has Event.");}
				}


				setText(a.name());
			}
			else setText("null");

			return this;
		}
	}

	//===============================================================================================
	class AreaConnectionsListShortTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public AreaConnectionsListShortTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

			if(value!=null)
			{
				setToolTipText("");

				Area a = ((Area)value);
				Area editingArea = Project.getSelectedMap().getArea(editingAreaIndex);


				if(a.isWarpArea())
				{
					setForeground(Color.BLUE);
					setToolTipText("Is WarpArea");

					if(a.destinationTYPEIDString() == a.getTYPEIDString()){setForeground(new Color(255,127,127));setToolTipText("Is Warp Area and Destination is self!");}

					if(a.eventData()==null){setForeground(Color.RED);setToolTipText("Is Warp Area and Has no Event. eventID == -1");}
				}



				setText(a.getShortTypeName());
			}
			else setText("null");



			return this;
		}
	}

	//===============================================================================================
	class WarpAreaListLongTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public WarpAreaListLongTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

			if(value!=null)
			{
				setToolTipText("");

				Area a = ((Area)value);
				Area editingArea = Project.getSelectedMap().getArea(editingAreaIndex);


				if(a.map()==editingArea.map()){setForeground(Color.LIGHT_GRAY);setToolTipText("Warp Area is on this map.");}
				if(a==editingArea){setForeground(Color.BLUE);setToolTipText("Warp Area is the one you are editing.");}
				if(a.destinationTYPEIDString() == a.getTYPEIDString()){setForeground(new Color(255,127,127));setToolTipText("Is Warp Area and Destination is self!");}
				if(a.eventData()==null){setForeground(Color.RED);setToolTipText("Warp Area has no Event. eventID == -1");}

				setText(a.getLongTypeName());
			}
			else setText("null");


			return this;
		}

	}


}
