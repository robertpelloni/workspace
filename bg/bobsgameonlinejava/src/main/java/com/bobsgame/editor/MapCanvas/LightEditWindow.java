package com.bobsgame.editor.MapCanvas;

import java.awt.BorderLayout;


import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;

import java.awt.event.ActionEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.util.Enumeration;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.ControlPanel.ColorWindow;
import com.bobsgame.editor.Project.GameObject;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.shared.MapData;


//===============================================================================================
public class LightEditWindow extends ColorWindow implements ItemListener, ListSelectionListener, CaretListener
{//===============================================================================================


	JTextField alphaTextField,radiusTextField,widthTextField,heightTextField,nameTextField,blendFalloffTextField,decayExponentTextField,focusRadiusTextField;
	JLabel alphaLabel,radiusLabel,widthLabel,heightLabel,nameLabel,blendFalloffLabel,decayExponentLabel, focusRadiusLabel, isDayLightLabel, isNightLightLabel, flickersLabel, changesColorLabel, toggleableLabel, commentLabel;
	JPanel lightPanel,dayNightPanel, optionsPanel, commentsPanel;

	JCheckBox isDayLightCheckbox, isNightLightCheckbox, flickersCheckbox, changesColorCheckbox, toggleableCheckbox;
	JTextField commentTextField;


	JLabel flickerOnTimeLabel, flickerOffTimeLabel, flickerRandomOnTimeLabel, flickerRandomOffTimeLabel;
	JTextField flickerOnTimeTextField, flickerOffTimeTextField;
	JCheckBox flickerRandomOnTimeCheckbox, flickerRandomOffTimeCheckbox;
	JPanel flickerOptionsPanel;


	EditorMain E;
	int mapX = -1;
	int mapY = -1;
	int width = -1;
	int height = -1;
	int a=127;
	int radius=50;
	String name="Light";
	float blendFalloff=2.0f;
	float decayExponent=1.0f;
	int focusRadius=0;
	boolean isDayLight=true;
	boolean isNightLight=true;

	boolean flickers=false;
	boolean changesColor=false;
	boolean toggleable=false;


	int toggleX = -1;
	int toggleY = -1;

	int flickerOnTime = 0;
	int flickerOffTime = 0;
	boolean flickerRandomUpToOnTime = false;
	boolean flickerRandomUpToOffTime = false;



	String comment = "";

	int editingLightIndex = -1;



	JList<Light> lightList;
	DefaultListModel<Light> lightListModel;

