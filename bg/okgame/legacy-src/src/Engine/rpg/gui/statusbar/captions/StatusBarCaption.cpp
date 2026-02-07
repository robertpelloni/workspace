#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once


Logger BobStatusBarCaption::log = Logger("BobStatusBarCaption");

BobStatusBarCaption::BobStatusBarCaption()
{ //=========================================================================================================================
}

BobStatusBarCaption::BobStatusBarCaption(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void BobStatusBarCaption::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void BobStatusBarCaption::init()
{ //=========================================================================================================================
}

void BobStatusBarCaption::update()
{ //=========================================================================================================================
}

void BobStatusBarCaption::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	if (layer == 0)
	{
		if (caption != nullptr)
		{
			caption->render();
		}
		if (light != nullptr)
		{
			light->renderLight();
		}
	}
}

void BobStatusBarCaption::updateCaption(const string& s)
{ //=========================================================================================================================

	if (caption == nullptr)
	{
		caption = new Caption(getEngine(), Caption::Position::NONE, 0, 2, -1, s, BobFont::font_small_16_outlined_smooth, currentFGColor, currentAAColor, currentBGColor, RenderOrder::OVER_TEXT, 1.0f, 0);
	}
	else
	{
		if (s.compare(caption->text) != 0)
		{
			caption->setText(s);
		}
	}
}

void BobStatusBarCaption::setColors(BobColor* fg, BobColor* aa, BobColor* bg)
{ //=========================================================================================================================

	currentFGColor = fg;
	currentAAColor = aa;
	currentBGColor = bg;

	if (caption != nullptr)
	{
		caption->setTextColor(fg, aa, bg);
	}
}

void BobStatusBarCaption::setDefaultColor()
{ //=========================================================================================================================
	setColors(defaultFGColor, defaultAAColor, defaultBGColor);
}

