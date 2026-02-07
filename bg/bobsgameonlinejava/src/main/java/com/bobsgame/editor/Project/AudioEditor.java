package com.bobsgame.editor.Project;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.ImageObserver;
import java.io.File;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.filechooser.FileFilter;

import org.apache.commons.io.FileUtils;


import com.bobsgame.EditorMain;
import com.bobsgame.editor.Project.Event.Music;
import com.bobsgame.editor.Project.Event.Sound;
import com.bobsgame.audio.AudioChannel;
import com.bobsgame.audio.AudioUtils;



//===============================================================================================
public class AudioEditor extends JFrame implements ActionListener, ItemListener, ImageObserver, KeyListener, ListSelectionListener, CaretListener
{//===============================================================================================


	JButton doneButton, cancelButton;



	JButton
	rescanDirectoriesButton,
	playStopMusicButton,
	playStopSoundButton,
	addMusicFileButton,
	addSoundFileButton,

	removeMusicFileButton,
	removeSoundFileButton

	;

	JTextField
	musicNameTextField,
	soundNameTextField,
	musicFileNameTextField,
	soundFileNameTextField

	;



	JPanel centerPanel;

	JList<Music> musicList;
	DefaultListModel<Music> musicListModel;
	JScrollPane musicListScroller;

	JCheckBox preloadMusicCheckbox;

	JList<Sound> soundList;
	DefaultListModel<Sound> soundListModel;
	JScrollPane soundListScroller;


	AudioChannel audioFile;

	public boolean musicIsPlaying=false;
	public boolean soundIsPlaying=false;


	public JFileChooser soundFileChooser;
	public JFileChooser musicFileChooser;

	//===============================================================================================
	public AudioEditor()
	{//===============================================================================================






		super("Audio Editor Window");
		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);



		soundFileChooser = new JFileChooser("F:\\source\\games\\bobsgame\\workspace\\_sfx");
		soundFileChooser.setMultiSelectionEnabled(true);
		soundFileChooser.setFileFilter(new FileFilter()
		{
			public boolean accept(File f)
			{
				if (f.isDirectory())
				{
					return true;
				}

				String extension = f.getName();
				if(extension.contains("."))extension = extension.substring(extension.indexOf(".")+1);
				extension = extension.toUpperCase();

				if (extension != null)
				{
					if
					(
							extension.equals("WAV")
							||extension.equals("OGG")
							//||extension.equals("MP3")
					)
					{
							return true;
					}
					else
					{
						return false;
					}
				}

				return false;
			}

			//The description of this filter
			public String getDescription()
			{
				return "Sound";
			}
		}
		);


		musicFileChooser = new JFileChooser("F:\\source\\games\\bobsgame\\workspace\\_music");
		musicFileChooser.setMultiSelectionEnabled(true);
		musicFileChooser.setFileFilter(new FileFilter()
		{

			public boolean accept(File f)
			{
				if (f.isDirectory())
				{
					return true;
				}

				String extension = f.getName();
				if(extension.contains("."))extension = extension.substring(extension.indexOf(".")+1);
				extension = extension.toUpperCase();

				if (extension != null)
				{
					if
					(
						extension.equals("OGG")
						//||extension.equals("MP3")
						||extension.equals("MOD")
						||extension.equals("XM")
						||extension.equals("S3M")
						||extension.equals("WAV")
					)
					{
							return true;
					}
					else
					{
						return false;
					}
				}
				return false;
			}

			//The description of this filter
			public String getDescription()
			{
				return "Music";
			}
		}
		);


		setLayout(new BorderLayout());


		addMusicFileButton = new JButton("Add Music File");
		addMusicFileButton.addActionListener(this);

		removeMusicFileButton = new JButton("Remove Music File");
		removeMusicFileButton.addActionListener(this);

		addSoundFileButton = new JButton("Add Sound File");
		addSoundFileButton.addActionListener(this);

		removeSoundFileButton = new JButton("Remove Sound File");
		removeSoundFileButton.addActionListener(this);


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



		Font listFont = new Font("Lucida Console", Font.PLAIN, 12);



		//----------------------
		//music list panel
		//----------------------
			JPanel musicPanel = new JPanel(new BorderLayout());
			musicPanel.setBorder(EditorMain.border);


