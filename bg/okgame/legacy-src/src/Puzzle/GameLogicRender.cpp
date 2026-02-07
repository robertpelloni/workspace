#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#include "Room.h"

//=========================================================================================================================
void GameLogic::renderQueuedGarbage()
{//=========================================================================================================================

	if (queuedVSGarbageAmountFromOtherPlayer > 0)
	{
		if (garbageWaitCaption == nullptr)
		{
			garbageWaitCaption = getCaptionManager()->newManagedCaption(Caption::Position::NONE, 0, 0, -1, " ", announcementCaptionFontSize, true, BobColor::white, BobColor::clear, RenderOrder::ABOVE, 0.5f);
		}
		garbageWaitCaption->screenX = (float)(grid->getXOnScreenNoShake());
		garbageWaitCaption->screenY = (float)(grid->getYOnScreenNoShake());
		garbageWaitCaption->flashing = true;
		garbageWaitCaption->flashingTicksPerFlash = 500;
		garbageWaitCaption->setText("Garbage: "+ to_string(queuedVSGarbageAmountFromOtherPlayer)+" Wait: " + to_string(garbageWaitForPiecesSetCount));

		ArrayList<shared_ptr<BlockType>> blockTypes = currentGameType->getGarbageBlockTypes(getCurrentDifficulty());

		for (int i = 0; i < queuedVSGarbageAmountFromOtherPlayer; i++)
		{

			float scale = 1.0f;
			if(queuedVSGarbageAmountFromOtherPlayer>grid->getWidth()*2)
			{
				scale = (float)(grid->getWidth()*2) / (float)queuedVSGarbageAmountFromOtherPlayer;
			}

			shared_ptr<BlockType> blockType = blockTypes.get((blockTypes.size()-1) % (i+1));
			Block b(this, grid, nullptr, blockType);
			b.update();
			b.render(grid->getXInFBO() + ((i%(int)(grid->getWidth()/scale)) * blockWidth * scale), grid->getYInFBO() + (blockHeight*scale*(i/(grid->getWidth()/scale))), 1.0f, scale, false, false);
		}
	}
	else
	{
		if (garbageWaitCaption != nullptr)
		{
			garbageWaitCaption->setToFadeOutAndBeDeleted();
			garbageWaitCaption = nullptr;
		}
	}
}

//=========================================================================================================================
void GameLogic::renderHoldPiece()
{//=========================================================================================================================

	if(currentGameType->gameMode==GameMode::STACK || currentGameType->holdPieceEnabled==false)
	{
		if (holdCaption != nullptr)
		{
			holdCaption->visible = false;
		}
		return;
	}

	float holdBoxX = grid->getXOnScreenNoShake() - 3 * cellW();
	float holdBoxY = grid->getYOnScreenNoShake();
	float holdBoxW = (float)(2 * cellW());
	float holdBoxH = (float)(2 * cellH());

	if (holdCaption != nullptr)
	{
		holdCaption->visible = true;
		holdCaption->screenX = holdBoxX;
		holdCaption->screenY = holdBoxY - captionYSize;
	}

	GLUtils::drawFilledRectXYWH(holdBoxX, holdBoxY, holdBoxW, holdBoxH, 1, 1, 1, 1.0f);
	GLUtils::drawFilledRectXYWH(holdBoxX + 1, holdBoxY + 1, holdBoxW - 2, holdBoxH - 2, 0, 0, 0, 1.0f);

	if (holdPiece != nullptr)
	{
		float scale = 0.5f;

		float w = (float)cellW();
		float h = (float)cellH();

		float holdX = (float)(holdBoxX + 1 * w * scale);
		float holdY = (float)(holdBoxY + 1 * h * scale);

		if (holdPiece->getWidth() == 3)
		{
			holdX -= 0.5f * w * scale;
		}
		if (holdPiece->getWidth() == 4)
		{
			holdX -= 1 * w * scale;
		}

		for (int i = 0; i < (int)holdPiece->getNumBlocksInCurrentRotation() && i < holdPiece->blocks.size(); i++)
		{
			float blockX = (holdPiece->blocks.get(i)->xInPiece - holdPiece->getLowestOffsetX()) * w * scale;
			float blockY = (holdPiece->blocks.get(i)->yInPiece - holdPiece->getLowestOffsetY()) * h * scale;

			float x = holdX + blockX;
			float y = holdY + blockY;
			holdPiece->blocks.get(i)->render(x, y, 1.0f, 0.5f, true, false);
		}
	}
}

//=========================================================================================================================
bool GameLogic::nextPieceEnabled()
{//=========================================================================================================================
	if (extraStage3 == false && extraStage4 == false && currentGameType->nextPieceEnabled == true)
	{
		return true;
	}
	return false;
}

