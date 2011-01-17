/*
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
///////////////////////////////////////////////////////////////////////////////
// EERIED3DFrame
///////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Updates: (date) (person) (update)
//
// Code: Ted Cipicchio
//
// Copyright (c) 1999 ARKANE Studios SA. All rights reserved
///////////////////////////////////////////////////////////////////////////////

#ifndef EERIESDLFRAME_H
#define EERIESDLFRAME_H

#ifndef EERIEFRAME_H
# error EERIESdlFrame.h should only be included via EERIEframe.h.
#endif

#include <ARX_Common.h>

//-----------------------------------------------------------------------------
// Name: CSdlFramework
// Desc: The SDL/OpenGL sample framework class.  Maintains OpenGL objects used
//       for 3D rendering.
//-----------------------------------------------------------------------------
class CSdlFramework
{
	public:
		// Internal variables for the framework class
		BOOL                 m_bIsStereo;          // Stereo view mode

	private:
		// Internal functions for the framework class

	public:
		BOOL				m_bIsFullscreen;      // Fullscreen vs. windowed

		// Access functions for DirectX objects
		BOOL				b_dlg;
		long				bitdepth;

		RECT				m_rcScreenRect;       // Screen rect for window
		BOOL				m_bHasMoved;
		short				Ystart;
		short				Xstart;

		DWORD                m_dwRenderWidth;      // Dimensions of the render target
		DWORD                m_dwRenderHeight;

		RECT	ClipWin;
		VOID	ClipWindow(long x0, long y0, long x1, long y1);
 

	public:
		CSdlFramework();
		~CSdlFramework();
		unsigned short	usBeginEndSceneCount;

		bool StartRender();
		bool EndRender();
		bool RenderError();
		void SetZBias(int);

		// Functions to aid rendering
		HRESULT RestoreSurfaces();
		HRESULT ShowFrame();
		HRESULT FlipToGDISurface(BOOL bDrawFrame = FALSE);

		void    Move(INT x, INT y);

		// Creates the Framework
		HRESULT Initialize(DWORD);
		HRESULT DestroyObjects();

};

#endif