				JPanel musicListPanel = new JPanel();
				musicListPanel.setBorder(EditorMain.border);
				musicListPanel.setLayout(new BoxLayout(musicListPanel,BoxLayout.Y_AXIS));

					musicListModel = new DefaultListModel<Music>();
						musicList = new JList<Music>(musicListModel);
						musicList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
						musicList.setLayoutOrientation(JList.VERTICAL);
						musicList.setVisibleRowCount(10);
						musicList.setForeground(Color.BLACK);
						musicList.setFont(listFont);
						musicList.setFixedCellHeight(16);
						musicList.addListSelectionListener(this);
						musicList.setCellRenderer(new MusicNameCellRenderer());
					musicListScroller = new JScrollPane(musicList);


				musicListPanel.add(new JLabel("Music"));
				musicListPanel.add(Box.createRigidArea(new Dimension(500,0)));
				musicListPanel.add(musicListScroller);


				JPanel musicOptionsPanel = new JPanel();
				musicOptionsPanel.setBorder(EditorMain.border);
				musicOptionsPanel.setLayout(new BoxLayout(musicOptionsPanel,BoxLayout.Y_AXIS));


				playStopMusicButton = new JButton("Play Music");
				playStopMusicButton.addActionListener(this);
				playStopMusicButton.setBackground(Color.GREEN);
				musicOptionsPanel.add(playStopMusicButton);


				musicOptionsPanel.add(Box.createGlue());


				musicNameTextField = new JTextField("",20);
				musicNameTextField.setMaximumSize(new Dimension(500,30));
				musicNameTextField.addCaretListener(this);
				musicNameTextField.addKeyListener(this);
				musicNameTextField.setForeground(Color.GRAY);
				musicOptionsPanel.add(new JLabel("Music Name:"));
				musicOptionsPanel.add(musicNameTextField);

				musicOptionsPanel.add(Box.createGlue());


				musicFileNameTextField = new JTextField("",30);
				musicFileNameTextField.setMaximumSize(new Dimension(500,30));
				musicFileNameTextField.addCaretListener(this);
				musicFileNameTextField.addKeyListener(this);
				musicFileNameTextField.setForeground(Color.GRAY);
				musicOptionsPanel.add(new JLabel("Music FileName:"));
				musicOptionsPanel.add(musicFileNameTextField);

				musicOptionsPanel.add(Box.createGlue());



				preloadMusicCheckbox = new JCheckBox("Preload Music.zip and MD5 to Client?");
				preloadMusicCheckbox.setSelected(false);
				preloadMusicCheckbox.addItemListener(this);

				musicOptionsPanel.add(preloadMusicCheckbox);

				musicOptionsPanel.add(Box.createGlue());

				musicOptionsPanel.add(addMusicFileButton);
				musicOptionsPanel.add(removeMusicFileButton);

			musicPanel.add(musicListPanel,BorderLayout.WEST);
			musicPanel.add(musicOptionsPanel,BorderLayout.EAST);




		//----------------------
		//sound list panel
		//----------------------
			JPanel soundPanel = new JPanel(new BorderLayout());
			soundPanel.setBorder(EditorMain.border);


				JPanel soundListPanel = new JPanel();
				soundListPanel.setBorder(EditorMain.border);
				soundListPanel.setLayout(new BoxLayout(soundListPanel,BoxLayout.Y_AXIS));

					soundListModel = new DefaultListModel<Sound>();
						soundList = new JList<Sound>(soundListModel);
						soundList.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
						soundList.setLayoutOrientation(JList.VERTICAL);
						soundList.setVisibleRowCount(10);
						soundList.setForeground(Color.BLACK);
						soundList.setFont(listFont);
						soundList.setFixedCellHeight(16);
						soundList.addListSelectionListener(this);
						soundList.setCellRenderer(new SoundNameCellRenderer());
					soundListScroller = new JScrollPane(soundList);


				soundListPanel.add(new JLabel("Sound"));
				soundListPanel.add(Box.createRigidArea(new Dimension(500,0)));
				soundListPanel.add(soundListScroller);


				JPanel soundOptionsPanel = new JPanel();
				soundOptionsPanel.setBorder(EditorMain.border);
				soundOptionsPanel.setLayout(new BoxLayout(soundOptionsPanel,BoxLayout.Y_AXIS));

				playStopSoundButton = new JButton("Play Sound");
				playStopSoundButton.addActionListener(this);
				playStopSoundButton.setBackground(Color.GREEN);
				soundOptionsPanel.add(playStopSoundButton);



