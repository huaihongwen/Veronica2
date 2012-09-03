


/**
 * veFontSystem.h
 */

#ifndef VEE_FONTSYSTEM_H
#define VEE_FONTSYSTEM_H

#include "vePrerequisites.h"
#include "veSingleton.h"
#include "veTexture.h"


namespace vee {

	// veFontSystem
	class veFontSystem : public SingletonVee<veFontSystem> {

	public:
		veFontSystem();
		~veFontSystem();


	public:
		// Get singleton
		static veFontSystem& veFontSystem::getSingleton(void);
		// Get singleton ptr
		static veFontSystem* veFontSystem::getSingletonPtr(void);


	public:
		// Init
		void init(int fw=16, int fh=16, veTexture* tex=NULL);

		// Destroy
		void destroy();


		// Render string
		// Render string, this function assumes the ortho projection and
		// viewport are already setup.
		// @param str input string.
		// @param len input string length.
		// @param x x position relative to window.
		// @param y y position relative to window.
		// @param color font color rgba.
		void renderString(const char* str, int len, int x, int y, uchar* color);


	public:
		// Set font width
		// @param w input width.
		void setFontWidth(int w);

		// Set font height
		// @param h input height.
		void setFontHeight(int h);


		// Set font texture
		// @param tex input font texture
		void setFontTexture(veTexture* tex);


	protected:
		// Font width in pixel
		int _mFontWidth;

		// Font height in pixel
		int _mFontHeight;


		// Font texture
		veTexture* _mFontTexture;
	};
};

#endif







#include "veFontSystem.h"
#include "veRenderSystem.h"

namespace vee {

	//---------------------------------------------------------------
	veFontSystem::veFontSystem() {

		// Font texture
		_mFontTexture = NULL;
	}

	//---------------------------------------------------------------
	veFontSystem::~veFontSystem() {

		destroy();
	}


	//---------------------------------------------------------------
	// Initialize the static member.
	template<> veFontSystem* SingletonVee<veFontSystem>::ms_Singleton = 0;
	veFontSystem& veFontSystem::getSingleton(void) {
		return *ms_Singleton;
	}

	//---------------------------------------------------------------
	veFontSystem* veFontSystem::getSingletonPtr(void) {
		return ms_Singleton;
	}


	//---------------------------------------------------------------
	// Init
	void veFontSystem::init(int fw, int fh, veTexture* tex) {

		// Font width in pixel
		_mFontWidth = fw;

		// Font height in pixel
		_mFontHeight = fh;


		// Font texture
		_mFontTexture = tex;
	}

	//---------------------------------------------------------------
	// Destroy
	void veFontSystem::destroy() {
	}


	//---------------------------------------------------------------
	// Render string
	void veFontSystem::renderString(const char* str, int len, int x, int y, uchar* color) {

		// Empty texture
		if (!_mFontTexture) {
			return;
		}


		// Render system
		RenderSystem& rs = RenderSystem::getSingleton();


		// Window height
		int wh = rs.getWindowHeight();

		// Start x
		float sx = float(x);
		// Start y
		float sy = float(y);


		// Char index
		int cIdx = 0;
		// Line idx
		int lIdx = 0;


		// UV step x
		float uvx = 0.0625f;
		// UV step y
		float uvy = 0.125f;

		// Grid position
		int gx, gy;


		// Bind font texture
		rs.bindTexture2D(_mFontTexture->getId(), 0);

		// Font color
		glColor4ubv(color);
		glBegin(GL_QUADS);

		// Loop each char in str
		for (int i = 0; i < len; i++) {

			// '\n'
			if (str[i] == '\n') {

				// Reset char index
				cIdx = 0;
				// Increase line index
				lIdx++;

				continue;
			} else {

				// Render char
				// Grid x
				gx = str[i] % 16;
				// Grid y
				gy = (int)floor((float)str[i] / 16.0f);


				// Fonts are rendered on top of GUI elements
				glTexCoord2f(gx*uvx, (gy+1)*uvy);
				glVertex3f(sx+cIdx*_mFontWidth, wh-(sy+lIdx*_mFontHeight), -1.0f);
				glTexCoord2f(gx*uvx, gy*uvy);
				glVertex3f(sx+cIdx*_mFontWidth, wh-(sy+(lIdx+1)*_mFontHeight), -1.0f);
				glTexCoord2f((gx+1)*uvx, gy*uvy);
				glVertex3f(sx+(cIdx+1)*_mFontWidth, wh-(sy+(lIdx+1)*_mFontHeight), -1.0f);
				glTexCoord2f((gx+1)*uvx, (gy+1)*uvy);
				glVertex3f(sx+(cIdx+1)*_mFontWidth, wh-(sy+lIdx*_mFontHeight), -1.0f);


				cIdx++;
			}
		}

		glEnd();

		// Unbind font texture
		rs.bindTexture2D(0, 0);
	}

	//---------------------------------------------------------------
	// Set font width
	void veFontSystem::setFontWidth(int w) {
		_mFontWidth = w;
	}

	//---------------------------------------------------------------
	// Set font height
	void veFontSystem::setFontHeight(int h) {
		_mFontHeight = h;
	}


	//---------------------------------------------------------------
	// Set font texture
	void veFontSystem::setFontTexture(veTexture* tex) {
		_mFontTexture = tex;
	}
};