#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

// number of people (n)
int n = 0;

// number of shares (p)
int p = 0;

class UserNode{
      public:
          int id;
          int d;
          int low;
          int visit;
          int low_visited;
          list<int> sharedList;
};

class Graph{
    public:
        int n;
        int p;
        int visited;
        list<int> L;
        vector<list<int> > SCC;
        vector<UserNode*> nodesVector;
}graph;


void Tarjan_Visit(int no){

    UserNode* node = graph.nodesVector[no-1];

    //int visited_aux = graph.visited;


    node->d = graph.visited;
    node->low = graph.visited;
    graph.visited++;
    int minn = node->low;
    node->visit = 1;


    graph.L.push_back(no);


    list<int>::iterator adj;

    // search the shared nodes of a node
    for(adj = node->sharedList.begin(); adj!= node->sharedList.end(); adj++){


        int adjNode = *adj;
        UserNode* shareNode = graph.nodesVector[adjNode-1];


        if(shareNode->visit == 0){

            Tarjan_Visit(shareNode->id);
//node->low = min(node->low, shareNode->low);


        }

        if(shareNode->low < minn){
            minn = shareNode->low;

        }
    }

    if(minn < node->low){

        node->low = minn;

        return;
    }


    list<int> componentList;
    int v;

    list<int>::iterator ad;

    if(node->d == node->low){


    do{

        v=graph.L.back();

        graph.L.pop_back();
        componentList.push_back(v);
        //graph.nodesVector[v-1]->low = min(graph.nodesVector[v-1]->low, node->low);
        graph.nodesVector[v-1]->low = graph.n;




    } while (v != node->id);



    graph.SCC.push_back(componentList);
}

}


//returns the list with the SCC of a grafo
vector<list<int> > SCC_Tarjan(Graph g){

    g.L.clear();
    g.visited = 0;


    for (int node = 0; node < g.n; node++){
        if(g.nodesVector[node]->d == -1){
            if(g.nodesVector[node]->visit == 0){
                Tarjan_Visit(node+1);
            }
        }
    }
return graph.SCC;
}


int main(){

    // read first line input
    cin >> n;  //number of users
    cin >> p;  //number of shares

    Graph g = graph;
    graph.n = n;
    graph.p = p;
    graph.nodesVector.reserve(n);

// initialize each node of the graph
    for(int i = 0; i < n; i++){

        UserNode* node = new UserNode();

        graph.nodesVector.push_back(node);

        int id_aux = i;

        graph.nodesVector[i]->id = (id_aux + 1);
        graph.nodesVector[i]->d = -1;
        graph.nodesVector[i]->low = -1;
        graph.nodesVector[i]->visit = 0;
    }

//receive as input the shared nodes
    for (int j = 0; j < p; j++){
            int auxN= 0;
            int auxP = 0;

            cin >> auxN;
            cin >> auxP;

            graph.nodesVector[auxN-1]->sharedList.push_back(auxP);
        }

    vector<list<int> > scComponents = SCC_Tarjan(graph);


    long max_groups = 0;

    int number = 0;


//IMPRIMIR VALORES DAS LISTAS

    for(int itr = 0; itr < scComponents.size(); itr++){
    //    cout << "lista: " << itr + 1 << " tamanho: " <<  scComponents[itr].size() << "\n";

    list<int>::iterator adj;
    cout << "[ ";

    for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){
        cout << *(adj) << " ";

        int a = *(adj) - 1;

        cout << "d:" << graph.nodesVector[a]->d << " low:" << graph.nodesVector[a]->low << "  |";





 }


 cout << "] " << "\n";
 }

 ///////////////////////////




//tamanho do maior grupo maximo de pessoas que partilham informacao
    for(int itr = 0; itr < scComponents.size(); itr++){
        list<int>::iterator adj;

        long max_groups_aux = 0;

            max_groups_aux = scComponents[itr].size();
            if(max_groups_aux > max_groups){
                max_groups = max_groups_aux;
            }
}


    list<int> listNodes;


//numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
    for(int itr = 0; itr < scComponents.size(); itr++){

        list<int>::iterator adj;

        long sizee = scComponents[itr].size();

        if(sizee == 1){
            int a = scComponents[itr].front();

            UserNode *node = graph.nodesVector[a - 1];

            if(node->sharedList.size() == 0){ //have a list with private shares
                number++;
            }
        }else{
            long counter_aux = 0;
            for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){
                    int k = *(adj) - 1;
                    UserNode *node = graph.nodesVector[k];

                    counter_aux = counter_aux + node->sharedList.size();
            }

            if(counter_aux >= sizee){
                number++;

            }
        }

}

    /*

        for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){

           int a = *(adj) - 1;

           UserNode *node = graph.nodesVector[a];

           if(node->sharedList.size() == 0){ //have a list with private shares
               number++;

           }else{
              int sizee = scComponents[itr].size();
              if(sizee > 1){
                 int counter_aux = 0;
                     for()
              }
           }
        }
    }*/


    

//numero de grupos maximos de pessoas que partilham informacao
        cout << scComponents.size() << "\n";

//tamanho do maior grupo maximo de pessoas que partilham informacao
        cout << max_groups << " ";

//numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
        cout << number << "\n";


return 0;

}