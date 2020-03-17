#pragma once

#ifdef _WIN32

#include <d3dx9.h>

#endif // _WIN32

#define PI ((float) 3.141592654f)

class Camera
{
#ifdef _WIN32

private:
	LPDIRECT3DDEVICE9 d3d_device = NULL;  //Direct3D设备对象

	D3DXVECTOR3	eye_vector = D3DXVECTOR3(0.0f, 3.0f, -5.0f);        // 右分量向量
	D3DXVECTOR3	look_at_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 观察方向向量
	D3DXVECTOR3	up_vector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// 上分量向量
	D3DXVECTOR3	camera_position = D3DXVECTOR3(0.0f, 0.0f, -250.0f);	// 摄像机位置的向量
	D3DXVECTOR3	target_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目标观察位置的向量
	D3DXMATRIX mat_world;
	D3DXMATRIX mat_view;          // 取景变换矩阵
	D3DXMATRIX mat_proj;          // 投影变换矩阵   

#endif // _WIN32

public:
	void CalculateViewMatrix();
	void SetCameraPosition(float x,float y,float z);
	void SetTargetPosition(float x, float y, float z);

	void SetWorldMatrix(float angle = 150.0f);

	void SetViewMatrix(float eye_x = 0.0f, float eye_y = 3.0f, float eye_z = -5.0f,
		float look_at_x = 0.0f, float look_at_y = 0.0f, float look_at_z = 0.0f,
		float up_vector_x = 0.0f, float up_vector_y = 1.0f, float up_vector_z = 0.0f);

	void SetProjMatrix(float fov = PI / 4);
	

public:
#ifdef _WIN32
	Camera(LPDIRECT3DDEVICE9 p_d3d_device);
#endif // _WIN32
	
	~Camera();
};