//=========================================================================================================================
void GameLogic::renderNextPiece()
{//=========================================================================================================================

	if (currentGameType->gameMode == GameMode::STACK || currentGameType->nextPieceEnabled == false)
	{
		if (nextCaption != nullptr)
		{
			nextCaption->visible = false;
		}
		return;
	}
	
	if (nextCaption != nullptr)
	{
		nextCaption->visible = true;
		nextCaption->screenX = grid->getXOnScreenNoShake() + ((grid->getWidth() / 2) * cellW());
		nextCaption->screenY = grid->getYOnScreenNoShake() - 4 * cellH();
	}

	if (nextPieceEnabled())
	{
		if (nextPieces.size() > 0)
		{
			if (nextPieces.isEmpty())
			{
				return;
			}

			float lastPieceX = 0;
			float startPieceX = 0;

			if (currentPiece != nullptr && currentPiece->yGrid <= 0 + GameLogic::aboveGridBuffer)
			{
				for (int i = 0; i < (int)currentPiece->getNumBlocksInCurrentRotation() && i < currentPiece->blocks.size(); i++)
				{
					float blockX = (float)(currentPiece->blocks.get(i)->xInPiece * cellW());

					float x = grid->getXInFBONoShake() + ((grid->getWidth() / 2) * cellW()) + blockX;
					if (currentPiece->getWidth() % 2 == 1)
					{
						x -= cellW();
					}

					if (x > lastPieceX)
					{
						lastPieceX = x;
					}
				}
			}

			for (int i = 0; i < nextPieces.size(); i++)
			{
				shared_ptr<Piece> nextPiece = nextPieces.get(i);

				startPieceX = lastPieceX + cellW();
				if (startPieceX > playingFieldX1)break;

				for (int b = 0; b < (int)nextPiece->getNumBlocksInCurrentRotation() && b < nextPiece->blocks.size(); b++)
				{
					if (i == 0 && (currentPiece == nullptr || currentPiece->yGrid > 0 + GameLogic::aboveGridBuffer))
					{
						float blockX = (float)(nextPiece->blocks.get(b)->xInPiece * cellW());
						float x = (float)(grid->getXOnScreenNoShake() + ((grid->getWidth() / 2) * cellW()) + blockX);
						if (nextPiece->getWidth() % 2 == 1)
						{
							x -= cellW();
						}

						float blockY = (float)(nextPiece->blocks.get(b)->yInPiece * cellH());

						float y = (float)(grid->getYOnScreenNoShake() - (cellH() * (nextPiece->getHeight())) + blockY);

						nextPiece->blocks.get(b)->render(x, y, 1.0f, 1.0f, true, false);

						if (x > lastPieceX)
						{
							lastPieceX = x;
						}
					}
					else
					{
						float s = 0.75f;

						float blockX = nextPiece->blocks.get(b)->xInPiece * cellW() * s;
						float x = startPieceX + (abs(nextPiece->getLowestOffsetX()) + 1) * cellW() * s + blockX;

						float blockY = nextPiece->blocks.get(b)->yInPiece * cellH() * s;
						float y = grid->getYOnScreenNoShake() - (cellH() * 3) + blockY;

						nextPiece->blocks.get(b)->render(x, y, 1.0f, s, true, false);

						if (x > lastPieceX)
						{
							lastPieceX = x;
						}
					}
				}
			}
		}
	}

}

//=========================================================================================================================
void GameLogic::renderCurrentPiece()
{//=========================================================================================================================
	if (currentPiece != nullptr)
	{
		if (currentGameType->gameMode == GameMode::STACK)
		{
		}
		else
		if (currentGameType->gameMode == GameMode::DROP)
		{
			if (pieceSetAtBottom == false && gravityThisFrame == false)
			{
				grid->renderGhostPiece(currentPiece);
			}
		}

		currentPiece->renderAsCurrentPiece();
	}
}

//=========================================================================================================================
void GameLogic::renderOverlays()
{//=========================================================================================================================

	if (timesToFlashScreenQueue > 0)
	{
		if (flashScreenOnOffToggle == true)
		{
			GLUtils::drawFilledRectXYWH(0, 0, (float)GLUtils::getViewportWidth(), (float)GLUtils::getViewportHeight(), 1.0f, 1.0f, 1.0f, Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha);
		}
	}
}

//=========================================================================================================================
void GameLogic::renderBackground()
{//=========================================================================================================================

	grid->renderBackground();

	grid->renderBorder();
}

//=========================================================================================================================
void GameLogic::renderBlocks()
{//=========================================================================================================================

	renderQueuedGarbage();

	for (int i = 0; i < fadingOutBlocks.size(); i++)
	{
		fadingOutBlocks.get(i)->renderDisappearing();
	}

	grid->render();

	renderHoldPiece();

	renderNextPiece();

	renderCurrentPiece();
}

