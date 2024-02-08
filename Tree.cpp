#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include "Tree.h"

Node::Node(const std::string& value)
{
    this->name = value;
}

Node::~Node()
{
    for(Node* child : children)
    {
        delete child;
    }
}

std::string Node::getName()
{
    return name;
}

Node* Tree::getRoot()
{
    return this->root;
}

std::string Tree::getNameTree()
{
    return this->nameOfTree;
}

Tree::Tree(std::string name)
{
    root = nullptr;
    nameOfTree = name;
}

void Tree::copyNodes(Node*& destination, const Node* source) 
{
    if (source) 
    {
        destination = new Node(source->name);
        for (const Node* child : source->children) 
        {
            Node* childCopy = nullptr;
            copyNodes(childCopy, child);
            destination->children.push_back(childCopy);
        }
    }
}

Tree::Tree()
{
    root = nullptr;
    nameOfTree = "";
}

Tree::Tree(const Tree& other) 
{
    root = nullptr;
    nameOfTree = other.nameOfTree;
    copyNodes(root, other.root);
}

Tree& Tree::operator=(const Tree& other) 
{
    if (this != &other) 
    {
        if (root) 
        {
            delete root;
            root = nullptr;
        }
        nameOfTree = other.nameOfTree;
        copyNodes(root, other.root);
    }
    return *this;
}

Tree::~Tree()
{
    if(root)
    {
        delete root;
    }
}

void Tree::InsertNode(const std::string& parentName, const std::string& childName)
{
    if(!this->root)
    {
        this->root = new Node(parentName);
    }

    Node* parentNode = findNode(root, parentName);
    if(parentNode)
    {
        parentNode->children.push_back(new Node(childName));
    }
    else 
    {
        std::cerr << "Parent node could not be found" << std::endl;
        delete root;
        root = new Node(parentName);
    }
}

Node* Tree::findNode(Node* node, const std::string& name)
{
    if(node->getName() == name)
    {
        return node;
    }

    Node* result = nullptr;
    for(Node* child : node->children)
    {
        result = findNode(child, name);
        if(result)
        {
            break;
        }
    }
    return result;
}

void Tree::display(Node* node, int depth = 0)
{
    if(node)
    {
        std::cout << std::string(depth * 2, ' ') << node->name << std::endl;
        for(Node* child : node->children)
        {
            display(child, depth + 1);
        }
    }
    else 
    {
        std::cerr << "Empty tree" << std::endl;
    }
}

void Tree::displayTree()
{
    display(this->root);
}

