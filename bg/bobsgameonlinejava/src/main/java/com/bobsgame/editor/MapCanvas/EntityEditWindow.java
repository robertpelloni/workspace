package com.bobsgame.editor.MapCanvas;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.util.Enumeration;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.Timer;
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
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.editor.Project.Sprite.Sprite;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.MapData.RenderOrder;

//===============================================================================================
public class EntityEditWindow extends JFrame implements ActionListener, ItemListener, ImageObserver, KeyListener, ListSelectionListener, DocumentListener, CaretListener
{//===============================================================================================

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	JButton doneButton, cancelButton;
	EditorMain E;



	JTextField
			entityNameTextField,
			spriteNameTextField,
			spriteDisplayNameTextField,
			commentTextField,
			ticksBetweenFramesTextField,
			ticksBetweenAnimationTextField,
			ticksPerPixelTextField,
			initialFrameTextField,
			scaleTextField

			;


	JCheckBox
			isNPCCheckbox,
			animateThroughFramesCheckbox,
			pushableCheckbox,
			nonWalkableCheckbox,
			transparentCheckbox,
			//aboveTopLayerCheckbox,
			aboveWhenEqualCheckbox,
			alwaysOnBottomCheckbox,
			randomTicksBetweenFramesCheckbox,
			randomTimeBetweenAnimationCheckbox,
			onlyHereDuringEventCheckbox,
			randomFramesCheckbox,
			disableShadowCheckbox


			;



	JList<Entity> entityList;
	DefaultListModel<Entity> entityListModel;

	JList<String> assignedBehaviorList;
	DefaultListModel<String> assignedBehaviorListModel;

	JList<String> selectableBehaviorList;
	DefaultListModel<String> selectableBehaviorListModel;




	JList<GameObject> assignedConnectionList;
	DefaultListModel<GameObject> assignedConnectionListModel;

	JList<GameObject> selectableConnectionList;
	DefaultListModel<GameObject> selectableConnectionListModel;



	JButton
			addSelectedConnectionButton,
			removeSelectedConnectionButton,
			addSelectedBehaviorButton,
			removeSelectedBehaviorButton,
			addOrEditEventButton
			;



	JPanel
			listsPanel,
			behaviorListsPanel,
			assignedBehaviorPanel,
			selectableBehaviorPanel,
			connectionListsPanel,
			assignedConnectionPanel,
			selectableConnectionPanel
			;


	JPanel centerPanel;



	//JComboBox<String> walkSpeedCombobox;
	//DefaultComboBoxModel<String> walkSpeedComboboxModel;

	JComboBox<String> renderOrderCombobox;
	DefaultComboBoxModel<String> renderOrderComboboxModel;

	JScrollPane assignedBehaviorListScroller;
	JScrollPane selectableBehaviorListScroller;
	JScrollPane assignedConnectionListScroller;
	JScrollPane selectableConnectionListScroller;



	//action list
	//if sprite in range walk to point look at sprite
	//if sprite in range look at sprite
	//walk to points in order
	//walk to points randomly
	//stand face direction
	//shuffle feet
	//look at sprite
	//has dialogue

	//points to walk to list
	//make list, populate with all areas on the map marked with "ofInterestToNPCs"






	//dialogue list with comments
	//"add new dialogue"




	Timer frameTimer, animateTimer;

	public int currentFrame=0;

	JComponent animationCanvas;

	public int editingEntityIndex=-1;

	EventEditor eventEditor = null;

	public Event event = null;

