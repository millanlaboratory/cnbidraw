#include "Engine.hpp"
#include "CircleStrip.hpp"
#include "EventsEngine.hpp"
#include "EventsHandler.hpp"

using namespace std::placeholders;
float mouse_x=0.0f;
float mouse_y=0.0f;
unsigned int mouse_state = 0;

class handler : public cnbi::draw::EventsHandler {
    public:
	void HandleRedraw(void) {
	    printf("Redraw from class method\n");
	}
};

void callback_simple_quit(void) {
    printf("Quit from simple function\n");
};

void callback_simple_mouse(cnbi::draw::EventMouse evt) {
    unsigned int mindim;
    unsigned int minpx_x, maxpx_x, minpx_y, maxpx_y;
    float ratio;
    float wwin, hwin;
    float nx, ny;
    float minrg_x, minrg_y, maxrg_x, maxrg_y;

    wwin = 800;
    hwin = 600;
    ratio = wwin/hwin;
    
    minpx_x = 0;
    maxpx_x = 800;
    minpx_y = 0;
    maxpx_y = 600;

    minrg_x = -1;
    maxrg_x =  1;
    minrg_y = -1;
    maxrg_y =  1;

    if(ratio > 1.0f) {
	minrg_x = minrg_x*ratio;
    	maxrg_x = maxrg_x*ratio;
    } else {
	minrg_y = minrg_y/ratio;
    	maxrg_y = maxrg_y/ratio;
    }

    nx = (maxrg_x-minrg_x)*(evt.x-minpx_x)/(maxpx_x-minpx_x) + minrg_x;
    ny = (maxrg_y-minrg_y)*(evt.y-minpx_y)/(maxpx_y-minpx_y) + minrg_y;

    printf("Mouse position (pixel): x=%d, y=%d\n", evt.x, evt.y);
    printf("Mouse position (coord): x=%f, y=%f\n", nx, ny);

    mouse_x = nx;
    mouse_y = -ny;

    if(evt.state == 1)
	printf("Mouse pressed\n");
    mouse_state = evt.state;

};

int main(int argc, char** argv) {

	cnbi::draw::Engine engine;
	cnbi::draw::EventsEngine events(&engine);
	handler hdl;
	bool showhide = true;

	cnbi::draw::CircleStrip	strip(0.1, 0.05, dtk_blue);
	strip.Create();
	
	events.onQuit   = callback_simple_quit;
	events.onRedraw = std::bind(&handler::HandleRedraw, hdl);
	events.onMouse  = callback_simple_mouse;

	if(engine.Add("strip", &strip) == false)
		fprintf(stderr, "[test_events] - Cannot add shape 'strip'\n");
	
	engine.Open();
	events.Start();

	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(engine.IsRunning() & events.IsRunning()) {
	
	    strip.Move(mouse_x, mouse_y);
	    
	    if(mouse_state == 1)
		showhide = !showhide;	

	    if(showhide == true) {
		strip.Show();
	    } else {
		strip.Hide();
	    }
		
	    CcTime::Sleep(100);
	}

	return 0;
}


