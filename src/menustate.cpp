#include "menustate.h"
#include "gamestate.h"
#include "imgui/imgui.h"
#include "console.h"

void CMenuState::setup()
{
	/*
	const char* sDefaultIP = "0.0.0.0";
	memcpy(&m_sIP, sDefaultIP, sizeof(sDefaultIP));
	const char* sDefaultPort = "27015";
	memcpy(&m_sPort, sDefaultPort, sizeof(sDefaultPort));
	*/
	memset(m_sUserName, 0, sizeof(m_sUserName));
	memset(m_sIP, 0, sizeof(m_sIP));
	memset(m_sHostPort, 0, sizeof(m_sHostPort));
	memset(m_sJoinPort, 0, sizeof(m_sJoinPort));

	m_pUDPMan = new ofxUDPManager();

	m_pUDPMan->Create();

}

void CMenuState::update()
{

}

void CMenuState::draw()
{
	ofBackground(ofColor(30,30,30));
	ofSetColor(ofColor::white);

	float XPos = 0;

	ImGui::Begin("General", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({ XPos += 16,64 });
	ImGui::SetWindowSize({ 128,128 });

	ImGui::InputText("Username",  m_sUserName, sizeof(m_sUserName));

	ImGui::End();

	ImGui::Begin("Host", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({ XPos += 128,64 });
	ImGui::SetWindowSize({ 256,416 });

	ImGui::PushItemWidth(ImGui::CalcItemWidth() * 0.25);
	ImGui::InputTextWithHint("Port", "27015", m_sHostPort, sizeof(m_sHostPort), ImGuiInputTextFlags_CharsDecimal);
	ImGui::PopItemWidth();

	bool bClickedHost = ImGui::Button("Start");
	ImGui::End();

	ImGui::Begin("Join", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({ XPos += 260,64 });
	ImGui::SetWindowSize({ 200, 128 });

	ImGui::PushItemWidth(ImGui::CalcItemWidth() * 0.75);
	ImGui::InputTextWithHint("IP", "0.0.0.0", m_sIP, sizeof(m_sIP), ImGuiInputTextFlags_CharsDecimal);
	ImGui::PopItemWidth();
	ImGui::PushItemWidth(ImGui::CalcItemWidth() * 0.25);
	ImGui::InputTextWithHint("Port", "27015", m_sJoinPort, sizeof(m_sJoinPort), ImGuiInputTextFlags_CharsDecimal);
	ImGui::PopItemWidth();

	bool bClickedJoin = ImGui::Button("Join");
	ImGui::End();

	if (bClickedHost)
	{

		CGameState* pGameState = new CGameState();
		pGameState->m_pUDPMan = m_pUDPMan;

		pGameState->m_bHosting = true;
		memcpy(pGameState->console->username, m_sUserName, sizeof(m_sUserName));
		memcpy(pGameState->m_sPort, m_sHostPort, sizeof(m_sHostPort));

		m_pApp->ChangeState(pGameState);
	}

	if (bClickedJoin)
	{
		unsigned short usPort = std::stoi(m_sJoinPort);
		bool bSuccess = m_pUDPMan->Connect(m_sIP, usPort);
		if (bSuccess)
		{
			ofLog(OF_LOG_NOTICE, "Connected Successfully\n");

			m_pUDPMan->Send("Mazeplode?", sizeof("Mazeplode?"));

			char sAcknowledge[5];
			int iRecv = m_pUDPMan->Receive(sAcknowledge, sizeof(sAcknowledge));

			if (iRecv > 0)
			{
				if (strcmp(sAcknowledge, "YES!") == 0)
				{
					CGameState* pGameState = new CGameState();
					pGameState->m_pUDPMan = m_pUDPMan;

					pGameState->m_bHosting = false;
					memcpy(pGameState->console->username, m_sUserName, sizeof(m_sUserName));

					m_pApp->ChangeState(pGameState);
				}
			}
			else
			{
				m_pUDPMan->Close();
			}
		}
	}
}

void CMenuState::release()
{
	IBaseState::release();
}

void CMenuState::keyPressed(int key)
{

}

void CMenuState::keyReleased(int key)
{

}

void CMenuState::mouseMoved(int x, int y)
{

}

void CMenuState::mouseDragged(int x, int y, int button)
{

}

void CMenuState::mousePressed(int x, int y, int button)
{

}

void CMenuState::mouseReleased(int x, int y, int button)
{

}

void CMenuState::mouseEntered(int x, int y)
{

}

void CMenuState::mouseExited(int x, int y)
{

}

void CMenuState::windowResized(int w, int h)
{

}

void CMenuState::dragEvent(ofDragInfo dragInfo)
{

}

void CMenuState::gotMessage(ofMessage msg)
{

}