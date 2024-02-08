#define CATCH_CONFIG_MAIN
#include "/Catch2-devel/src/catch2/catch_all.hpp"
#include "Tree.h"


TEST_CASE("Test Node Creation") 
{
    Node* node = new Node("TestNode");
    REQUIRE(node->getName() == "TestNode");
    delete node;
}

TEST_CASE("Test Tree Creation") 
{
    Tree* tree = new Tree("TestTree");
    REQUIRE(tree->getNameTree() == "TestTree");
    delete tree;
}

TEST_CASE("Test InsertNode Function") 
{
    Tree tree("TestTree");
    tree.InsertNode("Parent", "Child");

    Node* root = tree.getRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->getName() == "Parent");

    REQUIRE(root->children.size() == 1);
    REQUIRE(root->children[0]->getName() == "Child");
}

TEST_CASE("Test InsertNode") 
{
    Tree tree("TestTree");
    tree.InsertNode("Parent", "Child");

    tree.InsertNode("Parent", "SecondChild");

    Node* root = tree.getRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->getName() == "Parent");

    REQUIRE(root->children.size() == 2);
    REQUIRE(root->children[0]->getName() == "Child");
    REQUIRE(root->children[1]->getName() == "SecondChild");
}

TEST_CASE("Test findNode") 
{
    Tree tree("TestTree");
    tree.InsertNode("A", "B");
    tree.InsertNode("B", "C");
    tree.InsertNode("C", "D");

    Node* nodeB = tree.findNode(tree.getRoot(), "B");
    REQUIRE(nodeB != nullptr);
    REQUIRE(nodeB->getName() == "B");

    Node* nodeD = tree.findNode(tree.getRoot(), "D");
    REQUIRE(nodeD != nullptr);
    REQUIRE(nodeD->getName() == "D");

    Node* nodeE = tree.findNode(tree.getRoot(), "E");
    REQUIRE(nodeE == nullptr);
}

TEST_CASE("Test isEmployeeOfTree") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.isEmployeeOfTree("CEO", tree));
    REQUIRE(tree.isEmployeeOfTree("Manager1", tree));
    REQUIRE(tree.isEmployeeOfTree("Employee1", tree));
    REQUIRE(tree.isEmployeeOfTree("Employee3", tree));
    REQUIRE_FALSE(tree.isEmployeeOfTree("NonExisting", tree));
}

TEST_CASE("Test numberOfDirectWorkers") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.numberOfDirectWorkers("CEO", tree) == 2);
    REQUIRE(tree.numberOfDirectWorkers("Manager1", tree) == 2);
    REQUIRE(tree.numberOfDirectWorkers("Employee1", tree) == 0);
    REQUIRE(tree.numberOfDirectWorkers("Employee3", tree) == 0);
}

TEST_CASE("Test numberOfIndirectWorkers") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.numberOfIndirectWorkers("CEO", tree) == 3);
    REQUIRE(tree.numberOfIndirectWorkers("Manager1", tree) == 0);
}

TEST_CASE("Test getNameOfDirectBoss") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.getNameOfDirectBoss("Manager1", tree) == "CEO");
    REQUIRE(tree.getNameOfDirectBoss("Employee1", tree) == "Manager1");
    REQUIRE(tree.getNameOfDirectBoss("Employee3", tree) == "Manager2");
    REQUIRE(tree.getNameOfDirectBoss("NonExisting", tree).empty());
}

TEST_CASE("Test numberOfAllEmployees") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.numberOfAllEmployees(tree) == 6);
}

TEST_CASE("Test heightOfTree") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.heightOfTree(tree) == 3); 
}

TEST_CASE("Test salaryOfEmployee") 
{
    Tree tree("TestTree");
    tree.InsertNode("CEO", "Manager1");
    tree.InsertNode("CEO", "Manager2");
    tree.InsertNode("Manager1", "Employee1");
    tree.InsertNode("Manager1", "Employee2");
    tree.InsertNode("Manager2", "Employee3");

    REQUIRE(tree.salaryOfEmployee("Manager1", tree) == 1000); 
    REQUIRE(tree.salaryOfEmployee("Manager2", tree) == 500);
    REQUIRE(tree.salaryOfEmployee("CEO", tree) == 1150); 
}