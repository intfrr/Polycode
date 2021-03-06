/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolyPolygon.h"

namespace Polycode {

Polygon::Polygon()  : useVertexNormals(false), vertexCount(0) {
	useVertexNormals = true;	
}

Polygon::~Polygon() {
	
	for(int i=0; i < vertices.size(); i++) {	
		delete vertices[i];
	}
	vertices.clear();
}
	
void Polygon::flipUVY() {
	for(int i=0; i < vertices.size(); i++) {
		Vector2 coord = vertices[i]->getTexCoord();
		vertices[i]->setTexCoord(coord.x, 1-coord.y);
	}
}

unsigned int Polygon::getVertexCount() {
	return vertices.size();
}

Vertex *Polygon::getVertex(unsigned int index) {
	return vertices[index];
}

Vector3 Polygon::getFaceNormal() {
/*
	Vector3 fNormal;
	fNormal.x = (vertices[2]->z-vertices[1]->z)*(vertices[2]->y-vertices[1]->y)-(vertices[0]->y-vertices[1]->y)*(vertices[2]->z-vertices[1]->z);
	fNormal.y = (vertices[0]->x-vertices[1]->x)*(vertices[2]->z-vertices[1]->z)-(vertices[0]->z-vertices[1]->z)*(vertices[2]->x-vertices[1]->x);
	fNormal.z = (vertices[0]->y-vertices[1]->y)*(vertices[2]->x-vertices[1]->x)-(vertices[0]->x-vertices[1]->x)*(vertices[2]->y-vertices[1]->y);
	fNormal.Normalize();	
	return fNormal;
	*/
	return normal;
}

Rectangle Polygon::getBounds2D() {
	Rectangle retBox;
	retBox.x = 1000000000;
	retBox.y = 1000000000;
	for(int i=0; i < vertices.size(); i++) {
			retBox.x = min(retBox.x,vertices[i]->x);
			retBox.y = min(retBox.y,vertices[i]->y);
	}
	for(int i=0; i < vertices.size(); i++) {
			retBox.w = max(retBox.w, vertices[i]->x - retBox.x);
			retBox.h = max(retBox.h, vertices[i]->y - retBox.y);
	}
	
	return retBox;
}
	
void Polygon::removeVertex(int index) {
	Vertex *vert = vertices[index];
	vertices.erase(vertices.begin() + index);
	delete vert;
}

void Polygon::setNormal(Vector3 normal) {
	this->normal = normal;
}	

void Polygon::calculateNormal() {
	if(vertices.size() < 3)
		return;

//	normal->x = (vertices[2]->z-vertices[1]->z)*(vertices[2]->y-vertices[1]->y)-(vertices[0]->y-vertices[1]->y)*(vertices[2]->z-vertices[1]->z);
//	normal->y = (vertices[0]->x-vertices[1]->x)*(vertices[2]->z-vertices[1]->z)-(vertices[0]->z-vertices[1]->z)*(vertices[2]->x-vertices[1]->x);
//	normal->z = (vertices[0]->y-vertices[1]->y)*(vertices[2]->x-vertices[1]->x)-(vertices[0]->x-vertices[1]->x)*(vertices[2]->y-vertices[1]->y);

	normal = (*vertices[0] - *vertices[1]).crossProduct((*vertices[1] - *vertices[2]));
	
	normal.Normalize();
	
	for(int i=0; i < vertices.size(); i++) {
		vertices[i]->normal.x = normal.x;
		vertices[i]->normal.y = normal.y;
		vertices[i]->normal.z = normal.z;		
	}
}

Vertex *Polygon::addVertex(Number x, Number y, Number z) {
	Vertex *vertex = new Vertex(x,y,z);
	vertices.push_back(vertex);
	return vertex;
}

void Polygon::addVertex(Vertex *vertex) {
	vertices.push_back(vertex);
}

Vertex *Polygon::addVertex(Number x, Number y, Number z, Number u, Number v) {
	Vertex *vertex = new Vertex(x,y,z,u,v);
	vertices.push_back(vertex);
	return vertex;
}

}