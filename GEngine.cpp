//#include <iostream>

#include "GEngine.h"
#include "Vector3f.h"
#include "Quaternion.h"
#include "FileReader.h"
#include "Model.h"
#include "ConstantVelocity.h"
//#include "MotionUnderGravitation.h"
//#include "MassConnectedWithSpring.h"

#include "Tera.h"

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

unsigned FPS = 0;

bool drawDebugInfo = false;

enum Scene { Scene0, Scene1, Scene2, Scene3 };

Scene scene;

Simulation* simulation = nullptr;

Model model;

Tera tera;

// ��� ������� ������������� �������� ����� ��� ����������� ������, ���������� �� ������ ������

void Init()
{
	//if (MessageBox(NULL, "������ �� �� ��������� ���������� � ������������� ������?", "��������� � ������������� ������?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	//{
	//fullscreen = false;          // ������� �����
	//}

	FileReader fileReader;
	int sceneInt = fileReader.GetSceneNum("GEngine.ini");
	scene = static_cast<Scene>(sceneInt);

	render = new RenderGL(fullscreen, true, Vector3f(0.0f, 0.0f, 1000.0f), Quaternion(0.0f, Vector3f(0.0f, 0.0f, 0.0f)));

	// ������� ���� OpenGL ����
	if (!render->createWindow(title, width, height, bits))
	{
		return;              // �����, ���� ���� �� ����� ���� �������
	}

	if (scene == Scene::Scene0)
	{
		//fileReader.ReadModelOBJ(model, "data/Boat/MedievalBoat.obj");
		//fileReader.ReadModelOBJ(model, "data/PirateShip/PirateShip.obj");
		fileReader.ReadModelOBJ(model, "data/Tank/Tank.obj");
		//fileReader.ReadModelOBJ(model, "data/T34/T34_FBX.obj");
		//fileReader.ReadModelOBJ(model, "data/Dragon/BGE_Dragon_2.5_Blender_Game_Engine.obj");	
		//fileReader.ReadModelOBJ(model, "data/T34/t_34_obj.obj");
		//fileReader.ReadModelOBJ(model, "data/Manowar.obj");
	}

	if (scene == Scene::Scene1)
	{
		fileReader.LoadRawFile("data/Terrain.raw", tera.MAP_SIZE * tera.MAP_SIZE, tera.HeightMap);
	}

	if (scene == Scene::Scene2)
	{
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
	}
}

void Update(float dt)
{
	if (scene == Scene::Scene2)	simulation->operate(dt);
}

void Draw()
{	
	render->beginDraw();

	//render->drawBox(Vector3f(50.0f, 0.0f, 0.0f), Vector3f(100.0f, 1.0f, 1.0f), Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	//render->drawBox(Vector3f(0.0f, 50.0f, 0.0f), Vector3f(1.0f, 100.0f, 1.0f), Color4f(0.0f, 1.0f, 0.0f, 1.0f));
	//render->drawBox(Vector3f(0.0f, 0.0f, 50.0f), Vector3f(1.0f, 1.0f, 100.0f), Color4f(0.0f, 0.0f, 1.0f, 1.0f));

	//Draw Sea
	//render->drawSphere(Vector3f(0.0f, 0.0f, -500), 500.0f, Vector3f(0.1f, 0.3f, 0.9f));
	
	switch (scene)
	{
	case Scene::Scene0:
		for (size_t i = 0; i < model.nGroup; ++i)
		{
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
					Vector3f vert[5];
					Vector3f norm[5];
					vert[0] = model.vertexs[surface.Vertexs[0]];
					norm[0] = model.normals[surface.Normals[0]];
					vert[1] = model.vertexs[surface.Vertexs[1]];
					norm[1] = model.normals[surface.Normals[1]];
					vert[2] = model.vertexs[surface.Vertexs[2]];
					norm[2] = model.normals[surface.Normals[2]];
					vert[3] = model.vertexs[surface.Vertexs[3]];
					norm[3] = model.normals[surface.Normals[3]];
					vert[4] = model.vertexs[surface.Vertexs[4]];
					norm[4] = model.normals[surface.Normals[4]];
					Color4f color(0.0f, 1.0f, 0.0f, 1.0f);
					render->drawTriangleStrip(5, vert, norm, color);
				}
				else if (surface.n == 6)
				{
					Vector3f vert[6];
					Vector3f norm[6];
					vert[0] = model.vertexs[surface.Vertexs[0]];
					norm[0] = model.normals[surface.Normals[0]];
					vert[1] = model.vertexs[surface.Vertexs[1]];
					norm[1] = model.normals[surface.Normals[1]];
					vert[2] = model.vertexs[surface.Vertexs[2]];
					norm[2] = model.normals[surface.Normals[2]];
					vert[3] = model.vertexs[surface.Vertexs[3]];
					norm[3] = model.normals[surface.Normals[3]];
					vert[4] = model.vertexs[surface.Vertexs[4]];
					norm[4] = model.normals[surface.Normals[4]];
					vert[5] = model.vertexs[surface.Vertexs[4]];
					norm[5] = model.normals[surface.Normals[4]];


					Color4f color(0.0f, 0.0f, 1.0f, 1.0f);
					render->drawTriangleStrip(6, vert, norm, color);
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
		break;
	case Scene::Scene1:
		for (int Xint = 0; Xint < tera.MAP_SIZE; Xint += tera.STEP_SIZE)
			for (int Yint = 0; Yint < tera.MAP_SIZE; Yint += tera.STEP_SIZE)
			{
				float X = static_cast<float>(Xint) * teraScale.x;
				float Y = static_cast<float>(Yint) * teraScale.y;
				float difX = -tera.MAP_SIZE * teraScale.x / 2;
				float difY = -tera.MAP_SIZE * teraScale.y / 2;
				Vector3f vertexs[4];
				Vector3f n;
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

				n = ((vertexs[1] - vertexs[0]) * (vertexs[4] - vertexs[0])).unit();
				render->drawQuad(vertexs, n, colors[0]);
			}
		break;
	case Scene::Scene2:
		simulation->draw(*render);
		break;
	//case Scene::Scene3:
		//break;
	default:
		break;
	}

	if (drawDebugInfo)
	{
		render->print(Vector3f(-22.0f, 11.0f, -30.0f), "FPS: %d", FPS);
	}
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
		//render->MoveCameraQ(10.0f * moveScale);
		render->MoveCamera(Vector3f(0.0f, 25.0f * moveScale, 0.0f));
	}
	if (keys['S'])
	{
		//render->MoveCameraQ(-10.0f*moveScale);
		render->MoveCamera(Vector3f(0.0f, -25.0f * moveScale, 0.0f));
	}
	if (keys['A'])
	{
		render->MoveCamera(Vector3f(-25.0f * moveScale, 0.0f, 0.0f));
	}
	if (keys['D'])
	{
		render->MoveCamera(Vector3f(25.0f * moveScale, 0.0f, 0.0f));
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
	if (keys[VK_TAB])
	{
		keys[VK_TAB] = false;
		drawDebugInfo = !drawDebugInfo;
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

				if (dt > 0.0f)
					FPS = static_cast<unsigned>(1.0f / dt);
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
				render->setFullscreen(fullscreen);
				if (!render->createWindow(title, width, height, bits))
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


