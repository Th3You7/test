#include <stdio.h>
#include <string.h>
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

void display_users(Student* student, int size) {
    for(int i = 0; i < size; i++){
        printf("%d- %s %s \n", i + 1,  student[i].last_name, student[i].first_name);
    }
}

void get_data(Student* student) {
    //ask user to enter adress data
    printf("Enter your street: \n");
    //ask for street and remove new line sign;
    fgets(student->adress.street, sizeof(student->adress.street), stdin);
    student->adress.street[strcspn(student->adress.street, "\n")] = '\0';

    //ask for city and remove new line sign;
    printf("Enter your city: \n");
    fgets(student->adress.city, sizeof(student->adress.city), stdin);
    student->adress.city[strcspn(student->adress.city, "\n")] = '\0';

    //postal code
    printf("Enter your postal code: \n");
    scanf("%d", &student->adress.postal_code);
    //solving the problem of skipping fgets after scanf
    getchar();
    //ask user to enter student data
    //last name, remove new line
    printf("Enter your last name: \n");
    fgets(student->last_name, sizeof(student->last_name), stdin);
    student->last_name[strcspn(student->last_name, "\n")] = '\0';

    //first name, remove new line
    printf("Enter your first name: \n");
    fgets(student->first_name, sizeof(student->first_name), stdin);
    student->first_name[strcspn(student->first_name, "\n")] = '\0';
    
    //age
    printf("Enter your age: \n");
    scanf("%d", &student->age);
}

void display_data(Student* student) {
    printf("Fullname: %s %s,\nAge: %d\n", student->last_name, student->first_name, student->age);
    printf("Adress: %s, %s, %d\n", student->adress.city, student->adress.street, student->adress.postal_code);
}

void fupdate_last_name(Student* student) {
    char new_name[20];
    printf("Enter a new last name: \n");
    fgets(new_name, sizeof(new_name), stdin);
    new_name[strcspn(new_name, "\n")] = "\0";
    //reassihn a new value
    strcpy(student->last_name, new_name);
}

void fupdate_first_name(Student* student) {
    char new_name[20];
    printf("Enter a new first name: \n");
    fgets(new_name, sizeof(new_name), stdin);
    new_name[strcspn(new_name, "\n")] = "\0";
    //reassign a new value
    strcpy(student->first_name, new_name);
}

void fupdate_age(Student* student) {
    int age;
    printf("Enter a new age: \n");
    scanf("%d", &age);
    student->age = age;
}

void fupdate_adress(Student* student) {
    Adress adress;
    //new street
    printf("Enter new Street \n");
    fgets(adress.street, sizeof(adress.street), stdin);
    adress.street[strcspn(adress.street, "\n")] = "\0";
    //new city
    printf("Enter new city \n");
    fgets(adress.city, sizeof(adress.city), stdin);
    adress.city[strcspn(adress.city, "\n")] = "\0";
    //new postal code
    printf("Enter new postal code \n");
    scanf("%d", &adress.postal_code);

    //reassign new values
    student->adress = adress;
}

void delete_data(Student* student, int index, int count) {
    //if input is not valid
    if(index == 0 || index > count) {
        printf("Enter a valid student index");
    }
    //move the items to the left
    if(index > 0 && index <= count) {
        for (int i = index - 1; i < count; i++)
        {
            student[i] = student[i+1];
        }

        //delete user from db;
        printf("Your data is deleted successfully\n");
        
    }
}


int main() {
    //set max of data
    Student student_db[50];
    int count = 0;
    //declare vars;
    int update, action, delete, update_name, update_age, update_adress, quit = 0, repeat = 1, user = 0;
    int size = sizeof(student_db) / sizeof(student_db[0]);

    while(repeat && !quit) {
        printf("Add: 0, Edit: 1,  Delete: 2, List: 3, Quit: 4\n");
        scanf("%d", &action);
        //handle quit
        if(action == 4) {
            quit++;
        }
        //handle empty db
        if((action == 2 || action == 1) && !count ) {
            printf("No student registred yet!!! Try to add student first \n\n");
        }

        //handle list
        if(action == 3) {
            if(!count) printf("There is no user yet!! Try to add it! \n");
            else  display_users(student_db, count);
        }

         //Add new user
        if(action == 0) {
            Student student;
            //get data from user
            printf("Add a new Student \n");
            getchar();
            get_data(&student);
            student_db[count] = student;
            printf("***User added successfully*** \n");
            count++;
        }

        //handle edit a user
        if(action == 1 && count) {
            int selected_user;
            //select user
            printf("Select user to edit: \n");
            display_users(student_db, count);
            scanf("%d", &selected_user);
            //ask user if he wants to change anything seperately
            //here for name
            selected_user--;
            printf("Name: %s %s. update ?\n (0 yes, 1 no) \n", student_db[selected_user].last_name, student_db[selected_user].first_name);
            scanf("%d", &update_name);
            if(!update_name) {
                //no skip with getchar
                getchar();
                fupdate_first_name(&student_db[selected_user]);
                fupdate_last_name(&student_db[selected_user]);
             }
            //here for age
            printf("Age: %d. update ?\n (0 yes, 1 no) \n", student_db[selected_user].age);
            scanf("%d", &update_age);
            if (!update_age) fupdate_age(&student_db[selected_user]);
            //here for adress
            printf("Adress: %s, %s %d. update ?\n (0 yes, 1 no) \n", student_db[selected_user].adress.street, student_db[selected_user].adress.city, student_db[selected_user].adress.postal_code);
            scanf("%d", &update_adress);
            //noskip fgets
            getchar();
            if(!update_adress) fupdate_adress(&student_db[selected_user]);

            //display the new data
            printf("Your new data is: \n");
            display_data(&student_db[selected_user]);
    
        }
   
        //delete a user
        if(action == 2 && count) {
            int selected_user;
            //select user
            printf("Select user to delete: \n");
            display_users(student_db, count);
            scanf("%d", &selected_user);
            delete_data(student_db, selected_user, count);
            count--;
        }

        repeat++;
    }
    return 0;
}