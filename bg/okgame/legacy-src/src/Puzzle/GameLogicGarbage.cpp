#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#include "Room.h"

//=========================================================================================================================
void GameLogic::gotVSGarbageFromOtherPlayer(int amount)
{//=========================================================================================================================

	

	garbageWaitForPiecesSetCount += 3;
	if (garbageWaitForPiecesSetCount > 4)
	{
		garbageWaitForPiecesSetCount = 4;
	}

	if(getRoom()->multiplayer_GarbageScaleByDifficulty)
	{
		//it is scaled on both send and receive
		//so Insane send is cut in half, then cut in half again for beginner
		if(getCurrentDifficulty()->name == "Beginner")amount = (int)(amount*0.5f);
		if(getCurrentDifficulty()->name == "Easy")amount = (int)(amount*0.75f);
		if(getCurrentDifficulty()->name == "Normal")amount = (int)(amount*1.0f);
		if(getCurrentDifficulty()->name == "Hard")amount = (int)(amount*1.5f);
		if(getCurrentDifficulty()->name == "Insane")amount = (int)(amount*2.0f);
	}

	queuedVSGarbageAmountFromOtherPlayer += amount;


	if (getRoom()->multiplayer_GarbageLimit>0 && queuedVSGarbageAmountFromOtherPlayer > getRoom()->multiplayer_GarbageLimit)queuedVSGarbageAmountFromOtherPlayer = getRoom()->multiplayer_GarbageLimit;

	makeAnnouncementCaption("Got VS Garbage: " + to_string(amount));

//	if (garbageBlock == nullptr)
//	{
//
//		ArrayList<shared_ptr<PieceType>> garbagePieceTypes = currentGameType->getGarbagePieceTypes(getCurrentDifficulty());
//		if (garbagePieceTypes.size() == 0)garbagePieceTypes.add(PieceType::emptyPieceType);
//
//		shared_ptr<PieceType> pieceType = grid->getRandomPieceType(garbagePieceTypes);
//
//		ArrayList<shared_ptr<BlockType>> garbageBlockTypes = currentGameType->getGarbageBlockTypes(getCurrentDifficulty());
//
//		shared_ptr<Piece> p(new Piece(this, grid, pieceType, garbageBlockTypes));
//		p->init();
//
//		garbageBlock = p->blocks.get(0);
//	}
}

//=========================================================================================================================
void GameLogic::processQueuedGarbageSentFromOtherPlayer()
{//=========================================================================================================================

	if (queuedVSGarbageAmountFromOtherPlayer > 0)
	{
		if (garbageWaitForPiecesSetCount == 0)
		{
			//makeAnnouncementCaption("Processed VS Garbage: " + to_string(queuedGarbageAmountFromOtherPlayer));

			int garbageMultiplier = 2;
			//TODO: if garbageRuleMax, drop one line per garbageAmount
			//garbageRuleMultiplier, divide gridWidth times amount
			//could also drop indiviual garbage instead of lines

			while (queuedVSGarbageAmountFromOtherPlayer/(grid->getWidth()/garbageMultiplier) > 0)
			{
				queuedVSGarbageAmountFromOtherPlayer-= grid->getWidth();
				if (queuedVSGarbageAmountFromOtherPlayer < 0)queuedVSGarbageAmountFromOtherPlayer = 0;

				if (isNetworkPlayer)log.warn("Garbage");
				else log.debug("Garbage");

				if (currentGameType->vsGarbageRule == VSGarbageDropRule::FALL_FROM_CEILING_IN_EVEN_ROWS)
				{
					makeGarbageRowFromCeiling();
					moveDownBlocksOverBlankSpaces();
				}
				if (currentGameType->vsGarbageRule == VSGarbageDropRule::RISE_FROM_FLOOR_IN_EVEN_ROWS)
				{
					makeGarbageRowFromFloor();
				}
			}
		}
	}
}

