
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger BobStatusBar::log = Logger("BobStatusBar");


BobTexture* BobStatusBar::blackBackgroundTexture = nullptr;
BobTexture* BobStatusBar::blackForegroundTexture = nullptr;
BobTexture* BobStatusBar::whiteBackgroundTexture = nullptr;
BobTexture* BobStatusBar::whiteForegroundTexture = nullptr;
BobTexture* BobStatusBar::backgroundTexture = nullptr;
BobTexture* BobStatusBar::foregroundTexture = nullptr;
BobTexture* BobStatusBar::glowTexture = nullptr;
BobTexture* BobStatusBar::dividerTexture = nullptr;
int BobStatusBar::sizeY = 26;
float BobStatusBar::glossAlpha = 1.0f;
bool BobStatusBar::useLightTheme = false;

BobStatusBar::BobStatusBar(BGClientEngine* g)
{ //=========================================================================================================================

	this->e = g;

	clockCaption = new ClockCaption(g);
	dayCaption = new DayCaption(g);
	moneyCaption = new MoneyCaption(g);
	ndButton = new NDButton(g);
	gameStoreButton = new GameStoreButton(g);
	stuffButton = new StuffButton(g);

	notificationManager = new NotificationManager(g);


	blackBackgroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/blackbarbackground.png");
	blackForegroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/blackbarforeground.png");

	whiteBackgroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/whitebarbackground.png");
	whiteForegroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/whitebarforeground.png");

	backgroundTexture = blackBackgroundTexture;
	foregroundTexture = blackForegroundTexture;


	glowTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/greenDot.png");
	dividerTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/dividerLine.png");
}

void BobStatusBar::init()
{ //=========================================================================================================================

	clockCaption->init();
	dayCaption->init();
	moneyCaption->init();
	ndButton->init();
	gameStoreButton->init();
	stuffButton->init();

	notificationManager->init();
}

void BobStatusBar::update()
{ //=========================================================================================================================
	clockCaption->update();
	dayCaption->update();
	moneyCaption->update();

	ndButton->update();
	gameStoreButton->update();
	stuffButton->update();

	notificationManager->update();
}

void BobStatusBar::setLightTheme()
{ //=========================================================================================================================

	if (useLightTheme == false)
	{
		useLightTheme = true;
		backgroundTexture = whiteBackgroundTexture;
		foregroundTexture = whiteForegroundTexture;


		clockCaption->setColors(new BobColor(200, 0, 0), BobColor::lightRed, nullptr);
		dayCaption->setColors(BobColor::black, BobColor::lighterGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void BobStatusBar::setDarkTheme()
{ //=========================================================================================================================
	if (useLightTheme == true)
	{
		useLightTheme = false;
		backgroundTexture = blackBackgroundTexture;
		foregroundTexture = blackForegroundTexture;


		clockCaption->setColors(BobColor::red, BobColor::darkerRed, nullptr);
		dayCaption->setColors(BobColor::white, BobColor::darkerGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void BobStatusBar::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void BobStatusBar::render()
{ //=========================================================================================================================


	if (enabled == false)
	{
		return;
	}


	render(0);

	clockCaption->render(0); //getText, lights
	dayCaption->render(0);
	moneyCaption->render(0);


	ndButton->render(0); //button graphics
	gameStoreButton->render(0);
	stuffButton->render(0);

	notificationManager->render(0); //notification string

	render(1); //status bar gloss


	clockCaption->render(1); //nothing
	dayCaption->render(1); //nothing
	moneyCaption->render(1); //divider


	ndButton->render(1); //dividers
	gameStoreButton->render(1);
	stuffButton->render(1);


	notificationManager->render(1); //nothing yet
}

void BobStatusBar::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	BobTexture* texture = nullptr;
	if (layer == 0)
	{
		texture = backgroundTexture;
	}
	if (layer == 1)
	{
		texture = foregroundTexture;
	}

	float alpha = 1.0f;
	if (layer == 1)
	{
		alpha = glossAlpha;
	}


	GLUtils::drawTexture(texture, 0, (float)GLUtils::getViewportWidth(), -6, (float)sizeY + 6, alpha, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
}

