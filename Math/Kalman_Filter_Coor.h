#pragma once
#include "Kalman_Filter.h"

//对直线计算的卡尔曼滤波器
class Kalman_Coor_Class :public Kalman_Class
{
public:
	//噪声需由实验测量获取
	Kalman_Coor_Class() :noise_measurement_coor(0.0f) {}
	~Kalman_Coor_Class() = default;

	union
	{
		struct
		{
			float x_coor;	//x轴坐标
			float y_coor;	//y轴坐标
			float angle_coor;	//角度值
		};
		float state_variable_data[3];	//状态量数据数组 3*1
	};

	float vcovariance_data[9];	//协方差数据数组,3*3

	float process_data[3];
	float measurement_data[3];

	arm_matrix_instance_f32 process_matrix;
	arm_matrix_instance_f32 measurement_matrix;

	void Init(void) override;
	void Update_Process_Noise(const arm_matrix_instance_f32&input_noise);
	//根据控制量和测量量输出新的状态量
	void Kalman_Filter() { Kalman_Filter(process_matrix, measurement_matrix); }
	arm_matrix_instance_f32 &Kalman_Filter(const arm_matrix_instance_f32& input, const arm_matrix_instance_f32& measurement) override;
	arm_matrix_instance_f32 &Update_Stae_Variable_No_Measurement(const arm_matrix_instance_f32 & input);

private:
	void Init_Data(void) override {};
	void Set_Noise(float noise) override;	//设置卡尔曼滤波器的执行噪声、测量噪声

	//根据上一时刻的状态量和控制量预测这一时刻的状态量
	void Forecast_State_Variable_Process_Model(const arm_matrix_instance_f32& input) override;
	void Forecast_Covariance(void)  override;	//预测协方差矩阵
	void Cal_Kalman_Gain(void)  override;	//计算卡尔曼增益矩阵
	void Update_State_Variable(const arm_matrix_instance_f32& measurement)  override;	//使用测量值更新状态量
	void Update_Covariance(void)  override;	//更新协方差

	float noise_measurement_coor;	//PGV噪声，测量噪声

	float B_data[9];	//3*3 (旋转矩阵)

	float process_noise_covariance_matrix_data[9];
	float measurement_noise_covariance_matrix_data[9];
	float gain_matrix_data[9];

	arm_matrix_instance_f32 B_matrix;	//卡尔曼滤波器中的B

	arm_matrix_instance_f32 state_variable_matrix;	//卡尔曼滤波器中的状态量
	arm_matrix_instance_f32 vcovariance_matrix;	//卡尔曼滤波器中的协方差

	arm_matrix_instance_f32 process_noise_covariance_matrix;	//执行噪声协方差
	arm_matrix_instance_f32 measurement_noise_covariance_matrix;	//测量噪声协方差

	arm_matrix_instance_f32 gain_matrix;	//卡尔曼滤波器中的增益K
};