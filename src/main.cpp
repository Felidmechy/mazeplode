#include "ofMain.h"
#include "mazeplode.h"

//========================================================================
int main( ){

	ofSetupOpenGL(640,640,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetWindowTitle("mazeplode");
	ofRunApp(new mazeplode());

}