	//===============================================================================================
	public EntityEditWindow(EditorMain e)
	{//===============================================================================================
		super("Entity Edit Window");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		E = e;


		setLayout(new BorderLayout());


		eventEditor = new EventEditor(this);
		frameTimer = new Timer(100,this);
		animateTimer = new Timer(100,this);



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














		listsPanel = new JPanel();
		listsPanel.setBorder(EditorMain.border);
		listsPanel.setLayout(new BoxLayout(listsPanel, BoxLayout.Y_AXIS));

			behaviorListsPanel = new JPanel(new BorderLayout());
			behaviorListsPanel.setBorder(EditorMain.border);

				assignedBehaviorPanel = new JPanel();
				assignedBehaviorPanel.setLayout(new BoxLayout(assignedBehaviorPanel, BoxLayout.Y_AXIS));
				JLabel assignedBehaviorLabel = new JLabel("Assigned Behaviors");
				assignedBehaviorPanel.add(assignedBehaviorLabel);
				Font listFont = new Font("Lucida Console", Font.PLAIN, 12);
					assignedBehaviorListModel = new DefaultListModel<String>();
					assignedBehaviorList = new JList<String>(assignedBehaviorListModel); //data has type Object
					assignedBehaviorList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
					assignedBehaviorList.setLayoutOrientation(JList.VERTICAL);
					assignedBehaviorList.setVisibleRowCount(10);
					assignedBehaviorList.setForeground(Color.BLACK);
					assignedBehaviorList.setFont(listFont);
					assignedBehaviorList.setFixedCellHeight(16);
					assignedBehaviorList.addListSelectionListener(this);
					assignedBehaviorListScroller = new JScrollPane(assignedBehaviorList);
				assignedBehaviorPanel.add(assignedBehaviorListScroller);

				removeSelectedBehaviorButton = new JButton("Remove Selected Behavior");
				removeSelectedBehaviorButton.addActionListener(this);
				removeSelectedBehaviorButton.setForeground(Color.RED);
				assignedBehaviorPanel.add(removeSelectedBehaviorButton);


				selectableBehaviorPanel = new JPanel();
				selectableBehaviorPanel.setLayout(new BoxLayout(selectableBehaviorPanel, BoxLayout.Y_AXIS));
				JLabel selectableBehaviorLabel = new JLabel("Selectable Behaviors");
				selectableBehaviorPanel.add(selectableBehaviorLabel);
					selectableBehaviorListModel = new DefaultListModel<String>();
					selectableBehaviorList = new JList<String>(selectableBehaviorListModel); //data has type Object
					selectableBehaviorList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
					selectableBehaviorList.setLayoutOrientation(JList.VERTICAL);
					selectableBehaviorList.setVisibleRowCount(10);
					selectableBehaviorList.setForeground(Color.BLACK);
					selectableBehaviorList.setFont(listFont);
					selectableBehaviorList.setFixedCellHeight(16);
					selectableBehaviorList.addListSelectionListener(this);
					selectableBehaviorListScroller = new JScrollPane(selectableBehaviorList);
				selectableBehaviorPanel.add(selectableBehaviorListScroller);

				addSelectedBehaviorButton = new JButton("Add Selected Behavior");
				addSelectedBehaviorButton.addActionListener(this);
				selectableBehaviorPanel.add(addSelectedBehaviorButton);

			behaviorListsPanel.add(assignedBehaviorPanel, BorderLayout.WEST);
			behaviorListsPanel.add(selectableBehaviorPanel, BorderLayout.EAST);

		listsPanel.add(behaviorListsPanel);

			connectionListsPanel = new JPanel(new BorderLayout());
			connectionListsPanel.setBorder(EditorMain.border);

				assignedConnectionPanel = new JPanel();
				assignedConnectionPanel.setLayout(new BoxLayout(assignedConnectionPanel, BoxLayout.Y_AXIS));
				JLabel assignedConnectionLabel = new JLabel("Assigned Points Of Interest");
					assignedConnectionPanel.add(assignedConnectionLabel);
					assignedConnectionListModel = new DefaultListModel<GameObject>();
					assignedConnectionList = new JList<GameObject>(assignedConnectionListModel); //data has type Object
					assignedConnectionList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
					assignedConnectionList.setLayoutOrientation(JList.VERTICAL);
					assignedConnectionList.setVisibleRowCount(20);
					assignedConnectionList.setForeground(Color.BLACK);
					assignedConnectionList.setFont(listFont);
					assignedConnectionList.setFixedCellHeight(16);
					assignedConnectionList.addListSelectionListener(this);
					assignedConnectionList.setCellRenderer(new EntityConnectionsListShortTypeNameCellRenderer());
					assignedConnectionListScroller = new JScrollPane(assignedConnectionList);
				assignedConnectionPanel.add(assignedConnectionListScroller);

				removeSelectedConnectionButton = new JButton("Remove Selected Connection");
				removeSelectedConnectionButton.addActionListener(this);
				removeSelectedConnectionButton.setForeground(Color.RED);
				assignedConnectionPanel.add(removeSelectedConnectionButton);


				selectableConnectionPanel = new JPanel();
				selectableConnectionPanel.setLayout(new BoxLayout(selectableConnectionPanel, BoxLayout.Y_AXIS));
				JLabel selectableConnectionLabel = new JLabel("Selectable Points Of Interest");
				selectableConnectionPanel.add(selectableConnectionLabel);
					selectableConnectionListModel = new DefaultListModel<GameObject>();
					selectableConnectionList = new JList<GameObject>(selectableConnectionListModel); //data has type Object
					selectableConnectionList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
					selectableConnectionList.setLayoutOrientation(JList.VERTICAL);
					selectableConnectionList.setVisibleRowCount(20);
					selectableConnectionList.setForeground(Color.BLACK);
					selectableConnectionList.setFont(listFont);
					selectableConnectionList.setFixedCellHeight(16);
					selectableConnectionList.addListSelectionListener(this);
					selectableConnectionList.setCellRenderer(new EntityConnectionsListShortTypeNameCellRenderer());
					selectableConnectionListScroller = new JScrollPane(selectableConnectionList);
				selectableConnectionPanel.add(selectableConnectionListScroller);

				addSelectedConnectionButton = new JButton("Add Selected Connection");
				addSelectedConnectionButton.addActionListener(this);
				selectableConnectionPanel.add(addSelectedConnectionButton);

			connectionListsPanel.add(assignedConnectionPanel, BorderLayout.WEST);
			connectionListsPanel.add(selectableConnectionPanel, BorderLayout.EAST);

		listsPanel.add(connectionListsPanel);












		JPanel allSpriteOptionsPanel = new JPanel();
		allSpriteOptionsPanel.setBorder(EditorMain.border);
		allSpriteOptionsPanel.setLayout(new BoxLayout(allSpriteOptionsPanel, BoxLayout.Y_AXIS));


		JPanel leftPanel = new JPanel(new GridLayout(0,1,0,0));
		JPanel rightPanel = new JPanel(new GridLayout(0,1,0,0));
		//---------------------
		//Map Sprite Name
		//---------------------
			//JPanel entityNamePanel = new JPanel(new GridLayout(0,2,0,0));
			//entityNamePanel.setBackground(Color.LIGHT_GRAY);
			JLabel entityNameLabel = new JLabel("Map Sprite Name",JLabel.RIGHT);
			//entityNameLabel.setFont(new Font("Arial", Font.BOLD, 12));
			entityNameTextField = new JTextField("-1",30);
			//entityNameTextField.getDocument().addDocumentListener(this);
			entityNameTextField.addCaretListener(this);
			entityNameTextField.addKeyListener(this);
			entityNameTextField.setForeground(Color.GRAY);
			leftPanel.add(entityNameLabel);
			rightPanel.add(entityNameTextField);
		//allSpriteOptionsPanel.add(entityNamePanel);

		//---------------------
		//Sprite Name
		//---------------------
			//JPanel spriteNamePanel = new JPanel(new GridLayout(0,2,0,0));
			//spriteNamePanel.setBackground(Color.GRAY);
			JLabel spriteNameLabel = new JLabel("Sprite Name",JLabel.RIGHT);
			//spriteNameLabel.setFont(new Font("Arial", Font.BOLD, 12));
			spriteNameTextField = new JTextField("-1",30);
			spriteNameTextField.setEnabled(false);
			leftPanel.add(spriteNameLabel);
			rightPanel.add(spriteNameTextField);
		//allSpriteOptionsPanel.add(spriteNamePanel);

		//---------------------
		//Initial Animation Frame
		//---------------------
			//JPanel framePanel = new JPanel(new GridLayout(0,2,0,0));
			//framePanel.setBackground(Color.LIGHT_GRAY);
			JLabel frameLabel = new JLabel("Initial Animation Frame",JLabel.RIGHT);
			//frameLabel.setFont(new Font("Arial", Font.BOLD, 12));
			initialFrameTextField = new JTextField("0",4);
			initialFrameTextField.getDocument().addDocumentListener(this);
			//frameText.setEnabled(false);
			leftPanel.add(frameLabel);
			rightPanel.add(initialFrameTextField);
		//allSpriteOptionsPanel.add(framePanel);

		//---------------------
		//Comments
		//---------------------
			//JPanel commentPanel = new JPanel(new GridLayout(0,2,0,0));
			//commentPanel.setBackground(Color.GRAY);
			JLabel commentLabel = new JLabel("Comments: ",JLabel.RIGHT);
			//commentLabel.setFont(new Font("Arial", Font.BOLD, 12));
			commentTextField = new JTextField("-1",30);
			leftPanel.add(commentLabel);
			rightPanel.add(commentTextField);
		//allSpriteOptionsPanel.add(commentPanel);

		//---------------------
		//Animate Through Frames
		//---------------------
			//JPanel animateThroughFramesPanel = new JPanel(new GridLayout(0,2,0,0));
			//animateThroughFramesPanel.setBackground(Color.LIGHT_GRAY);
			JLabel animateThroughFramesLabel = new JLabel("Animate Through Frames?",JLabel.RIGHT);
			//animateThroughFramesLabel.setFont(new Font("Arial", Font.BOLD, 12));
			animateThroughFramesCheckbox = new JCheckBox();
			animateThroughFramesCheckbox.addItemListener(this);
			animateThroughFramesCheckbox.setSelected(false);
			leftPanel.add(animateThroughFramesLabel);
			rightPanel.add(animateThroughFramesCheckbox);
		//allSpriteOptionsPanel.add(animateThroughFramesPanel);

		//---------------------
		//Random Frames
		//---------------------
			//JPanel randomFramesPanel = new JPanel(new GridLayout(0,2,0,0));
			//randomFramesPanel.setBackground(Color.LIGHT_GRAY);
			JLabel randomFramesLabel = new JLabel("Randomly Select Frames?",JLabel.RIGHT);
			//randomFramesLabel.setFont(new Font("Arial", Font.BOLD, 12));
			randomFramesCheckbox = new JCheckBox();
			randomFramesCheckbox.addItemListener(this);
			randomFramesCheckbox.setSelected(false);
			leftPanel.add(randomFramesLabel);
			rightPanel.add(randomFramesCheckbox);
		//allSpriteOptionsPanel.add(randomFramesPanel);

		//---------------------
		//Ticks Between Frames
		//---------------------
			//JPanel ticksBetweenFramesPanel = new JPanel(new GridLayout(0,2,0,0));
			//ticksBetweenFramesPanel.setBackground(Color.LIGHT_GRAY);
			JLabel ticksBetweenFramesLabel = new JLabel("Ticks Between Frames",JLabel.RIGHT);
			//ticksBetweenFramesLabel.setFont(new Font("Arial", Font.BOLD, 12));
			ticksBetweenFramesTextField = new JTextField("100",4);
			//ticksBetweenFramesText.setEnabled(false);
			ticksBetweenFramesTextField.getDocument().addDocumentListener(this);
			leftPanel.add(ticksBetweenFramesLabel);
			rightPanel.add(ticksBetweenFramesTextField);
		//allSpriteOptionsPanel.add(ticksBetweenFramesPanel);

		//---------------------
		//Random Up To Ticks Between Frames?
		//---------------------

			//JPanel randomTimeBetweenFramesPanel = new JPanel(new GridLayout(0,2,0,0));
			//randomTimeBetweenFramesPanel.setBackground(Color.LIGHT_GRAY);
			JLabel randomTicksBetweenFramesLabel = new JLabel("Random (Up To Ticks) Between Frames?",JLabel.RIGHT);
			//randomTimeBetweenFramesLabel.setFont(new Font("Arial", Font.BOLD, 12));
			randomTicksBetweenFramesCheckbox = new JCheckBox();
			randomTicksBetweenFramesCheckbox.addItemListener(this);
			randomTicksBetweenFramesCheckbox.setSelected(false);

			leftPanel.add(randomTicksBetweenFramesLabel);
			rightPanel.add(randomTicksBetweenFramesCheckbox);
		//allSpriteOptionsPanel.add(randomTimeBetweenFramesPanel);



		//---------------------
		//Ticks Between Animation
		//---------------------
			//JPanel ticksBetweenAnimationPanel = new JPanel(new GridLayout(0,2,0,0));
			//ticksBetweenAnimationPanel.setBackground(Color.LIGHT_GRAY);
			JLabel ticksBetweenAnimationLabel = new JLabel("Ticks Between Anim Loop",JLabel.RIGHT);
			//ticksBetweenAnimationLabel.setFont(new Font("Arial", Font.BOLD, 12));
			ticksBetweenAnimationTextField = new JTextField("0",4);
			ticksBetweenAnimationTextField.getDocument().addDocumentListener(this);
			//ticksBetweenAnimationText.setEnabled(false);
			leftPanel.add(ticksBetweenAnimationLabel);
			rightPanel.add(ticksBetweenAnimationTextField);
		//allSpriteOptionsPanel.add(ticksBetweenAnimationPanel);

		//---------------------
		//Random Up To Ticks Between Loop?
		//---------------------

			//JPanel randomTimeBetweenAnimationPanel = new JPanel(new GridLayout(0,2,0,0));
			//randomTimeBetweenAnimationPanel.setBackground(Color.LIGHT_GRAY);
			JLabel randomTimeBetweenAnimationLabel = new JLabel("Random (Up To Ticks) Between Loop?",JLabel.RIGHT);
			//randomTimeBetweenAnimationLabel.setFont(new Font("Arial", Font.BOLD, 12));
			randomTimeBetweenAnimationCheckbox = new JCheckBox();
			randomTimeBetweenAnimationCheckbox.addItemListener(this);
			randomTimeBetweenAnimationCheckbox.setSelected(false);

			leftPanel.add(randomTimeBetweenAnimationLabel);
			rightPanel.add(randomTimeBetweenAnimationCheckbox);
		//allSpriteOptionsPanel.add(randomTimeBetweenAnimationPanel);

		//---------------------
		//Pushable By Entities?
		//---------------------

			//JPanel pushablePanel = new JPanel(new GridLayout(0,2,0,0));
			//pushablePanel.setBackground(Color.LIGHT_GRAY);
			JLabel pushableLabel = new JLabel("Pushable By Entities?",JLabel.RIGHT);
			//pushableLabel.setFont(new Font("Arial", Font.BOLD, 12));
			pushableCheckbox = new JCheckBox();
			pushableCheckbox.addItemListener(this);
			pushableCheckbox.setSelected(false);
			leftPanel.add(pushableLabel);
			rightPanel.add(pushableCheckbox);
		//allSpriteOptionsPanel.add(pushablePanel);

		//---------------------
		//Non Walkable?
		//---------------------

			//JPanel nonWalkablePanel = new JPanel(new GridLayout(0,2,0,0));
			//nonWalkablePanel.setBackground(Color.LIGHT_GRAY);
			JLabel nonWalkableLabel = new JLabel("Non Walkable (Use Hit Detection)?",JLabel.RIGHT);
			//nonWalkableLabel.setFont(new Font("Arial", Font.BOLD, 12));
			nonWalkableCheckbox = new JCheckBox();
			nonWalkableCheckbox.addItemListener(this);
			nonWalkableCheckbox.setSelected(true);
			leftPanel.add(nonWalkableLabel);
			rightPanel.add(nonWalkableCheckbox);
		//allSpriteOptionsPanel.add(nonWalkablePanel);

		//---------------------
		//Override shadow
		//---------------------

			//JPanel disableShadowPanel = new JPanel(new GridLayout(0,2,0,0));
			//disableShadowPanel.setBackground(Color.LIGHT_GRAY);
			JLabel disableShadowLabel = new JLabel("Disable Shadow (If Sprite Has One)?",JLabel.RIGHT);
			//disableShadowLabel.setFont(new Font("Arial", Font.BOLD, 12));
			disableShadowCheckbox = new JCheckBox();
			disableShadowCheckbox.addItemListener(this);
			disableShadowCheckbox.setSelected(true);
			leftPanel.add(disableShadowLabel);
			rightPanel.add(disableShadowCheckbox);
		//allSpriteOptionsPanel.add(disableShadowPanel);

		//---------------------
		//Transparent?
		//---------------------

			//JPanel transparentPanel = new JPanel(new GridLayout(0,2,0,0));
			//transparentPanel.setBackground(Color.LIGHT_GRAY);
			JLabel transparentLabel = new JLabel("Transparent?",JLabel.RIGHT);
			//transparentLabel.setFont(new Font("Arial", Font.BOLD, 12));
			transparentCheckbox = new JCheckBox();
			transparentCheckbox.addItemListener(this);
			transparentCheckbox.setSelected(false);
			leftPanel.add(transparentLabel);
			rightPanel.add(transparentCheckbox);
		//allSpriteOptionsPanel.add(transparentPanel);

		//---------------------
		//Scale
		//---------------------
			//JPanel scalePanel = new JPanel(new GridLayout(0,2,0,0));
			//scalePanel.setBackground(Color.LIGHT_GRAY);
			JLabel scaleLabel = new JLabel("Scale",JLabel.RIGHT);
			//scaleLabel.setFont(new Font("Arial", Font.BOLD, 12));
			scaleTextField = new JTextField("1.0f",4);
			scaleTextField.getDocument().addDocumentListener(this);

			leftPanel.add(scaleLabel);
			rightPanel.add(scaleTextField);
		//allSpriteOptionsPanel.add(scalePanel);

		//---------------------
		//Above Top Layers
		//---------------------

//			//JPanel aboveTopLayerPanel = new JPanel(new GridLayout(0,2,0,0));
//			//aboveTopLayerPanel.setBackground(Color.LIGHT_GRAY);
//			JLabel aboveTopLayerLabel = new JLabel("Above Top Layers?",JLabel.RIGHT);
//			//aboveTopLayerLabel.setFont(new Font("Arial", Font.BOLD, 12));
//			aboveTopLayerCheckbox = new JCheckBox();
//			aboveTopLayerCheckbox.setSelected(false);
//			leftPanel.add(aboveTopLayerLabel);
//			rightPanel.add(aboveTopLayerCheckbox);
//		//allSpriteOptionsPanel.add(aboveTopLayerPanel);


			//JPanel renderOrderPanel = new JPanel();
			renderOrderCombobox = new JComboBox<String>();
			renderOrderComboboxModel = new DefaultComboBoxModel<String>();
			renderOrderCombobox.setBackground(EditorMain.comboboxBackgroundColor);
			renderOrderCombobox.addItem("Ground");
			renderOrderCombobox.addItem("Overlay");
			renderOrderCombobox.addItem("Above Overlay");
			renderOrderCombobox.addItem("Above Text");
			renderOrderCombobox.setSelectedIndex(0);
			renderOrderCombobox.addActionListener(this);
			JLabel renderOrderLabel = new JLabel("Render Order (Layer)",JLabel.RIGHT);
			leftPanel.add(renderOrderLabel);
			rightPanel.add(renderOrderCombobox);
		//allSpriteOptionsPanel.add(renderOrderPanel);




		//---------------------
		//Above When Equal
		//---------------------

			//JPanel aboveWhenEqualPanel = new JPanel(new GridLayout(0,2,0,0));
			//aboveWhenEqualPanel.setBackground(Color.LIGHT_GRAY);
			JLabel aboveWhenEqualLabel = new JLabel("Above When Equal Z?",JLabel.RIGHT);
			//aboveWhenEqualLabel.setFont(new Font("Arial", Font.BOLD, 12));
			aboveWhenEqualCheckbox = new JCheckBox();
			aboveWhenEqualCheckbox.addItemListener(this);
			aboveWhenEqualCheckbox.setSelected(false);
			leftPanel.add(aboveWhenEqualLabel);
			rightPanel.add(aboveWhenEqualCheckbox);
		//allSpriteOptionsPanel.add(aboveWhenEqualPanel);

		//---------------------
		//Always On Bottom
		//---------------------

			//JPanel alwaysOnBottomPanel = new JPanel(new GridLayout(0,2,0,0));
			//alwaysOnBottomPanel.setBackground(Color.LIGHT_GRAY);
			JLabel alwaysOnBottomLabel = new JLabel("Always On Bottom?",JLabel.RIGHT);
			//alwaysOnBottomLabel.setFont(new Font("Arial", Font.BOLD, 12));
			alwaysOnBottomCheckbox = new JCheckBox();
			alwaysOnBottomCheckbox.addItemListener(this);
			alwaysOnBottomCheckbox.setSelected(false);
			leftPanel.add(alwaysOnBottomLabel);
			rightPanel.add(alwaysOnBottomCheckbox);
		//allSpriteOptionsPanel.add(alwaysOnBottomPanel);


		//---------------------
		//Only Here During Event
		//---------------------

			//JPanel onlyHereDuringEventPanel = new JPanel(new GridLayout(0,2,0,0));
			//onlyHereDuringEventPanel.setBackground(Color.LIGHT_GRAY);
			JLabel onlyHereDuringEventLabel = new JLabel("Only Here During Event?",JLabel.RIGHT);
			//onlyHereDuringEventLabel.setFont(new Font("Arial", Font.BOLD, 12));
			onlyHereDuringEventCheckbox = new JCheckBox();
			onlyHereDuringEventCheckbox.addItemListener(this);
			onlyHereDuringEventCheckbox.setSelected(false);
			leftPanel.add(onlyHereDuringEventLabel);
			rightPanel.add(onlyHereDuringEventCheckbox);
		//allSpriteOptionsPanel.add(onlyHereDuringEventPanel);


//			//JPanel walkSpeedPanel = new JPanel();
//			walkSpeedCombobox = new JComboBox<String>();
//			walkSpeedComboboxModel = new DefaultComboBoxModel<String>();
//			walkSpeedCombobox.setBackground(EditorMain.comboboxBackgroundColor);
//			walkSpeedCombobox.addItem("Slow");
//			walkSpeedCombobox.addItem("Medium");
//			walkSpeedCombobox.addItem("Fast");
//			walkSpeedCombobox.setSelectedIndex(1);
//			walkSpeedCombobox.addActionListener(this);
//			JLabel walkSpeedLabel = new JLabel("Walking Speed",JLabel.RIGHT);
//			leftPanel.add(walkSpeedLabel);
//			rightPanel.add(walkSpeedCombobox);
//		//allSpriteOptionsPanel.add(walkSpeedPanel);



			//JPanel ticksPerPixelSpeedPanel = new JPanel(new GridLayout(0,2,0,0));
			//ticksPerPixelSpeedPanel.setBackground(Color.LIGHT_GRAY);
			JLabel ticksPerPixelLabel = new JLabel("Ticks Per Pixel (Move Speed)",JLabel.RIGHT);
			//ticksPerPixelSpeedLabel.setFont(new Font("Arial", Font.BOLD, 12));
			ticksPerPixelTextField = new JTextField("12",4);
			ticksPerPixelTextField.getDocument().addDocumentListener(this);
			ticksPerPixelTextField.setToolTipText("3=Very Fast | 5=Player Speed | 8=Character Speed | 12=Entity Speed");
			//ticksPerPixelSpeedText.setEnabled(false);
			leftPanel.add(ticksPerPixelLabel);
			rightPanel.add(ticksPerPixelTextField);
		//allSpriteOptionsPanel.add(ticksPerPixelSpeedPanel);


			JPanel leftRightPanel = new JPanel(new BorderLayout());
			leftRightPanel.add(leftPanel,BorderLayout.WEST);
			leftRightPanel.add(rightPanel,BorderLayout.CENTER);
		allSpriteOptionsPanel.add(leftRightPanel);

			JPanel eventButtonPanel = new JPanel();
			addOrEditEventButton = new JButton("Add New Event");
			addOrEditEventButton.addActionListener(this);
			eventButtonPanel.add(Box.createHorizontalGlue());
			eventButtonPanel.add(addOrEditEventButton);
			eventButtonPanel.add(Box.createHorizontalGlue());
		allSpriteOptionsPanel.add(eventButtonPanel);




		JPanel animationPanel = new JPanel();
		animationPanel.setBorder(EditorMain.border);
		animationPanel.setLayout(new BoxLayout(animationPanel,BoxLayout.Y_AXIS));
		animationPanel.add(Box.createRigidArea(new Dimension(200,0)));
		animationCanvas = new JComponent()
		{
			/**
			 *
			 */
			private static final long serialVersionUID = 1L;

			public void paint(Graphics G)
			{
				Sprite sprite = getMap().getEntity(editingEntityIndex).getSprite();


				if(sprite==null||G==null)return;

				int w = sprite.wP()*2;
				int h = sprite.hP()*2;
				BufferedImage img = sprite.getFrameImage(currentFrame);

				if(G!=null)
				{
					G.setColor(Color.WHITE);
					G.fillRect(0,0,getWidth(), getHeight());
					G.drawImage(img,0,0,w,h,this);
				}
			}
		};
		animationPanel.add(animationCanvas);





		entityListModel = new DefaultListModel<Entity>();
		entityList = new JList<Entity>(entityListModel); //data has type Object
		entityList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		entityList.setLayoutOrientation(JList.VERTICAL);
		entityList.setVisibleRowCount(50);
		entityList.setForeground(Color.BLACK);
		entityList.setFont(listFont);
		entityList.setFixedCellHeight(16);
		entityList.addListSelectionListener(this);

		entityList.setCellRenderer(new EntityListNameCellRenderer());
		entityList.setFocusable(false);


		JScrollPane entityListScroller = new JScrollPane(entityList);

		entityListScroller.setBorder(EditorMain.border);
		entityListScroller.setFocusable(false);


		JPanel entityListPanel = new JPanel();
		entityListPanel.setLayout(new BoxLayout(entityListPanel,BoxLayout.Y_AXIS));
		entityListPanel.add(Box.createRigidArea(new Dimension(100,0)));
		entityListPanel.add(entityListScroller);


		entityListScroller.setPreferredSize(new Dimension(250,1));

		//entityList.setMaximumSize(new Dimension(300,2000));
		//entityListScroller.setMaximumSize(new Dimension(300,2000));
		//entityListPanel.setMaximumSize(new Dimension(300,2000));




		everythingPanel.add(animationPanel, BorderLayout.WEST);
		everythingPanel.add(allSpriteOptionsPanel, BorderLayout.CENTER);
		everythingPanel.add(listsPanel, BorderLayout.EAST);


		centerPanel = new JPanel(new BorderLayout());
		centerPanel.setBorder(EditorMain.border);

		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(eventEditor,BorderLayout.CENTER);


		add(entityListPanel,BorderLayout.WEST);
		add(centerPanel, BorderLayout.CENTER);



		setSize(EditorMain.getScreenWidth()-20, 770);
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
	public void showEntityWindow()
	{//===============================================================================================


		if(getMap().getSelectedEntityIndex()==-1)return;

		editingEntityIndex = getMap().getSelectedEntityIndex();

		entityListModel.removeAllElements();
		for(int i=0;i<getMap().getNumEntities();i++)
		{
			entityListModel.addElement(getMap().getEntity(i));
		}

		entityList.setSelectedIndex(editingEntityIndex);

		updateFieldsFromEntityVars();

		populateLists();


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}




		animationCanvas.repaint();


		entityNameTextField.setForeground(Color.GRAY);

	}



