//#include <iostream>

#include "GEngine.h"
#include "Vector3f.h"
#include "Quaternion.h"
#include "FileReader.h"
#include "Model.h"
#include "ConstantVelocity.h"
//#include "MotionUnderGravitation.h"
//#include "MassConnectedWithSpring.h"

//#include "Tera.h"

#include "RenderGL.h"

//Render* render = new RenderGL;
Render* render = nullptr;

const char* title = "GEngine";
unsigned width = 1366;
unsigned height = 768;
unsigned char bits = 32;
bool fullscreen = false;

float slowMotionRatio = 1.0f;
float timeElapsed = 0.0f;
float maxPossible_dt = 0.1f; // ����������� ��������� dt = 0.1 � ���������� ����� �� �� ��������� �� ������� ��������.

float moveScale = 0.1f;
float rotateScale = 0.2f;

Vector3f teraScale = Vector3f(1.0f, 1.0f, 1.0f);

bool active = true;
bool pause = false;
bool keys[256];                // ������, ������������ ��� �������� � �����������


//Simulation* simulation = nullptr;

Model model;

//Tera tera;

// ��� ������� ������������� �������� ����� ��� ����������� ������, ���������� �� ������ ������

/*void LoadRawFile(const char* fileName, const unsigned nSize, unsigned char* pHeightMap)
{
	FILE *pFile = NULL;

	// �������� ����� � ������ ��������� ������
	pFile = fopen(fileName, "rb");

	// ���� ������?
	if (pFile == NULL)
	{
		// ������� ��������� �� ������ � ������� �� ���������
		MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		return;
	}

	// ��������� .RAW ���� � ������ pHeightMap
	// ������ ��� ������ �� ������ �����, ������ = ������ * ������
	fread(pHeightMap, 1, nSize, pFile);

	// ��������� �� ������� ������
	int result = ferror(pFile);

	// ���� ��������� ������
	if (result)
	{
		MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
	}

	// ��������� ����
	fclose(pFile);
}
*/

void Init()
{
	//if (MessageBox(NULL, "������ �� �� ��������� ���������� � ������������� ������?", "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
	//fullscreen = false;          // ������� �����
	//}

	render = new RenderGL;

	// ������� ���� OpenGL ����
	if (!render->createWindow(title, width, height, bits, fullscreen))
	{
		return;              // �����, ���� ���� �� ����� ���� �������
	}



	FileReader fileReader;
	fileReader.ReadModelOBJ(model, "data/T34/T34_FBX.obj");
	//fileReader.ReadModelOBJ(model, "data/Dragon/BGE_Dragon_2.5_Blender_Game_Engine.obj");	
	//fileReader.ReadModelOBJ(model, "data/T34/t_34_obj.obj");
	//fileReader.ReadModelOBJ(model, "data/Manowar.obj");

	//LoadRawFile("Terrain.raw", tera.MAP_SIZE * tera.MAP_SIZE, tera.HeightMap);

	/*
	//simulation = new ConstantVelocity(8, Vector3f(0.0f, -1.0f, 0.0f));
	simulation = new ConstantVelocity(2);

	simulation->getMass(0)->m = 1.9885E6f;
	simulation->getMass(0)->r = 15.0f;
	simulation->getMass(0)->color = Color4f(0.8f, 0.4f, 0.2f, 1.0f);
	simulation->getMass(0)->pos = Vector3f(0.0f, 0.0f, 100.0f);
	simulation->getMass(0)->vel = Vector3f(0.0f, 0.0f, 0.0f);

	simulation->getMass(1)->m = 5.9726f;
	simulation->getMass(1)->r = 5.0f;
	simulation->getMass(1)->color = Color4f(0.1f, 0.4f, 0.9f, 1.0f);
	//simulation->getMass(1)->pos = Vector3f(147.098290f, 0, 0);
	simulation->getMass(1)->pos = Vector3f(152.098232f, 0.0f, 0.0f);
	simulation->getMass(1)->vel = Vector3f(0.0f, 297.83f, 0.0f);
	*/
}

