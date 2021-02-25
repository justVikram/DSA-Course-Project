#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct date
{
   int month;
   int day;
   int year;
}
DATE;

typedef struct Subtask
{
    char SubtaskTitle [40];
    int IsCompleted;
}
SUBTASK;

typedef struct SubtaskNode
{
    SUBTASK SubtaskDetails;
    struct SubtaskNode * next;
}
SUBTASK_NODE;

typedef struct Task
{
    char TaskTitle [40];                        // To store the actual task
    DATE ScheduledDate;
    int IsCompleted;                            // 1 -> Completed, 0 -> Not completed
    SUBTASK_NODE * ListOfSubtasks;
}
TASK;

typedef struct TaskNode
{
    TASK  TaskDetails;
    struct TaskNode * next;
}
TASK_NODE;

int compareDates (DATE d1, DATE d2)
{
    if (d1.year < d2.year)
       return -1;

    else if (d1.year > d2.year)
       return 1;

    if (d1.year == d2.year)
    {
         if (d1.month<d2.month)
              return -1;
         else if (d1.month>d2.month)
              return 1;
         else if (d1.day<d2.day)
              return -1;
         else if(d1.day>d2.day)
              return 1;
         else
              return 0;
    }
    else
        return 0;
}

//MARK:-

static void initListOfTasks (TASK_NODE ** ListOfTasks)
{
    ListOfTasks = NULL;
}

static void initTaskDetails (TASK ** ExistingTask)
{
    strcpy ((*ExistingTask)->TaskTitle, "<enter task title here>");

    (*ExistingTask)->ScheduledDate.day = 00;
    (*ExistingTask)->ScheduledDate.month = 00;
    (*ExistingTask)->ScheduledDate.year = 0000;
    
    (*ExistingTask)->IsCompleted = 0;
    (*ExistingTask)->ListOfSubtasks = NULL;
    
}

static void initSubtaskDetails (SUBTASK ** ExistingSubtask)
{
    strcpy ((*ExistingSubtask)->SubtaskTitle, "<enter subtask title here>");
    (*ExistingSubtask)->IsCompleted = 0;
}

//MARK:-

static void readNewTask (TASK_NODE ** NewTask)
{
    
}

static void addNewTask (TASK_NODE ** ListOfTasks, TASK_NODE * NewTask)
{
    //ADD AT POSITION
}

static void viewTask (const TASK_NODE * ExistingTask)
{
    
}

static void viewListOfTasks (const TASK_NODE * ListOfTasks)
{
    //IN ASCENDING ORDER BY DATE
}

static void viewTasksOnGivenDate (const TASK_NODE * ListOfTasks, DATE ScheduledDate)
{
    
}

static void viewCompletedTasks (const TASK_NODE * ListOfTasks)
{
    const TASK_NODE *cur = ListOfTasks;
    SUBTASK_NODE *cur1;

    while (cur)
    {
        if (cur->TaskDetails.IsCompleted == 1)
        {
            printf("%s\n", cur->TaskDetails.TaskTitle);
            cur1 = cur->TaskDetails.ListOfSubtasks;
            while (cur1)
            {
                printf("%s\n", cur1->SubtaskDetails.SubtaskTitle);

                cur1 = cur1->next;
            }
        }
        cur = cur->next;
    }
}

static int searchByTaskTitle(const TASK_NODE *ListOfTasks, char TaskTitle[])
{
    const TASK_NODE *cur = ListOfTasks;
    while (cur)
    {
        if (strcmp (cur->TaskDetails.TaskTitle, TaskTitle) == 0)
            return 1;
            
        cur = cur->next;
    }
    return 0;
}

static void markTaskAsCompleted (TASK_NODE ** ListOfTasks, char TaskTitle [])
{
    TASK_NODE *cur = (*ListOfTasks);

    while (cur && (strcmp(cur->TaskDetails.TaskTitle, TaskTitle)) != 0)
    {

        cur = cur->next;
    }
    if (cur)
    {
        cur->TaskDetails.IsCompleted = 1;
        SUBTASK_NODE *ListOfSubtasks = cur->TaskDetails.ListOfSubtasks;

        while (ListOfSubtasks)
        {
            ListOfSubtasks->SubtaskDetails.IsCompleted = 1;
            ListOfSubtasks = ListOfSubtasks->next;
        }
    }
}

static void markAllTasksAsCompleted (TASK_NODE ** ListOfTasks)
{
    TASK_NODE *cur = (*ListOfTasks);
    SUBTASK_NODE *cur1;
    while (cur)
    {
        cur->TaskDetails.IsCompleted = 1;
        cur1 = cur->TaskDetails.ListOfSubtasks;
        while (cur1)
        {
            cur1->SubtaskDetails.IsCompleted = 1;
            cur1 = cur1->next;
        }
        cur = cur->next;
    }
}

