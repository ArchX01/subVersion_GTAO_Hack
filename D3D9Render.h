/*
	Copyright 2016 sub1to

	This file is part of subVersion GTA:O SC External Hack.

    subVersion GTA:O SC External Hack is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

    subVersion GTA:O SC External Hack is distributed in the hope that it
	will be useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
	the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with subVersion GTA:O SC External Hack.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef D3D9_RENDER
#define D3D9_RENDER

#define FONT_BUFFER_SIZE	0x10									//max amount of fonts
#define VERTEX_FORMAT		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)		//custom vertex format

//Layout defines
#define LAYOUT_PADDING_TOP	50
#define LAYOUT_PADDING_LEFT	50

#define LAYOUT_BORDER_SIZE		2
#define LAYOUT_ELEMENT_WIDTH	300
#define LAYOUT_ELEMENT_HEIGHT	25


struct Vertex
{
    FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
    DWORD color;    // from the D3DFVF_DIFFUSE flag
};

class D3D9Render
{
	public:
		struct scrnVars
		{
			int		w = 800,		//screen width
					h = 600,
					x = 0,
					y = 0;		//screen height
		} m_screen;

				D3D9Render	();
				~D3D9Render	();

		bool	init		(HWND hWnd);
		bool	render		();
		bool	createFont	(char *font, int size, bool bold, bool italic);
		void	releaseFont	();
		bool	getViewport	();

		void	drawBox			(float x, float y, float w, float h, D3DCOLOR color);
		void	drawBoxInline	(float x, float y, float w, float h, float size, D3DCOLOR color);
		void	drawBoxBorder	(float x, float y, float w, float h, float borderSize, D3DCOLOR color, D3DCOLOR borderColor);
		void	drawText		(std::string str, float x, float y, int font, D3DCOLOR color);
	protected:

		LPDIRECT3D9				m_pD3d;			// the pointer to Direct3D interface
		LPDIRECT3DDEVICE9		m_pD3dDev;		// the pointer to the device
		LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer; //pointer to the vertex buffer interface
		LPD3DXFONT				m_pFont[FONT_BUFFER_SIZE];
		int						m_nFont;
};

extern D3D9Render*	g_pD3D9Render;

#endif