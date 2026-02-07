package com.bobsgame.client.engine.game.nd;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

import org.apache.commons.io.IOUtils;
import org.slf4j.LoggerFactory;


import ch.qos.logback.classic.Logger;

import com.bobsgame.client.Cache;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.map.Map;
import com.bobsgame.client.engine.sound.Music;
import com.bobsgame.client.engine.sound.Sound;
import com.bobsgame.shared.DialogueData;
import com.bobsgame.shared.MapData;
import com.bobsgame.shared.MusicData;
import com.bobsgame.shared.SoundData;
import com.bobsgame.shared.SpriteAnimationSequence;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.Utils;





//=========================================================================================================================
public class GameDataLoader extends EnginePart
{//=========================================================================================================================


	public static Logger log = (Logger) LoggerFactory.getLogger(GameDataLoader.class);

	public static GameDataLoader gameDataLoader;

	boolean debug = false;

	//=========================================================================================================================
	public GameDataLoader(Engine g)
	{//=========================================================================================================================
		super(g);
		gameDataLoader = this;

		loadGameData();
	}

	//=========================================================================================================================
	public void loadGameData()
	{//=========================================================================================================================

		Cache.downloadBigFileToCacheIfNotExist("gameData");

		List<String> stringList=null;

		try
		{
			//stringList = IOUtils.readLines(gameDataLoader.getClass().getClassLoader().getResourceAsStream("gameData"));
			stringList = IOUtils.readLines(Utils.getResourceAsStream(Cache.cacheDir+"gameData"), StandardCharsets.UTF_8);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}

		if(stringList!=null)
		{
			for(int i=0;i<stringList.size();i++)
			{
				String s = stringList.get(i);

				if(s.length()>0)
				{

					if(s.equals("Sprites"))
					{
						s = stringList.get(++i);//spriteData base64 GZipped GSON
						while(s.length()>1)
						{
							if(s.length()>0)
							{
								s = s.substring(s.indexOf(":")+1);
								SpriteData data = new SpriteData();
								data.initFromString(s);

								Sprite sprite = new Sprite(Engine());
								sprite.initalizeWithSpriteData(data);

								SpriteManager().spriteByIDHashMap.put(sprite.id(), sprite);
								SpriteManager().spriteByNameHashMap.put(sprite.name(), sprite);

								s = stringList.get(++i);//spriteData base64 GZipped intArray
								sprite.indexDataIntArray = Utils.getIntArrayFromByteArray(Utils.unzipStringToByteArray(Utils.decodeBase64String(s)));

//								for(int b=0;b<sprite.indexDataIntArray.length/(sprite.width()/2);b++)
//								{
//									String r = "";
//									for(int x=0;x<sprite.width()/2;x++)
//									{
//										r = r+sprite.indexDataIntArray[(b*sprite.width()/2)+x];
//									}
//									System.out.println(r);
//								}

								s = stringList.get(++i);//spritePalette base64 GZipped rgbByteArray
								sprite.paletteRGBByteArray = Utils.unzipStringToByteArray(Utils.decodeBase64String(s));

								//save to cache folder as md5 name
								byte[] byteArray = Utils.getByteArrayFromIntArray(sprite.indexDataIntArray);
								String md5FileName = Utils.getByteArrayMD5Checksum(byteArray);
								Cache.saveByteArrayToCache(byteArray,md5FileName);
								data.setDataMD5(md5FileName);

								byteArray = sprite.paletteRGBByteArray;
								md5FileName = Utils.getByteArrayMD5Checksum(byteArray);
								Cache.saveByteArrayToCache(byteArray,md5FileName);
								data.setPaletteMD5(md5FileName);

								sprite.loadTextures();

								if(debug)log.debug("Loaded Sprite: "+data.name());
								for(int n=0;n<data.animationList().size();n++)
								{
									SpriteAnimationSequence a = data.animationList().get(n);
									if(debug)log.debug("Loaded Animation: "+a.frameSequenceName);
								}

								s = stringList.get(++i);//blank line or another spriteData
							}
						}

					}


					if(s.equals("Maps"))
					{
						s = stringList.get(++i);//mapData base64 GZipped GSON
						while(s.length()>1)
						{
							if(s.length()>0)
							{
								s = s.substring(s.indexOf(":")+1);
								MapData data = new MapData();
								data.initFromString(s);

								Map map = new Map(Engine(),data);


								MapManager().mapList.add(map);
								MapManager().mapByIDHashMap.put(map.id(), map);
								MapManager().mapByNameHashMap.put(map.name(), map);

								s = stringList.get(++i);//tileData base64 GZipped intArray
								map.tilesetIntArray = Utils.getIntArrayFromByteArray(Utils.unzipStringToByteArray(Utils.decodeBase64String(s)));

								s = stringList.get(++i);//paletteData base64 GZipped rgbByteArray
								map.paletteRGBByteArray = Utils.unzipStringToByteArray(Utils.decodeBase64String(s));

								s = stringList.get(++i);//mapLayerData base64 GZipped intArray
								map.saveDataToCache(Utils.getIntArrayFromByteArray(Utils.unzipStringToByteArray(Utils.decodeBase64String(s))),map.tilesetIntArray,map.paletteRGBByteArray);


								if(debug)log.debug("Loaded Map: "+data.name());

								s = stringList.get(++i);//blank line or another mapData
							}
						}

					}

					if(s.equals("Sounds"))
					{
						s = stringList.get(++i);
						while(s.length()>1)
						{
							if(s.length()>0)
							{
								s = s.substring(s.indexOf(":")+1);
								//SoundData data = new SoundData();
								//data.initFromString(s);

								//Sound sound = new Sound(Engine(),data);


								s = stringList.get(++i);//tileData base64 GZipped intArray
								//sound.byteData = Utils.unzipStringToByteArray(Utils.decodeBase64String(s));


								//if(debug)log.debug("Loaded Sound: "+data.name());

								s = stringList.get(++i);//blank line or another soundData
							}
						}

					}


					if(s.equals("Music"))
					{
						s = stringList.get(++i);
						while(s.length()>1)
						{
							if(s.length()>0)
							{
								s = s.substring(s.indexOf(":")+1);
								//MusicData data = new MusicData();
								//data.initFromString(s);

								//Music music = new Music(Engine(),data);


								s = stringList.get(++i);//tileData base64 GZipped intArray
								//music.byteData = Utils.unzipStringToByteArray(Utils.decodeBase64String(s));


								//if(debug)log.debug("Loaded Music: "+data.name());

								s = stringList.get(++i);//blank line or another soundData
							}
						}

					}


				}


			}

		}





	}































}
