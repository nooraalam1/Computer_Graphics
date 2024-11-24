//Final
#include <graphics.h>
#include <math.h>
#include <iostream>
using namespace std;

const float GRAVITY = 0.5; // Acceleration due to gravity

void drawSky() {
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    rectangle(0, 0, 640, 480); // Cover the entire screen for the sky
    floodfill(1, 1, LIGHTBLUE);
}

void drawCloud(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    ellipse(x, y, 0, 360, 30, 20);
    floodfill(x, y, WHITE);

    ellipse(x + 30, y - 10, 0, 360, 35, 25);
    floodfill(x + 30, y - 10, WHITE);

    ellipse(x + 70, y, 0, 360, 30, 20);
    floodfill(x + 70, y, WHITE);

    ellipse(x + 50, y + 20, 0, 360, 25, 15);
    floodfill(x + 50, y + 20, WHITE);
}

void drawRiver() {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    rectangle(0, 450, 640, 480); // River behind the house at the bottom of the screen
    floodfill(320, 460, BLUE);
}

void drawSoil() {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(0, 440, 640, 450); // Soil surface above the river
    floodfill(320, 445, GREEN);
}

void drawMinimalHouse() {
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    rectangle(250, 350, 400, 450); // House body
    floodfill(251, 351, LIGHTGRAY);

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    rectangle(240, 340, 410, 350); // Roof
    floodfill(241, 341, DARKGRAY);

    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(300, 400, 330, 450); // Door
    floodfill(301, 401, BROWN);

    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    rectangle(260, 370, 290, 400); // Left window
    floodfill(261, 371, LIGHTBLUE);

    rectangle(360, 370, 390, 400); // Right window
    floodfill(361, 371, LIGHTBLUE);

    setcolor(BLACK);
    rectangle(250, 350, 400, 450);
    rectangle(240, 340, 410, 350);
    rectangle(300, 400, 330, 450);
    rectangle(260, 370, 290, 400);
    rectangle(360, 370, 390, 400);
}

void drawWindmill(int x, int y, float angle) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    rectangle(x - 10, y, x + 10, y + 150);
    floodfill(x, y + 75, WHITE);

    int bladeLength = 50;

    line(x, y, x + bladeLength * cos(angle), y - bladeLength * sin(angle));
    line(x, y, x - bladeLength * cos(angle), y + bladeLength * sin(angle));
    line(x, y, x + bladeLength * sin(angle), y + bladeLength * cos(angle));
    line(x, y, x - bladeLength * sin(angle), y - bladeLength * cos(angle));

    circle(x, y, 5);
    floodfill(x, y, WHITE);
}

void drawTree(int x, int y) {
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    rectangle(x - 10, y, x + 10, y + 50); // Tree trunk
    floodfill(x, y + 25, BROWN);

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    circle(x, y - 30, 30); // Tree foliage
    floodfill(x, y - 30, GREEN);
}

void drawCannon(int x, int y) {
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    rectangle(x - 20, y, x + 20, y + 10);
    floodfill(x, y + 5, DARKGRAY);

    rectangle(x - 5, y - 20, x + 5, y);
    floodfill(x, y - 10, DARKGRAY);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x - 15, y + 10, 5);
    circle(x + 15, y + 10, 5);
    floodfill(x - 15, y + 10, BLACK);
    floodfill(x + 15, y + 10, BLACK);
}

void drawCannonball(int x, int y) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x, y, 5);
    floodfill(x, y, BLACK);
}

bool checkCollision(float x1, float y1, float x2, float y2) {
    // Simple distance-based collision detection between two cannonballs
    float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return distance < 10; // If the distance between the two cannonballs is less than 10 pixels
}

void handleCollision(float &vx1, float &vy1, float &vx2, float &vy2) {
    // Elastic collision physics: Swap velocities upon collision for simplicity
    float tempVx = vx1;
    float tempVy = vy1;
    vx1 = vx2;
    vy1 = vy2;
    vx2 = tempVx;
    vy2 = tempVy;
}

// Function to draw the sun
void drawSun(int x, int y, int radius) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(x, y, radius); // Draw the sun as a circle
    floodfill(x, y, YELLOW);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    float angle = 0;
    int cloudX = 0;

    // Cannon positions and cannonball parameters
    const int leftCannonX = 50, leftCannonY = 440;
    const int rightCannonX = 590, rightCannonY = 440;

    float leftCannonballX = leftCannonX, leftCannonballY = leftCannonY;
    float rightCannonballX = rightCannonX, rightCannonballY = rightCannonY;

    float leftVelocityX = 3, leftVelocityY = -8;   // Initial velocity for left cannonball
    float rightVelocityX = -3, rightVelocityY = -8; // Initial velocity for right cannonball

    while (!kbhit()) {
        setactivepage(1);
        setvisualpage(0);

        cleardevice();

        drawSky();
        drawCloud(cloudX, 100);
        drawCloud(cloudX + 200, 80);
        drawCloud(cloudX + 400, 120);

        drawRiver(); // Draw the river behind the house
        drawSoil();  // Draw the soil surface
        drawMinimalHouse();
        drawWindmill(500, 300, angle);

        drawTree(150, 380); // Place trees on the soil surface
        drawTree(450, 380); // Place trees on the soil surface

        drawCannon(leftCannonX, leftCannonY);
        drawCannon(rightCannonX, rightCannonY);

        drawCannonball((int)leftCannonballX, (int)leftCannonballY);
        drawCannonball((int)rightCannonballX, (int)rightCannonballY);

        // Draw the sun at a specific position
        drawSun(550, 50, 30); // Position it at (550, 50) with a radius of 30

        angle += 0.05;
        cloudX = (cloudX + 2) % 640;

        // Update cannonball positions for parabolic motion
        leftCannonballX += leftVelocityX;
        leftCannonballY += leftVelocityY;
        leftVelocityY += GRAVITY;

        rightCannonballX += rightVelocityX;
        rightCannonballY += rightVelocityY;
        rightVelocityY += GRAVITY;

        // Check for collision between the two cannonballs
        if (checkCollision(leftCannonballX, leftCannonballY, rightCannonballX, rightCannonballY)) {
            // Handle collision with velocity swap (simple elastic collision)
            handleCollision(leftVelocityX, leftVelocityY, rightVelocityX, rightVelocityY);
        }

        // Reset cannonballs when they go off-screen or hit the ground
        if (leftCannonballY > 440 || leftCannonballX > 640) {
            leftCannonballX = leftCannonX;
            leftCannonballY = leftCannonY;
            leftVelocityY = -8;
        }
        if (rightCannonballY > 440 || rightCannonballX < 0) {
            rightCannonballX = rightCannonX;
            rightCannonballY = rightCannonY;
            rightVelocityY = -8;
        }

        setvisualpage(1);
        setactivepage(0);

        delay(30);
    }

    closegraph();
    return 0;
}

