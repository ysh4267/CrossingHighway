////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"

#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const int maxCarNum = 12;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	float camera_X;
	float camera_Y;
	float camera_Z;

	D3DXVECTOR3 m_PlayerV;
	D3DXVECTOR3 m_SystemPlayerV;

	float infMap1Z;
	float infMap2Z;
	float carsX[maxCarNum];

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);
	bool Frame(int, int, float);
	bool Render();
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_floor1Model;
	ModelClass* m_floor2Model;
	ModelClass* m_car1Model;
	ModelClass* m_car2Model;
	ModelClass* m_car3Model;
	ModelClass* m_suv1Model;
	ModelClass* m_suv2Model;
	ModelClass* m_suv3Model;
	ModelClass* m_truck1Model;
	ModelClass* m_truck2Model;
	ModelClass* m_truck3Model;
	ModelClass* m_bus1Model;
	ModelClass* m_bus2Model;
	ModelClass* m_bus3Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;
};

#endif