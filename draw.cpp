
#include<GL/glut.h> 
using namespace std;

int main () {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    circle(100, 100, 50);
    
    closegraph();
    
    return 0;
}
