#pragma once

#define MOVE_RIGHT 0.1
#define MOVE_LEFT -0.1
#define MOVE_UP 0.1
#define MOVE_DOWN -0.1


class Player
{

private:
	int PlayerImg;
	int AimingImg;

	int PlayerX;
	int PlayerY;

	float AimingX;
	float AimingY;

	float Provisional_LStickX;
	float Provisional_LStickY;

	float Additional_Value;

public:

	Player();
	~Player();

	void update();

	//ï`âÊèàóù
	void draw() const;

	int Player_AimingX();
	int Player_AimingY();
};
