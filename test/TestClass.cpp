
#define LiquidCrystal_Test LiquidCrystal
#include "Common.cpp"

unittest(testingClassName) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual("LiquidCrystal_CI", lcd.className());
}

unittest(getRows) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual(1, lcd.getRows());
  lcd.begin(16, 2);
  assertEqual(2, lcd.getRows());
}

unittest(clearBuffer) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // get currently displayed lines
  std::vector<std::string> lines = lcd.getLines();
  // verify that display contains 1 empty line
  assertEqual(1, lines.size());
  assertEqual(0, lines.at(0).length());

  // reset lcd to have two lines
  lcd.begin(16, 2);
  // verify that begin clears the display
  lines = lcd.getLines();
  // verify that display contains 2 empty lines
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());

  // write something to display
  lcd.print("hello world");

  // verify display not empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  // assertEqual(11, lines.at(0).length());
  // assertEqual("hello world", lines.at(0));
  assertEqual(0, lines.at(1).length());

  // clear display
  lcd.clear();

  // verify display is empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());
}

unittest(createCharHigh) {
  // Setup display
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);

  // create some chars
  byte smiley[8] = {B00000, B10001, B00000, B00000, B10001, B01110, B00000};
  byte spaceship[8] = {B00000, B00100, B01110, B01110,
                       B01110, B01010, B00000, B00000};
  lcd.createChar(0, smiley);
  lcd.createChar(4, spaceship);

  // check they were created where we expected them
  byte *character0 = lcd.getCustomCharacter(0);
  byte *character4 = lcd.getCustomCharacter(4);
  for (int bite = 0; bite < 8; bite++) {
    assertEqual(smiley[bite], *(character0 + bite));
    assertEqual(spaceship[bite], *(character4 + bite));
  }
}

unittest_main()
