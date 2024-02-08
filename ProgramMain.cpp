#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "Tree.h"

Tree* findTree(std::vector<Tree*>& trees, const std::string& treeToBeFound)
{
    for(Tree* tree : trees)
    {
        if(tree->getNameTree() == treeToBeFound)
        {
            return tree;
        }
    }
    return nullptr;
}

int main()
{
    Tree myTree("myTree");

    myTree.InsertNode("CEO", "Manager1");
    myTree.InsertNode("CEO", "Manager2");
    myTree.InsertNode("Manager1", "Employee1");
    myTree.InsertNode("Manager1", "Employee2");
    myTree.InsertNode("Manager1", "Employee3");
    myTree.InsertNode("Manager2", "George");
    myTree.InsertNode("Manager2", "Phil");
    myTree.InsertNode("Manager2", "Kargov");

    std::vector<Tree*> trees;



    std::string command;
    while (std::cin >> command) 
    {
        if (command == "help") 
        {
            myTree.help();
        } 
        else if (command == "load") 
        {
            std::string objectName, fileName;
            std::cin >> objectName >> fileName;


            Tree tree1(objectName);
            trees.push_back(&tree1);

            if(fileName.size() < 4) //zashtoto .txt e 4 simvola
            {
                (*findTree(trees, objectName)).buildTreeFromConsole(*findTree(trees, objectName));
                // (*findTree(trees, objectName)).displayTree();
            }
            else
            {
                (*findTree(trees, objectName)).buildTreeFromFile(fileName, *findTree(trees, objectName));
                // (*findTree(trees, objeexxitctName)).displayTree();
            }
        } 
        else if (command == "save") 
        {
            std::string objectName, fileName;
            std::cin >> objectName >> fileName;

            if(fileName.size() < 4) //zashtoto .txt e 4 simvola
            {
                (*findTree(trees, objectName)).displayTree();
            }
            else
            {
                (*findTree(trees, objectName)).saveTree(fileName, findTree(trees, objectName)->getRoot());
            }
        } 
        else if (command == "find") 
        {
            std::string objectName, employeeName;
            std::cin >> objectName >> employeeName;

            std::cout << (*findTree(trees, objectName)).isEmployeeOfTree(employeeName, *findTree(trees, objectName)) << std::endl;
        } 
        else if (command == "num_subordinates") 
        {
            std::string objectName, employeeName;
            std::cin >> objectName >> employeeName;

            std::cout << (*findTree(trees, objectName)).numberOfDirectWorkers(employeeName, findTree(trees, objectName)->getRoot()) << std::endl;
        }
        else if (command == "manager") 
        {
            std::string objectName, employeeName;
            std::cin >> objectName >> employeeName;

            (*findTree(trees, objectName)).getNameOfDirectBoss(employeeName, findTree(trees, objectName)->getRoot());
        }
        else if (command == "num_employees") 
        {
            std::string objectName;
            std::cin >> objectName;

            std::cout << (*findTree(trees, objectName)).numberOfAllEmployees(findTree(trees, objectName)->getRoot()) << std::endl;
        }
        else if (command == "overloaded") 
        {
            std::string objectName;
            std::cin >> objectName;

            const int n = 20;

            std::cout << (*findTree(trees, objectName)).numberOfOverworkedEmployees(findTree(trees, objectName)->getRoot(), 20) << std::endl;
        }
        else if (command == "join") 
        {
            std::string objectName1, objectName2, objectResult;
            std::cin >> objectName1 >> objectName2 >> objectResult;

            //(*findTree(trees, objectName)).getNameOfDirectBoss(employeeName, findTree(trees, objectName)->getRoot());
        }
        else if (command == "fire") 
        {
            std::string objectName, employeeName;
            std::cin >> objectName >> employeeName;

            (*findTree(trees, objectName)).fireEmployee(employeeName, findTree(trees, objectName)->getRoot());
        }
        else if (command == "hire") 
        {
            std::string objectName, employeeName, bossName;
            std::cin >> objectName >> employeeName >> bossName;

            (*findTree(trees, objectName)).employNewPerson(employeeName, bossName, findTree(trees, objectName)->getRoot());
        }
        else if (command == "salary") 
        {
            std::string objectName, employeeName;
            std::cin >> objectName >> employeeName;

            std::cout << (*findTree(trees, objectName)).salaryOfEmployee(employeeName, findTree(trees, objectName)->getRoot()) << std::endl;
        }
        else if (command == "incorporate") 
        {
            std::string objectName;
            std::cin >> objectName;

            (*findTree(trees, objectName)).incorporateEmployees(findTree(trees, objectName)->getRoot());
        }
        else if (command == "modernize") 
        {
            std::string objectName;
            std::cin >> objectName;

            (*findTree(trees, objectName)).modernizeTree(findTree(trees, objectName)->getRoot());
        }
        else if (command == "exit") 
        {
            break;
            return 0;
        }
        else 
        {
            std::cout << "Unknown command. Type 'help' for list of commands." << std::endl;
        }
    }


    // std::filesystem::path filepath = "File.txt";
    // if (exists(filepath))
    // {
    //     std::cout << "File path " << filepath << std::endl;
    // }
    // else 
    // {
    //     std::cout << "Not" << std::endl;
    // }

    // myTree.buildTreeFromFile("testFile.txt", myTree); 

    // std::cout << myTree.isEmployeeOfTree("hahahha", myTree) << std::endl;

    // std::cout << myTree.numberOfDirectWorkers("Manager2", myTree) << std::endl;

    // std::cout << myTree.numberOfIndirectWorkers("Manager2", myTree) << std::endl;

    // std::cout << myTree.getNameOfDirectBoss("Kargov", myTree) << std::endl;

    // std::cout << myTree.numberOfAllEmployees(myTree) << std::endl;

    // std::cout << myTree.numberOfOverworkedEmployees(myTree, 2) << std::endl;

    // std::cout << "Tree: " << std::endl; 
    // myTree.displayTree();
    // std::cout << "____________" << std::endl;

    // myTree.fireEmployee("Nishikori", myTree.getRoot());

    // myTree.employNewPerson("Nadal", "Alzaraz", myTree.getRoot());

    // std::cout << myTree.heightOfTree(myTree.getRoot()) << std::endl;

    // std::cout << myTree.salaryOfEmployee("CEO", myTree) << std::endl;

    // myTree.modernizeTree(myTree.getRoot(), myTree.getRoot());

    // myTree.incorporateEmployees(myTree.getRoot());

    // std::cout << "Tree: " << std::endl; 
    // myTree.displayTree(); 

    // myTree.saveTree("File.txt", myTree.getRoot());

    return 0;
}
