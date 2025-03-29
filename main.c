/*
 * Name : Nour moudi
 * ID : 1211080
 * Section : 4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node{
    int data;
    struct node* Pre;
    struct node* Next;
};
typedef struct node* D;// new type "D" which is a pointer to struct node

int isEmpty(struct node* head);
void printList(struct node* header);
void add(D header, int x);
void addFirst(D head, int x);
D FindLast(D head);
void DeleteNode(D head,D node);
void Filter(struct node *l1);
int compare(D head1, D head2);
D AddTwoNumbers(D head1,D head2);
void borrow(D head,D digit);
D SubtractTwoNumbers(D head1,D head2);
void DeleteList(struct node* N);
struct node* makeEmpty(struct node* N);
D MultiplyTwoNumbers(D head1,D head2);
D DivideTwoNumbers(D head1, D head2, FILE *q);
void OpenFileAndDoOpreation(FILE *q);
int repeatedSubtraction (D l1, D l2);
void emptyList (D N);
D copyList (D l1, D l2);
void printNumber_file (struct node *L, FILE *q);

int main() {

    FILE* printFile;
    printFile= fopen("output.txt","a");
    D result;

    OpenFileAndDoOpreation(printFile);
    fclose(printFile);

}


// this function is to check if the given linked list is empty or not
int isEmpty(struct node* head){
    return head->Next == NULL;
}

/* This function takes a pointer to the header
 * node of a linked list and prints the data values of
 * all the nodes in the list. If the list is empty, it prints
 * a message indicating that the list is empty. */
void printList(struct node* header){

    struct node* temp;
    temp=header->Next;

    if(isEmpty(header)){

        printf("The list is empty!");
        return;
    }

    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->Next;
    }
}

/* This function adds a new node with the data value
 * 'x' to the end of a doubly linked list. The
 * function takes a pointer to the header node of
 * the list and the value 'x' to be added. */
void add(D header, int x) {
// Set the data value and Next pointer of the new node
    D temp;
    D new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = x;
    new_node->Next = NULL;
// Check if the list is empty
    if (header->Next == NULL) {
        header->Next = new_node;
        new_node->Pre = header;
    }
    else {
        // Start traversing the list from the first node after the header
        temp = header->Next;
        // Traverse to the last node in the list
        while (temp->Next != NULL) {
            temp = temp->Next;
        }
        temp->Next = new_node;
        new_node->Pre=temp;
    }
}
/*this function to add a new node in the linked
 * list ant insert 'x' on it*/
void addFirst(D head, int x){

    D new_node = (D)malloc(sizeof(struct node));
    new_node->data = x;
    new_node->Next = head->Next;
    new_node->Pre = head;
    //check if the list is empty
    if(head->Next != NULL){
        head->Next->Pre = new_node;
    }
    if(head->Next==NULL){
        new_node->Next=NULL;
    }
    head->Next = new_node;
}
// this function to find the last node in the linked list
D FindLast(D head){
    D temp;
    temp=head->Next;
    while (temp->Next!=NULL){
        temp=temp->Next;
    }
    return temp;
}
/* This function deletes a specific node from a doubly linked list.
 * It takes the head pointer of the list (head)
 * and the node to be deleted (node). */
void DeleteNode(D head,D node){
    D temp;
    temp=head->Next;
    while(temp!=node){
        temp=temp->Next;
    }
    temp->Pre->Next=temp->Next;
    temp->Next->Pre=temp->Pre;
    free(temp);


}
/*this function to delete all the zeroes in the right of  the number
 * for example if the function takes "000123"
 * it will return "123"*/
void Filter (struct node *l1) {

    struct node* digit = l1->Next;


    while (digit->data == 0 && digit->Next != NULL) {
        DeleteNode(l1,digit);
        digit = l1->Next;
    }
}
/* This function compares two doubly linked lists (head1 and head2) and
 * returns an integer value based on the comparison result. */
