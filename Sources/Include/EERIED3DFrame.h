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
// Code: Cyril Meynier
//       Ted Cipicchio (SDL/OpenGL support)
//
// Copyright (c) 1999 ARKANE Studios SA. All rights reserved
///////////////////////////////////////////////////////////////////////////////

// Desc: Class to manage the Direct3D environment objects such as buffers,
//       viewports, and 3D devices.
//
//       The class is initialized with the Initialize() function, after which
//       the Get????() functions can be used to access the objects needed for
//       rendering. If the device or display needs to be changed, the
//       ChangeDevice() function can be called. If the display window is moved
//       the changes need to be reported with the Move() function.
//
//       After rendering a frame, the ShowFrame() function filps or blits the
//       backbuffer contents to the primary. If surfaces are lost, they can be
//       restored with the RestoreSurfaces() function. Finally, if normal
//       Windows output is needed, the FlipToGDISurface() provides a GDI
//       surface to draw on.

#ifndef EERIED3DFRAME_H
#define EERIED3DFRAME_H

#ifndef EERIEFRAME_H
# error EERIED3DFrame.h should only be included via EERIEframe.h.
#endif

#define D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>
#include <ARX_Common.h>

//-----------------------------------------------------------------------------
// Name: CD3DFramework7
// Desc: The Direct3D sample framework class for DX7. Maintains the D3D
//       surfaces and device used for 3D rendering.
//-----------------------------------------------------------------------------
class CD3DFramework7
{
	public:
		// Internal variables for the framework class
		HWND                 m_hWnd;               // The window object
		BOOL                 m_bIsStereo;          // Stereo view mode
		LPDIRECTDRAW7        m_pDD;                // The DirectDraw object
		LPDIRECT3D7          m_pD3D;               // The Direct3D object
		LPDIRECT3DDEVICE7    m_pd3dDevice;         // The D3D device
		LPDIRECTDRAWSURFACE7 m_pddsBackBufferLeft; // For stereo modes
		DWORD                m_dwDeviceMemType;

	private:
		// Internal functions for the framework class
		HRESULT CreateZBuffer(GUID *);
		HRESULT CreateFullscreenBuffers(DDSURFACEDESC2 *);
		HRESULT CreateWindowedBuffers();
		HRESULT CreateDirectDraw(GUID *, DWORD);
		HRESULT CreateDirect3D(GUID *);
		HRESULT CreateEnvironment(GUID *, GUID *, DDSURFACEDESC2 *, DWORD);

	public:
		BOOL				m_bIsFullscreen;      // Fullscreen vs. windowed

		// Access functions for DirectX objects
		BOOL				b_dlg;
		long				bitdepth;

		RECT				m_rcScreenRect;       // Screen rect for window
		BOOL				m_bHasMoved;
		short				Ystart;
		short				Xstart;
		LPDIRECTDRAWSURFACE7 m_pddsZBuffer;        // The zbuffer surface
		LPDIRECTDRAWSURFACE7 m_pddsFrontBuffer;    // The primary surface
		LPDIRECTDRAWSURFACE7 m_pddsBackBuffer;     // The backbuffer surface

		DWORD                m_dwRenderWidth;      // Dimensions of the render target
		DWORD                m_dwRenderHeight;

		RECT	ClipWin;
		VOID	ClipWindow(long x0, long y0, long x1, long y1);
 

	public:
		CD3DFramework7();
		~CD3DFramework7();
		unsigned short	usBeginEndSceneCount;

		bool StartRender();
		bool EndRender();
		bool RenderError();
		void SetZBias(int);

		LPDIRECTDRAW7        GetDirectDraw()
		{
			return m_pDD;
		}
		LPDIRECT3D7          GetDirect3D()
		{
			return m_pD3D;
		}
		LPDIRECT3DDEVICE7    GetD3DDevice()
		{
			return m_pd3dDevice;
		}
 
		LPDIRECTDRAWSURFACE7 GetRenderSurface()
		{
			return m_pddsBackBuffer;
		}
		LPDIRECTDRAWSURFACE7 GetRenderSurfaceLeft()
		{
			return m_pddsBackBufferLeft;
		}

		// Functions to aid rendering
		HRESULT RestoreSurfaces();
		HRESULT ShowFrame();
		HRESULT FlipToGDISurface(BOOL bDrawFrame = FALSE);

		VOID    Move(INT x, INT y);

		// Creates the Framework
		HRESULT Initialize(HWND, GUID *, GUID *, DDSURFACEDESC2 *, DWORD);
		HRESULT DestroyObjects();

};

#endif
