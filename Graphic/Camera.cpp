


#include "Camera.h"



#ifdef _WIN32

Camera::Camera(LPDIRECT3DDEVICE9 p_d3d_device)
{
    this->d3d_device = p_d3d_device;

    this->SetViewMatrix();
    this->SetProjMatrix();

}

#endif // _WIN32


Camera::~Camera()
{
}

void Camera::CalculateViewMatrix()
{

}

//-----------------------------------------------------------------------------
// Name：Camera::SetCameraPosition( )
// Desc: 设置摄像机所在的位置
//-----------------------------------------------------------------------------
void Camera::SetCameraPosition(float x,float y,float z)
{
#ifdef _WIN32

    D3DXVECTOR3 vector(x,y,z);
    this->camera_position = vector;

#endif // _WIN32
}

//-----------------------------------------------------------------------------
// Name：Camera::SetTargetPosition( )
// Desc: 设置摄像机的观察位置
//-----------------------------------------------------------------------------
void Camera::SetTargetPosition(float x, float y, float z)
{
#ifdef _WIN32
    D3DXVECTOR3 vector(x, y, z);
    this->target_position = vector;
#endif // _WIN32

}

void Camera::SetWorldMatrix(float angle)
{
#ifdef _WIN32
    D3DXMatrixRotationY(&this->mat_world, timeGetTime() / angle);
    this->d3d_device->SetTransform(D3DTS_WORLD, &this->mat_world);
#endif // _WIN32
}


//-----------------------------------------------------------------------------
// Name：Camera::SetViewMatrix( )
// Desc: 设置取景变换矩阵
//-----------------------------------------------------------------------------

void Camera::SetViewMatrix(float eye_x, float eye_y, float eye_z,
    float look_at_x, float look_at_y, float look_at_z,
    float up_vector_x, float up_vector_y, float up_vector_z)
{
#ifdef _WIN32
    this->eye_vector = D3DXVECTOR3(eye_x,eye_y,eye_z);
    this->look_at_vector = D3DXVECTOR3(look_at_x, look_at_y, look_at_z);
    this->up_vector = D3DXVECTOR3(up_vector_x, up_vector_y, up_vector_z);

    D3DXMatrixLookAtLH(&this->mat_view, &this->eye_vector, &this->look_at_vector, &this->up_vector);
    this->d3d_device->SetTransform(D3DTS_VIEW, &this->mat_view);
#endif // _WIN32
}

//-----------------------------------------------------------------------------
// Name：Camera::SetProjMatrix( )
// Desc: 设置投影变换矩阵
//-----------------------------------------------------------------------------
void Camera::SetProjMatrix(float fov)
{
#ifdef _WIN32
    D3DXMatrixPerspectiveFovLH(&this->mat_proj, fov, 1.0f, 1.0f, 100.0f);
    this->d3d_device->SetTransform(D3DTS_PROJECTION, &this->mat_proj);
#endif // _WIN32
}