int compare(D head1, D head2) {

    D temp1 = head1->Next;
    D temp2 = head2->Next;
    int count1 = 0, count2 = 0;
// Count the number of nodes in each list
    while (temp1 != NULL) {
        count1++;
        temp1 = temp1->Next;
    }

    while (temp2 != NULL) {
        count2++;
        temp2 = temp2->Next;
    }

    if (count1 > count2) {
        return 1;// List 1 is longer
    } else if (count2 > count1) {
        return -1;// List 2 is longer
    } else { //
        temp1 = head1->Next;
        temp2 = head2->Next;
        // Traverse both lists and compare the data values of each corresponding node

        while (temp1 != NULL && temp2 != NULL && temp1->data == temp2->data) {
            temp1 = temp1->Next;
            temp2 = temp2->Next;
        }
        // Check the result of the comparison
        if (temp1 != NULL && temp2 != NULL) {
            if (temp1->data > temp2->data) {
                return 1;
            } else if (temp1->data < temp2->data) {
                return -1;
            } else {
                // The lists are equal
                return 0;
            }
            // The lists are either empty or have reached the end without a conclusive comparison
        }
    }
}

/* This function takes two doubly linked lists (head1 and head2) representing
 * numbers and returns a new doubly linked list
 * that represents the sum of the two numbers. */
D AddTwoNumbers(D head1,D head2){
    D temp1,temp2;
    int sum,num,carry=0;
    temp1= FindLast(head1);
    temp2= FindLast(head2);
    int equal;
    equal=compare(head1,head2);
    D result=(D)malloc(sizeof(struct node));
    result->Next=NULL;
    // Add the corresponding digits from both numbers until one of the numbers reaches its head
    while(temp1!=head1&&temp2!=head2){
        sum=temp1->data+temp2->data+carry;
        num=sum%10;
        carry=sum/10;
        addFirst(result,num);
        temp1=temp1->Pre;
        temp2=temp2->Pre;
    }

    temp1=temp1->Next;
    temp2=temp2->Next;
    // Handle the remaining digits of the longer number
    while(temp1->Pre!=head1&&temp2->Pre==head2){
        sum=temp1->Pre->data+carry;
        carry=sum/10;
        num=sum%10;
        addFirst(result,num);
        temp1=temp1->Pre;
    }
    while(temp2->Pre!=head2&&temp1->Pre==head1){
        sum=temp2->Pre->data+carry;
        carry=sum/10;
        num=sum%10;
        addFirst(result,num);
        temp2=temp2->Pre;
    }
    // If there is a remaining carry, add it as a new digit at the beginning of the result
    if(carry==1){
        addFirst(result,carry);
    }

    return result;

}
/* This function is used to perform a borrow operation
 * in a doubly linked list. It takes the head pointer
 * of the list (head) and a specific digit node
 * (digit) as parameters. */
void borrow(D head,D digit){
    // Iterate through the previous nodes until a node with a non-zero digit is found
    D p;
    p=digit->Pre;
    while(1){
        if (p->data != 0) {
            p->data--;// Decrement the non-zero digit by 1
            digit->data += 10;// Add 10 to the current digit, representing the borrowed value
            break;
        } else {
            p->data+=9; // Add 9 to the current digit (to borrow from the previous node)
        }
        p=p->Pre;// Move to the previous node
    }
}
/* This function checks if all the digits in a doubly
 * linked list (head1) are zero. It returns an
 * integer value indicating the result. */


int allsZero(D head1){
    // Traverse through the list until a non-zero digit is found or the end of the list is reached
    D temp=head1->Next;
    while (temp!=NULL){
        if(temp->data==0)
            temp=temp->Next;
        else
            break;
    }
// Check if the traversal reached the end of the list
    if(temp==NULL){
        return 1;// All digits in the list are zero
    } else
        return 0; // There is at least one non-zero digit in the list
}


/*
 * Function that takes 2 lists of big integers and returns their difference as a list. Each of the lists
 * is unaffected in the process.
 */

