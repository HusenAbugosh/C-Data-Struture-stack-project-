// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


// I used double pointer in my implementation to allows modifications to the original stack pointer passed from the calling function
//(pass by refrence).

/// 👇🏽 LINKEDLIST STRUCTURES 👇🏽 ////
/*
doubly linked list: its a list of node each node have 3 spaces in it :

  data: space to store the data in it;
  next: pointer thats point to the next node;
  prev: pointer thats point to the previous node;

          list👇🏽       |            Nodes👇🏽                      |  tail 👇🏽
  |null/data/next| ->  <_|prev/data/next| -> <_|prev/data/next| ->   <_ |prev/data/null| -> Null

  disadvantages?  >yes its take more space than the single linked list cuse of the prev pointer.
*/

typedef struct Node{

    // each node will contain these 4 attributes:
    char data;
    struct Node *next;
    struct Node *prev;

} Node;

// will lock about sapce place for a node in the memo
Node *create_Node(char data){

    // TO find a space in memo to create a node:
    Node *newNode = (Node *)(malloc(sizeof(Node)));

    // if there is no space in the memo:
  if (newNode == NULL){
        printf("Out of memory!\n");
    }
    // to insert the data and set up the pointers
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// to insert a new node into the linked list
void insert(Node **list, char data){

    Node *new_node = create_Node(data);    //<--create a node:
    //if this list does not have nay node befor the new node will the first node
    if (*list == NULL){
        *list = new_node;
    }else{
        //if the list have a nodes the new node will be after the pervios tail(node->next = null)
        Node *current_node = *list;
        while (current_node->next != NULL){
            current_node = current_node->next;
        }
        //move the postion to the next node:
        current_node->next = new_node;
        new_node->prev = current_node;
    }
}

// to print the data of each node in givven list:
void display(Node *list){

    Node *current_node = list;
    while (current_node != NULL){
        printf("%c", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}

// to delete alist :
void deleteList(Node **list){

    Node *current_node = *list;
    Node *next_node;
    while (current_node != NULL){

        next_node = current_node->next; //<-- to save the next node before deleting the current node
        if (current_node->prev != NULL){
            current_node->prev->next = NULL; //<-- to set the next pointer of the previous node to null
        }

        free(current_node);       // Free the memory allocated for the current node
        current_node = next_node; // Move to the next node in the list
    }
    *list = NULL; // Set the list pointer to NULL, indicating the list is empty
}

// to reverse the list(the head will be the tail and the opposite is true)
Node *reverse(Node *head){

    Node *current_node = head;
    Node *temp = NULL;

    while (current_node != NULL){

        temp = current_node->prev;
        current_node->prev = current_node->next;
        current_node->next = temp;
        current_node = current_node->prev;
    }

    // Update the head of the reversed list
    if (temp != NULL){
        head = temp->prev;
    }

    return head;
}

// to caluclate the size of linked list:
int sizeOfList(Node *head){
    Node *current_node = head;
    int size = 0; //<-- couter to count how many node the list have till the tail
    while (current_node != NULL){
        size++;
        current_node = current_node->next;
    }
    return size;
}

/// 👇🏽 STACK STRUCTURES 👇🏽 ////

typedef struct  Stack{

    int data;              // <<<  will store the data in the node.
    struct Stack* next;    // <<<  will store the address of the next node (points on the NEXT NODE thats why its data is struct node).
}Stack;


Stack* createStack() {
    return NULL;
}

//Push function: equivalent to insert. Inserts element at top:
void push(Stack** stack, int element) {

    Stack* newNode = (Stack*)malloc(sizeof(Stack)); //<-- to find a address in the memo to save the new node in it.

    // if there is no space in the memo for this node tell the user:
    if (newNode == NULL) {
        printf("memory allocation failed, falied to push element.\n");
        return;
    }

    newNode->data = element;   //<-- sets the data of the newNode to be the element.
    newNode->next = *stack;    //<-- sets the next pointer of newNode to point to the current top of the stack).
    *stack = newNode;         //<-- sets the newNode to be the top(stack) node(top of the stack),  making it the new top of the stack.
    // printf("element %c pushed to the stack. \n", element); // <-- to tell the user the push success.

}


//Pop function: return AND delete the most recently added element:
char pop(Stack** stack) {

    // if the theere is no elements inside the stack there is nothing to pop so it will cuse an error:
    if (*stack == NULL) {
        printf("*EROOR the stack is empty, nothing to pop*\n");
        return -1;
    }

    Stack* temp = *stack;              //<--  temporary node will pointer to top node.
    int poppedElement = temp->data; //<-- to store the data that was in the last top.
    *stack = temp->next;            //<-- will make the next node of the pervious top to be the the final top.
    free(temp);                   //<-- free the temp (node) from the memo.
    // printf("element %c popped from the stack.\n", poppedElement); //<-- tell the user whats happend.
    return poppedElement;   //<-- return the poppedElement.

}

//getTop: examines (returns) the most recently added element without deleteing it:
char getTop(Stack** stack) {

    // if the theere is no elements inside the stack there is nothing to pop so it will cuse an error:
    if (*stack == NULL) {
        printf("*EROOR the stack is empty, nothing to pop*\n");
        return -1;
    }
    return (*stack)->data;  //<-- will return the elemnt that in the top node.
}

//deleteStack function : will delete the nedeed stack:
void deleteStack(Stack** stack) {

    // will delete all the nodes:
    while (*stack != NULL) {
        Stack* temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }
    // printf("Stack deleted.\n");
}

//sizeOf: to get the size of the stack:
int sizeOf(Stack** stack) {

    int size = 0;
    while (stack != NULL) {
        *stack = (*stack)->next;
        size++;
    }
    return size;
}

//isEmpty: return if the stack is null or not:
int isEmpty(Stack** stack){
    return (*stack == NULL); //<-- to return if the stack is null or not
}


/////// 👇🏽  Functions 👇🏽 ///////////

//global varibales:
char fileName[20];     //<--  a string (array of char) to store the input file name.
int lineNum = 1;

void readFile(){


    printf("Hi, please enter the input file name: equations.txt\n");
    scanf("%s", fileName);  //<-- get the input file name from the user.

    FILE *file = fopen(fileName, "r"); //<-- will open the wanted file & put it on the reading mode.
    // this if-statment used to check if there any error with openning the file.
    if (file == NULL){
        printf("*ERROR: File couldn't be opened*\n");
    }
    printf("\n");
    char character;     //<-- will save the exprestions in the file .
    // while the character its not the End of the file keep printing the characters that found in the file :
    while ((character = fgetc(file)) != EOF){
        if(character == '\n'){
            lineNum++;
        }
        printf("%c", character); //<--  print every characters that found in the file.
    }

    fclose(file); //<-- close the file.
}

/* to cheak if the top and the close parces are in the same type
maybe the top (  and the current char is } in this case is invalid: */
int arePair(char open , char close){

    if(open == '{' && close == '}'){
        return 1;
    }else if(open == '(' && close == ')'){
        return 1;
    }else if(open == '[' && close == ']'){
        return 1;
    }

    return 0;
}



/* isValid function : will get a list(infix notaion) as parmeter then return 1(true)
if its Valid or 0(flase) and why its inValid 
Complexity:  O(n) ->  where n is the number of characters in the CharList.
*/
int isValid(Node* charList, int reason){

    insert(&charList,' '); //<-- to review each original characters
    // display(charList);

    Node* currentNode = charList;
    Stack* stack1 = createStack(); //<-- to declear a stack.
    // check char char and push the char to the stack if its open parces: ( { [
    while(currentNode != NULL && currentNode->next != NULL ){

        char currentChar = currentNode->data;
        char nextChar = currentNode->next->data;

        /* if there a digit and after a digit we found open parces: ( { [  then we dont have any operation
           between them so its inVaild and vice versa*/
        if(isdigit(currentChar) && (nextChar == '['  || nextChar == '(' ||  nextChar == '{' )){

            if(reason == 1){
              printf("Invalid: there is no operator between %c & %c\n",currentChar,nextChar);
            }
            return 0; //<-- that mean invaild in the opertaion.

        } else if((currentChar == ']'  || currentChar == ')' ||  currentChar == '}' ) && isdigit(nextChar)){
            if(reason == 1){
              printf("Invalid: there is no operator between %c & %c\n",currentChar,nextChar);
            }
            return 0; //<-- that mean invaild in the opertaion.

        }else if((currentChar == '+' || currentChar == '-') && (nextChar == '*' || nextChar == '/')){
            if(reason == 1){
              printf("Invalid: can not be %c %c after each other!\n",currentChar,nextChar);
            }
            return 0; //<-- that mean invaild in the opertaion.
        }

        // if the char is open parces: ({[  push it to stack:
        if (currentChar == '{' || currentChar == '[' || currentChar == '('){
            push(&stack1,(int)(currentChar));

            // if the char is closed parces: )}] pop it but we need to check is not empty first:
            // eg: | } | <  there is no open  parces to close it !:
        }else if (currentChar == '}' || currentChar == ']' || currentChar == ')'){
            if(isEmpty(&stack1) || arePair((char)(getTop(&stack1)),currentChar) == 0){
                if(reason == 1){
                    printf("Invalid: %c is not closed\n",(char)(getTop(&stack1)));
                }
                return 0; //<-- inVaild equation.
            }else{
                pop(&stack1);
            }
        }

        currentNode = currentNode->next; //<-- move the postion to the next node.
    }

    // after checks everything > if the stack is empty then the 1eq will be Valid:
    if (isEmpty(&stack1)) {
        return 1;
    } else {
        if(reason == 1){
        printf("Invalid: there is no open parentheses for %c\n",(char)(getTop(&stack1)));
        }
        return 0;
    }

    deleteStack(&stack1); //<-- clean up the memo.
}


// this function will return the priority  of each operatior:
int priority(char c){

    if(c == '+' || c == '-'){
        return 1;
    }else if(c == '*' || c == '/') {
        return 2;
    }else if(c == '^'){
        return 3;
    }else{
        return 0;
    }
}

// if the char is one of these char(* / ^) will return 1 
int isOperator(char c){

    if(c == '*' || c == '/' || c == '^'){
        return 1;
    }else{
        return 0;
    }
}

/* Convert function: will take a likecList(CharList) thats conatain a infix notation 
 and will return a newList(output) that will contain the prefix notation
 
 Complexity:  O(n) -> where n is the number of nodes in the input linked list(infix notaion).
  */

Node* convert(Node* charList) {
    if (isValid(charList,1)) {

        //reverse the infix expression:
        charList = reverse(charList);

        Node* output = NULL;  //<-- list that will contain the preFix notation.
        Stack* stack1 = createStack();  //<-- stack will held the operators.

        Node* currentNode = charList;  //<-- to track the postion.
     
        // while the currentNode conatain a data in it keep doing these folwing comands:
        while (currentNode != NULL) {

            char currentChar = currentNode->data; //<-- will held the char data inside the charList.

            // if the currentChar is space(' ') dont waste time just move tso the nextNode (next char):
            if (isspace(currentChar)) {
                currentNode = currentNode->next;
                continue;
            }
            
            //if the currentChar is a digit then -> keep adding it to the output list:
            if (isdigit(currentChar)) {

                // to handle multi-digit integers:
                int number = 0; //<-- we held the int(& the case of multi-digit int)
                int numDigits = 0;
                while (currentNode != NULL && isdigit(currentNode->data)) {

                    //number will store a digit and sum it to next digit if there:
                    number = number * 10 + (currentNode->data - '0');
                    currentNode = currentNode->next; //<-- move to next node ;
                    numDigits++;
                }
                // allocate memory for the number string
                 char* numberStr = (char*)malloc((numDigits + 2) * sizeof(char)); 

                /* the snprintf function formats the integer number according to the provided format string
                 and writes the resulting string into numberStr:*/
                snprintf(numberStr, numDigits+2, "%d ", number); //<-- we will add space to know the diffrent int.
                // insert each character(digit) of the number string one by one 
                for (int i = 0; numberStr[i] != '\0'; i++) {
                    insert(&output, numberStr[i]);
                }
                continue;
            }
            
             // if the character is closed parenthesis )] then ->  push it to the operator stack:
            if (currentChar == ')' || currentChar == ']') {
                push(&stack1, (int)currentChar);

            /* if the character is an open parenthesis ([ then -> we will add every element to output list
                & pop it from the stack untill we found the closed parenthesis: */
            } else if (currentChar == '(' || currentChar == '[') {
                while (!arePair(currentChar, getTop(&stack1))) {
                    insert(&output, (char)getTop(&stack1));
                    pop(&stack1);
                }
                pop(&stack1);  //<-- to pop the left open parentheses from the stack.

                /*if the character is an operator {^ -> * / -> + - } then check for priority
                 between the top of the stack & the current char */
            } else {
                while (!isEmpty(&stack1) && priority(currentChar) < priority((char)getTop(&stack1))) {
                    insert(&output, (char)getTop(&stack1));
                    pop(&stack1);
                }
                push(&stack1, (int)currentChar);
            }

            currentNode = currentNode->next;  //<-- move the postion to the next node.
        }
        
        // after all the perviouschecks if ther any thing lift in the stack just add it to the output list:
        while (!isEmpty(&stack1)) {
            insert(&output, (char)getTop(&stack1));
            pop(&stack1);
        }
        
        // it will return the revese of the output list:
        return reverse(output);
    } else {
        // if the notation is inValid it will return Null:
        return NULL;
    }
}

/* will get the first & second operand then do the operation upon the operator type 
then return the result of this operation as int result:*/
int operations(int op1,int op2,char operation){

    switch (operation){
        case '+':
            return(op1+op2);
            break;
        case '-':
            return(op1-op2);
            break;
        case '*':
            return(op1*op2);
            break;
        case '/':
            return(op1/op2);
            break;
        case '^':
            return(pow(op1,op2));
            break;
        default:
            return 0;

            break;
    }
}


//reverseInt function: will get the a int num as parmaeter and return the revse of it:
int reverseInt(int num) {
    char str[10]; //<-- will assume the maximum number of digits is 10
    snprintf(str, sizeof(str), "%d", num);
    int length = strlen(str);
    
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
    
    return atoi(str);
}

/*Evaluate function: we get a list conatin an infix notaion eqaution 
then will do these:

1) cheack valdity .
2) convert it to prefix notaion.
3) return the final result of the notaion.

Complexity: O(n*k)-> where n is the number of char in the prefix list 
and k is the number of digit of the int.
*/
int Evaluate(Node* charList){

    Node* prefixList = convert(charList); //<-- to get the prefix of the charList.

    // if the prefix conatin a null value that mean  we have invalid equation:
    if (prefixList == NULL){
        return 404;
    }

    Node* reverseList = reverse(prefixList);//<-- to reverse the prefix list.

    Stack* stack1 = createStack(); //<-- to declear a stack.
    Node* currentNode = reverseList;  //<-- to track the position of the charList.
    //int sign = 1;  //<-- to store the sign of the number (positive or negative)

    // while the currentNode conatain a data in it keep doing these:
    while (currentNode!= NULL){

        char currentChar = currentNode->data; //<-- will store the data of the currentNode.

        // if the currentChar is digit then -> push it to stack:
        if(isdigit(currentChar)){


                // to handle multi-digit integers:
                int number = 0; //<-- we held the int(& the case of multi-digit int)
                while (currentNode != NULL && isdigit(currentNode->data)) {
                    //number will store a digit and sum it to next digit if there:
                    number = number * 10 + (currentNode->data - '0');
                    currentNode = currentNode->next; //<-- move to next node ;
                }
                number = reverseInt(number); //<-- will reverse the num to let it (most right digit to left).
    
            push(&stack1,(int)(number));
            //if the currentChar is operator do the operation then -> push the result to stack:
        }else if(!isdigit(currentChar)){


            int op1 = getTop(&stack1); //<-- get the element on the top and covert it to int.
            pop(&stack1);//<-- remove the top to get the second operand.

            int op2 = getTop(&stack1); //<-- get the element on the top and covert it to int.
            pop(&stack1);//<-- remove the top to get the second operand.

            int result = (operations(op1,op2,currentChar)) ; //<-- do the opertaion and return the result as char.
            push(&stack1,(int)(result));//<-- push the result to stack.

        }
        currentNode = currentNode ->next; //<-- move the postion to the next node.
    }
    int finalResult = getTop(&stack1); //<-- to store the last resul as int to return it


    // clean up the memo:
     deleteList(&reverseList);
     deleteStack(&stack1);

    return finalResult; //<-- return the Evaluate value.
}


/*lineByLine function : will read the target file then do:
1) read each equation then insert it in a list .
2) do the operation depending on the parameter on each equation.

Complexity: O(n*m) -> where n is the number of lines(equation) in the input File
and m is how many char in each equation.
 */
void lineByLine(int op){

    Node *list = NULL;
    Node* result = NULL;
    int eResult;

    FILE *file = fopen(fileName, "r"); //<-- will open the wanted file and put on the reading mode.
    // this if-statment used to check if there any error with openning the file:
    if (file == NULL){
        printf("ERROR: file couldn't be opened");
        // return NULL;
    }

    int i=1;
    // check line by line (equation by equation) if its vaild or not:
    while(i <= lineNum){

        char character = fgetc(file);
        if (character != EOF) {

            insert(&list, character);
            //the int who have more than one digit we
            // if(!isdigit(character)){
            //   insert(&list, ' ');
            // }
        }

        if(character == '\n' ||  character == EOF){

            switch (op){
                case 1:
                    // handle the isValid function:
                    printf("Equation No.%d -> ",i);
                    if(isValid(list,1) == 1){
                        printf("Valid\n");
                    }
                    break;
                case 2:
                    // handle the convert function:
                    result = convert(list);
                    display(result);
                    deleteList(&result);
                    break;
                case 3:
                    // handle the Evaluate function:
                    printf("Equation No.%d ->",i);
                    eResult = Evaluate(list);
                    if (eResult != 404){
                    printf(" %d\n",eResult);
                    }
                    break;
                case 4:
                   // to print all inValid eqaution:
                if (isValid(list,0) == 0){
                    display(list);
                    deleteList(&result);
                }
                default:
                    break;
            }

            deleteList(&list);
            i++;
        }
    }

}





int main(){


    int choice;              //<-- will store the choice of the user.
    int exitFlag = 0;        //<-- if the user rise the flag(exitFlag = 1) th loop will stop and close the programe.
    printf("breakpoint");
    //  this loop use for showing the menu:
    while (!exitFlag){


        printf("\n_______Menu_______\n\n");
        printf("1. Read Input File\n");
        printf("2. Check The Validity\n");
        printf("3. Convert(Infix > Prefix)\n");
        printf("4. Evaluate The Prefix\n");
        printf("5. Print Invalid\n");
        printf("6. Print All Equations\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n");
                readFile();
                break;
            case 2:
                printf("\n");
                lineByLine(1);
                break;
            case 3:
                printf("\n");
                lineByLine(2);
                break;
            case 4:
                 printf("\n");
                 lineByLine(3);
                break;
            case 5:
                printf("\n");
                lineByLine(4);
                break;
            case 6:
                break;
            case 7:
                break;
        }
        printf("\n");
    }
    return 1;
}