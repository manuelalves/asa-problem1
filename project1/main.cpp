#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>
#include <stdio.h>

using namespace std;

class UserNode{
      public:
          int id;
          int d;
          int low;
          bool L_exist;
          int visit;
          list<int> sharedList;
};

class Graph{
    public:
        int V;
        int E;
        int visited;
        stack<int> L;
        vector<list<int> > SCC;
        vector<UserNode*> nodesVector;
};

void Tarjan_Visit(int no, Graph* g){

    UserNode* node = g->nodesVector[no-1];

    node->d = g->visited;
    node->low = g->visited;

    g->visited = (g->visited + 1);

    (g->L).push(node->id);

    node->L_exist = true;

    list<int>::iterator adj;

    // search the shared nodes of a node
    for(adj = node->sharedList.begin(); adj!= node->sharedList.end(); adj++){

        int adjNode = *(adj);

        UserNode* shareNode = g->nodesVector[adjNode-1];

        if(shareNode->d == -1){
            Tarjan_Visit(shareNode->id, g);
            node->low = min(shareNode->low, node->low);
        }
        else{
            if(shareNode->L_exist == true){
                node->low = min(node->low, shareNode->d);
            }
        }
    }

    if(node->low == node->d){

        list<int> componentList;
        int w;

        do{
            w = (g->L).top();

            (g->L).pop();

            UserNode* w_Node = g->nodesVector[w-1];

            w_Node->L_exist = false;

            componentList.push_back(w);

        }while(w != node->id);

        g->SCC.push_back(componentList);
    }
}


//returns the list with the SCC of a grafo
vector<list<int> > SCC_Tarjan(Graph* g){

    if(!(g->L).empty()){
        (g->L).pop();
    }

    g->visited = 0;

    for (int node = 0; node < g->V; node++){
        if(g->nodesVector[node]->d == -1){
                Tarjan_Visit(node+1, g);
        }
    }
    return g->SCC;
}


int main(){

    int n=0;
    int p=0;
    int number=0;

    // read first line input
    scanf ("%d %d",&n,&p);

    Graph* graph = new Graph();

    graph->V = n;
    graph->E = p;
    graph->nodesVector.reserve(n);

    // initialize each node of the graph
    for(int i = 0; i < graph->V; i++){

        UserNode* node = new UserNode();

        graph->nodesVector.push_back(node);

        int id_aux = i;

        graph->nodesVector[i]->id = (id_aux + 1);
        graph->nodesVector[i]->d = -1;
        graph->nodesVector[i]->low = -1;
    }

    for (int j = 0; j < graph->E; j++){

        int user= 0;
        int share = 0;

        scanf ("%d %d",&user, &share);
        graph->nodesVector[user-1]->sharedList.push_back(share);
    }

    vector<list<int> > scComponents = SCC_Tarjan(graph);

    //tamanho do maior grupo maximo de pessoas que partilham informacao
    int max_groups = 0;

        for(unsigned int itr = 0; itr < scComponents.size(); itr++){
            list<int>::iterator adj;

            int max_groups_aux = 0;

                max_groups_aux = scComponents[itr].size();
                if(max_groups_aux > max_groups){
                    max_groups = max_groups_aux;
                }
    }


    //numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
    for(unsigned int itr = 0; itr < scComponents.size(); itr++){

        list<int>::iterator adj;

        int sizee = scComponents[itr].size();

        if(scComponents.size() == 1){
            number ++;
        }else{

            if(sizee == 1){
                int a = scComponents[itr].front();

                UserNode *node = graph->nodesVector[a - 1];

                if(node->sharedList.size() == 0){ //have a list with private shares
                    number++;
                }else{
                    if(node->sharedList.front() == node->id){
                        number++;
                    }
                }
            }else{
                int counter_aux = 0;
                for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){
                        int k = *(adj) - 1;
                        UserNode *node = graph->nodesVector[k];

                        counter_aux = counter_aux + node->sharedList.size();
                }

                if(counter_aux == sizee){
                    number++;

                }
            }
        }
    }

    //OUTPUT
    //numero de grupos maximos de pessoas que partilham informacao
    cout << scComponents.size() << "\n";

    //tamanho do maior grupo maximo de pessoas que partilham informacao
    cout << max_groups << "\n";

    //numero de grupos maximos de pessoas que partilham informacao apenas dentro do grupo
    cout << number << "\n";
}
