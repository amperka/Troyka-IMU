import processing.serial.*;
import toxi.geom.*;
import toxi.processing.*;

// NOTE: requires ToxicLibs to be installed in order to run properly.
// 1. Download from http://toxiclibs.org/downloads
// 2. Extract into [userdir]/Processing/libraries
//    (location may be different on Mac/Linux)
// 3. Run and bask in awesomeness

// The serial port
Serial port;                         

String message;

float[] q = new float[4];
Quaternion quat = new Quaternion(1, 0, 0, 0);
// New line character in ASCII
final char newLine = '\n';
String [] massQ = new String [4];
float[] ypr = new float[3];

void setup()  {
    // Size form 400x400
    size(400, 400, P3D); 
    // Open serial port
    // Replace "COM7" with the COM port on which your arduino is connected
    port = new Serial(this, "COM7", 9600);
}

void draw()  {
    // Read and parse incoming serial message
    serialEvent();
    // Set background to black
    background(0);
    printQuaternions();
    printYawPitchRoll();
    // Set position to centre
    translate(width / 2, height / 2);
    // Begin object
    pushMatrix();
    float[] axis = quat.toAxisAngle();
    rotate(axis[0], axis[2], axis[3], axis[1]);
    // Draw main body in red
    drawBody();
    // Draw front-facing tip in blue
    drawCylinder();
    // Draw Triangles
    drawTriangles();
    // Draw Quads
    drawQuads();
    // End of object
    popMatrix();
    // Send character 's' to Arduino
    port.write('s');
}

void serialEvent() {
    // Read from port until new line (ASCII code 13)
    message = port.readStringUntil(newLine);
    if (message != null) {
        // Split message by commas and store in String array 
        massQ = split(message, ",");
        q[0] = float(massQ[0]);
        q[1] = float(massQ[1]);
        q[2] = float(massQ[2]);
        q[3] = float(massQ[3]);
    }
    // Print values to console
    print(q[0]);
    print("\t");
    print(q[1]); 
    print("\t");
    print(q[2]);   
    print("\t");
    print(q[3]);   
    println("\t");
    // Set our toxilibs quaternion to new data
    quat.set(q[0], q[1], q[2], q[3]);
  
}

void drawCylinder() {
    float topRadius = 0;
    float bottomRadius = 20;
    float tall = 20;
    int sides = 8;
    // Begin object
    pushMatrix();
    translate(0, 0, -120);
    rotateX(PI/2);
    fill(0, 0, 255, 200);

    float angle = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
        for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
        vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
        angle += angleIncrement;
    }
  
    endShape();
    
    // if it is not a cone, draw the circular top cap
    if (topRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
        // Center point
        vertex(0, 0, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
  
    // If it is not a cone, draw the circular bottom cap
    if (bottomRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
        // Center point
        vertex(0, tall, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
    popMatrix(); 
}

void drawBody() {
    fill(255, 0, 0, 200);
    box(10, 10, 200);
}

void drawTriangles() {
    // Draw wings and tail fin in green
    fill(0, 255, 0, 200);
    beginShape(TRIANGLES);
    // Wing top layer
    vertex(-100,  2, 30); vertex(0,  2, -80); vertex(100,  2, 30);
    // Wing bottom layer
    vertex(-100, -2, 30); vertex(0, -2, -80); vertex(100, -2, 30);
    // Tail left layer
    vertex(-2, 0, 98); vertex(-2, -30, 98); vertex(-2, 0, 70);
    // Tail right layer
    vertex( 2, 0, 98); vertex( 2, -30, 98); vertex( 2, 0, 70);
    endShape();
}

void drawQuads() {
    beginShape(QUADS);
    vertex(-100, 2, 30); vertex(-100, -2, 30); vertex(  0, -2, -80); vertex(  0, 2, -80);
    vertex( 100, 2, 30); vertex( 100, -2, 30); vertex(  0, -2, -80); vertex(  0, 2, -80);
    vertex(-100, 2, 30); vertex(-100, -2, 30); vertex(100, -2,  30); vertex(100, 2,  30);
    vertex(-2,   0, 98); vertex(2,   0, 98); vertex(2, -30, 98); vertex(-2, -30, 98);
    vertex(-2,   0, 98); vertex(2,   0, 98); vertex(2,   0, 70); vertex(-2,   0, 70);
    vertex(-2, -30, 98); vertex(2, -30, 98); vertex(2,   0, 70); vertex(-2,   0, 70);
    endShape();
}

void printQuaternions() {
    // Set text mode to shape
    textMode(SHAPE);
    textSize(13);
    fill(255, 255, 255);
    text("Quaternions:", 20, 20, 10);
    text(q[0], 20, 40, 10);
    text(q[1], 20, 60, 10);
    text(q[2], 20, 80, 10);
    text(q[3], 20, 100, 10);
}

void printYawPitchRoll() {
    // Calculate yaw/pitch/roll angles
    ypr[0] = atan2(2*q[1]*q[2] - 2*q[0]*q[3], 2*q[0]*q[0] + 2*q[1]*q[1] - 1) * 57.2;
    ypr[1] = atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1) * 57.2;
    ypr[2] = -atan2(2.0f * (q[0] * q[2] - q[1] * q[3]), 1.0f - 2.0f * (q[2] * q[2] + q[1] *q[1] )) * 57.2;

    text("Yaw:", 150, 20, 10);
    text(ypr[0], 150, 40, 10);
    text("Pitch:", 220, 20, 10);
    text(ypr[1], 220, 40, 10);
    text("Roll:", 290, 20, 10);
    text(ypr[2], 290, 40, 10);
}
