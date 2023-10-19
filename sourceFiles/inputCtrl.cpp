//////////////////////////////////////////////////
// 入力 コントローラー
// 作成：kanaaa224
//////////////////////////////////////////////////
#include "inputCtrl.h"

char InputCtrl::nowBtn[PAD_BUTTONS];
char InputCtrl::oldBtn[PAD_BUTTONS];

XINPUT_STATE InputCtrl::padInput;

PadStick InputCtrl::padLStick;
PadStick InputCtrl::padRStick;

int InputCtrl::nowKey[KEYBOARD_KEYS];

MousePoint InputCtrl::mousePoint;
int InputCtrl::nowMouseClick[2];
int InputCtrl::oldMouseClick[2];