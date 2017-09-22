#include "Engine.hpp"
#include "Events.hpp"
#include "EventKeyboard.hpp"
#include "Gallery.hpp"

#define FOLDER_IMAGES "./"
using namespace cnbi;

bool quit = false;
void callback(cnbi::draw::EventKeyboard* evt) {
	if(evt->IsPressed(DTKK_ESCAPE))
		quit = !quit;
}


int main(int argc, char** argv) {

	cnbi::draw::Engine*		 engine;
	cnbi::draw::Events*		 events;
	cnbi::draw::Gallery*	 gallery;
	std::string				 path(FOLDER_IMAGES);
	std::vector<std::string> allowed_ext = {".jpg", ".png"};

	gallery = new cnbi::draw::Gallery(0.3f, 0.3f);
	engine  = new cnbi::draw::Engine;
	events  = new cnbi::draw::Events(engine);


	if(gallery->SetFolder(path, allowed_ext) == false) {
		printf("[test_gallery] + Cannot access to folder '%s'\n", path.c_str());
		exit(1);
	}

	if(gallery->list.size() == 0) {
		printf("[test_gallery] + No images in the folder: '%s'. Exit.\n", path.c_str());
		exit(1);
	}

	

	printf("[test_gallery] + Found %lu images on folder '%s':\n", gallery->list.size(), path.c_str());
	for(auto it = gallery->list.begin(); it!=gallery->list.end(); ++it) 
		printf("               |- %s\n", (*it).c_str());

	

	engine->Open();
	engine->Add("gallery", gallery);
	
	events->Start();
	events->onKeyboard = callback;


	printf("[test_gallery] - Showing picture at position 3:\n");
	auto pos = gallery->Begin();
	std::advance(pos, 2);
	gallery->Select(pos);
	CcTime::Sleep(1000.0f);

	printf("[test_gallery] - Showing picture at index 2:\n");
	gallery->Select(1);
	CcTime::Sleep(1000.0f);

	printf("[test_gallery] - Going to picture 3:\n");
	auto it = gallery->Begin() + 3;
	gallery->GoTo(it);
	gallery->Select();
	CcTime::Sleep(1000.0f);

	printf("[test_gallery] - Starting picture show from the beginning:\n");
	gallery->GoTo(gallery->Begin());
	while(quit == false) {
		if(gallery->Current() == gallery->End()) 
			gallery->Rewind();
		printf("[test_gallery] - Current picture: %s\n", (*gallery->Current()).c_str());
		gallery->Select();
		gallery->Next();
		CcTime::Sleep(1000.0f);
	}

	delete engine;
	delete events;
	
	return 0;
}


