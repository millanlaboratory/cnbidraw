#include "Engine.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Ring.hpp"
#include "Cross.hpp"
#include "Arrow.hpp"


int main(int argc, char** argv) {

	// Definition of shapes' sizes
	float rect_width    = 0.7f;
	float rect_height   = 0.3f;
	float circle_radius = 0.7f;
	float ring_radius   = 0.6f;
	float ring_thick	= 0.05f;
	float cross_size	= 0.2f;
	float cross_thick	= 0.05f;
	float arrow_width	= 0.4f;
	float arrow_height	= 0.3f;

	// Instanciation of the drawing engine
	cnbi::draw::Engine 	engine;

	// Instanciation of the shapes
	cnbi::draw::Rectangle   rectangle(rect_width, rect_height, dtk_red);
	cnbi::draw::Circle		circle(circle_radius, dtk_green);
	cnbi::draw::Ring		ring(ring_radius, ring_thick, dtk_blue);
	cnbi::draw::Cross	    cross(cross_size, cross_thick, dtk_white);
	cnbi::draw::Arrow	    arrow(arrow_width, arrow_height, dtk_cyan);

	// Creation of shapes
	printf("[test_shapes] - Create rectangle (width=%f, height=%f)\n", rect_width, rect_height);
	rectangle.Create();
	
	printf("[test_shapes] - Create circle (radius=%f)\n", circle_radius);
	circle.Create();
	
	printf("[test_shapes] - Create circular ring (radius=%f, thick=%f)\n", ring_radius, ring_thick);
	ring.Create();
	
	printf("[test_shapes] - Create cross (size=%f, thick=%f)\n", cross_size, cross_thick);
	cross.Create();
	
	printf("[test_shapes] - Create arrow (width=%f, height=%f)\n", arrow_width, arrow_height);
	arrow.Create();

	// Adding shapes to the engine with unique ids (names). Check if the shapes
	// are added, otherwise raise an error
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

	// Start the engine and dump the current shapes inside
	printf("[test_shapes] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();
    CcTime::Sleep(1000);
	
	// Demonstration of the position related methods
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
	
	// Demonstration of the movement methods
	printf("[test_shapes] - Start movement tests\n");
	CcTimeValue tic;
	CcTime::Tic(&tic);

	// While the loop is running move/hide/show the shapes.
	// The shapes can be manipolated directly by the instanciated objects.
	while(true) {

		// Rotate the rectangle of 1.0f degree (counter-clockwise)
		rectangle.RelRotate(1.0f);

		// Move the circle of one step in the diagonal direction
		circle.RelMove(0.01f, 0.01f);
		
		// Rotate the cross of 5.0f degrees (counter-clockwise) 
		cross.RelRotate(5.0f);
		
		// Move the cross along x-axis 
		cross.RelMove(-0.01f, 0.0f);
		
		// Rotate the arrow of 1.0f (clockwise)
		arrow.RelRotate(-1.0f);

		// Every 2 seconds show/hide the ring
		if((int)(CcTime::Toc(&tic)/1000) % 2 == 0) {
			ring.Show();
		} else {
			ring.Hide();
		}

		// After 5 seconds, exit from the loop
		if(CcTime::Toc(&tic) > 5000.0f)
			break;

		// Cycle sleep time
		CcTime::Sleep(50.0f);
	}
	engine.Dump();

	// Demonstration of the removing shape
	printf("[test_shapes] - Removing 'circle' shape\n");
	engine.Remove("circle");
	engine.Dump();

	// Quit the executable
	printf("[test_shapes] - Quit..\n");

	return 0;

	
}
