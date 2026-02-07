package com.bobsgame.editor.ControlPanel;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
//import javax.swing.border.EtchedBorder;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.MapCanvas.MapCanvas;
import com.bobsgame.editor.MapCanvas.MapPropertiesEditWindow;
import com.bobsgame.shared.MapData;
//===============================================================================================
public class ControlPanel extends JPanel implements ActionListener, ItemListener
{//===============================================================================================//, KeyListener{  //+keylistener , MouseWheelListener, //MouseMotionListener, MouseListener,

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;
	public EditorMain E;



	//public Graphics G;


	public JButton[] selectLayerButton;
	public JCheckBox[] showLayerCheckbox;
	public JLabel layerLabel[];
	public JPanel layerPanel[];

	public JCheckBox nightTimePreviewCheckbox;

	public JLabel colorNumLabel, colorUsedLabel, rgbLabel, hsbLabel, bgrLabel, selectedActionLabel, allLayersLabel;

	public JPanel rootLayerControlsPanel, colorInfoPanel, selectedColorPanel;

	public JScrollPane paletteScrollPane;
	public PaletteCanvas paletteCanvas;

	public Color bgc[];



	public NoteEditor noteEditor = null;



	static public JButton openNoteEditorButton;


	static public JButton openMapPropertiesEditorButton;

	public JButton moveMapUpButton;
	public JButton moveMapDownButton;


	public TileEditCanvas tileEditCanvas;

	MapPropertiesEditWindow mapPropertiesWindow;