	//===============================================================================================
	public LightEditWindow(EditorMain e)
	{//===============================================================================================
		super("Create Map Light");
		E = e;

		build();

		r=255;
		g=255;
		b=200;


		alphaTextField = new JTextField(4);
		radiusTextField = new JTextField(4);
		widthTextField = new JTextField(4);
		heightTextField = new JTextField(4);

		nameTextField = new JTextField(20);
		nameTextField.addCaretListener(this);
		nameTextField.addKeyListener(this);
		nameTextField.setForeground(Color.GRAY);

		blendFalloffTextField = new JTextField(4);
		decayExponentTextField = new JTextField(4);
		focusRadiusTextField = new JTextField(4);

		alphaLabel = new JLabel("A", JLabel.CENTER);
		alphaLabel.setFont(new Font("Arial", Font.BOLD, 12));
		alphaLabel.setForeground(Color.WHITE);
		//alphaLabel.setBackground(Color.BLACK);

		radiusLabel = new JLabel("Radius");
		widthLabel = new JLabel("Width");
		heightLabel = new JLabel("Height");

		nameLabel = new JLabel("Name");
		blendFalloffLabel = new JLabel("Blend Falloff");
		decayExponentLabel = new JLabel("Decay Exponent");
		focusRadiusLabel = new JLabel("Focus Radius");

		rgbTextFieldPanel.add(alphaLabel);
		rgbTextFieldPanel.add(alphaTextField);


		lightPanel = new JPanel(new FlowLayout());
		lightPanel.setBorder(EditorMain.border);

		rgbTextFieldPanel.add(radiusLabel);
		rgbTextFieldPanel.add(radiusTextField);


		lightPanel.add(blendFalloffLabel);
		lightPanel.add(blendFalloffTextField);

		lightPanel.add(decayExponentLabel);
		lightPanel.add(decayExponentTextField);

		lightPanel.add(focusRadiusLabel);
		lightPanel.add(focusRadiusTextField);


		JPanel dayLightPanel = new JPanel();
		dayLightPanel.setBackground(new Color(200,200,255));
		isDayLightLabel = new JLabel("On During Day");
		isDayLightCheckbox = new JCheckBox();
		isDayLightCheckbox.addItemListener(this);
		isDayLightCheckbox.setSelected(true);
		dayLightPanel.add(isDayLightLabel);
		dayLightPanel.add(isDayLightCheckbox);



		JPanel nightLightPanel = new JPanel();
		nightLightPanel.setBackground(new Color(0,0,63));
		isNightLightLabel = new JLabel("On At Night");
		isNightLightLabel.setForeground(Color.YELLOW);
		isNightLightCheckbox = new JCheckBox();
		isNightLightCheckbox.addItemListener(this);
		isNightLightCheckbox.setSelected(false);
		nightLightPanel.add(isNightLightLabel);
		nightLightPanel.add(isNightLightCheckbox);



		dayNightPanel = new JPanel(new FlowLayout());
		dayNightPanel.setBorder(EditorMain.border);
		dayNightPanel.add(dayLightPanel);
		dayNightPanel.add(nightLightPanel);

		commentLabel = new JLabel("Comments");
		commentTextField = new JTextField(20);


		dayNightPanel.add(commentLabel);
		dayNightPanel.add(commentTextField);






		JPanel flickersPanel = new JPanel();
		flickersLabel = new JLabel("Flickers?");
		flickersCheckbox = new JCheckBox();
		flickersCheckbox.addItemListener(this);
		flickersCheckbox.setSelected(false);
		flickersPanel.add(flickersLabel);
		flickersPanel.add(flickersCheckbox);



		JPanel flickerOnTimePanel = new JPanel();
		flickerOnTimeLabel = new JLabel("On Ticks:");
		flickerOnTimeTextField = new JTextField(5);
		flickerOnTimePanel.add(flickerOnTimeLabel);
		flickerOnTimePanel.add(flickerOnTimeTextField);

		JPanel flickerOffTimePanel = new JPanel();
		flickerOffTimeLabel = new JLabel("Off Ticks:");
		flickerOffTimeTextField = new JTextField(5);
		flickerOffTimePanel.add(flickerOffTimeLabel);
		flickerOffTimePanel.add(flickerOffTimeTextField);

		JPanel flickerRandomOnTimePanel = new JPanel();
		flickerRandomOnTimeLabel = new JLabel("Random % On Ticks?");
		flickerRandomOnTimeCheckbox = new JCheckBox();
		flickerRandomOnTimeCheckbox.addItemListener(this);
		flickerRandomOnTimeCheckbox.setSelected(false);
		flickerRandomOnTimePanel.add(flickerRandomOnTimeLabel);
		flickerRandomOnTimePanel.add(flickerRandomOnTimeCheckbox);

		JPanel flickerRandomOffTimePanel = new JPanel();
		flickerRandomOffTimeLabel = new JLabel("Random % Off Ticks?");
		flickerRandomOffTimeCheckbox = new JCheckBox();
		flickerRandomOffTimeCheckbox.addItemListener(this);
		flickerRandomOffTimeCheckbox.setSelected(false);
		flickerRandomOffTimePanel.add(flickerRandomOffTimeLabel);
		flickerRandomOffTimePanel.add(flickerRandomOffTimeCheckbox);

		flickerOptionsPanel = new JPanel(new FlowLayout());

		flickerOptionsPanel.setBorder(EditorMain.border);
		flickerOptionsPanel.add(flickerOnTimePanel);
		flickerOptionsPanel.add(flickerOffTimePanel);
		flickerOptionsPanel.add(flickerRandomOnTimePanel);
		flickerOptionsPanel.add(flickerRandomOffTimePanel);





		JPanel changesColorPanel = new JPanel();
		changesColorLabel = new JLabel("Changes Color?");
		changesColorCheckbox = new JCheckBox();
		changesColorCheckbox.addItemListener(this);
		changesColorCheckbox.setSelected(false);
		changesColorPanel.add(changesColorLabel);
		changesColorPanel.add(changesColorCheckbox);

		JPanel toggleablePanel = new JPanel();
		toggleableLabel = new JLabel("Toggleable?");
		toggleableCheckbox = new JCheckBox();
		toggleableCheckbox.addItemListener(this);
		toggleableCheckbox.setSelected(false);
		toggleablePanel.add(toggleableLabel);
		toggleablePanel.add(toggleableCheckbox);

		optionsPanel = new JPanel(new FlowLayout());
		optionsPanel.setBorder(EditorMain.border);
		optionsPanel.add(flickersPanel);
		optionsPanel.add(changesColorPanel);
		optionsPanel.add(toggleablePanel);




		buttonPanel.remove(applyButton);
		buttonPanel.remove(okButton);

		buttonPanel.add(nameLabel);
		buttonPanel.add(nameTextField);

		buttonPanel.add(widthLabel);
		buttonPanel.add(widthTextField);

		buttonPanel.add(heightLabel);
		buttonPanel.add(heightTextField);

		buttonPanel.add(okButton);
		buttonPanel.setBorder(EditorMain.border);

		rootPanel.remove(buttonPanel);
		rootPanel.add(lightPanel);
		rootPanel.add(dayNightPanel);
		rootPanel.add(optionsPanel);
		rootPanel.add(flickerOptionsPanel);

		rootPanel.add(buttonPanel);
		rootPanel.setBorder(EditorMain.border);



		JPanel centerPanel = new JPanel(new BorderLayout());
		remove(rootPanel);
		remove(cGrid);

		centerPanel.add(rootPanel,BorderLayout.NORTH);
		centerPanel.add(cGrid,BorderLayout.CENTER);
		add(centerPanel,BorderLayout.CENTER);







		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);
		lightListModel = new DefaultListModel<Light>();
		lightList = new JList<Light>(lightListModel); //data has type Object
		lightList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		lightList.setLayoutOrientation(JList.VERTICAL);
		lightList.setVisibleRowCount(10);
		lightList.setForeground(Color.BLACK);
		lightList.setFont(listFont);
		lightList.setFixedCellHeight(16);
		lightList.addListSelectionListener(this);
		lightList.setCellRenderer(new NameCellRenderer());
		lightList.setFocusable(false);
		JScrollPane lightListScroller = new JScrollPane(lightList);
		lightListScroller.setBorder(EditorMain.border);
		lightListScroller.setFocusable(false);

