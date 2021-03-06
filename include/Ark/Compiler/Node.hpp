#ifndef ark_node
#define ark_node

#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <Ark/Exceptions.hpp>

namespace Ark::internal
{
    /// The different node types available
    enum class NodeType
    {
        Symbol,
        Capture,
        GetField,
        Keyword,
        String,
        Number,
        List,
        Closure
    };

    /// The different keywords available
    enum class Keyword
    {
        Fun,
        Let,
        Mut,
        Set,
        If,
        While,
        Begin,
        Import,
        Quote,
        Del
    };

    /**
     * @brief A node of an Abstract Syntax Tree for ArkScript
     * 
     */
    class Node
    {
    public:
        using Iterator = std::vector<Node>::const_iterator;
        using Map      = std::unordered_map<std::string, Node>;
        using Value    = std::variant<double, std::string, Keyword>;

        /**
         * @brief Construct a new Node object
         * 
         * @param value 
         */
        Node(int value);

        /**
         * @brief Construct a new Node object
         * 
         * @param value 
         */
        Node(double value);

        /**
         * @brief Construct a new Node object
         * 
         * @param value 
         */
        Node(const std::string& value);

        /**
         * @brief Construct a new Node object
         * 
         * @param value 
         */
        Node(Keyword value);

        /**
         * @brief Construct a new Node object, does not set the value
         * 
         * @param type 
         */
        Node(NodeType type=NodeType::Symbol);

        /**
         * @brief Return the string held by the value (if the node type allows it)
         * 
         * @return const std::string& 
         */
        const std::string& string() const;

        /**
         * @brief Return the number held by the value (if the node type allows it)
         * 
         * @return double 
         */
        double number() const;

        /**
         * @brief Return the keyword held by the value (if the node type allows it)
         * 
         * @return Keyword 
         */
        Keyword keyword() const;

        /**
         * @brief Every node has a list as well as a value so we can push_back on all node no matter their type
         * 
         * @param node a sub-node to push on the list held by the current node
         */
        void push_back(const Node& node);

        /**
         * @brief Return the list of sub-nodes held by the node
         * 
         * @return std::vector<Node>& 
         */
        std::vector<Node>& list();

        /**
         * @brief Return the list of sub-nodes held by the node
         * 
         * @return const std::vector<Node>& 
         */
        const std::vector<Node>& const_list() const;

        /**
         * @brief Return the node type
         * 
         * @return NodeType 
         */
        NodeType nodeType() const;

        /**
         * @brief Set the Node Type object
         * 
         * @param type 
         */
        void setNodeType(NodeType type);

        /**
         * @brief Set the String object
         * 
         * @param value 
         */
        void setString(const std::string& value);

        /**
         * @brief Set the Number object
         * 
         * @param value 
         */
        void setNumber(double value);

        /**
         * @brief Set the Keyword object
         * 
         * @param kw 
         */
        void setKeyword(Keyword kw);

        /**
         * @brief Set the Position of the node in the text
         * 
         * @param line 
         * @param col 
         */
        void setPos(std::size_t line, std::size_t col);

        /**
         * @brief Get the line at which this node was created
         * 
         * @return std::size_t 
         */
        std::size_t line() const;

        /**
         * @brief Get the column at which this node was created
         * 
         * @return std::size_t 
         */
        std::size_t col() const;

        friend std::ostream& operator<<(std::ostream& os, const Node& N);
        friend inline bool operator==(const Node& A, const Node& B);

    private:
        NodeType m_type;
        Value m_value;
        std::vector<Node> m_list;
        // position of the node in the original code, useful when it comes to parser errors
        std::size_t m_line, m_col;
    };

    #include "Node.inl"

    using Nodes = std::vector<Node>;

    std::ostream& operator<<(std::ostream& os, const Nodes& N);
}

#endif  // ark_node