	//===============================================================================================
	public ControlPanel(EditorMain e)
	{//===============================================================================================

		E=e;

		setFocusable(true);
		addKeyListener(E);

		mapPropertiesWindow = new MapPropertiesEditWindow();


		setBackground(Color.BLACK);
		setLayout(new BorderLayout());

		bgc = new Color[MapData.layers];

		bgc[0]=new Color(100,50,0);//ground = brown
		bgc[1]=Color.GREEN.darker().darker();//ground objects = green
		bgc[2]=new Color(255,100,255);//ground shaders = magenta
		bgc[3]=Color.DARK_GRAY;//ground shadow = gray
		bgc[4]=Color.blue.darker();//objects = brown
		bgc[5]=Color.BLUE;//objects2 = purple
		bgc[6]=Color.DARK_GRAY;//object shadows = gray
		bgc[7]=Color.CYAN.darker();//above = light blue
		bgc[8]=Color.CYAN;//above 2 = white
		bgc[9]=Color.DARK_GRAY;//sprite shadows = yellow
		bgc[10]=new Color(255,150,0);//cam fx = orange
		bgc[11]=Color.RED; // hit bounds = red


		bgc[MapData.MAP_DOOR_LAYER]=new Color(0,255,0);//sprite
		bgc[MapData.MAP_ENTITY_LAYER]=new Color(191,0,255);//sprite
		bgc[MapData.MAP_LIGHT_LAYER]=Color.WHITE;//lights
		bgc[MapData.MAP_AREA_LAYER]=Color.YELLOW;//action
		bgc[MapData.MAP_LIGHT_MASK_LAYER]=Color.LIGHT_GRAY;//action



		//-----------------------------
		//tile edit area
		//-----------------------------
			//add(Box.createRigidArea(new Dimension(0,128+16)));



			//-----------------------------
			//labels
			//-----------------------------


				colorNumLabel = new JLabel(" Color:0", JLabel.LEFT);
				colorNumLabel.setForeground(Color.GRAY);
				colorNumLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
				//colorNumLabel.setMaximumSize(new Dimension(130, 20));

				colorUsedLabel = new JLabel(" Used:true", JLabel.LEFT);
				colorUsedLabel.setForeground(Color.GRAY);
				colorUsedLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));

				rgbLabel = new JLabel(" RGB:0,0,0", JLabel.LEFT);
				rgbLabel.setForeground(Color.GRAY);
				rgbLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
				//rgbLabel.setMaximumSize(new Dimension(130, 20));

				hsbLabel = new JLabel(" HSB:0,0,0", JLabel.LEFT);
				hsbLabel.setForeground(Color.GRAY);
				hsbLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
				//hsbLabel.setMaximumSize(new Dimension(130, 20));

				bgrLabel = new JLabel(" BGR:0", JLabel.LEFT);
				bgrLabel.setForeground(Color.GRAY);
				bgrLabel.setFont(new Font("Tahoma", Font.PLAIN, 10));
				//bgrLabel.setMaximumSize(new Dimension(130, 20));



				colorInfoPanel = new JPanel();
				colorInfoPanel.setLayout(new GridLayout(0,1,0,0));

				colorInfoPanel.setBackground(Color.BLACK);


				colorInfoPanel.add(colorNumLabel);
				colorInfoPanel.add(colorUsedLabel);
				colorInfoPanel.add(rgbLabel);
				colorInfoPanel.add(hsbLabel);
				colorInfoPanel.add(bgrLabel);


				selectedColorPanel = new JPanel();
				selectedColorPanel.setBackground(Color.WHITE);

				JPanel colorPanel = new JPanel();
				colorPanel.setLayout(new GridLayout(1,2,0,1));

				colorPanel.add(colorInfoPanel);
				colorPanel.add(selectedColorPanel);


				JPanel centerPanel = new JPanel();
				centerPanel.setLayout(new BorderLayout());


				JPanel topPanel = new JPanel(new BorderLayout());

				topPanel.add(colorPanel, BorderLayout.SOUTH);
				topPanel.setBackground(Color.BLACK);
				//centerPanel.add(colorPanel,BorderLayout.NORTH);







				tileEditCanvas = new TileEditCanvas(E);
				Dimension tileD = new Dimension((tileEditCanvas.EditZoom*8)+(tileEditCanvas.EditGrid_x*2)+1,(tileEditCanvas.EditZoom*8)+(tileEditCanvas.EditGrid_x*2)+1);


				tileEditCanvas.setSize(tileD);
				tileEditCanvas.setPreferredSize(tileD);
				tileEditCanvas.setMinimumSize(tileD);
				tileEditCanvas.setMaximumSize(tileD);

				topPanel.add(tileEditCanvas, BorderLayout.CENTER);



				add(topPanel, BorderLayout.NORTH);



				paletteCanvas = new PaletteCanvas(E);
				//paletteCanvas.setSize(new Dimension((8*16), 32*16));

				Dimension palD = new Dimension(((PaletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2, (paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2);




				paletteCanvas.setSize(palD);
				paletteCanvas.setPreferredSize(palD);
				paletteCanvas.setMinimumSize(palD);
				paletteCanvas.setMaximumSize(palD);


		//-----------------------------
		//palette panel
		//-----------------------------
			paletteScrollPane = new JScrollPane(paletteCanvas);//ScrollPane.SCROLLBARS_AS_NEEDED)
//			{
//				/**
//				 *
//				 */
//				private static final long serialVersionUID = 1L;
//
//				@Override
//				public void doLayout()
//				{
//					super.doLayout();
//
//					/*int height = (E.controlPanel.getHeight()-buttonPanel.getHeight())-tileEditCanvas.getHeight()-colorInfoPanel.getHeight();
//					int maxheight = ((paletteCanvas.colorsPerColumn*paletteCanvas.swathSize)+paletteCanvas.PaletteGrid_y+2)+4;
//					if(height>maxheight)height=maxheight;
//					setSize(new Dimension(((paletteCanvas.colorsPerRow*paletteCanvas.swathSize))+paletteCanvas.PaletteGrid_x+2+24,height));*/
//
//
//				}
//			};


			//paletteScrollPane.setFocusable(false);
			paletteScrollPane.setWheelScrollingEnabled(false);
			paletteScrollPane.setForeground(Color.BLACK);
			paletteScrollPane.setBackground(Color.BLACK);
			paletteScrollPane.setPreferredSize(new Dimension((PaletteCanvas.colorsPerRow*16)+25, 32*16));



			//paletteScrollPane.add(paletteCanvas);




			//paletteScrollPane.doLayout();
			//paletteScrollPane.validate();


			centerPanel.add(paletteScrollPane,BorderLayout.CENTER);

			add(centerPanel, BorderLayout.CENTER);

		//-----------------------------
		//buttons
		//-----------------------------

			selectLayerButton = new JButton[MapData.layers];



			selectLayerButton[0] = new JButton(" [~] ");
			selectLayerButton[1] = new JButton(" [1] ");
			selectLayerButton[2] = new JButton(" [2] ");
			selectLayerButton[3] = new JButton(" [3] ");
			selectLayerButton[4] = new JButton(" [4] ");
			selectLayerButton[5] = new JButton(" [5] ");
			selectLayerButton[6] = new JButton(" [6] ");
			selectLayerButton[MapData.MAP_ENTITY_LAYER]	 = new JButton("[F1]");//sprite
			selectLayerButton[MapData.MAP_DOOR_LAYER]	 = new JButton("[F7]");//doorsprite
			selectLayerButton[7] = new JButton(" [7] ");
			selectLayerButton[8] = new JButton(" [8] ");
			selectLayerButton[9] = new JButton(" [9] ");
			selectLayerButton[MapData.MAP_LIGHT_MASK_LAYER]	  = new JButton("[F2]");//light mask
			selectLayerButton[MapData.MAP_LIGHT_LAYER] 	 = new JButton("[F3]");//light
			selectLayerButton[10] = new JButton("[F4]");//fx
			selectLayerButton[11] = new JButton("[F5]");//hit
			selectLayerButton[MapData.MAP_AREA_LAYER]	  = new JButton("[F6]");//action



			for(int i=0;i<MapData.layers;i++)
			{
				selectLayerButton[i].setFont(new Font("Tahoma",Font.BOLD,14));

				selectLayerButton[i].setForeground(Color.BLACK);
				selectLayerButton[i].setBackground(Color.BLACK);
				selectLayerButton[i].addActionListener(this);
				selectLayerButton[i].setFocusable(true);
				selectLayerButton[i].addKeyListener(E);

			}

		//-----------------------------
		//checkboxes
		//-----------------------------


			showLayerCheckbox = new JCheckBox[MapData.layers];


			for(int i=0;i<MapData.layers;i++)
			{
				showLayerCheckbox[i] = new JCheckBox();

				showLayerCheckbox[i].setSelected(false);

				if(i!=MapData.MAP_SHADER_LAYER)
				if(i!=MapData.MAP_HIT_LAYER)
				if(i!=MapData.MAP_LIGHT_MASK_LAYER)
				if(i!=MapData.MAP_CAMERA_BOUNDS_LAYER)
					showLayerCheckbox[i].setSelected(true);


				showLayerCheckbox[i].addItemListener(this);

				showLayerCheckbox[i].setFocusable(true);
				showLayerCheckbox[i].addKeyListener(E);
				showLayerCheckbox[i].setBackground(Color.BLACK);//new Color(0,0,0,0));
			}


			//-----------------------------
			//labels
			//-----------------------------

				layerLabel = new JLabel[MapData.layers];

				layerLabel[MapData.MAP_GROUND_LAYER] = new JLabel("Ground");
				layerLabel[MapData.MAP_GROUND_DETAIL_LAYER] = new JLabel("Ground Objects");
				layerLabel[MapData.MAP_SHADER_LAYER] = new JLabel("*Shader Mask*");
				layerLabel[MapData.MAP_GROUND_SHADOW_LAYER] = new JLabel("Ground Shadows");
				layerLabel[MapData.MAP_OBJECT_LAYER] = new JLabel("Objects");
				layerLabel[MapData.MAP_OBJECT_DETAIL_LAYER] = new JLabel("Objects2");
				layerLabel[MapData.MAP_OBJECT_SHADOW_LAYER] = new JLabel("Obj Shadows");
				layerLabel[MapData.MAP_ENTITY_LAYER] = new JLabel("**Sprites**");	//sprite layer
				layerLabel[MapData.MAP_DOOR_LAYER] = new JLabel("**Doors**");	//doors layer
				layerLabel[MapData.MAP_ABOVE_LAYER] = new JLabel("Above");
				layerLabel[MapData.MAP_ABOVE_DETAIL_LAYER] = new JLabel("Above2");
				layerLabel[MapData.MAP_SPRITE_SHADOW_LAYER] = new JLabel("Sprite Shadows");
				layerLabel[MapData.MAP_LIGHT_MASK_LAYER] = new JLabel("**Light Mask**");//light mask
				layerLabel[MapData.MAP_LIGHT_LAYER] = new JLabel("**Lights**");//lights layer
				layerLabel[MapData.MAP_CAMERA_BOUNDS_LAYER] = new JLabel("*Camera Bounds/FX*");
				layerLabel[MapData.MAP_HIT_LAYER] = new JLabel("*Hit Detection*");
				layerLabel[MapData.MAP_AREA_LAYER] = new JLabel("**Areas/Warps**");//Area/WarpArea layer



				for(int i=0;i<MapData.layers;i++)
				{
					layerLabel[i].setBackground(bgc[i]);
					layerLabel[i].setForeground(bgc[i]);
					layerLabel[i].setFont(new Font("Tahoma", Font.PLAIN, 12));
				}

		//-----------------------------
		//button panel
		//-----------------------------
			//bp holds label, button, checkbox
			layerPanel = new JPanel[MapData.layers];


			for(int i=0;i<MapData.layers;i++)
			{
				layerPanel[i] = new JPanel(new FlowLayout(FlowLayout.RIGHT, 5, 0));

				layerPanel[i].setBackground(Color.BLACK);

				layerPanel[i].add(layerLabel[i]);
				layerPanel[i].add(selectLayerButton[i]);
				layerPanel[i].add(showLayerCheckbox[i]);
			}








			JPanel mapPropertiesPanel = new JPanel();
			openMapPropertiesEditorButton = new JButton("Open Map Properties");
			openMapPropertiesEditorButton.addActionListener(this);
			openMapPropertiesEditorButton.setFocusable(false);
			mapPropertiesPanel.add(openMapPropertiesEditorButton);
			mapPropertiesPanel.setBackground(Color.BLACK);





			JPanel nightTimePreviewPanel = new JPanel();
			nightTimePreviewPanel.setBackground(Color.BLACK);
			JLabel nightTimePreviewLabel = new JLabel("Night Time?");
			nightTimePreviewCheckbox = new JCheckBox();
			nightTimePreviewCheckbox.setSelected(false);
			nightTimePreviewCheckbox.addItemListener(this);
			nightTimePreviewPanel.add(nightTimePreviewLabel);
			nightTimePreviewPanel.add(nightTimePreviewCheckbox);
			nightTimePreviewLabel.setForeground(Color.WHITE);



			JPanel noteButtonPanel = new JPanel();
			noteButtonPanel.setBackground(Color.BLACK);
			noteEditor = new NoteEditor(e);
			openNoteEditorButton = new JButton("Open Map Notes");
			openNoteEditorButton.addActionListener(this);
			openNoteEditorButton.setFocusable(false);

			noteButtonPanel.add(Box.createRigidArea(new Dimension(20,0)));
			noteButtonPanel.add(openNoteEditorButton);
			noteButtonPanel.add(Box.createRigidArea(new Dimension(20,0)));


			JPanel miscPanel = new JPanel();
			miscPanel.setBackground(Color.BLACK);
			miscPanel.add(noteButtonPanel);
			miscPanel.add(nightTimePreviewPanel);

			JPanel moveMapPanel = new JPanel();
			moveMapPanel.setBackground(Color.BLACK);
			moveMapUpButton = new JButton("Move Up");
			moveMapUpButton.addActionListener(this);
			moveMapUpButton.setFocusable(false);
			moveMapDownButton = new JButton("Move Down");
			moveMapDownButton.addActionListener(this);
			moveMapDownButton.setFocusable(false);
			moveMapPanel.add(moveMapUpButton);
			moveMapPanel.add(moveMapDownButton);

			miscPanel.add(moveMapPanel);




			rootLayerControlsPanel = new JPanel();
			rootLayerControlsPanel.setLayout(new BoxLayout(rootLayerControlsPanel,BoxLayout.PAGE_AXIS));

			rootLayerControlsPanel.add(mapPropertiesPanel);
			rootLayerControlsPanel.add(miscPanel);
			rootLayerControlsPanel.setBackground(Color.BLACK);





			rootLayerControlsPanel.add(layerPanel[MapData.MAP_AREA_LAYER]);//action
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_HIT_LAYER]);//hit
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_CAMERA_BOUNDS_LAYER]);//fx
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_LIGHT_LAYER]);//lights
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_LIGHT_MASK_LAYER]);//lights
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_SPRITE_SHADOW_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_ABOVE_DETAIL_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_ABOVE_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_DOOR_LAYER]);//doors
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_ENTITY_LAYER]);//sprites
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_OBJECT_SHADOW_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_OBJECT_DETAIL_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_OBJECT_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_GROUND_SHADOW_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_SHADER_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_GROUND_DETAIL_LAYER]);
			rootLayerControlsPanel.add(layerPanel[MapData.MAP_GROUND_LAYER]);

			//-----------------------------


			JPanel allLayersPanel = new JPanel();
			allLayersLabel = new JLabel("All Layers [a]", JLabel.CENTER);
			allLayersLabel.setFont(new Font("Tahoma", Font.BOLD, 16));
			allLayersLabel.setForeground(Color.GRAY);

			allLayersPanel.add(allLayersLabel);
			allLayersPanel.setBackground(Color.BLACK);



			rootLayerControlsPanel.add(allLayersPanel);



			add(rootLayerControlsPanel, BorderLayout.SOUTH);




		//-----------------------------
		//turn off ground shader, camera bounds, and hit by default
		//-----------------------------




		//showLayerCheckbox[MapData.SHADER_LAYER].setSelected(false);//turn off ground shader
		selectLayerButton[MapData.MAP_SHADER_LAYER].setForeground(disabledLayerButtonLabel);
		selectLayerButton[MapData.MAP_SHADER_LAYER].setBackground(disabledLayerButtonBackground);
		layerPanel[MapData.MAP_SHADER_LAYER].setBackground(disabledLayerPanelBackground);

		//showLayerCheckbox[Map.CAMERA_BOUNDS_LAYER].setSelected(false);//turn off camera bounds
		selectLayerButton[MapData.MAP_CAMERA_BOUNDS_LAYER].setForeground(disabledLayerButtonLabel);
		selectLayerButton[MapData.MAP_CAMERA_BOUNDS_LAYER].setBackground(disabledLayerButtonBackground);
		layerPanel[MapData.MAP_CAMERA_BOUNDS_LAYER].setBackground(disabledLayerPanelBackground);

		//showLayerCheckbox[Map.HIT_LAYER].setSelected(false);//turn off hit bounds
		selectLayerButton[MapData.MAP_HIT_LAYER].setForeground(disabledLayerButtonLabel);
		selectLayerButton[MapData.MAP_HIT_LAYER].setBackground(disabledLayerButtonBackground);
		layerPanel[MapData.MAP_HIT_LAYER].setBackground(disabledLayerPanelBackground);

		//showLayerCheckbox[Map.LIGHT_MASK_LAYER].setSelected(false);//turn off light mask
		selectLayerButton[MapData.MAP_LIGHT_MASK_LAYER].setForeground(disabledLayerButtonLabel);
		selectLayerButton[MapData.MAP_LIGHT_MASK_LAYER].setBackground(disabledLayerButtonBackground);
		layerPanel[MapData.MAP_LIGHT_MASK_LAYER].setBackground(disabledLayerPanelBackground);


		//select layer 0

		selectLayerButton[0].setForeground(selectedLayerButtonBackground);
		selectLayerButton[0].setBackground(selectedLayerButtonLabel);//bgc[0]);
		layerPanel[0].setBackground(selectedLayerPanelBackground);




		//addMouseWheelListener(E);//bob9-23-05

	}