D SubtractTwoNumbers(D head1,D head2) {
    D result=(D)malloc(sizeof(struct node));
    result->Next=NULL;

    int com= compare(head1,head2); //compares the 2 lists

    if(com==0){ //returns a list representing a zero if both are function
        add(result,0);
        return result;
    }
    else {
        D temp1, temp2;
        int digit1, digit2, sub;
        temp1 = FindLast(head1); //gets the last digit in list 1
        temp2 = FindLast(head2); //gets the last digit in list 2

        /*
         * This while loop traverses all the digits in the list and subtarcts each one of them
         * untill the list has been traversed once.
         */

        while (temp1 != head1 && temp2 != head2) {

            digit1 = temp1->data;
            digit2 = temp2->data;
            if (digit1 >= digit2) {
                sub = digit1 - digit2;
                addFirst(result, sub);
                temp1 = temp1->Pre;
                temp2 = temp2->Pre;
            } else { //calls the borrow function if the first digit is less than the second
                borrow(head1, temp1);
                sub = temp1->data - temp2->data;
                addFirst(result, sub);
                temp1 = temp1->Pre;
                temp2 = temp2->Pre;
            }

        }

        while (temp1 != head1) {
            addFirst(result, temp1->data);
            temp1 = temp1->Pre;
        }
        while (temp2 != head2) {
            addFirst(result, temp2->data);
            temp2 = temp2->Pre;
        }

        Filter(result); //removes any redundant zeros at the beginning of the list.


    }
    return result;
}

/* This function deletes a doubly linked list and frees the memory
 * allocated for each node. It takes a pointer to
 * the head node (N) as a parameter. */

void DeleteList(struct node* N){

    struct node *L, *temp;
    L=N->Next;
    N->Next=NULL;

    while(L!=NULL){
        temp=L->Next;
        free(L);
        L=temp;

    }
    free(N);
}

/*
 * Function that multiplies 2 lists of big numbers and returns the result as another list.
 */

D MultiplyTwoNumbers(D head1,D head2){

    D temp1,temp2;
    D multiply=(D) malloc(sizeof(struct node)); //allocates memory for the result list

    if (multiply == NULL) {

        printf("out memory!");
        exit(1);
    }
    multiply->Next=NULL;
    D number=(D) malloc(sizeof(struct node));

    if (number == NULL) {
        printf("out of memory!");
        exit(1);
    }
    number->Next=NULL;

    int num=0,carry=0,res=0,count=0;
    temp1= FindLast(head1);
    temp2= FindLast(head2);
    while (temp1!=head1){
        num=carry+(temp2->data * temp1->data);
        res=num%10;
        carry=num/10;
        addFirst(multiply,res);
        temp1=temp1->Pre;
    }
    if(carry!=0){
        addFirst(multiply,carry);
    }
    temp1= FindLast(head1);
    temp2=temp2->Pre;
    carry=0;
    while (temp2!=head2){
        carry=0;
        while (temp1!=head1){
            num=carry+(temp2->data * temp1->data);
            res=num%10;
            carry=num/10;
            addFirst(number,res);
            temp1=temp1->Pre;
        }
        if(carry!=0){
            addFirst(number,carry);
        }

        count+=1;


        for(int i=0;i<count;i++){
            add(number,0);
        }

        multiply= AddTwoNumbers(multiply,number);
        temp2=temp2->Pre;
        temp1= FindLast(head1);
        emptyList(number);

    }
    free(number);
    return multiply;
}

/* This function performs division operation between two numbers represented
 * by doubly linked lists (head1 and head2). It also writes the
 * intermediate steps and remainder to a file (q). */

