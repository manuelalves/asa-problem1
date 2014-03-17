#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// number of people (n)
int n = 0;

// number of shares (p)
int p = 0;

vector<list<int> > SCC;


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
        stack<int> L;   //pilha de nos
        vector<UserNode*> nodesVector;
};



void Tarjan_Visit(int n, Graph g){
    cout << "Tarjan_Visit: no " << n <<  "\n";
    UserNode* node = g.nodesVector[n-1];

    int addVisit = g.visited;

    node->d = addVisit;
    node->low = addVisit;
    g.visited = (addVisit + 1);
    int min = node->low;
    node->visit = 1;

    g.L.push(node->id);

    list<int>::iterator adj;
    for(adj = node->sharedList.begin(); adj!= node->sharedList.end(); adj++){

        int adjNode = *adj;
        UserNode* shareNode = g.nodesVector[adjNode-1];

        cout << "Tarjan_Visit: adj " << adjNode <<  "\n";

    //    list<int>::iterator existPos;
    //    existPos = find(g.L.begin(), g.L.end(), n);           //finds position of element v
    //    if(shareNode->d == -1 || existPos != g.L.end()){

        if(shareNode->d == -1 || shareNode->visit == 1){

            if(shareNode->d == -1){

                cout << "Tarjan_Visit again: shareNode->id  " << shareNode->id <<  "\n";
                Tarjan_Visit(shareNode->id, g);

            }
            if(shareNode->low < min){
                    min = shareNode->low;
            }
        }
    }

    if(min < node->low){
        node->low = min;
        return;

    }

    if(node->d == node->low){
        int v;
        list<int> componentList;

        do{

        //    v = g.L.back();
        //    g.L.pop_back();

        v=g.L.top();
        cout << " POP " << v <<  "\n";


        g.L.pop();

        componentList.push_back(v);


    }while (node->id != v);   // ver se e == ou != AQUIIIIIII

        /////////
        list<int>::iterator ad;
        for(ad = componentList.begin(); ad!= componentList.end(); ++ad){
            //    cout << "componentlist: " << "begin " << *(componentList.begin()) << " end " <<  *(componentList.end()) << " " << *(ad)<<  "\n";
            cout << "componentlist: " << " " << *(ad)<<  "\n";

         }
         /////////

       SCC.push_back(componentList);

        //componentList.clear();

    }

}

//devolve a lista de SCC de um grafo
vector<list<int> > SCC_Tarjan(Graph g){


    for (int node = 0; node < g.p; node++){
        if(g.nodesVector[node]->d == -1){
            Tarjan_Visit(node+1, g);
        }
    }

return SCC;

}



int main(){

    // read first line input
    cin >> n;  //number of users
    cin >> p;  //number of shares

    Graph graph;
    graph.n = n;
    graph.p = p;
    graph.visited = 0;
    graph.nodesVector.reserve(n);

//inicializa cada no do grafo
    for(int i = 0; i < n; i++){

        UserNode* node = new UserNode();

        graph.nodesVector.push_back(node);

        int id_aux = i;

        graph.nodesVector[i]->id = (id_aux + 1);
        graph.nodesVector[i]->d = -1;
        graph.nodesVector[i]->low = -1;
        graph.nodesVector[i]->visit = 0;
    }

//recebe input de nos partilhados com a pessoa
    for (int j = 0; j < p; j++){
            int auxN= 0;
            int auxP = 0;

            cin >> auxN;
            cin >> auxP;

            graph.nodesVector[auxN-1]->sharedList.push_back(auxP);
        }


    /** print all strongly connected components **/

    vector<list<int> > scComponents = SCC_Tarjan(graph);

    cout << "SCC:" << "\n";
    cout << scComponents.size() << "\n";

    int counter = 0;

//IMPRIMIR VALORES DAS LISTAS

    for(int itr = 0; itr < scComponents.size(); itr++){
        cout << "lista: " << itr << " tamanho: " <<  scComponents[itr].size() << "\n";

    list<int>::iterator adj;

    for(adj = scComponents[itr].begin(); adj!= scComponents[itr].end(); adj++){
        cout << " users: " << *(adj)<<  "\n";

 }

 ///////////////////////////


        int counter_aux = 0;
            counter_aux = scComponents[itr].size();
            if(counter_aux > counter){
                counter = counter_aux;
            }
}

        cout << counter << "\n";





//       System.out.println(scComponents);

/*
///IMPRIMIR///
//////////////////////////////////
    for(int a=0;a<n;a++){
       cout <<  "\n";
       cout << "imprimir vector" <<  "\n";
       cout << "posicao vector: " << a <<  "\n";

       cout << "id " << graph.nodesVector[a]->id <<  "\n";
       cout << "d" << graph.nodesVector[a]->d <<  "\n";
       cout << "low " << graph.nodesVector[a]->low <<  "\n";
       cout << "visited " << graph.nodesVector[a]->visited <<  "\n";
       list<int>::iterator adj;

       for(adj = graph.nodesVector[a]->sharedList.begin(); adj!= graph.nodesVector[a]->sharedList.end(); adj++){
               cout << "partilha com: " << *(adj)<<  "\n";

        }

    }

//////////////////////////////////
*/

return 0;

}
