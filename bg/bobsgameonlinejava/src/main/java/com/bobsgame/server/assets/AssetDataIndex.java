package com.bobsgame.server.assets;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.io.IOUtils;
import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Logger;

import com.bobsgame.ServerMain;
import com.bobsgame.shared.DialogueData;
import com.bobsgame.shared.EventData;
import com.bobsgame.shared.FlagData;
import com.bobsgame.shared.GameStringData;
import com.bobsgame.shared.MusicData;
import com.bobsgame.shared.SkillData;
import com.bobsgame.shared.SoundData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MapStateData;
import com.bobsgame.shared.SpriteData;

public class AssetDataIndex
{




	public static Logger log = (Logger) LoggerFactory.getLogger(AssetDataIndex.class);


	static public ConcurrentHashMap<Integer,DialogueData> dialogueDataList = new ConcurrentHashMap<Integer,DialogueData>();
	//static public ConcurrentHashMap<String,String> dialogueDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> dialogueDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	//static public ConcurrentHashMap<String,Integer> dialogueDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	//static public ConcurrentHashMap<Integer,String> dialogueDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();


	//===============================================================================================
	public AssetDataIndex()
	{//===============================================================================================

		importDialogueDataFiles();
		importEventDataFiles();
		importFlagDataFiles();
		importGameStringDataFiles();
		importMapDataFiles();
		importMusicDataFiles();
		importSkillDataFiles();
		importSoundDataFiles();
		importSpriteDataFiles();
	}