D DivideTwoNumbers(D head1, D head2, FILE *q) {

    int result;
    D temp1 = head1->Next;
    D temp2 = head2->Next;

    D DivRes = (D)malloc(sizeof(struct node));
    DivRes->Next = NULL;

    D Remainder = (D)malloc(sizeof(struct node));
    Remainder->Next = NULL;

    D MultiplyRes = (D)malloc(sizeof(struct node));
    MultiplyRes->Next = NULL;

    D DigitToMultiply = (D)malloc(sizeof(struct node));
    DigitToMultiply->Next = NULL;

    D tempRemainder;

    int n = compare(head1, head2);

    if (n == -1) {
        addFirst(DivRes, 0);
        return DivRes;
    }
    else if (n == 0) {
        addFirst(DivRes, 1);
        return DivRes;
    }

    while (temp2 != NULL) {
        add(Remainder, temp1->data);
        temp2 = temp2->Next;
        temp1 = temp1->Next;
    }
  if (allsZero(head2)){
    printf("can't divide by zero\n");
    exit(1);
  }

    while(temp1!=NULL) {

        result = repeatedSubtraction(Remainder, head2);

        add(DivRes, result);
        add(DigitToMultiply, result);

        MultiplyRes = MultiplyTwoNumbers(DigitToMultiply, head2);
        Remainder = SubtractTwoNumbers(Remainder, MultiplyRes);
        Filter(Remainder);

        add(Remainder, temp1->data);
        temp1 = temp1->Next;
        emptyList(DigitToMultiply);
    }


    result = repeatedSubtraction(Remainder, head2);
    add(DivRes, result);

    if (DivRes->Next->data == 0) {
        DeleteNode(DivRes, DivRes->Next);
    }

    add(DigitToMultiply, result);
    MultiplyRes = MultiplyTwoNumbers(DigitToMultiply, head2);
    Remainder = SubtractTwoNumbers(Remainder, MultiplyRes);


    DeleteList(MultiplyRes);
    DeleteList(DigitToMultiply);

    printNumber_file(Remainder, q);
    fprintf(q, "\n");

    return DivRes;
}
int repeatedSubtraction (D l1, D l2) {


    D copy_l1  =(D)malloc(sizeof(struct node));
    copy_l1->Next = NULL;

    if (copy_l1 == NULL) {
        exit(1);
    }
    copyList(copy_l1, l1);

    D copy_l2 =(D) malloc(sizeof(struct node));
    copy_l2->Next = NULL;
    copyList(copy_l2, l2);

    int com = compare(copy_l1, copy_l2);
    int res= 0;
    D tempSub;
    D sub = copy_l1;


    while (com == 1 || com == 0) {

        sub = SubtractTwoNumbers(sub, copy_l2);
        res++;
        com = compare(sub, copy_l2);
    }

    return res;
}

