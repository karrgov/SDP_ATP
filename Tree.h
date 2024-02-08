#include <iostream>
#include <vector>
#include <string>


class Node 
{
    private:
    std::string name;
    std::vector<Node*> children;

    public: 
    std::string getName();
    Node(const std::string& value);
    ~Node();

    friend class Tree;
};


class Tree
{
    private:
    Node* root;
    std::string nameOfTree;

    void copyNodes(Node*& destination, const Node* source);

    public:
    Tree(std::string name);
    Tree();
    ~Tree();
    Tree(const Tree& other); 
    Tree& operator=(const Tree& other); 


    Node* getRoot();
    std::string getNameTree();

    void InsertNode(const std::string& parentName, const std::string& childName);
    Node* findNode(Node* node, const std::string& value);
    void display(Node* node, int depth);
    void displayTree();
    void buildTreeFromFile(const std::string& filename, Tree& tree);
    void buildTreeFromConsole(Tree& tree);
    void saveTreeToFile(Node* node, std::ofstream& outputFile);
    void saveTree(const std::string& filename, Node* root);

    bool isEmployeeOfTree(const std::string& employeeName, Node* node);
    bool isEmployeeOfTree(const std::string& employeeName, Tree& tree);

    int numberOfDirectWorkers(const std::string& employeeName, Node* node);
    int numberOfDirectWorkers(const std::string& employeeName, Tree& tree);

    int numberOfIndirectWorkers(const std::string& employeeName, Node* node);
    int numberOfIndirectWorkers(const std::string& employeeName, Tree& tree);

    std::string getNameOfDirectBoss(const std::string& employeeName, Node* node);
    std::string getNameOfDirectBoss(const std::string& employeeName, Tree& tree);

    int numberOfAllEmployees(Node* node);
    int numberOfAllEmployees(Tree& tree);

    int numberOfOverworkedEmployees(Node* node, const int n);
    int numberOfOverworkedEmployees(Tree& tree, const int n);

    void fireEmployee(const std::string& employeeName, Node* node);
    void fireEmployee(const std::string& employeeName, Tree& tree);

    void employNewPerson(const std::string& employeeName, const std::string& bossName, Node* node);
    void employNewPerson(const std::string& employeeName, const std::string& bossName, Tree& tree);
    
    int heightOfTree(Node* node);
    int heightOfTree(Tree& tree);

    void unionOfTrees(Tree& tree1, Tree& tree2, Tree& treeResult);

    int salaryOfEmployee(const std::string& employeeName, Node* node);
    int salaryOfEmployee(const std::string& employeeName, Tree& tree);

    //------------------------------------------------------------------------------------------------------------------------------

    void modernizeTree(Node* node);

    //------------------------------------------------------------------------------------------------------------------------------

    void findTeams(Node* node, std::vector<std::vector<Node*>>& teams);
    void incorporateEmployees(Node* root);
    void help();


};
