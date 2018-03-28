#include <cmath>

#include "Engine.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Ring.hpp"
#include "Cross.hpp"
#include "Arrow.hpp"
#include "Arc.hpp"


int main(int argc, char** argv) {

	float rect_width, rect_height;
	float circle_radius;
	float ring_radius, ring_thick;
	float cross_size, cross_thick;
	float arrow_width, arrow_height;
	float arc_radius, arc_thick, arc_length;

	rect_width    = 0.7f;
	rect_height   = 0.3f;
	circle_radius = 0.7f;
	ring_radius  = 0.6f;
	ring_thick   = 0.05f;
	cross_size    = 0.2f;
	cross_thick   = 0.05f;
	arrow_width	  = 0.4;
	arrow_height  = 0.3;
	arc_radius    = 0.3f;
	arc_thick	  = 0.05f;
	arc_length    = M_PI/2.0f;

	cnbi::draw::Engine 	engine;

	printf("[test_shapes] - Create rectangle (width=%f, height=%f)\n", rect_width, rect_height);
	cnbi::draw::Rectangle   rectangle(rect_height, rect_width, dtk_red);
	
	printf("[test_shapes] - Create circle (radius=%f)\n", circle_radius);
	cnbi::draw::Circle		circle(circle_radius, dtk_green);
	
	printf("[test_shapes] - Create circular ring (radius=%f, thick=%f)\n", ring_radius, ring_thick);
	cnbi::draw::Ring		ring(ring_radius, ring_thick, dtk_blue);
	
	printf("[test_shapes] - Create cross (size=%f, thick=%f)\n", cross_size, cross_thick);
	cnbi::draw::Cross	    cross(cross_size, cross_thick, dtk_white);
	
	printf("[test_shapes] - Create arrow (width=%f, height=%f)\n", arrow_width, arrow_height);
	cnbi::draw::Arrow	    arrow(arrow_width, arrow_height, dtk_cyan);
	
	printf("[test_shapes] - Create arc (radius=%f, length=%f, thick=%f)\n", arc_radius, arc_length, arc_thick);
	cnbi::draw::Arc			arc(arc_radius, arc_length, arc_thick, dtk_red);

	printf("[test_shapes] - Add shapes to the engine\n");	
	if(engine.Add("rectangle", &rectangle) == false) 
		fprintf(stderr, "[test_shapes] - Cannot add shape 'rectangle'\n");
	if(engine.Add("circle", &circle) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'circle'\n");
	if(engine.Add("ring", &ring) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'ring'\n");
	if(engine.Add("cross", &cross) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'cross'\n");
	if(engine.Add("arrow", &arrow) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'arrow'\n");
	if(engine.Add("arc", &arc) == false)
		fprintf(stderr, "[test_shapes] - Cannot add shape 'arc'\n");

	printf("[test_shapes] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();
    CcTime::Sleep(1000);
	
	printf("[test_shapes] - Raise rectangle:\n");
	engine.Raise("rectangle");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Lower ring to Bottom:\n");
	engine.LowerBottom("ring");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Lower circle:\n");
	engine.Lower("circle");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Raise ring to Top:\n");
	engine.RaiseTop("ring");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Raise cross to Top:\n");
	engine.RaiseTop("cross");
	engine.Dump();
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Set stroke for rectangle:\n");
	rectangle.SetStroke(0.05f, dtk_white);
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Hide stroke for rectangle:\n");
	rectangle.Hide(cnbi::draw::Shape::Stroke);
    CcTime::Sleep(2000);
	
	printf("[test_shapes] - Show stroke for rectangle:\n");
	rectangle.Show(cnbi::draw::Shape::Stroke);
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
		arc.RelRotate(-1.0f);

		if((int)(CcTime::Toc(&tic)/1000) % 2 == 0) {
			ring.Show();
		} else {
			ring.Hide();
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
