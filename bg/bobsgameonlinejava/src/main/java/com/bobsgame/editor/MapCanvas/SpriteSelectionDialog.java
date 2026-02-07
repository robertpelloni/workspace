package com.bobsgame.editor.MapCanvas;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.ImageObserver;
import java.util.Enumeration;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Project;
//===============================================================================================
public class SpriteSelectionDialog extends JDialog implements KeyListener, ActionListener, ItemListener, ImageObserver, WindowListener, CaretListener, ListSelectionListener
{//===============================================================================================
	EditorMain E;

	JPanel previewPanel;

	JList<String> spriteList;
	DefaultListModel<String> spriteListModel;

	JButton okButton, upButton, downButton, upTenButton, downTenButton;


	JCheckBox showNPCsCheckbox;

	JTextField filterTextField;

	boolean isDoorList = false;

	String lastFilterString = "";


	//===============================================================================================
	public SpriteSelectionDialog(Frame owner, String title, EditorMain e, boolean isDoorSelection)
	{//===============================================================================================
		super(owner, title, true);

		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		E=e;

		isDoorList = isDoorSelection;


		previewPanel = new JPanel();

		JPanel spriteListPanel = new JPanel(new BorderLayout());


		JPanel upDownButtonPanel = new JPanel();

		upButton = new JButton("Up");
		upButton.addActionListener(this);

		downButton = new JButton("Down");
		downButton.addActionListener(this);

		upTenButton = new JButton("Up Ten");
		upTenButton.addActionListener(this);

		downTenButton = new JButton("Down Ten");
		downTenButton.addActionListener(this);

		upDownButtonPanel.add(upButton);
		upDownButtonPanel.add(downButton);

		upDownButtonPanel.add(upTenButton);
		upDownButtonPanel.add(downTenButton);


		JPanel filterPanel = new JPanel();

		JLabel filterLabel = new JLabel("Filter");
		filterTextField = new JTextField(10);
		filterTextField.addCaretListener(this);
		filterPanel.add(filterLabel);
		filterPanel.add(filterTextField);

		upDownButtonPanel.add(filterPanel);


		spriteListPanel.add(upDownButtonPanel, BorderLayout.SOUTH);




		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);
		spriteListModel = new DefaultListModel<String>();
		spriteList = new JList<String>(spriteListModel); //data has type Object
		spriteList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		spriteList.setLayoutOrientation(JList.VERTICAL);
		spriteList.setVisibleRowCount(100);
		spriteList.setForeground(Color.BLACK);
		spriteList.setFont(listFont);
		spriteList.setFixedCellHeight(16);
		spriteList.addListSelectionListener(this);
		JScrollPane spriteListScroller = new JScrollPane(spriteList);


		spriteListPanel.add(spriteListScroller,BorderLayout.CENTER);






		JPanel bottomPanel = new JPanel();

		okButton = new JButton("OK");
		okButton.addActionListener(this);


		if(isDoorList==false)
		{
			JLabel showNPCsLabel = new JLabel("NPCs");

			showNPCsCheckbox = new JCheckBox();
			showNPCsCheckbox.setSelected(false);
			showNPCsCheckbox.addItemListener(this);

			bottomPanel.add(showNPCsLabel);
			bottomPanel.add(showNPCsCheckbox);
		}


		bottomPanel.add(okButton);




		setLayout(new BorderLayout());

		add(spriteListPanel,BorderLayout.WEST);
		add(previewPanel,BorderLayout.CENTER);
		add(bottomPanel,BorderLayout.SOUTH);



		setSize(1000, 770);
		setLocation(20, 800);

		previewPanel.addKeyListener(this);
		spriteList.addKeyListener(this);
		okButton.addKeyListener(this);

		populateList();

