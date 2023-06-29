#include <iostream>
#include <vector>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

const auto
input_numbers(size_t count) {
vector<double> result(count);
for (size_t i = 0; i < count; i++) {
cin >> result[i];
}
return result;
}

void
find_minmax(vector<double> numbers, double &min, double &max) {
min = numbers[0];
max = min;
for (int i = 1; i < numbers.size(); i++) {
    if (numbers[i] < min) min = numbers[i];
    if (numbers[i] > max) max = numbers[i];
}
}

int main()
{
    size_t number_count;
cout << "Enter number count: ";
cin >> number_count;

vector<double> numbers = input_numbers(number_count);

    double min, max;
    find_minmax(numbers, min, max);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    vector<size_t> bins(bin_count);
    double bin_size = (max - min) / bin_count;
    size_t max_count = 0;
    for (size_t i = 0; i < number_count; i++) {
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
    for (double count : bins) {
        size_t height = MAX_ASTERISK * (static_cast<double>(count) / max_count);
        if (height < 100) cout << " ";
        if (height < 10) cout << " ";
        cout << height << " | ";
        for (int i = 0; i < height; i++) cout << "*";
        cout << "\n";
    }
}
