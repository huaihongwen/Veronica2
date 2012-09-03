/**
 * veGUIElement.h
 */

#ifndef VEE_GUIELEMENT_H
#define VEE_GUIELEMENT_H

#include "vePrerequisites.h"
#include "veGeometry.h"
#include "veTexture.h"


namespace vee {

	// veGUIElement
	class veGUIElement {

	public:
		veGUIElement();
		virtual ~veGUIElement();


	public:
		// Init
		virtual void init();

		// Destroy
		virtual void destroy();


		// Render
		// This function assumes the ortho projection and the viewport are
		// already setup.
		virtual void render();


	public:
		// Mouse left botton down
		// @param x mouse x position relative to window.
		// @param y mouse y position relative to window.
		// @param mouse inside the GUI element or not.
		virtual bool mouseLDown(int x, int y);

		// Mouse left botton up
		// @param x mouse x position relative to window.
		// @param y mouse y position relative to window.
		// @param mouse inside the GUI element or not.
		virtual bool mouseLUp(int x, int y);

		// Mouse move
		// @param x mouse x position relative to window.
		// @param y mouse y position relative to window.
		// @param mouse inside the GUI element or not.
		virtual bool mouseMove(int x, int y);


	public:
		// Set id
		// @param id input id.
		void setId(const char* id);

		// Get id
		// @return GUI element's id reference.
		string& getId();


		// Set rect
		// @param r input rect reference.
		void setRect(veRect& r);

		// Get rect
		// @return GUI element's rect reference.
		veRect& getRect();


		// Set background color
		// @param r red.
		// @param g green.
		// @param b blue.
		// @param a alpha.
		void setBgColor(uchar r, uchar g, uchar b, uchar a=255);


		// Set texture
		// @param t input texture pointer.
		void setTexture(veTexture* t);

		// Set texture coordinates
		// @param coords input texture coordinates.
		void setTexCoords(float* coords);


	protected:
		// Id
		string _mId;


		// Rect
		veRect _mRect;


		// Background color
		uchar _mBgColor[4];


		// Texture
		veTexture* _mTexture;

		// Texture coordinates
		float _mTexCoords[8];
	};
};

#endif