		JPanel lightListPanel = new JPanel();
		lightListPanel.setLayout(new BoxLayout(lightListPanel,BoxLayout.Y_AXIS));
		lightListPanel.add(Box.createRigidArea(new Dimension(100,0)));
		lightListPanel.add(lightListScroller);


		add(lightListPanel,BorderLayout.WEST);





		setSize(512+10+200, 815+200);
		setLocation(800, 400);

		setResizable(true);


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
	public void showLightWindow(int pX, int pY, int w, int h)
	{//===============================================================================================

		Light l = new Light(getMap(),getMap().getSelectedState());

		l.setNameNoRename(getMap().createUniqueLightName("Light", -1));

		getMap().addLight(l);

		editingLightIndex = getMap().getNumLights()-1;

		//getMap().getLight(editingLightIndex).map = getMap(); //set the internal map, since this is a new light. //this isn't really used anywhere except in renaming the light from inside itself, so it knows which other lights to compare to.

		mapX = pX;
		mapY = pY;
		width = w+(w%2);
		height = h+(h%2);

		toggleX = -1;
		toggleY = -1;


		//these should remain set from the previous light when creating a new one

		//r
		//g
		//b
		//a
		//radius
		//blendFalloff
		//decayExponent
		//focusRadius
		//isDayLight = true;
		//isNightLight = true;
		//flickers=false;
		//changesColor=false;
		//toggleable=false;
		//flickerOnTime = 0;
		//flickerOffTime = 0;
		//flickerRandomUpToOnTime = false;
		//flickerRandomUpToOffTime = false;

		name = l.name();
		comment = "";

		updateFieldsFromVars();
		updateSelectedLightFromVars();

		//repaintLight();

		refreshLightList();


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}