void Tree::buildTreeFromFile(const std::string& filename, Tree& tree)
{
    std::ifstream inputFile(filename);

    if(!inputFile.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    
    while(std::getline(inputFile, line))
    {
        std::size_t separatorPosition = line.find('-');
        if(separatorPosition == std::string::npos)
        {
            std::cerr << "Invalid format in file: " << filename << std::endl;
            continue;
        }

        std::string parentName = line.substr(0, separatorPosition);
        std::string childName = line.substr(separatorPosition + 1);
        tree.InsertNode(parentName, childName);
    }

    inputFile.close();
}

void Tree::buildTreeFromConsole(Tree& tree) 
{
    std::string line;
    
    while (std::getline(std::cin, line)) 
    {
        std::size_t separatorPosition = line.find('-');
        if (separatorPosition == std::string::npos) 
        {
            std::cerr << "Invalid format from console input." << std::endl;
            continue;
        }

        std::string parentName = line.substr(0, separatorPosition);
        std::string childName = line.substr(separatorPosition + 1);
        tree.InsertNode(parentName, childName);
    }
}

void Tree::saveTreeToFile(Node* node, std::ofstream& outputFile)
{
    if(!node)
    {
        return;
    }
    for(Node* child : node->children)
    {
        outputFile << node->name << "-" << child->name << "\n";
        saveTreeToFile(child, outputFile);
    }
}

void Tree::saveTree(const std::string& filename, Node* root)
{
    std::ofstream outputFile(filename);
    if(!outputFile.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    saveTreeToFile(root, outputFile);
    outputFile.close();
}



bool Tree::isEmployeeOfTree(const std::string& employeeName, Node* node)
{
    if(!node)
    {
        return false;
    }

    if(node->name == employeeName)
    {
        return true;
    }

    for(Node* child : node->children)
    {
        if(isEmployeeOfTree(employeeName, child))
        {
            return true;
        }
    }
    return false;
}

bool Tree::isEmployeeOfTree(const std::string& employeeName, Tree& tree)
{
    return isEmployeeOfTree(employeeName, tree.getRoot());
}

int Tree::numberOfDirectWorkers(const std::string& employeeName, Node* node)
{
    if(!node)
    {
        return 0;
    }

    int directWorkers = 0;

    if(node->name == employeeName)
    {
        directWorkers = node->children.size();
    }

    for(Node* child : node->children)
    {
        directWorkers += numberOfDirectWorkers(employeeName, child);
    }

    return directWorkers;
}

int Tree::numberOfDirectWorkers(const std::string& employeeName, Tree& tree)
{
    return numberOfDirectWorkers(employeeName, tree.getRoot());
}

int Tree::numberOfIndirectWorkers(const std::string& employeeName, Node* node)
{
    if (!node) 
    {
        return 0;
    }

    return (numberOfAllEmployees(findNode(node, employeeName)) - 1) - numberOfDirectWorkers(employeeName, node);
}

int Tree::numberOfIndirectWorkers(const std::string& employeeName, Tree& tree)
{
    return numberOfIndirectWorkers(employeeName, tree.getRoot());
}

std::string Tree::getNameOfDirectBoss(const std::string& employeeName, Node* node)
{
    if(!node)
    {
        return "";
    }

    for(Node* child : node->children)
    {
        if(child->name == employeeName)
        {
            return node->name;
        }
    }

    for(Node* child : node->children)
    {
        std::string searchedName = getNameOfDirectBoss(employeeName, child);
        if(!searchedName.empty())
        {
            return searchedName;
        }
    }
    return "";
}

std::string Tree::getNameOfDirectBoss(const std::string& employeeName, Tree& tree)
{
    return getNameOfDirectBoss(employeeName, tree.getRoot());
}

int Tree::numberOfAllEmployees(Node* node)
{
    if(!node)
    {
        return 0;
    }

    int counter = 1;

    for(Node* child : node->children)
    {
        counter += numberOfAllEmployees(child);
    }

    return counter;
}

int Tree::numberOfAllEmployees(Tree& tree)
{
    return numberOfAllEmployees(tree.getRoot());
}

int Tree::numberOfOverworkedEmployees(Node* node, const int n)
{
    if(!node)
    {
        return 0;
    }

    int counter = 0;

    if(numberOfAllEmployees(node) > n)
    {
        counter++;
    }

    for(Node* child : node->children)
    {
        counter += numberOfOverworkedEmployees(child, n);
    }

    return counter;
}

int Tree::numberOfOverworkedEmployees(Tree& tree, const int n)
{
    return numberOfOverworkedEmployees(tree.getRoot(), n);
}

void Tree::fireEmployee(const std::string& employeeName, Node* node) 
{
    Node* employeeToFire = findNode(node, employeeName);
    Node* newBoss = nullptr;

    if (!employeeToFire) {
        std::cout << "Employee not found!" << std::endl;
        return;
    }

    if (employeeToFire == node) {
        std::cout << "CEO cannot be fired!" << std::endl;
        return;
    }

    newBoss = findNode(node, getNameOfDirectBoss(employeeName, node));

    if (newBoss) 
    {
        newBoss->children.insert(newBoss->children.end(), employeeToFire->children.begin(), employeeToFire->children.end());
    }

    if (newBoss) 
    {
        std::vector<Node*>::iterator it = std::find(newBoss->children.begin(), newBoss->children.end(), employeeToFire);
        if(it != newBoss->children.end()) 
        {
            newBoss->children.erase(it);
        }
    }
}

void Tree::fireEmployee(const std::string& employeeName, Tree& tree)
{
    if(tree.getRoot()->name == employeeName)
    {
        std::cerr << "Can not fire the CEO" << std::endl;
        return;
    }

    //fireEmployee(employeeName, tree.getRoot());
}

void Tree::unionOfTrees(Tree& tree1, Tree& tree2, Tree& treeResult)
{

}

void Tree::employNewPerson(const std::string& employeeName, const std::string& bossName, Node* node)
{
    if(!node)
    {
        return;
    }

    if(isEmployeeOfTree(employeeName, node) && findNode(node, employeeName)->children.size() == 0)
    {

        fireEmployee(employeeName, node);
        findNode(node, bossName)->children.push_back(new Node(employeeName));
    }
    if(isEmployeeOfTree(employeeName, node) && findNode(node, employeeName)->children.size() != 0)
    {
        Node* employeeToTransfer = findNode(node, employeeName);
        Node* newBoss = findNode(node, bossName);

        if (employeeToTransfer && newBoss) {
            std::string oldBossName = getNameOfDirectBoss(employeeName, node);
            
            Node* oldBoss = findNode(node, oldBossName);
            if (oldBoss) 
            {
                std::vector<Node*>::iterator it = std::find(oldBoss->children.begin(), oldBoss->children.end(), employeeToTransfer);
                if (it != oldBoss->children.end()) 
                {
                    oldBoss->children.erase(it);
                }
            }
            newBoss->children.push_back(employeeToTransfer);
        }
    }
    if(!isEmployeeOfTree(employeeName, node))
    {
        findNode(node, bossName)->children.push_back(new Node(employeeName));
    }

}

void Tree::employNewPerson(const std::string& employeeName, const std::string& bossName, Tree& tree)
{
    if(tree.getRoot()->name == bossName) 
    {
        std::cout << "Cannot assign a new boss to the CEO." << std::endl;
        return;
    }
    //employNewPerson(employeeName, bossName, tree.getRoot());
}

int Tree::heightOfTree(Node* node)
{
    if(!node)
    {
        return 0;
    }
    int maxHeight = 0;

    for(Node* child : node->children)
    {
        int height = heightOfTree(child);
        maxHeight = std::max(maxHeight, height);
    }

    return maxHeight + 1;
}

int Tree::heightOfTree(Tree& tree)
{
    return heightOfTree(tree.getRoot());
}

int Tree::salaryOfEmployee(const std::string& employeeName, Node* node)
{
    int directWorkers = numberOfDirectWorkers(employeeName, node);
    int indirectWorkers = numberOfIndirectWorkers(employeeName, node);

    return (500 * directWorkers) + (50 * indirectWorkers);
}

int Tree::salaryOfEmployee(const std::string& employeeName, Tree& tree)
{
    return salaryOfEmployee(employeeName, tree.getRoot());
}


//------------------------------------------------------------------------------------------------------------------------------


void Tree::modernizeTree(Node* node)
{

}

//------------------------------------------------------------------------------------------------------------------------------
void Tree::findTeams(Node* node, std::vector<std::vector<Node*>>& teams) 
{
    if (!node) 
    {
        return;
    }

    for (Node* child : node->children) 
    {
        findTeams(child, teams);
    }

    if (node->children.size() > 1) 
    {
        teams.push_back(node->children);
    }
}

void Tree::incorporateEmployees(Node* node) 
{
    std::vector<std::vector<Node*>> teams;
    findTeams(node, teams);

    for (int i = teams.size() - 1; i >= 0; --i) 
    {
        std::vector<Node*>& team = teams[i];
        Node* teamLeader = nullptr;
        int maxSalary = 0;

        for (Node* member : team) 
        {
            if (salaryOfEmployee(member->name, node) > maxSalary || (salaryOfEmployee(member->name, node) == maxSalary && (teamLeader == nullptr || member->name < teamLeader->name))) 
            {
                maxSalary = salaryOfEmployee(member->name, node);
                teamLeader = member;
            }
        }

        if (teamLeader) 
        {
            for (Node* member : team) 
            {
                if (member != teamLeader) 
                {
                    std::string oldBossName = getNameOfDirectBoss(member->name, node);
                    Node* oldBoss = findNode(node, oldBossName);

                    if (oldBoss) 
                    {
                        std::vector<Node*>::iterator it = std::find(oldBoss->children.begin(), oldBoss->children.end(), member);
                        if (it != oldBoss->children.end()) 
                        {
                            oldBoss->children.erase(it);
                        }
                    }

                    Node* newBoss = findNode(node, teamLeader->name);

                    if (newBoss) 
                    {
                        newBoss->children.push_back(member);
                    }
                }
            }
        }
    }
}

void Tree::help()
{
    std::cout << "load <име_на_обект> <име_на_файл> – зарежда данни за йерархия от файл с подаденото име и създава дърво, асоциирано с име_на_обект. Това име трябва да се състои само от малки и главни латински букви, цифри и символ за подчертаване. След него всичко до края на реда е името на файла от който трябва да прочетете данните в описания по-горе формат. Ако името на файла липсва се предполага да прочетете данните от стандартния вход, до срещане на край на файл (Ctrl+z/Ctrl+d).\n";

    std::cout << "save <име_на_обект> <име_на_файл> – записва информацията за йерархията на посочения обект във файл с посоченото име. Ако името на файла е празно, информацията да се изведе на стандартния изход.\n";

    std::cout << "find <име_на_обект> <име_на_служител> – проверява дали в посочения обект съществува служител с посоченото име.\n";

    std::cout << "num_subordinates <име_на_обект> <име_на_служител> – извежда броя преки подчинени на дадения служител  в посочения обект.\n";

    std::cout << "manager <име_на_обект> <име_на_служител> – извежда името на ръководителя на дадения служител  в посочения обект.\n";

    std::cout << "num_employees <име_на_обект> – извежда броя служители в посочения обект.\n";

    std::cout << "overloaded <име_на_обект> – извежда броя служители в посочения обект, за които броят подчинени (преки или не) е по-голям от 20.\n";

    std::cout << "join <име_на_обект_1> <име_на_обект_2> <име_на_обект_резултат> – обединява двата подадени обекта в нов обект с име <име_на_обект_резултат>.\n";

    std::cout << "fire <име_на_обект> <име_на_служител> – премахва служителя от съответния обект.\n";

    std::cout << "hire <име_на_обект> <име_на_служител> <име_на_ръководител> – назначава служителя в съответния обект като подчинен на подадения ръководител.\n";

    std::cout << "salary <име_на_обект> <име_на_служител> – извежда заплатата на служителя.\n";

    std::cout << "incorporate <име_на_обект> – инкорпорира фирмата; операцията се прилага върху обекта <име_на_обект>.\n";

    std::cout << "modernize <име_на_обект> – модернизира фирмата; операцията се прилага върху обекта <име_на_обект>.\n";

    std::cout << "exit - прекратява изпълнението на програмата. За всички нови или променени след зареждането обекти попитайте потребителя дали иска да ги запази във файл.\n";

}