Color selectedLayerButtonBackground = Color.green;
Color selectedLayerButtonLabel = Color.green;
Color selectedLayerPanelBackground = Color.green;

Color disabledSelectedLayerButtonBackground = Color.red;
Color disabledSelectedLayerButtonLabel = Color.red;
Color disabledSelectedLayerPanelBackground = Color.red;

Color disabledLayerButtonBackground = Color.gray;
Color disabledLayerButtonLabel = Color.LIGHT_GRAY;
Color disabledLayerPanelBackground = Color.gray;

Color unselectedLayerButtonBackground = Color.black;
Color unselectedLayerButtonLabel = Color.black;
Color unselectedLayerPanelBackground = Color.black;


	//===============================================================================================
	public void setSelectedLayerIfEnabled(int layer)
	{//===============================================================================================



		if(showLayerCheckbox[layer].isSelected())
		{

			//set the previously selected button colors
			if(showLayerCheckbox[MapCanvas.selectedLayer].isSelected())
			{
				//set it to normal unselected colors
				selectLayerButton[MapCanvas.selectedLayer].setBackground(unselectedLayerButtonBackground);
				selectLayerButton[MapCanvas.selectedLayer].setForeground(unselectedLayerButtonLabel);
				layerPanel[MapCanvas.selectedLayer].setBackground(unselectedLayerPanelBackground);
			}
			else
			{
				//set it to unselected and disabled
				selectLayerButton[MapCanvas.selectedLayer].setBackground(disabledLayerButtonBackground);
				selectLayerButton[MapCanvas.selectedLayer].setForeground(disabledLayerButtonLabel);
				layerPanel[MapCanvas.selectedLayer].setBackground(disabledLayerPanelBackground);
			}



			//set the newly selected button colors
			selectLayerButton[layer].setBackground(selectedLayerButtonBackground);//bgc[layer]);
			selectLayerButton[layer].setForeground(selectedLayerButtonLabel);
			layerPanel[layer].setBackground(selectedLayerPanelBackground);

			MapCanvas.selectedLayer=layer;


			EditorMain.mapCanvas.repaint();
		}

	}


	//===============================================================================================
	public void notifyLayerTurnedOnOrOff(int layer)
	{//===============================================================================================


		if(showLayerCheckbox[layer].isSelected())
		{
			//set the new button colors to normal from being disabled
			selectLayerButton[layer].setForeground(unselectedLayerButtonBackground);
			selectLayerButton[layer].setBackground(unselectedLayerButtonLabel);
			layerPanel[layer].setBackground(unselectedLayerPanelBackground);


			EditorMain.infoLabel.setTextSuccess("Layer "+layer+" ("+layerLabel[layer].getText()+") Turned On");

			//if we've selected this layer too, set it to selected colors
			if(layer==MapCanvas.selectedLayer)
			{
				selectLayerButton[MapCanvas.selectedLayer].setBackground(selectedLayerButtonBackground);//bgc[E.mapCanvas.selectedLayer]);
				selectLayerButton[MapCanvas.selectedLayer].setForeground(selectedLayerButtonLabel);
				layerPanel[MapCanvas.selectedLayer].setBackground(selectedLayerPanelBackground);
			}
		}
		else
		{

			selectLayerButton[layer].setForeground(disabledLayerButtonLabel);
			selectLayerButton[layer].setBackground(disabledLayerButtonBackground);
			layerPanel[layer].setBackground(disabledLayerPanelBackground);

			EditorMain.infoLabel.setText("Layer "+layer+" ("+layerLabel[layer].getText()+") Turned Off");

			if(layer==MapCanvas.selectedLayer)
			{
				selectLayerButton[MapCanvas.selectedLayer].setBackground(disabledSelectedLayerButtonBackground);//bgc[E.mapCanvas.selectedLayer]);
				selectLayerButton[MapCanvas.selectedLayer].setForeground(disabledSelectedLayerButtonLabel);
				layerPanel[MapCanvas.selectedLayer].setBackground(disabledSelectedLayerPanelBackground);
			}
		}
	}

	//===============================================================================================
	public void toggleLayerCheckbox(int layer)
	{//===============================================================================================

		showLayerCheckbox[layer].setSelected(!showLayerCheckbox[layer].isSelected());

		itemStateChanged(null);
		notifyLayerTurnedOnOrOff(layer);

	}

	//===============================================================================================
	public void toggleSoloLayerCheckbox(int layer)
	{//===============================================================================================

		if(showLayerCheckbox[layer].isSelected()==true)
		{
			//turn all over layer checkboxes on
			for(int n=0;n<MapData.layers;n++)showLayerCheckbox[n].setSelected(true);

			showLayerCheckbox[layer].setSelected(false);
		}
		else
		{
			//turn all over layer checkboxes off
			for(int n=0;n<MapData.layers;n++)showLayerCheckbox[n].setSelected(false);

			showLayerCheckbox[layer].setSelected(true);
		}



		itemStateChanged(null);
		notifyLayerTurnedOnOrOff(layer);

	}


	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		for(int l=0;l<MapData.layers;l++)
		if(ae.getSource() == selectLayerButton[l])setSelectedLayerIfEnabled(l);

		if(ae.getSource() == openNoteEditorButton)
		{
			noteEditor.openNoteEditor();

		}

		if(ae.getSource() == openMapPropertiesEditorButton)
		{
			mapPropertiesWindow.showMapPropertiesWindow();
		}

		if(ae.getSource() == moveMapUpButton)
		{
			if(E.project_loaded && E.mapCanvas.getMap() != null) {
				E.mapCanvas.getMap().shiftMap(0, -1);
				E.mapCanvas.repaint();
			}
		}

		if(ae.getSource() == moveMapDownButton)
		{
			if(E.project_loaded && E.mapCanvas.getMap() != null) {
				E.mapCanvas.getMap().shiftMap(0, 1);
				E.mapCanvas.repaint();
			}
		}


	}

	//===============================================================================================
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================

		if(ie != null)
		if(ie.getSource() == nightTimePreviewCheckbox)
		{
			MapCanvas.nightTimePreview = !MapCanvas.nightTimePreview;

		}
		//if we're using a buffer, we should only have to draw the layers into mapcanvasimage
		if(EditorMain.mapCanvas.useLayerImageBuffer==true)
		{
			EditorMain.mapCanvas.drawBufferedLayerImagesIntoMapCanvasImage();
			EditorMain.mapCanvas.repaint();
		}

		//if we're not using a buffer, we need to redraw everything from the ground up
		if(EditorMain.mapCanvas.useLayerImageBuffer==false)
		{
			EditorMain.mapCanvas.updateAndRepaintAllLayerImagesIntoMapCanvasImageAndRepaintMapCanvas();
		}

		if(ie != null)
		{
			for(int l=0;l<MapData.layers;l++)
			if(ie.getSource() == showLayerCheckbox[l])notifyLayerTurnedOnOrOff(l);
		}

	}




}
