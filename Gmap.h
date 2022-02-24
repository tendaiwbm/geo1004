#pragma once

#include "Point.h"

struct Point;
struct Dart;
struct Vertex;
struct Edge;
struct Face;
struct Volume;

/*
Below you find the basic elements that you need to build the generalised map.
The main thing you need to fill out are the links between the elements:
  * the involutions and cells on the Dart
  * the darts on the cells

One way to do this is by using pointers. eg. define a member on the dart struct like

  Struct Dart {
    // involutions:
    Dart* a0 = nullptr;
    // ...

    // cells:
    // ...
  
  };

Then you could create and link Darts like:
  
  Dart* dart_a = new Dart();
  Dart* dart_b = new Dart();

  dart_a->a0 = dart_b;
*/

struct Dart {
    int dart_id;
    int vertex_id;
    int edge_id;
    int face_id;

  // involutions:
  // ..

  // cells:
  // ...

};

struct Vertex {
  // the coordinates of this vertex:
  Point point;

  // constructor without arguments
  Vertex() : point(Point()) 
  {}

  // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
  Vertex(const double &x, const double &y, const double &z) : point(Point(x,y,z))
  {}

  // a dart incident to this Vertex:
  // ...

};

struct Edge {
    int id;
    int start_vertex;
    int end_vertex;
  // a dart incident to this Edge:
  // ...

  // function to compute the barycenter for this Edge (needed for triangulation output):

   //Point barycenter(Point a, Point b) {}
};

struct Face {
    int id;
    std::vector<int> node_list;
    std::vector<Edge> edge_list;
  // a dart incident to this Face:
  // ...

  // function to compute the barycenter for this Face (needed for triangulation output):
  // Point barycenter() {}

};

struct Volume {
    int id;
  // a dart incident to this Volume:
  // ...

};