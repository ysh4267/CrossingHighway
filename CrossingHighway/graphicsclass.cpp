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

	m_SystemPlayerV = { 0.0f, 0.0f, 0.0f };
	m_PlayerV = { 0.0f, 0.0f, 0.0f };
	m_PlayerRotation = { 0.0f, 0.0f, 0.0f };

	camera_X = 0.0f;
	camera_Y = -2.0f;
	camera_Z = -10.0f;

	infMap1Z = 0.0f;
	infMap2Z = 0.0f;

	m_ParticleShader = 0;
	m_ParticleSystem = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::CheckCubeIntersection(D3DXVECTOR3* vMin1, D3DXVECTOR3* vMax1, D3DXVECTOR3* vMin2, D3DXVECTOR3* vMax2)
{
	if (vMin1->x <= vMax2->x && vMax1->x >= vMin2->x &&
		vMin1->y <= vMax2->y && vMax1->y >= vMin2->y &&
		vMin1->z <= vMax2->z && vMax1->z >= vMin2->z)
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
	m_Camera->SetPosition(0.0f, 40.0f, 00.0f);
	m_Camera->SetRotation(60.0f, -15.0f, 0.0f);
	//m_Camera->SetPosition(0.0f, 0.5f, -3.0f);

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
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"data/star.dds");
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

#pragma region ¸ðµ¨ ¼±¾ð

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
	}

#pragma endregion ¸ðµ¨ ¼±¾ð

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
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"data/seafloor.dds", 256, 256);
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

	for (int i = 12; i < 24; i++)
	{
		carObject[i].worldPosition.y += 100;
		suvObject[i].worldPosition.y += 100;
		truckObject[i].worldPosition.y += 100;
		busObject[i].worldPosition.y += 100;
	}

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
	
	for each (auto object in carObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for each (auto object in suvObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for each (auto object in truckObject)
	{
		if (object.m_carModel)
		{
			object.m_carModel->Shutdown();
			delete object.m_carModel;
			object.m_carModel = 0;
		}
	}

	for each (auto object in busObject)
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

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
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

	m_Camera->SetPosition(m_PlayerV.x + 5, m_PlayerV.y + 30, m_PlayerV.z - 10);

	return true;
}

void GraphicsClass::CarPositionInitialize(int carNum) {
	//5, 10, 15, 30, 35, 40, 45, 55, 60, 75, 80, 85
	carObject[0 + carNum].worldPosition.x = 0;
	carObject[0 + carNum].worldPosition.y = 5;
	carObject[1 + carNum].worldPosition.x = 14;
	carObject[1 + carNum].worldPosition.y = 15;
	carObject[2 + carNum].worldPosition.x = -4;
	carObject[2 + carNum].worldPosition.y = 30;
	carObject[3 + carNum].worldPosition.x = 6;
	carObject[3 + carNum].worldPosition.y = 85;
	carObject[4 + carNum].worldPosition.x = -10;
	carObject[4 + carNum].worldPosition.y = 40;
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
	truckObject[5 + carNum].worldPosition.x = 24;
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

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX PlayerWorldMatrix, PlayerRotationMatrix, floor1WorldMatrix, floor2WorldMatrix,
		particleMatrix, particleScaleMatrix;
	bool result;


	D3DXVec3Lerp(&m_PlayerV, new D3DXVECTOR3(m_PlayerV), new D3DXVECTOR3(m_SystemPlayerV), 0.05f);
	D3DXMatrixRotationY(&PlayerRotationMatrix, m_PlayerRotation.y);
	D3DXMatrixTranslation(&PlayerWorldMatrix, m_PlayerV.x, m_PlayerV.y, m_PlayerV.z);
	D3DXMatrixTranslation(&particleMatrix, m_PlayerV.x, m_PlayerV.y, m_PlayerV.z);
	D3DXMatrixTranslation(&floor1WorldMatrix, 0, 0, infMap1Z);
	D3DXMatrixTranslation(&floor2WorldMatrix, 0, 0, infMap2Z + 100);
	D3DXMatrixScaling(&particleScaleMatrix, 10.0f, 10.0f, 10.0f);

	for (int i = 0; i < maxCarNum; i++)
	{
		D3DXMatrixTranslation(&carObject[i].worldMatrix, carObject[i].worldPosition.x, 0.0f, carObject[i].worldPosition.y);
		D3DXMatrixTranslation(&suvObject[i].worldMatrix, suvObject[i].worldPosition.x, 0.0f, suvObject[i].worldPosition.y);
		D3DXMatrixTranslation(&truckObject[i].worldMatrix, truckObject[i].worldPosition.x, 0.0f, truckObject[i].worldPosition.y);
		D3DXMatrixTranslation(&busObject[i].worldMatrix, busObject[i].worldPosition.x, 0.0f, busObject[i].worldPosition.y);
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	D3DXMatrixRotationY(&worldMatrix, rotation);
	m_D3D->TurnOnAlphaBlending();

	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), PlayerWorldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}
	m_D3D->TurnOffAlphaBlending();


	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 200, 200);
	//if (!result)
	//{
	//	return false;
	//}

	// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
		
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

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

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}