		nameTextField.setForeground(Color.GRAY);
	}



	//===============================================================================================
	public void showLightWindow()
	{//===============================================================================================

		editingLightIndex = getMap().getSelectedLightIndex();

		updateVarsFromSelectedLight();

		updateFieldsFromVars();

		refreshLightList();

		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}

		nameTextField.setForeground(Color.GRAY);
	}



	//===============================================================================================
	public void refreshLightList()
	{//===============================================================================================

		lightListModel.removeAllElements();

		for(int i=0;i<getMap().getNumLights();i++)
		{
			lightListModel.addElement(getMap().getLight(i));
		}

		//if(editingLightIndex==getMap().getNumLights()-1)
		//{
			//lightListModel.addElement("Light"+editingLightIndex);
		//}

		lightList.setSelectedIndex(editingLightIndex);

	}

	//===============================================================================================
	public void updateVarsFromSelectedLight()
	{//===============================================================================================
		Light l = getMap().getLight(editingLightIndex);

		mapX = l.xP();
		mapY = l.yP();
		width = l.wP();
		height = l.hP();

		r = l.redColorByte();
		g = l.greenColorByte();
		b = l.blueColorByte();
		a = l.alphaColorByte();
		radius = l.radiusPixels1X();
		blendFalloff = l.blendFalloff();
		decayExponent = l.decayExponent();
		focusRadius = l.focusRadiusPixels1X();


		isDayLight=l.isDayLight();
		isNightLight=l.isNightLight();

		flickers = l.flickers();
		changesColor = l.changesColor();
		toggleable = l.toggleable();

		toggleX = l.toggleXPixels1X();
		toggleY = l.toggleYPixels1X();

		flickerOnTime = l.flickerOnTicks();
		flickerOffTime = l.flickerOffTicks();
		flickerRandomUpToOnTime = l.flickerRandomUpToOnTicks();
		flickerRandomUpToOffTime = l.flickerRandomUpToOffTicks();

		name = l.name();
		comment=l.comment();

	}

	//===============================================================================================
	public void updateFieldsFromVars()
	{//===============================================================================================

		if(redScrollbar.getValue() != r)redScrollbar.setValue(r);
		if(greenScrollbar.getValue() != g)greenScrollbar.setValue(g);
		if(blueScrollbar.getValue() != b)blueScrollbar.setValue(b);

		redTextField.setText(""+r);
		greenTextField.setText(""+g);
		blueTextField.setText(""+b);
		alphaTextField.setText(""+a);
		radiusTextField.setText(""+radius);
		widthTextField.setText(""+width);
		heightTextField.setText(""+height);


		blendFalloffTextField.setText(""+blendFalloff);
		decayExponentTextField.setText(""+decayExponent);
		focusRadiusTextField.setText(""+focusRadius);

		isDayLightCheckbox.setSelected(isDayLight);
		isNightLightCheckbox.setSelected(isNightLight);

		flickersCheckbox.setSelected(flickers);
		changesColorCheckbox.setSelected(changesColor);
		toggleableCheckbox.setSelected(toggleable);

		flickerOnTimeTextField.setText(""+flickerOnTime);
		flickerOffTimeTextField.setText(""+flickerOffTime);
		flickerRandomOnTimeCheckbox.setSelected(flickerRandomUpToOnTime);
		flickerRandomOffTimeCheckbox.setSelected(flickerRandomUpToOffTime);

		commentTextField.setText(""+comment);

		cGrid.repaintColorWheelBackground(b);

		nameTextField.setText(""+name);

	}

	//===============================================================================================
	public void updateVarsFromFields()
	{//===============================================================================================

		r = Integer.parseInt(redTextField.getText());
		g = Integer.parseInt(greenTextField.getText());
		b = Integer.parseInt(blueTextField.getText());
		a = Integer.parseInt(alphaTextField.getText());
		radius = Integer.parseInt(radiusTextField.getText());
		width = Integer.parseInt(widthTextField.getText());
		height = Integer.parseInt(heightTextField.getText());

		blendFalloff = Float.parseFloat(blendFalloffTextField.getText());
		decayExponent = Float.parseFloat(decayExponentTextField.getText());
		focusRadius = Integer.parseInt(focusRadiusTextField.getText());

		isDayLight = isDayLightCheckbox.isSelected();
		isNightLight = isNightLightCheckbox.isSelected();

		flickers = flickersCheckbox.isSelected();
		changesColor = changesColorCheckbox.isSelected();
		toggleable = toggleableCheckbox.isSelected();

		flickerOnTime = Integer.parseInt(flickerOnTimeTextField.getText());
		flickerOffTime = Integer.parseInt(flickerOffTimeTextField.getText());
		flickerRandomUpToOnTime = flickerRandomOnTimeCheckbox.isSelected();
		flickerRandomUpToOffTime = flickerRandomOffTimeCheckbox.isSelected();



		comment = commentTextField.getText();

		width+=width%2;
		height+=height%2;


		name = nameTextField.getText();
		if(name.length()==0)name = "Light";
		name = getMap().createUniqueLightName(name, editingLightIndex);
		//nameTextField.setText(name);


	}

	//===============================================================================================
	public void updateSelectedLightFromVars()
	{//===============================================================================================

		getMap().getLight(editingLightIndex).setName(getMap().createUniqueLightName(name, editingLightIndex));
		getMap().getLight(editingLightIndex).bufferedImage = null;
		getMap().getLight(editingLightIndex).setRedColorByte(r);
		getMap().getLight(editingLightIndex).setGreenColorByte(g);
		getMap().getLight(editingLightIndex).setBlueColorByte(b);
		getMap().getLight(editingLightIndex).setAlphaColorByte(a);
		getMap().getLight(editingLightIndex).setXPixels(mapX);
		getMap().getLight(editingLightIndex).setYPixels(mapY);
		getMap().getLight(editingLightIndex).setWidthPixels(width);
		getMap().getLight(editingLightIndex).setHeightPixels(height);
		getMap().getLight(editingLightIndex).setRadiusPixels(radius);
		getMap().getLight(editingLightIndex).setBlendFalloff(blendFalloff);
		getMap().getLight(editingLightIndex).setDecayExponent(decayExponent);
		getMap().getLight(editingLightIndex).setFocusRadiusPixels(focusRadius);
		getMap().getLight(editingLightIndex).setIsDayLight(isDayLight);
		getMap().getLight(editingLightIndex).setIsNightLight(isNightLight);

		getMap().getLight(editingLightIndex).setFlickers(flickers);
		getMap().getLight(editingLightIndex).setChangesColor(changesColor);
		getMap().getLight(editingLightIndex).setToggleable(toggleable);

		getMap().getLight(editingLightIndex).setToggleXPixels(toggleX);
		getMap().getLight(editingLightIndex).setToggleYPixels(toggleY);

		getMap().getLight(editingLightIndex).setFlickerOnTicks(flickerOnTime);
		getMap().getLight(editingLightIndex).setFlickerOffTicks(flickerOffTime);
		getMap().getLight(editingLightIndex).setFlickerRandomUpToOnTicks(flickerRandomUpToOnTime);
		getMap().getLight(editingLightIndex).setFlickerRandomUpToOffTicks(flickerRandomUpToOffTime);


		getMap().getLight(editingLightIndex).setComment(comment);

		//if(editingLightIndex==getMap().getNumLights()-1)getMap().getNumLights()++;


	}


	//===============================================================================================
	public void repaintLight()
	{//===============================================================================================
		//if buffered, need to update lights layer and redraw it into mapcanvasimage
		if(EditorMain.mapCanvas.useLayerImageBuffer==true)
		{
			getMap().updateLayerBufferImage(MapData.MAP_LIGHT_LAYER);
			EditorMain.mapCanvas.drawBufferedLayerImagesIntoMapCanvasImage();

			EditorMain.mapCanvas.repaint();
		}


		//if unbuffered, only need to paint the tiles that the light covers into the mapcanvasimage
		if(EditorMain.mapCanvas.useLayerImageBuffer==false)
		{
			int sx = (mapX-radius);
			int sy = (mapY-radius);
			int sw = ((radius*2)+width);
			int sh = ((radius*2)+height);

			for(int x=sx/8;x<((sx+sw)/8)+1;x++)
			for(int y=sy/8;y<((sy+sh)/8)+1;y++)
				EditorMain.mapCanvas.paintTileXY(MapData.MAP_LIGHT_LAYER,x,y);

			EditorMain.mapCanvas.repaint();
		}

	}

	//===============================================================================================
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================
		if(ae.getSource() == okButton)
		{

			updateVarsFromFields();
			updateSelectedLightFromVars();


			getMap().setSelectedLightIndex(editingLightIndex);

			editingLightIndex=-1;

			setVisible(false);

			repaintLight();

		}

	}

	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================

		if(ie.getSource() == toggleableCheckbox)
		{
			if(toggleableCheckbox.isSelected()==true)
			{
				toggleX = (mapX);
				toggleY = (mapY+height);
			}
		}



		if(ie.getSource().getClass().equals(JCheckBox.class))
		{
			if(((JCheckBox)ie.getSource()).isSelected()==true)((JCheckBox)ie.getSource()).setBackground(Color.GREEN);
			else ((JCheckBox)ie.getSource()).setBackground(Color.LIGHT_GRAY);
		}


	}


	//===============================================================================================
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================


		if(ke.getSource() == nameTextField && ke.getKeyCode() == KeyEvent.VK_ENTER)
		{

			nameTextField.setForeground(Color.GRAY);

			//get var name
			//String oldName = name;

			//find var name in name list


			if(editingLightIndex==-1)return;


			int selectedIndex = -1;

			Light l = getMap().getLight(editingLightIndex);


			Enumeration<Light> enm = lightListModel.elements();

			for(int i=0; enm.hasMoreElements(); i++)
			{
				Light temp = (Light) enm.nextElement();
				if(temp==l)
				{
					selectedIndex = i;
					break;
				}
			}

//			Object[] listNames = lightListModel.toArray();
//
//			for(int i=0;i<listNames.length;i++)
//			{
//				if(listNames[i].toString().equals(oldName))
//				{
//					selectedItem = i;
//					break;
//				}
//			}




			if(selectedIndex!=-1)
			{

				name = nameTextField.getText();
				if(name.length()==0)name = "Light";
				l.setName(getMap().createUniqueLightName(name, editingLightIndex));

				//update name to textFieldName
				lightListModel.add(selectedIndex,l);
				lightListModel.remove(selectedIndex+1);

				lightList.setSelectedIndex(selectedIndex);


				validate();
			}


			return;

		}


		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			actionPerformed(new ActionEvent(okButton,ActionEvent.ACTION_PERFORMED,""));
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_PAGE_UP)
		{
			if(lightList.getSelectedIndex()>0)lightList.setSelectedIndex(lightList.getSelectedIndex()-1);
			valueChanged(new ListSelectionEvent(lightList,0,lightListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(lightList,ItemEvent.ITEM_STATE_CHANGED,lightList.getSelectedItem(), ItemEvent.SELECTED));
		}
		else
		if(ke.getKeyCode() == KeyEvent.VK_PAGE_DOWN)
		{
			if(lightList.getSelectedIndex()>=0&&lightList.getSelectedIndex()<lightListModel.getSize()-1)lightList.setSelectedIndex(lightList.getSelectedIndex()+1);
			valueChanged(new ListSelectionEvent(lightList,0,lightListModel.size()-1, false));
			//itemStateChanged(new ItemEvent(lightList,ItemEvent.ITEM_STATE_CHANGED,lightList.getSelectedItem(), ItemEvent.SELECTED));
		}
		else
		super.keyPressed(ke);
	}

	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================

		if(e.getSource() == lightList)
		{

			if(e.getValueIsAdjusting()==true)return;

			if(lightList.getSelectedIndex()==editingLightIndex)return;

			if(lightList.getSelectedIndex()==-1)return;


			Light selected = lightList.getSelectedValue();
			if(selected!=null)
			{

				//save current light selection
				updateVarsFromFields();
				updateSelectedLightFromVars();
				repaintLight();


				lightList.ensureIndexIsVisible(lightList.getSelectedIndex());



				//go through map lights, find light with selected name, set selected light
				for(int i=0;i<getMap().getNumLights();i++)
				{
					if(getMap().getLight(i)==selected)
					{
						editingLightIndex = i;
						break;
					}
				}


				//refreshLightList();
				//lightList.setSelectedIndex(editingLightIndex);




				//refresh light info
				updateVarsFromSelectedLight();
				updateFieldsFromVars();


				//repaint mapcanvas, scroll mapcanvas to light.
				// center light on screen with scrolling
				getMap().setSelectedLightIndex(editingLightIndex);
				EditorMain.mapCanvas.scrollToTop(getMap().getLight(editingLightIndex));

				nameTextField.setForeground(Color.GRAY);

			}
		}
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
	class NameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		public NameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
				super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);
				setText((value == null) ? "" : ((GameObject)value).name());
				return this;
		}
	}

}
