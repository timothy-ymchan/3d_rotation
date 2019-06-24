#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vector.h"

#define CAMERA_WIDTH  10
#define CAMERA_HEIGHT 10

#define CAMERA_MAX_X  CAMERA_WIDTH/2
#define CAMERA_MIN_X -CAMERA_WIDTH/2
#define CAMERA_MAX_Y  CAMERA_HEIGHT/2
#define CAMERA_MIN_Y -CAMERA_HEIGHT/2

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

#define SCREEN_MAX_X  SCREEN_WIDTH/2
#define SCREEN_MIN_X -SCREEN_WIDTH/2
#define SCREEN_MAX_Y  SCREEN_HEIGHT/2
#define SCREEN_MIN_Y -SCREEN_HEIGHT/2

#define VECT(X) X->x,X->y


Vector* GetRotated(Vector* o, Vector* k, float a);

void CoordTransform(float camX, float camY, float* screenX, float* screenY);
void DrawPoint(float px, float py);
void DrawLine(float startX,float startY,float endX, float endY);

#define MAX_POINTS 1000
#define MAX_LINES 1000
Vector* Points[MAX_POINTS];
int Lines[MAX_LINES][2];
int PointsLength = 0;
int LinesLength = 0;

int ReadAssets(char* filename);
void FreeAssets();

int main(int argc, char* argv[])
{

    /*  ====================
            Initialization
        ====================*/

    /* Initialize The Figure */
    if(argc != 2){
        printf("Error: Please enter a valid number of arguments\n");
        return -1;
    }
    if(!ReadAssets(argv[1]))
        return -2;

    initwindow(SCREEN_WIDTH,SCREEN_HEIGHT,"3D Projection");

    /* Initialize Rotational Axis */
    Vector* axis = Vector_Create(sqrt(0.3),sqrt(0),sqrt(0.7));
    int division = 100;
    Vector* rotated[MAX_POINTS];

    /*  =================
            Main Loop
        =================*/
    int i,j,k;

    //while(1){
    printf("Generating Animations\n");
    for(i=0;i<division;i++)
    {
        float angle = ((2.0*3.1415926535)/division)*i;

        //printf("Iterations: %i / %i \n",i,division);

        /* Rotate & Draw Every Point */
        for(j=0;j<PointsLength;j++)
        {
            rotated[j] = GetRotated(Points[j],axis,angle);
            DrawPoint(VECT(rotated[j]));
            //printf("%s\n",Vector_GetStr(rotated[j]));
        }


        /* Draw The Edges */
        for(j=0;j<LinesLength;j++){
            int begin = Lines[j][0];
            int end   = Lines[j][1];
            //printf("Line From: %d to %d\n",begin,end);
            DrawLine(VECT(rotated[begin]),VECT(rotated[end]));
        }

        /*Clean up*/
        for(j=0;j<PointsLength;j++)
        {
            Vector_Free(rotated[j]);
        }
        delay(80);
        cleardevice();
        //printf("\n");
    }


    /*  =================
            Cleanup
        =================*/

    system("pause");
    FreeAssets();
    closegraph();
}

void CoordTransform(float camX, float camY, float* screenX, float* screenY)
{
    //Transform View From World Coordinate to Screen Coordinate
    if
    (CAMERA_MIN_X <= camX && camX <= CAMERA_MAX_X &&
    CAMERA_MIN_Y <= camY && camY <= CAMERA_MAX_Y)
    {
        /* If point is in range */
        float disX = camX - CAMERA_MIN_X;
        float disY = camY - CAMERA_MIN_Y;
        *screenX = disX * SCREEN_WIDTH / CAMERA_WIDTH;
        *screenY = SCREEN_HEIGHT - disY * SCREEN_HEIGHT / CAMERA_HEIGHT;
    } else {
        *screenX = *screenY = -1;
    }
}


