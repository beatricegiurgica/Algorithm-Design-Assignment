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

Design Requirements - Task 1
- The production line logs are either ordered by date & time or may be in a random order for each day. Prepare a report for each line in Product id, Issue code, 
  date & time order.
- There are huge amounts of data stored, the running time of this algorithm should be O(NLog(N)) or better.


Beatrice Maria Giurgica 

01/04/2024
*/

#include <stdio.h>
#include <stdlib.h>


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


// Merge two subarrays of logs_data[]
// First subarray goes from left to mid
// Second subarray goes from mid+1 to right
void merge(struct ProductionLine_Log logs_data[], int left, int mid, int right) 
{
    int i, j, k;
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Create temporary arrays
    struct ProductionLine_Log temp_left[left_size], temp_right[right_size];

    // Copy data to temporary arrays temp_left[] and temp_right[]
    for (i = 0; i < left_size; i++)
    {
        temp_left[i] = logs_data[left + i];
    }
    for (j = 0; j < right_size; j++)
    {
        temp_right[j] = logs_data[mid + 1 + j];
    }

    // Merge the temporary arrays back into logs_data[]
    i = 0; //initial index of first subarray
    j = 0; //initial index of second subarray
    k = left; //initial index of merged subarray
    while (i < left_size && j < right_size) 
    {
        // Compare based on hierarchical order of sorting criteria: Product ID, Issue Code and Batch Date & Time
        if (temp_left[i].ProductId < temp_right[j].ProductId || 
            (temp_left[i].ProductId == temp_right[j].ProductId && temp_left[i].IssueCode < temp_right[j].IssueCode) ||
            (temp_left[i].ProductId == temp_right[j].ProductId && temp_left[i].IssueCode == temp_right[j].IssueCode && 
            (temp_left[i].BatchDateTime.dayofmonth < temp_right[j].BatchDateTime.dayofmonth ||
            (temp_left[i].BatchDateTime.dayofmonth == temp_right[j].BatchDateTime.dayofmonth &&
            (temp_left[i].BatchDateTime.hourofday < temp_right[j].BatchDateTime.hourofday ||
            (temp_left[i].BatchDateTime.hourofday == temp_right[j].BatchDateTime.hourofday &&
            temp_left[i].BatchDateTime.minuteofhour < temp_right[j].BatchDateTime.minuteofhour))))))
        {
            logs_data[k] = temp_left[i];
            i++;
        }
        else 
        {
            logs_data[k] = temp_right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of temp_left[], if there are any
    while (i < left_size) 
    {
        logs_data[k] = temp_left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of temp_right[], if there are any
    while (j < right_size) 
    {
        logs_data[k] = temp_right[j];
        j++;
        k++;
    }
}


// Merge Sort function to sort logs_data[] based on Product ID, Issue Code and Batch Date & Time
void mergeSort(struct ProductionLine_Log logs_data[], int left, int right) 
{
    if (left < right) 
    {
        // Divide array into smaller subarrays by calculating its middle index
        int mid = left + (right - left) / 2;

        // Sort left and right halves
        mergeSort(logs_data, left, mid);
        mergeSort(logs_data, mid + 1, right);

        // Merge sorted halves
        merge(logs_data, left, mid, right);
    }
}


// Function to print the sorted report
void printReport(struct ProductionLine_Log logs_data[], int size) 
{
    printf("Sorted Production Line Report:\n");

    for (int i = 0; i < size; i++) 
    {
        printf("Product ID: %d\n", logs_data[i].ProductId);
        printf("Issue Code: %d\n", logs_data[i].IssueCode);
        printf("Date & Time: %d (day of the month) %d:%d (time)\n", logs_data[i].BatchDateTime.dayofmonth, logs_data[i].BatchDateTime.hourofday, logs_data[i].BatchDateTime.minuteofhour);
        printf("\n");
    }
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

    // Display logs_data
    printf("Unsorted Production Line Report:\n");

    for (int i = 0; i < logs_number; i++) 
    {
        printf("Production Line: %d\n", logs_data[i].LineCode);
        printf("Batch Code: %d\n", logs_data[i].BatchCode);
        printf("Batch Date & Time: %d (day of the month) %d:%d (time)\n", logs_data[i].BatchDateTime.dayofmonth, logs_data[i].BatchDateTime.hourofday, logs_data[i].BatchDateTime.minuteofhour);
        printf("Product ID: %d\n", logs_data[i].ProductId);
        printf("Issue Code: %d\n", logs_data[i].IssueCode);
        printf("Issue Description: %s\n", logs_data[i].IssueDescription);
        printf("Resolution Code: %d\n", logs_data[i].ResolutionCode);
        printf("Resolution Description: %s\n", logs_data[i].ResolutionDescription);
        printf("Reporting Employee ID: %d\n", logs_data[i].ReportingEmployeeId);
        printf("\n");
    }

    // Perform merge sort on logs_data based on Product ID
    mergeSort(logs_data, 0, logs_number - 1);

    // Print the sorted report
    printReport(logs_data, logs_number);

    return 0;
}