#include "cursor.h"

Cursor::Cursor(TextureDrawer& textureDrawer, TextureDrawer3D& textureDrawer3D):
	textureDrawer(textureDrawer),
	textureDrawer3D(textureDrawer3D)
{
}

void Cursor::setup()
{
	ofAddListener(ofEvents().mouseMoved, this, &Cursor::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &Cursor::mouseMoved);
	ofAddListener(ofEvents().mousePressed, this, &Cursor::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &Cursor::mouseReleased);

	pencilImage.load("cursor/pencil.png");
	handImage.load("cursor/hand.png");
	closedHandImage.load("cursor/closedHand.png");
	selectionCursorImage.load("cursor/selection.png");
}

void Cursor::setCursorImage(CursorTypes type)
{
	this->type = type;
}

void Cursor::draw()
{
	switch (type)
	{
	case pencil:
		ofHideCursor();
		pencilImage.draw(x, y - 30, 30, 30);
		break;
	case hand:
		ofHideCursor();
		handImage.draw(x, y - 30, 30, 30);
		break;
	case closedHand:
		ofHideCursor();
		closedHandImage.draw(x, y - 30, 30, 30);
		break;
	case selection:
		ofHideCursor();
		selectionCursorImage.draw(x, y, 30, 30);
		break;
	case none:
		ofShowCursor();
		break;
	default:
		break;
	}
}

void Cursor::update()
{
	if (textureDrawer.isMouseInsideCanvas(x, y)) {
		if (textureDrawer.isTypeSelection()) {
			setCursorImage(selection);
		}
		else {
			setCursorImage(pencil);
		}
	}
	else if (textureDrawer3D.isMouseInsideModelCanvas(x, y)) {
		if (mouseIsPressed) {
			setCursorImage(closedHand);
		}
		else
		{
			setCursorImage(hand);
		}
	}
	else {
		setCursorImage(none);
	}
}

void Cursor::mouseMoved(ofMouseEventArgs & mouse)
{
	x = mouse.x;
	y = mouse.y;
}

void Cursor::mouseReleased(ofMouseEventArgs & mouse)
{
	mouseIsPressed = false;
}

void Cursor::mousePressed(ofMouseEventArgs & mouse)
{
	mouseIsPressed = true;
}
