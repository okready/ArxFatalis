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
//////////////////////////////////////////////////////////////////////////////////////
//   @@        @@@        @@@                @@                           @@@@@     //
//   @@@       @@@@@@     @@@     @@        @@@@                         @@@  @@@   //
//   @@@       @@@@@@@    @@@    @@@@       @@@@      @@                @@@@        //
//   @@@       @@  @@@@   @@@  @@@@@       @@@@@@     @@@               @@@         //
//  @@@@@      @@  @@@@   @@@ @@@@@        @@@@@@@    @@@            @  @@@         //
//  @@@@@      @@  @@@@  @@@@@@@@         @@@@ @@@    @@@@@         @@ @@@@@@@      //
//  @@ @@@     @@  @@@@  @@@@@@@          @@@  @@@    @@@@@@        @@ @@@@         //
// @@@ @@@    @@@ @@@@   @@@@@            @@@@@@@@@   @@@@@@@      @@@ @@@@         //
// @@@ @@@@   @@@@@@@    @@@@@@           @@@  @@@@   @@@ @@@      @@@ @@@@         //
// @@@@@@@@   @@@@@      @@@@@@@@@@      @@@    @@@   @@@  @@@    @@@  @@@@@        //
// @@@  @@@@  @@@@       @@@  @@@@@@@    @@@    @@@   @@@@  @@@  @@@@  @@@@@        //
//@@@   @@@@  @@@@@      @@@      @@@@@@ @@     @@@   @@@@   @@@@@@@    @@@@@ @@@@@ //
//@@@   @@@@@ @@@@@     @@@@        @@@  @@      @@   @@@@   @@@@@@@    @@@@@@@@@   //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@      @@@@@      //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@       @@        //
//@@@    @@@  @@@ @@@@@                          @@            @@@                  //
//            @@@ @@@                           @@             @@        STUDIOS    //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// EERIED3DApp
//////////////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Updates: (date) (person) (update)
//
// Code:	Cyril Meynier
//			Sébastien Scieux	(Zbuffer)
//			Ted Cipicchio		(SDL/OpenGL support)
//
// Copyright (c) 1999 ARKANE Studios SA. All rights reserved
//////////////////////////////////////////////////////////////////////////////////////

#ifndef  EERIED3DAPP_H
#define  EERIED3DAPP_H

#define  D3D_OVERLOADS

#include <windows.h>
#include <commctrl.h>
#include <d3d.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//-----------------------------------------------------------------------------
typedef struct
{
	HWND		hWnd;
	long		CreationToolBar;
	long		ToolBarNb;
	LPCTBBUTTON Buttons;
	long		Bitmap;
	char*		String;
	long		Type;
} EERIETOOLBAR;

//-----------------------------------------------------------------------------
extern LPDIRECT3DDEVICE7 GDevice;

extern HWND MSGhwnd;

//-----------------------------------------------------------------------------
// Name: class CD3DApplication
// Desc:
//-----------------------------------------------------------------------------
class CD3DApplication
{
		// Internal variables and member functions
		BOOL            m_bSingleStep;
		DWORD           m_dwBaseTime;
		DWORD           m_dwStopTime;

		HRESULT Render3DEnvironment();
		VOID    DisplayFrameworkError(HRESULT, DWORD);

public:
		float			fMouseSensibility;
protected:
		// Overridable variables for the app
		TCHAR*			m_strWindowTitle;
		BOOL			m_bAppUseZBuffer;
		BOOL			m_bAppUseStereo;
		BOOL			m_bShowStats;
		HRESULT(*m_fnConfirmDevice)(DDCAPS *, D3DDEVICEDESC7 *);
		HWND				 CreateToolBar(HWND hWndParent, long tbb, HINSTANCE hInst);

		// Overridable functions for the 3D scene created by the app
		virtual HRESULT OneTimeSceneInit()
		{
			return S_OK;
		}
		virtual HRESULT DeleteDeviceObjects()
		{
			return S_OK;
		}
		virtual HRESULT FrameMove(FLOAT)
		{
			return S_OK;
		}
		virtual HRESULT RestoreSurfaces()
		{
			return S_OK;
		}
		virtual HRESULT FinalCleanup()
		{
			return S_OK;
		}

		// Overridable power management (APM) functions
		virtual LRESULT OnQuerySuspend(DWORD dwFlags);
		virtual LRESULT OnResumeSuspend(DWORD dwData);
		virtual HRESULT BeforeRun()
		{
			return S_OK;
		}

		//zbuffer
		short			w_zdecal;
		long			dw_zmask;
		float			f_zmul;
		long			dw_zXmodulo;

	public:
		LPDIRECTDRAW7			m_pDD;
		LPDIRECT3DDEVICE7		m_pd3dDevice;
		LPDIRECTDRAWSURFACE7	m_pddsRenderTarget;
		LPDIRECTDRAWSURFACE7	m_pddsRenderTargetLeft;	// For stereo modes
		DDSURFACEDESC2			m_ddsdRenderTarget;
		int						WinManageMess();
		VOID					Cleanup3DEnvironment();
		LPDIRECT3D7				m_pD3D;
		void					EvictManagedTextures();
		virtual HRESULT Render()
		{
			return S_OK;
		}
		virtual HRESULT InitDeviceObjects()
		{
			return S_OK;
		}
		VOID					OutputText( DWORD x, DWORD y, char * str );
 
		HRESULT	SetClipping( float x1, float y1, float x2, float y2 );
 
		BOOL					m_bFrameMoving;
		BOOL					m_bActive;
		HRESULT					Change3DEnvironment();
		HRESULT					Initialize3DEnvironment();
		BOOL					m_bReady;
		D3DEnum_DeviceInfo*		m_pDeviceInfo;
		HWND					m_hWnd;
		HWND					m_hWndRender;
		WNDPROC					m_OldProc;
		HWND					m_dlghWnd;
		BOOL					b_dlg;
		long					d_dlgframe;
		void					EERIEMouseUpdate(short x, short y);

		// Functions to create, run, pause, and clean up the application
		virtual HRESULT			Create(HINSTANCE, char *);
		virtual INT				Run();
		virtual LRESULT			MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual VOID			Pause(BOOL bPause);
		LRESULT					SwitchFullScreen() ;

		CD3DFramework7*			m_pFramework;
		KEYBOARD_MNG			kbd;

		char					StatusText[512];
		short					CreationSizeX;
		short					CreationSizeY;
		long					CreationFlags;
		long					CreationMenu;
		EERIETOOLBAR*			ToolBar;
		HWND					owner;
 
		void*					logical;
		void*					zbuf;
		long					zbits;
		long					nbbits;
 
		void*					Lock();
		bool					Unlock();
		DDSURFACEDESC2			ddsd;
		DDSURFACEDESC2			ddsd2;

		void					EnableZBuffer();

		LPDIRECTDRAWGAMMACONTROL lpDDGammaControl;	//gamma control
		DDGAMMARAMP				DDGammaRamp;		//modified ramp value
		DDGAMMARAMP				DDGammaOld;			//backup gamma values
		HRESULT					UpdateGamma();
 
		float					GetZBufferMax();
		float					zbuffer_max;
		float					zbuffer_max_div;

		// Class constructor
		CD3DApplication();
};

#endif // EERIED3DAPP_H
