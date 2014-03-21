/*

Grupo 108

70179 - Manuel Alves     [manuelalves@tecnico.ulisboa.pt]
70298 - Jessica Ribeiro  [jessica.ribeiro@tecnico.ulisboa.pt]

*/

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
          list<int> sharedList;                                                 // List with the shared nodes
};

class Graph{
    public:
        int V;
        int E;
        int visited;
        stack<int> L;
        vector<list<int> > SCC;                                                 // SCC list of strongly connected components
        vector<UserNode*> nodesVector;                                          // Vector that contais the graph nodes
};


// Tarjan Algorithm with DFS in each node of graph
void Tarjan_Visit(int no, Graph* g){

    UserNode* node = g->nodesVector[no-1];                                      //gets the node in the nodesVector of graph

    node->d = g->visited;
    node->low = g->visited;

    g->visited = (g->visited + 1);

    (g->L).push(node->id);                                                      // add node to stack L

    node->L_exist = true;                                                       // node exists in the stack L

    list<int>::iterator adj;


    for(adj = node->sharedList.begin(); adj!= node->sharedList.end(); adj++){   // search the shared nodes of a node

        int adjNode = *(adj);

        UserNode* shareNode = g->nodesVector[adjNode-1];                        // gets the shared node

        if(shareNode->d == -1){                                                 // if the node was not visited yet
            Tarjan_Visit(shareNode->id, g);                                     // runs Tarjan algorithm on shared node
            node->low = min(shareNode->low, node->low);                         // modify parents low to the minimun value
        }
        else{                                                                   // the node was already been visited
            if(shareNode->L_exist == true){                                     // if the shared node is still in the stack L
                node->low = min(node->low, shareNode->d);                       // modify parents low to the minimun value
            }
        }
    }

    if(node->low == node->d){                                                   // if we are in the root of the component

        list<int> componentList;                                                // list of nodes contained in the component
        int w;

        do{
            w = (g->L).top();                                                   // saves the first node of stack L
            (g->L).pop();                                                       // pop node from stack L

            UserNode* w_Node = g->nodesVector[w-1];                             // gets the node from nodesVector of graph

            w_Node->L_exist = false;                                            // node does not exist in the stack L

            componentList.push_back(w);                                         // add node to the component

        }while(w != node->id);                                                  // while we are not in the root

        g->SCC.push_back(componentList);                                        // add the compoennt to the SCC list
    }
}


//returns the list with the SCC of a graph
vector<list<int> > SCC_Tarjan(Graph* g){

    if(!(g->L).empty()){                                                        // empty stack L
        (g->L).pop();
    }

    g->visited = 0;                                                             // number of nodes already visited in the graph

    for (int node = 0; node < g->V; node++){                                    // for each node in the graph
        if(g->nodesVector[node]->d == -1){                                      // if was not visited yet (is undifined)
                Tarjan_Visit(node+1, g);                                        // apply Tarjan Algorithm to the node
        }
    }
    return g->SCC;                                                              // returns list of strongly connected components
}


int main(){

    int n=0;
    int p=0;
    int number=0;

    // read first line input
    scanf ("%d %d",&n,&p);                                                      // gets the number of Vertices and Edges of graph from iput

    Graph* graph = new Graph();                                                 // creates a new graph

    graph->V = n;                                                               // sets number of vertices of graph
    graph->E = p;                                                               // sets number of edges of graph
    graph->nodesVector.reserve(n);                                              // allocates a vector with number of vertices (number of nodes)

    for(int i = 0; i < graph->V; i++){                                          // initialize each node of the graph

        UserNode* node = new UserNode();                                        // creates a new node

        graph->nodesVector.push_back(node);                                     // add node to the nodesVector of graph

        int id_aux = i;

        graph->nodesVector[i]->id = (id_aux + 1);                               // sets the id of node
        graph->nodesVector[i]->d = -1;                                          // sets the d of node
        graph->nodesVector[i]->low = -1;                                        // sets the low of node
    }

    for (int j = 0; j < graph->E; j++){                                         // for each number of edges

        int user= 0;
        int share = 0;

        scanf ("%d %d",&user, &share);                                          // gets the node and the shared_node
        graph->nodesVector[user-1]->sharedList.push_back(share);                //adds shared_node to the sharedList of the node
    }

    vector<list<int> > scComponents = SCC_Tarjan(graph);                        // aplly Tarjan Algorithm to the given graph

    // [2 - Maximum size of the largest group of people who share informa]
    int max_groups = 0;

    for(unsigned int itr = 0; itr < scComponents.size(); itr++){            // iterates the SSC vector
        list<int>::iterator adj;

        int max_groups_aux = 0;

        max_groups_aux = scComponents[itr].size();                      // actualize max_group number to the biggest one finded
        if(max_groups_aux > max_groups){
            max_groups = max_groups_aux;
        }
    }


    // [3 - Maximum number of groups of people who share information only within the group]
    for(unsigned int itr = 0; itr < scComponents.size(); itr++){                // iterates the SSC vector

        list<int>::iterator adj;

        int sizee = scComponents[itr].size();

        if(scComponents.size() == 1){                                           // if the SCC component has only one node
            number++;                                                           // increments number and finish the for loop
        }else{

            if(sizee == 1){                                                     // test if the list inside the vector scComponents has only one node
                int a = scComponents[itr].front();

                UserNode *node = graph->nodesVector[a - 1];

                if(node->sharedList.size() == 0){                               // have a list with private shares
                    number++;
                }else{

                    // test if the node in the SCC vector is equals to the node in the list with private shares
                    if(node->sharedList.front() == node->id){
                        number++;
                    }
                }
            }else{
                int counter_aux = 0;

                // for each node in SCC list gets the size of nodesshare list of actual node
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
    // [1 - Maximum number of groups of people who share information]
    cout << scComponents.size() << "\n";

    // [2 - Maximum size of the largest group of people who share informa]
    cout << max_groups << "\n";

    // [3 - Maximum number of groups of people who share information only within the group]
    cout << number << "\n";
}
