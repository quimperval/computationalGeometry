# Doubly-connected edge list

A *doubly-connected edge list* (dcel) contains a record for each face, edge and vertex of the subdivision.

To be able to walk around a face in counterclockwise order we store a pointer from each edge to the next. 

It is convenient to view the different sides of an edge as two distinct half-edges. Half-edges bound only one face. 

Defining the next half-edge of a given half-edge with respect to a counterclockwise traversal of a face induces an orientation on each half edge: it is oriented such that the face that it bounds lies to its left for an observer walking along the edge. 

Two half-edges we get for a given edge are called twins.

The dcel consists of three collections of records:

- One for the vertices. The vertex record lf a vertex v stores the coordinates of v in a field called Coordinates(v). It also stores a pointer IncidentEdge(v) to an arbitrary half-edge that has v as its origin.
- One for the faces. The face record of a face *f* stores a pointer *OuterComponent(f)* to some half-edge on its outer boundary. For the unbounded face this pointer is *nil*. It also stores a list *InnerComponents(f)*, which contains for each hole in the face a pointer to some half-edge on the boundary of the hole. 
- One for the half-edges. The half-edge record lf a half-edge e stores a pointer Origin(e) to its origin, a pointer Twin(e) to its twin half-edge, and a pointer IncidentFace(f) to the face that it bounds. The origin is chosen such that IncidentFace(e) lies to the left of e when traversed from origin to destination. The half-edge record also stores pointers Next(e) and Prev(e) to the next and previous on the boundary of IncidentFace(e). 



