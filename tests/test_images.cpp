#include "Engine.hpp"
#include "Image.hpp"


int main(int argc, char** argv) {

	float image1_width, image1_height;
	float image2_width, image2_height;
	//const std::string rootpath  = std::string(getenv("srcdir"));
	const std::string filename1 = "./tests/image1.png";
	const std::string filename2 = "./tests/image2.png";
	const std::string filename3 = "./tests/image3.png";

	image1_width = 1.0f;
	image1_height = 0.43f;
	
	image2_width = 1.0f;
	image2_height = 0.43f;

	cnbi::draw::Engine 	engine;
	
	cnbi::draw::Image image1(image1_width, image1_height);
	cnbi::draw::Image image2(image2_width, image2_height);

	if(image1.Set(filename1) == false) {
		fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename1.c_str());
		return EXIT_FAILURE;
	}
	
	if(image2.Set(filename2) == false) {
		fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename2.c_str());
		return EXIT_FAILURE;
	}

	printf("[test_images] - Create image1 (width=%f, height=%f)\n", image1_width, image1_height);
	image1.Create();
	
	printf("[test_images] - Create image2 (width=%f, height=%f)\n", image2_width, image2_height);
	image2.Create();


	printf("[test_images] - Add images to the engine\n");	
	if(engine.Add("image1", &image1) == false) 
		fprintf(stderr, "[test_images] - Cannot add image 'image1'\n");
	if(engine.Add("image2", &image2) == false) 
		fprintf(stderr, "[test_images] - Cannot add image 'image2'\n");
	
	printf("[test_images] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();

	printf("[test_images] - Start image tests\n");
	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(true) {
	
		image1.RelRotate(1.0f);
		image1.RelMove(-0.01f, 0.01f);
		image2.RelRotate(-1.0f);
		image2.RelMove(0.01f, -0.01f);

		if(CcTime::Toc(&tic) > 3500) {
			if(image2.Set(filename3) == false) {
				fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename1.c_str());
				return EXIT_FAILURE;
			}
		}
		
		if(CcTime::Toc(&tic) > 5000)
			break;
		
		CcTime::Sleep(100);
	}
	CcTime::Sleep(1000);
	engine.Dump();

	printf("[test_images] - Quit..\n");

	return 0;
}