	//===============================================================================================
	public void populateLists()
	{//===============================================================================================
		selectableBehaviorListModel.removeAllElements();
		selectableBehaviorListModel.addElement("ifSpriteInRangeWalkToFirstPointLookAtSprite");
		selectableBehaviorListModel.addElement("ifSpriteInRangeLookAtSprite");
		selectableBehaviorListModel.addElement("walkToPointsInOrder");
		selectableBehaviorListModel.addElement("walkToPointsRandomly");
		selectableBehaviorListModel.addElement("faceDirectionShuffleFeet");
		selectableBehaviorListModel.addElement("lookAtSpriteShuffleFeet");


		selectableConnectionListModel.removeAllElements();
		for(int i=0;i<getMap().getNumAreas();i++)
		{
			Area a = getMap().getArea(i);

			selectableConnectionListModel.addElement(a);

		}
		for(int i=0;i<getMap().getNumDoors();i++)
		{
			Door d = getMap().getDoor(i);
			selectableConnectionListModel.addElement(d);
		}





		Entity s = getMap().getEntity(editingEntityIndex);


		assignedBehaviorListModel.removeAllElements();
		for(int i=0;i<s.behaviorList().size();i++)
		{
			assignedBehaviorListModel.addElement(s.behaviorList().get(i));

		}

		assignedConnectionListModel.removeAllElements();
		for(int i=0;i<s.connectionTYPEIDList().size();i++)
		{
			assignedConnectionListModel.addElement(Project.getMapObjectByTYPEIDName(s.connectionTYPEIDList().get(i)));
		}



		refreshListLayout();

	}
	//===============================================================================================
	public void refreshListLayout()
	{//===============================================================================================

		//if(true)return;

/*
		assignedConnectionList.setMinimumSize(new Dimension(300,100));
		assignedConnectionList.setMaximumSize(new Dimension(300,100));
		assignedConnectionList.setPreferredSize(new Dimension(300,100));
		assignedConnectionList.setSize(new Dimension(300,100));
		assignedConnectionList.validate();


		assignedDialogueList.setMinimumSize(new Dimension(300,100));
		assignedDialogueList.setMaximumSize(new Dimension(300,100));
		assignedDialogueList.setPreferredSize(new Dimension(300,100));
		assignedDialogueList.setSize(new Dimension(300,100));
		assignedDialogueList.validate();


		selectableConnectionList.setMinimumSize(new Dimension(300,100));
		selectableConnectionList.setMaximumSize(new Dimension(300,100));
		selectableConnectionList.setPreferredSize(new Dimension(300,100));
		selectableConnectionList.setSize(new Dimension(300,100));
		selectableConnectionList.validate();


		selectableBehaviorList.setMinimumSize(new Dimension(300,100));
		selectableBehaviorList.setMaximumSize(new Dimension(300,100));
		selectableBehaviorList.setPreferredSize(new Dimension(300,100));
		selectableBehaviorList.setSize(new Dimension(300,100));
		selectableBehaviorList.validate();


		selectableDialogueList.setMinimumSize(new Dimension(300,100));
		selectableDialogueList.setMaximumSize(new Dimension(300,100));
		selectableDialogueList.setPreferredSize(new Dimension(300,100));
		selectableDialogueList.setSize(new Dimension(300,100));
		selectableDialogueList.validate();

*/
		assignedBehaviorListScroller.setMinimumSize(new Dimension(300,100));
		assignedBehaviorListScroller.setMaximumSize(new Dimension(300,200));
		assignedBehaviorListScroller.setPreferredSize(new Dimension(300,100));
		assignedBehaviorListScroller.setSize(new Dimension(300,200));
		assignedBehaviorListScroller.validate();


		assignedConnectionListScroller.setMinimumSize(new Dimension(300,100));
		assignedConnectionListScroller.setMaximumSize(new Dimension(300,200));
		assignedConnectionListScroller.setPreferredSize(new Dimension(300,100));
		assignedConnectionListScroller.setSize(new Dimension(300,200));
		assignedConnectionListScroller.validate();


//		assignedDialogueListScroller.setMinimumSize(new Dimension(300,200));
//		assignedDialogueListScroller.setMaximumSize(new Dimension(300,200));
//		assignedDialogueListScroller.setPreferredSize(new Dimension(300,200));
//		assignedDialogueListScroller.setSize(new Dimension(300,200));
//		assignedDialogueListScroller.validate();


		selectableConnectionListScroller.setMinimumSize(new Dimension(300,100));
		selectableConnectionListScroller.setMaximumSize(new Dimension(300,200));
		selectableConnectionListScroller.setPreferredSize(new Dimension(300,100));
		selectableConnectionListScroller.setSize(new Dimension(300,200));
		selectableConnectionListScroller.validate();


		selectableBehaviorListScroller.setMinimumSize(new Dimension(300,100));
		selectableBehaviorListScroller.setMaximumSize(new Dimension(300,200));
		selectableBehaviorListScroller.setPreferredSize(new Dimension(300,100));
		selectableBehaviorListScroller.setSize(new Dimension(300,200));
		selectableBehaviorListScroller.validate();

//
//		selectableDialogueListScroller.setMinimumSize(new Dimension(300,200));
//		selectableDialogueListScroller.setMaximumSize(new Dimension(300,200));
//		selectableDialogueListScroller.setPreferredSize(new Dimension(300,200));
//		selectableDialogueListScroller.setSize(new Dimension(300,200));
//		selectableDialogueListScroller.validate();

		assignedBehaviorList.setMinimumSize(new Dimension(300,100));
		assignedBehaviorList.setMaximumSize(new Dimension(300,200));
		assignedBehaviorList.setPreferredSize(new Dimension(300,100));
		assignedBehaviorList.setSize(new Dimension(300,200));
		assignedBehaviorList.validate();




//		dialoguePreviewTextArea.setMinimumSize(new Dimension(600,200));
//		dialoguePreviewTextArea.setMaximumSize(new Dimension(600,200));
//		dialoguePreviewTextArea.setPreferredSize(new Dimension(600,200));
//		dialoguePreviewTextArea.setSize(new Dimension(600,200));
//		dialoguePreviewTextArea.validate();

/*

		behaviorPanel.setMinimumSize(new Dimension(620,behaviorPanel.getHeight()));
		behaviorPanel.setMaximumSize(new Dimension(620,behaviorPanel.getHeight()));
		behaviorPanel.setPreferredSize(new Dimension(620,behaviorPanel.getHeight()));
		behaviorPanel.setSize(new Dimension(620,behaviorPanel.getHeight()));
		behaviorPanel.validate();

		assignedBehaviorPanel.setMinimumSize(new Dimension(300,assignedBehaviorPanel.getHeight()));
		assignedBehaviorPanel.setMaximumSize(new Dimension(300,assignedBehaviorPanel.getHeight()));
		assignedBehaviorPanel.setPreferredSize(new Dimension(300,assignedBehaviorPanel.getHeight()));
		assignedBehaviorPanel.setSize(new Dimension(300,assignedBehaviorPanel.getHeight()));
		assignedBehaviorPanel.validate();

		selectableBehaviorPanel.setMinimumSize(new Dimension(300,selectableBehaviorPanel.getHeight()));
		selectableBehaviorPanel.setMaximumSize(new Dimension(300,selectableBehaviorPanel.getHeight()));
		selectableBehaviorPanel.setPreferredSize(new Dimension(300,selectableBehaviorPanel.getHeight()));
		selectableBehaviorPanel.setSize(new Dimension(300,selectableBehaviorPanel.getHeight()));
		selectableBehaviorPanel.validate();




		connectionPanel.setMinimumSize(new Dimension(620,connectionPanel.getHeight()));
		connectionPanel.setMaximumSize(new Dimension(620,connectionPanel.getHeight()));
		connectionPanel.setPreferredSize(new Dimension(620,connectionPanel.getHeight()));
		connectionPanel.setSize(new Dimension(620,connectionPanel.getHeight()));
		connectionPanel.validate();

		assignedConnectionPanel.setMinimumSize(new Dimension(300,assignedConnectionPanel.getHeight()));
		assignedConnectionPanel.setMaximumSize(new Dimension(300,assignedConnectionPanel.getHeight()));
		assignedConnectionPanel.setPreferredSize(new Dimension(300,assignedConnectionPanel.getHeight()));
		assignedConnectionPanel.setSize(new Dimension(300,assignedConnectionPanel.getHeight()));
		assignedConnectionPanel.validate();

		selectableConnectionPanel.setMinimumSize(new Dimension(300,selectableConnectionPanel.getHeight()));
		selectableConnectionPanel.setMaximumSize(new Dimension(300,selectableConnectionPanel.getHeight()));
		selectableConnectionPanel.setPreferredSize(new Dimension(300,selectableConnectionPanel.getHeight()));
		selectableConnectionPanel.setSize(new Dimension(300,selectableConnectionPanel.getHeight()));
		selectableConnectionPanel.validate();




		dialoguePanel.setMinimumSize(new Dimension(620,dialoguePanel.getHeight()));
		dialoguePanel.setMaximumSize(new Dimension(620,dialoguePanel.getHeight()));
		dialoguePanel.setPreferredSize(new Dimension(620,dialoguePanel.getHeight()));
		dialoguePanel.setSize(new Dimension(620,dialoguePanel.getHeight()));
		dialoguePanel.validate();

		assignedDialoguePanel.setMinimumSize(new Dimension(300,assignedDialoguePanel.getHeight()));
		assignedDialoguePanel.setMaximumSize(new Dimension(300,assignedDialoguePanel.getHeight()));
		assignedDialoguePanel.setPreferredSize(new Dimension(300,assignedDialoguePanel.getHeight()));
		assignedDialoguePanel.setSize(new Dimension(300,assignedDialoguePanel.getHeight()));
		assignedDialoguePanel.validate();

		selectableDialoguePanel.setMinimumSize(new Dimension(300,selectableDialoguePanel.getHeight()));
		selectableDialoguePanel.setMaximumSize(new Dimension(300,selectableDialoguePanel.getHeight()));
		selectableDialoguePanel.setPreferredSize(new Dimension(300,selectableDialoguePanel.getHeight()));
		selectableDialoguePanel.setSize(new Dimension(300,selectableDialoguePanel.getHeight()));
		selectableDialoguePanel.validate();

		itemsPanel.setMinimumSize(new Dimension(620,itemsPanel.getHeight()));
		itemsPanel.setMaximumSize(new Dimension(620,itemsPanel.getHeight()));
		itemsPanel.setPreferredSize(new Dimension(620,itemsPanel.getHeight()));
		itemsPanel.setSize(new Dimension(620,itemsPanel.getHeight()));
		itemsPanel.validate();



		itemsPanel.validate();
		behaviorDialoguePanel.validate();


		validate();
		*/

	}




