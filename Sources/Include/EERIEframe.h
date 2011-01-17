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
// EERIEFrame
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

#ifndef EERIEFRAME_H
#define EERIEFRAME_H

#define D3D_OVERLOADS
#include <ddraw.h>
#include <d3d.h>
#include <ARX_Common.h>

//-----------------------------------------------------------------------------
// Flags used for the Initialize() method of a CD3DFramework object
//-----------------------------------------------------------------------------
#define FW_FULLSCREEN				0x00000001 // Use fullscreen mode
#define FW_STEREO					0x00000002 // Use stereo-scopic viewing
#define FW_ZBUFFER					0x00000004 // Create and use a zbuffer
#define FW_NO_FPUSETUP				0x00000008 // Don't use default DDSCL_FPUSETUP flag

//-----------------------------------------------------------------------------
// Errors that the Initialize() and ChangeDriver() calls may return
//-----------------------------------------------------------------------------
#define FWERR_INITIALIZATIONFAILED	0x82000000
#define FWERR_NODIRECTDRAW			0x82000001
#define FWERR_COULDNTSETCOOPLEVEL	0x82000002
#define FWERR_NODIRECT3D			0x82000003
#define FWERR_NO3DDEVICE			0x82000004
#define FWERR_NOZBUFFER				0x82000005
#define FWERR_INVALIDZBUFFERDEPTH	0x82000006
#define FWERR_NOVIEWPORT			0x82000007
#define FWERR_NOPRIMARY				0x82000008
#define FWERR_NOCLIPPER				0x82000009
#define FWERR_BADDISPLAYMODE		0x8200000a
#define FWERR_NOBACKBUFFER			0x8200000b
#define FWERR_NONZEROREFCOUNT		0x8200000c
#define FWERR_NORENDERTARGET		0x8200000d
#define FWERR_INVALIDMODE			0x8200000e
#define FWERR_NOTINITIALIZED		0x8200000f

#if USE_SDL
#include "EERIESdlFrame.h"
typedef CSdlFramework CFramework;
#else
#include "EERIED3DFrame.h"
typedef CD3DFramework7 CFramework;
#endif

#endif