Vector* GetRotated(Vector* vector, Vector* unitAxis, float angle)
{
    //Rodrigue's Rotation Formula
    Vector* v1 = Vector_Scale(vector,cos(angle));
    Vector* v2 = Vector_Cross(unitAxis,vector);
    Vector_ScaleInternal(v2,sin(angle));

    float scale_factor = Vector_Dot(unitAxis,vector)* (1.0 - cos(angle));
    Vector* v3 = Vector_Scale(unitAxis,scale_factor);

    Vector_AddInternal(v1,v2); // Add v1 v2 and store to v1
    Vector_AddInternal(v1,v3); // Add v1 v3 adn store to v1

    Vector_Free(v2);
    Vector_Free(v3);

    return v1;
}

void DrawPoint(float px, float py)
{
    float sx = 0,sy=0;
    CoordTransform(px, py,&sx,&sy);
    if(sx != -1 && sy != -1)
    {
        circle(sx,sy,3);
    }

}

void DrawLine(float startX, float startY, float endX, float endY)
{
    float sx=0,sy=0,ex=0,ey=0;
    CoordTransform(startX,startY,&sx,&sy);
    CoordTransform(endX,endY,&ex,&ey);
    if(sx != -1 && sy != -1 && ex != -1 && ey != -1)
    {
        line(sx,sy,ex,ey);
    }
}


/*  **************************************************************************** */

int ReadAssets(char* filename)
{
    /* Clear up Point and lines array*/
    int i=0;
    for(i=0;i<MAX_POINTS; i++){
        Points[i] = NULL;
    }
    for(i=0;i<MAX_LINES; i++){
        Lines[i][0] = -1;
        Lines[i][1] = -1;
    }

    /* Read From Files */

    int lastPoint = 0;
    int lastLine = 0;
    int readMode = 0; //ReadMode = 0 is POINTS; ReadMode = 1 is LINES
    FILE* file = fopen(filename,"r");
    if(file){
        char buffer[100];
        while(fgets(buffer,sizeof(buffer),file))
        {
            //Remove \n
            if(buffer[strlen(buffer)-1] == '\n')
                buffer[strlen(buffer)-1] = '\0';

            //printf("[%s]\n",buffer);

            //Check read mode
            if(strcmp(buffer, "POINTS") == 0){
                printf("\nReading Points ... \n\n");
                readMode = 0;
            } else if(strcmp(buffer,"LINES") == 0) {
                printf("\nReading Lines ... \n\n");
                readMode = 1;
            } else {
                if(readMode == 0){
                    //Handle POINTS
                    float x,y,z;
                    sscanf(buffer,"%f,%f,%f",&x,&y,&z);
                    Points[lastPoint] = Vector_Create(x,y,z);
                    printf("Point is added (%.2f,%.2f,%.2f)\n",x,y,z);
                    lastPoint++;
                } else if(readMode == 1){
                    //Handle LINES
                    int start, end;
                    sscanf(buffer,"%d,%d",&start,&end);
                    Lines[lastLine][0] = start;
                    Lines[lastLine][1] = end;
                    printf("Line is added (%02d,%02d)\n",start,end);
                    lastLine++;
                }
            }


        }

        PointsLength = lastPoint;
        LinesLength = lastLine;

        printf("\nPoints Length: %d\n",PointsLength);
        printf("Lines Length: %d\n",LinesLength);
        fclose(file);

        printf("Load Complete.\n\n");

        return 1;
    } else {
        printf("Error: Unable to read file: %s\n",filename);
        return 0;
    }
}


void FreeAssets(){
    int i=0;
    for(i=0;i<MAX_POINTS; i++){
        if(Points[i] != NULL)
            Vector_Free(Points[i]);
        Points[i] = NULL;
    }
    for(i=0;i<MAX_LINES; i++){
        if(Lines[i][0] != -1 || Lines[i][1] != -1)
            Lines[i][0] = Lines[i][1] = -1;
    }
    PointsLength = 0;
    LinesLength = 0;
}
