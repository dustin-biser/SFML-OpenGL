#include <Mesh.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ShaderException.hpp>

using namespace GlUtils;
using namespace std;

/**
 * Constructs a Mesh object from a Wavefront .obj file format.
 *
 * @param objFileName - path to .obj file
 */
Mesh::Mesh(const char* objFileName) {
    loadFromObjFile(objFileName);
}

void Mesh::loadFromObjFile(const char* objFileName){
    // Reset datastructures before loading them with data.
    vertices.resize(0);
    normals.resize(0);
    indices.resize(0);
    glm_vertices.resize(0);
    glm_normals.resize(0);

    ifstream in(objFileName, ios::in);
    in.exceptions(std::ifstream::badbit);

    if (!in) {
        stringstream errorMessage;
        errorMessage << "Unable to open .obj file: " << objFileName << endl;
        throw ShaderException(errorMessage.str());
    }

    string line;
    while (!in.eof()) {
        try {
            getline(in, line);
        } catch(const ifstream::failure & e) {
            cerr << "Error calling getline() -- ";
            cerr << e.what() << endl;
        }

        if (line.substr(0,2) == "v ") {
            // Vertex data on this line.
            // Get entire line excluding first 2 chars.
            istringstream s(line.substr(2));
            // Allocate new vec3, fill in its indices, and add to vertices vector.
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            glm_vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ") {
            // Face data on this line, which contains index indices
            // Get entire line excluding first 2 chars.
            istringstream s(line.substr(2));
            unsigned short a, b, c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
        }
    }

    // Construct a normal for each vertex.
    glm_normals.resize(glm_vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        unsigned short ia = indices.at(i);
        unsigned short ib = indices.at(i + 1);
        unsigned short ic = indices.at(i + 2);

        // Create two vectors; one from vertexA to vertexB, and one from vertexA to vertexC.
        // Compute normal by taking cross produce of these two vectors.  This is the normal
        // for the three vertices.
        glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3( glm_vertices.at(ib) ) - glm::vec3( glm_vertices.at(ia) ),
                glm::vec3( glm_vertices.at(ic) ) - glm::vec3( glm_vertices.at(ia) )
        ));

        glm_normals.at(ia) = glm_normals.at(ib) = glm_normals.at(ic) = normal;
    }

    // Copy data to vertex vector
    for(glm::vec3 v : glm_vertices) {
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
    }

    // Copy data to normal vector
    for(glm::vec3 v : glm_normals) {
        normals.push_back(v.x);
        normals.push_back(v.y);
        normals.push_back(v.z);
    }

    // Clear data from glm_vertices and glm_normals, no longer needed.
    glm_vertices.resize(0);
    glm_normals.resize(0);
}

/**
 * Initialize this Mesh object using contents of the given Wavefront .obj file.
 *
 * @param objFileName - path to .obj file
 */
void Mesh::fromObjFile(const char* objFileName) {
    loadFromObjFile(objFileName);
}

const float * Mesh::getVertexDataPtr() const {
    return const_cast<float *>(vertices.data());
}

const float * Mesh::getNormalDataPtr() const {
    return const_cast<float *>(normals.data());
}

const unsigned short * Mesh::getIndexDataPtr() const {
    return const_cast<unsigned short *>(indices.data());
}

/**
 * Returns the total size in bytes of the Mesh's vertex data.
 *
 * @return size_t
 */
size_t Mesh::getNumVertexBytes() const {
    return vertices.size() * sizeof(float);
}

/**
 * Returns the total size in bytes of the Mesh's normals.
 *
 * @return size_t
 */
size_t Mesh::getNumNormalBytes() const {
    return normals.size() * sizeof(float);
}

/**
 * Returns the total size in bytes of the Mesh's index data.
 *
 * @return size_t
 */
size_t Mesh::getNumIndexBytes() const {
    return indices.size() * sizeof(unsigned short);
}

/**
 *
 * @return the number of vertices for this \c Mesh, where each vertex is
 * composed of 3 floats {x,y,z}.
 */
size_t Mesh::getNumVertices() const {
    return (size_t)(vertices.size() / 3.0f);
}

/**
 *
 * @return the number of normals for this \c Mesh, where each normal is
 * composed of 3 floats {x,y,z}.
 */
size_t Mesh::getNumNormals() const {
   return (size_t)(normals.size() / 3.0f);
}

/**
 *
 * @return the number of index elements for this \c Mesh, where each index
 * is composed a single <tt>unsigned short</tt>.
 */
size_t Mesh::getNumIndices() const {
   return indices.size();
}
