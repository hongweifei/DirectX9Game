

#include "Renderer.h"

#ifdef _WIN32
Renderer::Renderer(HWND hWnd)
{
	ZeroMemory(&this->d3d_present_parameters, sizeof(this->d3d_present_parameters));
	this->d3d_present_parameters.Windowed = TRUE;
	this->d3d_present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3d_present_parameters.BackBufferFormat = D3DFMT_UNKNOWN;

    if (SUCCEEDED(this->InitDevice(hWnd)))
        printf("Device init finish.\n");

    D3DMATRIX mat_world;
    this->d3d_device->SetTransform(D3DTS_WORLD,&mat_world);

    D3DMATERIAL9 mtrl;
    ZeroMemory(&mtrl, sizeof(mtrl));
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
    this->d3d_device->SetMaterial(&mtrl);

}

HRESULT Renderer::InitDevice(HWND hWnd)
{
    if (NULL == (this->d3d = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    if (FAILED(this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &this->d3d_present_parameters, &this->d3d_device)))
        return E_FAIL;

    return S_OK;
}

#endif // _WIN32

#ifdef __linux

Renderer::Renderer()
{
    
}

#endif // __linux


Renderer::~Renderer()
{
#ifdef _WIN32
	if (this->d3d_device != NULL)
		this->d3d_device->Release();

	if (this->d3d != NULL)
        this->d3d->Release();
#endif // _WIN32

}

void Renderer::DrawVertices()
{
#ifdef _WIN32

    CUSTOMVERTEX vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 1.5f, 1.0f, 0xff00ff00, },
        {  50.0f, 250.0f, 2.5f, 1.0f, 0xff00ffff, },
    };

    LPDIRECT3DVERTEXBUFFER9 vertex_buffer = NULL;

    this->d3d_device->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 3, 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertex_buffer, NULL);

    VOID* Vertices;
    vertex_buffer->Lock(0, sizeof(vertices), (VOID**)&Vertices, 0);

    memcpy(Vertices, vertices, sizeof(vertices));

    vertex_buffer->Unlock();

    this->d3d_device->SetStreamSource(0, vertex_buffer, 0, sizeof(CUSTOMVERTEX));
    this->d3d_device->SetFVF(D3DFVF_CUSTOMVERTEX);
    this->d3d_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

#endif // _WIN32

}

void Renderer::SetLight(float r, float g, float b,float range)
{
#ifdef _WIN32
    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(light));
    light.Type = D3DLIGHT_DIRECTIONAL;

    light.Diffuse.r = r;
    light.Diffuse.g = g;
    light.Diffuse.b = b;

    vecDir = D3DXVECTOR3(cosf(timeGetTime() / 360.0f),0.0f,sinf(timeGetTime() / 360.0f));
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

    light.Range = range;

    this->d3d_device->SetLight(0, &light);
    this->d3d_device->LightEnable(0, TRUE);
    this->d3d_device->SetRenderState(D3DRS_LIGHTING, TRUE);
    this->d3d_device->SetRenderState(D3DRS_AMBIENT, 0x00202020);
#endif // _WIN32
    
}

/*
void Renderer::Render(void (*render)())
{
    return;
}
*/

void Renderer::Render()
{
#ifdef _WIN32
    if (this->d3d_device == NULL)
        return;

    // Clear the backbuffer to a blue color
    this->d3d_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Begin the scene
    if (SUCCEEDED(this->d3d_device->BeginScene()))
    {
        // Rendering of scene objects can happen here
        if (this->render_event != NULL)
            this->render_event(this);
        // End the scene
        this->d3d_device->EndScene();
    }

    // Present the backbuffer contents to the display
    this->d3d_device->Present(NULL, NULL, NULL, NULL);

#endif // _WIN32

#ifdef __linux
    glClear(GL_COLOR_BUFFER_BIT);

    if (this->render_event != NULL)
        this->render_event(this);

    glutSwapBuffers();  //后台缓冲区交换到前台缓冲区显示
#endif // __linux

}

void Renderer::SetRenderEvent(RenderEvent event)
{
    this->render_event = event;
}