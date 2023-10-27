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

	float Provisional_RStickX;
	float Provisional_RStickY;

	int Provisional_Abtn;

	float Additional_Value;
	float Additional_Value2;
	float Additional_Value3;

	float Avoidance;

	float MoveX;
	float MoveY;
	float MoveZ;

	

public:

	static float MovingX;
	static float MovingY;

	Player();
	~Player();

	void update();

	//ï`âÊèàóù
	void draw() const;

	int Player_AimingX();
	int Player_AimingY();

	int Player_MoveX();
	int Player_MoveY();

	static int Player_MovingX();
	static int Player_MovingY();
};