void Update(float dt)
{
	//simulation->operate(dt);
}

void Draw()
{	
	render->beginDraw();

	//render->drawBox(Vector3f(50.0f, 0.0f, 0.0f), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	//render->drawBox(Vector3f(0.0f, 50.0f, 0.0f), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f, 1.0f));
	//render->drawBox(Vector3f(0.0f, 0.0f, 50.0f), Vector3f(1.0f, 1.0f, 100.0f), Color4f(0.0f, 0.0f, 1.0f, 1.0f));

	for (size_t i = 0; i < model.nGroup; ++i)
	{
		if (model.groups[i].name == "Player_BOX_Cube.003") continue;
		for (size_t j = 0; j < model.groups[i].size; ++j)
		{
			Surface surface = model.groups[i].surfaces[j];
			if (surface.n == 3)
			{
				Color4f color(0.2f, 0.75f, 0.2f, 1.0f);
				render->drawTriangle(model.vertexs[surface.Vertexs[0]], model.vertexs[surface.Vertexs[1]], model.vertexs[surface.Vertexs[2]], model.normals[surface.Normals[0]], color);
			}
			else if (surface.n == 4)
			{
				Vector3f quad[4];
				Vector3f n = model.vertexs[surface.Normals[0]];
				quad[0] = model.vertexs[surface.Vertexs[0]];
				quad[1] = model.vertexs[surface.Vertexs[1]];
				quad[2] = model.vertexs[surface.Vertexs[2]];
				quad[3] = model.vertexs[surface.Vertexs[3]];
				Color4f color(0.2f, 0.2f, 0.25f, 1.0f);
				render->drawQuad(quad, n, color);
			}
			else if (surface.n == 5)
			{
				int t = 0;
			}
			else if (surface.n == 6)
			{
				//render->drawTriangle(model.vertexs[surface.Vertexs[0]], model.vertexs[surface.Vertexs[1]], model.vertexs[surface.Vertexs[2]], model.normals[surface.Normals[0]], Color4f(0.5f, 0.5f, 0.5f, 1.0f));
				//render->drawTriangle(model.vertexs[surface.Vertexs[3]], model.vertexs[surface.Vertexs[4]], model.vertexs[surface.Vertexs[5]], model.normals[surface.Normals[0]], Color4f(0.5f, 0.5f, 0.5f, 1.0f));
				Vector3f quad[4];
				quad[0] = model.vertexs[surface.Vertexs[0]];
				quad[1] = model.vertexs[surface.Vertexs[1]];
				quad[2] = model.vertexs[surface.Vertexs[4]];
				quad[3] = model.vertexs[surface.Vertexs[5]];

				Vector3f n = model.vertexs[surface.Normals[0]];

				Color4f color(0.0f, 0.0f, 1.0f, 1.0f);
				//render->drawQuad(quad, n, color);

				//Vector3f norm[6];
				//for (int i = 0; i < surface.n; ++i)
				//{
					//vert[i] = model.vertexs[surface.Vertexs[i]];
					//norm[i] = model.normals[surface.Normals[i]];
				//}

				//render->drawTriangleStrip(6, vert, norm, color);
			}
			else if (surface.n == 10)
			{
				Vector3f vert[10];
				Vector3f norm[10];
				for (int i = 0; i < surface.n; ++i)
				{
					vert[i] = model.vertexs[surface.Vertexs[i]];
					norm[i] = model.normals[surface.Normals[i]];
				}
				Color4f color(0.0f, 0.0f, 1.0f, 1.0f);
				//render->drawTriangleStrip(10, vert, norm, color);
			}
			else
			{
				int t = 0;
			}
		}
	}

	//Draw Sea
	//render->drawSphere(Vector3f(0.0f, 0.0f, -500), 500.0f, Vector3f(0.1f, 0.3f, 0.9f));


	//simulation->draw(*render);

/*
	for (int Xint = 0; Xint < tera.MAP_SIZE; Xint += tera.STEP_SIZE)
		for (int Yint = 0; Yint < tera.MAP_SIZE; Yint += tera.STEP_SIZE)
		{
			float X = static_cast<float>(Xint) * teraScale.x;
			float Y = static_cast<float>(Yint) * teraScale.y;
			float difX = - tera.MAP_SIZE * teraScale.x / 2;
			float difY = -tera.MAP_SIZE * teraScale.y / 2;
			Vector3f vertexs[4];
			Color4f colors[4];
			float fColor = -0.15f + (static_cast<float>(tera.Height(Xint, Yint)) / 256.0f);
			vertexs[0] = Vector3f(X + difX, Y + difY, static_cast<float>(tera.Height(Xint, Yint)) * teraScale.z);
			colors[0] = Color4f(0.2f, fColor, 0.2f, 1.0f);
			fColor = -0.15f + (static_cast<float>(tera.Height(Xint, Yint + tera.STEP_SIZE)) / 256.0f);
			vertexs[1] = Vector3f(X + difX, Y + difY + tera.STEP_SIZE, static_cast<float>(tera.Height(Xint, Yint + tera.STEP_SIZE)) * teraScale.z);
			colors[1] = Color4f(0.2f, fColor, 0.2f, 1.0f);
			fColor = -0.15f + (static_cast<float>(tera.Height(Xint + tera.STEP_SIZE, Yint + tera.STEP_SIZE)) / 256.0f);
			vertexs[2] = Vector3f(X + tera.STEP_SIZE + difX, Y + tera.STEP_SIZE + difY, static_cast<float>(tera.Height(Xint + tera.STEP_SIZE, Yint + tera.STEP_SIZE)) * teraScale.z);
			colors[2] = Color4f(0.2f, fColor, 0.2f, 1.0f);
			fColor = -0.15f + (static_cast<float>(tera.Height(Xint + tera.STEP_SIZE, Yint)) / 256.0f);
			vertexs[3] = Vector3f(X + tera.STEP_SIZE + difX, Y + difY, static_cast<float>(tera.Height(Xint + tera.STEP_SIZE, Yint)) * teraScale.z);
			colors[3] = Color4f(0.2f, fColor, 0.2f, 1.0f);
			render->drawQuad(vertexs, colors);
		}
		*/
	

	render->endDraw();
}

