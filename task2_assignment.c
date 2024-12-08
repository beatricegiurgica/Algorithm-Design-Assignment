/*
An engineering company manufactures aeronautical equipment on 4 different production lines at its factory in Dublin.  
The production line is sophisticated and audited to the highest quality standards.  
Each production line is used for the manufacture of multiple products in a multi-stage production process which ends when the product is packed for dispatch.
Quality Assurance (QA) is important to the company. Each product is manufactured in a single identified batch (group) and faults or issues identified at every
stage are logged and tracked by a QA engineer.
Working in the company's IT department, you have been given access to the QA logs of each production line. You have been asked to assist the management team 
in analysing the QA data from the manufacturing process. The QA logs contain the following data and are newly created for each month: 

a.	Line Code – Numeric
b.	Batch code - Numeric
c.	Batch date & time – numbered for day of month, hour of day, minute of hour.
d.	Product Id - numeric
e.	Issue Code & description - numeric + text
f.	Resolution code & description – numeric + text
g.	Reporting employee id – numeric

Design Requirements - Task 2
- Due to changes in the manufacturing process, the same product can be manufactured on different lines.
  Prepare a report which uses a single list to report Issue Codes by Product Id and Line Code for all production lines.
- There are huge amounts of data stored, the running time of this algorithm should be O(N) or better.


Beatrice Maria Giurgica 

02/04/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define DateTime structure
struct DateTime
{      
    int dayofmonth;
    int hourofday;
    int minuteofhour;
};

// Define ProductionLine_Log structure
struct ProductionLine_Log 
{
    int LineCode;
    int BatchCode;
    struct DateTime BatchDateTime;
    int ProductId;
    int IssueCode;
    char IssueDescription[100];
    int ResolutionCode;
    char ResolutionDescription[100];
    int ReportingEmployeeId;
};

// Define a linked list node for production line logs
struct Node 
{
    struct ProductionLine_Log data;
    struct Node *next;
};

// Function to insert a log into the linked list while maintaining order based on Product ID and Line Code
void insertLog(struct Node **head, struct ProductionLine_Log log) 
{
    // Allocate memory for the new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }

   
    newNode->data = log; // Assign log data to the new node
    newNode->next = NULL; // Set next node in the list to be last node in the list

    struct Node *current = *head;
    struct Node *prev = NULL;

    // Navigate through the list to find the correct position based on Product ID and Line Code
    while (current != NULL && (current->data.ProductId < newNode->data.ProductId || (current->data.ProductId == newNode->data.ProductId && current->data.LineCode < newNode->data.LineCode))) 
    {
        prev = current;
        current = current->next; // Move from current to next node in the list
    }   

    // Insert newNode at the correct position
    if (prev == NULL) 
    {
        newNode->next = *head; // newNode points to the head of the list
        *head = newNode; // newNode becomes the new head of the list
    } else 
    {
        prev->next = newNode; // newNode is placed after prev
        newNode->next = current; // newNode is placed before current
    }
}

// Function to generate and print the report
void generateReport(struct Node *head) 
{
    struct Node *current = head;
    printf("QA Report:\n");

    // Print log details
    while (current != NULL) 
    {
        printf("Product ID: %d  Line Code: %d  Issue Code: %d\n", current->data.ProductId, current->data.LineCode, current->data.IssueCode);
        current = current->next;
    }
}

int main() {
    // Example ProductionLine_Log array
    struct ProductionLine_Log logs_data[] = 
    {
        {1, 101, {1, 20, 45}, 1001, 10, "Defect in wing", 10, "Resolved by replacing faulty component", 100},
        {2, 102, {1, 5, 45}, 1003, 12, "Fire detection system malfunction", 12, "Resolved by conducting system testing", 105},
        {5, 105, {1, 11, 45}, 1002, 15, "Engine malfunction", 15, "Resolved by replacing affected parts", 102},
        {1, 107, {1, 7, 45}, 1001, 1, "Product damage", 1, "Resolved by adding final quality checks", 100},
        {9, 102, {1, 16, 45}, 1003, 3, "Shipping delay", 3, "Resolved by increasing number of couriers", 105},
        {6, 103, {1, 23, 45}, 1005, 15, "Engine malfunction", 15, "Resolved by replacing affected parts", 102},
        {1, 111, {1, 10, 45}, 1001, 17, "Transportation issue", 17, "Resolved by improving transportation methods", 100},
        {3, 116, {1, 6, 45}, 1006, 20, "Customer complaint", 20, "Resolved with personalised solutions", 105},
        {1, 109, {1, 22, 45}, 1002, 15, "Engine malfunction", 15, "Resolved by replacing affected parts", 102},
        {8, 107, {1, 21, 45}, 1005, 6, "Labelling issue", 6, "Resolved by implementing revised labelling procedures", 100},
        {7, 112, {1, 18, 45}, 1001, 12, "Fire detection system malfunction", 12, "Resolved by conducting system testing", 105},
        {1, 108, {1, 4, 45}, 1007, 30, "Staff shortage", 30, "Resolved by hiring temporary staff", 102},    
    };

    // Determine the number of logs in the array to ensure that the logs_number variable holds the correct number of logs, even if the size of the array changes in the future
    int logs_number = sizeof(logs_data) / sizeof(logs_data[0]);

    // Create an empty linked list
    struct Node *head = NULL;

    // Insert logs into the linked list while maintaining order
    for (int i = 0; i < logs_number; i++) 
    {
        insertLog(&head, logs_data[i]);
    }

    // Generate and print the report
    generateReport(head);

    return 0;
}