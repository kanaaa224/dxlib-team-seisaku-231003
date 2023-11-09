#include "kitamura_test.h"
#include "inputCtrl.h"

Scene* kitamura_test::update()
{/*
    if (!wp.GetLevelUpFlg()) {
        if (InputCtrl::GetKeyState(KEY_INPUT_1) == PRESS) {
            wp.SetWeaponType(sword);
        }
        if (InputCtrl::GetKeyState(KEY_INPUT_2) == PRESS) {
            wp.SetWeaponType(dagger);
        }
        if (InputCtrl::GetKeyState(KEY_INPUT_3) == PRESS) {
            wp.SetWeaponType(greatSword);
        }
    }
    wp.Update(p.Player_AimingX(), p.Player_AimingY(),p.Player_Location());
    p.update();*/
    return this;
}

void kitamura_test::draw() const
{
  /*  p.draw();
    wp.Draw();*/
}
