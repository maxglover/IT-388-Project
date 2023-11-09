//
// Created by Tim on 10/25/2023.
//

#include "project.h"
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv){
    if(argc<5){
        cout<< "Correct usage: ./project <input_file> <template_file> <type>\n Type: 0 -> Time series\n1 -> Image";
		exit(1);
    }
    Project project;
    string fileName = argv[1];
	string templateName = argv[2];
    int type = atoi(argv[3]);

    //Check for invalid type
    if(type<0 || type>1){
        cout<< "Invalid type, 0 or 1 only";
        exit(1);
    }
    project.setType(type);
    project.inputFile = project.fileInput(fileName);
	project.templateFile = project.fileInput(templateName);

    int N;
    int nproc;
    int rank;
	/*
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &rank);

    MPI_Barrier(comm);
    double start = MPI_Wtime();
    */

	//Time series
    if(project.getType()==0){
		string line;
		//Gets data from data file
		getline(project.inputFile, line);

		double* timeData = project.timeSeriesMatch(line);

		getline(project.inputFile, line);

		double* dataData = project.timeSeriesMatch(line);


		//Gets data from template file
		getline(project.templateFile, line);

		double* timeTemplate = project.timeSeriesMatch(line);

		getline(project.templateFile, line);

		double* dataTemplate = project.timeSeriesMatch(line);
	}

    //Image
    else{
		//Convert both files to grayscale
		Mat imageData = imread(fileName, IMREAD_GRAYSCALE);
		Mat imageTemplate = imread(templateName, IMREAD_GRAYSCALE);

		//Get files as arrays
		std::vector<uchar> imageVec(imageData.rows*imageData.cols*imageData.channels());
		imageVec = imageData.data;

		//Convert to 2d Array
		uchar imageArr[imageData.rows][imageData.cols];
		for(int i=0;i<imageData.rows;i++){
			for(int j=0;j<imageData.cols;j++){
				imageArr[i][j] = imageVec.get(i*j);
			}
		}


		std::vector<uchar> templateVec(imageTemplate.rows*imageTemplate.cols*imageTemplate.channels());
		templateVec = imageTemplate.data;

		//Convert to 2d array
		uchar templateArr[imageTemplate.rows][imageTemplate.cols];

		for(int i=0;i<imageTemplate.rows;i++){
			for(int j=0;j<imageTemplate.cols;j++){
				templateArr[i][j] = templateVec.get(i*j);
			}
		}
    }

    /*
	double end = MPI_Wtime() - start;

    cout<<"Time: "<<fabs(end);

    MPI_Finalize();
    */
	return 0;
}

/**
 * Opens, tests and returns file
 * @param fileName Name of file to open
 * @return Returns file
 */
ofstream Project::fileInput(string fileName){
    file.open(fileName, ofstream::out);
    if(file.fail()){
        cout<< "File cannot be opened";
		exit(2);
    }
	return file;
}



/**
 * Processes a time series input
 * @return Returns 1D array
 */
int Project::timeSeriesMatch(double* input, double* temp){
	int position = -1;
	//Temp max value
	double minSAD = 10000;
	//Loop through input
	for(int i=0;i<=(sizeof(input) / sizeof(double) - sizeof(temp) / sizeof(double));i++){
		double SAD = 0.0;
		//Loop through template
		for(int j=0;j<=sizeof(temp) / sizeof(double);j++){
			SAD += abs(input[i+j] - temp[j]);
		}

		if(minSAD > SAD){
			minSAD = SAD;
			//Stores index start of best matched template (go til length of template)
			position = i;
		}
	}
	cout<<"Best SAD "<<SAD;
	return position;
}

/**
 * Processes an image input
 * @return Returns 2D array
 */
int** Project::imageMatch(int** input, int** temp){


}

/**
 * Parses input file for time series data
 * @param file File input
 * @return Returns 1D of data
 */
double* Project::parseTimeSeries(string line){
	string s;
	double data[1000];
	int count=0;
	while(getline(line, s, ' ')){
		data[count} = s;
		count++;
	}
	return data;
}