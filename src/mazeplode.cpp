#include "mazeplode.h"
#include "menustate.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//--------------------------------------------------------------
void mazeplode::setup()
{

	GLFWwindow* window = static_cast<ofAppGLFWWindow*>(ofGetWindowPtr())->getGLFWWindow();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::CreateContext();
	mazeplode::ChangeState(new CMenuState);
}

//--------------------------------------------------------------
void mazeplode::update()
{
	m_pState->update();
}

//--------------------------------------------------------------
void mazeplode::draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	m_pState->draw();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

mazeplode::~mazeplode()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void mazeplode::ChangeState(IBaseState* pNewState)
{
	if (m_pState)
	{
		ofLog(OF_LOG_NOTICE, "Changing State from %s to %s", m_pState->m_sStateName, pNewState->m_sStateName);
		m_pState->release();
	}
	else
	{
		ofLog(OF_LOG_NOTICE, "Changing Initial State to %s", pNewState->m_sStateName);
	}

	m_pState = pNewState;
	m_pState->m_pApp = this;
	m_pState->setup();
}

//--------------------------------------------------------------
void mazeplode::keyPressed(int key)
{
	m_pState->keyPressed(key);
}

//--------------------------------------------------------------
void mazeplode::keyReleased(int key)
{
	m_pState->keyReleased(key);
}

//--------------------------------------------------------------
void mazeplode::mouseMoved(int x, int y)
{
	m_pState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void mazeplode::mouseDragged(int x, int y, int button)
{
	m_pState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void mazeplode::mousePressed(int x, int y, int button)
{
	m_pState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void mazeplode::mouseReleased(int x, int y, int button)
{
	m_pState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void mazeplode::mouseEntered(int x, int y)
{
	m_pState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void mazeplode::mouseExited(int x, int y)
{
	m_pState->mouseExited(x, y);
}

//--------------------------------------------------------------
void mazeplode::windowResized(int w, int h)
{
	m_pState->windowResized(w, h);
}

//--------------------------------------------------------------
void mazeplode::gotMessage(ofMessage msg)
{
	m_pState->gotMessage(msg);
}

//--------------------------------------------------------------
void mazeplode::dragEvent(ofDragInfo dragInfo)
{
	m_pState->dragEvent(dragInfo);
}