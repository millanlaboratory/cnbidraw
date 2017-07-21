#include "Engine.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "CircleStrip.hpp"
#include "Cross.hpp"
#include "Arrow.hpp"


int main(int argc, char** argv) {

	float rect_width, rect_height;
	float circle_radius;
	float strip_radius, strip_thick;
	float cross_size, cross_thick;
	float arrow_width, arrow_height;

	rect_width    = 0.7f;
	rect_height   = 0.3f;
	circle_radius = 0.7f;
	strip_radius  = 0.6f;
	strip_thick   = 0.05f;
	cross_size    = 0.2f;
	cross_thick   = 0.05f;
	arrow_width	  = 0.4;
	arrow_height  = 0.3;

	cnbi::draw::Engine 	engine;

	cnbi::draw::Rectangle   rectangle(rect_width, rect_height, dtk_red);
	cnbi::draw::Circle		circle(circle_radius, dtk_green);
	cnbi::draw::CircleStrip	strip(strip_radius, strip_thick, dtk_blue);
	cnbi::draw::Cross	    cross(cross_size, cross_thick, dtk_white);
	cnbi::draw::Arrow	    arrow(arrow_width, arrow_height, dtk_cyan);

	printf("[test_shapes] - Create rectangle (width=%f, height=%f)\n", rect_width, rect_height);
	rectangle.Create();
	
	printf("[test_shapes] - Create circle (radius=%f)\n", circle_radius);
	circle.Create();
	
	printf("[test_shapes] - Create circular strip (radius=%f, thick=%f)\n", strip_radius, strip_thick);
	strip.Create();
	
	printf("[test_shapes] - Create cross (size=%f, thick=%f)\n", cross_size, cross_thick);
	cross.Create();
	
	printf("[test_shapes] - Create arrow (width=%f, height=%f)\n", arrow_width, arrow_height);
	arrow.Create();
	
	printf("[test_shapes] - Add shapes to the engine\n");	
	if(engine.Add("rectangle", &rectangle) == false) 
		fprintf(stderr, "[test_shapes] - Cannot add shape 'rectangle'\n");
	if(engine.Add("circle", &circle) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'circle'\n");
	if(engine.Add("strip", &strip) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'circle'\n");
	if(engine.Add("cross", &cross) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'cross'\n");
	if(engine.Add("arrow", &arrow) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'arrow'\n");

	printf("[test_shapes] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();
    CcTime::Sleep(1000);
	
	printf("[test_shapes] - Raise rectangle:\n");
	engine.Raise("rectangle");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Lower strip to Bottom:\n");
	engine.LowerBottom("strip");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Lower circle:\n");
	engine.Lower("circle");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Raise strip to Top:\n");
	engine.RaiseTop("strip");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Raise cross to Top:\n");
	engine.RaiseTop("cross");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Start movement tests\n");
	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(true) {

		rectangle.RelRotate(1.0f);

		circle.RelMove(0.01f, 0.01f);
		cross.RelRotate(5.0f);
		cross.RelMove(-0.01f, 0.0f);
		arrow.RelRotate(-1.0f);

		if((int)(CcTime::Toc(&tic)/1000) % 2 == 0) {
			strip.Show();
		} else {
			strip.Hide();
		}

		if(CcTime::Toc(&tic) > 5000)
			break;

		CcTime::Sleep(100);
	}
	engine.Dump();

	
	printf("[test_shapes] - Removing 'circle' shape\n");
	engine.Remove("circle");
	engine.Dump();

	printf("[test_shapes] - Quit..\n");

	return 0;

	
}
