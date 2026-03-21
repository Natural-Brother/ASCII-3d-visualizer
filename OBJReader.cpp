#include <fstream>
#include <string>
#include "graphicsColor/canvas.h"
#include "graphicsColor/ModelsUtils.h"
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

vector<string> split(string str,string del){
    auto pos = str.find(del);
    vector<string> result;
    while (pos != string::npos) {

        result.push_back(str.substr(0, pos));

        str.erase(0, pos + del.length());

        pos = str.find(del);
    }
    result.push_back(str);
    return result;
}

vector<Vector3> readVectors(std::string objFile,string key,int index){
    vector<string> lines = split(objFile,"\n");
    vector<Vector3> vertex;
    vector<string> line = split(lines[index]," ");
    int i = index;
        while(line[0] == key){

            //cout<< i << " vector line: "<< lines[i]<<std::endl;
            Vector3 vec = Vector3(stod(line[1]),stod(line[2]),stod(line[3]));
            //cout << vertex.size() <<"values: " << vec<<  std::endl;
            vertex.push_back(vec);
            i++;
            line = split(lines[i]," ");
    }
    return vertex;
}

vector<int> readFaces(std::string objFile,vector<Vector3> normal,int index){
    vector<string> lines = split(objFile,"\n");
    vector<int> faces;
        for(int i = index; i< lines.size();i++){
           vector<string> line = split(lines[i]," ");
           //cout << i <<" line: "<< lines[i];
        if(line[0] == "f"){
            //cout <<" values: "<< stoi(split(line[1],"//")[0])<< std::endl;
            faces.push_back(stoi(split(line[1],"//")[0]));
            faces.push_back(stoi(split(line[2],"//")[0]));
            faces.push_back(stoi(split(line[3],"//")[0]));
        }else{
            break;
        }
    }
    int l = faces[0];
    for(int i = 0; i<faces.size(); i++){
        l = faces[i] < l ? faces[i] : l;
    }
    for(int i = 0; i<faces.size(); i++){
        faces[i] -= (l-1);
    }
    return faces;
}

vector<int> readFacesNormal(std::string objFile,vector<Vector3> normal,int index){
    vector<string> lines = split(objFile,"\n");
    vector<int> faces;
        for(int i = index; i< lines.size();i++){
           vector<string> line = split(lines[i]," ");
           //cout << i <<" line: "<< lines[i];
        if(line[0] == "f"){
            //cout <<" values: "<< stoi(split(line[1],"//")[0])<< std::endl;
            faces.push_back(stoi(split(line[1],"//")[1]));
            faces.push_back(stoi(split(line[2],"//")[1]));
            faces.push_back(stoi(split(line[3],"//")[1]));
        }else{
            break;
        }
    }

    int l = faces[0];
    for(int i = 0; i<faces.size(); i++){
        l = faces[i] < l ? faces[i] : l;
    }
    for(int i = 0; i<faces.size(); i++){
        faces[i] -= (l-1);
    }
    return faces;
}

struct Solid{
    Model3D model;
    int vectorCount;
    int normalCount;
};



Model3D readObject(std::string objFile,unordered_map<string, Vector3> material,int index){
            vector<string> lines = split(objFile,"\n");
            vector<string> line = split(lines[index]," ");
            Model3D object;
            vector<Vector3> vertex = readVectors(objFile,"v",index+1);
            object.Vertex = new Vector3[vertex.size()];
            std::copy(vertex.begin(), vertex.end(), object.Vertex);
            object.NVertex = vertex.size();
            vector<Vector3> normal = readVectors(objFile,"vn",index+vertex.size()+1);

            int materialIndex = index+vertex.size()+normal.size()+2;
            
            Vector3 actualColor = material[split(lines[materialIndex]," ")[1]];
            
            int faceIndex = materialIndex+1;
            vector<int> faces = readFaces(objFile,normal,faceIndex);

            cout<<" nfaces: "<< faces.size()/3<<std::endl;
            int * arrfaces = new int[faces.size()];
            std::copy(faces.begin(), faces.end(), arrfaces);
            object.NFaces = faces.size()/3;
            object.setFaces(faces.size()/3,arrfaces,actualColor);

            //cout << "COLOR?"<< object.getFace(0).color << endl;
            
            vector<int> facesNormal = readFacesNormal(objFile,normal,faceIndex);
            // fixing the normals
            for(int i = 0; i < object.NFaces; i++){
                object.faces[i].normal = ((normal[facesNormal[i*3]] + normal[facesNormal[i*3+1]] + normal[facesNormal[i*3+2]])/3.0);
            }
            
            
            //cout << "readObject's Model: " << object;
            return object;
}


