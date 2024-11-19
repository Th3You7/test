#include <stdio.h>

//create a struct
//one thing to mention; declaration must be before definition
//we declare adress before its definition

// declaring with typeddef
typedef struct {
    char street[20];
    char city[20];
    int  postal_code;
} Adress;

typedef struct {
    char first_name[12];
    char last_name[12];
    int age;
    float note;
    Adress adress;
} Student;


void get_data(Student* student) {
    //ask user to enter adress data
    printf("Enter your street: \n");
    fgets(student->adress.street, sizeof(student->adress.street), stdin);
    printf("Enter your city: \n");
    fgets(student->adress.city, sizeof(student->adress.city), stdin);
    printf("Enter your postal code: \n");
    scanf("%d", student->adress.postal_code);
    //ask user to enter student data
    printf("Enter your first name: \n");
    fgets(student->first_name, sizeof(student->first_name), stdin);
    printf("Enter your last name: \n");
    fgets(student->last_name, sizeof(student->first_name), stdin);
    printf("Enter your age: \n");
    scanf("%d", student->age);
}

void display_data(Student* student) {
    printf("Fullname: %s %s \n, age: %d\n", student->last_name, student->first_name, student->age);
    printf("Adress: %s, %s, %d\n", student->adress.city, student->adress.street, student->adress.postal_code);
}

void fupdate_last_name(Student* student) {
    char new_name[20];
    printf("Enter a new last name: \n");
    fgets(new_name, sizeof(new_name), stdin);
    student->last_name = new_name;
    return;
}

void fupdate_first_name(Student* student) {
    char new_name[20];
    printf("Enter a new first name: \n");
    fgets(new_name, sizeof(new_name), stdin);
    student->first_name = new_name;
    return;
}

void fupdate_age(Student* student) {
    int age;
    printf("Enter a new age: \n");
    scanf("%d", age);
    student->age = age;
    return;
}

void fupdate_adress(Student* student) {
    Adress adress;
    printf("Enter new Street \n");
    fgets(adress.street, sizeof(adress.street), stdin);
    printf("Enter new city \n");
    fgets(adress.street, sizeof(adress.street), stdin);
    printf("Enter new postal code \n");
    scanf("%d", adress.postal_code);

    student->adress = adress;
}

void delete_data(Student* student) {
    Adress empty_adress = {.city = "", .postal_code = "", .street = ""};
    Student empty_student = {.age = "", .first_name = "", .last_name = "", .adress = empty_adress};

    student->adress = empty_adress;
    student->age = empty_student.age;
    student->first_name = empty_student.first_name;
    student->last_name = empty_student.last_name;
}


int main() {
    //declare vars;
    int update, delete, update_name, update_age, update_adress;
    //initiate a student
    Student student;
    //get data from user
    get_data(&student);

    //display data
    display_data(&student);

    //ask user to update data or delete
    printf("do you want to update your data?\n(0 yes, 1 no): \n");
    scanf("%d", update);

    //if user wants to update something
    if(!update) {
        //ask user if he wants to change anything seperately
        //here for name
        printf("Name: %s %s. update ?\n (0 yes, 1 no) \n", student.last_name, student.first_name);
        scanf("%d", update_name);
        if(update_name) {
            fupdate_first_name(&student);
            fupdate_last_name(&student);
        }
        //here for age
        printf("Age: %d. update ?\n (0 yes, 1 no) \n", student.age);
        scanf("%d", update_age);
        if (update_age) fupdate_age(&student);
        //here for age
        printf("Adress: %s, %s %d. update ?\n (0 yes, 1 no) \n", student.adress.street, student.adress.postal_code, student.adress.postal_code);
        scanf("%d", update_age);
        if(update_adress) fupdate_adress(&student);
    }
 
    //ask user to update data or delete
    printf("do you want to delete your data?\n(0 yes, 1 no): \n");
    scanf("%d", delete);

    //if user wants to delete data
    if(!delete) {
        delete_data(&student);
    }


    return 0;
}