/** Created by David Praise Chukwuma Kalu **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const char FILENAME[14] = {"File.txt"}; // filename

//structure that contains all values of circle
typedef struct{
    int id;
    float x, y, r, area;
} circle;

//gets all values of circles from FILENAME file to array of circles
void putCirclesToArray(FILE *file,circle x[],int y){
    for(int i=0;i<=y;i++){
        fscanf(file, "%d %f %f %f" , &x[i].id, &x[i].x, &x[i].y, &x[i].r);
    }
}

//gets all values of circles from FILENAME file to array of circles and prints them in order
void printAllData(FILE *file,circle x[],int y){
    for(int i=0;i<=y;i++){
        fscanf(file, "%d %f %f %f" , &x[i].id, &x[i].x, &x[i].y, &x[i].r);
        printf("[ %d (%.2f , %.2f) %.2f ]\n",x[i].id,x[i].x,x[i].y,x[i].r);
    }
}

//Custom scanf that only accepts integers and numbers
float readInput(){
    float num;
    while (scanf("%f",&num) !=1){
        while((getchar()!='\n'));
        printf("Please enter a number\n");
    }
    return num;
}

//scans values for new circle and adds them to file
void userInput(FILE *file, int id){
    float x,y,r;
    printf("Enter the x coordinate : ");
    x=readInput();
    printf("Enter the y coordinate : ");
    y=readInput();
    printf("Enter the radius : ");
    r=readInput();
    fprintf(file,"%d %.2f %.2f %.2f\n",id+2,x,y,r);
}

//Sort the files in the circle in descending order
circle sortFileInDescendingOrder(FILE *file,int x,circle y[]){
    circle temp;
    for(int i=0;i<=x;i++){
        for(int j=i+1;j<=x;j++){
            if(y[i].area<y[j].area){
                temp = y[i];
                y[i]=y[j];
                y[j]=temp;
            }
        }
    }
}

// print out all the circles along with the area
void AreaPrint(FILE *file,circle x[],int y){
    for(int i=0;i<=y;i++){
        printf("[%d, (%.2f, %.2f), %.2f, %.2f]\n",x[i].id,x[i].x,x[i].y,x[i].r,x[i].area);
    }
}

//returns a circle structure from user inputs data
circle InputCircle(){
    circle c;
    printf("\nEnter the x coordinate: ");
    c.x=readInput();
    printf("\nEnter the y coordinate: ");
    c.y=readInput();
    printf("\nEnter the radius: ");
    c.r=readInput();
    printf("\n");
    return c;
}

//read the data back from the chars fed into the filename
circle ExtractData(char line[40]){
    int i;
    float *p;
    circle *c;
    float extractedArray[4];
    char *convertStringToFloat;            //convertStringToFloat is the float element extracted from the char array
    convertStringToFloat = strtok(line," ");
    for(i=0;i<4;i++){
        extractedArray[i]=atof(convertStringToFloat); // converts strings into floats.
    }
    p=&extractedArray[0];
    c->id = extractedArray[0];
    c->x = extractedArray[1];
    c->y = extractedArray[2];
    c->r = extractedArray[3];
    return *c;
}

//calculate the vector length between two points
float DistanceBetweenPts(float x1, float y1, float x2, float y2){
    return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

//checks if 2 circles from our array file intersects with each other
void Intersect(const char *filename,circle x[]){
    FILE *file = fopen(filename, "r");
    int first,second;
    float distance;

    printf("\nEnter your first id : ");
    first = readInput();
    printf("\nEnter your second id : ");
    second = readInput();

    distance = DistanceBetweenPts(x[first].x, x[first].y, x[second].x, x[second].y);

    if((x[first].r+x[second].r)>distance && distance>(abs(x[first].r-x[second].r))){
        printf("\nThey intersect with each other\n");
    }else if((x[first].r+x[second].r)==distance){
        printf("\nThey are touching against each other\n");
    }else{
        printf("\nThey don't intersect with each other\n");
    }
    fclose(file);
}

//asks for values of a new circle and checks if it is contained in any circle from FILENAME file
int Contain(const char *filename,circle x[],int y){

    circle circleIn, iterCircle;
    circleIn=InputCircle();
    FILE *file = fopen(filename,"r");
    char line[40];
    int i;
    float distance;
    int pairExists=0;
    printf("The circle is contained in following places:\n");
    for(i=0;i<y;i++){
        fscanf(file, "%[^\n]", line); // Scans the line until a new line.
        fgetc(file);
        iterCircle=ExtractData(&line);
        distance = DistanceBetweenPts(circleIn.x,circleIn.y,iterCircle.x,iterCircle.y);
            if(distance+circleIn.r <= iterCircle.r){
                printf("[%d,(%f,%f),%f]\n",iterCircle.id,iterCircle.x,iterCircle.y,iterCircle.r);
                pairExists=1;
            }
        }
    return pairExists;
}

int main(){
    int ExitCheck=1;
    int selection;

    while(ExitCheck){
        FILE *file;
        file = fopen(FILENAME,"a+");
        int ch=0,lines=0;

        while(!feof(file)){
            ch = fgetc(file);
            if(ch == '\n'){
                lines++;
            }
        }

        circle a[lines];
        fclose(file);
        file = fopen(FILENAME,"a+");

        // This is used to calculate the area of the circle.
        putCirclesToArray(file,a,lines);
        for(int i=0;i<=lines;i++){
            a[i].area=3.14*a[i].r*a[i].r;
        }
        fclose(file);

        do{ // Math operation selector
            printf("\nSelect the operation that you would like to do.\n");
            printf("1 - Print out all the circles within the file.\n");
            printf("2 - Add a new circle to the file.\n");
            printf("3 - Sort circles by descending area.\n");
            printf("4 - Print out all the circles within the file + Area.\n");
            printf("5 - Print the circle with the smallest area.\n");
            printf("6 - Check if two circles intersect.\n");
            printf("7 - Input a new circle and check if it's contained anywhere.\n");
            printf("8 - Exit.\n");
            printf("\nSelection:");
            selection=readInput();
            if(selection < 0 || selection > 8){
                printf("Invalid input, try again\n");
                selection=0;
            }
        }while(selection<0 || selection >8);

        switch(selection)
        {
            case 1:
                if(lines == 0){
                    printf("Please enter a text manually");
                }
                file = fopen(FILENAME,"a+");
                printAllData(file,a,lines);
                fclose(file);
                break;
            case 2:
                file = fopen(FILENAME,"a+");
                userInput(file,lines);
                fclose(file);
                break;
            case 3:
                file = fopen(FILENAME,"a+");
                sortFileInDescendingOrder(file,lines,a);
                fclose(file);
                file=fopen(FILENAME,"w");
                for(int i=0;i<=lines;i++){
                    fprintf(file,"%d %.2f %.2f %.2f\n",a[i].id,a[i].x,a[i].y,a[i].r);
                }
                fclose(file);
                break;
            case 4:
                file = fopen(FILENAME,"a+");
                AreaPrint(file,a,lines);
                fclose(file);
                break;
            case 5:
                file = fopen(FILENAME,"a+");
                sortFileInDescendingOrder(file,lines,a);
                printf("[%d, (%.2f, %.2f), %.2f, %.2f]\n",a[lines-1].id,a[lines-1].x,a[lines-1].y,a[lines-1].r,a[lines-1].area); // get the last line of our array.
                fclose(file);
                break;
            case 6:
                Intersect(file,a);
                break;
            case 7:
                if(Contain(FILENAME,a,lines)==0){
                    printf("This circle is not contained within any existing circles in the file.\n\n");
                }
                printf("\n");
                break;
            case 8:
                printf("\n******************Thank you for using our program. Exiting the program*******************\n");
                exit(1);
                ExitCheck=0;
                break;
            default:
                printf("Invalid Option\n");
                break;
        }
    }
    return 0;
}