	//===============================================================================================
	public void importDialogueDataFiles()
	{//===============================================================================================


		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/DialogueData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					DialogueData data = DialogueData.fromJSON(s);

					if(data.name()==null)data.setName("Dialogue"+data.id());

					dialogueDataList.put(data.id(),data);
					//dialogueDataBase64List.put(data.name(),s);
					//dialogueDataByIDBase64List.put(data.id(),s);
					//dialogueDataGetIDByNameList.put(data.name(),data.id());
					//dialogueDataGetNameByIDList.put(data.id(),data.name());


					log.debug("Loaded Dialogue: "+data.name());

				}
			}
		}
	}




	static public int loadEventID = -1;

	static public ConcurrentHashMap<Integer,EventData> eventDataList = new ConcurrentHashMap<Integer,EventData>();
	//static public ConcurrentHashMap<String,String> eventDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> eventDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	//static public ConcurrentHashMap<String,Integer> eventDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	//static public ConcurrentHashMap<Integer,String> eventDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();






	//===============================================================================================
	public void importEventDataFiles()
	{//===============================================================================================

		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/CutsceneEventData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					EventData eventAsset = EventData.fromJSON(s);

					if(eventAsset.type()==EventData.TYPE_PROJECT_INITIAL_LOADER)
					{
						loadEventID = eventAsset.id();
						log.info("Found project load event:"+eventAsset.id());
					}

					eventDataList.put(eventAsset.id(),eventAsset);
					//eventDataBase64List.put(eventAsset.name(),s);
					//eventDataByIDBase64List.put(eventAsset.id(),s);
					//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
					//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());


					log.debug("Loaded Cutscene Event: "+eventAsset.name());

				}
			}
		}

	}




	static public ConcurrentHashMap<Integer,FlagData> flagDataList = new ConcurrentHashMap<Integer,FlagData>();
	//static public ConcurrentHashMap<String,String> flagDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> flagDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	//static public ConcurrentHashMap<String,Integer> flagDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	//static public ConcurrentHashMap<Integer,String> flagDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();





	//===============================================================================================
	public void importFlagDataFiles()
	{//===============================================================================================

		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/FlagData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					FlagData flagAsset = FlagData.fromJSON(s);

					flagDataList.put(flagAsset.id(),flagAsset);
					//flagDataBase64List.put(flagAsset.name(),s);
					//flagDataByIDBase64List.put(flagAsset.id(),s);
					//flagDataGetIDByNameList.put(flagAsset.name(),flagAsset.id());
					//flagDataGetNameByIDList.put(flagAsset.id(),flagAsset.name());


					log.debug("Loaded Flag: "+flagAsset.name());

				}
			}
		}

	}




	static public ConcurrentHashMap<Integer,GameStringData> gameStringDataList = new ConcurrentHashMap<Integer,GameStringData>();
	//static public ConcurrentHashMap<String,String> gameStringDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> gameStringDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	//static public ConcurrentHashMap<String,Integer> gameStringDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	//static public ConcurrentHashMap<Integer,String> gameStringDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();




	//===============================================================================================
	public void importGameStringDataFiles()
	{//===============================================================================================


		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/GameStringData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					GameStringData gameStringAsset = GameStringData.fromJSON(s);

					gameStringDataList.put(gameStringAsset.id(),gameStringAsset);
					//gameStringDataBase64List.put(gameStringAsset.name(),s);
					//gameStringDataByIDBase64List.put(gameStringAsset.id(),s);
					//gameStringDataGetIDByNameList.put(gameStringAsset.name(),gameStringAsset.id());
					//gameStringDataGetNameByIDList.put(gameStringAsset.id(),gameStringAsset.name());


					log.debug("Loaded GameString: "+gameStringAsset.name());

				}

			}

		}

	}





	static public ConcurrentHashMap<Integer,MapData> mapDataList = new ConcurrentHashMap<Integer,MapData>();
	//static public ConcurrentHashMap<String,String> mapDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> mapDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	static public ConcurrentHashMap<String,Integer> mapDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	static public ConcurrentHashMap<Integer,String> mapDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();





	//===============================================================================================
	public void importMapDataFiles()
	{//===============================================================================================


		List<String> mapB64Strings=null;

		try
		{
			mapB64Strings = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/MapData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(mapB64Strings!=null)
		{
			for(int i=0;i<mapB64Strings.size();i++)
			{
				String s = mapB64Strings.get(i);

				if(s.length()>0)
				{
					MapData mapData = MapData.fromJSON(s);

					mapDataList.put(mapData.id(),mapData);
					//mapDataBase64List.put(mapData.name(),s);
					//mapDataByIDBase64List.put(mapData.id(),s);
					mapDataGetIDByNameList.put(mapData.name(),mapData.id());
					mapDataGetNameByIDList.put(mapData.id(),mapData.name());

					log.debug("Loaded Map: "+mapData.name());

					for(int n = 0; n< mapData.eventDataList().size();n++)
					{
						EventData eventAsset = mapData.eventDataList().get(n);

						eventDataList.put(eventAsset.id(),eventAsset);
						//eventDataBase64List.put(eventAsset.name(),s);
						//eventDataByIDBase64List.put(eventAsset.id(),s);
						//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
						//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());

						log.debug("Loaded Map Event: "+eventAsset.name());
					}

					for(int n = 0; n< mapData.doorDataList().size();n++)
					{
						EventData eventAsset = mapData.doorDataList().get(n).eventData;

						if(eventAsset!=null)
						{
							eventDataList.put(eventAsset.id(),eventAsset);
							//eventDataBase64List.put(eventAsset.name(),s);
							//eventDataByIDBase64List.put(eventAsset.id(),s);
							//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
							//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());

							log.debug("Loaded Door Event: "+eventAsset.name());
						}
					}

					for(int n = 0; n< mapData.stateDataList().size();n++)
					{
						MapStateData stateData = mapData.stateDataList().get(n);

						for(int x = 0; x< stateData.areaDataList().size();x++)
						{
							EventData eventAsset = stateData.areaDataList().get(x).eventData;

							if(eventAsset!=null)
							{
								eventDataList.put(eventAsset.id(),eventAsset);
								//eventDataBase64List.put(eventAsset.name(),s);
								//eventDataByIDBase64List.put(eventAsset.id(),s);
								//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
								//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());

								log.debug("Loaded Area Event: "+eventAsset.name());
							}
						}

						for(int x = 0; x< stateData.entityDataList().size();x++)
						{
							EventData eventAsset = stateData.entityDataList().get(x).eventData;

							if(eventAsset!=null)
							{
								eventDataList.put(eventAsset.id(),eventAsset);
								//eventDataBase64List.put(eventAsset.name(),s);
								//eventDataByIDBase64List.put(eventAsset.id(),s);
								//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
								//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());

								log.debug("Loaded Entity Event: "+eventAsset.name());
							}
						}

					}


				}
			}
		}


	}


	static public ConcurrentHashMap<Integer,MusicData> musicDataList = new ConcurrentHashMap<Integer,MusicData>();
	//static public ConcurrentHashMap<String,String> musicDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> musicDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	static public ConcurrentHashMap<String,Integer> musicDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	static public ConcurrentHashMap<Integer,String> musicDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();




	//===============================================================================================
	public void importMusicDataFiles()
	{//===============================================================================================



		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/MusicData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					MusicData musicAsset = MusicData.fromJSON(s);

					musicDataList.put(musicAsset.id(),musicAsset);
					//musicDataBase64List.put(musicAsset.name(),s);
					//musicDataByIDBase64List.put(musicAsset.id(),s);
					musicDataGetIDByNameList.put(musicAsset.name(),musicAsset.id());
					musicDataGetNameByIDList.put(musicAsset.id(),musicAsset.name());


					log.debug("Loaded Music: "+musicAsset.name());

				}

			}

		}

	}




	static public ConcurrentHashMap<Integer,SkillData> skillDataList = new ConcurrentHashMap<Integer,SkillData>();
	//static public ConcurrentHashMap<String,String> skillDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> skillDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	//static public ConcurrentHashMap<String,Integer> skillDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	//static public ConcurrentHashMap<Integer,String> skillDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();





	//===============================================================================================
	public void importSkillDataFiles()
	{//===============================================================================================


		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/SkillData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					SkillData skillAsset = SkillData.fromJSON(s);


					skillDataList.put(skillAsset.id(),skillAsset);
					//skillDataBase64List.put(skillAsset.name(),s);
					//skillDataByIDBase64List.put(skillAsset.id(),s);
					//skillDataGetIDByNameList.put(skillAsset.name(),skillAsset.id());
					//skillDataGetNameByIDList.put(skillAsset.id(),skillAsset.name());


					log.debug("Loaded Skill: "+skillAsset.name());

				}

			}

		}

	}





	static public ConcurrentHashMap<Integer,SoundData> soundDataList = new ConcurrentHashMap<Integer,SoundData>();
	//static public ConcurrentHashMap<String,String> soundDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> soundDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	static public ConcurrentHashMap<String,Integer> soundDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	static public ConcurrentHashMap<Integer,String> soundDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();




	//===============================================================================================
	public void importSoundDataFiles()
	{//===============================================================================================


		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/SoundData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					SoundData soundAsset = SoundData.fromJSON(s);

					soundDataList.put(soundAsset.id(),soundAsset);
					//soundDataBase64List.put(soundAsset.name(),s);
					//soundDataByIDBase64List.put(soundAsset.id(),s);
					soundDataGetIDByNameList.put(soundAsset.name(),soundAsset.id());
					soundDataGetNameByIDList.put(soundAsset.id(),soundAsset.name());


					log.debug("Loaded Sound: "+soundAsset.name());
				}
			}
		}
	}





	static public ConcurrentHashMap<Integer,SpriteData> spriteDataList = new ConcurrentHashMap<Integer,SpriteData>();
	//static public ConcurrentHashMap<String,String> spriteDataBase64List = new ConcurrentHashMap<String,String>();
	//static public ConcurrentHashMap<Integer,String> spriteDataByIDBase64List = new ConcurrentHashMap<Integer,String>();
	static public ConcurrentHashMap<String,Integer> spriteDataGetIDByNameList = new ConcurrentHashMap<String,Integer>();
	static public ConcurrentHashMap<Integer,String> spriteDataGetNameByIDList = new ConcurrentHashMap<Integer,String>();




	//===============================================================================================
	public void importSpriteDataFiles()
	{//===============================================================================================


		List<String> b64List=null;

		try
		{
			b64List = IOUtils.readLines(ServerMain.class.getClassLoader().getResourceAsStream("data/SpriteData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(b64List!=null)
		{
			for(int i=0;i<b64List.size();i++)
			{
				String s = b64List.get(i);

				if(s.length()>0)
				{
					SpriteData spriteAsset = SpriteData.fromJSON(s);

					spriteDataList.put(spriteAsset.id(),spriteAsset);
					//spriteDataBase64List.put(spriteAsset.name(),s);
					//spriteDataByIDBase64List.put(spriteAsset.id(),s);
					spriteDataGetIDByNameList.put(spriteAsset.name(),spriteAsset.id());
					spriteDataGetNameByIDList.put(spriteAsset.id(),spriteAsset.name());

					log.debug("Loaded Sprite: "+spriteAsset.name());

					EventData eventAsset = spriteAsset.eventData;

					if(eventAsset!=null)
					{
						eventDataList.put(eventAsset.id(),eventAsset);
						//eventDataBase64List.put(eventAsset.name(),s);
						//eventDataByIDBase64List.put(eventAsset.id(),s);
						//eventDataGetIDByNameList.put(eventAsset.name(),eventAsset.id());
						//eventDataGetNameByIDList.put(eventAsset.id(),eventAsset.name());

						log.debug("Loaded Sprite Event: "+eventAsset.name());
					}




				}

			}

		}

	}


}
