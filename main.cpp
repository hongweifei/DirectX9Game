

#include "Window/Window.h"
#include "Graphic/Renderer.h"
#include "Graphic/Camera.h"

float angle = 0.0f;

inline void render(Renderer* renderer)
{
	renderer->DrawVertices();

	if (angle == 10.0f)
		angle = 0.0f;

	angle += 0.1f;
}

int main()
{
	Window* window = new Window((char*)"title", 800, 600);
	Renderer* renderer = new Renderer(window->GetHandle());
	Camera* camera = new Camera(renderer->GetRenderDevice());

	renderer->SetRenderEvent(&render);
	renderer->SetLight();
	
	window->SetRenderer(renderer);
	window->MainLoop();
	
	delete window;
	delete renderer;

	return 0;
}
