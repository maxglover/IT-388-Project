#include "ImageMatch.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc != 3){
        cout << "Correct usage: ./project <input_file> <template_file>\n";
		exit(1);
    }

    string fileName = argv[1];
	string templateName = argv[2];

    vector<vector<int>> series;
    vector<vector<int>> temp;

    ImageMatch match;
    match.parseImage(fileName);

    match.parseTemplate(templateName);

    vector<double> arr = match.matchImage();

    cout << "X: " << arr[0] << ", Y: " << arr[1] << ", SAD Value: " << arr[2] << endl;
}