	//===============================================================================================
	public void openEventEditor()
	{//===============================================================================================
		addOrEditEventButton.setVisible(false);
		centerPanel.add(eventEditor);




		setSize(EditorMain.getScreenWidth()-20, 970);
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
	public void updateEntityVarsFromFields()
	{//===============================================================================================


		//if(currentEntity==-1)return;

		Entity entity = getMap().getEntity(editingEntityIndex);
		//Sprite sprite = getMap().getEntity(editingEntityIndex).getSprite();

		//change entityName
		//replace space with _
		if(entityNameTextField.getText().contains(" "))entityNameTextField.setText(entityNameTextField.getText().replace(' ', '_'));

		String name = entityNameTextField.getText();
		name = getMap().createUniqueEntityName(name, editingEntityIndex);
		entity.setName(name);


		if(Integer.parseInt(initialFrameTextField.getText())<entity.getSprite().frames())
			entity.setInitialFrame(Integer.parseInt(initialFrameTextField.getText()));


		entity.setComment(commentTextField.getText());
		entity.setToAlpha(transparentCheckbox.isSelected()?0.5f:1.0f);
		entity.setPushable(pushableCheckbox.isSelected());
		entity.setNonWalkable(nonWalkableCheckbox.isSelected());
		entity.setScale(Float.parseFloat(scaleTextField.getText()));
		//entity.setAboveTopLayer(aboveTopLayerCheckbox.isSelected());
		entity.setAboveWhenEqual(aboveWhenEqualCheckbox.isSelected());
		entity.setAlwaysOnBottom(alwaysOnBottomCheckbox.isSelected());

		entity.setRandomFrames(randomFramesCheckbox.isSelected());
		entity.setDisableShadow(disableShadowCheckbox.isSelected());

		entity.setRandomUpToTicksBetweenFrames(randomTicksBetweenFramesCheckbox.isSelected());
		entity.setRandomUpToTicksBetweenAnimationLoop(randomTimeBetweenAnimationCheckbox.isSelected());
		entity.setAnimateThroughAllFrames(animateThroughFramesCheckbox.isSelected());
		entity.setTicksBetweenFrames(Integer.parseInt(ticksBetweenFramesTextField.getText()));
		entity.setTicksBetweenAnimationLoop(Integer.parseInt(ticksBetweenAnimationTextField.getText()));
		entity.setTicksPerPixelMoved(Float.parseFloat(ticksPerPixelTextField.getText()));



		//entity.setWalkSpeed(walkSpeedCombobox.getSelectedIndex());
		if(renderOrderCombobox.getSelectedIndex()==0)entity.setRenderOrder(RenderOrder.GROUND);
		if(renderOrderCombobox.getSelectedIndex()==1)entity.setRenderOrder(RenderOrder.ABOVE);
		if(renderOrderCombobox.getSelectedIndex()==2)entity.setRenderOrder(RenderOrder.ABOVE_TOP);
		if(renderOrderCombobox.getSelectedIndex()==3)entity.setRenderOrder(RenderOrder.OVER_TEXT);



		entity.setOnlyHereDuringEvent(onlyHereDuringEventCheckbox.isSelected());

		entity.behaviorList().clear();
		for(int i=0;i<assignedBehaviorListModel.getSize();i++)entity.behaviorList().add(assignedBehaviorListModel.get(i));



		entity.connectionTYPEIDList().clear();
		for(int i=0;i<assignedConnectionListModel.getSize();i++)
		{
			entity.connectionTYPEIDList().add(assignedConnectionListModel.get(i).getTYPEIDString());
		}



		if(event!=null)
		{
			if(entity.eventData()!=event.getData())entity.setEventData(event.getData());

			eventEditor.storeEventTreeInString();

			closeEventEditor();
			event = null;
		}


	}

	//===============================================================================================
	public void updateFieldsFromEntityVars()
	{//===============================================================================================

		//if(currentEntity==-1)return;

		Entity entity = getMap().getEntity(editingEntityIndex);
		//Sprite sprite = getMap().getEntity(editingEntityIndex).sprite;

		entityNameTextField.setText(entity.name());
		initialFrameTextField.setText(""+entity.initialFrame());
		commentTextField.setText(entity.comment());
		spriteNameTextField.setText(entity.getSprite().name());

		scaleTextField.setText(""+entity.scale());


		//aboveTopLayerCheckbox.setSelected(entity.aboveTopLayer());
		aboveWhenEqualCheckbox.setSelected(entity.aboveWhenEqual());
		alwaysOnBottomCheckbox.setSelected(entity.alwaysOnBottom());

		randomFramesCheckbox.setSelected(entity.randomFrames());
		disableShadowCheckbox.setSelected(entity.disableShadow());


		transparentCheckbox.setSelected(entity.toAlpha()<1.0f);
		pushableCheckbox.setSelected(entity.pushable());
		nonWalkableCheckbox.setSelected(entity.nonWalkable());
		randomTicksBetweenFramesCheckbox.setSelected(entity.randomUpToTicksBetweenFrames());
		randomTimeBetweenAnimationCheckbox.setSelected(entity.randomUpToTicksBetweenAnimationLoop());
		animateThroughFramesCheckbox.setSelected(entity.animatingThroughAllFrames());
		ticksBetweenFramesTextField.setText(""+entity.ticksBetweenFrames());
		ticksBetweenAnimationTextField.setText(""+entity.ticksBetweenAnimationLoop());
		ticksPerPixelTextField.setText(""+entity.ticksPerPixelMoved());

		//onlyHereDuringEventCheckbox.setState(entity.onlyHereDuringEvent);


		//walkSpeedCombobox.setSelectedIndex(entity.walkSpeed());
		if(entity.renderOrder()==RenderOrder.GROUND)renderOrderCombobox.setSelectedIndex(0);
		if(entity.renderOrder()==RenderOrder.ABOVE)renderOrderCombobox.setSelectedIndex(1);
		if(entity.renderOrder()==RenderOrder.ABOVE_TOP)renderOrderCombobox.setSelectedIndex(2);
		if(entity.renderOrder()==RenderOrder.OVER_TEXT)renderOrderCombobox.setSelectedIndex(3);


		currentFrame = entity.initialFrame();



		if(entity.eventData()!=null)
		{
			event = Project.getEventByID(entity.eventData().id());
			if(event!=null)
			{
				if(event.name().length()==0)event.setName(Project.getSelectedMap().name()+"."+entity.name()+".Event");
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




//	//===============================================================================================
//	public void createNewDialogue()
//	{//===============================================================================================
//
//		//open dialogue editor
//		dialogueEditor.createNewDialogue();
//
//		Dialogue d = dialogueEditor.currentDialogue;
//		assignedDialogueListModel.addElement(makeDialogueListString(d));
//		selectableDialogueListModel.addElement(makeDialogueListString(d));
//
//	}
//
//	//===============================================================================================
//	public void editSelectedDialogue()
//	{//===============================================================================================
//		if(selectableDialogueList.getSelectedIndex()>=0)
//		{
//			//open dialogue editor
//
//			Dialogue selectedDialogue = getDialogueFromSelectedListString(selectableDialogueList.getSelectedValue().toString());
//
//			dialogueEditor.editDialogue(selectedDialogue);
//
//			int i = selectableDialogueList.getSelectedIndex();
//			selectableDialogueListModel.remove(i);
//
//			Dialogue d = dialogueEditor.currentDialogue;
//			selectableDialogueListModel.add(i,makeDialogueListString(d));
//
//			selectableDialogueList.setSelectedIndex(i);
//		}
//
//	}

	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		Entity entity = getMap().getEntity(editingEntityIndex);
		//Sprite sprite = getMap().getEntity(editingEntityIndex).sprite;

		if(ae.getSource() == doneButton)
		{


			updateEntityVarsFromFields();

			if(animateThroughFramesCheckbox.isSelected())
			{
				entity.frameTimer.setInitialDelay(Integer.parseInt(ticksBetweenFramesTextField.getText()));
				entity.frameTimer.setDelay(Integer.parseInt(ticksBetweenFramesTextField.getText()));
				entity.startAnimationTimer.setInitialDelay(Integer.parseInt(ticksBetweenAnimationTextField.getText()));
				entity.startAnimationTimer.setDelay(Integer.parseInt(ticksBetweenAnimationTextField.getText()));

				entity.frameTimer.start();
				entity.startAnimationTimer.start();
			}
			else
			{
				entity.frameTimer.stop();
				entity.startAnimationTimer.stop();
			}

			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();



			editingEntityIndex = -1;

			frameTimer.stop();
			animateTimer.stop();
			setVisible(false);


		}
		else
		if(ae.getSource() == cancelButton)
		{
			frameTimer.stop();
			animateTimer.stop();
			setVisible(false);
		}


		if(ae.getSource() == frameTimer)
		{

			//increment current frame
			currentFrame++;

			//if we're the last frame, set frame to 0, stop frameTimer
			if(currentFrame>=entity.getSprite().frames())
			{
				currentFrame=0;
				frameTimer.stop();
				animateTimer.start();
			}

			//draw current frame into mapcanvas.
			animationCanvas.repaint();

		}


		if(ae.getSource() == animateTimer)
		{
			//start frameTimer
			frameTimer.start();
			animateTimer.stop();
		}



		if(ae.getSource() == addSelectedConnectionButton)
		{
			if(selectableConnectionList.getSelectedIndex()>=0)assignedConnectionListModel.addElement(selectableConnectionList.getSelectedValue());

			refreshListLayout();

		}


		if(ae.getSource() == removeSelectedConnectionButton)
		{

			if(assignedConnectionList.getSelectedIndex()>=0)assignedConnectionListModel.remove(assignedConnectionList.getSelectedIndex());

			refreshListLayout();

		}


		if(ae.getSource() == addSelectedBehaviorButton)
		{

			if(selectableBehaviorList.getSelectedIndex()>=0)assignedBehaviorListModel.addElement(selectableBehaviorList.getSelectedValue());
			refreshListLayout();


		}


		if(ae.getSource() == removeSelectedBehaviorButton)
		{
			if(assignedBehaviorList.getSelectedIndex()>=0)assignedBehaviorListModel.remove(assignedBehaviorList.getSelectedIndex());

			refreshListLayout();
		}

		if(ae.getSource() == addOrEditEventButton)
		{

			if(event==null)
			{
				event = new Event(EventData.TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING,Project.getSelectedMap().name()+"."+entity.name(),"","{if(isPlayerTouchingThisEntity() == TRUE){}}");
				entity.setEventData(event.getData());
				eventEditor.editEvent(Project.getSelectedMap(),event);

				openEventEditor();

			}

		}

	}








	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================
		//if animatethroughframes
		if(ie.getSource() == animateThroughFramesCheckbox)
		{
			if(animateThroughFramesCheckbox.isSelected())
			{
				//set timer
				animateTimer.start();
			}
			else
			{

				frameTimer.stop();
				animateTimer.stop();
			}
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




		if(e.getSource() == entityList)
		{
			if(e.getValueIsAdjusting()==true)return;

			if(entityList.getSelectedIndex()==editingEntityIndex)return;

			if(entityList.getSelectedIndex()==-1)return;

			//stop timer
			frameTimer.stop();
			animateTimer.stop();

			//save all vars to previous sprite
			updateEntityVarsFromFields();

			//set current sprite to selected sprite
			editingEntityIndex = entityList.getSelectedIndex();

			entityList.ensureIndexIsVisible(entityList.getSelectedIndex());



			//set text fields from vars

			updateFieldsFromEntityVars();

			populateLists();

			animationCanvas.repaint();

			//select sprite on map canvas
			getMap().setSelectedEntityIndex(editingEntityIndex);
			EditorMain.mapCanvas.scrollToTop(getMap().getSelectedEntity());

			entityNameTextField.setForeground(Color.GRAY);

		}

		refreshListLayout();
	}


	//===============================================================================================
	@Override
	public boolean imageUpdate(Image i, int infoflags, int x, int y, int width, int height)
	{//===============================================================================================
		return true;
	}

	//===============================================================================================
	public void keyTyped(KeyEvent e)
	{//===============================================================================================


	}

	//===============================================================================================
	public void keyPressed(KeyEvent e)
	{//===============================================================================================


		if(e.getSource() == entityNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{

			entityNameTextField.setForeground(Color.GRAY);

			Entity entity = getMap().getEntity(editingEntityIndex);
			Sprite sprite = entity.getSprite();


			if(entityNameTextField.getText().length()==0)return;

			//get var name
			String oldName = entity.name();

			//find var name in name list
			int selectedItem = -1;



			Enumeration<Entity> enm = entityListModel.elements();

			for(int i=0; enm.hasMoreElements(); i++)
			{
				Entity temp = (Entity) enm.nextElement();
				if(temp.name().equals(oldName))
				{
					selectedItem = i;
					break;
				}
			}

//			Object[] listNames = entityListModel.toArray();
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

				String name = entityNameTextField.getText();



				name = getMap().createUniqueEntityName(name, editingEntityIndex);

				entity.setName(name);

				//if(entityNameTextField.getText().equals(name)==false)entityNameTextField.setText(name);

				//update name to textFieldName


				entityListModel.add(selectedItem,entity);
				entityListModel.remove(selectedItem+1);
				entityList.setSelectedIndex(selectedItem);

				validate();
			}
			return;
		}



		if(e.getKeyCode() == KeyEvent.VK_ENTER)
		{
			actionPerformed(new ActionEvent(doneButton,ActionEvent.ACTION_PERFORMED,""));
		}

		if(e.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{
			if(entityList.getSelectedIndex()>0)entityList.setSelectedIndex(entityList.getSelectedIndex()-1);
			valueChanged(new ListSelectionEvent(entityList,0,entityListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(entityList,ItemEvent.ITEM_STATE_CHANGED,entityList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}


		if(e.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{
			if(entityList.getSelectedIndex()>=0&&entityList.getSelectedIndex()<entityListModel.getSize()-1)entityList.setSelectedIndex(entityList.getSelectedIndex()+1);
			valueChanged(new ListSelectionEvent(entityList,0,entityListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(entityList,ItemEvent.ITEM_STATE_CHANGED,entityList.getSelectedValue().toString(), ItemEvent.SELECTED));
		}

	}

	//===============================================================================================
	public void keyReleased(KeyEvent e)
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
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================

		if(e.getSource()==entityNameTextField)
		{
			entityNameTextField.setForeground(Color.RED);
		}

	}


	//===============================================================================================
	@Override
	public void changedUpdate(DocumentEvent e)
	{//===============================================================================================

		Entity entity = getMap().getEntity(editingEntityIndex);
		Sprite sprite = entity.getSprite();



		//if initialframe
		if(e.getDocument() == initialFrameTextField.getDocument())
		{
			if(initialFrameTextField.getText().length()>0)
			{
				if(Integer.parseInt(initialFrameTextField.getText())>=sprite.frames())initialFrameTextField.setText(""+(sprite.frames()-1));

				currentFrame = Integer.parseInt(initialFrameTextField.getText());
				animationCanvas.repaint();
			}
		}

		//if ticksbetweenframes
		if(e.getDocument() == ticksBetweenFramesTextField.getDocument())
		{
			if(ticksBetweenFramesTextField.getText().length()>0)
			frameTimer.setDelay(Integer.parseInt(ticksBetweenFramesTextField.getText()));
		}

		//if ticksbetweenanimation
		if(e.getDocument() == ticksBetweenAnimationTextField.getDocument())
		{
			if(ticksBetweenAnimationTextField.getText().length()>0)
			animateTimer.setDelay(Integer.parseInt(ticksBetweenAnimationTextField.getText()));
		}


	}





	//===============================================================================================
	class EntityListNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public EntityListNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
			if(value!=null)
			{
				setToolTipText("");

				Entity e = (Entity)value;

				if(e.eventData()!=null){setForeground(Color.GREEN);setToolTipText("Entity Has Event.");}

				setText(e.name());
			}
			else setText("null");

				return this;
		}
	}
	//===============================================================================================
	class EntityConnectionsListShortTypeNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public EntityConnectionsListShortTypeNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
			if(value!=null)
			{
				setToolTipText("");

				if(value.getClass().equals(Area.class)){setForeground(Color.YELLOW.darker());setToolTipText("Area");}
				if(value.getClass().equals(Entity.class)){setForeground(Color.BLUE.darker());setToolTipText("Entity");}
				if(value.getClass().equals(Door.class)){setForeground(Color.GREEN.darker());setToolTipText("Door");}


				setText(((GameObject)value).getShortTypeName());
			}
			else setText("null");

				return this;
		}
	}

}