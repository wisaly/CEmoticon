#include "acckeys.h"
#include "acckeythread.h"

#include <QStringList>

AccKeys::AccKeys()
    : m_arrData(AccKeyThread::COUNT_VK)
{
}

AccKeys AccKeys::fromString( QString keystr,QString separator /*= "+"*/ )
{
    AccKeys keys;
    QStringList keystrs = keystr.split(separator);
    for (int i = 0;i < AccKeyThread::COUNT_VK;i ++)
    {
        QString keyString = translateVKey(i);
        for (int j = 0;j < keystrs.count();j ++)
        {
            if (keyString == keystrs[j])
            {
                keys.setKey(i);
            }
        }
    }

    return keys;
}

bool AccKeys::operator==( AccKeys &keys ) const
{
    return keys.m_arrData == this->m_arrData;
}

bool AccKeys::operator!=( AccKeys &keys ) const
{
    return keys.m_arrData != this->m_arrData;
}

QString AccKeys::translateVKey( int vkey,QString nullString /*= "<Invalid>"*/ )
{
    switch(vkey)
    {
    case 0x01 : // VK_LBUTTON  Left mouse button
        return "LButton";
    case 0x02 : // VK_RBUTTON  Right mouse button
        return "RButton";
    case 0x03 : // VK_CANCEL  Control-break processing
        return "Cancel";
    case 0x04 : // VK_MBUTTON  Middle mouse button (three-button mouse)
        return "MButton";
    case 0x08 : // VK_BACK  backspace key
        return "Backspace";
    case 0x09 : // VK_TAB  tab key
        return "Tab";
    case 0x0C : // VK_CLEAR  clear key
        return "Clear";
    case 0x0D : // VK_RETURN  enter key
        return "Return";
    case 0x10 : // VK_SHIFT  shift key
        return "Shift";
    case 0x11 : // VK_CONTROL  ctrl key
        return "Ctrl";
    case 0x12 : // VK_MENU  alt key
        return "Alt";
    case 0x13 : // VK_PAUSE  pause key
        return "Pause";
    case 0x14 : // VK_CAPITAL  caps lock key
        return "Capital";
    case 0x1B : // VK_ESCAPE  esc key
        return "Escape";
    case 0x20 : // VK_SPACE  spacebar
        return "Space";
    case 0x21 : // VK_PRIOR  page up key
        return "PgUp";
    case 0x22 : // VK_NEXT  page down key
        return "PgDn";
    case 0x23 : // VK_END  end key
        return "End";
    case 0x24 : // VK_HOME  home key
        return "Home";
    case 0x25 : // VK_LEFT  left arrow key
        return "Left";
    case 0x26 : // VK_UP  up arrow key
        return "Up";
    case 0x27 : // VK_RIGHT  right arrow key
        return "Right";
    case 0x28 : // VK_DOWN  down arrow key
        return "Down";
    case 0x29 : // VK_SELECT  select key
        return "Select";
    case 0x2B : // VK_EXECUTE  execute key
        return "Execute";
    case 0x2C : // VK_SNAPSHOT  print screen key
        return "PrtScn";
    case 0x2D : // VK_INSERT  ins key
        return "Insert";
    case 0x2E : // VK_DELETE  del key
        return "Delete";
    case 0x2F : // VK_HELP  help key
        return "Help";
    case 0x30 : // VK_0  0 key
        return "0";
    case 0x31 : // VK_1  1 key
        return "1";
    case 0x32 : // VK_2  2 key
        return "2";
    case 0x33 : // VK_3  3 key
        return "3";
    case 0x34 : // VK_4  4 key
        return "4";
    case 0x35 : // VK_5  5 key
        return "5";
    case 0x36 : // VK_6  6 key
        return "6";
    case 0x37 : // VK_7  7 key
        return "7";
    case 0x38 : // VK_8  8 key
        return "8";
    case 0x39 : // VK_9  9 key
        return "9";
    case 0x41 : // VK_A  a key
        return "A";
    case 0x42 : // VK_B  b key
        return "B";
    case 0x43 : // VK_C  c key
        return "C";
    case 0x44 : // VK_D  d key
        return "D";
    case 0x45 : // VK_E  e key
        return "E";
    case 0x46 : // VK_F  f key
        return "F";
    case 0x47 : // VK_G  g key
        return "G";
    case 0x48 : // VK_H  h key
        return "H";
    case 0x49 : // VK_I  i key
        return "I";
    case 0x4A : // VK_J  j key
        return "J";
    case 0x4B : // VK_K  k key
        return "K";
    case 0x4C : // VK_L  l key
        return "L";
    case 0x4D : // VK_M  m key
        return "M";
    case 0x4E : // VK_N  n key
        return "N";
    case 0x4F : // VK_O  o key
        return "O";
    case 0x50 : // VK_P  p key
        return "P";
    case 0x51 : // VK_Q  q key
        return "Q";
    case 0x52 : // VK_R  r key
        return "R";
    case 0x53 : // VK_S  s key
        return "S";
    case 0x54 : // VK_T  t key
        return "T";
    case 0x55 : // VK_U  u key
        return "U";
    case 0x56 : // VK_V  v key
        return "V";
    case 0x57 : // VK_W  w key
        return "W";
    case 0x58 : // VK_X  x key
        return "X";
    case 0x59 : // VK_Y  y key
        return "Y";
    case 0x5A : // VK_Z  z key
        return "Z";
    case 0x5B : // VK_LWIN  Left Windows key (Microsoft Natural Keyboard)
        return "LWin";
    case 0x5C : // VK_RWIN  Right Windows key (Microsoft Natural Keyboard)
        return "RWin";
    case 0x5D : // VK_APPS  Applications key (Microsoft Natural Keyboard)
        return "Apps";
    case 0x60 : // VK_NUMPAD0  Numeric keypad 0 key
        return "Numpad0";
    case 0x61 : // VK_NUMPAD1  Numeric keypad 1 key
        return "Numpad1";
    case 0x62 : // VK_NUMPAD2  Numeric keypad 2 key
        return "Numpad2";
    case 0x63 : // VK_NUMPAD3  Numeric keypad 3 key
        return "Numpad3";
    case 0x64 : // VK_NUMPAD4  Numeric keypad 4 key
        return "Numpad4";
    case 0x65 : // VK_NUMPAD5  Numeric keypad 5 key
        return "Numpad5";
    case 0x66 : // VK_NUMPAD6  Numeric keypad 6 key
        return "Numpad6";
    case 0x67 : // VK_NUMPAD7  Numeric keypad 7 key
        return "Numpad7";
    case 0x68 : // VK_NUMPAD8  Numeric keypad 8 key
        return "Numpad8";
    case 0x69 : // VK_NUMPAD9  Numeric keypad 9 key
        return "Numpad9";
    case 0x6A : // VK_MULTIPLY  Multiply key
        return "Numpad*";
    case 0x6B : // VK_ADD  Add key
        return "Numpad+";
    case 0x6C : // VK_SEPARATOR  Separator key
        return "Separator";
    case 0x6D : // VK_SUBTRACT  Subtract key
        return "Numpad-";
    case 0x6E : // VK_DECIMAL  Decimal key
        return "Numpad.";
    case 0x6F : // VK_DIVIDE  Divide key
        return "Numpad/";
    case 0x70 : // VK_F1  f1 key
        return "F1";
    case 0x71 : // VK_F2  f2 key
        return "F2";
    case 0x72 : // VK_F3  f3 key
        return "F3";
    case 0x73 : // VK_F4  f4 key
        return "F4";
    case 0x74 : // VK_F5  f5 key
        return "F5";
    case 0x75 : // VK_F6  f6 key
        return "F6";
    case 0x76 : // VK_F7  f7 key
        return "F7";
    case 0x77 : // VK_F8  f8 key
        return "F8";
    case 0x78 : // VK_F9  f9 key
        return "F9";
    case 0x79 : // VK_F10  f10 key
        return "F10";
    case 0x7A : // VK_F11  f11 key
        return "F11";
    case 0x7B : // VK_F12  f12 key
        return "F12";
    case 0x7C : // VK_F13  f13 key
        return "F13";
    case 0x7D : // VK_F14  f14 key
        return "F14";
    case 0x7E : // VK_F15  f15 key
        return "F15";
    case 0x7F : // VK_F16  f16 key
        return "F16";
    case 0x80 : // VK_F17  f17 key
        return "F17";
    case 0x81 : // VK_F18  f18 key
        return "F18";
    case 0x82 : // VK_F19  f19 key
        return "F19";
    case 0x83 : // VK_F20  f20 key
        return "F20";
    case 0x84 : // VK_F21  f21 key
        return "F21";
    case 0x85 : // VK_F22  f22 key
        return "F22";
    case 0x86 : // VK_F23  f23 key
        return "F23";
    case 0x87 : // VK_F24  f24 key
        return "F24";
    case 0x90 : // VK_NUMLOCK  num lock key
        return "Numlock";
    case 0x91 : // VK_SCROLL  scroll lock key
        return "Scroll";
    case 0xA0 : // VK_LSHIFT
        return "LShift";
    case 0xA1 : // VK_RSHIFT
        return "RShift";
    case 0xA2 : // VK_LCONTROL
        return "LCtrl";
    case 0xA3 : // VK_RCONTROL
        return "RCtrl";
    case 0xA4 : // VK_LMENU
        return "LAlt";
    case 0xA5 : // VK_RMENU
        return "RAlt";

    case 0xF6 : // VK_ATTN  Attn key
        return "Attn";
    case 0xF7 : // VK_CRSEL  CrSel key
        return "Crsel";
    case 0xF8 : // VK_EXSEL  ExSel key
        return "Exsel";
    case 0xF9 : // VK_EREOF  Erase EOF key
        return "Ereof";
    case 0xFA : // VK_PLAY  Play key
        return "Play";
    case 0xFB : // VK_ZOOM  Zoom key
        return "Zoom";
    case 0xFC : // VK_NONAME  Reserved for future use.
        return "Noname";
    case 0xFD : // VK_PA1  PA1 key
        return "Pa1";
    case 0xFE : // VK_OEM_CLEAR  Clear key
        return "Clear";

    case 0xBA:   // ';:' for US
        return ";";
    case 0xBB:   // '+' any country
        return "+";
    case 0xBC:   // ',' any country
        return ",";
    case 0xBD:   // '-' any country
        return "-";
    case 0xBE:   // '.' any country
        return ".";
    case 0xBF:   // '/?' for US
        return "/";
    case 0xC0:   // '`~' for US
        return "~";
    case 0xDB:  //  '[{' for US
        return "[";
    case 0xDC:  //  '\|' for US
        return "\\";
    case 0xDD:  //  ']}' for US
        return "]";
    case 0xDE:  //  ''"' for US
        return "'";
    }
    return nullString;
}

AccKeys & AccKeys::setKey( int vkey )
{
    m_arrData.setBit(vkey); return *this;
}

bool AccKeys::existKey( int vkey )
{
    return m_arrData.testBit(vkey);
}

QString AccKeys::toString( QString separator /*= "+"*/ )
{
    QString result;
    for (int i = 0;i < m_arrData.size();i ++)
    {
        if(m_arrData.testBit(i))
        {
            if (!result.isEmpty())
            {
                result += separator;
            }
            result += translateVKey(i);
        }
    }

    return result;
}