				soundOptionsPanel.add(Box.createGlue());

				soundNameTextField = new JTextField("",20);
				soundNameTextField.setMaximumSize(new Dimension(500,30));
				soundNameTextField.addCaretListener(this);
				soundNameTextField.addKeyListener(this);
				soundNameTextField.setForeground(Color.GRAY);
				soundOptionsPanel.add(new JLabel("Sound Name:"));
				soundOptionsPanel.add(soundNameTextField);

				soundOptionsPanel.add(Box.createGlue());


				soundFileNameTextField = new JTextField("",30);
				soundFileNameTextField.setMaximumSize(new Dimension(500,30));
				soundFileNameTextField.addCaretListener(this);
				soundFileNameTextField.addKeyListener(this);
				soundFileNameTextField.setForeground(Color.GRAY);
				soundOptionsPanel.add(new JLabel("Sound FileName:"));
				soundOptionsPanel.add(soundFileNameTextField);

				soundOptionsPanel.add(Box.createGlue());
				soundOptionsPanel.add(addSoundFileButton);
				soundOptionsPanel.add(removeSoundFileButton);


			soundPanel.add(soundListPanel,BorderLayout.WEST);
			soundPanel.add(soundOptionsPanel,BorderLayout.EAST);






		JPanel centerPanel = new JPanel(new BorderLayout());


		JPanel listsPanel = new JPanel(new BorderLayout());

		listsPanel.add(musicPanel,BorderLayout.WEST);
		listsPanel.add(soundPanel,BorderLayout.EAST);


//		JPanel otherPanel = new JPanel();
//		rescanDirectoriesButton = new JButton("Rescan Directories");
//		rescanDirectoriesButton.addActionListener(this);
//
//		otherPanel.add(rescanDirectoriesButton);



		centerPanel.add(everythingPanel,BorderLayout.NORTH);
		centerPanel.add(listsPanel,BorderLayout.CENTER);
		//centerPanel.add(otherPanel,BorderLayout.SOUTH);

		add(centerPanel,BorderLayout.CENTER);









