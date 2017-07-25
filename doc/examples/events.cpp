#include "Engine.hpp"
#include "Ring.hpp"
#include "String.hpp"
#include "Events.hpp"

// Placeholders for std::bind function
using namespace std::placeholders;

// Definition of global variables 
float mouse_x = 0.0f;
float mouse_y =	0.0f;
unsigned int mouse_state	= 0;
unsigned int keyboard_esc	= 0;
unsigned int keyboard_space = 0;

// Example of Handler class for the events (in order to show how to bind
// callbacks to class methods.
class Handler {
    public:
		void HandleRedraw(void) {
		    printf("[test_events] - Redraw from class method\n");
		}
		void HandleKeyboard(cnbi::draw::EventKeyboard* evt) {
			unsigned int key, mod;
			evt->GetKey(&key, &mod);
			if(evt->IsPressed(DTKK_ESCAPE)) {
				keyboard_esc = 1;
				printf("[test_events] - User pressed ESCAPE\n");
			} else if(evt->IsPressed(DTKK_SPACE)) {
				// A filter for really-close pressions should be added
				keyboard_space = 1;
				printf("[test_events] - User pressed SPACE\n");
			}
		}
};

// Example of simple function callback
void callback_simple_quit(void) {
    printf("[test_events] - Quit from simple function\n");
};

// Example of simple function callback
void callback_simple_mouse(cnbi::draw::EventMouse* evt) {
	unsigned int px_x, px_y;
	float crd_x, crd_y;
	evt->GetPosition(&px_x, &px_y);
	evt->GetCoordinates(&crd_x, &crd_y);
    printf("[test_events] - Mouse position (pixel): x=%d, y=%d\n", px_x, px_y);
    printf("[test_events] - Mouse position (coord): x=%f, y=%f\n", crd_x, crd_y);

    mouse_x = crd_x;
    mouse_y = crd_y;

    if(evt->IsPressed())
		printf("[test_events] - Mouse pressed\n");
	
	// A filter for really-close pressions should be added
	mouse_state = evt->IsPressed();	
};

int main(int argc, char** argv) {

	// Instanciation of the drawing engine and ethe event engine
	cnbi::draw::Engine engine;
	cnbi::draw::Events events(&engine);

	// Instanciation of the font
	cnbi::draw::Font font("arial:style=bold");

	// Instanciation of the example Handler class
	Handler handler;

	// Instanciation of the mouse-following shape
	cnbi::draw::Ring	ring(0.1f, 0.05f, dtk_blue);

	// Variable definition
	bool showhide	 = true;
	bool changecolor = false;
	const std::string text1 = "Press Esc to quit";
	const std::string text2 = "Press Mouse button to hide/show shape";
	const std::string text3 = "Press space to change shapes color";
	
	// Instanciation of the string shapes
	cnbi::draw::String string1(text1, 0.1f, dtk_white);
	cnbi::draw::String string2(text2, 0.1f, dtk_white);
	cnbi::draw::String string3(text3, 0.1f, dtk_white);

	// Setting the font for the strings
	string1.SetFont(&font);
	string2.SetFont(&font);
	string3.SetFont(&font);

	// Creation of the strings and the ring shape
	string2.Create();
	string1.Create();
	string3.Create();
	ring.Create();

	// Definition of the callback for the event engine. The callback can be
	// defined as follows for raw functions:
	events.onQuit   = callback_simple_quit;
	events.onMouse  = callback_simple_mouse;

	// Or by means the std::bind method for class methods
	events.onRedraw = std::bind(&Handler::HandleRedraw, handler);
	events.onKeyboard = std::bind(&Handler::HandleKeyboard, handler, std::placeholders::_1);

	// Adding shapes to the engine with unique ids (names). Check if the shapes
	// are added, otherwise raise an error
	if(engine.Add("ring", &ring) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'ring'\n");
	if(engine.Add("string2", &string2) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string2'\n");
	if(engine.Add("string1", &string1) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string1'\n");
	if(engine.Add("string3", &string3) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string3'\n");

	// Start the drawing engine and the event engine and dump the current shapes inside
	engine.Dump();
	engine.Open();
	events.Open();
	
	// Move the string at the bottom
	string1.Move(0.0f, -0.4f);
	string2.Move(0.0f, -0.5f);
	string3.Move(0.0f, -0.6f);

	CcTimeValue tic;
	CcTime::Tic(&tic);
	// While the loop is running move/hide/show the shapes according to the
	// mouse position/click
	while(engine.IsRunning() & events.IsRunning()) {

		// Move the ring according to the current mouse position
	    ring.Move(mouse_x, mouse_y);
	    
	    if(mouse_state == 1) {
			showhide = !showhide;	
		}
	    
		if(keyboard_space == 1) {
			changecolor = !changecolor;	
			keyboard_space = 0;
		}

		// Show/Hide the ring if the mouse button is pressed
	    if(showhide == true) {
			ring.Show();
	    } else {
			ring.Hide();
	    }

		// Change the color of the ring if SPACE key is pressed
		if(changecolor == true) {
			ring.SetColor(dtk_red);
		} else {
			ring.SetColor(dtk_blue);
		}

		// If ESCAPE key is pressed, exit from the loop
		if(keyboard_esc)
			break;

		// Cycle sleep time
	    CcTime::Sleep(50.0f);
	}

	return 0;
}


