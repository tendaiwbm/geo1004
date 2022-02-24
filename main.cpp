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
            while(iss >> word) face_vertex_indexes.push_back(stoi(word)-1);
            if (face_vertex_indexes.size() == 4) faces_intermediate.push_back(face_vertex_indexes);
        }
      }
    }

    int edge_id = 1;
    for (int i = 0; i < faces_intermediate.size(); i++) {
        //std::cout << vertices[faces[i][0]].point << std::endl;
        std::vector<Edge> face_edges;
        Edge e1 = {edge_id,faces_intermediate[i][0],faces_intermediate[i][1]};
        face_edges.push_back(e1);
        edge_id++;

        Edge e2 = {edge_id,faces_intermediate[i][1],faces_intermediate[i][2]};
        face_edges.push_back(e2);
        edge_id++;

        Edge e3 = {edge_id,faces_intermediate[i][2],faces_intermediate[i][3]};
        face_edges.push_back(e3);
        edge_id++;

        Edge e4 = {edge_id,faces_intermediate[i][3],faces_intermediate[i][0]};
        face_edges.push_back(e4);
        edge_id++;

        for (auto e: face_edges) {
            for (auto v: edges) {
                if ((e.start_vertex == v[0].start_vertex) && (e.end_vertex == v[0].end_vertex) && (e.id != v[0].id)) {
                    e.id = v[0].id;
                    e.start_vertex = v[0].start_vertex;
                    e.end_vertex = v[0].end_vertex;
                } else if ((e.start_vertex == v[0].end_vertex) && (e.end_vertex == v[0].start_vertex) && (e.id != v[0].id)) {
                        e.id = v[0].id;
                        e.start_vertex = v[0].end_vertex;
                        e.end_vertex = v[0].start_vertex;
                    }
                if ((e.start_vertex == v[1].start_vertex) && (e.end_vertex == v[1].end_vertex) && (e.id != v[1].id)) {
                    e.id = v[1].id;
                    e.start_vertex = v[1].start_vertex;
                    e.end_vertex = v[1].end_vertex;
                } else if ((e.start_vertex == v[1].end_vertex) && (e.end_vertex == v[1].start_vertex) && (e.id != v[1].id)) {
                        e.id = v[1].id;
                        e.start_vertex = v[1].end_vertex;
                        e.end_vertex = v[1].start_vertex;
                    }
                if ((e.start_vertex == v[2].start_vertex) && (e.end_vertex == v[2].end_vertex) && (e.id != v[2].id)) {
                    e.id = v[2].id;
                    e.start_vertex = v[2].start_vertex;
                    e.end_vertex = v[2].end_vertex;
                } else if ((e.start_vertex == v[2].end_vertex) && (e.end_vertex == v[2].start_vertex) && (e.id != v[2].id)) {
                        e.id = v[2].id;
                        e.start_vertex = v[2].end_vertex;
                        e.end_vertex = v[2].start_vertex;
                }
                if ((e.start_vertex == v[3].start_vertex) && (e.end_vertex == v[3].end_vertex) && (e.id != v[3].id)) {
                    e.id = v[3].id;
                    e.start_vertex = v[3].start_vertex;
                    e.end_vertex = v[3].end_vertex;
                } else if ((e.start_vertex == v[3].end_vertex) && (e.end_vertex == v[3].start_vertex) && (e.id != v[3].id)) {
                        e.id = v[3].id;
                        e.start_vertex = v[3].end_vertex;
                        e.end_vertex = v[3].start_vertex;
                }
            }
        }
        edges.push_back(face_edges);
        face_edges.clear();

    }

    /*
    std::cout << "num_vertices: " << vertices.size() << std::endl;
    std::cout << "num_edges: " << edges[0].size() << std::endl;
    std::cout << "num_faces: " << faces_intermediate.size() << std::endl;
    int q = 1;
    for (auto v: vertices) {
        std::cout << v.point << "," << q << std::endl;
        q++;
    }
    for (auto f: faces_intermediate) std::cout << "(" << f[0]+1 << f[1]+1 << f[2]+1 << f[3]+1 << ")" << std::endl;
    for (auto e: edges) std::cout << "(" << "[" << vertices[e[0].start_vertex].point << "," << vertices[e[0].end_vertex].point << "]" << "," << "[" << vertices[e[1].start_vertex].point << "," << vertices[e[1].end_vertex].point << "]" << "," "[" << vertices[e[2].start_vertex].point << "," << vertices[e[2].end_vertex].point << "]" << "," << "[" << vertices[e[3].start_vertex].point << "," << vertices[e[3].end_vertex].point << "]" << ")" << std::endl;
    */

    //  declare faces to store Face objects which model edges, and vertices joining them, bounding each face
    std::vector<Face> faces;
    for (int i = 0; i < faces_intermediate.size(); i++) {
        //std::cout << "(" << faces_intermediate[i][0]+1 << "," << faces_intermediate[i][1]+1 << "," << faces_intermediate[i][2]+1 << "," << faces_intermediate[i][3]+1 << ")" << std::endl;
        std::vector<int> face_vertex_indexes{faces_intermediate[i][0],faces_intermediate[i][1],faces_intermediate[i][2],faces_intermediate[i][3]};
        Face f = {i+1,face_vertex_indexes,edges[i]};
        faces.push_back(f);
    }

    





  
  // ## Output generalised map to CSV ##

  // ## Create triangles from the darts ##

  // ## Write triangles to obj ##
  
  return 0;
}
