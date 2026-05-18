#ifndef NODE_HPP
#define NODE_HPP

enum class NodeType
{
    START_NODE,
    WEIGHTED_NODE,
    END_NODE
};

enum class ObstacleWeight
{
    MOUNTAIN_NODE = -1,
    RIVER_NODE = 5
};

class Node
{
public:
    Node(NodeType type, int x = 0, int y = 0);
    Node(NodeType type, double weight, int x = 0, int y = 0);
    Node();

    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;
    bool operator<(const Node& other) const;
    int getX() const;
    int getY() const;
    double getWeight() const;
    NodeType Type() const;
    void setX(int);
    void setY(int);

private:
    int m_x;
    int m_y;
    double m_weight;
    NodeType m_type;
};

#endif // NODE_HPP
