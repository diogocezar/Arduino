U8GLIB_ST7920_128X64_4X u8g(2, 3, 4 ,5); //Enable, RW, RS, RESET  
void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}
