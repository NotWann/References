#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int selectButton = 27;
const int enterButton = 25;
int select_Menu = 0;
int enter_Select_Menu = 0;

static const unsigned char PROGMEM displayMenu[] = {0xf0,0x80,0x00,0x60,0x00,0x00,0x88,0x00,0x00,0x20,0x00,0x00,0x89,0x87,0xac,0x21,0x88,0x80,0x88,0x88,0x32,0x20,0x48,0x80,0x88,0x87,0x32,0x21,0xc7,0x80,0x88,0x80,0xac,0x22,0x40,0x80,0xf1,0xcf,0x20,0x71,0xe8,0x80,0x00,0x00,0x20,0x00,0x07,0x00};
static const unsigned char PROGMEM displaySelect[] = {0x0f,0x7f,0xff,0x9f,0xff,0x80,0x77,0xff,0xff,0xdf,0xff,0x80,0x76,0x78,0x53,0xde,0x77,0x00,0x77,0x77,0xcd,0xdf,0xb7,0x00,0x77,0x78,0xcd,0xde,0x38,0x00,0x77,0x7f,0x53,0xdd,0xbf,0x00,0x0e,0x30,0xdf,0x8e,0x17,0x00,0xff,0xff,0xdf,0xff,0xf8,0x80};

void select_button_menu() {
  int selectButtonState = digitalRead(selectButton);

  if (selectButtonState == LOW)
  {
    delay(200);
    select_Menu = (select_Menu + 1) % 8;
    
  }
  Serial.print("Select: "); Serial.println(select_Menu);
  Serial.print("State: "); Serial.println(selectButtonState);
}

void draw_select_menu_option() {
  display.clearDisplay();
  
  // Array of y-coordinates for menu options
  int y_positions[] = {7, 15, 23, 31, 39, 47, 56};
  int num_options = sizeof(y_positions) / sizeof(y_positions[0]);
  
  // Ensure select_Menu is within valid range (1 to num_options)
  if (select_Menu < 1 || select_Menu > num_options) {
    for (int i = 0; i < num_options; i++) {
      display.drawBitmap(0, y_positions[i], displayMenu, 41, 8, 1);
    }
  }
  
  // Loop through all positions
  for (int i = 0; i < num_options; i++) {
    // Draw displayMenu at the selected position, displaySelect elsewhere
    if (i == select_Menu - 1) {
      display.drawBitmap(0, y_positions[i], displaySelect, 41, 8, 1);
    } else {
      display.drawBitmap(0, y_positions[i], displayMenu, 41, 8, 1);
    }
  }
}

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
  }
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(enterButton, INPUT_PULLUP);
  display.clearDisplay();
  display.display();
}

void loop() {
  select_button_menu();
  draw_select_menu_option();
  display.display();
}