//=========================================================================================================================
void GameLogic::renderForeground()
{//=========================================================================================================================

	grid->renderBlockOutlines();

	if (currentGameType->gameMode == GameMode::STACK)
	{
		grid->renderTransparentOverLastRow();
	}

	renderOverlays();

	
}




//=========================================================================================================================
void GameLogic::renderHighScoreMeters()
{//=========================================================================================================================
	
	if (triedToGetHighScore == false)
	{
		triedToGetHighScore = true;

		string gameTypeOrSequenceUUID = "";
		if (currentGameSequence->gameTypes.size() == 1)
		{
			gameTypeOrSequenceUUID = currentGameSequence->gameTypes.get(0)->uuid;
		}
		else
		{
			gameTypeOrSequenceUUID = currentGameSequence->uuid;
		}

		string difficultyString = currentGameSequence->currentDifficultyName;

		string objectiveString = "Play To Credits";
		if (getRoom()->endlessMode)objectiveString = "Endless Mode";

		myHighScore = getBobsGame()->getUserStatsForGame(gameTypeOrSequenceUUID, difficultyString, objectiveString);

		BobsGameLeaderBoardAndHighScoreBoard *currentLeaderboard = nullptr;
		if (getRoom()->endlessMode)
		{
			currentLeaderboard = getBobsGame()->getLeaderboardOrHighScoreBoardForGame(gameTypeOrSequenceUUID, difficultyString, objectiveString,
				false,
				false,
				false,
				false,
				false,
				true);
		}
		else
		{
			currentLeaderboard = getBobsGame()->getLeaderboardOrHighScoreBoardForGame(gameTypeOrSequenceUUID, difficultyString, objectiveString,
				false,
				false,
				false,
				false,
				true,
				false);
		}
		if(currentLeaderboard!=nullptr)
		{
			currentLeaderboardEntry = currentLeaderboard->entries.get(0);

			if (currentLeaderboardEntry->userName == "")
			{
				currentLeaderboardEntry = nullptr;
			}
		}

	}

	if (myHighScore != nullptr || currentLeaderboardEntry != nullptr)
	{


		long long highestScore = 0;

		if(myHighScore!=nullptr)
		{

			if(getRoom()->endlessMode)
			{
				if (myHighScore->mostBlocksCleared > highestScore)highestScore = myHighScore->mostBlocksCleared;
			}
			else
			{
				if (myHighScore->fastestClearedLength > highestScore)highestScore = myHighScore->fastestClearedLength;
			}
		}

		if(currentLeaderboardEntry != nullptr)
		{

			if (getRoom()->endlessMode)
			{
				if (currentLeaderboardEntry->mostBlocksClearedInOneGame > highestScore)highestScore = currentLeaderboardEntry->mostBlocksClearedInOneGame;
			}
			else
			{
				if (currentLeaderboardEntry->fastestClearedLength > highestScore)highestScore = currentLeaderboardEntry->fastestClearedLength;
			}
			
		}


		int startX = 0;
		for (int i = 0; i < infoCaptions->size(); i++)
		{
			Caption* c = infoCaptions->get(i);

			if (c != nullptr)
			{
				int x = c->screenX + c->getWidth();
				if (x > startX)startX = x;
			}
		}
		startX += 30;




		int startY = GLUtils::getViewportHeight() / 6 * 1;
		int height = GLUtils::getViewportHeight() / 6 * 4;

		long long currentScore = 0;
		if(getRoom()->endlessMode)
		{
			currentScore = blocksClearedTotal;
		}
		else
		{
			currentScore = totalTicksPassed;
		}

		if (highestScore == 0)return;

		int barWidth = GLUtils::getViewportWidth() / 50;

		int amount = 0;
		amount = height * (float)((float)currentScore / (float)highestScore);
		BobColor *c = BobColor::cyan;
		GLUtils::drawFilledRectXYWH((float)startX, (float)startY + (height - amount), barWidth, amount, c->rf(), c->gf(), c->bf(), 0.7f);

		if (myScoreBarCaption == nullptr)myScoreBarCaption = new Caption(getBobsGame(),Caption::Position::NONE, startX, startY + height, -1, "Current", 10, true, BobColor::white, BobColor::clear);
		myScoreBarCaption->screenX = startX;
		myScoreBarCaption->screenY = startY + height;
		myScoreBarCaption->update();
		myScoreBarCaption->render();


		string typeText = "";
		if (getRoom()->endlessMode)
		{
			typeText = "Blocks Cleared";
		}
		else
		{
			typeText = "Fastest Time To Completion";
		}
		if (scoreBarTypeCaption == nullptr)scoreBarTypeCaption = new Caption(getBobsGame(),Caption::Position::NONE, startX, startY + height, -1, typeText, 10, true, BobColor::white, BobColor::clear);
		scoreBarTypeCaption->screenX = startX;
		scoreBarTypeCaption->screenY = startY + height + 20;
		scoreBarTypeCaption->update();
		scoreBarTypeCaption->render();



		if (myHighScore != nullptr)
		{
			if (getRoom()->endlessMode)
			{
				currentScore = myHighScore->mostBlocksCleared;
			}
			else
			{
				currentScore = myHighScore->fastestClearedLength;
			}

			if (currentScore > 0)
			{
				startX += barWidth + 10;

				if (myScoreBarCaption != nullptr)
				{
					if (startX < myScoreBarCaption->screenX + myScoreBarCaption->getWidth())startX = myScoreBarCaption->screenX + myScoreBarCaption->getWidth();
				}

				amount = height * (float)((float)currentScore / (float)highestScore);
				c = BobColor::green;
				GLUtils::drawFilledRectXYWH((float)startX, (float)startY + (height - amount), barWidth, amount, c->rf(), c->gf(), c->bf(), 0.7f);

				if (myHighScoreBarCaption == nullptr)myHighScoreBarCaption = new Caption(getBobsGame(), Caption::Position::NONE, startX, startY + height, -1, "Your Best", 10, true, BobColor::white, BobColor::clear);
				myHighScoreBarCaption->screenX = startX;
				myHighScoreBarCaption->screenY = startY + height;
				myHighScoreBarCaption->update();
				myHighScoreBarCaption->render();
			}
		}


		if (currentLeaderboardEntry != nullptr)
		{

			if (getRoom()->endlessMode)
			{
				currentScore = currentLeaderboardEntry->mostBlocksClearedInOneGame;
			}
			else
			{
				currentScore = currentLeaderboardEntry->fastestClearedLength;
			}

			if (currentScore > 0)
			{
				startX += barWidth + 10;

				if(myScoreBarCaption !=nullptr)
				{
					if (startX < myScoreBarCaption->screenX + myScoreBarCaption->getWidth())startX = myScoreBarCaption->screenX + myScoreBarCaption->getWidth();
				}

				if(myHighScoreBarCaption!=nullptr)
				{
					if (startX < myHighScoreBarCaption->screenX + myHighScoreBarCaption->getWidth())startX = myHighScoreBarCaption->screenX + myHighScoreBarCaption->getWidth();
				}

				amount = height * (float)((float)currentScore / (float)highestScore);
				c = BobColor::magenta;
				GLUtils::drawFilledRectXYWH((float)startX, (float)startY + (height - amount), barWidth, amount, c->rf(), c->gf(), c->bf(), 0.7f);

				if (leaderboardBarCaption == nullptr)leaderboardBarCaption = new Caption(getBobsGame(), Caption::Position::NONE, startX, startY + height, -1, "Leaderboard ("+ FileUtils::removeSwearWords(currentLeaderboardEntry->userName) + ")", 10, true, BobColor::white, BobColor::clear);
				leaderboardBarCaption->screenX = startX;
				leaderboardBarCaption->screenY = startY + height;
				leaderboardBarCaption->update();
				leaderboardBarCaption->render();
			}
		}




	}
	
}

