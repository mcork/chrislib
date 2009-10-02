//#include <QApplication>
#include <QtGui/qcursor.h>

#ifdef __APPLE__
#include <OpenCV/cv.h>
#include <OpenCV/cvaux.h>
#include <OpenCV/highgui.h>
#include <ApplicationServices/ApplicationServices.h>
// Threads
#define THREAD_RETURN_TYPE void*
#define SLEEP(x) usleep(x*1000)
#endif

#if defined(WIN32) || defined(WIN64) 
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <windows.h>
#include <process.h>
// Threads
#define THREAD_RETURN_TYPE void
#define SLEEP(x) Sleep(x)
#endif

#ifdef LINUX
#include <SDL.h>
#include <X11/extensions/XTest.h>
#include <sys/time.h>
#include <unistd.h>	
#include <assert.h>	
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <iostream>
#include <sys/time.h>
#include <math.h>

#include "osc.h"





// Se 1 funciona a partir da camera senao a partir do AVI
#define cam 1
// Se 1 modo multi-point senao single point
#define multiPoint 0
#define debug 0
// precache MAX circles for spiral
#define DEEP 5
// One or two CAM
#define camQUANTITY 1
// Background Model Gauss 1 FGD 2
#define bgdMODEL 1
// Projection 1 - Front 0
#define PROJECTION 0




using namespace std;

struct coordinate {
	int x, y;
	float sizeRect;
	int intensity;
};

struct lineBlob {
	int min, max;
	unsigned int blobId;

	bool attached;
};

struct blob {
	//unsigned int blobId;
	coordinate min, max;

	coordinate center;
};




class Algorithms {
public:
	Algorithms();
	~Algorithms();
	Algorithms(int thresholdValue);
	void distance(int max);
	void printCircle(coordinate center, IplImage* frame);
	coordinate processCenter();
	coordinate findCenter(coordinate temp, IplImage* frame);
	void cleanVector();
	void qtMove(int x, int y);
	void screenSize();
	int convertToResolution(int p, int escalaOrigem, int escalaDestino);
	float convertToResolutionF(float p, float escalaOrigem, float escalaDestino);
	vector<coordinate> detectBlobs(IplImage* frame, IplImage* finalFrame);
	coordinate singlePointProcess(IplImage* workFrame);
	coordinate singlePointProcess(IplImage* workFrame, int step);
	coordinate singlePointProcessPTR(IplImage* workFrame);
	coordinate singlePointProcessPTR(IplImage* workFrame, int step);
	coordinate spiral(IplImage* workFrame, int x, int y);
	coordinate spiral2(IplImage* workFrame, int x, int y);
	coordinate smartSinglePointProcess(IplImage* workFrame);
	void reportCoordinate(coordinate temp);
	void initialize(int argc, char *argv[]);
	void cleanVectorResults();
	void startProcessing();
	coordinate Process();
	void interfaceIO();
	void interpreter();
	void verticalFlipON();
	void verticalFlipOFF();
	void blurON();
	void blurOFF();
	void setCapture(int captureFPS, int captureWidth, int captureHeight);
	void showCaptureProperties(CvCapture* cap);
	void setStep(int value);
	void setJumpSpiral(int value);
	void printSpiralDistance();
	void setSpiralDeep(int value);
	void printTime();
	void startCalibrate();
	void setScale();
	coordinate convertToScale(coordinate temp);
	void setAlgorithm(int value);
	void windowIO();
	void setTestCoordinates(int height,int width);
	float returnMetricValue(IplImage * frame);



	//Threads
	static THREAD_RETURN_TYPE _processVideo(void*);
	static THREAD_RETURN_TYPE _processIO(void*);
	static THREAD_RETURN_TYPE _windowIO(void * obj);


#ifdef __APPLE__
	void postMouseEventApple(int x, int y, int width, int height, int click);
	void postMouseEventApple(int x, int y, int click);

#endif
	
#ifdef LINUX
	void postMouseEventLinux(int x, int y, int click);
#endif
	
#if defined(WIN32) || defined(WIN64) 
	void postMouseEventwindows(int x, int y, int click);
#endif

	CvCapture *capture, *capture2;
	int xCenter, yCenter, xDelta, yDelta, step, scaleX, scaleY;
	vector<int> xValues;
	vector<int> yValues;
	vector<coordinate> vDistance;
	int threshold, choice;
	vector<coordinate> results;
	coordinate lastPoint, presentPoint, tryPoint;
	bool wantToClic, keyPress;

	int imgWidth, imgHeight, aproximation;
	bool flipVertical, Blur;
	CvBGStatModel* bg_model;
	int captureFPS, captureHeight, captureWidth;
	int jumpValue;
	int deep;
	int spiralTentatives, spiralSuceeded;
	coordinate references[4], projection[4];

	int countRightClic;
	bool rightClic;
	
	// Resolução usada no seu portatil
	int screenWidth;
	int screenHeight;

	// IO
	bool circle, report, move, calibrate, difer, haveCalibrate, restartBackground, Quit, haveCalibrateScreen,adpatativeBackground;
	int keyPressValue;
	// Scale
	CvPoint2D32f srcQuad[4], dstQuad[4];
	CvMat * mat_trf;


	// Test Value to restart Background
	float metricValue,tempMetricValue;
	vector<float> vectorMetricValue;
	// Coordinates to test
	vector<long> testingCoordinates;
	
	//TUIO ID BLOB
	OSCApp app;
	int blobID;
	
	//Frame for metric
	IplImage* workingMetricFrame;

#if defined(WIN32) || defined(WIN64) 
	HANDLE hThread;
#else
	pthread_t hThread;
	pthread_t ioThread;

#endif

};
