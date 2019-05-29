#include <openGLCD.h>

/*

  Rapunzel.pde

  Short story Rapunzel, taken from gutenberg.org
  Copyright expired at least for US and Germany.
  See www.gutenberg.org for more information.
  
  GLCD Example

  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

   // inform Arduino IDE that we will use GLCD library
#include "M2tk.h"
#include "utility/m2ghglcd.h"

uint8_t uiKeySelectPin = 3;
uint8_t uiKeyDownPin = 2;
uint8_t uiKeyUpPin = 1;
uint8_t uiKeyExitPin = 0;


//m2_rom_char part1[] M2_SECTION_PROGMEM = "1\n2\n3\n4\n5\n6\n" ;
//const m2_rom_char part1[] = "1\n2\n3\n4\n5\n6\n" ;
//typedef char PROGMEM pgm_char;

char part1[] M2_SECTION_PROGMEM =
"RAPUNZEL\n"
"\n"
"There were once a\n"
"man and a woman who\n"
"had long in vain\n"
"wished for a child.\n"
"At length the woman\n"
"hoped that God was\n"
"about to grant her\n"
"desire. These\n"
"people had a little\n"
"window at the back\n"
"of their house from\n"
"which a splendid\n"
"garden could be\n"
"seen, which was\n"
"full of the most\n"
"beautiful flowers\n"
"and herbs. It was,\n"
"however, surrounded\n"
"by a high wall, and\n"
"no one dared to go\n"
"into it because it\n"
"belonged to an\n"
"enchantress, who\n"
"had great power and\n"
"was dreaded by all\n"
"the world. One day\n"
"the woman was\n"
"standing by this\n"
"window and looking\n"
"down into the\n"
"garden, when she\n"
"saw a bed which was\n"
"planted with the\n"
"most beautiful\n"
"rampion (rapunzel),\n"
"and it looked so\n"
"fresh and green\n"
"that she longed for\n"
"it, she quite pined\n"
"away, and began to\n"
"look pale and\n"
"miserable. Then her\n"
"husband was\n"
"alarmed, and asked:\n"
"'What ails you,\n"
"dear wife?' 'Ah,'\n"
"she replied, 'if I\n"
"can't eat some of\n"
"the rampion, which\n"
"is in the garden\n"
"behind our house, I\n"
"shall die.' The\n"
"man, who loved her,\n"
"thought: 'Sooner\n"
"than let your wife\n"
"die, bring her some\n"
"of the rampion\n"
"yourself, let it\n"
"cost what it will.'\n"
"At twilight, he\n"
"clambered down over\n"
"the wall into the\n"
"garden of the\n"
"enchantress,\n"
"hastily clutched a\n"
"handful of rampion,\n"
"and took it to his\n"
"wife. She at once\n"
"made herself a\n"
"salad of it, and\n"
"ate it greedily. It\n"
"tasted so good to\n"
"her--so very good,\n"
"that the next day\n"
"she longed for it\n"
"three times as much\n"
"as before. If he\n"
"was to have any\n"
"rest, her husband\n"
"must once more\n"
"descend into the\n"
"garden. In the\n"
"gloom of evening\n"
"therefore, he let\n"
"himself down again;\n"
"but when he had\n"
"clambered down the\n"
"wall he was\n"
"terribly afraid,\n"
"for he saw the\n"
"enchantress\n"
"standing before\n"
"him. 'How can you\n"
"dare,' said she\n"
"with angry look,\n"
"'descend into my\n"
"garden and steal my\n"
"rampion like a\n"
"thief? You shall\n"
"suffer for it!'\n"
"'Ah,' answered he,\n"
"'let mercy take the\n"
"place of justice, I\n"
"only made up my\n"
"mind to do it out\n"
"of necessity. My\n"
"wife saw your\n"
"rampion from the\n"
"window, and felt\n"
"such a longing for\n"
"it that she would\n"
"have died if she\n"
"had not got some to\n"
"eat.' Then the\n"
"enchantress allowed\n"
"her anger to be\n"
"softened, and said\n"
"to him: 'If the\n"
"case be as you say,\n"
"I will allow you to\n"
"take away with you\n"
"as much rampion as\n"
"you will, only I\n"
"make one condition,\n"
"you must give me\n"
"the child which\n"
"your wife will\n"
"bring into the\n"
"world; it shall be\n"
"well treated, and I\n"
"will care for it\n"
"like a mother.' The\n"
"man in his terror\n"
"consented to\n"
"everything, and\n"
"when the woman was\n"
"brought to bed, the\n"
"enchantress\n"
"appeared at once,\n"
"gave the child the\n"
"name of Rapunzel,\n"
"and took it away\n"
"with her.\n"
"\n"
"Rapunzel grew into\n"
"the most beautiful\n"
"child under the\n"
"sun. When she was\n"
"twelve years old,\n"
"the enchantress\n"
"shut her into a\n"
"tower, which lay in\n"
"a forest, and had\n"
"neither stairs nor\n"
"door, but quite at\n"
"the top was a\n"
"little window. When\n"
"the enchantress\n"
"wanted to go in,\n"
"she placed herself\n"
"beneath it and\n"
"cried:\n"
"\n"
" 'Rapunzel,\n"
"  Rapunzel, Let\n"
"  down your hair to\n"
"  me.'\n"
"\n"
"Rapunzel had\n"
"magnificent long\n"
"hair, fine as spun\n"
"gold, and when she\n"
"heard the voice of\n"
"the enchantress she\n"
"unfastened her\n"
"braided tresses,\n"
"wound them round\n"
"one of the hooks of\n"
"the window above,\n"
"and then the hair\n"
"fell twenty ells\n"
"down, and the\n"
"enchantress climbed\n"
"up by it.\n"
"\n"
"After a year or\n"
"two, it came to\n"
"pass that the\n"
"king's son rode\n"
"through the forest\n"
"and passed by the\n"
"tower. Then he\n"
"heard a song, which\n"
"was so charming\n"
"that he stood still\n"
"and listened. This\n"
"was Rapunzel, who\n"
"in her solitude\n"
"passed her time in\n"
"letting her sweet\n"
"voice resound. The\n"
"king's son wanted\n"
"to climb up to her,\n"
"and looked for the\n"
"door of the tower,\n"
"but none was to be\n"
"found. He rode\n"
"home, but the\n"
"singing had so\n"
"deeply touched his\n"
"heart, that every\n"
"day he went out\n"
"into the forest and\n"
"listened to it.\n"
"Once when he was\n"
"thus standing\n"
"behind a tree, he\n"
"saw that an\n"
"enchantress came\n"
"there, and he heard\n"
"how she cried:\n"
"\n"
;

char part2[] M2_SECTION_PROGMEM =
" 'Rapunzel,\n"
"  Rapunzel, Let\n"
"  down your hair to\n"
"  me.'\n"
"\n"
"Then Rapunzel let\n"
"down the braids of\n"
"her hair, and the\n"
"enchantress climbed\n"
"up to her. 'If that\n"
"is the ladder by\n"
"which one mounts, I\n"
"too will try my\n"
"fortune,' said he,\n"
"and the next day\n"
"when it began to\n"
"grow dark, he went\n"
"to the tower and\n"
"cried:\n"
"\n"
" 'Rapunzel,\n"
"  Rapunzel, Let\n"
"  down your hair to\n"
"  me.'\n"
"\n"
"Immediately the\n"
"hair fell down and\n"
"the king's son\n"
"climbed up.\n"
"\n"
"At first Rapunzel\n"
"was terribly\n"
"frightened when a\n"
"man, such as her\n"
"eyes had never yet\n"
"beheld, came to\n"
"her; but the king's\n"
"son began to talk\n"
"to her quite like a\n"
"friend, and told\n"
"her that his heart\n"
"had been so stirred\n"
"that it had let him\n"
"have no rest, and\n"
"he had been forced\n"
"to see her. Then\n"
"Rapunzel lost her\n"
"fear, and when he\n"
"asked her if she\n"
"would take him for\n"
"her husband, and\n"
"she saw that he was\n"
"young and handsome,\n"
"she thought: 'He\n"
"will love me more\n"
"than old Dame\n"
"Gothel does'; and\n"
"she said yes, and\n"
"laid her hand in\n"
"his. She said: 'I\n"
"will willingly go\n"
"away with you, but\n"
"I do not know how\n"
"to get down. Bring\n"
"with you a skein of\n"
"silk every time\n"
"that you come, and\n"
"I will weave a\n"
"ladder with it, and\n"
"when that is ready\n"
"I will descend, and\n"
"you will take me on\n"
"your horse.' They\n"
"agreed that until\n"
"that time he should\n"
"come to her every\n"
"evening, for the\n"
"old woman came by\n"
"day. The\n"
"enchantress\n"
"remarked nothing of\n"
"this, until once\n"
"Rapunzel said to\n"
"her: 'Tell me, Dame\n"
"Gothel, how it\n"
"happens that you\n"
"are so much heavier\n"
"for me to draw up\n"
"than the young\n"
"king's son--he is\n"
"with me in a\n"
"moment.' 'Ah! you\n"
"wicked child,'\n"
"cried the\n"
"enchantress. 'What\n"
"do I hear you say!\n"
"I thought I had\n"
"separated you from\n"
"all the world, and\n"
"yet you have\n"
"deceived me!' In\n"
"her anger she\n"
"clutched Rapunzel's\n"
"beautiful tresses,\n"
"wrapped them twice\n"
"round her left\n"
"hand, seized a pair\n"
"of scissors with\n"
"the right, and\n"
"snip, snap, they\n"
"were cut off, and\n"
"the lovely braids\n"
"lay on the ground.\n"
"And she was so\n"
"pitiless that she\n"
"took poor Rapunzel\n"
"into a desert where\n"
"she had to live in\n"
"great grief and\n"
"misery.\n"
"\n"
"On the same day\n"
"that she cast out\n"
"Rapunzel, however,\n"
"the enchantress\n"
"fastened the braids\n"
"of hair, which she\n"
"had cut off, to the\n"
"hook of the window,\n"
"and when the king's\n"
"son came and cried:\n"
"\n"
" 'Rapunzel,\n"
"  Rapunzel, Let\n"
"  down your hair to\n"
"  me.'\n"
"\n"
"she let the hair\n"
"down. The king's\n"
"son ascended, but\n"
"instead of finding\n"
"his dearest\n"
"Rapunzel, he found\n"
"the enchantress,\n"
"who gazed at him\n"
"with wicked and\n"
"venomous looks.\n"
"'Aha!' she cried\n"
"mockingly, 'you\n"
"would fetch your\n"
"dearest, but the\n"
"beautiful bird sits\n"
"no longer singing\n"
"in the nest; the\n"
"cat has got it, and\n"
"will scratch out\n"
"your eyes as well.\n"
"Rapunzel is lost to\n"
"you; you will never\n"
"see her again.' The\n"
"king's son was\n"
"beside himself with\n"
"pain, and in his\n"
"despair he leapt\n"
"down from the\n"
"tower. He escaped\n"
"with his life, but\n"
"the thorns into\n"
"which he fell\n"
"pierced his eyes.\n"
"Then he wandered\n"
"quite blind about\n"
"the forest, ate\n"
"nothing but roots\n"
"and berries, and\n"
"did naught but\n"
"lament and weep\n"
"over the loss of\n"
"his dearest wife.\n"
"Thus he roamed\n"
"about in misery for\n"
"some years, and at\n"
"length came to the\n"
"desert where\n"
"Rapunzel, with the\n"
"twins to which she\n"
"had given birth, a\n"
"boy and a girl,\n"
"lived in\n"
"wretchedness. He\n"
"heard a voice, and\n"
"it seemed so\n"
"familiar to him\n"
"that he went\n"
"towards it, and\n"
"when he approached,\n"
"Rapunzel knew him\n"
"and fell on his\n"
"neck and wept. Two\n"
"of her tears wetted\n"
"his eyes and they\n"
"grew clear again,\n"
"and he could see\n"
"with them as\n"
"before. He led her\n"
"to his kingdom\n"
"where he was\n"
"joyfully received,\n"
"and they lived for\n"
"a long time\n"
"afterwards, happy\n"
"and contented.\n"
;


extern M2tk m2;
M2_EXTERN_ALIGN(el_top);

uint8_t total_lines1 = 0;
uint8_t first_visible_line1 = 0;

uint8_t total_lines2 = 0;
uint8_t first_visible_line2 = 0;

void goto_top_fn(m2_el_fnarg_p fnarg) {
  m2.setRoot(&el_top);
}

M2_INFOP(el_info1, "W59l5", &first_visible_line1, &total_lines1, part1, goto_top_fn);
M2_VSB(el_vsb1, "W2r1l5", &first_visible_line1, &total_lines1);
M2_LIST(el_list1) = { &el_info1, &el_vsb1};
M2_HLIST(el_part1, NULL, el_list1);

M2_INFOP(el_info2, "W59l5", &first_visible_line2, &total_lines2, part2, goto_top_fn);
M2_VSB(el_vsb2, "W2r1l5", &first_visible_line2, &total_lines2);
M2_LIST(el_list2) = { &el_info2, &el_vsb2};
M2_HLIST(el_part2, NULL, el_list2);

M2_LABEL(el_goto_title, NULL, "Rapunzel");
M2_ROOT(el_goto_part1, NULL, "Part 1", &el_part1);
M2_ROOT(el_goto_part2, NULL, "Part 2", &el_part2);
M2_LIST(list_menu) = {&el_goto_title, &el_goto_part1, &el_goto_part2};
M2_VLIST(el_menu_vlist, NULL, list_menu);
M2_ALIGN(el_top, "W64H64", &el_menu_vlist);
M2tk m2(&el_top, m2_es_arduino, m2_eh_4bs, m2_gh_glcd_ffs);

void setup() {
  m2.setPin(M2_KEY_SELECT, uiKeySelectPin);
  m2.setPin(M2_KEY_NEXT, uiKeyDownPin);
  m2.setPin(M2_KEY_PREV, uiKeyUpPin);
  m2.setPin(M2_KEY_EXIT, uiKeyExitPin);  
}

void loop() {
  m2.checkKey();
  if ( m2.handleKey() ) {
      m2.draw();
  }
}



