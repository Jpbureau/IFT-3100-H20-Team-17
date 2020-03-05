#include "cameraGui.h"


CameraGui::CameraGui()
{
}

void CameraGui::setup(int positionX, int positionY)
{
	CameraPanel.setup("Camera");
	CameraPanel.setPosition(positionX, positionY);

	perspective = true;
	selectedViewMode.setName("Mode camera");
	selectedViewMode.set("Perspective");

	xCoordinateSlider.set("Coordonnees X", 100.0f, -1000.0f, 1000.0f);
	yCoordinateSlider.set("Coordonnees Y ", 100.0f, -1000.0f, 1000.0f);
	zCoordinateSlider.set("Coordonnees Z", 100.0f, -1000.0f, 1000.0f);

	xRotationSlider.set("Rotation X", 180.0f, 0.0f, 360.0f);
	yRotationSlider.set("Rotation Y", 180.0f, 0.0f, 360.0f);
	zRotationSlider.set("Rotation Z", 180.0f, 0.0f, 360.0f);

	horizontalAngleSlider.set("Angle horizontal", 45.0f, 10.0f, 120.0f);
	verticalAngleSlider.set("Angle vertical", 45.0f, 10.0f, 120.0f);

	frustumCloseSlider.set("Frustum rapproche", 10.0f, 5.0f, 1000.0f);
	frustumFarSlider.set("Frustum eloigne", 200.0f, 5.0f, 1000.0f);

	CameraPanel.add(selectedViewMode);
	CameraPanel.add(perpesctiveModeButton.setup("Orthogonale"));
	CameraPanel.add(xCoordinateSlider);
	CameraPanel.add(yCoordinateSlider);
	CameraPanel.add(zCoordinateSlider);
	CameraPanel.add(xRotationSlider);
	CameraPanel.add(yRotationSlider);
	CameraPanel.add(zRotationSlider);
	CameraPanel.add(horizontalAngleSlider);
	CameraPanel.add(verticalAngleSlider);
	CameraPanel.add(frustumCloseSlider);
	CameraPanel.add(frustumFarSlider);
	CameraPanel.add(resetCameraButton.setup("Reset Camera"));

	perpesctiveModeButton.addListener(this, &CameraGui::changerPerspective);
	resetCameraButton.addListener(this, &CameraGui::resetCamera);
}

void CameraGui::update()
{

}

void CameraGui::draw()
{
	CameraPanel.draw();
}

void CameraGui::resetCamera()
{
	//TextureDrawer3D::resetCamera();
}

void CameraGui::changerPerspective()
{
	perspective = !perspective;
	if (perspective)
	{
		selectedViewMode.set("Perspective");
		perpesctiveModeButton.setName("Orthogonale");
	}
	else
	{
		selectedViewMode.set("Orthogonale");
		perpesctiveModeButton.setName("Perspective");
	}
}