		addWindowListener(this);

	}

	//===============================================================================================
	public void populateList()
	{//===============================================================================================

		if(isDoorList==true)
		{
			Object selectedObject = spriteList.getSelectedValue();

			spriteListModel.removeAllElements();


			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(Project.getSprite(i).name().startsWith("DoorLeft"))
				if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
				spriteListModel.addElement(Project.getSprite(i).name());
			}
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(Project.getSprite(i).name().startsWith("DoorRight"))
				if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
				spriteListModel.addElement(Project.getSprite(i).name());
			}
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(Project.getSprite(i).name().startsWith("DoorUp"))
				if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
				spriteListModel.addElement(Project.getSprite(i).name());
			}
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(Project.getSprite(i).name().startsWith("DoorDown"))
				if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
				spriteListModel.addElement(Project.getSprite(i).name());
			}
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(
						Project.getSprite(i).name().startsWith("Door")&&
						!Project.getSprite(i).name().startsWith("DoorLeft")&&
						!Project.getSprite(i).name().startsWith("DoorRight")&&
						!Project.getSprite(i).name().startsWith("DoorUp")&&
						!Project.getSprite(i).name().startsWith("DoorDown")
					)
					if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
					spriteListModel.addElement(Project.getSprite(i).name());
			}



			if(selectedObject!=null)
			{
				Enumeration<String> en = spriteListModel.elements();
				for(int i=0;en.hasMoreElements();i++)
				{
					if(selectedObject.equals(en.nextElement())){spriteList.setSelectedIndex(i);break;}
				}
			}


			spriteList.setEnabled(true);

			if(spriteListModel.getSize()==0)spriteListModel.addElement("No Sprites start with \"Door\"!");
			//else itemStateChanged(new ItemEvent(spriteList, ItemEvent.ITEM_STATE_CHANGED, "yay", ItemEvent.SELECTED));


		}
		else
		{
			Object selectedObject = spriteList.getSelectedValue();
			spriteListModel.removeAllElements();
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				//only add sprites that don't start with door
				if(Project.getSprite(i).name().startsWith("Door")==false)
				if(filterTextField.getText().length()==0||Project.getSprite(i).name().contains((CharSequence)filterTextField.getText())==true)
				{
					if(showNPCsCheckbox.isSelected()==true)
					{
						if(Project.getSprite(i).isNPC()==true)
						{
							spriteListModel.addElement(Project.getSprite(i).name());
						}
					}
					else
					{
						if(Project.getSprite(i).isNPC()==false)
						{
							spriteListModel.addElement(Project.getSprite(i).name());
						}
					}
				}
			}



			if(selectedObject!=null)
			{

				Enumeration<String> en = spriteListModel.elements();
				for(int i=0;en.hasMoreElements();i++)
				{
					if(selectedObject.equals(en.nextElement())){spriteList.setSelectedIndex(i);break;}
				}
			}

			spriteList.setEnabled(true);
		}

	}
	//===============================================================================================
	public void filterList()
	{//===============================================================================================

		if(filterTextField.getText().length()>0)
		{
			//String[] items = spriteList.getItems();
			for(int i=0;i < spriteListModel.getSize();i++)
			{
				if(spriteListModel.getElementAt(i).toLowerCase().contains((CharSequence)filterTextField.getText().toLowerCase())==false){spriteListModel.remove(i);i--;}
			}
		}
	}

	//===============================================================================================
	public void show(String name)
	{//===============================================================================================

		setVisible(true);
	}

	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent ke)
	{//===============================================================================================

		if(ke.getKeyCode() == KeyEvent.VK_ENTER)
		{
			setVisible(false);
		}
	}
	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================

		if(ae.getSource() == okButton)
		{
			setVisible(false);
		}

		if(ae.getSource() == upButton)
		{
			moveSpriteUp();
		}

		if(ae.getSource() == downButton)
		{
			moveSpriteDown();
		}

		if(ae.getSource() == upTenButton)
		{


			for(int t=0;t<10;t++)
			{
				moveSpriteUp();
			}
		}

		if(ae.getSource() == downTenButton)
		{

			for(int t=0;t<10;t++)
			{
				moveSpriteDown();

			}
		}

	}
	//===============================================================================================
	public void moveSpriteUp()
	{//===============================================================================================

		String selected = spriteList.getSelectedValue();
		int selectedIndex = spriteList.getSelectedIndex();

		if(selected!=null&&selectedIndex>0)
		{
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(selected.equals(Project.getSprite(i).name()))
				{
					Project.setSelectedSpriteIndex(i);

					if(i==1||i==Project.getNumSprites()-1)Project.moveSpriteUp();
					else
					while(Project.getSprite(Project.getSelectedSpriteIndex()+1).name().equals(spriteListModel.getElementAt(selectedIndex-1))==false)Project.moveSpriteUp();

					spriteListModel.remove(selectedIndex);
					spriteListModel.add(selectedIndex-1,selected);
					spriteList.setSelectedIndex(selectedIndex-1);
					break;
				}
			}
		}
	}
	//===============================================================================================
	public void moveSpriteDown()
	{//===============================================================================================

		String selected = spriteList.getSelectedValue();
		int selectedIndex = spriteList.getSelectedIndex();

		if(selected!=null&&selectedIndex<spriteListModel.getSize()-1)
		{
			for(int i = 0; i < Project.getNumSprites(); i++)
			{
				if(selected.equals(Project.getSprite(i).name()))
				{
					Project.setSelectedSpriteIndex(i);

					if(i==0||i==Project.getNumSprites()-2)Project.moveSpriteDown();
					else
					while(Project.getSprite(Project.getSelectedSpriteIndex()-1).name().equals(spriteListModel.getElementAt(selectedIndex+1))==false)Project.moveSpriteDown();

					spriteListModel.remove(selectedIndex);
					spriteListModel.add(selectedIndex+1, selected);
					spriteList.setSelectedIndex(selectedIndex+1);
					break;

				}
			}
		}
	}

	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent ie)
	{//===============================================================================================


		if(ie.getSource() == showNPCsCheckbox)
		{
			populateList();
		}



	}

	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================
		if(e.getSource() == spriteList)
		{

			//repaint panel with selected sprite
			Graphics G = previewPanel.getGraphics();

			G.setColor(Color.WHITE);
			G.fillRect(0, 0, previewPanel.getWidth(), previewPanel.getHeight());

			String selected = spriteList.getSelectedValue();
			if(selected!=null)
			{
				for(int i = 0; i < Project.getNumSprites(); i++)
				{
					if(selected.equals(Project.getSprite(i).name()))
					{
						G.drawImage(Project.getSprite(i).getFrameImage(0), 0,0,Project.getSprite(i).wP()*4,Project.getSprite(i).hP()*4,this);
						break;
					}
				}
			}


		}

	}





	//===============================================================================================
	@Override
	public void windowOpened(WindowEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void windowClosing(WindowEvent e)
	{//===============================================================================================
		setVisible(false);

	}
	//===============================================================================================
	@Override
	public void windowClosed(WindowEvent e)
	{//===============================================================================================
		setVisible(false);

	}
	//===============================================================================================
	@Override
	public void windowIconified(WindowEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void windowDeiconified(WindowEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void windowActivated(WindowEvent e)
	{//===============================================================================================


	}
	//===============================================================================================
	@Override
	public void windowDeactivated(WindowEvent e)
	{//===============================================================================================


	}

	@Override
	public void caretUpdate(CaretEvent e)
	{

		if(e.getSource()==filterTextField)
		{

			if(filterTextField.getText().length()>lastFilterString.length())
			{
				lastFilterString=filterTextField.getText();
				filterList();

			}
			else
			{
				lastFilterString=filterTextField.getText();
				populateList();

			}


		}
	}


}
