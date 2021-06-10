////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_floor1Model = 0;
	m_floor2Model = 0;
	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

	m_Text = 0;

	m_BackPlayerV = { 0.0f, 0.0f, 0.0f };
	m_SystemPlayerV = { 0.0f, 0.0f, 0.0f };
	m_PlayerV = { 0.0f, 0.0f, 0.0f };
	m_PlayerRotation = { 0.0f, 0.0f, 0.0f };

	camera_X = 0.0f;
	camera_Y = 0.0f;
	camera_Z = 0.0f;

	infMap1Z = 0.0f;
	infMap2Z = 100.0f;

	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	
	gameover = false;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::CheckCubeIntersection(D3DXVECTOR2* vMin1, D3DXVECTOR2* vMax1, D3DXVECTOR2* vMin2, D3DXVECTOR2* vMax2)
{
	if (vMin1->x <= vMax2->x && vMax1->x >= vMin2->x &&
		vMin1->y <= vMax2->y && vMax1->y >= vMin2->y)
		return true;
	return false;
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetRotation(60.0f, -15.0f, 0.0f);

		m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}
	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"data/dust.png");
	if (!result)
	{
		return false;
	}
	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

#pragma region Model declaration

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "data/player.obj", L"data/playertexture.png");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_floor1Model = new ModelClass;
	if (!m_floor1Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_floor1Model->Initialize(m_D3D->GetDevice(), "data/map_01.obj", L"data/map_01_texture.png");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_floor2Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_floor2Model->Initialize(m_D3D->GetDevice(), "data/map_01.obj", L"data/map_01_texture.png");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	/////////////////////////////////////////////////////////////////////////////////Car
	// Create the model object.
	for (int i = 0; i < maxCarNum; i++)
	{
		carObject[i].m_carModel = new ModelClass;
		if (!carObject[i].m_carModel)
		{
			return false;
		}

		if (i % 3 == 2)
		{
			result = carObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car.obj", L"data/Car_07.png");
		}
		else if (i % 3 == 1)
		{
			result = carObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car.obj", L"data/Car_08.png");
		}
		else
		{
			result = carObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car.obj", L"data/Car_09.png");
		}

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		carObject[i].maxSize = D3DXVECTOR2(3.0f, 2.0f);
		carObject[i].minSize = D3DXVECTOR2(-3.0f, -2.0f);
	}

	//////////////////////////////////////////////////////////////////////////Suv
	// Create the model object.
	for (int i = 0; i < maxCarNum; i++)
	{
		suvObject[i].m_carModel = new ModelClass;
		if (!suvObject[i].m_carModel)
		{
			return false;
		}

		if (i % 3 == 2)
		{
			result = suvObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car_2.obj", L"data/Car_01.png");
		}
		else if (i % 3 == 1)
		{
			result = suvObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car_2.obj", L"data/Car_02.png");
		}
		else
		{
			result = suvObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/car_2.obj", L"data/Car_03.png");
		}

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		suvObject[i].maxSize = D3DXVECTOR2(3.0f, 2.0f);
		suvObject[i].minSize = D3DXVECTOR2(-3.0f, -2.0f);
	}

	//////////////////////////////////////////////////////////////////Truck
	// Create the model object.
	for (int i = 0; i < maxCarNum; i++)
	{
		truckObject[i].m_carModel = new ModelClass;
		if (!truckObject[i].m_carModel)
		{
			return false;
		}

		if (i % 3 == 2)
		{
			result = truckObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/truck.obj", L"data/Car_04.png");
		}
		else if (i % 3 == 1)
		{
			result = truckObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/truck.obj", L"data/Car_05.png");
		}
		else
		{
			result = truckObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/truck.obj", L"data/Car_06.png");
		}

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		truckObject[i].maxSize = D3DXVECTOR2(4.0f, 2.0f);
		truckObject[i].minSize = D3DXVECTOR2(-4.0f, -2.0f);
	}

	///////////////////////////////////////////////////////////Bus
	// Create the model object.
	for (int i = 0; i < maxCarNum; i++)
	{
		busObject[i].m_carModel = new ModelClass;
		if (!busObject[i].m_carModel)
		{
			return false;
		}

		if (i % 3 == 2)
		{
			result = busObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/bus.obj", L"data/Car_10.png");
		}
		else if (i % 3 == 1)
		{
			result = busObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/bus.obj", L"data/Car_11.png");
		}
		else
		{
			result = busObject[i].m_carModel->Initialize(m_D3D->GetDevice(), "data/bus.obj", L"data/Car_12.png");
		}

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		busObject[i].maxSize = D3DXVECTOR2(5.5f, 2.0f);
		busObject[i].minSize = D3DXVECTOR2(-5.5f, -2.0f);
	}

#pragma endregion Model declaration

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.25f, 0.3f, 0.2f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.3f, -0.7f, 0.7f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"data/gameover3.png", 600, 600);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	CarPositionInitialize(0);
	CarPositionInitialize(12);
	WallPositionInitialize(wallObject1);
	WallPositionInitialize(wallObject2);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the model object.
	if (m_floor1Model)
	{
		m_floor1Model->Shutdown();
		delete m_floor1Model;
		m_floor1Model = 0;
	}

	// Release the model object.
	if (m_floor2Model)
	{
		m_floor2Model->Shutdown();
		delete m_floor2Model;
		m_floor2Model = 0;
	}
	
	for (auto &object : carObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for (auto &object : suvObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for (auto &object : truckObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for (auto &object : busObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}
	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int score,int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;

	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetScore(score, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.

	m_Camera->SetPosition(m_PlayerV.x+5, m_PlayerV.y +30, m_PlayerV.z - 10);

	return true;
}

#pragma region Model Position Initialize
void GraphicsClass::WallPositionInitialize(WallModelInfo * wallObject) {
	wallObject[0].maxPosSize = { -22.5, 100 };
	wallObject[0].minPosSize = { -52.5, 0 };
	wallObject[1].maxPosSize = { 52.5, 100 };
	wallObject[1].minPosSize = { 32.5, 0 };
	wallObject[2].maxPosSize = { 0, 20 };
	wallObject[3].maxPosSize = { 15, 20 };
	wallObject[4].maxPosSize = { 20, 20 };
	wallObject[5].maxPosSize = { 25, 20 };
	wallObject[6].maxPosSize = { 5, 25 };
	wallObject[7].maxPosSize = { 15, 25 };
	wallObject[8].maxPosSize = { 20, 25 };
	wallObject[9].maxPosSize = { 10, 50 };
	wallObject[10].maxPosSize = { 15, 50 };
	wallObject[11].maxPosSize = { -15, 50 };
	wallObject[12].maxPosSize = { -20, 50 };
	wallObject[13].maxPosSize = { 0, 65 };
	wallObject[14].maxPosSize = { 15, 65 };
	wallObject[15].maxPosSize = { 20, 65 };
	wallObject[16].maxPosSize = { 25, 65 };
	wallObject[17].maxPosSize = { -15, 65 };
	wallObject[18].maxPosSize = { 5, 70 };
	wallObject[19].maxPosSize = { 15, 70 };
	wallObject[20].maxPosSize = { 20, 70 };
	wallObject[21].maxPosSize = { -15, 70 };
	wallObject[22].maxPosSize = { -20, 70 };
	wallObject[23].maxPosSize = { 15, 90 };
	wallObject[24].maxPosSize = { 20, 90 };
	wallObject[25].maxPosSize = { 30, 90 };
	wallObject[26].maxPosSize = { 25, 95 };
	wallObject[27].maxPosSize = { 30, 95 };
	wallObject[28].maxPosSize = { 30, 0 };

	for (int i = 2; i < 29; i++)
	{
		wallObject[i].minPosSize = { wallObject[i].maxPosSize.x - 2.5f, wallObject[i].maxPosSize.y - 2.5f };
		wallObject[i].maxPosSize = { wallObject[i].maxPosSize.x + 2.5f, wallObject[i].maxPosSize.y + 2.5f };
	}
}

void GraphicsClass::CarPositionInitialize(int carNum) {
	//5, 10, 15, 30, 35, 40, 45, 55, 60, 75, 80, 85
	carObject[0 + carNum].worldPosition.x = -40;
	carObject[0 + carNum].worldPosition.y = 5;
	carObject[1 + carNum].worldPosition.x = 14;
	carObject[1 + carNum].worldPosition.y = 15;
	carObject[2 + carNum].worldPosition.x = -4;
	carObject[2 + carNum].worldPosition.y = 30;
	carObject[3 + carNum].worldPosition.x = 6;
	carObject[3 + carNum].worldPosition.y = 85;
	carObject[4 + carNum].worldPosition.x = -40;
	carObject[4 + carNum].worldPosition.y = 15;
	carObject[5 + carNum].worldPosition.x = -8;
	carObject[5 + carNum].worldPosition.y = 75;
	carObject[6 + carNum].worldPosition.x = -38;
	carObject[6 + carNum].worldPosition.y = 85;
	carObject[7 + carNum].worldPosition.x = -28;
	carObject[7 + carNum].worldPosition.y = 80;
	carObject[8 + carNum].worldPosition.x = -18;
	carObject[8 + carNum].worldPosition.y = 55;
	carObject[9 + carNum].worldPosition.x = -10;
	carObject[9 + carNum].worldPosition.y = 35;
	carObject[10 + carNum].worldPosition.x = 46;
	carObject[10 + carNum].worldPosition.y = 60;
	carObject[11 + carNum].worldPosition.x = 12;
	carObject[11 + carNum].worldPosition.y = 80;


	suvObject[0 + carNum].worldPosition.x = 0;
	suvObject[0 + carNum].worldPosition.y = 75;
	suvObject[1 + carNum].worldPosition.x = 4;
	suvObject[1 + carNum].worldPosition.y = 10;
	suvObject[2 + carNum].worldPosition.x = -4;
	suvObject[2 + carNum].worldPosition.y = 45;
	suvObject[3 + carNum].worldPosition.x = 44;
	suvObject[3 + carNum].worldPosition.y = 30;
	suvObject[4 + carNum].worldPosition.x = 25;
	suvObject[4 + carNum].worldPosition.y = 35;
	suvObject[5 + carNum].worldPosition.x = 40;
	suvObject[5 + carNum].worldPosition.y = 40;
	suvObject[6 + carNum].worldPosition.x = 40;
	suvObject[6 + carNum].worldPosition.y = 55;
	suvObject[7 + carNum].worldPosition.x = 34;
	suvObject[7 + carNum].worldPosition.y = 80;
	suvObject[8 + carNum].worldPosition.x = -44;
	suvObject[8 + carNum].worldPosition.y = 75;
	suvObject[9 + carNum].worldPosition.x = -40;
	suvObject[9 + carNum].worldPosition.y = 55;
	suvObject[10 + carNum].worldPosition.x = -38;
	suvObject[10 + carNum].worldPosition.y = 35;
	suvObject[11 + carNum].worldPosition.x = -36;
	suvObject[11 + carNum].worldPosition.y = 10;


	truckObject[0 + carNum].worldPosition.x = -10;
	truckObject[0 + carNum].worldPosition.y = 10;
	truckObject[1 + carNum].worldPosition.x = -20;
	truckObject[1 + carNum].worldPosition.y = 45;
	truckObject[2 + carNum].worldPosition.x = 14;
	truckObject[2 + carNum].worldPosition.y = 55;
	truckObject[3 + carNum].worldPosition.x = 20;
	truckObject[3 + carNum].worldPosition.y = 75;
	truckObject[4 + carNum].worldPosition.x = 12;
	truckObject[4 + carNum].worldPosition.y = 5;
	truckObject[5 + carNum].worldPosition.x = 38;
	truckObject[5 + carNum].worldPosition.y = 15;
	truckObject[6 + carNum].worldPosition.x = 30;
	truckObject[6 + carNum].worldPosition.y = 10;
	truckObject[7 + carNum].worldPosition.x = 24;
	truckObject[7 + carNum].worldPosition.y = 30;
	truckObject[8 + carNum].worldPosition.x = 16;
	truckObject[8 + carNum].worldPosition.y = 40;
	truckObject[9 + carNum].worldPosition.x = -34;
	truckObject[9 + carNum].worldPosition.y = 30;
	truckObject[10 + carNum].worldPosition.x = 26;
	truckObject[10 + carNum].worldPosition.y = 85;
	truckObject[11 + carNum].worldPosition.x = -24;
	truckObject[11 + carNum].worldPosition.y = 75;


	busObject[0 + carNum].worldPosition.x = 35;
	busObject[0 + carNum].worldPosition.y = 5;
	busObject[1 + carNum].worldPosition.x = -20;
	busObject[1 + carNum].worldPosition.y = 15;
	busObject[2 + carNum].worldPosition.x = 20;
	busObject[2 + carNum].worldPosition.y = 45;
	busObject[3 + carNum].worldPosition.x = 0;
	busObject[3 + carNum].worldPosition.y = 80;
	busObject[4 + carNum].worldPosition.x = -16;
	busObject[4 + carNum].worldPosition.y = 60;
	busObject[5 + carNum].worldPosition.x = 4;
	busObject[5 + carNum].worldPosition.y = 35;
	busObject[6 + carNum].worldPosition.x = -4;
	busObject[6 + carNum].worldPosition.y = 55;
	busObject[7 + carNum].worldPosition.x = -16;
	busObject[7 + carNum].worldPosition.y = 30;
	busObject[8 + carNum].worldPosition.x = -12;
	busObject[8 + carNum].worldPosition.y = 85;
	busObject[9 + carNum].worldPosition.x = -24;
	busObject[9 + carNum].worldPosition.y = 5;
	busObject[10 + carNum].worldPosition.x = -24;
	busObject[10 + carNum].worldPosition.y = 40;
	busObject[11 + carNum].worldPosition.x = 24;
	busObject[11 + carNum].worldPosition.y = 60;
}

void GraphicsClass::MoveCarForward(CarModelInfo &object) {
	//5, 10, 15, 30, 35, 40, 45, 55, 60, 75, 80, 85
	//  45, 75

	if (object.worldPosition.x > 50) object.worldPosition.x = -50;
	if (object.worldPosition.y == 5 ||
		object.worldPosition.y == 35 ||
		object.worldPosition.y == 60 ||
		object.worldPosition.y == 80)
	{
		object.worldPosition.x += 0.08f;
	}

	else if (object.worldPosition.y == 10 ||
			object.worldPosition.y == 30 ||
			object.worldPosition.y == 40 ||
			object.worldPosition.y == 55 ||
			object.worldPosition.y == 85)
	{
		object.worldPosition.x += 0.05f;
	}

	else 
	{
		object.worldPosition.x += 0.03f;
	}
}

bool GraphicsClass::IsCollision() {
	for (auto object : carObject) {
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &object.minPosSize, &object.maxPosSize)) {
			gameover = true;
			return true;
		}
	}
	for (auto object : suvObject) {
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &object.minPosSize, &object.maxPosSize)) {
			gameover = true;
			return true;
		}
	}
	for (auto object : truckObject) {
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &object.minPosSize, &object.maxPosSize)) {
			gameover = true;
			return true;
		}
	}
	for (auto object : busObject) {
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &object.minPosSize, &object.maxPosSize)) {
			gameover = true;
			return true;
		}
	}
	for (auto object : wallObject1) {
		D3DXVECTOR2 maxV = { object.maxPosSize.x, object.maxPosSize.y + infMap1Z };
		D3DXVECTOR2 minV = { object.minPosSize.x, object.minPosSize.y + infMap1Z };
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &minV, &maxV))
		{
			return true;
		}
	}
	for (auto object : wallObject2) {
		D3DXVECTOR2 maxV = { object.maxPosSize.x, object.maxPosSize.y + infMap2Z };
		D3DXVECTOR2 minV = { object.minPosSize.x, object.minPosSize.y + infMap2Z };
		if (CheckCubeIntersection(new D3DXVECTOR2(m_PlayerV.x - 0.5f, m_PlayerV.z - 0.5f), new D3DXVECTOR2(m_PlayerV.x + 0.5f, m_PlayerV.z + 0.5f), &minV, &maxV))
		{
			return true;
		}
	}
	return false;
}
#pragma endregion Model Position Initialize

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX PlayerWorldMatrix, PlayerRotationMatrix, floor1WorldMatrix, floor2WorldMatrix,
		particleMatrix,particleRotationMatrix,particleScaleMatrix, BitmapMatrix, offset;
	bool result;

	D3DXVec3Lerp(&m_PlayerV, new D3DXVECTOR3(m_PlayerV), new D3DXVECTOR3(m_SystemPlayerV), 0.1f);
	D3DXMatrixRotationY(&PlayerRotationMatrix, m_PlayerRotation.y);
	D3DXMatrixTranslation(&PlayerWorldMatrix, m_PlayerV.x, m_PlayerV.y, m_PlayerV.z);
	D3DXMatrixTranslation(&particleMatrix, m_PlayerV.x, m_PlayerV.y, m_PlayerV.z);
	D3DXMatrixRotationYawPitchRoll(&particleRotationMatrix, 90.0f * 0.0174532925f,90.0f * 0.0174532925f,0.0f);
	D3DXMatrixTranslation(&floor1WorldMatrix, 0, 0, infMap1Z);
	D3DXMatrixTranslation(&floor2WorldMatrix, 0, 0, infMap2Z);
	D3DXMatrixScaling(&particleScaleMatrix, 10.0f, 10.0f, 10.0f);
	
	for (auto &object : carObject) {
		MoveCarForward(object);
	}
	for (auto& object : suvObject) {
		MoveCarForward(object);
	}
	for (auto& object : truckObject) {
		MoveCarForward(object);
	}
	for (auto& object : busObject) {
		MoveCarForward(object);
	}

	for (int i = 0; i < maxCarNum / 2; i++)
	{
		D3DXMatrixTranslation(&carObject[i].worldMatrix, carObject[i].worldPosition.x, 0.0f, carObject[i].worldPosition.y + infMap1Z);
		D3DXMatrixTranslation(&suvObject[i].worldMatrix, suvObject[i].worldPosition.x, 0.0f, suvObject[i].worldPosition.y + infMap1Z);
		D3DXMatrixTranslation(&truckObject[i].worldMatrix, truckObject[i].worldPosition.x, 0.0f, truckObject[i].worldPosition.y + infMap1Z);
		D3DXMatrixTranslation(&busObject[i].worldMatrix, busObject[i].worldPosition.x, 0.0f, busObject[i].worldPosition.y + infMap1Z);
		D3DXVec2Add(&carObject[i].maxPosSize, new D3DXVECTOR2(carObject[i].maxSize), new D3DXVECTOR2(carObject[i].worldPosition.x, carObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&carObject[i].minPosSize, new D3DXVECTOR2(carObject[i].minSize), new D3DXVECTOR2(carObject[i].worldPosition.x, carObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&suvObject[i].maxPosSize, new D3DXVECTOR2(suvObject[i].maxSize), new D3DXVECTOR2(suvObject[i].worldPosition.x, suvObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&suvObject[i].minPosSize, new D3DXVECTOR2(suvObject[i].minSize), new D3DXVECTOR2(suvObject[i].worldPosition.x, suvObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&truckObject[i].maxPosSize, new D3DXVECTOR2(truckObject[i].maxSize), new D3DXVECTOR2(truckObject[i].worldPosition.x, truckObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&truckObject[i].minPosSize, new D3DXVECTOR2(truckObject[i].minSize), new D3DXVECTOR2(truckObject[i].worldPosition.x, truckObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&busObject[i].maxPosSize, new D3DXVECTOR2(busObject[i].maxSize), new D3DXVECTOR2(busObject[i].worldPosition.x, busObject[i].worldPosition.y + infMap1Z));
		D3DXVec2Add(&busObject[i].minPosSize, new D3DXVECTOR2(busObject[i].minSize), new D3DXVECTOR2(busObject[i].worldPosition.x, busObject[i].worldPosition.y + infMap1Z));
	}

	for (int i = maxCarNum / 2; i < maxCarNum; i++)
	{
		D3DXMatrixTranslation(&carObject[i].worldMatrix, carObject[i].worldPosition.x, 0.0f, carObject[i].worldPosition.y + infMap2Z);
		D3DXMatrixTranslation(&suvObject[i].worldMatrix, suvObject[i].worldPosition.x, 0.0f, suvObject[i].worldPosition.y + infMap2Z);
		D3DXMatrixTranslation(&truckObject[i].worldMatrix, truckObject[i].worldPosition.x, 0.0f, truckObject[i].worldPosition.y + infMap2Z);
		D3DXMatrixTranslation(&busObject[i].worldMatrix, busObject[i].worldPosition.x, 0.0f, busObject[i].worldPosition.y + infMap2Z);
		D3DXVec2Add(&carObject[i].maxPosSize, new D3DXVECTOR2(carObject[i].maxSize), new D3DXVECTOR2(carObject[i].worldPosition.x, carObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&carObject[i].minPosSize, new D3DXVECTOR2(carObject[i].minSize), new D3DXVECTOR2(carObject[i].worldPosition.x, carObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&suvObject[i].maxPosSize, new D3DXVECTOR2(suvObject[i].maxSize), new D3DXVECTOR2(suvObject[i].worldPosition.x, suvObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&suvObject[i].minPosSize, new D3DXVECTOR2(suvObject[i].minSize), new D3DXVECTOR2(suvObject[i].worldPosition.x, suvObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&truckObject[i].maxPosSize, new D3DXVECTOR2(truckObject[i].maxSize), new D3DXVECTOR2(truckObject[i].worldPosition.x, truckObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&truckObject[i].minPosSize, new D3DXVECTOR2(truckObject[i].minSize), new D3DXVECTOR2(truckObject[i].worldPosition.x, truckObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&busObject[i].maxPosSize, new D3DXVECTOR2(busObject[i].maxSize), new D3DXVECTOR2(busObject[i].worldPosition.x, busObject[i].worldPosition.y + infMap2Z));
		D3DXVec2Add(&busObject[i].minPosSize, new D3DXVECTOR2(busObject[i].minSize), new D3DXVECTOR2(busObject[i].worldPosition.x, busObject[i].worldPosition.y + infMap2Z));
	}

	if (m_SystemPlayerV.z - 150 > infMap1Z) {
		infMap1Z += 200;
	}
	if (m_SystemPlayerV.z - 150 > infMap2Z) { 
		infMap2Z += 200; 
	}
	if (m_SystemPlayerV.z + 80 < infMap1Z) { 
		infMap1Z -= 200; 
	}
	if (m_SystemPlayerV.z + 80 < infMap2Z) { 
		infMap2Z -= 200; 
	}

	if (IsCollision())
	{
		m_SystemPlayerV = m_BackPlayerV;
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(BitmapMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetWorldMatrix(offset);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->TurnOnAlphaBlending();

	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

#pragma region Particle Position
	for (int i = 0; i < 12; i++)
	{
		D3DXMATRIX TempM;
		D3DXMatrixTranslation(&TempM, carObject[i].worldPosition.x - 0.5f, 0.0f, carObject[i].worldPosition.y + 0.5f + infMap1Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, suvObject[i].worldPosition.x - 0.5f, 0.0f, suvObject[i].worldPosition.y + 0.5f + infMap1Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, truckObject[i].worldPosition.x - 2.7f, 0.0f, truckObject[i].worldPosition.y + 0.5f + infMap1Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, busObject[i].worldPosition.x - 4.5f, 0.0f, busObject[i].worldPosition.y + 0.5f + infMap1Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	for (int i = 12; i < 24; i++)
	{
		D3DXMATRIX TempM;
		D3DXMatrixTranslation(&TempM, carObject[i].worldPosition.x - 0.5f, 0.0f, carObject[i].worldPosition.y + 0.5f + infMap2Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, suvObject[i].worldPosition.x - 0.5f, 0.0f, suvObject[i].worldPosition.y + 0.5f + infMap2Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, truckObject[i].worldPosition.x - 3.0f, 0.0f, truckObject[i].worldPosition.y + 0.5f + infMap2Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}

		D3DXMatrixTranslation(&TempM, busObject[i].worldPosition.x - 4.5f, 0.0f, busObject[i].worldPosition.y + 0.5f + infMap2Z);
		// Render the model using the texture shader.
		result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), particleRotationMatrix * TempM, viewMatrix, projectionMatrix,
			m_ParticleSystem->GetTexture());
		if (!result)
		{
			return false;
		}
	}
#pragma endregion Particle Position

	m_D3D->TurnOffAlphaBlending();



	// Rotate the world matrix by the rotation value so that the triangle will spin.

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), PlayerRotationMatrix*PlayerWorldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_floor1Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_floor1Model->GetIndexCount(), floor1WorldMatrix, viewMatrix, projectionMatrix,
		m_floor1Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
								   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_floor2Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_floor2Model->GetIndexCount(), floor2WorldMatrix, viewMatrix, projectionMatrix,
		m_floor2Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	////////////////////////Car
	for (int i = 0; i < maxCarNum; i++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		carObject[i].m_carModel->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), carObject[i].m_carModel->GetIndexCount(), carObject[i].worldMatrix, viewMatrix, projectionMatrix,
			carObject[i].m_carModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}
	////////////////////////Suv
	for (int i = 0; i < maxCarNum; i++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		suvObject[i].m_carModel->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), suvObject[i].m_carModel->GetIndexCount(), suvObject[i].worldMatrix, viewMatrix, projectionMatrix,
			suvObject[i].m_carModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}
	////////////////////////Truck
	for (int i = 0; i < maxCarNum; i++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		truckObject[i].m_carModel->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), truckObject[i].m_carModel->GetIndexCount(), truckObject[i].worldMatrix, viewMatrix, projectionMatrix,
			truckObject[i].m_carModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}
	////////////////////////Bus
	for (int i = 0; i < maxCarNum; i++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		busObject[i].m_carModel->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), busObject[i].m_carModel->GetIndexCount(), busObject[i].worldMatrix, viewMatrix, projectionMatrix,
			busObject[i].m_carModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result)
		{
			return false;
		}
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();
	D3DXVECTOR3 cameraPosition = m_Camera->GetPosition();
	D3DXVECTOR3 cameraRotation = m_Camera->GetRotation();

	D3DXMatrixTranslation(&viewMatrix,0,0,cameraPosition.z+12);

	D3DXMatrixRotationYawPitchRoll(&BitmapMatrix, cameraRotation.y * 0.0174532925f, cameraRotation.x * 0.0174532925f, cameraRotation.z );

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	if (gameover) {
		static float y = 200;
		if (y >= 50.0f) {
			y -= 1.5f;
		}
		
		result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
		if (!result)
		{
			return false;
		}
		D3DXMatrixTranslation(&offset, 100, y, 0);
		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix * offset, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
		if (!result)
		{
			return false;
		}
	}
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), viewMatrix * BitmapMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}