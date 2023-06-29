#include <iostream>
#include <vector>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

const vector<double>
input_numbers(size_t count) {
vector<double> result(count);
for (size_t i = 0; i < count; i++) {
cin >> result[i];
}
return result;
}

void
find_minmax(const vector<double>& numbers, double &min, double &max) {
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

void show_histogram_text(vector<size_t>bins){
    for (double x : bins) {
        //if (height < 100) cout << " ";
        //if (height < 10) cout << " ";
        cout << x << " | ";
        for (int i = 0; i < x; i++) cout << "*";
        cout << "\n";
    }
}

int main()
{
    size_t number_count;
cout << "Enter number count: ";
cin >> number_count;

const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_text(bins);

}
