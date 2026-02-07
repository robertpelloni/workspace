package com.bobsgame.client.engine.sound;


import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.event.ServerObject;
import com.bobsgame.shared.MusicData;
import com.bobsgame.audio.AudioChannel;
import com.bobsgame.audio.AudioUtils;
//=========================================================================================================================
public class Music extends ServerObject
{//=========================================================================================================================


	protected boolean fileExists = false;
	protected boolean _fileExists = false;
	protected boolean startedDownloadThread = false;


	private MusicData data;
	public byte[] byteData;



	protected AudioChannel channel = null;
	public float pitch = 1.0f;
	public float volume = 1.0f;
	private boolean loop = false;



	private boolean shouldBePlaying = false;
	private boolean playingStarted = false;
	private int ticksToFadeOutTotal = -1;
	private int ticksToFadeOutCounter = -1;
	private float volumeWhenStartedFade = 0;


	//=========================================================================================================================
	public Music(Engine g, int id)
	{//=========================================================================================================================
		super(g);

		this.data = new MusicData(id,"","");

		for(int i=0;i<AudioManager().musicList.size();i++){if(AudioManager().musicList.get(i).id()==data.id()){log.error("Music already exists:"+data.name());return;}}
		AudioManager().musicList.add(this);
	}

	//=========================================================================================================================
	public Music(Engine g, MusicData data)
	{//=========================================================================================================================
		super(g);

		this.data = data;
		setInitialized_S(true);

		for(int i=0;i<AudioManager().musicList.size();i++){if(AudioManager().musicList.get(i).id()==data.id()){log.error("Music already exists:"+data.name());return;}}
		AudioManager().musicList.add(this);
	}


	public MusicData getData(){return data;}

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
	public synchronized void setData_S(MusicData data)
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
								try{Thread.currentThread().setName("Music_downloadToCache");}catch(SecurityException e){e.printStackTrace();}
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
			if(shouldBePlaying==true)
			{
				if(channel==null)
				{
					loadDataIntoChannel();
				}


				//startAudioIfNotPlaying();
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

					//resetOrLoopAudioIfDonePlaying();
					if(channel.isDone()==true)//this should never happen for looping music, the channel just repeats
					{
						if(loop==false)
						{
							stop();
						}
					}
				}

			}
			else
			{
				stop();
			}





			if(ticksToFadeOutTotal!=-1)
			{
				ticksToFadeOutCounter-=Engine().engineTicksPassed();

				if(ticksToFadeOutCounter<=0)
				{
					stop();
				}
				else
				{
					setVolume(((float)ticksToFadeOutCounter/(float)ticksToFadeOutTotal)*volumeWhenStartedFade);
				}
			}


		}





	}

	//=========================================================================================================================
	public void loadDataIntoChannel()
	{//=========================================================================================================================

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
	}







	//=========================================================================================================================
	public void play()
	{//=========================================================================================================================
		play(1.0f,1.0f,true);
	}

	//=========================================================================================================================
	public void play(float pitch, float volume, boolean loop)
	{//=========================================================================================================================

		if(this.pitch!=pitch || this.volume != volume || this.loop != loop)
		{

			this.pitch = pitch;
			this.volume = volume;
			this.loop = loop;

			if(channel!=null)
			{
				channel.setVolume(volume);
				channel.setLoop(loop);
				channel.setPitch(pitch);
			}

		}

		shouldBePlaying=true;

		update();

	}


	//=========================================================================================================================
	public void fadeOutAndStop(int ticksToFadeOut)
	{//=========================================================================================================================

		this.ticksToFadeOutTotal = ticksToFadeOut;
		this.ticksToFadeOutCounter = ticksToFadeOut;
		this.volumeWhenStartedFade = volume;
	}

	//=========================================================================================================================
	public boolean isFadingOut()
	{//=========================================================================================================================
		if(ticksToFadeOutTotal!=-1)return true;

		return false;
	}





	//=========================================================================================================================
	public void pause()
	{//=========================================================================================================================
		if(channel!=null)channel.pause();
	}

	//=========================================================================================================================
	public void unpause()
	{//=========================================================================================================================
		if(channel!=null)channel.unPause();
	}

	//=========================================================================================================================
	public void stop()
	{//=========================================================================================================================
		pitch = 1.0f;
		volume = 1.0f;
		loop = false;
		ticksToFadeOutCounter=-1;
		ticksToFadeOutTotal=-1;
		volumeWhenStartedFade = 0;


		shouldBePlaying=false;

		if(playingStarted)
		{
			if(channel!=null)
			{
				channel.closeChannelAndFlushBuffers();
				playingStarted=false;
			}
		}
	}

	//=========================================================================================================================
	public void setLoop(boolean b)
	{//=========================================================================================================================
		this.loop = b;
		if(channel!=null)channel.setLoop(b);
	}

	//=========================================================================================================================
	public boolean getLoop()
	{//=========================================================================================================================
		return loop;
	}

	//=========================================================================================================================
	public boolean isPlaying()
	{//=========================================================================================================================

		if(channel!=null)
		{
			if(channel.isPaused())return false;

			if(channel.isPlaying())return true;
		}

		return shouldBePlaying;
	}


	//=========================================================================================================================
	public void setVolume(float v)
	{//=========================================================================================================================
		volume = v;
		if(channel!=null)channel.setVolume(v);
	}

	//=========================================================================================================================
	public void setPitch(float p)
	{//=========================================================================================================================

		pitch = p;
		if(channel!=null)channel.setPitch(p);
	}



}



