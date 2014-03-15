#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class userNode{
      public:
          int id;
          int d;
          int low;
          int visited;
          list<int> sharedList;
};

// apply Tarjan Algorithm to a node
void Tarjan_Visit(userNode* actual_node, list<int> L, vector<userNode*> user_vector){
      int visited = actual_node->visited;

      actual_node->d = visited;
      actual_node->low = visited;
      actual_node->visited = (visited + 1);

      L.push_back(actual_node->id);


      list<int>::iterator adj;

      //search in the adjacent nodes list of actual node
      for(adj = actual_node->sharedList.begin(); adj!= actual_node->sharedList.end(); ++adj){

            list<int>::iterator pos;
            int shared_node = *adj;

            userNode* v = user_vector[shared_node];  //ver se indices tao bem ou se -1

            pos = find(L.begin(), L.end(), shared_node);           //finds position of element v



           if((v->d == -1) || (pos != L.end())){
               if(v->d == -1){
            //Tarjan_Visit();
              }
          }
      }

}




int main(){

    // number of people (n)
    int n = 0;

    // number of shares (p)
    int p = 0;

    // list of nodes visited (empty)
    list<int> L;

    // users vector
    vector<userNode*> userVector;

    userNode* node = NULL;

    // read first line input
    cin >> n;  //number of users
    cin >> p;  //number of shares



    // initialize users vector
    for(int i = 0; i < n; i++){
        node = new userNode();
        userVector.push_back(node);
    }

    // insert shares on users vector
    for (int j = 0; j < p; j++){
        int auxN= 0;
        int auxP = 0;

        cin >> auxN;
        cin >> auxP;

        userVector[auxN-1]->id = auxN;
        userVector[auxN-1]->d = -1;
        userVector[auxN-1]->low = -1;
        userVector[auxN-1]->visited = 0;
        userVector[auxN-1]->sharedList.push_back(auxP);
    }


    for (int k = 0; k < p; k++){
        if(userVector[k]->d == -1){
            Tarjan_Visit(userVector[k], L, userVector);
        }
    }


    //


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
