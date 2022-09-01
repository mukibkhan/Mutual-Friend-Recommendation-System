#include<bits/stdc++.h>
using namespace std;
 
const int INF = 1000000000;

struct Person {     // defining a class person which contains all the characteristics etails of any id
    string name; 
    string attribute[3];
    vector<string> friends;
    Person(vector<string>); 
};
 



class CSVReader {
    string fileName;
    char delimeter;
public:
    CSVReader(string filename, char delim = ',') {
        fileName = filename;
        delimeter = delim;
    }

    vector<Person> getData();
};
 

Person::Person(vector<string> vec = {"","","",""}) {
    name = vec[0];
    attribute[0] = vec[1];
    attribute[1] = vec[2];
    attribute[2] = vec[3];
    for(int i = 4; i < vec.size(); i++) {
        friends.push_back(vec[i]);
    }
}
 
vector<Person> CSVReader::getData() {  // all details of csv files are stored in datalist
    ifstream file(fileName);
    string line = "";
    vector<Person> dataList;
    while(getline(file,line)) {
        vector<string> vec;
        string token = "";
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == delimeter) {
                vec.push_back(token);
                token = "";
            }
            else token += line[i];
        }
        vec.push_back(token);
        Person temp(vec); 
        dataList.push_back(temp);
    }
    file.close();
    return dataList;
}

void dijkstra(int s, vector<int> & d,vector<int>adj[],int n ) {
    
    d.assign(n, INF);

    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge;
            

            if (d[v] + 1 < d[to]) {
                d[to] = d[v] + 1;
            
            }
        }
    }
}




int main() {


    CSVReader reader("example.csv");
    vector<Person> dataList = reader.getData();
    int V = dataList.size(); // number of vertices
    map<string,int> nameMapId;
    map<int, Person> idMapPerson; 
    int id = 1;
    for(int i = 0; i < V; i++) {
        nameMapId[dataList[i].name] = id;     // giving id to each name so we will word here with id instead of name
        idMapPerson[id] = dataList[i];        // creating the reference between id and name so we can switch to anyone on need
        id++;
    }
    vector<int> adj[V+1]; // adjacency list    
    for(int i = 0; i < V; i++) {
        for(auto x : dataList[i].friends)
            adj[i+1].push_back(nameMapId[x]);
    }
 
    //** Uncomment the following 20 lines to see how the data is being represented **
     for(int i = 0; i < dataList.size(); i++) {
        cout << dataList[i].name << " ";
         for(int j = 0; j < 3; j++) cout << dataList[i].attribute[j] << " ";
         for(int j = 0; j < dataList[i].friends.size(); j++) cout << dataList[i].friends[j] << " ";
         cout << endl;   
     }
     cout << endl;
 
     for(auto i : nameMapId) {
         cout << i.first << " " << i.second << endl;
     }
    // cout << endl;
 
     for(int i = 1; i <= V; i++) {
         cout << i << ": ";
         for(auto x : adj[i]) {
             cout << x << " ";
         }
         cout << endl;
     }
 
    // WRITE YOUR LOGIC FROM BELOW
    // taking input from user whose mutual want to know
    cout<<"whose mutual u want to find"<<endl;
    string req_name;
    cin>>req_name;

     int id_name;

     id_name=nameMapId[req_name]

    // cout<<req_name<<endl;
     //cout<<id_name;
    // cout<<4;
    
    vector<int>dist(V);
    vector<int>mutuals;
    dijkstra(id_name,dist,adj,V);   // calculation the distace of al friends from source

    for(int i=1;i<=V;i++)
    {
        cout<<dist[i]<<" ";
        if(dist[i]==2 )
        {
             mutuals.push_back(i);
             
        }
    }
    int mx=INT_MIN;
    vector<int>final_list;


    for(int i=0;i<mutuals.size();i++)             // calcuating the weigh between two edges 
    {
        int weight=0;
        if(dataList[mutuals[i]-1].attribute[0]==dataList[id_name-1].attribute[0])
        {
            weight++;
        }
        if(dataList[mutuals[i]-1].attribute[1]==dataList[id_name-1].attribute[1])
        {
            weight++;
        }
        if(dataList[mutuals[i]-1].attribute[2]==dataList[id_name-1].attribute[2])
        {
            weight++;
        }

        if(weight>=mx)
        {
            mx=weight;
            final_list.push_back(mutuals[i]-1);
        }

    }


    cout<<"suggested friend are:"<<endl;
    for(int i=0;i<final_list.size();i++)
    {
        cout<<dataList[final_list[i]].name<<" ";      // all most weighted edges which two edge away are recomended for that particular id
    }

 
    return 0; 
}
