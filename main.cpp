// some standard libraries that are helpfull for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Gmap.h"

int main(int argc, const char * argv[]) {
    std::string filename("cube.obj");
    std::string file_out_obj = "/home/ravi/git/geo1004.2022/hw/01/data/torus_triangulated.obj";
    std::string file_out_csv_d = "/home/ravi/git/geo1004.2022/hw/01/data/torus_darts.csv";
    std::string file_out_csv_0 = "/home/ravi/git/geo1004.2022/hw/01/data/torus_vertices.csv";
    std::string file_out_csv_1 = "/home/ravi/git/geo1004.2022/hw/01/data/torus_edges.csv";
    std::string file_out_csv_2 = "/home/ravi/git/geo1004.2022/hw/01/data/torus_faces.csv";
    std::string file_out_csv_3 = "/home/ravi/git/geo1004.2022/hw/01/data/torus_volume.csv";
  
  // ## Read OBJ file ##
  // ## Construct generalised map using the structures from Gmap.h ##

  /* Example how to read vertices from an obj file: */

    /* declare vertices to Store vertex from the .obj file
       declare edges to store Edge objects constructed from vertices
       declare faces_intermediate to store temporary faces, not face objects
    */
    std::ifstream input_file(filename);
    std::vector<Vertex> vertices;
    std::vector<std::vector<Edge>> edges;
    std::vector<std::vector<int>> faces_intermediate;
    std::vector<Dart> darts;

    if (input_file.is_open()) {
      std::string line;
      while (getline(input_file, line)) {
        std::istringstream iss(line);
        std::string word;
        iss >> word;
        if (word == "v") {
          std::vector<float> coordinates;
          while (iss >> word) coordinates.push_back(std::stof(word));
          if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
          else vertices.push_back(Vertex());
        }

        if (word == "f") {
            std::vector<int> face_vertex_indexes;
            while(iss >> word) face_vertex_indexes.push_back(stoi(word));
            if (face_vertex_indexes.size() == 4) faces_intermediate.push_back(face_vertex_indexes);
        }
      }
    }

    int edge_id = 1;
    for (int i = 0; i < faces_intermediate.size(); i++) {
        //std::cout << vertices[faces[i][0]].point << std::endl;
        std::vector<Edge> face_edges;

        edge_id++;
        Edge e1 = {edge_id, faces_intermediate[i][0], faces_intermediate[i][1]};
        face_edges.push_back(e1);


        edge_id++;
        Edge e2 = {edge_id, faces_intermediate[i][1], faces_intermediate[i][2]};
        face_edges.push_back(e2);

        edge_id++;
        Edge e3 = {edge_id, faces_intermediate[i][2], faces_intermediate[i][3]};
        face_edges.push_back(e3);

        edge_id++;
        Edge e4 = {edge_id, faces_intermediate[i][3], faces_intermediate[i][0]};
        face_edges.push_back(e4);


        for (auto e: face_edges) {
            for (int v = 0; v < edges.size(); v++) {
                for (int vi = 0; vi < edges[v].size(); vi++) {
                    if ((e.start_vertex == edges[v][vi].start_vertex) && (e.end_vertex == edges[v][vi].end_vertex)) {
                        //std::cout << "Existing edge id: " << edges[v][vi].id << "\t" << "New edge id: " << e.id << std::endl;
                        e.id = edges[v][vi].id;
                        //std::cout << "Existing edge id: " << edges[v][vi].id << "\t" << "New edge id: " << e.id << std::endl;
                        //e.start_vertex = v[0].start_vertex;
                        //e.end_vertex = v[0].end_vertex;
                    } else if ((e.start_vertex == edges[v][vi].end_vertex) && (e.end_vertex == edges[v][vi].start_vertex)) {
                        //std::cout << "Existing edge id: " << edges[v][vi].id << "\t" << "New edge id: " << e.id << std::endl;
                        e.id = edges[v][vi].id;
                        //std::cout << "Existing edge id: " << edges[v][vi].id << "\t" << "New edge id: " << e.id << std::endl;
                    }
                }
            }
        }
        edges.push_back(face_edges);
        face_edges.clear();
    }

    for (auto f: faces_intermediate) std::cout << "(" << f[0] << f[1] << f[2] << f[3] << ")" << std::endl;
    for (auto e: edges) std::cout << "(" << "[" << e[0].start_vertex << "," << e[0].end_vertex << "]" << "," << "[" << e[1].start_vertex << "," << e[1].end_vertex << "]" << "," "[" << e[2].start_vertex << "," << e[2].end_vertex << "]" << "," << "[" << e[3].start_vertex << "," << e[3].end_vertex << "]" << ")" << std::endl;


    //  declare faces to store Face objects which model edges, and vertices joining them, bounding each face
    std::vector<Face> faces;
    for (int i = 0; i < faces_intermediate.size(); i++) {
        //std::cout << "(" << faces_intermediate[i][0]+1 << "," << faces_intermediate[i][1]+1 << "," << faces_intermediate[i][2]+1 << "," << faces_intermediate[i][3]+1 << ")" << std::endl;
        std::vector<int> face_vertex_indexes{faces_intermediate[i][0],faces_intermediate[i][1],faces_intermediate[i][2],faces_intermediate[i][3]};
        Face f = {i+1,face_vertex_indexes,edges[i]};
        faces.push_back(f);
    }

    bool face_test = true;
    Face current_face = faces[5];
    Vertex current_vertex = vertices[current_face.node_list[0]];
    Edge current_edge = current_face.edge_list[3];
    //std::cout << current_edge.id;
    int t = 0;
    while (face_test) {
       //std::cout << starting_face.id << std::endl;
       face_test = false;
    }

  
  // ## Output generalised map to CSV ##

  // ## Create triangles from the darts ##

  // ## Write triangles to obj ##
  
  return 0;
}
