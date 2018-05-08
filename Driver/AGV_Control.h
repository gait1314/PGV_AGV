#pragma once
/*
* AGV运动控制
*/
#include "../Math/Trigonometric.h"
#include "../App/Position.h"

class AGV_Control_Class
{
public:
	AGV_Control_Class() = default;
	virtual ~AGV_Control_Class() = default;

	virtual void Init(void) = 0;
	virtual void Brake(bool value) = 0;
	virtual void Run(bool value) = 0;


	unsigned short Cal_Cycle(void);	//根据车体速度计算控制周期


	void Write_Velocity(const Position_Class::Coordinate_Class&AGV_Current_Coor_InWorld, const Position_Class::Coordinate_Class&AGV_Target_Coor_InWorld,Position_Class::Velocity_Class &AGV_Target_Velocity_InAGV);	//根据AGV在世界坐标系中的当前位置和期望位置，更新速度

	virtual Position_Class::Velocity_Class & Update_Velocity_By_ErrorCoor(const Position_Class::Coordinate_Class&Error_Coor_InAGV, Position_Class::Velocity_Class &AGV_Velocity_InAGV) = 0;	//根据位姿误差更新期望速度
	virtual Position_Class::Velocity_Class& Update_Velocity_By_Limit(Position_Class::Velocity_Class&Velocity) = 0;	//对速度限幅
	virtual void Write_Velocity(Position_Class::Velocity_Class &AGV_Velocity_InAGV) = 0;	//将AGV速度转换为车轮速度，更新velocity
	virtual Position_Class &Update_Post_By_Encoder(Position_Class &Current_InWorld,bool &update_by_extern) = 0; //根据编码器更新世界坐标系下的坐标和速度

	//Position_Class::Coordinate_Class &Absolute_To_Relative(Position_Class::Coordinate_Class &Absolute_Coor, Position_Class::Coordinate_Class &Relative_Coor)
	//{
	//	return Position_Class::Absolute_To_Relative(Absolute_Coor, Relative_Coor, this->Position_InWorld_By_Encoder.Coordinate);
	//} //绝对坐标转换为相对坐标
	//Position_Class::Coordinate_Class &Relative_To_Absolute(Position_Class::Coordinate_Class &Absolute_Coor, Position_Class::Coordinate_Class &Relative_Coor)
	//{
	//	return Position_Class::Relative_To_Absolute(Absolute_Coor, Relative_Coor, this->Position_InWorld_By_Encoder.Coordinate);
	//} //相对坐标转换为绝对坐标

	Position_Class Displacement_Velocity_InAGV_By_Encoder;	//AGV坐标系下由编码器计算得出的位移和速度
	//Position_Class Position_InWorld_By_Encoder;	//世界坐标系下的速度和坐标
	float velocity;	//根据AGV的质心速度2范数(mm/s,°/s)计算控制周期(10us),该值由Write_Velocity函数修改
private:

};
