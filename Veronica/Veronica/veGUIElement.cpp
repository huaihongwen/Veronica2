#include "veGUIElement.h"
#include "veUtils.h"

#include <windows.h>
#include <GL\glew.h>

namespace vee {

	//---------------------------------------------------------------
	veGUIElement::veGUIElement() {

		// Texture
		_mTexture = NULL;

		// Texture coordinates
		_mTexCoords[0] = 0.0f;
		_mTexCoords[1] = 1.0f;
		_mTexCoords[2] = 0.0f;
		_mTexCoords[3] = 0.0f;
		_mTexCoords[4] = 1.0f;
		_mTexCoords[5] = 0.0f;
		_mTexCoords[6] = 1.0f;
		_mTexCoords[7] = 1.0f;
	}

	//---------------------------------------------------------------
	veGUIElement::~veGUIElement() {
	}


	//---------------------------------------------------------------
	// Init
	void veGUIElement::init() {
	}

	//---------------------------------------------------------------
	// Destroy
	void veGUIElement::destroy() {
	}


	//---------------------------------------------------------------
	// Render
	void veGUIElement::render() {

		// Upper left corner and bottom right corner
		float x0 = float(_mRect.x);
		float y0 = float(_mRect.y);
		float x1 = x0 + _mRect.w;
		float y1 = y0 + _mRect.h;


		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();

		// Get window height
		int wh = rs.getWindowHeight();


		// Texture
		if (_mTexture) {

			// Bind texture
			rs.bindTexture2D(_mTexture->getId(), 0);

			// Color
			glColor4ubv(_mBgColor);
			glBegin(GL_QUADS);
				glTexCoord2f(_mTexCoords[0], _mTexCoords[1]);
				glVertex3f(x0, wh-y0, 0.0f);
				glTexCoord2f(_mTexCoords[2], _mTexCoords[3]);
				glVertex3f(x0, wh-y1, 0.0f);
				glTexCoord2f(_mTexCoords[4], _mTexCoords[5]);
				glVertex3f(x1, wh-y1, 0.0f);
				glTexCoord2f(_mTexCoords[6], _mTexCoords[7]);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();

			// Unbind texture
			rs.bindTexture2D(0, 0);
		} else {

			// Color
			glColor4ubv(_mBgColor);
			glBegin(GL_QUADS);
				glVertex3f(x0, wh-y0, 0.0f);
				glVertex3f( x0, wh-y1, 0.0f);
				glVertex3f(x1, wh-y1, 0.0f);
				glVertex3f(x1, wh-y0, 0.0f);
			glEnd();
		}
	}


	//---------------------------------------------------------------
	// Mouse left button down
	bool veGUIElement::mouseLDown(int x, int y) {
		return true;
	}

	//---------------------------------------------------------------
	// Mouse left button up
	bool veGUIElement::mouseLUp(int x, int y) {
		return true;
	}

	//---------------------------------------------------------------
	// Mouse move
	bool veGUIElement::mouseMove(int x, int y) {
		return true;
	}


	//---------------------------------------------------------------
	// Set id
	void veGUIElement::setId(const char* id) {
		_mId = id;
	}

	//---------------------------------------------------------------
	// Get id
	string& veGUIElement::getId() {
		return _mId;
	}


	//---------------------------------------------------------------
	// Set rect
	void veGUIElement::setRect(veRect& r) {
		_mRect = r;
	}

	//---------------------------------------------------------------
	// Get rect
	veRect& veGUIElement::getRect() {
		return _mRect;
	}


	//---------------------------------------------------------------
	// Set background color
	void veGUIElement::setBgColor(uchar r, uchar g, uchar b, uchar a) {

		_mBgColor[0] = r;
		_mBgColor[1] = g;
		_mBgColor[2] = b;
		_mBgColor[3] = a;
	}


	//---------------------------------------------------------------
	// Set texture
	void veGUIElement::setTexture(veTexture* t) {
		_mTexture = t;
	}

	//---------------------------------------------------------------
	// Set texture coordinates
	void veGUIElement::setTexCoords(float* coords) {

		for (int i = 0; i < 8; i++) {

			_mTexCoords[i] = coords[i];
		}
	}
};