#include "Engine.hpp"
#include "String.hpp"


int main(int argc, char** argv) {

	float string1_size;
	float string2_size;
	float string3_size;
	const std::string format1 = "arial:style=bold";
	const std::string format2 = "arial:style=italic";
	const std::string format3 = "arial:style";
	const std::string text1   = "This is a test string..";
	const std::string text2   = "This is another test string..";
	const std::string text3   = "This is test string aligned right-bottom..";
	bool passed = false;

	string1_size = 0.1f;
	string2_size = 0.1f;
	string3_size = 0.1f;

	cnbi::draw::Engine engine;

	cnbi::draw::String string1(text1, string1_size, dtk_green);
	cnbi::draw::String string2(text2, string2_size, dtk_red);
	cnbi::draw::String string3(text3, string3_size, dtk_blue);

	if(string1.SetFormat(format1) == false) {
		fprintf(stderr, "[test_strings] - Cannot set string format: %s\n", format1.c_str());
		return EXIT_FAILURE;
	}
	
	if(string2.SetFormat(format2) == false) {
		fprintf(stderr, "[test_strings] - Cannot set string format: %s\n", format2.c_str());
		return EXIT_FAILURE;
	}

	if(string3.SetFormat(format3) == false) {
		fprintf(stderr, "[test_strings] - Cannot set string format: %s\n", format3.c_str());
		return EXIT_FAILURE;
	}


	printf("[test_strings] - Create string1 (size=%f)\n", string1_size);
	string1.Create();
	
	printf("[test_strings] - Create string2 (size=%f)\n", string2_size);
	string2.Create();
	
	printf("[test_strings] - Create string3 (size=%f)\n", string3_size);
	string3.Create();
	
	printf("[test_strings] - Add strings to the engine\n");	
	if(engine.Add("string1", &string1) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string1'\n");
	if(engine.Add("string2", &string2) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string2'\n");
	if(engine.Add("string3", &string3) == false) 
		fprintf(stderr, "[test_strings] - Cannot add string 'string3'\n");


	printf("[test_strings] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();
	CcTime::Sleep(1000);

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
	while(true) {
		
		string1.RelRotate(1.0f);
		string2.RelRotate(-1.0f);
		string3.RelMove(0.0f, -0.01f);

		if(CcTime::Toc(&tic) > 3500 & passed == false) {
			printf("[test_strings] - Change format to bold-italic and size to 0.05\n");
			string3.SetFormat("arial:style=bold italic");
			string3.SetSize(0.05);
			passed = true;
		}

		if(CcTime::Toc(&tic) > 5000)
			break;
		
		CcTime::Sleep(100);
	}
	CcTime::Sleep(1000);
	engine.Dump();

	printf("[test_strings] - Quit..\n");

	return 0;
}


