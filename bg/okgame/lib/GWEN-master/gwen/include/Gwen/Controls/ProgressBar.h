/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_PROGRESSBAR_H
#define GWEN_CONTROLS_PROGRESSBAR_H
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"


namespace Gwen
{
	namespace Controls
	{
		class GWEN_EXPORT ProgressBar : public Label
		{
			public:

				GWEN_CONTROL( ProgressBar, Label );

				virtual void Render( Skin::Base* skin );

				virtual void SetVertical()  { m_bHorizontal = false; }
				virtual void SetHorizontal() { m_bHorizontal = true; }

				

#if defined(ORBIS) || defined(__ORBIS__) || defined(__MACOSX__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif
				virtual void SetValue(float val);
				virtual float GetValue() const { return m_fProgress; }
#if defined(ORBIS) || defined(__ORBIS__) || defined(__MACOSX__)
#pragma clang diagnostic pop
#endif

				

				virtual void SetAutoLabel( bool b ) { m_bAutoLabel = b; }

				virtual float GetCycleSpeed();
				virtual void SetCycleSpeed( float f );

				virtual void CycleThink( float fDelta );

			protected:

				float m_fProgress;
				float m_fCycleSpeed;

				bool m_bHorizontal;
				bool m_bAutoLabel;
		};
	}
}
#endif
