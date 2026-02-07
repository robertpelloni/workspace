package com.bobsgame.server.assets;


//=========================================================================================================================
public class Flag
{//=========================================================================================================================

	public int id = -1;


	private boolean value = false;



	//=========================================================================================================================
	public Flag(int id)
	{//=========================================================================================================================


		this.id=id;


		//we don't particularly need to know what the actual flag name is... ID is fine.
		//so, don't really care about getting the flag name from the server.
		//it's a good idea for debugging.

	}






}
