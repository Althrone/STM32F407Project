#include "main.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2

    RGBLED_Init();
    TIM6_Init();

    IIC_Init();
    USART1_Init();//上位机串口

    PPM_Init();

    MPU6050_Init();
    SPL06_Init();
    AK8975_Init();

    Motor_Init();
    Steer_Init();

    PID_ParamInit();

    //校准代码区
    //获取遥控器数值

    ANO_DT_SendSenserTypeDef ANO_DT_SendSenserStruct;//发送到上位机的传感器数据结构体
    ANO_DT_SendRCDataTypeDef ANO_DT_SendRCDataStruct;//发送到上位机的遥控数据
    ANO_DT_SendStatusTypeDef ANO_DT_SendStatusStruct;//无人机当前姿态，这里我只是随便塞两个数进去看看

    MPU6050_RawDataTypeDef MPU6050_RawDataStruct;
    MPU6050_FloatDataTypeDef MPU6050_FloatDataStruct;
    AK8975_FloatDataTypeDef AK8975_FloatDataStruct;

    ATT_AngleDataTypeDef ATT_AngleDataStruct;
    AK8975_RawDataTypeDef AK8975_RawDataStruct;

    while (1)
    {
        if(CalFlag==1)
        {
            MPU6050_AllRawDataRead(&MPU6050_RawDataStruct);
            MPU6050_RawData2FloatData(&MPU6050_RawDataStruct,&MPU6050_FloatDataStruct);
            AK8975_AllRawDataRead(&AK8975_RawDataStruct);
            //姿态解算
            // AHRS_EKF(&MPU6050_FloatDataStruct,&ATT_AngleDataStruct);
            // ATT_RawData(&MPU6050_FloatDataStruct,
            //             &AK8975_FloatDataStruct,
            //             &ATT_AngleDataStruct);
            AHRS_MahonyUpdate(&MPU6050_FloatDataStruct,
                              &AK8975_FloatDataStruct,
                              &ATT_AngleDataStruct);
            //暴力矫正
            ATT_AngleDataStruct.ATT_AnglePhi-=4.3;
            ATT_AngleDataStruct.ATT_AngleTheta+=3.8;
            ATT_AngleDataStruct.ATT_AnglePsi=0;
            CalFlag=0;
        }
        if(LEDFlag==1)
        {
            RGBLED_StateSet(RGBLED_Yellow,RGBLED_1sMode);
        }

        ANO_DT_SendSenserStruct.ANO_DT_AccX=MPU6050_RawDataStruct.MPU6050_RawAccelX;
        ANO_DT_SendSenserStruct.ANO_DT_AccY=MPU6050_RawDataStruct.MPU6050_RawAccelY;
        ANO_DT_SendSenserStruct.ANO_DT_AccZ=MPU6050_RawDataStruct.MPU6050_RawAccelZ;
        ANO_DT_SendSenserStruct.ANO_DT_GyroX=MPU6050_RawDataStruct.MPU6050_RawGyroX;
        ANO_DT_SendSenserStruct.ANO_DT_GyroY=MPU6050_RawDataStruct.MPU6050_RawGyroY;
        ANO_DT_SendSenserStruct.ANO_DT_GyroZ=MPU6050_RawDataStruct.MPU6050_RawGyroZ;

        ANO_DT_SendSenserStruct.ANO_DT_MagX=AK8975_RawDataStruct.AK8975_RawMagX;
        ANO_DT_SendSenserStruct.ANO_DT_MagY=AK8975_RawDataStruct.AK8975_RawMagY;
        ANO_DT_SendSenserStruct.ANO_DT_MagZ=AK8975_RawDataStruct.AK8975_RawMagZ;

        ANO_DT_SendSenser(USART1,&ANO_DT_SendSenserStruct);
        // 发送遥控器参数到上位机
        PPM_GetRCData(&ANO_DT_SendRCDataStruct);
        ANO_DT_SendRCData(USART1,&ANO_DT_SendRCDataStruct);

        ANO_DT_SendStatusStruct.ANO_DT_Roll=ATT_AngleDataStruct.ATT_AnglePhi*100;
        ANO_DT_SendStatusStruct.ANO_DT_Pitch=ATT_AngleDataStruct.ATT_AngleTheta*100;
        ANO_DT_SendStatusStruct.ANO_DT_Yaw=ATT_AngleDataStruct.ATT_AnglePsi*100;
        ANO_DT_SendStatus(USART1,&ANO_DT_SendStatusStruct);

        FLY_DroneCtrl(&ANO_DT_SendRCDataStruct,&ATT_AngleDataStruct,&MPU6050_FloatDataStruct);
    }
}