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

    int visited_aux = graph.visited;

    node->d = visited_aux;
    node->low = visited_aux;
    graph.visited = (visited_aux + 1);
    int minn = node->low;
    node->visit = 1;

    graph.L.push_back(node->id);


    list<int>::iterator adj;

    // search the shared nodes of a node
    for(adj = node->sharedList.begin(); adj!= node->sharedList.end(); adj++){
        int adjNode = *adj;
        UserNode* shareNode = graph.nodesVector[adjNode-1];

        if(shareNode->visit == 0){
            Tarjan_Visit(shareNode->id);
        }

        if(shareNode->low < minn){
            minn = shareNode->low;
        }
    }

    if(minn < node-> low){
        node->low = minn;
        return;
    }


    list<int> componentList;
    int v;

    do{
        v=graph.L.back();
        graph.L.pop_back();
        componentList.push_back(v);
        graph.nodesVector[v-1]->low = min(graph.nodesVector[v-1]->low, node->low);
    } while (v != node->id);

    graph.SCC.push_back(componentList);
}


//returns the list with the SCC of a grafo
vector<list<int> > SCC_Tarjan(Graph g){

    for (int node = 0; node < g.p; node++){
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
    graph.visited = 0;
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

    int max_groups = 0;

    int number = 0;


//tamanho do maior grupo maximo de pessoas que partilham informacao
    for(int itr = 0; itr < scComponents.size(); itr++){
        list<int>::iterator adj;

        int max_groups_aux = 0;

            max_groups_aux = scComponents[itr].size();
            if(max_groups_aux > max_groups){
                max_groups = max_groups_aux;
            }
}


    list<int> listNodes;


//numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
    for(int itr = 0; itr < scComponents.size(); itr++){

        list<int>::iterator adj;

        for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){

           int a = *(adj) - 1;

           UserNode *node = graph.nodesVector[a];

           if(node->sharedList.size() > 0){ //have a list with shares

                list<int>::iterator pos;
                pos = find(scComponents[itr].begin(), scComponents[itr].end(), node->id);

                if(*(pos) != 0){        //exists in a group with shares

                    if(node->low == node->d){    //have low=d
                        number++;
                    }
                }
            }
        }
    }


        cout <<"\n";

        cout << "SCC:" << "\n";

//numero de grupos maximos de pessoas que partilham informacao
        cout << scComponents.size() << " ";

//tamanho do maior grupo maximo de pessoas que partilham informacao
        cout << max_groups << " ";

//numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
        cout << number << "\n";


return 0;

}
