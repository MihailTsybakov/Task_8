#include <stdio.h>
#include <stdlib.h>

//Error codes| "-1" - wrong input, "-2" - wrong number to delete, "-3" - dot in input
//Error codes| "-4" - unknown status, "-5" - invalid number to delete,
//Error codes|  "-7" - Internal error (In Test), "-8" - Autotest not passed

typedef
struct Segment_{
    float x_beg;
    float y_beg;
    float x_end;
    float y_end;
    struct Segment_ *pointer;
}Segment;

int init(Segment* Root_node);
int init(Segment* Root_node){

    float root_x_beg, root_y_beg, root_x_end, root_y_end;
    printf("Enter 4 coordinates of the first segment: \n");
    printf("x_1: ");
    if (scanf("%g", &root_x_beg) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("y_1: ");
    if (scanf("%g", &root_y_beg) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("x_2: ");
    if (scanf("%g", &root_x_end) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("y_2: ");
    if (scanf("%g", &root_y_end) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    Root_node->x_beg = root_x_beg;
    Root_node->y_beg = root_y_beg;
    Root_node->x_end = root_x_end;
    Root_node->y_end = root_y_end;
    Root_node->pointer = NULL;
    printf("\nRoot node created\n");

    return 0;
}

int Input(Segment** Previous_pointer);
int Input(Segment** Previous_pointer){

    Segment* Temp_Node;
    float tmp_x_beg, tmp_y_beg, tmp_x_end, tmp_y_end;

    Temp_Node = (Segment*)malloc(sizeof(Segment));
    printf("Enter coordinates of current segment: \n");
    printf("x_1: ");
    if (scanf("%g", &tmp_x_beg) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("y_1: ");
    if (scanf("%g", &tmp_y_beg) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("x_2: ");
    if (scanf("%g", &tmp_x_end) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }
    printf("y_2: ");
    if (scanf("%g", &tmp_y_end) == 0){
        printf("Error: wrong input\n");
        exit(-1);
    }

    if ((tmp_x_beg == tmp_x_end)&&(tmp_y_beg == tmp_y_end)){
        printf("Error: it's a dot, not a segment\n");
        exit(-3);
    }
    Temp_Node->x_beg = tmp_x_beg;
    Temp_Node->y_beg = tmp_y_beg;
    Temp_Node->x_end = tmp_x_end;
    Temp_Node->y_end = tmp_y_end;
    Temp_Node->pointer = (*Previous_pointer);
    (*Previous_pointer) = Temp_Node;
    printf("New segment created\n");

    return 0;
}

int Chain_Printer(Segment* Previous_Pointer);
int Chain_Printer(Segment* Previous_pointer){
    int index = 0;
    float x_1, y_1, x_2, y_2;
    while (1){
        index++;
        if (Previous_pointer != NULL){
            x_1 = Previous_pointer->x_beg;
            y_1 = Previous_pointer->y_beg;
            x_2 = Previous_pointer->x_end;
            y_2 = Previous_pointer->y_end;
            printf("Segment %d: (%g, %g) ---> (%g, %g) \n", index, x_1, y_1, x_2, y_2);
        }
        if (Previous_pointer == NULL){
            break;
        }
        (Previous_pointer) = Previous_pointer->pointer;
    }
    return 0;
}

int Count(Segment* Previous_Pointer);
int Count(Segment* Previous_Pointer){
    int number_of_nodes = 0;
    Segment* Pointer_to_node;
    Segment* Pointer_from_node;
    Segment* Pointer_to_previous_node;

    Pointer_to_node = Previous_Pointer;
    Pointer_from_node = Pointer_to_node->pointer;
    Pointer_to_previous_node = NULL;
    while(1){
        number_of_nodes++;
        if (Pointer_from_node == NULL){
            break;
        }
        Pointer_to_previous_node = Pointer_to_node;
        Pointer_to_node = Pointer_from_node;
        Pointer_from_node = Pointer_from_node->pointer;
    }
    return number_of_nodes;
}

int Delete_Segment(Segment** Previous_Pointer);
int Delete_Segment(Segment** Previous_Pointer){
    int delete_number, number_of_segments;
    Segment* Pointer_to_node;
    Segment* Pointer_from_node;
    Segment* Pointer_to_previous;

    number_of_segments = Count(*Previous_Pointer);
    if (number_of_segments == 0){
        printf("Error: there are no segments to delete\n");
    }
    if (number_of_segments > 0){
        Chain_Printer(*Previous_Pointer);
        printf("Enter a number of segment which you want to delete: ");
        scanf("%d", &delete_number);
    }
    if (delete_number < 1){
        printf("Error: invalid number of segment to delete\n");
        exit(-5);
    }
    if (number_of_segments > 0){
        (Pointer_to_node) = (*Previous_Pointer);
        (Pointer_from_node) = Pointer_to_node->pointer;
        Pointer_to_previous = NULL;
    }
    if (number_of_segments > 1){
        if (delete_number != 1){
            for (int index = 0; index < (delete_number - 1); index++){
                Pointer_to_previous = Pointer_to_node;
                Pointer_to_node = Pointer_from_node;
                Pointer_from_node = Pointer_to_node->pointer;
                if ((index != delete_number-2)&&(Pointer_from_node == NULL)){
                    printf("Error: number of segment is out of range\n");
                    exit(-2);
                }
            }
            Pointer_to_previous->pointer = Pointer_from_node;
        }
        if (delete_number == 1){
            (*Previous_Pointer) = (*Previous_Pointer)->pointer;
        }
    }
    if (number_of_segments == 1){
        if (delete_number != 1){
            printf("Error: wrong number of segment to delete\n");
            exit(-2);
        }
       Last_Node = (Segment*)malloc(sizeof(Segment));
        Last_Node->pointer = NULL;
        printf("If you want to add a segment, enter '1', to delete a segment - '2', to end execution of the program - '3': ");
        scanf("%d", &status);
        if (status == 3){
            printf("Executing complete\n");
            exit(0);
        }
        if (status == 2){
            printf("Error: nothing more to delete\n");
            exit(-5);
        }
        if (status == 1){
            printf("Enter coordinates of the current segment: ");
            printf("x_1: ");
            if (scanf("%g", &tmp_x_beg) == 0){
                printf("Error: wrong input\n");
                exit(-1);
            }
            printf("y_1: ");
            if (scanf("%g", & tmp_y_beg) == 0){
                printf("Error: wrong input\n");
                exit(-1);
            }
            printf("x_2: ");
            if (scanf("%g", &tmp_y_beg) == 0){
                printf("Error: wrong input\n");
                exit(-1);
            }
            printf("y_2: ");
            if (scanf("%g", &tmp_y_end) == 0){
                printf("Error: wrong input\n");
                exit(-1);
            }
            Last_Node->x_beg = tmp_x_beg;
            Last_Node->y_beg = tmp_y_beg;
            Last_Node->x_end = tmp_x_end;
            Last_Node->y_end = tmp_y_end;

            (*Previous_Pointer) = Last_Node;
            printf("New segment created\n");
        }
    }
    return 0;
}

int Intersections(Segment** Previous_Pointer, int print_code);
int Intersections(Segment** Previous_Pointer, int print_code){

    float x_1, y_1, x_2, y_2, k, b, compare_temp;
    float tmp_x_1, tmp_y_1, tmp_x_2, tmp_y_2;
    int number_of_segment = 0;
    Segment* Pointer_to_node;
    Segment* Pointer_from_node;
    Segment* Pointer_to_previous_node;

    Pointer_to_node = (*Previous_Pointer);
    Pointer_from_node = Pointer_to_node->pointer;
    Pointer_to_previous_node = NULL;

    if (Pointer_from_node == NULL){
        printf("Error: cannot compare, inputted segment is the only segment in the list\n");
        exit(-4);
    }

    x_1 = (*Previous_Pointer)->x_beg;
    y_1 = (*Previous_Pointer)->y_beg;
    x_2 = (*Previous_Pointer)->x_end;
    y_2 = (*Previous_Pointer)->y_end;

    // Just changing names of dots if needed
    if (x_1 > x_2){
        compare_temp = x_1;
        x_1 = x_2;
        x_2 = compare_temp;
        compare_temp = y_1;
        y_1 = y_2;
        y_2 = compare_temp;
    }
    if ((x_1 == x_2) && (y_1 > y_2)){
        compare_temp = x_1;
        x_1 = x_2;
        x_2 = compare_temp;
        compare_temp = y_1;
        y_1 = y_2;
        y_2 = compare_temp;
    }

    if (x_1 != x_2){

        k = (y_1 - y_2)/(x_1 - x_2);
        b = y_1 - k*x_1;
        while (1){
            number_of_segment++;
            Pointer_to_previous_node = Pointer_to_node;
            Pointer_to_node = Pointer_from_node;
            Pointer_from_node = Pointer_from_node->pointer;
            tmp_x_1 = Pointer_to_node->x_beg;
            tmp_y_1 = Pointer_to_node->y_beg;
            tmp_x_2 = Pointer_to_node->x_end;
            tmp_y_2 = Pointer_to_node->y_end;

            // Again, just changing names of dots if needed:
            if (tmp_x_1 > tmp_x_2){
                compare_temp = tmp_x_1;
                tmp_x_1 = tmp_x_2;
                tmp_x_2 = compare_temp;

                compare_temp = tmp_y_1;
                tmp_y_1 = tmp_y_2;
                tmp_y_2 = compare_temp;
            }
            if ((tmp_y_1 ==  (k * tmp_x_1 + b)) && (tmp_y_2 == (tmp_x_2 * k + b))){
                // I. if current segment  lies inside inputted segment:
                if ((tmp_x_1 >= x_1)&&(tmp_x_2 <= x_2)){
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment lied inside inputted\n");
                    }

                }
                // II. if inputted segment lies inside the current segment:
                if ((tmp_x_1 <= x_1)&&(tmp_x_2 >= x_2)){
                    (*Previous_Pointer) = (*Previous_Pointer)->pointer;
                    if (print_code == 1){
                        printf("Inputted segment lied inside one of the previous segments\n");
                    }
                }
                // III. if current segment touches inputted segment by the left side:
                if ((tmp_x_2 >= x_1) && (tmp_x_2 < x_2) && (tmp_x_1 < x_1)){
                    (*Previous_Pointer)->x_beg = tmp_x_1;
                    (*Previous_Pointer)->y_beg = tmp_y_1;
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment touched inputted segment by the left side\n");
                    }
                }
                // IV. if current segment touches inputted segment by the right side:
                if ((tmp_x_1 > x_1)&&(tmp_x_1 <= x_2)&&(tmp_x_2 > x_2)){
                    (*Previous_Pointer)->x_end = tmp_x_2;
                    (*Previous_Pointer)->y_end = tmp_y_2;
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment touched inputted segment by the right side\n");
                    }
                }
            }
            if (Pointer_from_node == NULL){
                break;
            }
        }
    }
    if (x_1 == x_2){
        while(1){
            Pointer_to_previous_node = Pointer_to_node;
            Pointer_to_node = Pointer_from_node;
            Pointer_from_node = Pointer_from_node->pointer;
            tmp_x_1 = Pointer_to_node->x_beg;
            tmp_y_1 = Pointer_to_node->y_beg;
            tmp_x_2 = Pointer_to_node->x_end;
            tmp_y_2 = Pointer_to_node->y_end;

            // Changing names of dots if needed:
            if ((tmp_x_1 - tmp_x_2) > 0.001){
                compare_temp = tmp_x_1;
                tmp_x_1 = tmp_x_2;
                tmp_x_2 = compare_temp;

                compare_temp = tmp_y_1;
                tmp_y_1 = tmp_y_2;
                tmp_y_2 = compare_temp;
            }

            if ((tmp_x_1 == x_1)&&(tmp_x_2 == x_1)){
                // I. if current segment lies inside the inputted segment:
                if (((tmp_y_1 >= y_1) && (tmp_y_2 <= y_2))){
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment lied inside the inputted segment\n");
                    }
                }
                // II. if inputted segment lies inside the current segment:
                if ((tmp_y_1 < y_1) && (tmp_y_2 > y_2)){
                    (*Previous_Pointer) = (*Previous_Pointer)->pointer;
                    if (print_code == 1){
                        printf("Inputted segment lied inside one of the previous segments\n");
                    }
                }
                // III. if current segment touches inputted segment by the lower side:
                if ((tmp_y_1 < y_1) && (tmp_y_2 >= y_1) && (tmp_y_2 < y_2)){
                    (*Previous_Pointer)->y_beg = tmp_y_1;
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment touched inputted segment by the lower side\n");
                    }
                }
                // IV. if current segment touches inputted segment by the higher side:
                if ((tmp_y_1 <= y_2) && (tmp_y_2 > y_2) && (tmp_y_1 > y_1)){
                    (*Previous_Pointer)->y_end = tmp_y_2;
                    Pointer_to_previous_node->pointer = Pointer_from_node;
                    if (print_code == 1){
                        printf("Some segment touched inputted segment by the higher side\n");
                    }
                }
            }
            if (Pointer_from_node == NULL){
                break;
            }
        }
    }

    return 0;
}

int Input_from_file(Segment** Pointer, FILE* file);
int Input_from_file(Segment** Pointer, FILE* file){
    Segment* Temp_Node;
    float x_beg_tmp, y_beg_tmp, x_end_tmp, y_end_tmp;

    Temp_Node = (Segment*)malloc(sizeof(Segment));


    if (fscanf(file, "%g", &x_beg_tmp)==0){
        printf("Internal error\n");
        exit(-7);
    }
    if (fscanf(file, "%g", &y_beg_tmp)==0){
        printf("Internal error\n");
        exit(-7);
    }
    if (fscanf(file, "%g", &x_end_tmp)==0){
        printf("Internal error\n");
        exit(-7);
    }
    if (fscanf(file, "%g", &y_end_tmp)==0){
        printf("Internal error\n");
        exit(-7);
    }
    Temp_Node->x_beg = x_beg_tmp;
    Temp_Node->y_beg = y_beg_tmp;
    Temp_Node->x_end = x_end_tmp;
    Temp_Node->y_end = y_end_tmp;
    Temp_Node->pointer = (*Pointer);
    (*Pointer) = Temp_Node;

    return 0;
}

int Autotest_Counter(void);
int Autotest_Counter(void){
    FILE* test_file;
    Segment Test_Root;
    Segment* Test_Pointer;
    int test_number = 0;

    test_file = fopen("test.txt","r");
    if (!test_file){
        printf("Error: cannot open autotest file\n");
        exit(-9);
    }

    Test_Root.x_beg = 1;
    Test_Root.y_beg = 2;
    Test_Root.x_end = 3;
    Test_Root.y_end = 4;
    Test_Root.pointer = NULL;

    Test_Pointer = (&Test_Root);
    for (int i = 0; i < 4; i++){
        Input_from_file(&Test_Pointer, test_file);
    }
    test_number = Count(Test_Pointer);
    if (test_number == 5){
        printf("Autotest_1 passed successfully\n");
    }
    else{
        printf("Autotest_1 not passed\n");
        exit(-8);
    }
    fclose(test_file);
    return 0;
}

int Autotest_Intersections(void);
int Autotest_Intersections(void){
    FILE* test_file;
    Segment Test_Node;
    Segment* Test_Pointer;
    int number_of_segments = 0;

    test_file = fopen("test.txt","r");
    if (!test_file){
        printf("Error: cannot open autotest file\n");
        exit(-9);
    }
    Test_Node.x_beg = 1;
    Test_Node.y_beg = 2;
    Test_Node.x_end = 3;
    Test_Node.y_end = 4;
    Test_Node.pointer = NULL;
    Test_Pointer = (&Test_Node);
    for (int i = 0; i < 4; i++){
        Input_from_file(&Test_Pointer, test_file);
    }
    Intersections(&Test_Pointer, 0);
    number_of_segments = Count(Test_Pointer);
    if (number_of_segments == 4){
        printf("Autotest_2 passed successfully\n");
    }
    else{
        printf("Autotest_2 not passed\n");
        exit(-8);
    }
    fclose(test_file);
    return 0;
}

int main(void){
    Segment Root_Node;
    Segment* Previous_Pointer;
    int status;

    Autotest_Counter();
    Autotest_Intersections();
    init(&Root_Node);
    Previous_Pointer = &Root_Node;

    while (1){
        printf("Current segments are:\n");
        Chain_Printer(Previous_Pointer);
        printf("If you want to add a segment, enter '1', to delete a segment - '2', to end execution of the program - '3': ");
        scanf("%d", &status);
        if (status == 3){
            printf("Execution complete\n");
            exit(0);
        }
        if (status == 1){
            Input(&Previous_Pointer);
            Intersections(&Previous_Pointer, 1);
        }
        if (status == 2){
            Delete_Segment(&Previous_Pointer);
        }
        if ((status != 3) && (status != 1) && (status != 2)){
            printf("Error: unknown status, ending execution\n");
            exit(-4);
        }
    }
    return 0;
}
