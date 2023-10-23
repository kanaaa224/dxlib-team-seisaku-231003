#include "kitamura_test.h"

Scene* kitamura_test::update()
{


    wp.Update();

    return this;
}

void kitamura_test::draw() const
{
    wp.Draw();
}
