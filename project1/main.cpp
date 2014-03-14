#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(){

    // number of people (n)
    int n = 0;

    // number of shares (p)
    int p = 0;

    // share list
    list<int> shareList;

    // users vector
    vector<list<int> > userVector;

    // read first line input
    cin >> n;
    cin >> p;

    // initialize users vector
    for(int i = 0; i < n; i++){
        userVector.push_back(shareList);
    }

    // insert shares on users vector
    for (int j = 0; j < p; j++){
        int auxN= 0;
        int auxP = 0;

        cin >> auxN;
        cin >> auxP;

        userVector[auxN-1].push_back(auxP);
    }



    // test print
    /*for (int z = 0; z < n; z++){
        list<int> test = userVector[z];
        list<int>::const_iterator pos;

        for(pos=test.begin(); pos != test.end(); ++pos){
            cout << z + 1 << ' ' << *pos << ' ';
        }
        cout << "\n";
    }*/


    // write output
    /*cout << n << " " << p << "\n";
    cout << n << "\n";
    cout << p << "\n"; */
    

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
