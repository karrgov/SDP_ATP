ATP Tennis Association Simulator (ATP) - C++

Welcome to the ATP Tennis Association Simulator! 
This program is written in C++ and simulates the operations of the Association of Tennis Professionals (ATP). 
Users can create and manage their own different tennis associations.

Features

load <object_name> <file_name> – loads data for a hierarchy from the specified file and creates a tree associated with the object name.

save <object_name> <file_name> – writes the information about the hierarchy of the specified object to the specified file.

find <object_name> <employee_name> – checks if an employee with the specified name exists in the specified object.

num_subordinates <object_name> <employee_name> – outputs the number of direct subordinates of the given employee in the specified object.

manager <object_name> <employee_name> – outputs the name of the manager of the given employee in the specified object.

num_employees <object_name> – outputs the number of employees in the specified object.

overloaded <object_name> – outputs the number of employees in the specified object for which the number of subordinates (direct or not) is greater than 20.

join <object_name_1> <object_name_2> <result_object_name> – merges the two specified objects into a new object with the specified result object name.

fire <object_name> <employee_name> – removes the employee from the specified object.

hire <object_name> <employee_name> <manager_name> – assigns the employee in the specified object as a subordinate of the specified manager.

salary <object_name> <employee_name> – outputs the salary of the specified employee.

incorporate <object_name> – incorporates the company; operation applied on the specified object.

modernize <object_name> – modernizes the company; operation applied on the specified object.

exit - terminates the program execution. Ask the user if they want to save any new or modified objects after loading.

User-friendly Interface: The program provides an intuitive command-line interface for easy interaction.
The program also has comprehensive unit testing done.

