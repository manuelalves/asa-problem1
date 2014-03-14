/* g++ -O3 -ansi -Wall asa_project1.cpp -lm */

#include <iostream>

using namespace std;

int main(){
    
    // number of people (n)
    int n = 0;
    
    // number of shares (p)
    int p = 0;
    
    cin >> n;
    cin >> p;
    
    cout << n << " " << p << "\n";
    cout << n << "\n";
    cout << p << "\n";
    
    return 0;
}


/* 
 
 // Writing to a File
 
 #include <fstream>
 ofstream outputFile;
 outputFile.open("output.txt");
 outputFile << n << " " << p << endl;
 outputFile << n << endl;
 outputFile << p << endl;
 outputFile.close();
*/