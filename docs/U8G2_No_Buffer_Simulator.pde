/**
 * U8g2 Speed Stress Test (2x Scale)
 * 
 * SPACE: Toggle Snapshot Mode
 * UP/DOWN: Increase/Decrease FrameRate (Simulates I2C Speed)
 */

class Page {
  byte[] buffer; 
  int pageIndex = 0;
  final int totalPages = 8;

  public Page() {
    this.buffer = new byte[128];
  }

  public void step() {
    renderCurrentPage(); 
    pageIndex++;
    if (pageIndex >= totalPages) {
      pageIndex = 0;
    }
    clearBuffer(); 
  }

  private void clearBuffer() {
    for (int i = 0; i < 128; i++) buffer[i] = 0;
  }

  public void drawPixel(int x, int y) {
    if (x < 0 || x >= 128 || y < 0 || y >= 64) return;
    int pageStart = pageIndex * 8;
    int pageEnd = pageStart + 8;

    if (y >= pageStart && y < pageEnd) {
      int localY = y - pageStart;
      buffer[x] |= (1 << localY); 
    }
  }

  public void renderCurrentPage() {
    noStroke();
    for (int x = 0; x < 128; x++) {
      for (int bit = 0; bit < 8; bit++) {
        boolean isSet = ((buffer[x] >> bit) & 1) == 1;
        int screenY = (pageIndex * 8) + bit;
        fill(isSet ? 255 : 0);
        rect(x * 2, screenY * 2, 2, 2);
      }
    }
  }
}

Page u8g2 = new Page();
boolean snapshotMode = false;
int snapX, snapY;
int simFrameRate = 60; // Initial "I2C 100kHz" feel

void setup() {
  size(256, 128); 
  background(0);
}

void draw() {
  frameRate(simFrameRate);
  
  int logicMouseX = mouseX / 2;
  int logicMouseY = mouseY / 2;

  if (u8g2.pageIndex == 0) {
    if (snapshotMode) {
      snapX = logicMouseX;
      snapY = logicMouseY;
    }
  }

  if (snapshotMode) {
    drawFilledSquare(snapX, snapY, 20);
  } else {
    drawFilledSquare(logicMouseX, logicMouseY, 20);
  }
  
  drawIndicator();
  u8g2.step();
}

void drawFilledSquare(int x, int y, int size) {
  int half = size / 2;
  for (int i = x - half; i < x + half; i++) {
    for (int j = y - half; j < y + half; j++) {
      u8g2.drawPixel(i, j);
    }
  }
}

void drawIndicator() {
  if (snapshotMode) {
    // S
    for(int i=2; i<6; i++) { u8g2.drawPixel(i, 2); u8g2.drawPixel(i, 4); u8g2.drawPixel(i, 6); }
    u8g2.drawPixel(2, 3); u8g2.drawPixel(5, 5);
  } else {
    // R
    for(int i=2; i<7; i++) u8g2.drawPixel(2, i);
    u8g2.drawPixel(3, 2); u8g2.drawPixel(4, 2); u8g2.drawPixel(5, 3);
    u8g2.drawPixel(4, 4); u8g2.drawPixel(5, 5); u8g2.drawPixel(6, 6);
  }
}

void keyPressed() {
  if (key == ' ') {
    snapshotMode = !snapshotMode;
    background(0);
  }
  if (keyCode == UP) simFrameRate += 20;
  if (keyCode == DOWN) simFrameRate = max(20, simFrameRate - 20);
  
  println("Simulation FrameRate: " + simFrameRate + " (Actual FPS: " + (simFrameRate/8.0) + ")");
}