//=========================================================================================================================
void GameLogic::queueVSGarbageToSend(int amount)
{//=========================================================================================================================

	//if queued garbage, send it to the other side and negate it

	//garbage types per game?

	amount *= getRoom()->multiplayer_GarbageMultiplier;


	if (getRoom()->multiplayer_GarbageScaleByDifficulty)
	{
		//it is scaled on both send and receive
		//so Insane send is cut in half, then cut in half again for beginner
		if (getCurrentDifficulty()->name == "Beginner")amount = (int)(amount*2.0f);
		if (getCurrentDifficulty()->name == "Easy")amount = (int)(amount*1.5f);
		if (getCurrentDifficulty()->name == "Normal")amount = (int)(amount*1.0f);
		if (getCurrentDifficulty()->name == "Hard")amount = (int)(amount*0.75f);
		if (getCurrentDifficulty()->name == "Insane")amount = (int)(amount*0.5f);
	}

	if (queuedVSGarbageAmountFromOtherPlayer > 0)
	{
		if (amount >= queuedVSGarbageAmountFromOtherPlayer)
		{
			makeAnnouncementCaption("Negated VS Garbage: " + to_string(queuedVSGarbageAmountFromOtherPlayer));

			amount -= queuedVSGarbageAmountFromOtherPlayer;
			queuedVSGarbageAmountFromOtherPlayer = 0;
		}
		else
		{
			if (amount < queuedVSGarbageAmountFromOtherPlayer)
			{
				makeAnnouncementCaption("Negated VS Garbage: " + to_string(amount));
				queuedVSGarbageAmountFromOtherPlayer -= amount;
				amount = 0;
			}
		}
	}

	if (getBobsGame()->isMultiplayer() && getRoom()->multiplayer_DisableVSGarbage==false)
	{
		if (amount > 0)
		{
			queuedVSGarbageAmountToSend += amount;
			makeAnnouncementCaption("Sent VS Garbage: " + to_string(amount) + " Total: " + to_string(queuedVSGarbageAmountToSend));
		}
	}
}

//=========================================================================================================================
void GameLogic::processGarbageRules()
{//=========================================================================================================================

	bool makeGarbage = false;

	if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::TICKS)
	{
		playingFieldGarbageValueCounter += ticks();
		if (playingFieldGarbageValueCounter > getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
		{
			playingFieldGarbageValueCounter = 0;
			makeGarbage = true;
		}
	}
	else
	{
		if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::PIECES_MADE)
		{
			if (piecesMadeThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
			{
				playingFieldGarbageValueCounter = piecesMadeThisGame;
				makeGarbage = true;
			}
		}
		else
		{
			if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::BLOCKS_CLEARED)
			{
				if (blocksClearedThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
				{
					playingFieldGarbageValueCounter = blocksClearedThisGame;
					makeGarbage = true;
				}
			}
			else
			{
				if (currentGameType->playingFieldGarbageSpawnRule == GarbageSpawnRule::LINES_CLEARED)
				{
					if (linesClearedThisGame >= playingFieldGarbageValueCounter + getCurrentDifficulty()->playingFieldGarbageSpawnRuleAmount)
					{
						playingFieldGarbageValueCounter = linesClearedThisGame;
						makeGarbage = true;
					}
				}
			}
		}
	}

	if (makeGarbage)
	{
		makeGarbageRowFromFloor();
	}
}

//=========================================================================================================================
void GameLogic::makeGarbageRowFromFloor()
{//=========================================================================================================================
	grid->makeGarbageRowFromFloor();
	manuallyApplyGravityWithoutChainChecking();
	//forceGravityThisFrame = true;

	grid->shakeMedium();
}

//=========================================================================================================================
void GameLogic::makeGarbageRowFromCeiling()
{//=========================================================================================================================
	grid->makeGarbageRowFromCeiling();
	//forceGravityThisFrame = true;
	manuallyApplyGravityWithoutChainChecking();

	grid->shakeHard();
}
