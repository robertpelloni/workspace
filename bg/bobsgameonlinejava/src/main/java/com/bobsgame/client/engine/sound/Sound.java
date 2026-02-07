package com.bobsgame.client.engine.sound;

import java.util.ArrayList;


import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.event.ServerObject;
import com.bobsgame.shared.SoundData;
import com.bobsgame.audio.AudioChannel;
import com.bobsgame.audio.AudioUtils;
//=========================================================================================================================
public class Sound extends ServerObject
{//=========================================================================================================================

	protected boolean fileExists = false;
	protected boolean _fileExists = false;
	protected boolean startedDownloadThread = false;



	private SoundData data;
	public byte[] byteData;


	protected ArrayList<SoundChannel> soundChannels = new ArrayList<SoundChannel>();


	//=========================================================================================================================
	public Sound(Engine g, int id)
	{//=========================================================================================================================

		super(g);
		this.data = new SoundData(id,"","");

		for(int i=0;i<AudioManager().soundList.size();i++){if(AudioManager().soundList.get(i).id()==data.id()){log.error("Sound already exists:"+data.name());return;}}
		AudioManager().soundList.add(this);
	}


	//=========================================================================================================================
	public Sound(Engine g, SoundData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<AudioManager().soundList.size();i++){if(AudioManager().soundList.get(i).id()==data.id()){log.error("Sound already exists:"+data.name());return;}}
		AudioManager().soundList.add(this);
	}



	public SoundData getData(){return data;}

	public int id(){return data.id();}
	public String name(){return data.name();}
	public String fileName(){return data.fileName();}
	//public String fullFilePath(){return data.fullFilePath();}
	public String md5Name(){return data.md5Name();}


	public String getTYPEIDString(){return data.getTYPEIDString();}


	public void setID(int id){data.setID(id);}
	public void setName(String name){data.setName(name);}
	public void setFileName(String fileName){data.setFileName(fileName);}
	//public void setFullFilePath(String fullFilePath){data.setFullFilePath(fullFilePath);}
	public void setMD5Name(String s){data.setMD5Name(s);}



	//=========================================================================================================================
	protected boolean getFileExists()
	{//=========================================================================================================================
		return _fileExists;
	}
	//=========================================================================================================================
	protected void setFileExists(boolean i)
	{//=========================================================================================================================
		_fileExists=i;
	}

	//=========================================================================================================================
	public byte[] getByteData()
	{//=========================================================================================================================
		return byteData;
	}

	//=========================================================================================================================
	public synchronized void setData_S(SoundData data)
	{//=========================================================================================================================

		this.data = data;
		setInitialized_S(true);
	}

	Thread downloadThread = null;

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		//get the name and filename from the server
		super.update();

		if(loadedInfoDataFromServer==false)return;

		//download the file to the cache if it doesnt exist
		if(fileExists==false && getByteData()==null)
		{
			if(getFileExists()==false)
			{
				if(startedDownloadThread==false)
				{
					startedDownloadThread=true;

					//check cache FIRST before start thread.
					//only start thread if not in cache.
					if(Cache.checkIfFileExistsInCache(md5Name()))
					{
						setFileExists(true);
					}
					else
					{
						downloadThread = new Thread(new Runnable()
						{
							public void run()
							{
								try{Thread.currentThread().setName("Sound_downloadToCache");}catch(SecurityException e){e.printStackTrace();}
								//now check the cache and download the mp3/ogg/xm/s3m from the s3 bucket in a new thread if not exist.
								Cache.downloadBigFileToCacheIfNotExist(md5Name());
							}

						});

						downloadThread.start();
					}
				}
				else
				{
					if(downloadThread!=null&&downloadThread.isAlive()==false)
					{
						if(Cache.checkIfFileExistsInCache(md5Name()))
						{
							setFileExists(true);
						}
						else
						{
							log.error("Download thread timed out for Sound: "+name());
							downloadThread.start();
						}
					}
				}
			}
			else
			{
				fileExists=true;
			}
		}


		if(fileExists==true || getByteData()!=null)
		{
			for(int i=0;i<soundChannels.size();i++)
			{
				SoundChannel sound = soundChannels.get(i);
				sound.handlePlaying();
			}
		}




		for(int i=0;i<soundChannels.size();i++)
		{
			SoundChannel sound = soundChannels.get(i);

			if(sound.delete==true)
			{
				soundChannels.remove(i);
				i=-1;
			}
		}

	}



	//=========================================================================================================================
	public void play()
	{//=========================================================================================================================
		play(1.0f,1.0f,0);
	}

	//=========================================================================================================================
	public void play(float pitch, float volume, int timesToPlay)
	{//=========================================================================================================================

		SoundChannel s = new SoundChannel();
		s.play(pitch,volume,timesToPlay);

		update();
	}








	//sounds can be played multiple times at once, so they get a unique audio handler per instance played

	//music can only be played once per song loaded at a time

	//=========================================================================================================================
	public class SoundChannel
	{//=========================================================================================================================
		AudioChannel channel;
		protected boolean shouldBePlaying = false;
		protected boolean playingStarted = false;
		protected float pitch = 1.0f;
		protected float volume = 1.0f;
		protected boolean loop = false;
		public int timesToPlay = 1;
		public boolean delete = false;

		//=========================================================================================================================
		public SoundChannel()
		{//=========================================================================================================================
			soundChannels.add(this);
		}



		//=========================================================================================================================
		public void play(float pitch, float volume, int timesToPlay)
		{//=========================================================================================================================

			if(timesToPlay<0)log.error("Trying to play sound -1 times. Sounds cannot be infinitely looped, only music can.");

			if(timesToPlay==1)timesToPlay=0;

			this.pitch = pitch;
			this.volume = volume;
			this.timesToPlay = timesToPlay;

			shouldBePlaying=true;

		}
		//=========================================================================================================================
		public void handlePlaying()
		{//=========================================================================================================================
			if(shouldBePlaying==true)
			{
				if(channel==null)
				{
					if(getByteData()==null)
					{
						channel = AudioUtils.open(fileName(),Cache.cacheDir+md5Name());
					}
					else
					{
						channel = AudioUtils.open(fileName(),md5Name(),getByteData());
					}
				}


				if(channel!=null)
				{
					if(playingStarted==false)
					{
						channel.play(pitch,volume,loop);
						playingStarted=true;
					}
					else
					if(playingStarted==true)
					{
						channel.updateBufferAndPlay();
					}


					if(channel.isDone()==true)
					{
						if(timesToPlay>0)
						{
							timesToPlay--;
							playingStarted=false;
						}
						else
						{
							shouldBePlaying=false;
							playingStarted=false;
						}
					}
				}
			}

			if(shouldBePlaying==false)
			{
				if(channel!=null)
				{
					channel.closeChannelAndFlushBuffers();
					playingStarted=false;
					delete = true;
				}
			}
		}



	}

}