void OpenFileAndDoOpreation(FILE *q) {
    FILE *file;
    file= fopen("input.txt","r");

    if (file == NULL) {
        printf("Error: Cannot open file\n");
    }
    int count=0;
    char c,find;
/* the next while loop determine the number of numbers in the file and that is through
 increasing the value of the counter by one when ever the find was a new line character*/
    while(1){
        find= fgetc(file);
        if(find=='\n')
            count++;
        else if(find==EOF){
            break;
        } 
    }
    D numbers[count];

/* this is array of struct node pointer
 that make us able to put every node in a seperate linked list*/

    fclose(file);
    file= fopen("input.txt","r");

    for(int i=0;i<count;i++) {

        numbers[i] = (D) malloc(sizeof(struct node));
        numbers[i]->Next = NULL;

        // printf("%d",i+1);

        while (1) {
            c = fgetc(file);
            if(c=='-') {
                numbers[i]->data = -1;

            }
            else
            if (c == '\n'||c==EOF) {
                break;
            }
            else
            if (c == NULL) {
                continue;
            } else {

                int digit = c - '0'; // convert ASCII digit to integer
                add(numbers[i], digit);
            }
        }
    }

/* the for loop is to creat a linked list for every number
 and the while loop to determine where each number finish*/
    fclose(file);


    D test=(D)malloc(sizeof(struct node));
    test->Next=NULL;
    int sign;
    char operation;
    int number1,number2;

    for (;;) {

        printf("\nHi! please choose two numbers to do the Calculation on it. Enter -1 to exit.\n\n");
        for(int i=0;i<count;i++) {


            if(numbers[i]->Next!=NULL) {
                printf("%d)  ", i + 1);
                if(numbers[i]->data==-1){
                    printf("-");
                }
                printList(numbers[i]);
                printf("\n");
            }
        }

        scanf("%d", &number1);

        if (number1 == -1) {
            printf("Thanks for using my calculator");
            exit(0);

        }

        scanf("%d", &number2);
        printf(" please choose an operation (+,-,/,*)\n");
        scanf(" %c", &operation);

        if (operation == '+') {

            if (numbers[number2 - 1]->data == -1 && numbers[number1 - 1]->data == -1) {
                printf("-");
                test = AddTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);
            }
            else if (numbers[number1 - 1]->data == -1) {
                sign = compare(numbers[number1 - 1], numbers[number2 - 1]);
                if (sign == 1) {
                    printf("-");
                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
                } else if (sign == -1) {

                    test = SubtractTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);
                }
                if (sign == 0) {

                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
                }
            } else if (numbers[number2 - 1]->data == -1) {
                sign = compare(numbers[number1 - 1], numbers[number2 - 1]);
                if (sign == 1) {

                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
                } else if (sign == -1) {
                    printf("-");
                    test = SubtractTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);
                } else if (sign == 0)
                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
            } else {
                test = AddTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);
            }

        }


        if (operation == '-') {
            if (numbers[number1 - 1]->data == -1 && numbers[number2 - 1]->data == -1) {
                printf("-");
                test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);


                sign = compare(numbers[number1 - 1], numbers[number2 - 1]);
                if (sign == 1) {
                    printf("-");
                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
                } else if (sign == -1) {

                    test = SubtractTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);

                } else
                    test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);


            } else if (numbers[number1 - 1]->data == -1) {
                test = SubtractTwoNumbers(numbers[number2 - 1], numbers[number1 - 1]);
            } else if (numbers[number2 - 1]->data == -1) {
                test = AddTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
            } else {
                test = SubtractTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);
            }

        }

        if (operation == '*') {
            if (numbers[number2 - 1]->data == -1 && numbers[number1 - 1]->data == -1) {

            } else if (numbers[number2 - 1]->data == -1 || numbers[number1 - 1]->data == -1) {
                printf("-");

            }
            test = MultiplyTwoNumbers(numbers[number1 - 1], numbers[number2 - 1]);


        }
        if (operation == '/') {
            if (numbers[number2 - 1]->data == -1 && numbers[number1 - 1]->data == -1) {

            } else if (numbers[number1 - 1]->data == -1) {
                printf("-");
                test = DivideTwoNumbers(numbers[number1 - 1], numbers[number2 - 1], q);
            } else if (numbers[number2 - 1]->data == -1) {
                printf("-");
                test = DivideTwoNumbers(numbers[number1 - 1], numbers[number2 - 1], q);
            } else
                test = DivideTwoNumbers(numbers[number1 - 1], numbers[number2 - 1], q);

        }

        printNumber_file(test, q);
        printList(test);
        printf("\n");
    }
}





void emptyList (D N) {

    struct node *L, *temp;
    L=N->Next;
    N->Next=NULL;

    while(L!=NULL){
        temp=L->Next;
        free(L);
        L=temp;

    }
}

struct node* copyList (struct node *l1, struct node *l2) {

    //  emptyList(l1);
    struct node *p;


    for (p = l2->Next;p!=NULL;p = p->Next) {
        add(l1, p->data);
    }

    return l1;

}

void printNumber_file (struct node *L, FILE *q) {
   struct node *p;
  
    for (p = L->Next; p != NULL; p = p->Next) {
        fprintf(q, "%d", p->data);
    }
    fprintf(q, "\n");

}

