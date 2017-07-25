#include "Engine.hpp"
#include "String.hpp"
#include "Font.hpp"


int main(int argc, char** argv) {

	// Definition of strings' sizes
	float string_size = 0.1f;
	bool passed = false;
	
	// Definition of string text
	const std::string text1   = "This is a test string..";
	const std::string text2   = "This is another test string..";
	const std::string text3   = "This is test string aligned right-bottom..";
	
	// Instanciation of the required fonts
	cnbi::draw::Font font1("arial:style=bold");
	cnbi::draw::Font font2("arial:style=italic");
	cnbi::draw::Font font3("arial:style");
	cnbi::draw::Font font4("arial:style=italic bold");
	
	// Instanciation of the drawing engine
	cnbi::draw::Engine engine;

	// Instanciation of the strings
	cnbi::draw::String string1(text1, string_size, dtk_green);
	cnbi::draw::String string2(text2, string_size, dtk_red);
	cnbi::draw::String string3(text3, string_size, dtk_blue);

	// Important! The string must be linked to the desired font.
	// In this case, if the string cannot be linked, an error is raised and the
	// executable exits.
	if(string1.SetFont(&font1) == false) {
		fprintf(stderr, "[test_strings] - Cannot set font1\n");
		return EXIT_FAILURE;
	}
	
	if(string2.SetFont(&font2) == false) {
		fprintf(stderr, "[test_strings] - Cannot set font2\n");
		return EXIT_FAILURE;
	}

	if(string3.SetFont(&font3) == false) {
		fprintf(stderr, "[test_strings] - Cannot set font3\n");
		return EXIT_FAILURE;
	}

	// Creation of strings
	printf("[test_strings] - Create string1 (size=%f)\n", string_size);
	string1.Create();
	
	printf("[test_strings] - Create string2 (size=%f)\n", string_size);
	string2.Create();
	
	printf("[test_strings] - Create string3 (size=%f)\n", string_size);
	string3.Create();
	
	// Adding strings to the engine with unique ids (names). Check if the
	// strings are added, otherwise raise an error
	printf("[test_strings] - Add strings to the engine\n");	
	if(engine.Add("string1", &string1) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string1'\n");
	if(engine.Add("string2", &string2) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string2'\n");
	if(engine.Add("string3", &string3) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string3'\n");

	// Start the engine and dump the current shapes inside
	printf("[test_strings] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();
	CcTime::Sleep(1000);

	// Demonstration of the string methods
	printf("[test_strings] - Start string tests:\n");
	printf("[test_strings] - Move 'string1' and 'string2' to the corners\n");
	string1.Move(-0.8f, 0.5f);
	string2.Move(0.8f, 0.5f);
	CcTime::Sleep(1000);

	printf("[test_strings] - Align 'string3' right-bottom\n");
	string3.SetAlign(cnbi::draw::String::ToBottom|cnbi::draw::String::ToRight);
	CcTime::Sleep(1000);

	CcTimeValue tic;
	CcTime::Tic(&tic);

	// While the loop is running move/hide/show the shapes.
	// The shapes can be manipolated directly by the instanciated objects.
	while(true) {
		
		// Rotate string1 of 1.0f degree (counter-clockwise)
		string1.RelRotate(1.0f);
		
		// Rotate string2 of 1.0f degree (clockwise)
		string2.RelRotate(-1.0f);
		
		// Move string3 along y-axis
		string3.RelMove(0.0f, -0.01f);

		// After 3.5 seconds, change the font for string3
		if(CcTime::Toc(&tic) > 3500.0f & passed == false) {
			printf("[test_strings] - Change format to bold-italic and size to 0.05\n");
			string3.SetFont(&font4);
			string3.SetSize(0.05f);
			passed = true;
		}

		// After 5 seconds, exit from the loop
		if(CcTime::Toc(&tic) > 5000.0f)
			break;
		
		// Cycle sleep time
		CcTime::Sleep(50.0f);
	}
	CcTime::Sleep(1000);
	engine.Dump();

	// Quit the executable
	printf("[test_strings] - Quit..\n");

	return 0;
}


