#include "Engine.hpp"
#include "Image.hpp"


int main(int argc, char** argv) {

	// Definition of images' sizes and filename
	float image1_width	= 1.0f;
	float image1_height	= 0.43f;
	float image2_width	= 1.0f;
	float image2_height = 0.43;
	const std::string filename1 = "./image1.png";
	const std::string filename2 = "./image2.png";
	const std::string filename3 = "./image3.png";

	// Instanciation of the drawing engine
	cnbi::draw::Engine 	engine;
	
	// Instanciation of the image shape
	cnbi::draw::Image image1(image1_width, image1_height);
	cnbi::draw::Image image2(image2_width, image2_height);

	// Important! The raw image must be loaded into the shape.
	// In this case, if the image cannot be loaded, an error is raised and the
	// executable exits.
	if(image1.Set(filename1) == false) {
		fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename1.c_str());
		return EXIT_FAILURE;
	}
	
	if(image2.Set(filename2) == false) {
		fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename2.c_str());
		return EXIT_FAILURE;
	}

	// Creation of image shapes
	printf("[test_images] - Create image1 (width=%f, height=%f)\n", image1_width, image1_height);
	image1.Create();
	
	printf("[test_images] - Create image2 (width=%f, height=%f)\n", image2_width, image2_height);
	image2.Create();

	// Adding shapes to the engine with unique ids (names). Check if the shapes
	// are added, otherwise raise an error
	printf("[test_images] - Add images to the engine\n");	
	if(engine.Add("image1", &image1) == false) 
		fprintf(stderr, "[test_images] - Cannot add image 'image1'\n");
	if(engine.Add("image2", &image2) == false) 
		fprintf(stderr, "[test_images] - Cannot add image 'image2'\n");
	
	// Start the engine and dump the current shapes inside
	printf("[test_images] - Start the engine and dumping:\n");
	engine.Dump();
	engine.Open();

	// Demonstration of the movement methods
	printf("[test_images] - Start image tests\n");
	CcTimeValue tic;
	CcTime::Tic(&tic);
	
	// While the loop is running move/hide/show the shapes.
	// The shapes can be manipolated directly by the instanciated objects.
	while(true) {
	
		// Rotate image1 of 1.0f degree (counter-clockwise)
		image1.RelRotate(1.0f);
		
		// Move image1 of one step in the diagonal direction
		image1.RelMove(-0.01f, 0.01f);
		
		// Rotate image2 of 1.0f degree (clockwise)
		image2.RelRotate(-1.0f);
		
		// Move image2 of one step in the diagonal direction
		image2.RelMove(0.01f, -0.01f);

		// After 3.5 seconds, change the image2
		if(CcTime::Toc(&tic) > 3500.0f) {
			if(image2.Set(filename3) == false) {
				fprintf(stderr, "[test_images] - Cannot load the image: %s\n", filename1.c_str());
				return EXIT_FAILURE;
			}
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
	printf("[test_images] - Quit..\n");

	return 0;
}


