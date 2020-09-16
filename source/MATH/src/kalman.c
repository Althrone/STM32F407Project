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
    MPU6050_RawDataTypeDef MPU6050_RawDataStruct;
    MPU6050_FloatDataTypeDef MPU6050_FloatDataStruct;
    //����1000�Σ���ƽ��ֵ
    MPU6050_AllRawDataRead(&MPU6050_RawDataStruct);
    MPU6050_RawData2FloatData(&MPU6050_RawDataStruct,&MPU6050_FloatDataStruct);
}

/**
 * @brief   ��ʼ����ʱ����ã�������������
 * @param   Kalman_MPU6050MeanDataStruct: MPU6050����ƽ��ֵ
 * @param   Kalman_AK8975MeanDataStruct: AK8975����ƽ��ֵ
 * @param   Kalman_MPU6050VarDataStruct: MPU6050��������
 * @param   Kalman_AK8975VarDataStruct: AK8975��������
 **/
void Kalman_GetVar(Kalman_MPU6050MeanDataTypeDef* Kalman_MPU6050MeanDataStruct,
                   Kalman_AK8975MeanDataTypeDef* Kalman_AK8975MeanDataStruct,
                   Kalman_MPU6050VarDataTypeDef* Kalman_MPU6050VarDataStruct,
                   Kalman_AK8975VarDataTypeDef* Kalman_AK8975VarDataStruct)
{
    //����1000�Σ��㷽��
}