void readModel(std::string objFile,unordered_map<string, Vector3> material, vector<Model3D>& modelBuffer) {
    vector<string> lines = split(objFile,"\n");
    int i = 0;
    int vertexC = 0;
    
    while(i<lines.size()){
        i++;
        vector<string> line = split(lines[i]," ");
        //cout << lines[i] << endl;
        if(line[0] == "o"){
            std::cout <<"Loading Object: "<< line[1]<< std::endl;
            
            cout<< "pushing to model buffer: \n";
            Model3D object;
            object = readObject(objFile,material,i);
            modelBuffer.push_back(object);
             
            
            //cout << "actual object model buffer: "<< modelBuffer.back()<< endl;
            
            cout <<"Loaded Sucessfully Object: "<< line[1]<< endl;
           
        }
    }
}


int main() 
{ 
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_VIRTUAL_TERMINAL_INPUT);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);


    string name;
    cout << "file name?\n";
    cin >> name;
    cout << name;

    cout<< "Opening Material"<< std::endl;
    std::ifstream file(name + ".mtl");
    unordered_map<string, Vector3> materials;
    std::string mtlstr; 
    string actualmtlName= "";
    while (std::getline(file, mtlstr))
    {
        vector<string> line = split(mtlstr," ");
        cout<< mtlstr<< std::endl;
        if(line[0] == "newmtl"){
        cout<< "initializing a material "<< line.size()<< std::endl;
        actualmtlName = line[1];
        cout<< "new Material: "<<actualmtlName<< std::endl;
        }else if(line[0] == "Kd"){
            Vector3 color = Vector3(stod(line[1]),stod(line[2]),stod(line[3]));
            cout<< "setting the material: "<< color<<  std::endl;
            materials[actualmtlName] = color;
            
        }
    }
    file.close();
    cout<<"end of file"<<std::endl;
    vector<Model3D> modelBuffer;
    
    std::ifstream file2(name + ".obj");
    std::string objfile = "";
    std::string objstr; 
    while (std::getline(file2, objstr))
    {
        objfile += objstr + "\n";
    }
    file2.close();
    readModel(objfile,materials,modelBuffer);
    cout<<"size of buffer : " << modelBuffer.size() << endl;
    /*Model3D Cube = ModelsUtils::returnCube(5);
    modelBuffer.push_back(Cube);*/
    canvas ctx(50,125,0);
    ctx.alph =  " .:-=+*#%@";
    double maxswell = 120.0;
    string answer;
    vector<triangle> faceBuffer;
    //modelBuffer.push_back(ModelsUtils::returnCube(2.5));
    cin >> answer;
    double dist = stod(answer);
    while(true){
    maxswell+=0.1;
    
    for(auto& i : modelBuffer){
        
    ctx.addModel(faceBuffer,i.rotatedModel(Vector3(0,-1,0).unit(),maxswell).offset(Vector3(0,0.0,dist)));
        //cout << i<< std::endl;
        Sleep(2);
    }

    ctx.vertexShader(faceBuffer);
    //cout << faceBuffer[0].color << endl;
    faceBuffer.clear();
    ctx.Update();
    ctx.fillMap(0);
    }
    while(true);

    return 0;
}