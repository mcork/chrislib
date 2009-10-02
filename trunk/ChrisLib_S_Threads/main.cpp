#include "Algorithms.h"

using namespace std;

int main(int argc, char *argv[]) {
	// value define threshold
	Algorithms * alg = new Algorithms();

	//alg->setCapture(10, 320, 240);

	alg->jumpValue = 1;
	alg->deep = 8;
	alg->step = 2;

	alg->initialize(argc, argv);

	// vertical flip of capture frame
	alg->verticalFlipON();
	
	//alg->verticalFlipOFF();
	//alg->setStep(5);

	// blur image
	// alg->blurON();

	// 1 - simglePointProcess (use for)
	// 2 - simglePointProcess (use for with step)
	// 3 - simglePointProcessPTR	(use pointer with step)
	// 4 - smartSimglePointProcess (use spiral)
	// 5 - Multipoint
	
	alg->screenWidth=1280;
	alg->screenHeight=800;
	
	//alg->screenWidth=800;
	//alg->screenHeight=600;
	
	//alg->startCalibrate();

	alg->setAlgorithm(5);
	alg->startProcessing();
	
	alg->~Algorithms();

	return -1;
}
