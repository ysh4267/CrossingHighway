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

#include "particleshaderclass.h"
#include "particlesystemclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const int maxCarNum = 24;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
private:
	struct CarModelInfo
	{
		ModelClass* m_carModel;
		D3DXVECTOR2 worldPosition;
		D3DXMATRIX worldMatrix;
		D3DXVECTOR2 maxSize;
		D3DXVECTOR2 minSize;
		D3DXVECTOR2 maxPosSize;
		D3DXVECTOR2 minPosSize;
	};

	struct WallModelInfo
	{
		D3DXVECTOR2 maxPosSize;
		D3DXVECTOR2 minPosSize;
	};

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	float camera_X;
	float camera_Y;
	float camera_Z;

	D3DXVECTOR3 m_PlayerV;
	D3DXVECTOR3 m_SystemPlayerV;
	D3DXVECTOR3 m_BackPlayerV;
	D3DXVECTOR3 m_PlayerRotation;
	D3DXMATRIX UIViewMatrix;

	float infMap1Z;
	float infMap2Z;

	int m_score;
	int polyNum;
	int objNum;
	float accel;

	bool gameover;

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);
	bool Frame(int,int, int, float);
	bool Render();
	bool Render(float);
	bool CheckCubeIntersection(D3DXVECTOR2*, D3DXVECTOR2*, D3DXVECTOR2*, D3DXVECTOR2*);
	void CarPositionInitialize(int);
	void WallPositionInitialize(WallModelInfo* wallObject);
	void MoveCarForward(CarModelInfo&);
	bool IsCollision();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_floor1Model;
	ModelClass* m_floor2Model;
	CarModelInfo carObject[maxCarNum];
	CarModelInfo suvObject[maxCarNum];
	CarModelInfo truckObject[maxCarNum];
	CarModelInfo busObject[maxCarNum];
	WallModelInfo wallObject1[29];
	WallModelInfo wallObject2[29];
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	ParticleShaderClass* m_ParticleShader; 
	ParticleSystemClass* m_ParticleSystem;

	TextClass* m_Text;
};

#endif