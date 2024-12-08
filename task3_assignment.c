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

Design Requirements - Task 3
- Provide a facility to search for the earliest occurrence of an issue code for a given product id across all production lines.
- There are huge amounts of data stored, the running time of this algorithm should be O(Log(N)) or better.


Beatrice Maria Giurgica 

03/04/2024
*/

#include <stdio.h>

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

// Binary search function to find the earliest occurrence of issue code for a product ID
int searchEarliestOccurrence(struct ProductionLine_Log logs_data[], int logs_number, int productID)
{
    int left = 0;
    int right = logs_number - 1;
    int earliestIndex = -1; // Value not found yet

    while (left <= right)
    {
        // Calculate mid point
        int mid = left + (right - left) / 2;

        // Check if the current log matches the productID
        if (logs_data[mid].ProductId == productID)
        {
            earliestIndex = mid;
            return earliestIndex;
        }
        else if (logs_data[mid].ProductId > productID)
        {
            // Search in the left subarray
            right = mid - 1;  // Update right value of left subarray to restrict the search
        }
        else
        {
            // Search in the right subarray
            left = mid + 1;  // Update left value of right subarray to restrict the search
        }
    }

    return earliestIndex;
}

int main()
{
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

    int productID;
    printf("Enter Product ID to search: ");
    scanf("%d", &productID);

    // Perform binary search for earliest occurrence
    int earliestIndex = searchEarliestOccurrence(logs_data, logs_number, productID);

    if (earliestIndex != -1)
    {
        printf("Earliest occurrence of Product ID %d found at index %d\n", productID, earliestIndex);
        printf("Related Issue Code: %d\n", logs_data[earliestIndex].IssueCode);
    }
    else
    {
        printf("Product ID %d not found in logs.\n", productID);
    }

    return 0;
}

