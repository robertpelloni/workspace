#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger BobStatusBarButton::log = Logger("BobStatusBarButton");

BobStatusBarButton::BobStatusBarButton()
{ //=========================================================================================================================
}

BobStatusBarButton::BobStatusBarButton(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void BobStatusBarButton::init()
{ //=========================================================================================================================
}

void BobStatusBarButton::setOffsets()
{ //=========================================================================================================================
}

void BobStatusBarButton::clicked()
{ //=========================================================================================================================
}

bool BobStatusBarButton::isAssociatedMenuActive()
{ //=========================================================================================================================
	return false;
}

void BobStatusBarButton::update()
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	setOffsets();

	if (getControlsManager()->getMouseX() > clickX0 && getControlsManager()->getMouseX() < clickX1 && getControlsManager()->getMouseY() > (GLUtils::getViewportHeight() - BobStatusBar::sizeY))
	{
		glow = true;
		glowAlpha = 1.0f;

//		if (getControlsManager()->MOUSE_0_HELD == true)
//		{
//			pressedOffsetY = 2;
//		}
//		else
//		{
//			pressedOffsetY = 0;
//		}
//
//		if (getControlsManager()->MOUSE_0_PRESSED == true)
//		{
//			clicked();
//		}
	}
	else if (isAssociatedMenuActive() == true)
	{
		glow = true;
	}
	else
	{
		glow = false;
	}

	if (pulse == true)
	{
		glow = true;

		pulseTicks += (int)getEngine()->engineTicksPassed();

		if (pulseTicks > lastPulseTicks + 1000)
		{
			lastPulseTicks = pulseTicks;

			pulseInOut = !pulseInOut;
		}

		if (pulseInOut == true)
		{
			glowAlpha += ((float)(getEngine()->engineTicksPassed()) / 1000.0f);
			if (glowAlpha > 1.0f)
			{
				glowAlpha = 1.0f;
			}
		}
		else
		{
			glowAlpha -= ((float)(getEngine()->engineTicksPassed()) / 1000.0f);
			if (glowAlpha < 0.0f)
			{
				glowAlpha = 0.0f;
			}
		}
	}
	else
	{
		glowAlpha = 1.0f;
	}
}

void BobStatusBarButton::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void BobStatusBarButton::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	if (texture == nullptr)
	{
		return;
	}

	if (layer == 0)
	{
		if (glow)
		{
			GLUtils::drawTexture(BobStatusBar::glowTexture, (float)glowX0, (float)glowX1, (float)glowY0, (float)glowY1, glowAlpha, GLUtils::FILTER_LINEAR);
		}

		GLUtils::drawTexture(texture, (float)offsetX0, (float)offsetX1, (float)offsetY0 + pressedOffsetY, (float)(BobStatusBar::sizeY - offsetY1) + pressedOffsetY, 1.0f, GLUtils::FILTER_LINEAR);

		if (glow)
		{
			GLUtils::drawTexture(BobStatusBar::glowTexture, (float)glowX0, (float)glowX1, (float)glowY0, (float)glowY1, 0.2f, GLUtils::FILTER_LINEAR);
		}
	}

	if (layer == 1)
	{
		GLUtils::drawTexture(BobStatusBar::dividerTexture, (float)dividerX, (float)dividerX + 3, 0, (float)BobStatusBar::sizeY - 1, 1.0f, GLUtils::FILTER_LINEAR);
	}
}

