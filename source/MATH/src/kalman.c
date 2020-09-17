#include "kalman.h"

/**
 * @brief   ��ʼ����ʱ����ã���������ƽ��ֵ�����ڼ�����������
 * @param   MPU6050_FloatDataStruct: MPU6050��������
 * @param   AK8975_FloatDataStruct: AK8975��������
 * @param   Kalman_MPU6050MeanDataStruct: MPU6050����ƽ��ֵ
 * @param   Kalman_AK8975MeanDataStruct: AK8975����ƽ��ֵ
 **/
void Kalman_GetMean(Kalman_MPU6050MeanDataTypeDef* Kalman_MPU6050MeanDataStruct,
                    Kalman_AK8975MeanDataTypeDef* Kalman_AK8975MeanDataStruct)
{
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelX=0;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelY=0;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelZ=0;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroX=0;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroY=0;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroZ=0;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagX=0;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagY=0;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagZ=0;

    MPU6050_RawDataTypeDef MPU6050_RawDataStruct;
    MPU6050_FloatDataTypeDef MPU6050_FloatDataStruct;
    AK8975_RawDataTypeDef AK8975_RawDataStruct;
    AK8975_FloatDataTypeDef AK8975_FloatDataStruct;
    //����1000�Σ���ƽ��ֵ
    for(uint16_t i=0;i<1000;i++)
    {
        MPU6050_AllRawDataRead(&MPU6050_RawDataStruct);
        MPU6050_RawData2FloatData(&MPU6050_RawDataStruct,&MPU6050_FloatDataStruct);
        AK8975_AllRawDataRead(&AK8975_RawDataStruct);
        AK8975_RawData2FloatData(&AK8975_RawDataStruct,&AK8975_FloatDataStruct);
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelX+=MPU6050_FloatDataStruct.MPU6050_FloatAccelX;
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelY+=MPU6050_FloatDataStruct.MPU6050_FloatAccelY;
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelZ+=MPU6050_FloatDataStruct.MPU6050_FloatAccelZ;
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroX+=MPU6050_FloatDataStruct.MPU6050_FloatGyroX;
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroY+=MPU6050_FloatDataStruct.MPU6050_FloatGyroY;
        Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroZ+=MPU6050_FloatDataStruct.MPU6050_FloatGyroZ;
        Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagX+=AK8975_FloatDataStruct.AK8975_FloatMagX;
        Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagY+=AK8975_FloatDataStruct.AK8975_FloatMagY;
        Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagZ+=AK8975_FloatDataStruct.AK8975_FloatMagZ;
    }
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelX/=1000;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelY/=1000;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanAccelZ/=1000;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroX/=1000;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroY/=1000;
    Kalman_MPU6050MeanDataStruct->Kalman_MPU6050MeanGyroZ/=1000;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagX/=1000;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagY/=1000;
    Kalman_AK8975MeanDataStruct->Kalman_AK8975MeanMagZ/=1000;
}

/**
 * @brief   ��ʼ����ʱ����ã�������������
 * @param   Kalman_MPU6050MeanDataStruct: MPU6050����ƽ��ֵ
 * @param   Kalman_AK8975MeanDataStruct: AK8975����ƽ��ֵ
 * @param   Kalman_MPU6050VarDataStruct: MPU6050��������
 * @param   Kalman_AK8975VarDataStruct: AK8975��������
 **/
void Kalman_GetVar(Kalman_MPU6050VarDataTypeDef* Kalman_MPU6050VarDataStruct,
                   Kalman_AK8975VarDataTypeDef* Kalman_AK8975VarDataStruct)
{
    Kalman_MPU6050MeanDataTypeDef Kalman_MPU6050MeanDataStruct;
    Kalman_AK8975MeanDataTypeDef Kalman_AK8975MeanDataStruct;
    Kalman_GetMean(&Kalman_MPU6050MeanDataStruct,&Kalman_AK8975MeanDataStruct);
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelX=0;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelY=0;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelZ=0;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroX=0;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroY=0;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroZ=0;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagX=0;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagY=0;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagZ=0;

    MPU6050_RawDataTypeDef MPU6050_RawDataStruct;
    MPU6050_FloatDataTypeDef MPU6050_FloatDataStruct;
    AK8975_RawDataTypeDef AK8975_RawDataStruct;
    AK8975_FloatDataTypeDef AK8975_FloatDataStruct;
    //����1000�Σ��㷽��
    for(uint16_t i=0;i<1000;i++)
    {
        MPU6050_AllRawDataRead(&MPU6050_RawDataStruct);
        MPU6050_RawData2FloatData(&MPU6050_RawDataStruct,&MPU6050_FloatDataStruct);
        AK8975_AllRawDataRead(&AK8975_RawDataStruct);
        AK8975_RawData2FloatData(&AK8975_RawDataStruct,&AK8975_FloatDataStruct);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelX=
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelX-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelX)*
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelX-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelX);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelY=
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelY-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelY)*
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelY-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelY);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelZ=
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelZ-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelZ)*
        (MPU6050_FloatDataStruct.MPU6050_FloatAccelZ-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanAccelZ);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroX=
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroX-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroX)*
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroX-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroX);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroY=
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroY-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroY)*
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroY-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroY);
        Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroZ=
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroZ-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroZ)*
        (MPU6050_FloatDataStruct.MPU6050_FloatGyroZ-Kalman_MPU6050MeanDataStruct.Kalman_MPU6050MeanGyroZ);
        Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagX=
        (AK8975_FloatDataStruct.AK8975_FloatMagX-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagX)*
        (AK8975_FloatDataStruct.AK8975_FloatMagX-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagX);
        Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagY=
        (AK8975_FloatDataStruct.AK8975_FloatMagY-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagY)*
        (AK8975_FloatDataStruct.AK8975_FloatMagY-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagY);
        Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagZ=
        (AK8975_FloatDataStruct.AK8975_FloatMagZ-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagZ)*
        (AK8975_FloatDataStruct.AK8975_FloatMagZ-Kalman_AK8975MeanDataStruct.Kalman_AK8975MeanMagZ);
    }
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelX/=1000-1;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelY/=1000-1;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarAccelZ/=1000-1;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroX/=1000-1;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroY/=1000-1;
    Kalman_MPU6050VarDataStruct->Kalman_MPU6050VarGyroZ/=1000-1;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagX/=1000-1;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagY/=1000-1;
    Kalman_AK8975VarDataStruct->Kalman_AK8975VarMagZ/=1000-1;
}