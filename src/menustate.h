#include "ofMain.h"
#include "basestate.h"
#include "ofxNetwork.h"
#pragma once

class CMenuState : public IBaseState
{
public:

	CMenuState() : IBaseState("CMenuState")
	{

	}

	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void release();

	char m_sUserName[16];

	char m_sIP[16];
	char m_sHostPort[8];
	char m_sJoinPort[8];

	ofxUDPManager *m_pUDPMan;


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

