package com.bobsgame.client.engine.entity;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.concurrent.ConcurrentHashMap;

import com.bobsgame.client.Texture;


import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.shared.SpriteData;
import com.bobsgame.shared.MapData.RenderOrder;



//=========================================================================================================================
public class SpriteManager extends EnginePart
{//=========================================================================================================================

	public ConcurrentHashMap<Integer,Sprite> spriteByIDHashMap = new ConcurrentHashMap<Integer,Sprite>();
	public ConcurrentHashMap<String,Sprite> spriteByNameHashMap = new ConcurrentHashMap<String,Sprite>();






	public ArrayList<ScreenSprite> screenSpriteList = new ArrayList<ScreenSprite>();





	public Texture actionTexture = null;

	public int actionTextureFrame = 0;
	public int actionTextureAnimTicks = 0;


	//=========================================================================================================================
	public SpriteManager(Engine g)
	{//=========================================================================================================================

		super(g);

		if(actionTexture==null)actionTexture = GLUtils.loadTexture("res/misc/glowingDot.png");

	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}




	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================




		//for doorknobs and action icons for areas
		actionTextureAnimTicks+=Engine().engineTicksPassed();
		if(actionTextureAnimTicks>70)
		{
			actionTextureAnimTicks=0;
			actionTextureFrame++;
			if(actionTextureFrame>19)actionTextureFrame=0;
		}




		for(int n=0;n<screenSpriteList.size();n++)
		{
			Entity e = screenSpriteList.get(n);
			e.update();
		}


		//TODO: update sprites here, initialize them from server etc. need to reorganize this better.
		Enumeration<Sprite> e = spriteByIDHashMap.elements();
		while(e.hasMoreElements())
		{
			e.nextElement().update();
		}


	}





	//=========================================================================================================================
	public void renderScreenSprites(RenderOrder layer)
	{//=========================================================================================================================

		if(Engine().entityLayerEnabled)
		{
			//screensprites

			for(int n=0;n<screenSpriteList.size();n++)
			{
				ScreenSprite e = screenSpriteList.get(n);

				if(e.renderOrder()==layer)
				{
					if(e.shouldDraw())
					{
						e.render(1.0f);
					}
				}
			}
		}

	}







//
//	//=========================================================================================================================
//	Entity delete_entity(Entity e)
//	{//=========================================================================================================================
//










		//DONE: if this is a random entity with a custom texture, delete the texture.




		//if it is a normal entity, its texture is still stored in graphics memory, referenced by the spriteAsset.
		//next time that entity is created, its texture already exists.
		//TODO: if this becomes a problem and we start filling up the VRAM, we can unload these textures. in fact, might as well, it's not that expensive to load them again.
		//just need to set the spriteAsset texture to null after releasing it, the MD5 is still stored and it doesn't need the server call again.


		/*

		if(e!=null)
		{

			//if it's the first one, make the next one the first one.
			if(e==first_NPC)
			{
				//if it's the only one, then entity.next will be null and this will set first_NPC to null
				//otherwise it makes the next one the first one
				first_NPC = entity.next;

			}
			else //connect the chain before and after this one
			{

				Entity current_entity = first_NPC;

				//find the one that points to this entity (directly before it)
				while(current_entity.next!=entity)
				{
					current_entity = (Entity )current_entity.next;
				}

				//set it to point to the one after this one
				//if this one is the last one it will point to null, so this will just set the second to last one to null.
				current_entity.next = entity.next;
			}

			if(entity.sprite!=null)HARDWARE_delete_sprite(entity.sprite);
			entity.sprite=null;

			stop_chasing(entitypp);
			stop_avoiding(entitypp);
			stop_following(entitypp);
			stop_pulling_against(entitypp);

			//if it has an external pointer (it should) then set that pointer to null
			if(entity.entitypp!=null)
			{
				//set the external pointer to null
				if(*(entity.entitypp)!=null)
				{
					*(entity.entitypp)=null;
				}

				//set the internal pointer to that pointer to null (dont really need to do this)
				entity.entitypp=null;
			}

			free(entity);
		}

		*/
