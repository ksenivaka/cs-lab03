#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;

const vector<double> input_numbers_from_file(string filePath, int &bin_count) { 
    ifstream file;
    file.open(filePath, ios::in);
    size_t count;
    file >> count;
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
       file >> result[i];
    }
    file >> bin_count;
    file.close();
    return result;
}

void find_minmax(const vector<double>& numbers, double &min, double &max) {
min = numbers[0];
max = min;
for (int i = 1; i < numbers.size(); i++) {
    if (numbers[i] < min) min = numbers[i];
    if (numbers[i] > max) max = numbers[i];
}
}

vector <size_t> make_histogram(vector<double>numbers,int bin_count) {
vector<size_t> bins(bin_count);
double min, max;
find_minmax(numbers, min, max);
double bin_size = (max - min) / bin_count;
    size_t max_count = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
                if (bins[j] > max_count) max_count = bins[j];
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
            if (bins[bin_count-1] > max_count) max_count = bins[bin_count-1];
        }
    }
    return bins;
}

string svg_begin(double width, double height) {
    string svg = "<?xml version='1.0' encoding='UTF-8'?>\n";
svg.append("<svg " + "width='" + width + "' " +
 "height='" + height + "' " + "viewBox='0 0 " + width + " " + height + "' " 
 + "xmlns='http://www.w3.org/2000/svg'>\n");
return svg;
}

string svg_end() {
    string svg = "</svg>\n";
    return svg;
}

string svg_rect(double x, double y, double width, double height){
    string rect = "<rect x='" + x + "' y='" + y + 
        "' width='" + width + "' height='" + height +
        "' stroke='red' fill='#ffeeee'/>";
    return rect;
}

string svg_text(double left, double baseline, string text) {
    string text =  "<text x='" + left + "' " +
        baseline + "='35'>" + text + "</text>";
    return text;
}

void show_histogram_svg(const vector<size_t>& bins, string filePath) {
    ofstream svg_output;
    svg_output.open(filePath, ios::out | ios::trunc);
    svg_output << svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_output << svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_output << svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_output << svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_output << svg_end();
    svg_output.close();
}

int main()
{
    string fp;
    cout << "Enter input file path: ";
    cin >> fp;
    size_t bin_count;

    const auto numbers = input_numbers_from_file(fp, bin_count);

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins);

}
