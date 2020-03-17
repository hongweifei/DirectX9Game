

#pragma once


#ifdef _WIN32
#include <Windows.h>
#include <d3dx9.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

#endif // WIN32

#ifdef __linux
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif // linux

#include <stdio.h>
#include <stdarg.h>

#ifndef RENDERER
#define RENDERER

class Renderer;
struct CUSTOMVERTEX;

typedef void(*RenderEvent)(Renderer* renderer);

class Renderer
{
public:
#ifdef _WIN32
	Renderer(HWND hWnd);
#endif // _WIN32

#ifdef __linux
	Renderer();
#endif // __linux


	~Renderer();

	void DrawVertices();

	void SetLight(float r = 1.0f, float g = 1.0f, float b = 1.0f, float range = 1000.0f);

	void Render();
	void SetRenderEvent(RenderEvent event);
	RenderEvent GetRenderEvent() { return this->render_event; };

#ifdef _WIN32
	LPDIRECT3DDEVICE9 GetRenderDevice() { return this->d3d_device; };
#endif // _WIN32

private:
	RenderEvent render_event = NULL;

#ifdef _WIN32
	LPDIRECT3D9 d3d = NULL; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9 d3d_device = NULL; // Our rendering device
	D3DPRESENT_PARAMETERS d3d_present_parameters;
	
	HRESULT InitDevice(HWND hWnd);
#endif // _WIN32
	
	

protected:

};

struct CUSTOMVERTEX
{
	float x, y, z, rhw; // The transformed position for the vertex.
	unsigned long color;        // The vertex color.
};


#endif // !RENDERER

