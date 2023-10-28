#include "Loader.h"

Loader::Loader(const std::string& path) : m_path(path)
{
    std::ifstream file(path);
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;

            if (keyword == "v") {
                float x, y;
                iss >> x >> y;
                m_vertices.push_back(Vector2D(x,y));
            }
            else if (keyword == "f") {
                int index;
                while (iss >> index) {
                    m_indices.push_back(index);
                }
            }
        }
        file.close();
    }
}

Loader::~Loader()
{}

std::vector<Vector2D> Loader::vertices() const
{
    return m_vertices;
}

std::vector<int> Loader::indices() const
{
    return m_indices;
}

bool Loader::isLoad()
{
    return false;
}