static void deleteTaskFromList (TASK_NODE ** ListOfTasks, char TaskTitle [])
{
    TASK_NODE *cur = *ListOfTasks;
    TASK_NODE *prev = NULL;
    while (cur)
    {
        if (strcmp(cur->TaskDetails.TaskTitle, TaskTitle) == 0)
        {
            if (cur == *ListOfTasks)
            {
                *ListOfTasks = cur->next;
                free(cur);
            }
            else
            {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

//MARK:-

static void readNewSubtask (SUBTASK_NODE ** NewSubtask)
{
    printf ("Enter subtask title:");
    scanf ("%s", (*NewSubtask)->SubtaskDetails.SubtaskTitle);
}

static void viewSubtask (const SUBTASK_NODE * ExistingSubtask)
{
    printf ("%s", ExistingSubtask->SubtaskDetails.SubtaskTitle);
}

static void addNewSubtask (TASK_NODE ** ExistingTask, SUBTASK_NODE * NewSubtask)
{
    if (! (*ExistingTask)->TaskDetails.ListOfSubtasks)
        (*ExistingTask)->TaskDetails.ListOfSubtasks = NewSubtask;
    
    else
    {
        SUBTASK_NODE * cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
        
        while (cur->next)
            cur = cur->next;
        
        cur->next = NewSubtask;
    }
}

static void viewListOfSubtasks (const TASK_NODE * ExistingTask)
{
    int i = 1;
    SUBTASK_NODE * cur = ExistingTask->TaskDetails.ListOfSubtasks;
    
    while (cur)
    {
        printf ("Subtask %d:\n", i++);
        viewSubtask (cur);
    }
}

static void markSubtaskAsCompleted (TASK_NODE ** ExistingTask, char SubtaskTitle [])
{
    SUBTASK_NODE * cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    
    while (cur && (strcmp (cur->SubtaskDetails.SubtaskTitle, SubtaskTitle) != 0))
        cur = cur->next;
    
    if (! cur)
        printf ("ERROR -- Check the title and try again.\n");
    
    else
        cur->SubtaskDetails.IsCompleted = 1;
}

static void markAllSubtasksAsCompleted (TASK_NODE ** ExistingTask)
{
    SUBTASK_NODE *cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    while (cur)
    {
        cur->SubtaskDetails.IsCompleted = 1;
        cur = cur->next;
    }
}

static void deleteSubtask (SUBTASK_NODE ** ListOfSubtasks, char SubtaskTitle [])
{
     SUBTASK_NODE *cur = *ListOfSubtasks;
    SUBTASK_NODE *prev = NULL;
    while (cur)
    {
        if (strcmp(cur->SubtaskDetails.SubtaskTitle, SubtaskTitle) == 0)
        {
            if (cur == *ListOfSubtasks)
            {
                *ListOfSubtasks = cur->next;
                free(cur);
            }
            else
            {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

static void deleteSubtaskList (TASK_NODE ** ExistingTask)
{
    SUBTASK_NODE *head = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    SUBTASK_NODE *cur = head;
    while (cur)
    {
        head = cur->next;
        free(cur);
        cur = head;
    }
}

//MARK:-

static int isLeapYear (int y)
{
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

static int leapYears (int y)
{
    return y/4 - y/100 + y/400;
}

static int todayOf (int y, int m, int d)
{
    static int DayOfMonth[] = {-1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    return DayOfMonth[m] + d + ((m > 2 && isLeapYear (y))? 1 : 0);
}

static long days (int y, int m, int d)
{
    int lastYear;
    lastYear = y - 1;
    
    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}

static void calendar (int y, int m) /* display calendar at m y */
{
    const char *NameOfMonth[] = {NULL, "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    
    char Week[] = "Su Mo Tu We Th Fr Sa";
    
    int DayOfMonth[] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i, day;
    
    weekOfTopDay = days (y, m, 1) % 7;
    
    if (isLeapYear (y))
        DayOfMonth [2] = 29;
    
    printf ("\n     %s %d\n%s\n", NameOfMonth[m], y, Week);
    
    for (i = 0; i < weekOfTopDay; i++)
        printf("   ");
    
    for (i = weekOfTopDay, day = 1; day <= DayOfMonth [m]; i++, day++)
    {
        printf ("%2d ", day);
        
        if(i % 7 == 6)
            printf("\n");
    }
    printf("\n");
}

//MARK:-

int main (int argV, const char * argC [])
{
    TASK_NODE * ListOfTasks;
    
    /*                                                          TO DISPLAY CALENDAR FOR A MONTH
    int year,month;
    
    printf("Enter the month and year: ");
    scanf("%d %d", &month, &year);
    
    calendar(year, month);
    
    return 0;
     */
}
