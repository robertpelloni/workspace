#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#include "Room.h"

//=========================================================================================================================
void GameLogic::flashScreen()
{//=========================================================================================================================

	flashScreenTicksCounter += ticks();
	if (flashScreenTicksCounter > flashScreenSpeedTicks)
	{
		flashScreenTicksCounter = 0;

		flashScreenOnOffToggle = !flashScreenOnOffToggle;

		if (flashScreenOnOffToggle == true)
		{
			timesToFlashScreenQueue--;
		}
	}
}

//=========================================================================================================================
void GameLogic::flashChainBlocks()
{//=========================================================================================================================

	flashBlocksTicksCounter += ticks();

	if (flashBlocksTicksCounter > flashBlockSpeedTicks)
	{
		flashBlocksTicksCounter = 0;

		if (detectedChain())
		{
			for (int i = 0; i < currentChainBlocks.size(); i++)
			{
				currentChainBlocks.get(i)->flashingToBeRemovedLightDarkToggle = !currentChainBlocks.get(i)->flashingToBeRemovedLightDarkToggle;
			}
		}

		timesToFlashBlocksQueue--;
	}
}

//=========================================================================================================================
void GameLogic::removeFlashedChainBlocks()
{//=========================================================================================================================

	int linesCleared = 0;
	int blocksCleared = 0;

	if (currentChainBlocks.size() > 0)
	{
		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			shared_ptr<Block> b = currentChainBlocks.get(i);

			if (b->overrideAnySpecialBehavior == false)
			{
				if (b->blockType->makePieceTypeWhenCleared_UUID.size()>0)
				{
					shared_ptr<PieceType> pt = currentGameType->getPieceTypeByUUID(b->blockType->makePieceTypeWhenCleared_UUID.get(getRandomIntLessThan(b->blockType->makePieceTypeWhenCleared_UUID.size(), "removeFlashedChainBlocks")));
					shared_ptr<Piece> p = make_shared<Piece>(this, grid, pt, BlockType::emptyBlockType);
					p->init();
					nextPieceSpecialBuffer.add(p);

					if (p->pieceType->bombPiece)
					{
						makeAnnouncementCaption("BOMB", BobColor::blue);
						getAudioManager()->playSound(currentGameType->gotBombSound, getVolume(), 1.0f);
					}

					if (p->pieceType->weightPiece)
					{
						makeAnnouncementCaption("WEIGHT", BobColor::orange);
						getAudioManager()->playSound(currentGameType->gotWeightSound, getVolume(), 1.0f);
					}

					if (p->pieceType->clearEveryRowPieceIsOnIfAnySingleRowCleared)
					{
						makeAnnouncementCaption("FLASHING CLEAR", BobColor::green);
						getAudioManager()->playSound(currentGameType->flashingClearSound, getVolume(), 1.0f);
					}

					if (p->pieceType->pieceRemovalShooterPiece)
					{
						makeAnnouncementCaption("SUBTRACTOR", BobColor::red);
						getAudioManager()->playSound(currentGameType->gotSubtractorSound, getVolume(), 1.0f);
					}

					if (p->pieceType->pieceShooterPiece)
					{
						makeAnnouncementCaption("ADDER", BobColor::yellow);
						getAudioManager()->playSound(currentGameType->gotAdderSound, getVolume(), 1.0f);
					}
				}

				if (b->blockType->clearEveryOtherLineOnGridWhenCleared)
				{
					makeAnnouncementCaption("SCANLINE CLEAR", BobColor::red);
					getAudioManager()->playSound(currentGameType->scanlineClearSound, getVolume(), 1.0f);

					for (int y = gridH() - 2; y >= 0; y -= 2)
					{
						for (int x = 0; x < gridW(); x++)
						{
							shared_ptr<Block> c = grid->get(x, y);
							if (c != nullptr)
							{
								if (currentChainBlocks.contains(c) == false)
								{
									currentChainBlocks.add(c);
								}
							}
						}
					}

					grid->shakeSmall();
				}
			}
		}

		removeBlocksTicksCounter += ticks();

		while 
		(
			currentChainBlocks.size() > 0 
			&& 
			(
				currentGameType->removingBlocksDelayTicksBetweenEachBlock == 0 
				|| 
				removeBlocksTicksCounter > currentGameType->removingBlocksDelayTicksBetweenEachBlock
			)
		)
		{
			removeBlocksTicksCounter = 0;

			shared_ptr<Block> a = currentChainBlocks.get(0);
			ArrayList<shared_ptr<Block>> temp = grid->getConnectedBlocksUpDownLeftRight(a);
			if (temp.size() > 0)
			{
				for (int i = 0; i < temp.size(); i++)
				{
					shared_ptr<Block> b = temp.get(i);

					if (b->blockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size()>0)
					{
						b->popping = true;
						b->animationFrame = 0;

						checkForChainAgainIfNoBlocksPopping = true;
					}
				}
			}

			if (currentGameType->chainRule_CheckEntireLine)
			{
				for (int i = 0; i < currentChainBlocks.size(); i++)
				{
					shared_ptr<Block> b = currentChainBlocks.get(i);

					if (b != a && b->yGrid == a->yGrid)
					{
						currentChainBlocks.remove(b);

						grid->remove(b, true, true);

						blocksCleared++;
						blocksClearedThisGame++;
						blocksClearedThisLevel++;
						blocksClearedTotal++;

						i = -1;
					}
				}

				linesCleared++;
				linesClearedThisGame++;
				linesClearedThisLevel++;
				linesClearedTotal++;
			}

			currentChainBlocks.remove(a);

			grid->remove(a, true, true);

			blocksCleared++;
			blocksClearedThisGame++;
			blocksClearedThisLevel++;
			blocksClearedTotal++;
		}
	}

	timesToFlashScreenQueue += linesCleared;

	if (linesCleared == 1)
	{
		getAudioManager()->playSound(currentGameType->singleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared == 2)
	{
		getAudioManager()->playSound(currentGameType->doubleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared == 3)
	{
		getAudioManager()->playSound(currentGameType->tripleLineFlashingSound, getVolume(), 1.0f);
	}
	if (linesCleared >= 4)
	{
		getAudioManager()->playSound(currentGameType->quadLineFlashingSound, getVolume(), 1.0f);
		makeAnnouncementCaption("SOSUMI!", BobColor::green);
	}

	if (currentGameType->chainRule_CheckEntireLine)
	{
		lineClearDelayTicksCounter += linesCleared * currentGameType->lineClearDelayTicksAmountPerLine;
	}
	else
	{
		lineClearDelayTicksCounter += blocksCleared * currentGameType->lineClearDelayTicksAmountPerBlock;
	}

	currentChain = currentChainBlocks.size();
}

//=========================================================================================================================
void GameLogic::updateSpecialPiecesAndBlocks()
{//=========================================================================================================================

	if (currentPiece != nullptr)
	{
		currentPiece->update();
	}
	if (holdPiece != nullptr)
	{
		holdPiece->update();
	}

	if (nextPieces.size() > 0)
	{
		for (int i = 0; i < nextPieces.size(); i++)
		{
			nextPieces.get(i)->update();
		}
	}

	if (nextPieceSpecialBuffer.size() > 0)
	{
		for (int i = 0; i < nextPieceSpecialBuffer.size(); i++)
		{
			nextPieceSpecialBuffer.get(i)->update();
		}
	}

	if (fadingOutBlocks.size() > 0)
	{
		for (int i = 0; i < fadingOutBlocks.size(); i++)
		{
			fadingOutBlocks.get(i)->update();
		}
	}
}

//=========================================================================================================================
void GameLogic::addToChainBlocks(ArrayList<shared_ptr<Block>> &arr)
{//=========================================================================================================================

	if (arr.size() > 0)
	{

		for (int i = 0; i < arr.size(); i++)
		{
			if (currentChainBlocks.contains(arr.get(i)) == false)
			{
				currentChainBlocks.add(arr.get(i));
			}
		}
	}
}

//=========================================================================================================================
bool GameLogic::detectedChain()
{//=========================================================================================================================
	if (currentChainBlocks.size() > 0 && currentChainBlocks.size() > 0)
	{
		return true;
	}

	return false;
}


//=========================================================================================================================
void GameLogic::checkForChain()
{//=========================================================================================================================

	currentChainBlocks.clear();

	ArrayList<shared_ptr<BlockType>> ignoreTypes = currentGameType->getBlockTypesToIgnoreWhenCheckingChain(getCurrentDifficulty());
	ArrayList<shared_ptr<BlockType>> mustContainAtLeastOneTypes = currentGameType->getBlockTypesChainMustContain(getCurrentDifficulty());

	grid->setColorConnections(ignoreTypes);

	int toRow = grid->getHeight();
	if (currentGameType->gameMode == GameMode::STACK)
	{
		toRow = grid->getHeight() - 1;
	}

	if (currentGameType->chainRule_CheckEntireLine)
	{
		ArrayList<shared_ptr<Block>> chainBlocks = grid->checkLines(ignoreTypes, mustContainAtLeastOneTypes);
		addToChainBlocks(chainBlocks);
	}
	

	if (currentGameType->chainRule_AmountPerChain > 0)
	{
		ArrayList<shared_ptr<Block>> chainBlocks;

		for (int y = 0; y < toRow; y++)
		{
			for (int x = 0; x < grid->getWidth(); x++)
			{
				shared_ptr<Block> b = grid->get(x, y);

				if (b != nullptr && (ignoreTypes.isEmpty() || ignoreTypes.contains(b->blockType) == false))
				{
					if (currentGameType->chainRule_CheckRow)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
					if (currentGameType->chainRule_CheckColumn)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
					if (currentGameType->chainRule_CheckDiagonal)
					{
						grid->addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(b, chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
					}
				}
			}
		}

		if (currentGameType->chainRule_CheckRecursiveConnections)
		{
			grid->checkRecursiveConnectedRowOrColumn(chainBlocks, currentGameType->chainRule_AmountPerChain, 0, grid->getWidth(), 0, toRow, ignoreTypes, mustContainAtLeastOneTypes);
		}

		addToChainBlocks(chainBlocks);
	}
	

	if (currentGameType->chainRule_CheckTouchingBreakerBlocksChain)
	{
		ArrayList<shared_ptr<Block>> chainBlocks = grid->checkBreakerBlocks(toRow, ignoreTypes, mustContainAtLeastOneTypes);
		addToChainBlocks(chainBlocks);
	}
}

//=========================================================================================================================
void GameLogic::handleNewChain()
{//=========================================================================================================================
	if (detectedChain())
	{
		int chainMinimum = currentGameType->chainRule_AmountPerChain;
		if (currentGameType->chainRule_CheckEntireLine)chainMinimum = currentGameType->gridWidth;

		if (currentCombo == 0)
		{
			currentCombo = 1;
			currentChain = currentChainBlocks.size();

			makeAnnouncementCaption("Chain: " + to_string(currentChain));

			int bonusAmount = (currentChain - chainMinimum);
			if (currentGameType->chainRule_CheckEntireLine)
			{
				bonusAmount = currentChain / currentGameType->gridWidth;
				if (bonusAmount == 1)
				{
					bonusAmount = 0;
				}
			}

			if (bonusAmount > 0)
			{
				makeAnnouncementCaption("Chain Bonus: " + to_string(bonusAmount), BobColor::green);
				queueVSGarbageToSend(bonusAmount);
			}

			getBobsGame()->changeBG();

			getBobsGame()->shakeSmall();
			grid->shakeSmall();
		}
		else
		{
			currentCombo++;
			currentChain = currentChainBlocks.size();
			comboChainTotal += currentChain;
			totalCombosMade++;

			if (comboChainTotal > biggestComboChain)biggestComboChain = comboChainTotal;

			makeAnnouncementCaption("Chain: " + to_string(currentChain));

			makeAnnouncementCaption("" + to_string(currentCombo) + "X Combo! Total: " + to_string(comboChainTotal), BobColor::magenta);

			int bonusAmount = (currentChain - chainMinimum);
			if (bonusAmount == 0)
			{
				bonusAmount = 1;
			}

			makeAnnouncementCaption("Combo Bonus: " + to_string(bonusAmount) + " X " + to_string(currentCombo), BobColor::green);

			queueVSGarbageToSend(currentCombo);

			getBobsGame()->shakeHard();
			grid->shakeHard();
		}

		ArrayList<shared_ptr<Block>> addToChain;
		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			shared_ptr<Block> a = currentChainBlocks.get(i);

			ArrayList<shared_ptr<Block>> temp = grid->getConnectedBlocksUpDownLeftRight(a);
			if (temp.size() > 0)
			{
				for (int k = 0; k < temp.size(); k++)
				{
					shared_ptr<Block> b = temp.get(k);

					if (b->blockType->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks)
					{
						if (addToChain.contains(b) == false)
						{
							addToChain.add(b);
						}
					}
				}
			}
		}

		for (int i = 0; i < addToChain.size(); i++)
		{
			shared_ptr<Block> a = addToChain.get(i);
			if (currentChainBlocks.contains(a) == false)
			{
				currentChainBlocks.add(a);
			}
		}

		for (int i = 0; i < currentChainBlocks.size(); i++)
		{
			shared_ptr<Block> a = currentChainBlocks.get(i);
			a->flashingToBeRemoved = true;
		}

		if (currentGameType->gameMode == GameMode::STACK)
		{
			if (currentChainBlocks.size() > 3)
			{
				stopStackRiseTicksCounter += 1000 * currentChainBlocks.size();

				if (getRoom()->stackWaitLimit > -1 && stopStackRiseTicksCounter > getRoom()->stackWaitLimit)stopStackRiseTicksCounter = getRoom()->stackWaitLimit;
			}
		}

		getAudioManager()->playSound(currentGameType->blocksFlashingSound, getVolume(), 1.0f);
		timesToFlashBlocksQueue = timesToFlashBlocks;
	}
}

//=========================================================================================================================
void GameLogic::checkForFastMusic()
{//=========================================================================================================================

	bool anythingAboveThreeQuarters = grid->isAnythingAboveThreeQuarters();

	if (player->gridRule_showWarningForFieldThreeQuartersFilled && (anythingAboveThreeQuarters || extraStage1 || extraStage2 || extraStage3))
	{
		if (playingFastMusic == false)
		{
			playingFastMusic = true;

			if (currentGameType->fastMusic == "" || currentGameType->fastMusic.length() == 0)
			{
				getAudioManager()->stopMusic(playingMusic);
				playingMusic = currentGameType->normalMusic;
				getAudioManager()->playMusic(playingMusic, getVolume(), 1.5f, true);
			}
			else
			{
				getAudioManager()->stopMusic(playingMusic);
				playingMusic = currentGameType->fastMusic;
				getAudioManager()->playMusic(currentGameType->fastMusic, getVolume(), 1.0f, true);
			}

			if (anythingAboveThreeQuarters)
			{
				makeAnnouncementCaption("Uh oh, be careful!");
			}
		}
	}
	else
	{
		if (playingFastMusic == true)
		{
			playingFastMusic = false;

			getAudioManager()->stopMusic(playingMusic);
			playingMusic = currentGameType->normalMusic;
			getAudioManager()->playMusic(playingMusic);
		}
	}

	return;
}
