#include "Engine.hpp"
#include "CircleStrip.hpp"
#include "String.hpp"
#include "Events.hpp"

using namespace std::placeholders;
float mouse_x = 0.0f;
float mouse_y =	0.0f;
unsigned int mouse_state	= 0;
unsigned int keyboard_esc	= 0;
unsigned int keyboard_space = 0;

class handler {
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
			keyboard_space = 1;
			printf("[test_events] - User pressed SPACE\n");
		}
	}
};

void callback_simple_quit(void) {
    printf("[test_events] - Quit from simple function\n");
};

void callback_simple_mouse(cnbi::draw::EventMouse* evt) {
	unsigned int px_x, px_y;
	float crd_x, crd_y;
	evt->GetPosition(&px_x, &px_y);
	evt->GetCoordinates(&crd_x, &crd_y);
    //printf("[test_events] - Mouse position (pixel): x=%d, y=%d\n", px_x, px_y);
    //printf("[test_events] - Mouse position (coord): x=%f, y=%f\n", crd_x, crd_y);

    mouse_x = crd_x;
    mouse_y = crd_y;

    if(evt->IsPressed())
		printf("[test_events] - Mouse pressed\n");
		
	mouse_state = evt->IsPressed();	
};

int main(int argc, char** argv) {

	cnbi::draw::Engine engine;
	cnbi::draw::Events events(&engine);
	cnbi::draw::Font font("arial:style=bold");
	handler hdl;
	bool showhide	 = true;
	bool changecolor = false;
	const std::string text1 = "Press Esc to quit";
	const std::string text2 = "Press Mouse button to hide/show shape";
	const std::string text3 = "Press space to change shapes color";
	

	cnbi::draw::CircleStrip	strip(0.1f, 0.05f, dtk_blue);

	cnbi::draw::String string1(text1, 0.1f, dtk_white);
	cnbi::draw::String string2(text2, 0.1f, dtk_white);
	cnbi::draw::String string3(text3, 0.1f, dtk_white);

	string1.SetFont(&font);
	string2.SetFont(&font);
	string3.SetFont(&font);
	
	string2.Create();
	string1.Create();
	string3.Create();
	strip.Create();
	
	events.onQuit   = callback_simple_quit;
	events.onRedraw = std::bind(&handler::HandleRedraw, hdl);
	events.onMouse  = callback_simple_mouse;
	events.onKeyboard = std::bind(&handler::HandleKeyboard, hdl, std::placeholders::_1);

	if(engine.Add("strip", &strip) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'strip'\n");
	if(engine.Add("string2", &string2) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string2'\n");
	if(engine.Add("string1", &string1) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string1'\n");
	if(engine.Add("string3", &string3) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'string3'\n");


	engine.Dump();
	engine.Open();
	events.Start();
	
	string1.Move(0.0f, -0.4f);
	string2.Move(0.0f, -0.5f);
	string3.Move(0.0f, -0.6f);

	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(engine.IsRunning() & events.IsRunning()) {
	
	    strip.Move(mouse_x, mouse_y);
	    
	    if(mouse_state == 1) {
			showhide = !showhide;	
		}
	    
		if(keyboard_space == 1) {
			changecolor = !changecolor;	
			keyboard_space = 0;
		}

	    if(showhide == true) {
			strip.Show();
	    } else {
			strip.Hide();
	    }

		if(changecolor == true) {
			strip.SetColor(dtk_red);
		} else {
			strip.SetColor(dtk_blue);
		}

		if(keyboard_esc)
			break;

		
	    CcTime::Sleep(100);
	}

	return 0;
}


