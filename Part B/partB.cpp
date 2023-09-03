///imports
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class HeapBuilder {
private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  //Outputs what the swaps were and if it correctly matches the .a file
  void WriteResponse() const {
    cout << swaps_.size() << "\n"; //should be 99990
    int numCorrectSwaps = 0;
    int counter = 0;
    //read .a file
    std::ifstream file("tests_partB/04.a");
    if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
        if (counter>0)
          //print swap
          cout << swaps_[counter-1].first << " " << swaps_[counter-1].second;
          string result = to_string(swaps_[counter-1].first) + " " + to_string(swaps_[counter-1].second);
          //checks the .a file to see if the swap is correct
          if (result == line.c_str()) {
            cout << " Correct" << endl;
            numCorrectSwaps++; //tracks total # of correct swaps
          }
          else
            cout << " Incorrect" << endl; //brutally tells us when we've done a bad job during testing
        counter++;
    }
    file.close();
      //these #'s should be the same
      cout << endl << "Number of correct swaps: " << numCorrectSwaps;
      cout << endl << "Number of swaps that should be correct: " << swaps_.size() << "\n";
    }
    
  }

  //Reads the input data
  void ReadData() {
    fstream file;
    string word, t, q, filename;
 
    // filename of the file
    filename = "tests_partB/04";
    // opening file
    file.open(filename.c_str());
    // extracting words from the file
    int numWords = 0;
    while (file >> word) //loops by word
    {
      if (numWords>0)
        data_[numWords-1] = stoi(word); //stoi is string-to-int
      else 
        data_.resize(stoi(word)); //gets length of data_ vec
      numWords++;
    }
  }

  // the more effective implementation of GenerateSwaps()
  //that processes the combination of swaps given a series of inputs
  void GenerateSwaps(int i) {  
    int smallest = i;  // Initialize smallest as root
    int l = 2 * i + 1; // left
    int r = 2 * i + 2; // right

    // If left is smaller
    if (l < data_.size() && data_[l] < data_[smallest])
      smallest = l;

    // If right is smaller
    if (r < data_.size() && data_[r] < data_[smallest])
      smallest = r;

    // If smallest is not root
    if (smallest != i) {

      swap(data_[i], data_[smallest]);
      swaps_.push_back(make_pair(i, smallest));

      // Recursively heapify the affected sub-tree
      GenerateSwaps(smallest);
    }
  }

  void buildHeap() {
    // Start Index
    int startIdx = (data_.size() / 2) - 1;

    // Perform reverse level order traversal
    // from last Start Index
    for (int i = startIdx; i >= 0; i--) {
      GenerateSwaps(i);
    }
  }

public:
  void Solve() {
    ReadData();
    buildHeap();
    WriteResponse();
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}