//=========================================================================================================================
void GameLogic::showResultsRanking()
{//=========================================================================================================================



}

//=========================================================================================================================
void GameLogic::doExtraStageEffects()
{//=========================================================================================================================

	if (currentLevel >= getCurrentDifficulty()->extraStage1Level)
	{
		grid->wigglePlayingField();
	}
}

//=========================================================================================================================

string GameLogic::getRandomMakePieceSound()
{//=========================================================================================================================

	int r = Math::randLessThan(7);
	if (r == 0)
	{
		return "piece1";
	}
	if (r == 1)
	{
		return "piece2";
	}
	if (r == 2)
	{
		return "piece3";
	}
	if (r == 3)
	{
		return "piece4";
	}
	if (r == 4)
	{
		return "piece5";
	}
	if (r == 5)
	{
		return "piece6";
	}
	return "piece7";
}

//=========================================================================================================================
float GameLogic::getSoundEffectSpeed()
{//=========================================================================================================================
	if (currentGameType->useRandomSoundModulation)
	{
		default_random_engine generator;
		uniform_real_distribution<double> distribution(0.0, 1.0);
		double number = distribution(generator);

		return 0.5f + (float)(number * 1.5f);
	}
	return 1.0f;
}

//=========================================================================================================================
float GameLogic::getVolume()
{//=========================================================================================================================
	if (mute)
	{
		return 0.0f;
	}
	else
	{
		return 1.0f;
	}
}
