#include "ofMain.h"
#include "basestate.h"
#include "ofxNetwork.h"
#include "imgui/imgui.h"
#include <map>
#pragma once

struct UserInfo
{
    int id;
    char name[16];
};


enum MessageType
{
    MESSAGE_JOIN = 1,
    MESSAGE_SAY,
    MESSAGE_LEAVE,
    MESSAGE_ID,
    MESSAGE_UPDATEUSERS
};

struct Message
{
    int m_iMsgType;
    int m_iVer = 1;

};

struct JoinMessage : public Message
{
    JoinMessage()
    {
        m_iMsgType = MESSAGE_JOIN;
    }

    char m_sName[16];
};

struct SayMessage : public Message
{
    SayMessage()
    {
        m_iMsgType = MESSAGE_SAY;
    }

    int m_iID;
    char m_sContent[256];
};

struct LeaveMessage : public Message
{
    LeaveMessage()
    {
        m_iMsgType = MESSAGE_LEAVE;
    }

    int m_iID;
};

struct IDMessage : public Message
{
    IDMessage()
    {
        m_iMsgType = MESSAGE_ID;
    }

    UserInfo id;
};

struct UpdateUsersMessage : public Message
{
    UpdateUsersMessage()
    {
        m_iMsgType = MESSAGE_UPDATEUSERS;
    }

    int numusers;
    UserInfo* data;
};

struct Console;
class CGameState : public IBaseState
{
public:

    CGameState();
    ~CGameState();

	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void release();


    bool m_bHosting;
    UserInfo m_info;
    std::map<int, UserInfo> m_infos;
    int m_lastid;
    char m_sPort[8];
	ofxUDPManager* m_pUDPMan;

    Console *console;

	virtual void keyPressed(int key);
	virtual void keyReleased(int key);
	virtual void mouseMoved(int x, int y);
	virtual void mouseDragged(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);
	virtual void mouseEntered(int x, int y);
	virtual void mouseExited(int x, int y);
	virtual void windowResized(int w, int h);
	virtual void dragEvent(ofDragInfo dragInfo);
	virtual void gotMessage(ofMessage msg);
};


