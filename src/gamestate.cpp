#include "gamestate.h"
#include "menustate.h"
#include "console.h"

CGameState::CGameState() : IBaseState("CGameState")
{
	console = new Console();
	console->gamestate = this;
}

CGameState::~CGameState()
{
	//bleh, but just incase the user closes the entire application
	if (m_pUDPMan) 
	{
		LeaveMessage msg;
		msg.m_iID = m_info.id;
		m_pUDPMan->Send(reinterpret_cast<const char*>(&msg), sizeof(msg));
	}
}

void CGameState::setup()
{
	m_lastid = 0;

	m_pUDPMan->SetNonBlocking(true);
	if (m_bHosting)
	{
		unsigned short usPort = std::stoi(m_sPort);
		m_pUDPMan->Bind(usPort);

		UserInfo info;
		info.id = 0;
		memcpy(info.name, console->username, sizeof(console->username));
		m_info = info;
		m_infos[m_lastid] = info;
		m_lastid++;
	}
	else
	{
		JoinMessage msg;
		memcpy(msg.m_sName, console->username, sizeof(console->username));

		m_pUDPMan->Send(reinterpret_cast<const char*>(&msg), sizeof(msg));
	}
}

void CGameState::update()
{

	char sData[512];
	m_pUDPMan->Receive(sData, sizeof(sData));

	Message* msg = reinterpret_cast<Message*>(sData);

	if (m_bHosting)
	{
		if (strcmp(sData, "Mazeplode?") == 0)
		{
			m_pUDPMan->Send("YES!", sizeof("YES!"));
		}
		if (msg->m_iMsgType == MESSAGE_JOIN)
		{

			JoinMessage* joinmsg = reinterpret_cast<JoinMessage*>(msg);

			UserInfo info;
			info.id = m_lastid;
			memcpy(info.name, joinmsg->m_sName, sizeof(joinmsg->m_sName));
			m_infos[m_lastid] = info;
			m_lastid++;

			IDMessage idmsg;
			idmsg.id = info;
			m_pUDPMan->Send(reinterpret_cast<const char*>(&idmsg), sizeof(idmsg));

			UpdateUsersMessage updmsg;
			int count = m_infos.size();
			UserInfo* data = reinterpret_cast<UserInfo*>(calloc(count, sizeof(UserInfo)));

			for (int i = 0; i < count; i++)
			{
				data[i] = m_infos[i];
			}

			updmsg.numusers = count;
			updmsg.data = data;

			//FIX THIS

			m_pUDPMan->Send(reinterpret_cast<const char*>(&updmsg), (sizeof(updmsg)));

			free(data);
		}
	}
	else
	{
		if (msg->m_iMsgType == MESSAGE_ID)
		{
			IDMessage* idmsg = reinterpret_cast<IDMessage*>(msg);
			m_info = idmsg->id;
		}
	}
	if (msg->m_iMsgType == MESSAGE_JOIN)
	{
		JoinMessage* joinmsg = reinterpret_cast<JoinMessage*>(msg);
		console->AddLog("%s has joined!\n", joinmsg->m_sName);
	}
	if (msg->m_iMsgType == MESSAGE_SAY)
	{
		SayMessage* saymsg = reinterpret_cast<SayMessage*>(msg);
		console->Say(m_infos[saymsg->m_iID].name, saymsg->m_sContent);
	}
	if (msg->m_iMsgType == MESSAGE_LEAVE)
	{
		LeaveMessage* leavemsg = reinterpret_cast<LeaveMessage*>(msg);
		console->AddLog("%s has left!\n", m_infos[leavemsg->m_iID].name);
	}
	if (msg->m_iMsgType == MESSAGE_UPDATEUSERS)
	{
		UpdateUsersMessage* updmsg = reinterpret_cast<UpdateUsersMessage*>(msg);
		for (int i = 0; i < updmsg->numusers; i++)
		{
			m_infos[i] = updmsg->data[i];
		}
	}
}

void CGameState::draw()
{
	ofBackground(ofColor(30,30,30));
	ofSetColor(ofColor::white);

	bool bOpen = true;
	console->Draw("Console", &bOpen);

	if (!bOpen)
	{
		m_pApp->ChangeState(new CMenuState());
	}
}

void CGameState::release()
{
	if (m_bHosting)
	{

	}
	else
	{
		LeaveMessage msg;
		msg.m_iID = m_info.id;

		m_pUDPMan->Send(reinterpret_cast<const char*>(&msg), sizeof(msg));
	}
	m_pUDPMan->Close();
	delete m_pUDPMan;
	delete console;
	IBaseState::release();
}

void CGameState::keyPressed(int key)
{

}

void CGameState::keyReleased(int key)
{

}

void CGameState::mouseMoved(int x, int y)
{

}

void CGameState::mouseDragged(int x, int y, int button)
{

}

void CGameState::mousePressed(int x, int y, int button)
{

}

void CGameState::mouseReleased(int x, int y, int button)
{

}

void CGameState::mouseEntered(int x, int y)
{

}

void CGameState::mouseExited(int x, int y)
{

}

void CGameState::windowResized(int w, int h)
{

}

void CGameState::dragEvent(ofDragInfo dragInfo)
{

}

void CGameState::gotMessage(ofMessage msg)
{

}