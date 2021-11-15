//
// Created by dietrich on 28.10.21.
//

#ifndef GEOBURST_OSM_CO_OCCURRENCE_GRAPH_H
#define GEOBURST_OSM_CO_OCCURRENCE_GRAPH_H

#include <vector>
#include <memory>
#include <numeric>
#include <eigen3/Eigen/SparseCore>

#include "sliding_window/sliding_window.h"

using EventTweet::SlidingWindow::SnapShot;
using Eigen::SparseMatrix;
using Eigen::Triplet;
using Eigen::ColMajor;

namespace EventTweet::Co_Occurrence_Graph {

    class Vertex {
    private:
        std::unique_ptr<std::string> word_ptr;

    public:
        Vertex() {
            word_ptr = std::unique_ptr<std::string> { };
        }

        explicit Vertex(std::string& _word) {
            word_ptr = std::make_unique<std::string>(_word);
        }

        explicit Vertex(std::string&& _word) {
            word_ptr = std::make_unique<std::string>(std::move(_word));
        }

        Vertex(const Vertex& vertex) = delete;

        Vertex(Vertex&& vertex)  noexcept {
            this->word_ptr = std::exchange(vertex.word_ptr, nullptr);
        }

        std::string GetVertex() {
            return *word_ptr;
        }
    };

    class KeyWordGraph {
    private:
        SnapShot snapshot;
        std::size_t SIZE = 0;
        std::vector<Vertex> vertex_list = {};
        SparseMatrix<double, ColMajor> adjacent_matrix;

    public:
        KeyWordGraph() = default;

        ~KeyWordGraph();

        explicit KeyWordGraph(SnapShot& _snapshot);

        KeyWordGraph& Init();

        KeyWordGraph& GenerateVertexList();

        KeyWordGraph& GenerateAdjacentMatrix();

        int FindCommonTweets(std::unordered_set<std::string>& left_set, std::unordered_set<std::string>& right_set);

        SparseMatrix<double, ColMajor>& GetAdjacentMatrix();
    };
}
#endif //GEOBURST_OSM_CO_OCCURRENCE_GRAPH_H
