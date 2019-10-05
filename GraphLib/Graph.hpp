//Debugging

#include <iostream>
#include <memory>
#include <vector>
#include <atomic>

template <typename T>
class Graph;

template <typename T>
void no_op_int(Graph<T> *ptr)
{
    // for locally created obejects;
}

//template <typename T>

int GetID()
{
    static std::atomic<int> id(0);
    return id++;
}

template <typename T>
class Graph
{
    typedef std::shared_ptr<Graph<T>> GraphPTR;

    Graph()
    {
    }

public:

    
    void AddToPath(Graph<T> & edge)
    {
        GraphPTR ptr(&edge, no_op_int<T>);
        mPath.push_back(ptr);
    }

    Graph(const Graph<T> &copy)
    {
        mID = copy.mID;
        mData = copy.mData;
        mEdges.clear();
        mEdges = copy.mEdges;
        mDist  = copy.mDist;
        mVisited = copy.mVisited;
    }

    Graph<T> &operator=(const Graph<T> &copy)
    {
        mID = copy.mID;
        mData = copy.mData;
        mEdges.clear();
        mEdges = copy.mEdges;
        mDist  = copy.mDist;
        mVisited = copy.mVisited;
    }

    Graph(T data) : mData(data)
    {
        mDist = INT32_MAX;
        mVisited = false;
    }

    void AddEdge(Graph<T> &edge, int weight)
    {
        //Don't copy
        GraphPTR ptr(&edge, no_op_int<T>);
        mEdges.push_back(GraphMeta(ptr, weight));
    }

    const GraphPTR findMin()
    {
        int dist = INT32_MAX;
        GraphPTR minNode;
        int index = -1;
        int last_index = 0;
        for (auto &node : mPath)
        {   
            if (dist > node->mDist && !node->mVisited)
            {
                dist = node->mDist;
                minNode = node;

            }
        }

        //nodes[last_index].mVisited= true;
        minNode->mVisited = true;
        return minNode;
    }

    //This node consider to be shortest node
    std::vector<Graph<T>>
    DijkstraShortestPath()
    {
        
        std::vector<GraphPTR> tmp;
        //we should be knowing in advance what node should be participting
        //in advance
        mPath[0]->mDist = 0;
        // or we can find all pair shortest path
        for (int j = 0; j < mPath.size(); j++)
        {
            auto minNode = findMin();

            int size = minNode->mEdges.size();

            for (int i = 0; i < size; i++)
            {

                if (minNode->mEdges[i].edge->mDist > minNode->mDist + minNode->mEdges[i].weight)
                {
                    
                    minNode->mEdges[i].edge->mDist = minNode->mDist + minNode->mEdges[i].weight;
                    minNode->mEdges[i].edge->mParent = std::make_shared<Graph<T>>(*minNode);

                    // Front 

                }
            }
        }
        
        std::vector<Graph<T>> pathToParent;
        GraphPTR graph = mPath[mPath.size() -1];
        
        while(graph) {
          
          pathToParent.push_back(graph);
          graph = graph->mParent;
        
        }

        if(graph->mID == mPath[0]->mID) {
           
          pathToParent.push_back(graph);

        }

        
        return pathToParent;
        
    }

private:
    struct GraphMeta
    {
        GraphMeta(GraphPTR ptr, int wt) : edge(ptr), weight(wt)
        {
        }

        GraphMeta(const GraphMeta& other) {
            weight = other.weight;
            edge   = other.edge;
        }

        GraphMeta& operator=(const GraphMeta& other) {
            weight = other.weight;
            edge   = other.edge;
        }

        int weight;
        Graph::GraphPTR edge;
    };

    T mData;
    int mDist;
    GraphPTR mParent;
    bool mVisited;
    std::vector<GraphMeta> mEdges;
    std::vector<GraphPTR> mPath;
    int mID;
};