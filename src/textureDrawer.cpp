#include "textureDrawer.h"

void TextureDrawer::setup()
{
	//Un peu comme on fait dans le cours, on pourrait éventuellement penser à une meilleure structure de données
	count = 100;

	stroke_color_r = 242;
	stroke_color_g = 225;
	stroke_color_b = 31;
	stroke_color_a = 0;

	fill_color_r = 242;
	fill_color_g = 225;
	fill_color_b = 31;
	fill_color_a = 0;

	head = 0;

	stride = sizeof(VectorPrimitive);

	size = count * stride;

	shapes = (VectorPrimitive*)std::malloc(size);

	selectedType = VectorPrimitiveType::point;
}

void TextureDrawer::draw()
{
	for (int index = 0; index < count; index++)
	{
		switch (shapes[index].type)
		{

		case VectorPrimitiveType::point:

			ofFill();
			ofSetLineWidth(0);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_point(
				shapes[index].position2[0],
				shapes[index].position2[1],
				shapes[index].stroke_width);
			break;

		case VectorPrimitiveType::line:

			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_line(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::rectangle:

			ofFill();
			ofSetLineWidth(0);
			ofSetColor(
				shapes[index].fill_color[0],
				shapes[index].fill_color[1],
				shapes[index].fill_color[2]);
			draw_rectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_rectangle(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		case VectorPrimitiveType::ellipse:

			ofFill();
			ofSetLineWidth(0);
			ofSetCircleResolution(48);
			ofSetColor(
				shapes[index].fill_color[0],
				shapes[index].fill_color[1],
				shapes[index].fill_color[2]);
			draw_ellipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			ofNoFill();
			ofSetLineWidth(shapes[index].stroke_width);
			ofSetColor(
				shapes[index].stroke_color[0],
				shapes[index].stroke_color[1],
				shapes[index].stroke_color[2]);
			draw_ellipse(
				shapes[index].position1[0],
				shapes[index].position1[1],
				shapes[index].position2[0],
				shapes[index].position2[1]);
			break;

		default:
			break;
		}
	}
}

void TextureDrawer::selectPointType()
{
	selectedType = VectorPrimitiveType::point;
	cout << "point" << endl;
}

void TextureDrawer::selectLineType()
{
	selectedType = VectorPrimitiveType::line;
	cout << "line" << endl;
}

void TextureDrawer::selectRectangleType()
{
	selectedType = VectorPrimitiveType::rectangle;
	cout << "rectangle" << endl;
}

void TextureDrawer::selectEllipseType()
{
	selectedType = VectorPrimitiveType::ellipse;
	cout << "ellipse" << endl;
}

void TextureDrawer::add_vector_shape()
{
	shapes[head].type = selectedType;

	shapes[head].position1[0] = mouse_pressed_posX;
	shapes[head].position1[1] = mouse_pressed_posY;

	shapes[head].position2[0] = mouse_current_posX;
	shapes[head].position2[1] = mouse_current_posY;

	shapes[head].stroke_color[0] = stroke_color_r;
	shapes[head].stroke_color[1] = stroke_color_g;
	shapes[head].stroke_color[2] = stroke_color_b;
	shapes[head].stroke_color[3] = stroke_color_a;

	shapes[head].fill_color[0] = fill_color_r;
	shapes[head].fill_color[1] = fill_color_g;
	shapes[head].fill_color[2] = fill_color_b;
	shapes[head].fill_color[3] = fill_color_a;

	switch (shapes[head].type)
	{
	case VectorPrimitiveType::point:
		shapes[head].stroke_width = 4;
		break;

	case VectorPrimitiveType::line:
		shapes[head].stroke_width = ofRandom(1, 16);
		break;

	case VectorPrimitiveType::rectangle:
		shapes[head].stroke_width = stroke_width_default;
		break;

	case VectorPrimitiveType::ellipse:
		shapes[head].stroke_width = stroke_width_default;
		break;

	default:
		shapes[head].stroke_width = stroke_width_default;
		break;
	}

	cout << "<new primitive at index: " << head << ">" << endl;

	head = ++head >= count ? 0 : head;
}

void TextureDrawer::draw_point(float x, float y, float radius) const
{
	ofDrawEllipse(x, y, radius, radius);
}

void TextureDrawer::draw_line(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);
}

void TextureDrawer::draw_rectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

void TextureDrawer::draw_ellipse(float x1, float y1, float x2, float y2) const
{
	float diameter_x = x2 - x1;
	float diameter_y = y2 - y1;

	ofDrawEllipse(x1 + diameter_x / 2.0f, y1 + diameter_y / 2.0f, diameter_x, diameter_y);
}