		setSize(EditorMain.getScreenWidth()-20, 770);
		setLocation(20, 800);

	}


	//===============================================================================================
	public void showSoundAndMusicEditor()
	{//===============================================================================================


		if(EditorMain.soundWasInitialized==false)
		{
			EditorMain.audioUtils = new AudioUtils();
			EditorMain.soundWasInitialized = true;
		}

		//on editor open, scan C:\Users\Administrator\workspace\_sfx
		//check Project.musicList.get.filename to see if each entry is recorded.
		//if any files don't exist in musicList, add them with blank names

		updateListsFromMusicAndSoundArrays();

		//in list, files without names are gray
		//files with invalid filenames are red


		//need to be able to change entry filename
		//entry has name which is referenced.

		//need button to rescan


		setVisible(true);

		try
		{
			setAlwaysOnTop(true);
		}
		catch(SecurityException se){}


		musicNameTextField.setForeground(Color.GRAY);
		musicFileNameTextField.setForeground(Color.GRAY);

		soundNameTextField.setForeground(Color.GRAY);
		soundFileNameTextField.setForeground(Color.GRAY);

	}



	//===============================================================================================
	public void updateListsFromMusicAndSoundArrays()
	{//===============================================================================================



		//String baseDir = "C:\\Users\\Administrator\\workspace\\";

//
//		{
//
//
//			File directory = new File(baseDir+"_music\\");
//
//			File[] files = directory.listFiles();
//
//			for(int f=0;f<files.length;f++)
//			{
//
//				boolean found = false;
//
//				for(int i=0;i<Project.musicList.size();i++)
//				{
//					Music music = Project.musicList.get(i);
//
//					if(music.fileName().equals(files[f].getName()))
//					{
//						found=true;
//						music.found=true;
//						music.fullfilepath = files[f].getPath();
//					}
//
//				}
//
//				if(found==false)
//				{
//					Music newMusic = new Music("",files[f].getName());
//					newMusic.found=true;
//
//					newMusic.fullfilepath = files[f].getPath();
//				}
//
//
//			}

			//alphabetize list
			{
				ArrayList<Music> temp = new ArrayList<Music>();
				for(char letter='0';letter<'9';letter++){for(int i=0;i<Project.musicList.size();i++){Music m=Project.musicList.get(i);if(m.name().toLowerCase().startsWith(""+letter)&&temp.contains(m)==false)temp.add(m);}}
				for(char letter='a';letter<'z';letter++){for(int i=0;i<Project.musicList.size();i++){Music m=Project.musicList.get(i);if(m.name().toLowerCase().startsWith(""+letter)&&temp.contains(m)==false)temp.add(m);}}
				for(int i=0;i<Project.musicList.size();i++){Music m=Project.musicList.get(i);if(temp.contains(m)==false)temp.add(m);}
				Project.musicList = temp;
			}

			musicListModel.clear();
			for(int i=0;i<Project.musicList.size();i++)
			{
				Music music = Project.musicList.get(i);

				musicListModel.addElement(music);
			}



//
//
//
//		}



//		{
//
//
//			File directory = new File(baseDir+"_sfx\\");
//
//			File[] files = directory.listFiles();
//
//			for(int f=0;f<files.length;f++)
//			{
//
//				boolean found = false;
//
//				for(int i=0;i<Project.soundList.size();i++)
//				{
//					Sound sound = Project.soundList.get(i);
//
//					if(sound.fileName().equals(files[f].getName()))
//					{
//						found=true;
//						sound.found=true;
//
//						sound.fullfilepath = files[f].getPath();
//					}
//
//				}
//
//				if(found==false)
//				{
//					Sound newSound = new Sound("",files[f].getName());
//					newSound.found=true;
//
//					newSound.fullfilepath = files[f].getPath();
//
//
//				}
//
//
//			}


			//alphabetize list
			{
				ArrayList<Sound> temp = new ArrayList<Sound>();
				for(char letter='0';letter<'9';letter++){for(int i=0;i<Project.soundList.size();i++){Sound m=Project.soundList.get(i);if(m.name().toLowerCase().startsWith(""+letter)&&temp.contains(m)==false)temp.add(m);}}
				for(char letter='a';letter<'z';letter++){for(int i=0;i<Project.soundList.size();i++){Sound m=Project.soundList.get(i);if(m.name().toLowerCase().startsWith(""+letter)&&temp.contains(m)==false)temp.add(m);}}
				for(int i=0;i<Project.soundList.size();i++){Sound m=Project.soundList.get(i);if(temp.contains(m)==false)temp.add(m);}
				Project.soundList = temp;
			}

			soundListModel.clear();
			for(int i=0;i<Project.soundList.size();i++)
			{
				Sound sound = Project.soundList.get(i);

				soundListModel.addElement(sound);
			}

//
//
//
//		}



	}






	//===============================================================================================
	@Override
	public void valueChanged(ListSelectionEvent e)
	{//===============================================================================================


		if(e.getSource() == soundList)
		{

			if(soundList.getSelectedValue()!=null)
			{
				Sound sound = soundList.getSelectedValue();
				soundNameTextField.setText(sound.name());
				soundFileNameTextField.setText(sound.fileName());

				soundNameTextField.setForeground(Color.GRAY);
				soundFileNameTextField.setForeground(Color.GRAY);
			}

		}

		if(e.getSource() == musicList)
		{
			if(musicList.getSelectedValue()!=null)
			{
				Music music = musicList.getSelectedValue();
				musicNameTextField.setText(music.name());
				musicFileNameTextField.setText(music.fileName());

				musicNameTextField.setForeground(Color.GRAY);
				musicFileNameTextField.setForeground(Color.GRAY);
				preloadMusicCheckbox.setSelected(music.preload());
			}

		}

	}


	//===============================================================================================
	@Override
	public void caretUpdate(CaretEvent e)
	{//===============================================================================================


		if(e.getSource()==musicNameTextField)
		{
			musicNameTextField.setForeground(Color.RED);
		}

		if(e.getSource()==musicFileNameTextField)
		{
			musicFileNameTextField.setForeground(Color.RED);
		}

		if(e.getSource()==soundNameTextField)
		{
			soundNameTextField.setForeground(Color.RED);
		}

		if(e.getSource()==soundFileNameTextField)
		{
			soundFileNameTextField.setForeground(Color.RED);
		}
	}


	//===============================================================================================
	@Override
	public void keyTyped(KeyEvent e)
	{//===============================================================================================

	}


	//===============================================================================================
	@Override
	public void keyPressed(KeyEvent e)
	{//===============================================================================================
		if(e.getSource()==soundNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{

			soundNameTextField.setForeground(Color.GRAY);

			if(soundNameTextField.getText().length()<1)return;

			if(soundList.getSelectedValue()!=null)
			{
				Sound sound = soundList.getSelectedValue();
				sound.setName(soundNameTextField.getText());

			}


		}

		if(e.getSource()==soundFileNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{

			soundFileNameTextField.setForeground(Color.GRAY);

			if(soundFileNameTextField.getText().length()<1)return;


			if(soundList.getSelectedValue()!=null)
			{
				Sound sound = soundList.getSelectedValue();
				sound.setFileName(soundFileNameTextField.getText());

			}



		}



		if(e.getSource()==musicNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{

			musicNameTextField.setForeground(Color.GRAY);

			if(musicNameTextField.getText().length()<1)return;

			if(musicList.getSelectedValue()!=null)
			{
				Music music = musicList.getSelectedValue();
				music.setName(musicNameTextField.getText());

			}

		}

		if(e.getSource()==musicFileNameTextField && e.getKeyCode() == KeyEvent.VK_ENTER)
		{

			musicFileNameTextField.setForeground(Color.GRAY);

			if(musicFileNameTextField.getText().length()<1)return;


			if(musicList.getSelectedValue()!=null)
			{
				Music music = musicList.getSelectedValue();
				music.setFileName(musicFileNameTextField.getText());

			}
		}
	}


	//===============================================================================================
	@Override
	public void keyReleased(KeyEvent e)
	{//===============================================================================================

	}


	//===============================================================================================
	@Override
	public void itemStateChanged(ItemEvent e)
	{//===============================================================================================
		if(e.getSource()==preloadMusicCheckbox)
		{

			if(musicList.getSelectedValue()!=null)
			{
				Music music = musicList.getSelectedValue();
				music.setPreload(preloadMusicCheckbox.isSelected());

			}
		}
	}



	//===============================================================================================
	@Override
	public void actionPerformed(ActionEvent ae)
	{//===============================================================================================




		if(ae.getSource() == doneButton)
		{
			setVisible(false);
		}
		else if(ae.getSource() == cancelButton)
		{
			setVisible(false);
		}


		if(ae.getSource() == addMusicFileButton)
		{

			int val = musicFileChooser.showOpenDialog(this);

			if(val==JFileChooser.APPROVE_OPTION)
			{

				File[] files = musicFileChooser.getSelectedFiles();

				for(int i=0;i<files.length;i++)
				{
					File f = files[i];

					String filename = f.getName();
					String directory = musicFileChooser.getCurrentDirectory().getPath()+"\\";


					String name = filename;
					if(name.contains("."))name = name.substring(0,name.indexOf("."));

					if(Project.getMusicByName(name)!=null)continue;

					Music music = new Music(name,filename);

					music.setFileName(filename);
					music.setFullFilePath(""+directory+filename);

					musicListModel.addElement(music);
				}
			}
			updateListsFromMusicAndSoundArrays();
		}


		if(ae.getSource() == addSoundFileButton)
		{

			int val = soundFileChooser.showOpenDialog(this);

			if(val==JFileChooser.APPROVE_OPTION)
			{
				File[] files = soundFileChooser.getSelectedFiles();

				for(int i=0;i<files.length;i++)
				{
					File f = files[i];

					String filename = f.getName();
					String directory = soundFileChooser.getCurrentDirectory().getPath()+"\\";

					String name = filename;
					if(name.contains("."))name = name.substring(0,name.indexOf("."));

					if(Project.getSoundByName(name)!=null)continue;

					Sound sound = new Sound(name,filename);

					sound.setFileName(filename);
					sound.setFullFilePath(""+directory+filename);

					soundListModel.addElement(sound);
				}

			}
			updateListsFromMusicAndSoundArrays();
		}



		if(ae.getSource() == removeSoundFileButton)
		{
			Sound s = soundListModel.remove(soundList.getSelectedIndex());

			if(s!=null)
			{
				Project.soundHashtable.remove(s.getTYPEIDString());
				Project.soundList.remove(s);
			}
		}



		if(ae.getSource() == removeMusicFileButton)
		{
			Music s = musicListModel.remove(musicList.getSelectedIndex());

			if(s!=null)
			{
				Project.musicHashtable.remove(s.getTYPEIDString());
				Project.musicList.remove(s);
			}
		}



		if(ae.getSource() == playStopMusicButton)
		{


			if(musicIsPlaying)
			{

				audioFile.closeChannelAndFlushBuffers();
				musicIsPlaying = false;
				playStopMusicButton.setText("Play Music");
				playStopMusicButton.setBackground(Color.GREEN);

			}
			else
			{

				if(musicList.getSelectedValue()!=null)
				{
					Music music = musicList.getSelectedValue();

					if(music==null)return;

					audioFile = AudioUtils.open(music.fullFilePath(),music.fullFilePath());

					audioFile.play(1.0f, 1.0f, false);

					musicIsPlaying=true;

					new Thread
					(
							new Runnable()
							{
								public void run()
								{
									while(musicIsPlaying==true)
									{
										audioFile.updateBufferAndPlay();
										try
										{
											Thread.sleep(10);
										}
										catch(InterruptedException e)
										{
											e.printStackTrace();
										}
										if(audioFile.isDone())
										{
											musicIsPlaying=false;
											playStopMusicButton.setText("Play Music");
											playStopMusicButton.setBackground(Color.GREEN);
										}
									}
								}
							}
					).start();

					playStopMusicButton.setText("Stop Music");
					playStopMusicButton.setBackground(Color.RED);

				}
			}
		}


		if(ae.getSource() == playStopSoundButton)
		{


			if(soundIsPlaying)
			{
				audioFile.closeChannelAndFlushBuffers();
				soundIsPlaying = false;
				playStopSoundButton.setText("Play Sound");
				playStopSoundButton.setBackground(Color.GREEN);
			}
			else
			{

				if(soundList.getSelectedValue()!=null)
				{

					Sound sound = soundList.getSelectedValue();
					if(sound==null)return;

					audioFile = AudioUtils.open(sound.fullFilePath(),sound.fullFilePath());

					audioFile.play(1.0f, 1.0f, false);

					soundIsPlaying=true;


					new Thread
					(
							new Runnable()
							{
								public void run()
								{
									while(soundIsPlaying==true)
									{
										audioFile.updateBufferAndPlay();
										try
										{
											Thread.sleep(10);
										}
										catch(InterruptedException e)
										{
											e.printStackTrace();
										}
										if(audioFile.isDone())
										{
											soundIsPlaying=false;
											playStopSoundButton.setText("Play Sound");
											playStopSoundButton.setBackground(Color.GREEN);
										}
									}
								}
							}
					).start();


					playStopSoundButton.setText("Stop Sound");
					playStopSoundButton.setBackground(Color.RED);

				}

			}
		}
	}

	//===============================================================================================
	class SoundNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public SoundNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);

			String displayName = "";

			Sound s = ((Sound)value);

			File f = new File(s.fullFilePath());
			long size = 0;
			if(f.exists())size = FileUtils.sizeOf(f);

			if(value!=null)displayName = s.name()+" ["+s.fileName()+"] ["+size/1024+"KB]";

			if(value!=null)if(s.name().equals("")){setForeground(Color.LIGHT_GRAY);}
			if(value!=null)if(f.exists()==false){setForeground(Color.RED);}

			setText((value == null) ? "" : displayName);
			return this;
		}
	}





	//===============================================================================================
	class MusicNameCellRenderer extends DefaultListCellRenderer
	{//===============================================================================================
		/**
		 *
		 */
		private static final long serialVersionUID = 1L;
		public MusicNameCellRenderer(){}
		public Component getListCellRendererComponent(JList<?> list,Object value,int index,boolean isSelected,boolean cellHasFocus)
		{
			super.getListCellRendererComponent(list,value,index,isSelected,cellHasFocus);


			String displayName = "";

			Music m = ((Music)value);
			File f = new File(m.fullFilePath());
			long size = 0;
			if(f.exists())size = FileUtils.sizeOf(f);

			if(value!=null)displayName = m.name()+" ["+m.fileName()+"] ["+size/1024+"KB]";

			if(value!=null)
			{
				if(m.name().equals("")){setForeground(Color.LIGHT_GRAY);}
				if(m.preload()==true){setForeground(Color.GREEN);}
				if(f.exists()==false){setForeground(Color.RED);}
			}

			setText((value == null) ? "" : displayName);
			return this;
		}
	}







}