//		return null;
//	}
//


	//DONE: maybe have entities not controlled by pointers, but by text
	//make_entity("yuu",x,y);
	//delete_entity("yuu");
	//set_var("yuu",3);

//
//	//=========================================================================================================================
//	void delete_all_entitys()
//	{//=========================================================================================================================

		/*
		if(first_NPC!=null)
		{

			Entity current_entity = first_NPC;

			while(current_entity.next!=null)
			{
				Entity temp_entity = current_entity;
				current_entity = (Entity )current_entity.next;

				if(temp_entity!=first_NPC)delete_entity(&temp_entity);
			}
			if(current_entity!=first_NPC)delete_entity(&current_entity);
		}

		delete_chase_structs();
		delete_follow_structs();
		delete_avoid_structs();
		delete_pull_againster_structs();
		*/
//	}
//
//
//	//=========================================================================================================================
//	void pause()
//	{//=========================================================================================================================

			//just deletes all the sprites
		/*
			if(first_NPC==null)return;

			Entity current_entity = first_NPC;
			int stop=0;
			while(stop==0)
			{
				if(current_entity.sprite!=null)HARDWARE_delete_sprite(current_entity.sprite);
				current_entity.sprite=null;


				if(current_entity.next!=null)current_entity = (Entity )current_entity.next; else stop=1;
			}
			*/

//	}
//
//	//=========================================================================================================================
//	void unpause()
//	{//=========================================================================================================================
//
//
//	}








	//=========================================================================================================================
	public Sprite getSpriteAssetByIDOrRequestFromServerIfNotExist(int id)
	{//=========================================================================================================================


		if(id==-1)
		{
			Sprite s = spriteByIDHashMap.get(id);
			if(s==null)
			{
				s = new Sprite(Engine());
				s.initalizeWithSpriteData(null);
				spriteByNameHashMap.put(s.name(),s);
				spriteByIDHashMap.put(s.id(),s);
			}
			return s;
		}


		Sprite s = spriteByIDHashMap.get(id);
		if(s!=null)
		{
			if(s.getInitialized_S()==true)
			{
				return s;
			}
			else
			{
				s.sendDataRequest(id);
			}
		}
		else
		{
			s = new Sprite(Engine());
			spriteByIDHashMap.put(id,s);

			s.sendDataRequest(id);
		}


		//String e = "SpriteAsset not found! getSpriteByID():"+id;
		//Console.error(e);
		//log.error(e);

		return null;
	}





	//=========================================================================================================================
	public Sprite getSpriteByNameOrRequestFromServerIfNotExist(String spriteAssetName)
	{//=========================================================================================================================

		if(spriteAssetName==null||spriteAssetName.equals("")||spriteAssetName.length()==0)spriteAssetName = "none";

		if(spriteAssetName.equals("none")||spriteAssetName.equals("Camera"))
		{

			Sprite s = spriteByNameHashMap.get(spriteAssetName);
			if(s==null)
			{
				s = new Sprite(Engine());

				SpriteData d = null;
				if(spriteAssetName.equals("Camera"))d = new SpriteData(-1,"Camera","",0,0,1,false,false,false,false,false,false,false,false,false,false,false,false,false,false,null,"",0,0,0,"","");
				if(spriteAssetName.equals("none"))d = new SpriteData(-1,"none","",0,0,1,false,false,false,false,false,false,false,false,false,false,false,false,false,false,null,"",0,0,0,"","");

				s.initalizeWithSpriteData(d);
				spriteByNameHashMap.put(s.name(),s);
				spriteByIDHashMap.put(s.id(),s);
			}
			return s;
		}






		Sprite s = spriteByNameHashMap.get(spriteAssetName);
		if(s!=null)
		{
			if(s.getInitialized_S()==true)
			{
				return s;
			}
			else
			{
				s.sendDataRequest(spriteAssetName);
			}
		}
		else
		{
			s = new Sprite(Engine());
			spriteByNameHashMap.put(spriteAssetName,s);


			s.sendDataRequest(spriteAssetName);
		}



		//String e = "SpriteAsset not found! getSpriteByName():"+spriteAssetName;//this is normal
		//Console.error(e);
		//log.warn(e);

		return null;
	}






}