void UpdateKeys()
{
	if (keys[VK_PRIOR])
	{
		render->MoveCamera(Vector3f(0.0f, 1.0f * moveScale, 0.0f));		
	}
	if (keys[VK_NEXT])
	{		
		render->MoveCamera(Vector3f(0.0f, -1.0f * moveScale, 0.0f));	
	}
	if (keys['W'])
	{
		render->MoveCameraQ(1.0f * moveScale);		
	}
	if (keys['S'])
	{
		render->MoveCameraQ(-1.0f*moveScale);		
	}
	if (keys['A'])
	{
		render->MoveCamera(Vector3f(-1.0f * moveScale, 0.0f, 0.0f));
	}
	if (keys['D'])
	{
		render->MoveCamera(Vector3f(1.0f * moveScale, 0.0f, 0.0f));
	}
	if (keys[VK_UP])
	{
		render->RotateCamera(Quaternion(1.0f * rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (keys[VK_DOWN])
	{
		render->RotateCamera(Quaternion(-1.0f * rotateScale, Vector3f(1.0f, 0.0f, 0.0f)));
	}
	if (keys[VK_LEFT])
	{
		render->RotateCamera(Quaternion(1.0f * rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
	}
	if (keys[VK_RIGHT])
	{
		render->RotateCamera(Quaternion(-1.0f * rotateScale, Vector3f(0.0f, 1.0f, 0.0f)));
	}
}
//int main()
//_WIN#32
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Init();
	Draw();

	MSG msg;//_WIN#32
	memset(&msg, 0, sizeof(MSG));
	bool done = false;	
	DWORD tickCount = 0;//_WIN#32

	DWORD lastTickCount = GetTickCount();//_WIN#32

	// ���� ��������� ���������:
	while(!done)
	{
		//while GetMessage(&msg, nullptr, 0, 0)
		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		//{
		//TranslateMessage(&msg);
		//DispatchMessage(&msg);
		//}
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // ���� �� � ������� �����-������ ���������?
		{
			if (msg.message == WM_QUIT)        // �� ������� ��������� � ������?
			{
				done = true;          // ���� ���, done=true
			}
			else              // ���� ���, ������������ ���������
			{
				TranslateMessage(&msg);        // ��������� ���������
				DispatchMessage(&msg);        // �������� ���������
			}
		}
		else                // ���� ��� ���������
		{
			// ������������� �����.
			if (active && !pause)          // ������� �� ���������?
			{
				UpdateKeys();

				// �� ����� ��� ������, ������� �����.
				tickCount = GetTickCount();//_WIN#32
				DWORD milliseconds = tickCount - lastTickCount;//_WIN#32
				lastTickCount = tickCount;
				float dt = static_cast<float>(milliseconds) / 1000.0f; // ����������� ������������ � �������
				dt /= slowMotionRatio;             // ����� �� slowMotionRatio

				timeElapsed += dt;                 // �������� ���-�� ���������� �������

				int numOfIterations = static_cast<int>((dt / maxPossible_dt) + 1);	// ������������ ���������� ��������, ������� ���������� �������� � ���� �������� ����������(������� �� maxPossible_dt � dt).

				if (numOfIterations != 0)		// ��������� ������� �� 0
					dt = dt / numOfIterations;	// dt ����� ��������, �������� �� numOfIterations.
											   
				for (int a = 0; a < numOfIterations; ++a)	// �� ������ ��������� ��������� "numOfIterations" ���.
					Update(dt);			

				Draw();
			}

			if (keys[VK_F1])          // ���� �� ������ F1?
			{
				keys[VK_F1] = false;        // ���� ���, ������ �������� ������ ������� �� false
				render->killWindow();          // ��������� ������� ����
				fullscreen = !fullscreen;      // ����������� �����
											   // ���������� ���� OpenGL ����
				if (!render->createWindow(title, width, height, bits, fullscreen))
				{
					done = true;
				}
				else
				{
					Draw();
				}
			}
			if (keys[VK_SPACE])
			{
				if (pause)	lastTickCount = GetTickCount();

				keys[VK_SPACE] = false;
				pause = ! pause;
			}
			if (keys[VK_ESCAPE])        // ���� �� ������ ������� ESC?
			{
				done = true;      // ESC ������� �� �������� ���������� ���������
			}

		}
	}

	//delete simulation;

	delete render;

	return static_cast<int>(msg.wParam);
}

//_WIN#32
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:            // �������� ��������� ���������� ����
	{
		if (!HIWORD(wParam))//_WIN#32 // ��������� ��������� �����������
		{
			active = true;          // ��������� �������
		}
		else
		{
			active = false;          // ��������� ������ �� �������
		}

		return 0;            // ������������ � ���� ��������� ���������
	}
	case WM_SYSCOMMAND:            // ������������� ��������� �������
	{
		switch (wParam)            // ������������� ��������� �����
		{
		case SC_SCREENSAVE:        // �������� �� ���������� �����������?
		case SC_MONITORPOWER:        // �������� �� ������� ������� � ����� ���������� �������?
			return 0;          // ������������� ���
		}
		break;              // �����
	}
	case WM_CLOSE:              // �� �������� ��������� � ��������?
	{
		PostQuitMessage(0);//_WIN#32          // ��������� ��������� � ������
		return 0;            // ��������� �����
	}
	case WM_KEYDOWN:            // ���� �� ������ ������?
	{
		keys[wParam] = true;          // ���� ���, �� ����������� ���� ������ true
		return 0;            // ������������
	}
	case WM_KEYUP:              // ���� �� �������� �������?
	{
		keys[wParam] = false;          //  ���� ���, �� ����������� ���� ������ false
		return 0;            // ������������
	}
	case WM_SIZE:              // �������� ������� OpenGL ����
	{
		render->resize(LOWORD(lParam), HIWORD(lParam));//_WIN#32  // ������� �����=Width, ������� �����=Height
		return 0;            // ������������
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);//_WIN#32
}


