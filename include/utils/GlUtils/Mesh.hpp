#ifndef MESH_HPP_
#define MESH_HPP_

#include <glm/glm.hpp>
#include <vector>
#include <memory>

using namespace std;

namespace GlUtils {

    class Mesh {
    private:
        vector<float> vertices;
        vector<float>  normals;
        vector<unsigned short>  indices;  /**< Collection of vertex index elements */

        vector<glm::vec3> glm_vertices;
        vector<glm::vec3> glm_normals;

    public:
        Mesh(const char* objFileName);

        Mesh() { }

        ~Mesh() { }

        void fromObjFile(const char* objFileName);

        const float * getVertexDataPtr() const;

        const float * getNormalDataPtr() const;

        const unsigned short * getIndexDataPtr() const;

        size_t getNumVertexBytes() const;

        size_t getNumNormalBytes() const;

        size_t getNumIndexBytes() const;

        size_t getNumVertices() const;

        size_t getNumNormals() const;

        size_t getNumIndices() const;

    private:
        void initialize();
        void loadFromObjFile(const char* objFileName);
    };
}

#endif /* MESH_HPP_ */
