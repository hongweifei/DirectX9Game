

#pragma once


#ifdef _WIN32
#include <Windows.h>

#define CREATE WM_CREATE
#define DESTROY WM_DESTROY
#define MOVE WM_MOVE
#define SIZE WM_SIZE
#define ACTIVATE WM_ACTIVATE
#define PAINT WM_PAINT
#define QUIT WM_QUIT

#define INACTIVE WA_INACTIVE
#define ACTIVE WA_ACTIVE
#define CLICKACTIVE WA_CLICKACTIVE

#endif // _WIN32

#ifdef _linux

#include <GL/glut.h>
#include <GL/freeglut.h>

#endif // _linux

#include "../Graphic/Renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef WINDOW
#define WINDOW

class Window
{
public:
	Window(char* window_title, int window_width = 800, int window_height = 600);
	~Window();

	void WindowCreate(int window_width = 800, int window_height = 600);
	void MainLoop();

#ifdef _WIN32
	HWND GetHandle() { return this->hWnd; };
#endif // _WIN32

	void SetRenderer(Renderer* renderer);
	//Renderer* GetRenderer() { return this->renderer; };

private:

#ifdef _WIN32
	WNDCLASSEX window_class;
	HWND hWnd;
	MSG msg;
#endif // _WIN32
	
	char* title;
	int width;
	int height;
	
	Renderer* renderer = NULL;

protected:
	
};

#endif


