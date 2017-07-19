#include "Engine.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "CircleStrip.hpp"

int main(int argc, char** argv) {

	float rect_width, rect_height;
	float circle_radius;
	float strip_radius, strip_thick;

	rect_width    = 0.7f;
	rect_height   = 0.3f;
	circle_radius = 0.5f;
	strip_radius  = 0.7f;
	strip_thick   = 0.05f;

	cnbi::draw::Engine 	engine;

	cnbi::draw::Rectangle   rectangle(rect_width, rect_height, dtk_red);
	cnbi::draw::Circle		circle(circle_radius, dtk_green);
	cnbi::draw::CircleStrip	strip(strip_radius, strip_thick, dtk_blue);

	printf("Create rectangle (width=%f, height=%f)\n", rect_width, rect_height);
	rectangle.Create();
	
	printf("Create circle (radius=%f)\n", circle_radius);
	circle.Create();
	
	printf("Create circular strip (radius=%f, thick=%f)\n", strip_radius, strip_thick);
	strip.Create();
	
	printf("Add shapes to the engine\n");	
	engine.AddShape("rectangle", &rectangle);
	engine.AddShape("circle", &circle);
	engine.AddShape("strip", &strip);

	printf("Dumping current shapes\n");
	engine.Dump();
	engine.Open();

	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(true) {

		rectangle.RelRotate(1.0f);

		circle.RelMove(0.01f, 0.01f);

		if((int)(CcTime::Toc(&tic)/1000) % 2 == 0) {
			strip.Show();
		} else {
			strip.Hide();
		}

		if(CcTime::Toc(&tic) > 5000)
			break;

		CcTime::Sleep(100);
	}
	printf("Dumping current shapes\n");
	engine.Dump();

	printf("Raise rectangle:\n");
	engine.RaiseShape("rectangle");
	engine.Dump();
	
	printf("Lower strip:\n");
	engine.LowerShape("strip");
	engine.Dump();
	
	printf("Lower circle:\n");
	engine.LowerShape("circle");
	engine.Dump();
	
	printf("Removing 'circle' shape\n");
	engine.RemoveShape("circle");
	engine.Dump();

	printf("Quit..\n");

	return 0;

	
}
