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

    int edge_id = 0;
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


        for (int e = 0;e<face_edges.size();e++) {
            for (int v = 0; v < edges.size(); v++) {
                for (int vi = 0; vi < edges[v].size(); vi++){
                    if ((face_edges[e].start_vertex == edges[v][vi].start_vertex) && (face_edges[e].end_vertex == edges[v][vi].end_vertex) && (face_edges[e].id != edges[v][vi].id)) {
                        int * p = &edges[v][vi].id;
                        face_edges[e].id = *p;

                    } else if ((face_edges[e].start_vertex == edges[v][vi].end_vertex) && (face_edges[e].end_vertex == edges[v][vi].start_vertex) && (face_edges[e].id != edges[v][vi].id)) {
                        int * p = &edges[v][vi].id;
                        face_edges[e].id = *p;
                    }
                }
            }
        }

        edges.push_back(face_edges);
        face_edges.clear();
    }

    //  declare faces to store Face objects which model edges, and vertices joining them, bounding each face
    std::vector<Face> faces;
    for (int i = 0; i < faces_intermediate.size(); i++) {
        //std::cout << "(" << faces_intermediate[i][0]+1 << "," << faces_intermediate[i][1]+1 << "," << faces_intermediate[i][2]+1 << "," << faces_intermediate[i][3]+1 << ")" << std::endl;
        std::vector<int> face_vertex_indexes{faces_intermediate[i][0],faces_intermediate[i][1],faces_intermediate[i][2],faces_intermediate[i][3]};
        Face f = {i+1,face_vertex_indexes,edges[i]};
        faces.push_back(f);
    }

    int t = 1;
    for (int face_index = 0; face_index < faces.size(); face_index++) {
        for (int edge_index = 0; edge_index < faces[1].edge_list.size(); edge_index++) {

            Dart d1;
            d1.dart_id = t;
            d1.face_id = faces[face_index].id;
            d1.edge_id = faces[face_index].edge_list[edge_index].id;
            d1.vertex_index = faces[face_index].edge_list[edge_index].start_vertex;
            d1.alpha0 = faces[face_index].edge_list[edge_index].end_vertex;
            t++;
            for (auto e: faces[face_index].edge_list) {
                if (d1.vertex_index == e.end_vertex) {
                    d1.alpha1 = e.start_vertex;
                    darts.push_back(d1);
                }
            }

            Dart d2;
            d2.dart_id = t;
            d2.face_id = faces[face_index].id;
            d2.edge_id = faces[face_index].edge_list[edge_index].id;
            d2.vertex_index = faces[face_index].edge_list[edge_index].end_vertex;
            d2.alpha0 = faces[face_index].edge_list[edge_index].start_vertex;
            //darts.push_back(d2);
            t++;
            for (auto e: faces[face_index].edge_list) {
                if (d2.vertex_index == e.start_vertex) {
                    d2.alpha1 = e.end_vertex;
                    darts.push_back(d2);
                }
            }
            //std::cout << d1.dart_id << "\tv:" << d1.vertex_index << "\te:" << d1.edge_id << "\tf:" << d1.face_id << "\ta0:" << d1.alpha0 << "\ta1:" << d1.alpha1 << std::endl;
            //std::cout << d2.dart_id << "\tv:" << d2.vertex_index << "\te:" << d2.edge_id << "\tf:" << d2.face_id << "\ta0:" << d2.alpha0 << "\ta1:" << d2.alpha1 << std::endl;
        }
    }
    for (int dart_index = 0; dart_index < darts.size(); dart_index++) {
        for (auto other_dart: darts) {
            if ((darts[dart_index].vertex_index == other_dart.vertex_index) && (darts[dart_index].edge_id == other_dart.edge_id) && (darts[dart_index].face_id != other_dart.face_id)) {
                //std::cout << darts[dart_index].dart_id << "\tv:" << darts[dart_index].vertex_index << "\te:" << darts[dart_index].edge_id << "\tf:" << darts[dart_index].face_id << "\ta0:" << darts[dart_index].alpha0 << "\ta1:" << darts[dart_index].alpha1 << std::endl;
                //std::cout << other_dart.dart_id << "\tv:" << other_dart.vertex_index << "\te:" << other_dart.edge_id << "\tf:" << other_dart.face_id << "\ta0:" << other_dart.alpha0 << "\ta1:" << other_dart.alpha1 << std::endl;
                darts[dart_index].alpha2 = other_dart.face_id;
            }
        }
    }
    for (int dart_index = 0; dart_index < darts.size(); dart_index++)
        std::cout << darts[dart_index].dart_id << "\tvertex:" << darts[dart_index].vertex_index << "\tedge:" << darts[dart_index].edge_id <<
        "\t\tface:" << darts[dart_index].face_id << "\t\talpha0:" << darts[dart_index].alpha0 << "\talpha1:" << darts[dart_index].alpha1 <<
        "\talpha2:" << darts[dart_index].alpha2 << std::endl;




  // ## Output generalised map to CSV ##

  // ## Create triangles from the darts ##

  // ## Write triangles to obj ##
  
  return 0;
}
